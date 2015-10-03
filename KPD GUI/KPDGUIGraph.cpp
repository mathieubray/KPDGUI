#include "KPDGUIGraph.h"

KPDGUISimulation::KPDGUISimulation(KPDGUIRecord * record, ParamInfoStruct params){

	kpdguiRecord = record;

	kpdguiParameters.optScheme = params.optScheme;
	kpdguiParameters.utilityScheme = params.utilityScheme;
	kpdguiParameters.maxChainLength = params.maxChainLength;
	
	kpdguiParameters.pairFailureRate = params.pairFailureRate;
	kpdguiParameters.adFailureRate = params.adFailureRate;
	kpdguiParameters.exogenousFailureRate = params.exogenousFailureRate;
	
	kpdguiParameters.addAdvantageToHighPRACandidates = params.addAdvantageToHighPRACandidates;
	kpdguiParameters.praAdvantageCutoff = params.praAdvantageCutoff;
	kpdguiParameters.praAdvantageValue = params.praAdvantageValue;

	kpdguiParameters.numberOfSolutions = params.numberOfSolutions;

	kpdguiParameters.chainStorage = params.chainStorage;
	kpdguiParameters.reserveODonorsForOCandidates = params.reserveODonorsForOCandidates;
	kpdguiParameters.checkDP = params.checkDP;
	kpdguiParameters.includeCompatiblePairs = params.includeCompatiblePairs;
	kpdguiParameters.excludeABDonorsFromSimulation = params.excludeABDonorsFromSimulation;
	kpdguiParameters.allowABBridgeDonors = params.allowABBridgeDonors;

}

//Clear KPDGUISimulation

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

vector<vector<int> > & KPDGUISimulation::getCurrentMatchRunCyclesAndChains(){

	//Parameters
	int maxChainLength = kpdguiParameters.maxChainLength;
	int maximum = std::max(maxChainLength + 1, 3);

	QString chainStorage = kpdguiParameters.chainStorage;
	bool allowABBridgeDonors = kpdguiParameters.allowABBridgeDonors;

	vector<vector<int> > storedCyclesAndChains;

	int start = 1;
	int nVertices = kpdguiRecord->getNumberOfVertices();
	vector<int> visitedVector(nVertices + 1, 0);
	vector<int> stack_vec;

	//Depth-first search of graph
	while (start <= nVertices){
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
						if ((int)potentialCycleOrChain.size() <= maxChainLength + 1){
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
								if (kpdguiRecord->pairInfoVector[potentialCycleOrChain.back()].donorBT == "AB"){
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

// Searches graphs for connected components

vector<vector<int> > & KPDGUISimulation::getCurrentMatchRunComponents(){

	//Parameters
	int maxChainLength = kpdguiParameters.maxChainLength;
	int maximum = std::max(maxChainLength + 1, 3);

	QString chainStorage = kpdguiParameters.chainStorage;

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

//Utility values for all chains/cycles

vector<double> & KPDGUISimulation::getUtilityForCurrentMatchRunCyclesAndChains(){

	utilityOfCurrentMatchRunCyclesAndChains.clear();

	//Parameters
	KPDUtilityScheme utilityScheme = kpdguiParameters.utilityScheme;

	bool addAdvantageToHighPRACandidates = kpdguiParameters.addAdvantageToHighPRACandidates;
	double praAdvantageCutoff = kpdguiParameters.praAdvantageCutoff;
	double praAdvantageValue = kpdguiParameters.praAdvantageValue;
	
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
	}
	
	return utilityOfCurrentMatchRunCyclesAndChains;
}

//Expected utility values for all chains/cycles

vector<double> & KPDGUISimulation::getExpectedUtilityForCurrentMatchRunCyclesAndChains(){
	expectedUtilityOfCurrentMatchRunCyclesAndChains.clear();

	for (vector<vector<int> >::iterator it = currentMatchRunStructureNodeLists.begin(); it != currentMatchRunStructureNodeLists.end(); it++){
		double eu = calculateExpectedUtility(*it);
		expectedUtilityOfCurrentMatchRunCyclesAndChains.push_back(eu);
	}

	return expectedUtilityOfCurrentMatchRunCyclesAndChains;
}

//Expected utility values for all sets

vector<double> & KPDGUISimulation::getExpectedUtilityForCurrentMatchRunSets(){

	expectedUtilityOfCurrentMatchRunSets.clear();

	for (vector<vector<int> >::iterator it = currentMatchRunStructureNodeLists.begin(); it != currentMatchRunStructureNodeLists.end(); it++){
		double eu = calculateExpectedUtilityWithFB(*it);
		expectedUtilityOfCurrentMatchRunSets.push_back(eu);
	}

	return expectedUtilityOfCurrentMatchRunSets;
}

//Expected utility values for all components

vector<double> & KPDGUISimulation::getExpectedUtilityForCurrentMatchRunComponents(){

	expectedUtilityOfCurrentMatchRunComponents.clear();

	for (vector<vector<int > >::iterator it = currentMatchRunStructureNodeLists.begin(); it != currentMatchRunStructureNodeLists.end(); it++){
		double eu = calculateExpectedUtilityWithFB(*it);
		expectedUtilityOfCurrentMatchRunComponents.push_back(eu);
	}

	return expectedUtilityOfCurrentMatchRunComponents;
}

//Optimize

void KPDGUISimulation::getOptimalSolution(){

	KPDOptimizationScheme optScheme = kpdguiParameters.optScheme;
	int numberOfSolutions = kpdguiParameters.numberOfSolutions;

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

//Helper function for graph searching	

int KPDGUISimulation::getChild(int lower, int current, vector<int> &visitedVector, vector<vector<bool> > & thisIMatrix){
	int nV = (int)visitedVector.size() - 1;
	for (int j = lower + 1; j <= nV; j++){
		if (thisIMatrix[current][j] == true && visitedVector[j] == 0)
			return j;
	}
	return -1;
}

double KPDGUISimulation::calculateExpectedUtility(vector<int> structure){

	//Parameters
	KPDUtilityScheme utilityScheme = kpdguiParameters.utilityScheme;

	bool addAdvantageToHighPRACandidates = kpdguiParameters.addAdvantageToHighPRACandidates;
	double praAdvantageCutoff = kpdguiParameters.praAdvantageCutoff;
	double praAdvantageValue = kpdguiParameters.praAdvantageValue;
	
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



double KPDGUISimulation::calculateExpectedUtilityWithFB(vector<int> structure){

	//Parameters
	KPDUtilityScheme utilityScheme = kpdguiParameters.utilityScheme;

	bool addAdvantageToHighPRACandidates = kpdguiParameters.addAdvantageToHighPRACandidates;
	double praAdvantageCutoff = kpdguiParameters.praAdvantageCutoff;
	double praAdvantageValue = kpdguiParameters.praAdvantageValue;
	
	int nV = (int)structure.size();
	double utility = 0;

	//Initialize submatrices (5 year, 10 year survivals stored in subutility matrix)
	vector<vector<bool> > subIncidenceMatrix(nV + 1, vector<bool>(nV + 1, false));
	vector<vector<double> > subUtilityMatrix(nV + 1, vector<double>(nV + 1, 0));
	vector<vector<double> > subProbabilityMatrix(nV + 1, vector<double>(nV + 1, 0));
	vector<int> subPairTypeVector(nV + 1, 0);
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
		subABDonorVector[i] = (kpdguiRecord->pairInfoVector[*it].recipBT == "AB");
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
			vector<int> subsubPairTypeVector(numberOfVertices + 1, 0);
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

//Helper function for fallback options

double KPDGUISimulation::calculatePartialUtility(int nV, vector<vector<bool> > &incidenceMatrix_temp, vector<vector<double> > &subsubUtilityMatrix, vector<int> & subsubPairTypeVector, vector<bool> & subsubABDonorVector){

	//Parameters
	bool allowABBridgeDonors = kpdguiParameters.allowABBridgeDonors;

	int maxChainLength = kpdguiParameters.maxChainLength;
	int maximum = std::max(maxChainLength + 1, 3);

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
						if (subsubPairTypeVector[potentialCycleOrChain[i]] != 0){
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
							if ((int)potentialCycleOrChain.size() <= maxChainLength + 1){
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

	if (maxChainLength > 4){
		utility = utilEstimate;
	}

	else if (possibleCyclesOrChains.size() == 1){
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

