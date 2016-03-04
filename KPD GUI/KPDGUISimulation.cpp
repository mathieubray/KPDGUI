#include "KPDGUISimulation.h"

KPDGUISimulation::KPDGUISimulation(KPDGUIRecord * record, KPDGUISimParameters * params){

	kpdguiRecord = record;
	kpdguiParameters->copyParameters(params);

	/*kpdguiParameters->getOptimizationScheme() = params->getOptimizationScheme();
	kpdguiParameters->getUtilityScheme() = params.utilityScheme;
	kpdguiParameters.maxSize = params.maxSize;
	
	kpdguiParameters.pairFailureRate = params.pairFailureRate;
	kpdguiParameters.adFailureRate = params.adFailureRate;
	kpdguiParameters.exogenousFailureRate = params.exogenousFailureRate;
	
	kpdguiParameters->getAddAdvantageToHighPRACandidates() = params.addAdvantageToHighPRACandidates;
	kpdguiParameters->getPRAAdvantageCutoff() = params->getPRAAdvantageCutoff();
	kpdguiParameters->getPRAAdvantageValue = params->getPRAAdvantageValue;

	kpdguiParameters->getNumberOfSolutions() = params->getNumberOfSolutions();
	kpdguiParameters->getNumberOfEUSimulations() = params->getNumberOfEUSimulations();

	kpdguiParameters.chainStorage = params.chainStorage;
	kpdguiParameters.reserveODonorsForOCandidates = params.reserveODonorsForOCandidates;
	kpdguiParameters.checkAdditionalHLA = params.checkAdditionalHLA;
	kpdguiParameters.includeCompatiblePairs = params.includeCompatiblePairs;
	kpdguiParameters.excludeABDonorsFromSimulation = params.excludeABDonorsFromSimulation;
	kpdguiParameters.allowABBridgeDonors = params.allowABBridgeDonors;*/

}

KPDGUISimulation::~KPDGUISimulation(){

	currentMatchRunStructureNodeLists.clear();

	utilityOfCurrentMatchRunCyclesAndChains.clear();
	expectedUtilityOfCurrentMatchRunCyclesAndChains.clear();
	expectedUtilityOfCurrentMatchRunSets.clear();
	expectedUtilityOfCurrentMatchRunComponents.clear();

	SelectedSolutions.clear();
	SelectedStructures.clear();
	SolutionObjectives.clear();
}

vector<vector<int> > & KPDGUISimulation::getCurrentMatchRunCyclesAndChains(QProgressDialog * progressBar){

	//Parameters
	int maxSize = kpdguiParameters->getMaxSize();
	int maximum = std::max(maxSize + 1, 3);

	QString chainStorage = kpdguiParameters->getChainStorage();
	bool allowABBridgeDonors = kpdguiParameters->getAllowABBridgeDonors();

	vector<vector<int> > storedCyclesAndChains;

	int start = 1;
	int nVertices = kpdguiRecord->getNumberOfVertices();
	vector<int> visitedVector(nVertices + 1, 0);
	vector<int> stack_vec;

	progressBar->setLabelText("Discovering Cycles and Chains...");
	progressBar->setRange(0, nVertices);
	progressBar->setValue(0);

	//Depth-first search of graph
	while (start <= nVertices){
		progressBar->setValue(start);

		visitedVector[start] = 1;
		stack_vec.push_back(start);
		int v = getChild(start, start, visitedVector, kpdguiRecord->incidenceMatrix);
		while (!stack_vec.empty()){

			if (v == -1){
				int top = stack_vec.back();
				stack_vec.pop_back();

				if (top == start){
					visitedVector[top] = 0;
					break;
				}
				visitedVector[top] = 0;
				v = getChild(top, stack_vec.back(), visitedVector, kpdguiRecord->incidenceMatrix);
			}
			else{
				visitedVector[v] = 1;
				stack_vec.push_back(v);

				if (kpdguiRecord->incidenceMatrix[v][start] == true){
					
					int multipleADCheck = 0;
					int index = 0;

					vector<int> potentialCycleOrChain;
					for (unsigned i = 0; i < stack_vec.size(); i++){
						potentialCycleOrChain.push_back(stack_vec[i]);
					}

					for (unsigned i = 0; i < potentialCycleOrChain.size(); i++){
						if (kpdguiRecord->pairInfoVector[potentialCycleOrChain[i]].pairType == KPDPairType::AD){
							multipleADCheck++;
							index = i;
						}
					}

					if (multipleADCheck == 1){
						//Check if size of chain is appropriate
						if ((int)potentialCycleOrChain.size() <= maxSize + 1){
							//Queue up AD to front of chain
							while (index > 0){
								int temp = *(potentialCycleOrChain.begin());
								potentialCycleOrChain.erase(potentialCycleOrChain.begin());
								potentialCycleOrChain.push_back(temp);
								index--;
							}

							bool exclude = false;
							//Check for AB Bridge Donor
							if (!allowABBridgeDonors){
								if (kpdguiRecord->pairInfoVector[potentialCycleOrChain.back()].donorBT == BT_AB){
									exclude = true;
								}
							}

							if (!exclude){
								if (chainStorage == "LAST"){
									storedCyclesAndChains.push_back(potentialCycleOrChain);
								}
								else {
									currentMatchRunStructureNodeLists.push_back(potentialCycleOrChain);
								}
							}
						}
					}

					//Cycle
					else if (multipleADCheck == 0){
						//Check if size of cycle is appropriate
						if ((int)potentialCycleOrChain.size() <= 3){
							if (chainStorage == "FIRST"){
								storedCyclesAndChains.push_back(potentialCycleOrChain);
							}
							else {
								currentMatchRunStructureNodeLists.push_back(potentialCycleOrChain);
							}
						}
					}
				}

				if (stack_vec.size() >= maximum)
					v = -1;
				else {
					v = getChild(start, v, visitedVector, kpdguiRecord->incidenceMatrix);
				}
			}
		}
		start++;
	}

	if (storedCyclesAndChains.size()>0){
		for (vector<vector<int> >::iterator it = storedCyclesAndChains.begin(); it != storedCyclesAndChains.end(); ++it){
			currentMatchRunStructureNodeLists.push_back(*it);
		}
	}
	return currentMatchRunStructureNodeLists;
}

/*
vector<vector<int> > & KPDGUISimulation::getCurrentMatchRunComponents(){

	//Parameters
	int maxSize = kpdguiParameters->getMaxSize();
	int maximum = std::max(maxSize, 3);

	QString chainStorage = kpdguiParameters->getChainStorage();

	vector<vector<int> > storedComponents;
	int nVertices = kpdguiRecord->getNumberOfVertices();

	//Size 2 components
	for (int i = 1; i <= nVertices - 1; i++){
		for (int j = i + 1; j <= nVertices; j++){
			if (kpdguiRecord->incidenceMatrix[i][j] == true && kpdguiRecord->incidenceMatrix[j][i] == true){
				bool chain = (kpdguiRecord->pairInfoVector[i].pairType == KPDPairType::AD || kpdguiRecord->pairInfoVector[j].pairType == KPDPairType::AD);

				vector<int > temp;
				temp.push_back(i); temp.push_back(j);

				if ((chain && chainStorage == "LAST") || (!chain && chainStorage == "FIRST")){
					storedComponents.push_back(temp);
				}
				else {
					currentMatchRunStructureNodeLists.push_back(temp);
				}
			}
		}
	}

	//Size 3 components
	for (int i = 1; i <= nVertices - 2; i++){
		for (int j = i + 1; j <= nVertices - 1; j++){
			for (int k = j + 1; k <= nVertices; k++){
				//i to j
				if (kpdguiRecord->incidenceMatrix[i][j] == false && (kpdguiRecord->incidenceMatrix[i][k] == false || kpdguiRecord->incidenceMatrix[k][j] == false))
					continue;
				//i to k
				if (kpdguiRecord->incidenceMatrix[i][k] == false && (kpdguiRecord->incidenceMatrix[i][j] == false || kpdguiRecord->incidenceMatrix[j][k] == false))
					continue;
				//j to i
				if (kpdguiRecord->incidenceMatrix[j][i] == false && (kpdguiRecord->incidenceMatrix[j][k] == false || kpdguiRecord->incidenceMatrix[k][i] == false))
					continue;
				//j to k
				if (kpdguiRecord->incidenceMatrix[j][k] == false && (kpdguiRecord->incidenceMatrix[j][i] == false || kpdguiRecord->incidenceMatrix[i][k] == false))
					continue;
				//k to i
				if (kpdguiRecord->incidenceMatrix[k][i] == false && (kpdguiRecord->incidenceMatrix[k][j] == false || kpdguiRecord->incidenceMatrix[j][i] == false))
					continue;
				//k to j
				if (kpdguiRecord->incidenceMatrix[k][j] == false && (kpdguiRecord->incidenceMatrix[k][i] == false || kpdguiRecord->incidenceMatrix[i][j] == false))
					continue;

				bool chain = (kpdguiRecord->pairInfoVector[i].pairType == KPDPairType::AD || kpdguiRecord->pairInfoVector[j].pairType == KPDPairType::AD || kpdguiRecord->pairInfoVector[k].pairType == KPDPairType::AD);
				vector<int > temp;
				temp.push_back(i); temp.push_back(j); temp.push_back(k);

				if ((chain && chainStorage == "LAST") || (!chain && chainStorage == "FIRST")){
					storedComponents.push_back(temp);
				}
				else {
					currentMatchRunStructureNodeLists.push_back(temp);
				}
			}
		}
	}

	//Size 4 components
	if (maximum >= 4){
		for (int i = 1; i <= nVertices - 3; i++){
			for (int j = i + 1; j <= nVertices - 2; j++){
				for (int k = j + 1; k <= nVertices - 1; k++){
					for (int l = k + 1; l <= nVertices; l++){
						// i to j
						if (kpdguiRecord->incidenceMatrix[i][j] == false && (kpdguiRecord->incidenceMatrix[i][k] == false || kpdguiRecord->incidenceMatrix[k][j] == false)
							&& (kpdguiRecord->incidenceMatrix[i][l] == false || kpdguiRecord->incidenceMatrix[l][j] == false)
							&& (kpdguiRecord->incidenceMatrix[i][k] == false || kpdguiRecord->incidenceMatrix[k][l] == false || kpdguiRecord->incidenceMatrix[l][j] == false)
							&& (kpdguiRecord->incidenceMatrix[i][l] == false || kpdguiRecord->incidenceMatrix[l][k] == false || kpdguiRecord->incidenceMatrix[k][j] == false))
							continue;
						// i to k
						if (kpdguiRecord->incidenceMatrix[i][k] == false && (kpdguiRecord->incidenceMatrix[i][j] == false || kpdguiRecord->incidenceMatrix[j][k] == false)
							&& (kpdguiRecord->incidenceMatrix[i][l] == false || kpdguiRecord->incidenceMatrix[l][k] == false)
							&& (kpdguiRecord->incidenceMatrix[i][l] == false || kpdguiRecord->incidenceMatrix[l][j] == false || kpdguiRecord->incidenceMatrix[j][k] == false)
							&& (kpdguiRecord->incidenceMatrix[i][j] == false || kpdguiRecord->incidenceMatrix[j][l] == false || kpdguiRecord->incidenceMatrix[l][k] == false))
							continue;
						// i to l
						if (kpdguiRecord->incidenceMatrix[i][l] == false && (kpdguiRecord->incidenceMatrix[i][j] == false || kpdguiRecord->incidenceMatrix[j][l] == false)
							&& (kpdguiRecord->incidenceMatrix[i][k] == false || kpdguiRecord->incidenceMatrix[k][l] == false)
							&& (kpdguiRecord->incidenceMatrix[i][j] == false || kpdguiRecord->incidenceMatrix[j][k] == false || kpdguiRecord->incidenceMatrix[k][l] == false)
							&& (kpdguiRecord->incidenceMatrix[i][k] == false || kpdguiRecord->incidenceMatrix[k][j] == false || kpdguiRecord->incidenceMatrix[j][l] == false))
							continue;
						// j to i
						if (kpdguiRecord->incidenceMatrix[j][i] == false && (kpdguiRecord->incidenceMatrix[j][k] == false || kpdguiRecord->incidenceMatrix[k][i] == false)
							&& (kpdguiRecord->incidenceMatrix[j][l] == false || kpdguiRecord->incidenceMatrix[l][i] == false)
							&& (kpdguiRecord->incidenceMatrix[j][k] == false || kpdguiRecord->incidenceMatrix[k][l] == false || kpdguiRecord->incidenceMatrix[l][i] == false)
							&& (kpdguiRecord->incidenceMatrix[j][l] == false || kpdguiRecord->incidenceMatrix[l][k] == false || kpdguiRecord->incidenceMatrix[k][i] == false))
							continue;
						// j to k
						if (kpdguiRecord->incidenceMatrix[j][k] == false && (kpdguiRecord->incidenceMatrix[j][i] == false || kpdguiRecord->incidenceMatrix[i][k] == false)
							&& (kpdguiRecord->incidenceMatrix[j][l] == false || kpdguiRecord->incidenceMatrix[l][k] == false)
							&& (kpdguiRecord->incidenceMatrix[j][i] == false || kpdguiRecord->incidenceMatrix[i][l] == false || kpdguiRecord->incidenceMatrix[l][k] == false)
							&& (kpdguiRecord->incidenceMatrix[j][l] == false || kpdguiRecord->incidenceMatrix[l][i] == false || kpdguiRecord->incidenceMatrix[i][k] == false))
							continue;
						// j to l
						if (kpdguiRecord->incidenceMatrix[j][l] == false && (kpdguiRecord->incidenceMatrix[j][i] == false || kpdguiRecord->incidenceMatrix[i][l] == false)
							&& (kpdguiRecord->incidenceMatrix[j][k] == false || kpdguiRecord->incidenceMatrix[k][l] == false)
							&& (kpdguiRecord->incidenceMatrix[j][i] == false || kpdguiRecord->incidenceMatrix[i][k] == false || kpdguiRecord->incidenceMatrix[k][l] == false)
							&& (kpdguiRecord->incidenceMatrix[j][k] == false || kpdguiRecord->incidenceMatrix[k][i] == false || kpdguiRecord->incidenceMatrix[i][l] == false))
							continue;
						// k to i
						if (kpdguiRecord->incidenceMatrix[k][i] == false && (kpdguiRecord->incidenceMatrix[k][j] == false || kpdguiRecord->incidenceMatrix[j][i] == false)
							&& (kpdguiRecord->incidenceMatrix[k][l] == false || kpdguiRecord->incidenceMatrix[l][i] == false)
							&& (kpdguiRecord->incidenceMatrix[k][j] == false || kpdguiRecord->incidenceMatrix[j][l] == false || kpdguiRecord->incidenceMatrix[l][i] == false)
							&& (kpdguiRecord->incidenceMatrix[k][l] == false || kpdguiRecord->incidenceMatrix[l][j] == false || kpdguiRecord->incidenceMatrix[j][i] == false))
							continue;
						// k to j
						if (kpdguiRecord->incidenceMatrix[k][j] == false && (kpdguiRecord->incidenceMatrix[k][i] == false || kpdguiRecord->incidenceMatrix[i][j] == false)
							&& (kpdguiRecord->incidenceMatrix[k][l] == false || kpdguiRecord->incidenceMatrix[l][j] == false)
							&& (kpdguiRecord->incidenceMatrix[k][i] == false || kpdguiRecord->incidenceMatrix[i][l] == false || kpdguiRecord->incidenceMatrix[l][j] == false)
							&& (kpdguiRecord->incidenceMatrix[k][l] == false || kpdguiRecord->incidenceMatrix[l][i] == false || kpdguiRecord->incidenceMatrix[i][j] == false))
							continue;
						// k to l
						if (kpdguiRecord->incidenceMatrix[k][l] == false && (kpdguiRecord->incidenceMatrix[k][i] == false || kpdguiRecord->incidenceMatrix[i][l] == false)
							&& (kpdguiRecord->incidenceMatrix[k][j] == false || kpdguiRecord->incidenceMatrix[j][l] == false)
							&& (kpdguiRecord->incidenceMatrix[k][i] == false || kpdguiRecord->incidenceMatrix[i][j] == false || kpdguiRecord->incidenceMatrix[j][l] == false)
							&& (kpdguiRecord->incidenceMatrix[k][j] == false || kpdguiRecord->incidenceMatrix[j][i] == false || kpdguiRecord->incidenceMatrix[i][l] == false))
							continue;
						// l to i
						if (kpdguiRecord->incidenceMatrix[l][i] == false && (kpdguiRecord->incidenceMatrix[l][j] == false || kpdguiRecord->incidenceMatrix[j][i] == false)
							&& (kpdguiRecord->incidenceMatrix[l][k] == false || kpdguiRecord->incidenceMatrix[k][i] == false)
							&& (kpdguiRecord->incidenceMatrix[l][j] == false || kpdguiRecord->incidenceMatrix[j][k] == false || kpdguiRecord->incidenceMatrix[k][i] == false)
							&& (kpdguiRecord->incidenceMatrix[l][k] == false || kpdguiRecord->incidenceMatrix[k][j] == false || kpdguiRecord->incidenceMatrix[j][i] == false))
							continue;
						// l to j
						if (kpdguiRecord->incidenceMatrix[l][j] == false && (kpdguiRecord->incidenceMatrix[l][i] == false || kpdguiRecord->incidenceMatrix[i][j] == false)
							&& (kpdguiRecord->incidenceMatrix[l][k] == false || kpdguiRecord->incidenceMatrix[k][j] == false)
							&& (kpdguiRecord->incidenceMatrix[l][i] == false || kpdguiRecord->incidenceMatrix[i][k] == false || kpdguiRecord->incidenceMatrix[k][j] == false)
							&& (kpdguiRecord->incidenceMatrix[l][k] == false || kpdguiRecord->incidenceMatrix[k][i] == false || kpdguiRecord->incidenceMatrix[i][j] == false))
							continue;
						// l to k
						if (kpdguiRecord->incidenceMatrix[l][k] == false && (kpdguiRecord->incidenceMatrix[l][i] == false || kpdguiRecord->incidenceMatrix[i][k] == false)
							&& (kpdguiRecord->incidenceMatrix[l][j] == false || kpdguiRecord->incidenceMatrix[j][k] == false)
							&& (kpdguiRecord->incidenceMatrix[l][i] == false || kpdguiRecord->incidenceMatrix[i][j] == false || kpdguiRecord->incidenceMatrix[j][k] == false)
							&& (kpdguiRecord->incidenceMatrix[l][j] == false || kpdguiRecord->incidenceMatrix[j][i] == false || kpdguiRecord->incidenceMatrix[i][k] == false))
							continue;

						bool chain = (kpdguiRecord->pairInfoVector[i].pairType == KPDPairType::AD || kpdguiRecord->pairInfoVector[j].pairType == KPDPairType::AD || kpdguiRecord->pairInfoVector[k].pairType == KPDPairType::AD || kpdguiRecord->pairInfoVector[l].pairType == KPDPairType::AD);

						vector<int > temp;
						temp.push_back(i); temp.push_back(j); temp.push_back(k); temp.push_back(l);
						if ((chain && chainStorage == "LAST") || (!chain && chainStorage == "FIRST")){
							storedComponents.push_back(temp);
						}
						else {
							currentMatchRunStructureNodeLists.push_back(temp);
						}
					}
				}
			}
		}
	}

	return currentMatchRunStructureNodeLists;
}
*/

std::vector<std::vector<int > > & KPDGUISimulation::getCurrentMatchRunComponents(QProgressDialog * progressBar){

	//Clear Information from Previous Match Run
	//currentMatchRunNodes.clear();
	//currentMatchRunStructures.clear();

	//Update Match Run Time
	//currentMatchRun++;
	//mostRecentMatchRunTime = currentTime;

	//Collect Nodes for Current Match Run
	//simulationLog << "Match Run: " << currentMatchRun << " at time " << currentTime << std::endl;
	//simulationLog << "Active Pool: ";

	//currentMatchRunNodes.push_back(0);
	//for (unsigned i = 1; i < pairUnderlyingStatus.size(); i++){
		//If pair is active and not already transplanted
		//if (pairTransplantationStatus[i] == NOTTRANSPLANTED && pairUnderlyingStatus[i] == ACTIVE){
			//currentMatchRunNodes.push_back(i);
			//simulationLog << i << " ";
		//}
	//}
	//simulationLog << std::endl;

	//int currentMatchRunSize = (int)currentMatchRunNodes.size() - 1;

	//Build Incidence Matrix
	//std::vector<std::vector<bool> > subIncidenceMatrix;
	//subIncidenceMatrix.assign(1 + currentMatchRunSize, std::vector<bool>(1 + currentMatchRunSize, false));

	int nVertices = kpdguiRecord->getNumberOfVertices();
	bool matchRunContainsADs = false;

	progressBar->setLabelText("Discovering Locally Relevant Subgraphs...");
	progressBar->setRange(0, nVertices);
	progressBar->setValue(0);

	for (int i = 1; i <= nVertices; i++){
		//for (int j = 1; j <= currentMatchRunSize; j++){
			//subIncidenceMatrix[i][j] = incidenceMatrix[currentMatchRunNodes[i]][currentMatchRunNodes[j]];
		//}

		if (kpdguiRecord->pairInfoVector[i].pairType != PAIR){
			matchRunContainsADs = true;
		}
	}

	if (matchRunContainsADs){
		getSCCWithADs(progressBar);
	}

	getSCCPairsOnly(progressBar);

	return currentMatchRunStructureNodeLists;
}

vector<double> & KPDGUISimulation::getUtilityForCurrentMatchRunCyclesAndChains(QProgressDialog * progressBar){

	utilityOfCurrentMatchRunCyclesAndChains.clear();

	progressBar->setLabelText("Calculating Utility...");
	progressBar->setRange(0, currentMatchRunStructureNodeLists.size());
	progressBar->setValue(0);

	//Parameters
	KPDUtilityScheme utilityScheme = kpdguiParameters->getUtilityScheme();

	bool addAdvantageToHighPRACandidates = kpdguiParameters->getAddAdvantageToHighPRACandidates();
	double praAdvantageCutoff = kpdguiParameters->getPRAAdvantageCutoff();
	double praAdvantageValue = kpdguiParameters->getPRAAdvantageValue();
	int i = 0;
	
	for (vector<vector<int> >::iterator itLists = currentMatchRunStructureNodeLists.begin(); itLists != currentMatchRunStructureNodeLists.end(); itLists++){
		double u = 0;
		//Sums over all utility values
		for (vector<int>::iterator itNodes = (*itLists).begin(); itNodes != (*itLists).end() - 1; itNodes++){
			//Transplants
			if (utilityScheme == KPDUtilityScheme::TRANSPLANTS){
				u += kpdguiRecord->viableTransplantMatrix[*itNodes][*(itNodes + 1)];
			}
			//5 year survival
			else if (utilityScheme == KPDUtilityScheme::SURVIVAL5YEAR){
				u += kpdguiRecord->survival5yearMatrix[*itNodes][*(itNodes + 1)];
			}
			//10 year survival
			else if (utilityScheme == KPDUtilityScheme::SURVIVAL10YEAR){
				u += kpdguiRecord->survival10yearMatrix[*itNodes][*(itNodes + 1)];
			}
			//Other utility specification
			else {
				u += kpdguiRecord->scoreMatrix[*itNodes][*(itNodes + 1)];
			}

			if (addAdvantageToHighPRACandidates && kpdguiRecord->pairInfoVector[*(itNodes + 1)].recipPRA >= praAdvantageCutoff){
				u += praAdvantageValue;
			}
		}

		if (utilityScheme == KPDUtilityScheme::TRANSPLANTS){
			u += kpdguiRecord->viableTransplantMatrix[*(itLists->end() - 1)][*(itLists->begin())];
		}
		else if (utilityScheme == KPDUtilityScheme::SURVIVAL5YEAR){
			u += kpdguiRecord->survival5yearMatrix[*(itLists->end() - 1)][*(itLists->begin())];
		}
		else if (utilityScheme == KPDUtilityScheme::SURVIVAL10YEAR){
			u += kpdguiRecord->survival10yearMatrix[*(itLists->end() - 1)][*(itLists->begin())];
		}
		else {
			u += kpdguiRecord->scoreMatrix[*(itLists->end() - 1)][*(itLists->begin())];
		}

		if (addAdvantageToHighPRACandidates && kpdguiRecord->pairInfoVector[*(itLists->begin())].recipPRA >= praAdvantageCutoff){
			u += praAdvantageValue;
		}

		utilityOfCurrentMatchRunCyclesAndChains.push_back(u);
		
		i++;
		progressBar->setValue(i);
		QApplication::processEvents();
	}
	
	return utilityOfCurrentMatchRunCyclesAndChains;
}

vector<double> & KPDGUISimulation::getExpectedUtilityForCurrentMatchRunCyclesAndChains(QProgressDialog * progressBar){
	expectedUtilityOfCurrentMatchRunCyclesAndChains.clear();

	progressBar->setLabelText("Calculating Utility...");
	progressBar->setRange(0, currentMatchRunStructureNodeLists.size());
	progressBar->setValue(0);

	int i = 0;
	for (vector<vector<int> >::iterator it = currentMatchRunStructureNodeLists.begin(); it != currentMatchRunStructureNodeLists.end(); it++){
		i++;		
		double eu = calculateExpectedUtility(*it);
		expectedUtilityOfCurrentMatchRunCyclesAndChains.push_back(eu);
		
		progressBar->setValue(i);
		QApplication::processEvents();
	}

	return expectedUtilityOfCurrentMatchRunCyclesAndChains;
}

vector<double> & KPDGUISimulation::getExpectedUtilityForCurrentMatchRunSets(QProgressDialog * progressBar){

	expectedUtilityOfCurrentMatchRunSets.clear();

	progressBar->setLabelText("Calculating Utility...");
	progressBar->setRange(0, currentMatchRunStructureNodeLists.size());
	progressBar->setValue(0);

	int i = 0;
	for (vector<vector<int> >::iterator it = currentMatchRunStructureNodeLists.begin(); it != currentMatchRunStructureNodeLists.end(); it++){
		i++;
		double eu = calculateExpectedUtilityWithFallbacks(*it);
		expectedUtilityOfCurrentMatchRunSets.push_back(eu);

		progressBar->setValue(i);
		QApplication::processEvents();
	}

	return expectedUtilityOfCurrentMatchRunSets;
}

vector<double> & KPDGUISimulation::getExpectedUtilityForCurrentMatchRunComponents(QProgressDialog * progressBar){

	expectedUtilityOfCurrentMatchRunComponents.clear();
	progressBar->setLabelText("Calculating Utility...");
	progressBar->setRange(0, currentMatchRunStructureNodeLists.size());
	progressBar->setValue(0);

	int i = 0;
	for (vector<vector<int > >::iterator it = currentMatchRunStructureNodeLists.begin(); it != currentMatchRunStructureNodeLists.end(); it++){
		//double eu = calculateExpectedUtilityWithFallbacks(*it);
		i++;
		double eu = estimateExpectedUtilityWithFallbacks(*it);
		expectedUtilityOfCurrentMatchRunComponents.push_back(eu);

		progressBar->setValue(i);
		QApplication::processEvents();
	}

	return expectedUtilityOfCurrentMatchRunComponents;
}

void KPDGUISimulation::getOptimalSolution(QProgressDialog * progressBar){

	KPDOptimizationScheme optScheme = kpdguiParameters->getOptimizationScheme();
	int numberOfSolutions = kpdguiParameters->getNumberOfSolutions();

	progressBar->setLabelText("Finding Optimal Solutions...");
	progressBar->setRange(0, numberOfSolutions);
	progressBar->setValue(0);

	SelectedSolutions.clear();
	SelectedStructures.clear();
	SolutionObjectives.clear();

	int nStructures = (int)currentMatchRunStructureNodeLists.size();
	if (nStructures == 0) return;

	double objective = 0;
	int iteration = 1;

	GRBEnv *env = 0;	//Created outside try; needs to be recollected;
	GRBVar *vars = 0;	//Created outside try; needs to be recollected;
	GRBVar *myVars = new GRBVar[nStructures + 1]; //Created outside try; needs to be recollected;
	try{
		env = new GRBEnv();
		env->set(GRB_IntParam_Threads, 4); // Limit the threads

		GRBModel model = GRBModel(*env);
		model.getEnv().set(GRB_IntParam_OutputFlag, 0);// 0 means no solver output; 1 otherwise;


		//Set utilities on structures
		if (optScheme == KPDOptimizationScheme::MUC)
		{
			for (int i = 1; i <= nStructures; i++){
				string s = "cycle_" + intToString(i);
				myVars[i] = model.addVar(0.0, 1.0, -1 * utilityOfCurrentMatchRunCyclesAndChains[i - 1] /* Max Utility */, GRB_BINARY, s); //The default is min, hence the -1
			}
		}
		else if (optScheme == KPDOptimizationScheme::MEUC)
		{
			for (int i = 1; i <= nStructures; i++){
				string s = "cycle_" + intToString(i);
				myVars[i] = model.addVar(0.0, 1.0, -1 * expectedUtilityOfCurrentMatchRunCyclesAndChains[i - 1] /* Max Utility */, GRB_BINARY, s); //The default is min, hence the -1
			}
		}
		else if (optScheme == KPDOptimizationScheme::MEUS)
		{
			for (int i = 1; i <= nStructures; i++){
				string s = "cycle_" + intToString(i);
				myVars[i] = model.addVar(0.0, 1.0, -1 * expectedUtilityOfCurrentMatchRunSets[i - 1] /* Max Utility */, GRB_BINARY, s); //The default is min, hence the -1
			}
		}
		else if (optScheme == KPDOptimizationScheme::SCC)
		{
			for (int i = 1; i <= nStructures; i++){
				string s = "cycle_" + intToString(i);
				myVars[i] = model.addVar(0.0, 1.0, -1 * expectedUtilityOfCurrentMatchRunComponents[i - 1] /* Max Utility */, GRB_BINARY, s); //The default is min, hence the -1
			}
		}
		model.update();

		int nVertices = kpdguiRecord->getNumberOfVertices();
		//Restriction: Each vertex can only appear at most once in solution
		for (int i = 1; i <= nVertices; i++){
			GRBLinExpr expr = 0;
			for (int j = 0; j <= nStructures - 1; j++){
				for (vector<int>::iterator it = currentMatchRunStructureNodeLists[j].begin(); it != currentMatchRunStructureNodeLists[j].end(); ++it){
					if (*it == i){
						expr += myVars[j + 1];
					}
				}
			}
			string s = "vertex_" + intToString(i);
			model.addConstr(expr, GRB_LESS_EQUAL, 1.0, s); // Disjoint cycles and chains
		}

		model.optimize();
		int optimstatus = model.get(GRB_IntAttr_Status);
		double objval = 0;

		if (numberOfSolutions > 1){
			simLog.append(QString::number(iteration) + "- ");
		}
		simLog.append("Optimization complete / ");

		if (optimstatus == GRB_OPTIMAL) { // GRB_OPTIMAL when the MIPGap is reached, default is 1e-4;
			objval = model.get(GRB_DoubleAttr_ObjVal);
			simLog.append("Optimal objective: " + QString::number((-1)*objval) + "\n");
		}
		else if (optimstatus == GRB_INF_OR_UNBD) {
			simLog.append("Model is infeasible or unbounded\n");
			return;
		}
		else if (optimstatus == GRB_INFEASIBLE) {
			simLog.append("Model is infeasible\n");
			return;
		}
		else if (optimstatus == GRB_UNBOUNDED) {
			simLog.append("Model is unbounded\n");
			return;
		}
		else {
			simLog.append("Optimization was stopped\n");
			return;
		}

		int numvars = model.get(GRB_IntAttr_NumVars);
		vars = model.getVars();

		vector<int> candidateSolution;

		for (int j = 0; j < numvars; j++) {
			GRBVar v = vars[j];
			if (v.get(GRB_DoubleAttr_X) == 1){
				candidateSolution.push_back(j);
			}
		}

		SelectedSolutions.push_back(candidateSolution);
		SolutionObjectives.push_back(objval);

		progressBar->setValue(iteration);
		QApplication::processEvents();

		while (iteration < numberOfSolutions){
			iteration++;
			GRBLinExpr expr = 0;

			//Add restriction against previously found solution
			for (int j = 0; j <= nStructures - 1; j++){
				bool found = false;
				for (vector<int>::iterator it = SelectedSolutions[iteration - 2].begin(); it != SelectedSolutions[iteration - 2].end(); ++it){
					if (*it == j){ found = true; }
				}
				if (found == true){
					expr += (1 - myVars[j + 1]);
				}
				else {
					expr += myVars[j + 1];
				}
			}
			string s = "alternate_" + intToString(iteration - 2);
			model.addConstr(expr, GRB_GREATER_EQUAL, 1.0, s); //Remove previous solution

			model.optimize();

			optimstatus = model.get(GRB_IntAttr_Status);
			simLog.append(QString::number(iteration) + ": ");
			if (optimstatus == GRB_OPTIMAL) { // GRB_OPTIMAL when the MIPGap is reached, default is 1e-4;
				objval = model.get(GRB_DoubleAttr_ObjVal);
				simLog.append("Optimal objective: " + QString::number((-1)*objval) + "\n");
			}
			else if (optimstatus == GRB_INF_OR_UNBD) {
				simLog.append("Model is infeasible or unbounded\n");
				return;
			}
			else if (optimstatus == GRB_INFEASIBLE) {
				simLog.append("Model is infeasible\n");
				return;
			}
			else if (optimstatus == GRB_UNBOUNDED) {
				simLog.append("Model is unbounded\n");
				return;
			}
			else {
				simLog.append("Optimization was stopped\n");
				return;
			}

			numvars = model.get(GRB_IntAttr_NumVars);
			vars = model.getVars();

			vector<int> candidateSolution;

			for (int j = 0; j < numvars; j++) {
				GRBVar v = vars[j];
				if (v.get(GRB_DoubleAttr_X) == 1){
					candidateSolution.push_back(j);
				}
			}

			SelectedSolutions.push_back(candidateSolution);
			SolutionObjectives.push_back(objval);

			progressBar->setValue(iteration);
			QApplication::processEvents();
		}

	}
	catch (GRBException e) {
		simLog.append("Error code = " + QString::number(e.getErrorCode()) + "\n");
		simLog.append(QString::fromStdString(e.getMessage()) + "\n");
	}
	catch (...) {
		simLog.append("Error during optimization\n");
	}

	delete[] myVars;
	delete[] vars;
	delete env;
}

vector<vector<int> > & KPDGUISimulation::returnSolutionSet(){
	return SelectedSolutions;
}

vector<double> & KPDGUISimulation::returnSolutionObjectives(){
	return SolutionObjectives;
}

QString KPDGUISimulation::getSimLog(){
	return simLog;
}

int KPDGUISimulation::getChild(int lower, int current, vector<int> &visitedVector, vector<vector<bool> > & thisIMatrix){
	int nV = (int)visitedVector.size() - 1;
	for (int j = lower + 1; j <= nV; j++){
		if (thisIMatrix[current][j] == true && visitedVector[j] == 0)
			return j;
	}
	return -1;
}


void KPDGUISimulation::getSCCPairsOnly(QProgressDialog * progressBar){

	int progressBarValue = progressBar->value();

	int maxSize = kpdguiParameters->getMaxSize();

	int nVertices = kpdguiRecord->getNumberOfVertices();

	vector<int> currentMatchRunPairs;
	currentMatchRunPairs.push_back(0);
	for (int i = 1; i <= nVertices; i++){
		if (kpdguiRecord->pairInfoVector[i].pairType == PAIR){
			currentMatchRunPairs.push_back(i);
		}
	}

	int numberOfPairs = (int)currentMatchRunPairs.size() - 1;

	//Collect SCCs	
	vector<int> bfsTree;
	vector<int> bfsLevel;
	vector<bool> visited(1 + numberOfPairs, false);

	int next;
	int child;
	int childLevel;

	//Iterate Through Pairs	
	for (int i = 1; i <= numberOfPairs; i++){
		progressBarValue++;
		progressBar->setValue(progressBarValue);
		QApplication::processEvents();

		//Start the with the first pair
		bfsTree.push_back(i);
		bfsLevel.push_back(0);
		visited[i] = true;

		//"next" is the next node
		next = i + 1;
		childLevel = 1;

		//While there are still pairs in the bfsTree
		while (!bfsTree.empty()) {
			// Get child
			child = getChildSCCPairsOnly(bfsTree, bfsLevel, currentMatchRunPairs, visited, next, childLevel, numberOfPairs, kpdguiRecord->incidenceMatrix);

			// If (i) the size of the bfsTree is at the limit or (ii) no children, bfsLevel is currently at the next bfsLevel of the previous node
			if ((int)bfsTree.size() == maxSize || (child == -1 && childLevel == bfsLevel.back() + 1)) {
				next = bfsTree.back() + 1;
				childLevel = bfsLevel.back();

				visited[bfsTree.back()] = false;

				bfsTree.pop_back();
				bfsLevel.pop_back();
			}
			// If no children, bfsLevel is currently at the same bfsLevel of the previous node
			else if (child == -1 && childLevel == bfsLevel.back()) {
				next = i + 1;
				childLevel = bfsLevel.back() + 1;
			}
			// Otherwise
			else {
				bfsTree.push_back(child);
				bfsLevel.push_back(childLevel);

				visited[child] = true;

				if (judgeReverseTreeSCCPair(currentMatchRunPairs, bfsTree, nVertices, kpdguiRecord->incidenceMatrix)) {
					vector<int> newSCC;
					for (vector<int>::iterator itTree = bfsTree.begin(); itTree != bfsTree.end(); itTree++) {
						newSCC.push_back(currentMatchRunPairs[*itTree]);
					}
					currentMatchRunStructureNodeLists.push_back(newSCC);
				}

				next = child + 1;
			}
		}
	}
}

int KPDGUISimulation::getChildSCCPairsOnly(std::vector<int> &tree, std::vector<int> &level, std::vector<int> &pairs, std::vector<bool> &visited, int next, int childLevel, int nodes, std::vector<std::vector<bool> > &incidence){

	for (int child = next; child <= nodes; child++) {
		//Can only visit children not already visited
		if (visited[child] == false){
			//Go through previous nodes
			for (int i = 0; i<(int)level.size(); i++) {
				//At low levels, make sure potential node is not a direct successor
				if (level[i] < childLevel - 1)	{
					if (incidence[pairs[tree[i]]][pairs[child]] == true) {
						break;
					}
				}
				//At previous level, if potential node is a successor, it is the next child
				if (level[i] == childLevel - 1) {
					if (incidence[pairs[tree[i]]][pairs[child]] == true) {
						return child;
					}
				}
			}
		}
	}
	return -1;
}

void KPDGUISimulation::getSCCWithADs(QProgressDialog * progressBar){

	int progressBarValue = progressBar->value();

	int maxSize = kpdguiParameters->getMaxSize();

	vector<int> orderedNodes;

	vector<int> tempNodes;
	int numberOfPairs = 0;
	int numberOfADs = 0;

	int nVertices = kpdguiRecord->getNumberOfVertices();

	for (int i = 1; i <= nVertices; i++){
		if (kpdguiRecord->pairInfoVector[i].pairType == PAIR){
			tempNodes.push_back(i);
			numberOfPairs++;
		}
		else {
			orderedNodes.push_back(i);
			numberOfADs++;
		}
	}

	for (int i = 0; i < tempNodes.size(); i++){
		orderedNodes.push_back(tempNodes[i]);
	}

	vector<vector<int> > listOfBFSTrees;
	vector<vector<int> > listOfBFSLevels;
	vector<int> inducedBFSLevel;

	vector<vector<bool> > adjacentToLowerLevels;

	vector<bool> visited((int)orderedNodes.size(), false);

	int child;
	int next;
	int nextAD;

	int childLevel;
	int childLevelAD;
	int treeSize;

	bool childCanBeAD;
	bool childIsAdjacentToLowerLevels;

	for (int i = 0; i < numberOfADs; i++){

		progressBar->setValue(progressBarValue);
		QApplication::processEvents();

		vector<int> newBFSTree;
		newBFSTree.push_back(i);
		listOfBFSTrees.push_back(newBFSTree);

		treeSize = 1;

		visited[i] = true;

		vector<int> newBFSLevel;
		newBFSLevel.push_back(0);
		listOfBFSLevels.push_back(newBFSLevel);

		inducedBFSLevel.push_back(0);

		vector<bool> newAdjacencyList;
		newAdjacencyList.push_back(false);
		adjacentToLowerLevels.push_back(newAdjacencyList);

		next = numberOfADs; //First regular pair
		nextAD = i + 1;
		childLevel = 1;
		childLevelAD = 1;
		childCanBeAD = false;

		while (!listOfBFSTrees.empty()){
			child = getChildSCCWithADs(childIsAdjacentToLowerLevels, listOfBFSTrees, listOfBFSLevels, inducedBFSLevel, orderedNodes, visited, next, nextAD, childLevel, childLevelAD, childCanBeAD, numberOfADs, kpdguiRecord->incidenceMatrix);

			int mostRecentNodeLevel = listOfBFSLevels.back().back();

			if (treeSize == maxSize || (child == orderedNodes.size() && mostRecentNodeLevel + 1 == childLevel)){
				if (listOfBFSTrees.back().back() < numberOfADs) {
					if (listOfBFSTrees.size() > 1) {
						//If previous super tree level is one higher than the super tree level before it
						if (inducedBFSLevel.back() == inducedBFSLevel[inducedBFSLevel.size() - 2] + 1) {
							//Assign the before super tree level to child level
							childLevel = listOfBFSLevels[listOfBFSLevels.size() - 2].back() + 1;
							//Assign the most recent super tree level to child level AD
							childLevelAD = inducedBFSLevel.back();

							//Assign next to the first listed pair
							next = numberOfADs;
						}
						else {
							childLevel = listOfBFSLevels[listOfBFSLevels.size() - 2].back();
							childLevelAD = inducedBFSLevel.back();

							next = std::max(numberOfADs, listOfBFSTrees[listOfBFSTrees.size() - 2].back() + 1);
						}
					}

					inducedBFSLevel.pop_back();

					nextAD = listOfBFSTrees.back().back() + 1;
					childCanBeAD = true;

					visited[listOfBFSTrees.back().back()] = false;

					listOfBFSTrees.pop_back();
					listOfBFSLevels.pop_back();
					adjacentToLowerLevels.pop_back();
				}

				else {
					nextAD = numberOfADs;
					next = listOfBFSTrees.back().back() + 1;
					if (listOfBFSLevels.back().back() == listOfBFSLevels.back()[listOfBFSLevels.back().size() - 2] + 1){
						childLevelAD = inducedBFSLevel.back() + 1;
					}
					else {
						childLevelAD = inducedBFSLevel.back();
					}

					childLevel = listOfBFSLevels.back().back();

					if (adjacentToLowerLevels.back().back() == true){
						childCanBeAD = false;
					}

					visited[listOfBFSTrees.back().back()] = false;
					listOfBFSTrees.back().pop_back();
					listOfBFSLevels.back().pop_back();
					adjacentToLowerLevels.back().pop_back();
				}
				treeSize--;
			}

			else if (child == orderedNodes.size() && listOfBFSLevels.back().back() == childLevel){
				next = numberOfADs;
				nextAD = i + 1;
				childLevel = childLevel + 1;
				childLevelAD = childLevelAD + 1;
			}

			else {
				if (child < numberOfADs) {
					vector<int> newBFSTree;
					newBFSTree.push_back(child);
					listOfBFSTrees.push_back(newBFSTree);

					vector<int> newBFSLevel;
					newBFSLevel.push_back(0);
					listOfBFSLevels.push_back(newBFSLevel);

					inducedBFSLevel.push_back(childLevelAD);

					vector<bool> newAdjacencyList;
					newAdjacencyList.push_back(childIsAdjacentToLowerLevels);
					adjacentToLowerLevels.push_back(newAdjacencyList);

					next = numberOfADs + 1;
					nextAD = child + 1;
					childLevel = 0;

					if (childIsAdjacentToLowerLevels == false) {
						childCanBeAD = false;
					}
				}

				else {
					listOfBFSTrees.back().push_back(child);
					listOfBFSLevels.back().push_back(childLevel);
					if (childCanBeAD == true){
						adjacentToLowerLevels.back().push_back(false);
					}
					else {
						adjacentToLowerLevels.back().push_back(childIsAdjacentToLowerLevels);

						if (childIsAdjacentToLowerLevels == true || (listOfBFSTrees.size() == 1 && listOfBFSTrees.front().size() == 2)){
							childCanBeAD = true;
						}
					}

					next = child + 1;
					nextAD = listOfBFSTrees.back().at(0) + 1;
					childLevelAD = inducedBFSLevel.back();
				}

				treeSize++;
				visited[child] = true;
				if (childCanBeAD == true) {
					vector<int> newSCC;
					for (int i = 0; i < listOfBFSTrees.size(); i++) {
						for (int j = 0; j < listOfBFSTrees[i].size(); j++)	{
							newSCC.push_back(orderedNodes[listOfBFSTrees[i][j]]);
						}
					}
					currentMatchRunStructureNodeLists.push_back(newSCC);
				}
			}
		}
	}
}

int KPDGUISimulation::getChildSCCWithADs(bool &childIsAdjacentToLowerLevels, std::vector<std::vector<int> > &trees, std::vector<std::vector<int> > &levels, std::vector<int> &inducedLevels, std::vector<int> &ordered, std::vector<bool> &visited, int &next, int &nextAD, int &childLevel, int &childLevelAD, bool &childCanBeAD, int &ads, std::vector<std::vector<bool> > &incidence){
	bool breakFlag;

	int numberOfNodes = (int)ordered.size() - 1;

	if (childCanBeAD && !(inducedLevels.size() == 1 && childLevelAD == 0)) {
		//Iterate through ads as potential child
		for (int child = nextAD; child < ads; child++)  {
			if (visited[child] == false) {
				breakFlag = false;

				childIsAdjacentToLowerLevels = false;

				for (int i = 0; i < (int)trees.size(); i++)	{
					if (inducedLevels[i] < childLevelAD - 1) {
						for (int j = 0; j < trees[i].size(); j++){
							int node = ordered[trees[i][j]];
							int potentialChild = ordered[child];

							if (incidence[node][potentialChild] == true || incidence[potentialChild][node] == true)
							{
								breakFlag = true;
								break;
							}
						}
					}
					else if (inducedLevels[i] == childLevelAD - 1){
						if (trees[i][0] < child){
							for (int j = 0; j < trees[i].size(); j++){
								int node = ordered[trees[i][j]];
								int potentialChild = ordered[child];

								if (incidence[node][potentialChild] == true) {
									breakFlag = true;
									break;
								}

								if (incidence[potentialChild][node] == true){
									childIsAdjacentToLowerLevels = true;
								}
							}
						}
						else {
							for (int j = 0; j < trees[i].size(); j++){
								int node = ordered[trees[i][j]];
								int potentialChild = ordered[child];

								if (incidence[potentialChild][node]) {
									breakFlag = true;
									break;
								}

								if (incidence[node][potentialChild]) {
									childIsAdjacentToLowerLevels = true;
								}
							}
						}
					}

					if (breakFlag) {
						break;
					}
				}

				if (breakFlag == false){
					return child;
				}
			}
		}
	}

	if (!(trees.back().size() == 1 && childLevel == 0)) {
		//Start at "Next", iterate through all pairs.
		for (int child = next; child < ordered.size(); child++) {
			if (visited[child] == false) {
				breakFlag = false;

				childIsAdjacentToLowerLevels = false;

				for (int i = 0; i < (int)trees.size(); i++)	{
					//Iterator is at last trees.
					if (i == int(trees.size()) - 1) {
						//Iterate through current trees
						for (int j = 0; j < trees[i].size(); j++){

							//Current Node is at a low level
							if (levels[i][j] < childLevel - 1) {
								int node = ordered[trees[i][j]];
								int potentialChild = ordered[child];

								if (incidence[node][potentialChild] == true) {
									breakFlag = true;
									break;
								}
							}

							//Current node is at previous level
							else if (levels[i][j] == childLevel - 1) {
								int node = ordered[trees[i][j]];
								int potentialChild = ordered[child];

								if (incidence[node][potentialChild] == true) {
									return child;
								}
							}
						}
					}
					//Induced BFS level is at low level
					else if (inducedLevels[i] < inducedLevels.back() - 1) {
						for (int j = 0; j < (int)trees[i].size(); j++){
							int node = ordered[trees[i][j]];
							int potentialChild = ordered[child];

							if (incidence[node][potentialChild] == true || incidence[potentialChild][node] == true){
								breakFlag = true;
								break;
							}
						}
					}
					//Induced BFS level is at previous level
					else if (inducedLevels[i] == inducedLevels.back() - 1) {
						//if root of current trees is less than root of most recent trees
						if (trees[i][0] < trees.back()[0]) {
							//Iterate through nodes
							for (int j = 0; j < trees[i].size(); j++) {
								int node = ordered[trees[i][j]];
								int potentialChild = ordered[child];

								if (incidence[node][potentialChild] == true) {
									breakFlag = true;
									break;
								}

								if (incidence[potentialChild][node] == true) {
									childIsAdjacentToLowerLevels = true;
								}
							}
						}
						else {
							//Iterate through nodes 
							for (int j = 0; j < trees[i].size(); j++) {
								int node = ordered[trees[i][j]];
								int potentialChild = ordered[child];

								if (incidence[potentialChild][node] == true) {
									breakFlag = true;
									break;
								}

								if (incidence[node][potentialChild] == true) {
									childIsAdjacentToLowerLevels = true;
								}
							}
						}
					}
					//Induced BFS level is at same level
					else if (inducedLevels[i] == inducedLevels.back()) {
						//If root of current trees is less than root of most recent trees
						if (trees[i][0] < trees.back()[0]) {
							//Iterate through current trees
							for (int j = 0; j < trees[i].size(); j++) {
								int node = ordered[trees[i][j]];
								int potentialChild = ordered[child];

								if (incidence[node][potentialChild] == true){
									breakFlag = true;
									break;
								}
							}
						}
					}

					if (breakFlag) {
						break;
					}
				}
			}
		}
	}

	return (int)ordered.size();
}

bool KPDGUISimulation::judgeReverseTreeSCCPair(std::vector<int> &pairs, std::vector<int> &tree, int size, std::vector<std::vector<bool> > &incidence){

	std::vector<std::vector<bool> > reverseMatrix;
	reverseMatrix.assign(1 + size, std::vector<bool>(1 + size, false));

	for (int i = 1; i <= size; i++){
		for (int j = 1; j <= size; j++){
			if (i != j){
				reverseMatrix[j][i] = incidence[i][j];
			}
		}
	}

	int treeSize = (int)tree.size();

	std::vector<bool> visited;
	visited.assign(1 + size, false);

	std::queue<int> bfsTree;
	bfsTree.push(tree[0]);
	visited[tree[0]] = true;

	int curr = 1;
	while (!bfsTree.empty()) {
		int u = bfsTree.front();
		bfsTree.pop();

		for (int i = curr; i < treeSize; i++){
			if (visited[tree[i]] == false && reverseMatrix[pairs[u]][pairs[tree[i]]] == true){
				visited[tree[i]] = true;
				bfsTree.push(tree[i]);
			}
		}
	}

	for (int i = 0; i < treeSize; i++){
		if (!visited[tree[i]]){
			return false;
		}
	}

	return true;
}

double KPDGUISimulation::calculateExpectedUtility(vector<int> structure){

	//Parameters
	KPDUtilityScheme utilityScheme = kpdguiParameters->getUtilityScheme();

	bool addAdvantageToHighPRACandidates = kpdguiParameters->getAddAdvantageToHighPRACandidates();
	double praAdvantageCutoff = kpdguiParameters->getPRAAdvantageCutoff();
	double praAdvantageValue = kpdguiParameters->getPRAAdvantageValue();

	bool chain = (kpdguiRecord->pairInfoVector[*(structure.begin())].pairType == KPDPairType::AD);

	double expUtility = 0.0;
	double cycleProb = 1.0;
	double cycleUtil = 0.0;

	//Chain
	if (chain == true){
		//Utility based on number of structure
		if (utilityScheme == KPDUtilityScheme::TRANSPLANTS){
			cycleUtil = kpdguiRecord->viableTransplantMatrix[*(structure.begin())][*(structure.begin() + 1)];
		}
		//Utility based on 5 year survival
		else if (utilityScheme == KPDUtilityScheme::SURVIVAL5YEAR){
			cycleUtil = kpdguiRecord->survival5yearMatrix[*(structure.begin())][*(structure.begin() + 1)];
		}
		//Utility based on 10 year survival
		else if (utilityScheme == KPDUtilityScheme::SURVIVAL10YEAR){
			cycleUtil = kpdguiRecord->survival10yearMatrix[*(structure.begin())][*(structure.begin() + 1)];
		}
		//Utility based on other specified scoring matrix
		else {
			cycleUtil = kpdguiRecord->scoreMatrix[*(structure.begin())][*(structure.begin() + 1)];
		}

		if (addAdvantageToHighPRACandidates && kpdguiRecord->pairInfoVector[*(structure.begin() + 1)].recipPRA >= praAdvantageCutoff){
			cycleUtil += praAdvantageValue;
		}

		cycleProb = kpdguiRecord->pairInfoVector[*(structure.begin())].uncertainty*kpdguiRecord->pairInfoVector[*(structure.begin() + 1)].uncertainty*kpdguiRecord->probabilityMatrix[*(structure.begin())][*(structure.begin() + 1)];

		if (structure.size() == 2){
			expUtility = cycleProb*cycleUtil;
		}

		//Longer Chains
		else if (structure.size() > 2){
			for (vector<int >::iterator itTransplants = structure.begin() + 1; itTransplants != structure.end() - 2; ++itTransplants){
				//Probability of continuing to next transplant
				double probContinue = kpdguiRecord->pairInfoVector[*(itTransplants + 1)].uncertainty*kpdguiRecord->probabilityMatrix[*itTransplants][*(itTransplants + 1)];
				expUtility += (1 - probContinue)*cycleUtil*cycleProb;

				cycleProb = cycleProb*probContinue;

				//Add additional utility from new transplant
				if (utilityScheme == KPDUtilityScheme::TRANSPLANTS){
					cycleUtil += kpdguiRecord->viableTransplantMatrix[*itTransplants][*(itTransplants + 1)];
				}
				else if (utilityScheme == KPDUtilityScheme::SURVIVAL5YEAR){
					cycleUtil += kpdguiRecord->survival5yearMatrix[*itTransplants][*(itTransplants + 1)];
				}
				else if (utilityScheme == KPDUtilityScheme::SURVIVAL10YEAR){
					cycleUtil += kpdguiRecord->survival10yearMatrix[*itTransplants][*(itTransplants + 1)];
				}
				else {
					cycleUtil += kpdguiRecord->scoreMatrix[*itTransplants][*(itTransplants + 1)];
				}

				if (addAdvantageToHighPRACandidates && kpdguiRecord->pairInfoVector[*(itTransplants + 1)].recipPRA >= praAdvantageCutoff){
					cycleUtil += praAdvantageValue;
				}
			}

			//Final transplant
			double probContinue = kpdguiRecord->pairInfoVector[*(structure.end() - 1)].uncertainty*kpdguiRecord->probabilityMatrix[*(structure.end() - 2)][*(structure.end() - 1)];
			expUtility += (1 - probContinue)*cycleUtil*cycleProb;

			cycleProb = cycleProb*probContinue;
			if (utilityScheme == KPDUtilityScheme::TRANSPLANTS){
				cycleUtil += kpdguiRecord->viableTransplantMatrix[*(structure.end() - 2)][*(structure.end() - 1)];
			}
			else if (utilityScheme == KPDUtilityScheme::SURVIVAL5YEAR){
				cycleUtil += kpdguiRecord->survival5yearMatrix[*(structure.end() - 2)][*(structure.end() - 1)];
			}
			else if (utilityScheme == KPDUtilityScheme::SURVIVAL10YEAR){
				cycleUtil += kpdguiRecord->survival10yearMatrix[*(structure.end() - 2)][*(structure.end() - 1)];
			}
			else {
				cycleUtil += kpdguiRecord->scoreMatrix[*(structure.end() - 2)][*(structure.end() - 1)];
			}

			if (addAdvantageToHighPRACandidates && kpdguiRecord->pairInfoVector[*(structure.end() - 1)].recipPRA >= praAdvantageCutoff){
				cycleUtil += praAdvantageValue;
			}

			expUtility += cycleUtil*cycleProb;
		}
	}

	//Cycles
	else{
		//Calculates cycle probability and cycle utility
		cycleProb = kpdguiRecord->pairInfoVector[*(structure.begin())].uncertainty;

		for (vector<int >::iterator itTransplants = structure.begin(); itTransplants != structure.end() - 1; ++itTransplants){
			cycleProb = cycleProb*kpdguiRecord->pairInfoVector[*(itTransplants + 1)].uncertainty*kpdguiRecord->probabilityMatrix[*itTransplants][*(itTransplants + 1)];
			if (utilityScheme == KPDUtilityScheme::TRANSPLANTS){
				cycleUtil += kpdguiRecord->viableTransplantMatrix[*itTransplants][*(itTransplants + 1)];
			}
			else if (utilityScheme == KPDUtilityScheme::SURVIVAL5YEAR){
				cycleUtil += kpdguiRecord->survival5yearMatrix[*itTransplants][*(itTransplants + 1)];
			}
			else if (utilityScheme == KPDUtilityScheme::SURVIVAL10YEAR){
				cycleUtil += kpdguiRecord->survival10yearMatrix[*itTransplants][*(itTransplants + 1)];
			}
			else {
				cycleUtil += kpdguiRecord->scoreMatrix[*itTransplants][*(itTransplants + 1)];
			}

			if (addAdvantageToHighPRACandidates && kpdguiRecord->pairInfoVector[*(itTransplants + 1)].recipPRA >= praAdvantageCutoff){
				cycleUtil += praAdvantageValue;
			}
		}

		cycleProb = cycleProb*kpdguiRecord->probabilityMatrix[*(structure.end() - 1)][*(structure.begin())];

		if (utilityScheme == KPDUtilityScheme::TRANSPLANTS){
			cycleUtil += kpdguiRecord->viableTransplantMatrix[*(structure.end() - 1)][*(structure.begin())];
		}
		else if (utilityScheme == KPDUtilityScheme::SURVIVAL5YEAR){
			cycleUtil += kpdguiRecord->survival5yearMatrix[*(structure.end() - 1)][*(structure.begin())];
		}
		else if (utilityScheme == KPDUtilityScheme::SURVIVAL10YEAR){
			cycleUtil += kpdguiRecord->survival10yearMatrix[*(structure.end() - 1)][*(structure.begin())];
		}
		else {
			cycleUtil += kpdguiRecord->scoreMatrix[*(structure.end() - 1)][*(structure.begin())];
		}

		if (addAdvantageToHighPRACandidates && kpdguiRecord->pairInfoVector[*(structure.begin())].recipPRA >= praAdvantageCutoff){
			cycleUtil += praAdvantageValue;
		}

		expUtility = cycleProb*cycleUtil;
	}

	return expUtility;
}

double KPDGUISimulation::calculateExpectedUtilityWithFallbacks(vector<int> structure){

	//Parameters
	KPDUtilityScheme utilityScheme = kpdguiParameters->getUtilityScheme();

	bool addAdvantageToHighPRACandidates = kpdguiParameters->getAddAdvantageToHighPRACandidates();
	double praAdvantageCutoff = kpdguiParameters->getPRAAdvantageCutoff();
	double praAdvantageValue = kpdguiParameters->getPRAAdvantageValue();

	int nV = (int)structure.size();
	double utility = 0;

	//Initialize submatrices (5 year, 10 year survivals stored in subutility matrix)
	vector<vector<bool> > subIncidenceMatrix(nV + 1, vector<bool>(nV + 1, false));
	vector<vector<double> > subUtilityMatrix(nV + 1, vector<double>(nV + 1, 0));
	vector<vector<double> > subProbabilityMatrix(nV + 1, vector<double>(nV + 1, 0));
	vector<KPDPairType> subPairTypeVector(nV + 1, PAIR);
	vector<bool> subABDonorVector(nV + 1, true);
	vector<double> subProbVertexVector(nV + 1, 0.0);

	int i = 1, j = 1;

	//Form submatrices
	for (vector<int>::iterator it = structure.begin(); it != structure.end(); ++it, i++){
		for (vector<int>::iterator it2 = structure.begin(); it2 != structure.end(); ++it2, j++){
			if (i != j){
				subIncidenceMatrix[i][j] = kpdguiRecord->incidenceMatrix[*it][*it2];
				subProbabilityMatrix[i][j] = kpdguiRecord->probabilityMatrix[*it][*it2];
				if (utilityScheme == KPDUtilityScheme::TRANSPLANTS){
					subUtilityMatrix[i][j] = kpdguiRecord->viableTransplantMatrix[*it][*it2];
				}
				else if (utilityScheme == KPDUtilityScheme::SURVIVAL5YEAR){
					subUtilityMatrix[i][j] = kpdguiRecord->survival5yearMatrix[*it][*it2];
				}
				else if (utilityScheme == KPDUtilityScheme::SURVIVAL10YEAR){
					subUtilityMatrix[i][j] = kpdguiRecord->survival10yearMatrix[*it][*it2];
				}
				else {
					subUtilityMatrix[i][j] = kpdguiRecord->scoreMatrix[*it][*it2];
				}

				if (addAdvantageToHighPRACandidates && kpdguiRecord->pairInfoVector[*it2].pairType == PAIR && kpdguiRecord->pairInfoVector[*it2].recipPRA >= praAdvantageCutoff){
					subUtilityMatrix[i][j] += praAdvantageValue;
				}
			}
		}
		subPairTypeVector[i] = kpdguiRecord->pairInfoVector[*it].pairType;
		subABDonorVector[i] = (kpdguiRecord->pairInfoVector[*it].donorBT == BT_AB);
		subProbVertexVector[i] = kpdguiRecord->pairInfoVector[*it].uncertainty;

		j = 1;
	}

	int possibleConfigs = 0;

	//Iterates through each possible subset of vertices (2^|V| subsets)
	for (int v = 3; v< pow((double)2, nV); v++){
		vector<int> vertex_flags(nV + 1, 0);
		int p = v;
		int q = 1;
		int numberOfVertices = 0;
		while (p != 0){
			int r = p % 2;
			if (r == 1) {
				numberOfVertices++;
				vertex_flags[q] = numberOfVertices;
			}
			p = p / 2;
			q++;
		}

		//Must have at least 2 pairs/ADs
		if (numberOfVertices > 1){
			double probVertexSubset = 1;
			for (int vIndex = 1; vIndex < nV + 1; vIndex++){
				//If vertex is included in this subset, include probability
				if (vertex_flags[vIndex] != 0){
					if (subPairTypeVector[vIndex] == PAIR){
						probVertexSubset = probVertexSubset*subProbVertexVector[vIndex];
					}
				}
				//If vertex is not included in this subset, include 1-probability
				else{
					if (subPairTypeVector[vIndex] == PAIR){
						probVertexSubset = probVertexSubset*(1 - subProbVertexVector[vIndex]);
					}
					else {
						probVertexSubset = 0;
					}
				}
			}

			//Form sub-sub matrices
			vector<vector<bool> > subsubIncidenceMatrix(numberOfVertices + 1, vector<bool>(numberOfVertices + 1, false));
			vector<vector<double> > subsubUtilityMatrix(numberOfVertices + 1, vector<double>(numberOfVertices + 1, 0));
			vector<vector<double> > subsubProbabilityMatrix(numberOfVertices + 1, vector<double>(numberOfVertices + 1, 0));
			vector<KPDPairType> subsubPairTypeVector(numberOfVertices + 1, PAIR);
			vector<bool> subsubABDonorVector(numberOfVertices + 1, false);

			int nE = 0;
			vector<vector<int> > edgeMatrix; edgeMatrix.push_back(vector<int>(0));
			vector<double> edgeProbVector; edgeProbVector.push_back(0);

			for (int k = 1; k <= numberOfVertices; k++){
				int i = 0;
				while (vertex_flags[i] != k){
					i++;
				}
				subsubPairTypeVector[k] = subPairTypeVector[i];
				subsubABDonorVector[k] = subABDonorVector[i];

				for (int l = 1; l <= numberOfVertices; l++){
					if (k != l){
						int j = 0;
						while (vertex_flags[j] != l){
							j++;
						}
						subsubIncidenceMatrix[k][l] = subIncidenceMatrix[i][j];
						subsubUtilityMatrix[k][l] = subUtilityMatrix[i][j];
						subsubProbabilityMatrix[k][l] = subProbabilityMatrix[i][j];
						if (subsubIncidenceMatrix[k][l] == true){
							vector<int> temp_vec(3, 0);
							temp_vec[1] = k; temp_vec[2] = l;
							edgeMatrix.push_back(temp_vec);
							edgeProbVector.push_back(1 - subsubProbabilityMatrix[k][l]);
							nE++;
						}
					}
				}
			}

			// Iterate through every possible combination of edges
			double partialUtility = 0;
			for (int e = 3; e< pow((double)2, nE); e++){
				vector<vector<bool> > incidenceMatrix_temp(numberOfVertices + 1, vector<bool>(numberOfVertices + 1, false));
				vector<double> edgeProbVector_temp(edgeProbVector);
				int w = e;
				int x = 1;
				int numberOfEdges = 0;
				while (w != 0){
					int y = w % 2;
					if (y == 1) {
						incidenceMatrix_temp[edgeMatrix[x][1]][edgeMatrix[x][2]] = true;
						edgeProbVector_temp[x] = 1 - edgeProbVector[x];
						numberOfEdges++;
					}
					w = w / 2;
					x++;
				}
				//Calculate probability of subset
				if (numberOfEdges > 1){
					double probability = 1;
					for (int j = 1; j < (int)edgeProbVector_temp.size(); j++){
						probability = probability*edgeProbVector_temp[j];
					}

					partialUtility = partialUtility + probability*calculatePartialUtility(numberOfVertices, incidenceMatrix_temp, subsubUtilityMatrix, subsubPairTypeVector, subsubABDonorVector);
				}
			}
			utility = utility + partialUtility*probVertexSubset;
		}
	}

	return utility;
}

double KPDGUISimulation::estimateExpectedUtilityWithFallbacks(std::vector<int> &structure){

	//Parameters
	KPDUtilityScheme utilityScheme = kpdguiParameters->getUtilityScheme();
	int numberOfEUSimulations = kpdguiParameters->getNumberOfEUSimulations();

	bool addAdvantageToHighPRACandidates = kpdguiParameters->getAddAdvantageToHighPRACandidates();
	double praAdvantageCutoff = kpdguiParameters->getPRAAdvantageCutoff();
	double praAdvantageValue = kpdguiParameters->getPRAAdvantageValue();

	int nV = (int)structure.size();

	//Initialize submatrices (5 year, 10 year survivals stored in subutility matrix)
	std::vector<std::vector<bool> > subIncidenceMatrix(nV + 1, std::vector<bool>(nV + 1, false));
	std::vector<std::vector<double> > subUtilityMatrix(nV + 1, std::vector<double>(nV + 1, 0));
	std::vector<std::vector<double> > subProbabilityMatrix(nV + 1, std::vector<double>(nV + 1, 0));
	std::vector<KPDPairType> subPairTypeVector(nV + 1, PAIR);
	std::vector<bool> subABDonorVector(nV + 1, true);
	std::vector<double> subProbVertexVector(nV + 1, 0.0);
	//std::vector<int> subRecipIDVector(nV + 1, 0);

	int i = 1, j = 1;

	//Form submatrices
	for (std::vector<int>::iterator itDonors = structure.begin(); itDonors != structure.end(); ++itDonors, i++){
		for (std::vector<int>::iterator itCandidates = structure.begin(); itCandidates != structure.end(); ++itCandidates, j++){
			if (i != j){
				subIncidenceMatrix[i][j] = kpdguiRecord->incidenceMatrix[*itDonors][*itCandidates];
				subProbabilityMatrix[i][j] = kpdguiRecord->probabilityMatrix[*itDonors][*itCandidates];
				if (utilityScheme == TRANSPLANTS){
					subUtilityMatrix[i][j] = kpdguiRecord->viableTransplantMatrix[*itDonors][*itCandidates];
				}
				else if (utilityScheme == SURVIVAL5YEAR){
					subUtilityMatrix[i][j] = kpdguiRecord->survival5yearMatrix[*itDonors][*itCandidates];
				}
				else if (utilityScheme == SURVIVAL10YEAR){
					subUtilityMatrix[i][j] = kpdguiRecord->survival10yearMatrix[*itDonors][*itCandidates];
				}
				else {
					subUtilityMatrix[i][j] = kpdguiRecord->scoreMatrix[*itDonors][*itCandidates];
				}

				if (addAdvantageToHighPRACandidates && kpdguiRecord->pairInfoVector[*itCandidates].pairType == PAIR && kpdguiRecord->pairInfoVector[*itCandidates].recipPRA >= praAdvantageCutoff){
					subUtilityMatrix[i][j] += praAdvantageValue;
				}

				qDebug() << *itDonors << " " << *itCandidates << " " << subUtilityMatrix[i][j];
			}
		}
		subPairTypeVector[i] = kpdguiRecord->pairInfoVector[*itDonors].pairType;
		subABDonorVector[i] = (kpdguiRecord->pairInfoVector[*itDonors].donorBT == BT_AB);
		//subRecipIDVector[i] = kpdguiRecord->pairInfoVector[*itDonors].recipID;
		subProbVertexVector[i] = kpdguiRecord->pairInfoVector[*itDonors].uncertainty;

		j = 1;
	}

	double utility = 0;
	double probability = 0;

	for (int sims = 1; sims <= numberOfEUSimulations; sims++){
		double prob = 1;

		vector<int> availableNodes;
		availableNodes.push_back(0);
		for (int i = 1; i <= nV; i++){
			if (rngSimulation.runif() <= subProbVertexVector[i]){
				availableNodes.push_back(i);
				prob = prob * subProbVertexVector[i];
			}
			else {
				prob = prob * (1 - subProbVertexVector[i]);
			}
		}
		int subsetSize = (int)availableNodes.size() - 1;

		if (subsetSize > 1){

			std::vector<std::vector<bool> > subsubIncidenceMatrix(subsetSize + 1, std::vector<bool>(subsetSize + 1, false));
			std::vector<std::vector<double> > subsubUtilityMatrix(subsetSize + 1, std::vector<double>(subsetSize + 1, 0));
			std::vector<KPDPairType> subsubPairTypeVector(subsetSize + 1, PAIR);
			std::vector<bool> subsubABDonorVector(subsetSize + 1, true);
			//std::vector<int> subsubRecipIDVector(subsetSize + 1, 0);

			//Form subsubmatrices
			for (int k = 1; k <= subsetSize; k++){
				for (int l = 1; l <= subsetSize; l++){
					if (k != l){
						if (subIncidenceMatrix[availableNodes[k]][availableNodes[l]] == true){
							if (rngSimulation.runif() <= subProbabilityMatrix[availableNodes[k]][availableNodes[l]]){
								subsubIncidenceMatrix[k][l] = true;
								subsubUtilityMatrix[k][l] = subUtilityMatrix[availableNodes[k]][availableNodes[l]];
								prob = prob * subProbabilityMatrix[availableNodes[k]][availableNodes[l]];
							}
							else {
								prob = prob * (1 - subProbabilityMatrix[availableNodes[k]][availableNodes[l]]);
							}
						}
					}
				}
				subsubPairTypeVector[k] = subPairTypeVector[availableNodes[k]];
				subsubABDonorVector[k] = subABDonorVector[availableNodes[k]];
				//subsubRecipIDVector[k] = subRecipIDVector[availableNodes[k]];
			}

			//utility += prob * calculatePartialUtility(subsetSize, subsubIncidenceMatrix, subsubUtilityMatrix, subsubPairTypeVector, subsubABDonorVector);
			utility += calculatePartialUtility(subsetSize, subsubIncidenceMatrix, subsubUtilityMatrix, subsubPairTypeVector, subsubABDonorVector);
		}

		probability += prob;
	}

	return utility / numberOfEUSimulations;
}

double KPDGUISimulation::calculatePartialUtility(int nV, vector<vector<bool> > &incidenceMatrix_temp, vector<vector<double> > &subsubUtilityMatrix, vector<KPDPairType> & subsubPairTypeVector, vector<bool> & subsubABDonorVector){

	//Parameters
	bool allowABBridgeDonors = kpdguiParameters->getAllowABBridgeDonors();

	int maxSize = kpdguiParameters->getMaxSize();
	int maximum = std::max(maxSize + 1, 3);

	vector<vector<int> > possibleCyclesOrChains;
	vector<double> utilityOfPossibleCyclesOrChains;

	double utility = 0;
	double utilEstimate = 0;

	int start = 1;
	vector<int> visitedVec(nV + 1, 0);
	vector<int> stack_vec;

	while (start <= nV){
		visitedVec[start] = 1;

		stack_vec.push_back(start);
		int v = getChild(start, stack_vec.back(), visitedVec, incidenceMatrix_temp);
		while (!stack_vec.empty()){
			if (v == -1){
				int top = stack_vec.back();
				stack_vec.pop_back();
				if (top == start) {
					visitedVec[top] = 0;
					break;
				}
				visitedVec[top] = 0;
				v = getChild(top, stack_vec.back(), visitedVec, incidenceMatrix_temp);
			}
			else{
				visitedVec[v] = 1;
				stack_vec.push_back(v);

				if (incidenceMatrix_temp[v][start] == true){
					int multipleADCheck = 0;
					int index = 0;

					double tempUtil = 0;
					vector<int> potentialCycleOrChain;
					for (unsigned i = 0; i < stack_vec.size() - 1; i++){
						potentialCycleOrChain.push_back(stack_vec[i]);
						tempUtil += subsubUtilityMatrix[stack_vec[i]][stack_vec[i + 1]];
					}
					potentialCycleOrChain.push_back(stack_vec.back());
					tempUtil += subsubUtilityMatrix[stack_vec.back()][stack_vec.front()];

					for (unsigned i = 0; i < potentialCycleOrChain.size(); i++){
						if (subsubPairTypeVector[potentialCycleOrChain[i]] != PAIR){
							multipleADCheck++;
							index = i;
						}
					}

					//Cannot have more than one AD
					if (multipleADCheck <= 1){
						bool ignore = false;

						//Chain
						if (multipleADCheck == 1){
							//Check if chain is of appropriate size
							if ((int)potentialCycleOrChain.size() <= maxSize + 1){
								//Queue up AD to front of chain
								while (index > 0){
									int tempVec = *(potentialCycleOrChain.begin());
									potentialCycleOrChain.erase(potentialCycleOrChain.begin());
									potentialCycleOrChain.push_back(tempVec);
									index--;
								}

								//Check for AB bridge donor
								if (!allowABBridgeDonors){
									if (subsubABDonorVector[potentialCycleOrChain.back()]){
										//If AB bridge donor, contribute minimal utility
										ignore = true;
									}
								}
							}
							//If not of appropriate size, contribute minimal utility
							else {
								ignore = true;
							}
						}
						// Cycle 
						else {
							//If not of appropriate size, contribute minimal utility
							if ((int)potentialCycleOrChain.size() > 3){
								ignore = true;
							}
						}

						//Add miniscule value to eligible transplants that are likely to be ignored
						if (ignore){
							tempUtil = 0.00001;
						}

						possibleCyclesOrChains.push_back(vector<int>(potentialCycleOrChain));
						utilityOfPossibleCyclesOrChains.push_back(tempUtil);
						if (tempUtil > utilEstimate){
							utilEstimate = tempUtil;
						}
					}
				}

				if (stack_vec.size() >= maximum)
					v = -1;
				else
					v = getChild(start, v, visitedVec, incidenceMatrix_temp);
			}
		}
		start++;
	}

	//if (maxChainLength > 4){
	//utility = utilEstimate;
	//}

	if (possibleCyclesOrChains.size() == 1){
		//else if (possibleCyclesOrChains.size() == 1){
		utility = utilityOfPossibleCyclesOrChains.at(0);
	}

	else if (possibleCyclesOrChains.size() > 1){

		int nPossibleCycles = (int)possibleCyclesOrChains.size();

		for (int c = 1; c < pow((double)2, nPossibleCycles); c++){
			double tempU = 0;

			vector<int> cycleVec_flags(nPossibleCycles, 0);
			int mc = c;
			int kc = 0;
			int countc = 0;
			while (mc != 0){
				int rc = mc % 2;
				cycleVec_flags[kc] = rc;
				mc = mc / 2;
				kc++;
			}

			vector<int> checkUniqueness(nV + 1, 0);
			bool validSolution = true;
			double uOfCombination = 0;
			for (int q = 0; q < nPossibleCycles; q++){
				if (cycleVec_flags[q] == 1){
					tempU += utilityOfPossibleCyclesOrChains[q];
					for (vector<int>::iterator it = possibleCyclesOrChains.at(q).begin(); it != possibleCyclesOrChains.at(q).end(); ++it){
						checkUniqueness[*it]++;
						if (checkUniqueness[*it] > 1){
							validSolution = false;
						}
					}
				}
			}

			if (validSolution == true && tempU > utility){
				utility = tempU;
			}
		}
	}

	return utility;
}

std::string KPDGUISimulation::intToString(int number){
	std::stringstream ss;	//Create a stringstream
	ss << number;		//Add number to the stream
	return ss.str();	//Return a string with the contents of the stream
}

