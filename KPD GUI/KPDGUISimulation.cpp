#include "KPDGUISimulation.h"

KPDGUISimulation::KPDGUISimulation(KPDGUIRecord * record, KPDGUISimParameters * params){

	kpdguiRecord = record;
	kpdguiParameters->copyParameters(params);

	incidenceMatrix = kpdguiRecord->getIncidenceMatrix();
	associatedDonorMatrix = kpdguiRecord->getAssociatedDonorMatrix();
	associatedScoresMatrix = kpdguiRecord->getAssociatedScoresMatrix();
	associated5YearSurvivalMatrix = kpdguiRecord->getAssociated5YearSurvivalMatrix();
	associated10YearSurvivalMatrix = kpdguiRecord->getAssociated10YearSurvivalMatrix();
	associatedProbabilitiesMatrix = kpdguiRecord->getAssociatedProbabilitiesMatrix();

	nodeInfoVector = kpdguiRecord->getNodeInfoVector();

}

KPDGUISimulation::~KPDGUISimulation(){

	currentMatchRunNodes.clear();
	currentMatchRunStructures.clear();

	utilityOfCurrentMatchRunCyclesAndChains.clear();
	expectedUtilityOfCurrentMatchRunCyclesAndChains.clear();
	expectedUtilityOfCurrentMatchRunSets.clear();
	expectedUtilityOfCurrentMatchRunComponents.clear();

	selectedSolutions.clear();
	selectedStructures.clear();
	solutionObjectives.clear();
}

int KPDGUISimulation::selectDonor(int donorNodeID, int candidateNodeID) {
	double maxVal = 0.0;
	int maxIndex = -1;

	int associatedDonors = nodeInfoVector[donorNodeID].numberOfDonors;

	for (int k = 1; k <= associatedDonors; k++) {

		if (associatedDonorMatrix[donorNodeID][candidateNodeID][k] == 1) {
			if (kpdguiParameters->getUtilityScheme() == SCORE) {
				if (associatedScoresMatrix[donorNodeID][candidateNodeID][k] > maxVal) {
					maxIndex = k;
				}
			}
			else if (kpdguiParameters->getUtilityScheme() == SURVIVAL5YEAR) {
				if (associated5YearSurvivalMatrix[donorNodeID][candidateNodeID][k] > maxVal) {
					maxIndex = k;
				}
			}
			else if (kpdguiParameters->getUtilityScheme() == SURVIVAL10YEAR) {
				if (associated10YearSurvivalMatrix[donorNodeID][candidateNodeID][k] > maxVal) {
					maxIndex = k;
				}
			}
			else {
				maxIndex = k;
			}
		}

		k++;
	}

	return maxIndex;
}

vector<vector<int> > & KPDGUISimulation::getCurrentMatchRunCyclesAndChains(QProgressDialog * progressBar){

	//Parameters
	int maxCycleSize = kpdguiParameters->getMaxCycleSize();
	int maxChainLength = kpdguiParameters->getMaxChainLength();
	int maximum = std::max(maxChainLength + 1, maxCycleSize);

	KPDChainStorage chainStorage = kpdguiParameters->getChainStorage();
	bool allowABBridgeDonors = kpdguiParameters->getAllowABBridgeDonors();

	vector<vector<int> > storedCyclesAndChains;

	int start = 1;
	int currentMatchRunSize = kpdguiRecord->getNumberOfAvailableNodes() - 1;
	vector<int> visitedVector(currentMatchRunSize + 1, 0);
	vector<int> stack_vec;

	//progressBar->setLabelText("Discovering Cycles and Chains...");
	//progressBar->setRange(0, nVertices);
	//progressBar->setValue(0);

	//Depth-first search of graph
	while (start <= currentMatchRunSize){
		//progressBar->setValue(start);

		visitedVector[start] = 1;
		stack_vec.push_back(start);
		int v = getChild(start, start, visitedVector, incidenceMatrix);

		while (!stack_vec.empty()){
			if (v == -1){
				int top = stack_vec.back();
				stack_vec.pop_back();
				if (top == start){
					visitedVector[top] = 0;
					break;
				}
				visitedVector[top] = 0;
				v = getChild(top, stack_vec.back(), visitedVector, incidenceMatrix);
			}
			else{
				visitedVector[v] = 1;
				stack_vec.push_back(v);

				if (incidenceMatrix[v][start] == true){
					
					int multipleADCheck = 0;
					int index = 0;

					vector<int> potentialCycleOrChain;
					for (unsigned i = 0; i < stack_vec.size(); i++){
						potentialCycleOrChain.push_back(stack_vec[i]);
					}

					for (unsigned i = 0; i < potentialCycleOrChain.size(); i++){
						if (nodeInfoVector[potentialCycleOrChain[i]].nodeType == AD){
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

							if (allowABBridgeDonors) {
								if (chainStorage == CHAINS_LAST) {
									storedCyclesAndChains.push_back(potentialCycleOrChain);
								}
								else {
									currentMatchRunStructures.push_back(potentialCycleOrChain);
								}
							}
							else {
								bool exclude = true;

								for (int k = 1; k <= nodeInfoVector[*(potentialCycleOrChain.end() - 1)].numberOfDonors; k++) {
									if (nodeInfoVector[*(potentialCycleOrChain.end() - 1)].donorBTs[k] != BT_AB) {
										exclude = false;
									}
								}

								if (!exclude) {
									if (chainStorage == CHAINS_LAST) {
										storedCyclesAndChains.push_back(potentialCycleOrChain);
									}
									else {
										currentMatchRunStructures.push_back(potentialCycleOrChain);
									}
								}
							}
						}
					}

					//Cycle
					else if (multipleADCheck == 0){
						//Check if size of cycle is appropriate
						if ((int)potentialCycleOrChain.size() <= maxCycleSize){
							if (chainStorage == CHAINS_FIRST){
								storedCyclesAndChains.push_back(potentialCycleOrChain);
							}
							else {
								currentMatchRunStructures.push_back(potentialCycleOrChain);
							}
						}
					}
				}

				if (stack_vec.size() >= maximum)
					v = -1;
				else {
					v = getChild(start, v, visitedVector, incidenceMatrix);
				}
			}
		}
		start++;
	}

	if (storedCyclesAndChains.size()>0){
		for (vector<vector<int> >::iterator it = storedCyclesAndChains.begin(); it != storedCyclesAndChains.end(); ++it){
			currentMatchRunStructures.push_back(*it);
		}
	}
	return currentMatchRunStructures;
}

vector<vector<int> > & KPDGUISimulation::getCurrentMatchRunComponentsNaive(QProgressDialog * progressBar){

	//Parameters
	int maxCycleSize = kpdguiParameters->getMaxCycleSize();
	int maxChainLength = kpdguiParameters->getMaxChainLength();
	int maxComponentSize = kpdguiParameters->getMaxComponentSize();

	KPDChainStorage chainStorage = kpdguiParameters->getChainStorage();

	vector<vector<int> > storedComponents;
	int currentMatchRunSize = kpdguiRecord->getNumberOfAvailableNodes() - 1;

	//Size 2 components
	for (int i = 1; i <= currentMatchRunSize - 1; i++){
		for (int j = i + 1; j <= currentMatchRunSize; j++){
			if (incidenceMatrix[i][j] == true && incidenceMatrix[j][i] == true){
				bool chain = (nodeInfoVector[i].nodeType == AD || nodeInfoVector[j].nodeType == AD);

				vector<int > temp;
				temp.push_back(i); temp.push_back(j);

				if ((chain && chainStorage == CHAINS_LAST) || (!chain && chainStorage == CHAINS_FIRST)){
					storedComponents.push_back(temp);
				}
				else {
					currentMatchRunStructures.push_back(temp);
				}
			}
		}
	}

	//Size 3 components
	for (int i = 1; i <= currentMatchRunSize - 2; i++){
		for (int j = i + 1; j <= currentMatchRunSize - 1; j++){
			for (int k = j + 1; k <= currentMatchRunSize; k++){
				//i to j
				if (incidenceMatrix[i][j] == false && (incidenceMatrix[i][k] == false || incidenceMatrix[k][j] == false))
					continue;
				//i to k
				if (incidenceMatrix[i][k] == false && (incidenceMatrix[i][j] == false || incidenceMatrix[j][k] == false))
					continue;
				//j to i
				if (incidenceMatrix[j][i] == false && (incidenceMatrix[j][k] == false || incidenceMatrix[k][i] == false))
					continue;
				//j to k
				if (incidenceMatrix[j][k] == false && (incidenceMatrix[j][i] == false || incidenceMatrix[i][k] == false))
					continue;
				//k to i
				if (incidenceMatrix[k][i] == false && (incidenceMatrix[k][j] == false || incidenceMatrix[j][i] == false))
					continue;
				//k to j
				if (incidenceMatrix[k][j] == false && (incidenceMatrix[k][i] == false || incidenceMatrix[i][j] == false))
					continue;

				bool chain = (nodeInfoVector[i].nodeType == AD || nodeInfoVector[j].nodeType == AD || nodeInfoVector[k].nodeType == AD);
				vector<int > temp;
				temp.push_back(i); temp.push_back(j); temp.push_back(k);

				if ((chain && chainStorage == CHAINS_LAST) || (!chain && chainStorage == CHAINS_FIRST)){
					storedComponents.push_back(temp);
				}
				else {
					currentMatchRunStructures.push_back(temp);
				}
			}
		}
	}

	//Size 4 components
	if (maxComponentSize >= 4){
		for (int i = 1; i <= currentMatchRunSize - 3; i++){
			for (int j = i + 1; j <= currentMatchRunSize - 2; j++){
				for (int k = j + 1; k <= currentMatchRunSize - 1; k++){
					for (int l = k + 1; l <= currentMatchRunSize; l++){
						// i to j
						if (incidenceMatrix[i][j] == false && (incidenceMatrix[i][k] == false || incidenceMatrix[k][j] == false)
							&& (incidenceMatrix[i][l] == false || incidenceMatrix[l][j] == false)
							&& (incidenceMatrix[i][k] == false || incidenceMatrix[k][l] == false || incidenceMatrix[l][j] == false)
							&& (incidenceMatrix[i][l] == false || incidenceMatrix[l][k] == false || incidenceMatrix[k][j] == false))
							continue;
						// i to k
						if (incidenceMatrix[i][k] == false && (incidenceMatrix[i][j] == false || incidenceMatrix[j][k] == false)
							&& (incidenceMatrix[i][l] == false || incidenceMatrix[l][k] == false)
							&& (incidenceMatrix[i][l] == false || incidenceMatrix[l][j] == false || incidenceMatrix[j][k] == false)
							&& (incidenceMatrix[i][j] == false || incidenceMatrix[j][l] == false || incidenceMatrix[l][k] == false))
							continue;
						// i to l
						if (incidenceMatrix[i][l] == false && (incidenceMatrix[i][j] == false || incidenceMatrix[j][l] == false)
							&& (incidenceMatrix[i][k] == false || incidenceMatrix[k][l] == false)
							&& (incidenceMatrix[i][j] == false || incidenceMatrix[j][k] == false || incidenceMatrix[k][l] == false)
							&& (incidenceMatrix[i][k] == false || incidenceMatrix[k][j] == false || incidenceMatrix[j][l] == false))
							continue;
						// j to i
						if (incidenceMatrix[j][i] == false && (incidenceMatrix[j][k] == false || incidenceMatrix[k][i] == false)
							&& (incidenceMatrix[j][l] == false || incidenceMatrix[l][i] == false)
							&& (incidenceMatrix[j][k] == false || incidenceMatrix[k][l] == false || incidenceMatrix[l][i] == false)
							&& (incidenceMatrix[j][l] == false || incidenceMatrix[l][k] == false || incidenceMatrix[k][i] == false))
							continue;
						// j to k
						if (incidenceMatrix[j][k] == false && (incidenceMatrix[j][i] == false || incidenceMatrix[i][k] == false)
							&& (incidenceMatrix[j][l] == false || incidenceMatrix[l][k] == false)
							&& (incidenceMatrix[j][i] == false || incidenceMatrix[i][l] == false || incidenceMatrix[l][k] == false)
							&& (incidenceMatrix[j][l] == false || incidenceMatrix[l][i] == false || incidenceMatrix[i][k] == false))
							continue;
						// j to l
						if (incidenceMatrix[j][l] == false && (incidenceMatrix[j][i] == false || incidenceMatrix[i][l] == false)
							&& (incidenceMatrix[j][k] == false || incidenceMatrix[k][l] == false)
							&& (incidenceMatrix[j][i] == false || incidenceMatrix[i][k] == false || incidenceMatrix[k][l] == false)
							&& (incidenceMatrix[j][k] == false || incidenceMatrix[k][i] == false || incidenceMatrix[i][l] == false))
							continue;
						// k to i
						if (incidenceMatrix[k][i] == false && (incidenceMatrix[k][j] == false || incidenceMatrix[j][i] == false)
							&& (incidenceMatrix[k][l] == false || incidenceMatrix[l][i] == false)
							&& (incidenceMatrix[k][j] == false || incidenceMatrix[j][l] == false || incidenceMatrix[l][i] == false)
							&& (incidenceMatrix[k][l] == false || incidenceMatrix[l][j] == false || incidenceMatrix[j][i] == false))
							continue;
						// k to j
						if (incidenceMatrix[k][j] == false && (incidenceMatrix[k][i] == false || incidenceMatrix[i][j] == false)
							&& (incidenceMatrix[k][l] == false || incidenceMatrix[l][j] == false)
							&& (incidenceMatrix[k][i] == false || incidenceMatrix[i][l] == false || incidenceMatrix[l][j] == false)
							&& (incidenceMatrix[k][l] == false || incidenceMatrix[l][i] == false || incidenceMatrix[i][j] == false))
							continue;
						// k to l
						if (incidenceMatrix[k][l] == false && (incidenceMatrix[k][i] == false || incidenceMatrix[i][l] == false)
							&& (incidenceMatrix[k][j] == false || incidenceMatrix[j][l] == false)
							&& (incidenceMatrix[k][i] == false || incidenceMatrix[i][j] == false || incidenceMatrix[j][l] == false)
							&& (incidenceMatrix[k][j] == false || incidenceMatrix[j][i] == false || incidenceMatrix[i][l] == false))
							continue;
						// l to i
						if (incidenceMatrix[l][i] == false && (incidenceMatrix[l][j] == false || incidenceMatrix[j][i] == false)
							&& (incidenceMatrix[l][k] == false || incidenceMatrix[k][i] == false)
							&& (incidenceMatrix[l][j] == false || incidenceMatrix[j][k] == false || incidenceMatrix[k][i] == false)
							&& (incidenceMatrix[l][k] == false || incidenceMatrix[k][j] == false || incidenceMatrix[j][i] == false))
							continue;
						// l to j
						if (incidenceMatrix[l][j] == false && (incidenceMatrix[l][i] == false || incidenceMatrix[i][j] == false)
							&& (incidenceMatrix[l][k] == false || incidenceMatrix[k][j] == false)
							&& (incidenceMatrix[l][i] == false || incidenceMatrix[i][k] == false || incidenceMatrix[k][j] == false)
							&& (incidenceMatrix[l][k] == false || incidenceMatrix[k][i] == false || incidenceMatrix[i][j] == false))
							continue;
						// l to k
						if (incidenceMatrix[l][k] == false && (incidenceMatrix[l][i] == false || incidenceMatrix[i][k] == false)
							&& (incidenceMatrix[l][j] == false || incidenceMatrix[j][k] == false)
							&& (incidenceMatrix[l][i] == false || incidenceMatrix[i][j] == false || incidenceMatrix[j][k] == false)
							&& (incidenceMatrix[l][j] == false || incidenceMatrix[j][i] == false || incidenceMatrix[i][k] == false))
							continue;

						bool chain = (nodeInfoVector[i].nodeType == AD || nodeInfoVector[j].nodeType == AD || nodeInfoVector[k].nodeType == AD || nodeInfoVector[l].nodeType == AD);

						vector<int > temp;
						temp.push_back(i); temp.push_back(j); temp.push_back(k); temp.push_back(l);
						if ((chain && chainStorage == CHAINS_LAST) || (!chain && chainStorage == CHAINS_FIRST)){
							storedComponents.push_back(temp);
						}
						else {
							currentMatchRunStructures.push_back(temp);
						}
					}
				}
			}
		}
	}

	return currentMatchRunStructures;
}

std::vector<std::vector<int > > & KPDGUISimulation::getCurrentMatchRunComponentsNew(QProgressDialog * progressBar){

	int nVertices = kpdguiRecord->getNumberOfAvailableNodes();
	bool matchRunContainsADs = false;

	//progressBar->setLabelText("Discovering Locally Relevant Subgraphs...");
	//progressBar->setRange(0, nVertices);
	//progressBar->setValue(0);

	for (int i = 1; i <= nVertices; i++){
		if (nodeInfoVector[i].nodeType != PAIR){
			matchRunContainsADs = true;
		}
	}

	if (matchRunContainsADs){
		getSCCWithADs(progressBar);
	}

	getSCCPairsOnly(progressBar);

	return currentMatchRunStructures;
}

vector<double> & KPDGUISimulation::getUtilityForCurrentMatchRunCyclesAndChains(QProgressDialog * progressBar){

	utilityOfCurrentMatchRunCyclesAndChains.clear();

	//progressBar->setLabelText("Calculating Utility...");
	//progressBar->setRange(0, currentMatchRunStructures.size());
	//progressBar->setValue(0);

	//Parameters
	KPDUtilityScheme utilityScheme = kpdguiParameters->getUtilityScheme();

	bool addAdvantageToHighPRACandidates = kpdguiParameters->getAddAdvantageToHighPRACandidates();
	double praAdvantageCutoff = kpdguiParameters->getPRAAdvantageCutoff();
	double praAdvantageValue = kpdguiParameters->getPRAAdvantageValue();
	//int i = 0;
	
	for (vector<vector<int> >::iterator itStructures = currentMatchRunStructures.begin(); itStructures != currentMatchRunStructures.end(); itStructures++){
		double u = 0;
		//Sums over all utility values
		for (vector<int>::iterator itNodes = (*itStructures).begin(); itNodes != (*itStructures).end() - 1; itNodes++){

			int donorIndex = selectDonor(*itNodes, *(itNodes + 1));

			if (utilityScheme == TRANSPLANTS){
				if (nodeInfoVector[*(itNodes + 1)].nodeType == PAIR) {
					u += 1;
				}
			}
			//5 year survival
			else if (utilityScheme == SURVIVAL5YEAR){
				u += associated5YearSurvivalMatrix[*itNodes][*(itNodes + 1)][donorIndex];
			}
			//10 year survival
			else if (utilityScheme == KPDUtilityScheme::SURVIVAL10YEAR){
				u += associated10YearSurvivalMatrix[*itNodes][*(itNodes + 1)][donorIndex];
			}
			//Other utility specification
			else {
				u += associatedScoresMatrix[*itNodes][*(itNodes + 1)][donorIndex];
			}

			if (addAdvantageToHighPRACandidates && nodeInfoVector[*(itNodes + 1)].candidatePRA >= praAdvantageCutoff){
				u += praAdvantageValue;
			}
		}

		int donorIndex = selectDonor(*(itStructures->end() - 1), *(itStructures->begin()));

		if (utilityScheme == TRANSPLANTS){
			if (nodeInfoVector[*(itStructures->begin())].nodeType == PAIR) {
				u += 1;
			}
		}
		else if (utilityScheme == SURVIVAL5YEAR){
			u += associated5YearSurvivalMatrix[*(itStructures->end() - 1)][*(itStructures->begin())][donorIndex];
		}
		else if (utilityScheme == SURVIVAL10YEAR){
			u += associated10YearSurvivalMatrix[*(itStructures->end() - 1)][*(itStructures->begin())][donorIndex];
		}
		else {
			u += associatedScoresMatrix[*(itStructures->end() - 1)][*(itStructures->begin())][donorIndex];
		}

		if (addAdvantageToHighPRACandidates && nodeInfoVector[*(itStructures->begin())].candidatePRA >= praAdvantageCutoff){
			u += praAdvantageValue;
		}

		utilityOfCurrentMatchRunCyclesAndChains.push_back(u);
		
		//i++;
		//progressBar->setValue(i);
		QApplication::processEvents();
	}
	
	return utilityOfCurrentMatchRunCyclesAndChains;
}

double KPDGUISimulation::calculateExpectedUtility(std::vector<int> structure, KPDUtilityScheme utility) {

	double praAdvantageValue = kpdguiParameters->getPRAAdvantageValue();
	double praAdvantageCutoff = kpdguiParameters->getPRAAdvantageCutoff();
	bool addAdvantageToHighPRACandidates = kpdguiParameters->getAddAdvantageToHighPRACandidates();

	bool chain = (nodeInfoVector[*(structure.begin())].nodeType != PAIR);

	vector<double> transformedProbabilities;
	vector<double> transformedUtilities;

	for (vector<int>::iterator itNodes = structure.begin(); itNodes != structure.end() - 1; itNodes++) {
		//Sort utilities, associated probabilities
		vector<double> sortedUtilities;
		vector<double> sortedMatchProbabilities;
		vector<double> sortedDonorProbabilities;

		vector<double> utils;
		vector<double> matchProbs;
		vector<double> donorProbs;

		for (int k = 1; k <= nodeInfoVector[*itNodes].numberOfDonors; k++) {
			if (associatedDonorMatrix[*itNodes][*(itNodes + 1)][k] == 1) {
				if (utility == TRANSPLANTS) {
					if (nodeInfoVector[*(itNodes + 1)].nodeType == PAIR) {
						utils.push_back(1);
					}
				}
				else if (utility == SURVIVAL5YEAR) {
					utils.push_back(associated5YearSurvivalMatrix[*itNodes][*(itNodes + 1)][k]);
				}
				else if (utility == SURVIVAL10YEAR) {
					utils.push_back(associated10YearSurvivalMatrix[*itNodes][*(itNodes + 1)][k]);
				}
				else {
					utils.push_back(associatedScoresMatrix[*itNodes][*(itNodes + 1)][k]);
				}

				matchProbs.push_back(associatedProbabilitiesMatrix[*itNodes][*(itNodes + 1)][k]);
				donorProbs.push_back(nodeInfoVector[*itNodes].donorUncertainty[k]);
			}
		}

		while (utils.size() > 1) {
			double maxScore = utils[0];
			double associatedMatchProb = matchProbs[0];
			double associatedDonorProb = donorProbs[0];
			int maxIndex = 0;

			for (unsigned i = 1; i < utils.size(); i++) {
				if (utils[i] > maxScore) {
					maxScore = utils[i];
					associatedMatchProb = matchProbs[i];
					associatedDonorProb = donorProbs[i];
					maxIndex = i;
				}
				else if (utils[i] == maxScore && matchProbs[i] * donorProbs[i] > associatedMatchProb*associatedDonorProb) {
					associatedMatchProb = matchProbs[i];
					associatedDonorProb = donorProbs[i];
					maxIndex = i;
				}
			}
			sortedUtilities.push_back(maxScore);
			sortedMatchProbabilities.push_back(associatedMatchProb);
			sortedDonorProbabilities.push_back(associatedDonorProb);

			utils.erase(utils.begin() + maxIndex);
			matchProbs.erase(matchProbs.begin() + maxIndex);
			donorProbs.erase(donorProbs.begin() + maxIndex);
		}
		sortedUtilities.push_back(utils[0]);
		sortedMatchProbabilities.push_back(matchProbs[0]);
		sortedDonorProbabilities.push_back(donorProbs[0]);

		double prob = sortedDonorProbabilities[0] * sortedMatchProbabilities[0];
		double util = sortedUtilities[0];

		if (sortedUtilities.size() == 1) {
			transformedProbabilities.push_back(prob);
			transformedUtilities.push_back(util);
		}
		else {
			double expectedUtil = prob*util;
			double expectedProb = prob;
			double probContinue = 1 - prob;

			for (unsigned i = 1; i < sortedUtilities.size(); i++) {
				expectedUtil += probContinue * sortedDonorProbabilities[i] * sortedMatchProbabilities[i] * sortedUtilities[i];
				expectedProb += probContinue * sortedDonorProbabilities[i] * sortedMatchProbabilities[i];
				probContinue = probContinue * (1 - sortedDonorProbabilities[i] * sortedMatchProbabilities[i]);
			}

			transformedProbabilities.push_back(expectedProb);
			transformedUtilities.push_back(expectedUtil / expectedProb);
		}
	}

	if (!chain) {

		//Sort utilities, associated probabilities
		vector<double> sortedUtilities;
		vector<double> sortedMatchProbabilities;
		vector<double> sortedDonorProbabilities;

		vector<double> utils;
		vector<double> matchProbs;
		vector<double> donorProbs;

		for (int k = 1; k <= nodeInfoVector[*(structure.end() - 1)].numberOfDonors; k++) {
			if (associatedDonorMatrix[*(structure.end() - 1)][*structure.begin()][k] == 1) {
				if (utility == TRANSPLANTS) {
					if (nodeInfoVector[*structure.begin()].nodeType == PAIR) {
						utils.push_back(1);
					}
				}
				else if (utility == SURVIVAL5YEAR) {
					utils.push_back(associated5YearSurvivalMatrix[*(structure.end() - 1)][*structure.begin()][k]);
				}
				else if (utility == SURVIVAL10YEAR) {
					utils.push_back(associated10YearSurvivalMatrix[*(structure.end() - 1)][*structure.begin()][k]);
				}
				else {
					utils.push_back(associatedScoresMatrix[*(structure.end() - 1)][*structure.begin()][k]);
				}

				matchProbs.push_back(associatedProbabilitiesMatrix[*(structure.end() - 1)][*structure.begin()][k]);
				donorProbs.push_back(nodeInfoVector[*(structure.end() - 1)].donorUncertainty[k]);
			}
		}

		while (utils.size() > 1) {
			double maxScore = utils[0];
			double associatedMatchProb = matchProbs[0];
			double associatedDonorProb = donorProbs[0];
			int maxIndex = 0;

			for (unsigned i = 1; i < utils.size(); i++) {
				if (utils[i] > maxScore) {
					maxScore = utils[i];
					associatedMatchProb = matchProbs[i];
					associatedDonorProb = donorProbs[i];
					maxIndex = i;
				}
				else if (utils[i] == maxScore && matchProbs[i] * donorProbs[i] > associatedMatchProb*associatedDonorProb) {
					associatedMatchProb = matchProbs[i];
					associatedDonorProb = donorProbs[i];
					maxIndex = i;
				}
			}
			sortedUtilities.push_back(maxScore);
			sortedMatchProbabilities.push_back(associatedMatchProb);
			sortedDonorProbabilities.push_back(associatedDonorProb);

			utils.erase(utils.begin() + maxIndex);
			matchProbs.erase(matchProbs.begin() + maxIndex);
			donorProbs.erase(donorProbs.begin() + maxIndex);
		}
		sortedUtilities.push_back(utils[0]);
		sortedMatchProbabilities.push_back(matchProbs[0]);
		sortedDonorProbabilities.push_back(donorProbs[0]);

		double prob = sortedDonorProbabilities[0] * sortedMatchProbabilities[0];
		double util = sortedUtilities[0];

		if (sortedUtilities.size() == 1) {
			transformedProbabilities.push_back(prob);
			transformedUtilities.push_back(util);
		}
		else {
			double expectedUtil = prob*util;
			double expectedProb = prob;
			double probContinue = 1 - prob;

			for (unsigned i = 1; i < sortedUtilities.size(); i++) {
				expectedUtil += probContinue * sortedDonorProbabilities[i] * sortedMatchProbabilities[i] * sortedUtilities[i];
				expectedProb += probContinue * sortedDonorProbabilities[i] * sortedMatchProbabilities[i];
				probContinue = probContinue * (1 - sortedDonorProbabilities[i] * sortedMatchProbabilities[i]);
			}

			transformedProbabilities.push_back(expectedProb);
			transformedUtilities.push_back(expectedUtil / expectedProb);
		}
	}

	int i = 0;
	double expUtility = 0.0;
	double cycleProb = 1.0;
	double cycleUtil = 0.0;

	//Chain
	if (chain) {
		cycleUtil = transformedUtilities[i];

		if (addAdvantageToHighPRACandidates && nodeInfoVector[*(structure.begin() + 1)].candidatePRA >= praAdvantageCutoff) {
			cycleUtil += praAdvantageValue;
		}

		cycleProb = nodeInfoVector[*(structure.begin() + 1)].candidateUncertainty * transformedProbabilities[i];

		if (structure.size() == 2) {
			expUtility = cycleProb*cycleUtil;
		}
		else if (structure.size()>2) {
			for (vector<int >::iterator itNodes = structure.begin() + 1; itNodes != structure.end() - 1; ++itNodes) {
				i++;

				//Probability of continuing to next transplant
				double probContinue = nodeInfoVector[*(itNodes + 1)].candidateUncertainty * transformedProbabilities[i];
				expUtility += (1 - probContinue)*cycleUtil*cycleProb;

				cycleProb = cycleProb*probContinue;
				cycleUtil += transformedUtilities[i];

				if (addAdvantageToHighPRACandidates && nodeInfoVector[*(itNodes + 1)].candidatePRA >= praAdvantageCutoff) {
					cycleUtil += praAdvantageValue;
				}
			}

			expUtility += cycleUtil*cycleProb;
		}
	}

	//Cycles
	else {
		//Calculates cycle probability and cycle utility		
		for (vector<int >::iterator itNodes = structure.begin(); itNodes != structure.end() - 1; ++itNodes) {
			cycleProb = cycleProb * nodeInfoVector[*(itNodes + 1)].candidateUncertainty * transformedProbabilities[i];

			cycleUtil += transformedUtilities[i];

			if (addAdvantageToHighPRACandidates && nodeInfoVector[*(itNodes + 1)].candidatePRA >= praAdvantageCutoff) {
				cycleUtil += praAdvantageValue;
			}
			i++;
		}

		cycleProb = cycleProb * nodeInfoVector[*(structure.begin())].candidateUncertainty * transformedProbabilities[i];
		cycleUtil += transformedUtilities[i];

		if (addAdvantageToHighPRACandidates && nodeInfoVector[*(structure.begin())].candidatePRA >= praAdvantageCutoff) {
			cycleUtil += praAdvantageValue;
		}

		expUtility = cycleProb*cycleUtil;
	}

	return expUtility;
}

vector<double> & KPDGUISimulation::getExpectedUtilityForCurrentMatchRunCyclesAndChains(QProgressDialog * progressBar) {
	expectedUtilityOfCurrentMatchRunCyclesAndChains.clear();

	//progressBar->setLabelText("Calculating Utility...");
	//progressBar->setRange(0, currentMatchRunStructures.size());
	//progressBar->setValue(0);

	//int i = 0;
	for (vector<vector<int> >::iterator it = currentMatchRunStructures.begin(); it != currentMatchRunStructures.end(); it++) {
		//i++;
		double eu = calculateExpectedUtility(*it, kpdguiParameters->getUtilityScheme());
		expectedUtilityOfCurrentMatchRunCyclesAndChains.push_back(eu);

		//progressBar->setValue(i);
		//QApplication::processEvents();
	}

	return expectedUtilityOfCurrentMatchRunCyclesAndChains;
}

double KPDGUISimulation::calculateExpectedUtilityWithFallbacks(std::vector<int> structure) {

	//Parameters
	KPDUtilityScheme utilityScheme = kpdguiParameters->getUtilityScheme();

	bool addAdvantageToHighPRACandidates = kpdguiParameters->getAddAdvantageToHighPRACandidates();
	double praAdvantageCutoff = kpdguiParameters->getPRAAdvantageCutoff();
	double praAdvantageValue = kpdguiParameters->getPRAAdvantageValue();

	double utility = 0;

	int nCandidates = (int)structure.size();

	//Iterates through each possible subset of candidates
	for (int c = 3; c < pow((double)2, nCandidates); c++) {
		std::vector<int> candidateFlags(nCandidates, 0);
		int p = c;
		int cIndex = 0;
		int candidateSubsetSize = 0;
		while (p != 0) {
			int r = p % 2;
			if (r == 1) {
				candidateSubsetSize++;
				candidateFlags[cIndex] = candidateSubsetSize;
			}
			p = p / 2;
			cIndex++;
		}

		//Must have at least 2 candidates
		if (candidateSubsetSize > 1) {

			int numberOfDonorsInCandidateSubset = 0;
			double probCandidateSubset = 1;

			std::vector<int> subsetCandidateIndices;

			std::vector<int> subsetDonorNodeIndices;
			std::vector<int> subsetDonorIDs;

			//Iterate through candidates
			for (int index = 0; index < nCandidates; index++) {

				int candidateID = structure[index];

				//If candidate is included in this subset, include probability
				if (candidateFlags[index] != 0) {
					probCandidateSubset = probCandidateSubset * nodeInfoVector[candidateID].candidateUncertainty;

					//Add to subset
					subsetCandidateIndices.push_back(index);

					//Count donors and add to subset
					for (int k = 1; k <= nodeInfoVector[candidateID].numberOfDonors; k++) {
						numberOfDonorsInCandidateSubset++;
						subsetDonorNodeIndices.push_back(index);
						subsetDonorIDs.push_back(k);
					}
				}
				//If candidate is not included in this subset, include 1-probability
				else {
					probCandidateSubset = probCandidateSubset * (1 - nodeInfoVector[candidateID].candidateUncertainty);
				}
			}

			//Iterates through each possible subset of donors
			for (int d = 3; d < pow((double)2, numberOfDonorsInCandidateSubset); d++) {
				std::vector<int> donorFlags(numberOfDonorsInCandidateSubset, 0);
				int p = d;
				int dIndex = 0;
				int donorSubsetSize = 0;
				while (p != 0) {
					int r = p % 2;
					if (r == 1) {
						donorSubsetSize++;
						donorFlags[dIndex] = donorSubsetSize;
					}
					p = p / 2;
					dIndex++;
				}

				//Must have at least 2 donors
				if (donorSubsetSize > 1) {

					int numberOfEdgesInDonorSubset = 0;
					double probDonorSubset = probCandidateSubset;

					std::vector<int> edgeSubsetCandidateIndices;
					std::vector<int> edgeSubsetDonorNodeIndices;
					std::vector<int> edgeSubsetDonorIDs;

					//Iterate through donors
					for (int index = 0; index < numberOfDonorsInCandidateSubset; index++) {

						int subsetDonorNodeIndex = subsetDonorNodeIndices[index];
						int subsetDonorNodeID = structure[subsetDonorNodeIndex];
						int subsetDonorID = subsetDonorIDs[index];

						//If donor is included in this subset, include probability
						if (donorFlags[index] != 0) {
							probDonorSubset = probDonorSubset * nodeInfoVector[subsetDonorNodeID].donorUncertainty[subsetDonorID];

							//Iterate through candidates to find edges
							for (int index2 = 0; index2 < candidateSubsetSize; index2++) {

								int subsetCandidateIndex = subsetCandidateIndices[index2];
								int subsetCandidateID = structure[subsetCandidateIndex];

								if (subsetDonorNodeID != subsetCandidateID) {
									//Count edges and add to subset
									if (associatedDonorMatrix[subsetDonorNodeID][subsetCandidateID][subsetDonorID] == 1) {
										numberOfEdgesInDonorSubset++;

										edgeSubsetCandidateIndices.push_back(subsetCandidateIndex);
										edgeSubsetDonorNodeIndices.push_back(subsetDonorNodeIndex);
										edgeSubsetDonorIDs.push_back(subsetDonorID);
									}
								}
							}
						}

						//If donor is not included in this subset, include 1-probability
						else {
							probDonorSubset = probDonorSubset * (1 - nodeInfoVector[subsetDonorNodeID].donorUncertainty[subsetDonorID]);
						}
					}

					// Iterate through every possible combination of edges
					for (int e = 3; e < pow((double)2, numberOfEdgesInDonorSubset); e++) {
						std::vector<int> edgeFlags(numberOfEdgesInDonorSubset, 0);
						int p = e;
						int eIndex = 0;
						int edgeSubsetSize = 0;
						while (p != 0) {
							int r = p % 2;
							if (r == 1) {
								edgeSubsetSize++;
								edgeFlags[eIndex] = edgeSubsetSize;
							}
							p = p / 2;
							eIndex++;
						}

						//Must have at least 2 edges
						if (edgeSubsetSize > 1) {

							double probEdgeSubset = probDonorSubset;

							std::vector<std::vector<std::vector<int> > > reducedDonorMatrix(nCandidates + 1, std::vector<std::vector<int> >(nCandidates + 1, std::vector<int>(1, 0)));
							std::vector<int> reducedNumberOfDonors(nCandidates + 1, 0);

							std::vector<std::vector<bool> > reducedIncidenceMatrix(nCandidates + 1, std::vector<bool>(nCandidates + 1, false));
							std::vector<std::vector<std::vector<double> > > reducedUtilityMatrix(nCandidates + 1, std::vector<std::vector<double> >(nCandidates + 1, std::vector<double>(1, 0.0)));

							std::vector<KPDNodeType> reducedNodeTypeVector(nCandidates + 1, PAIR);
							std::vector<std::vector<KPDBloodType> > reducedDonorBloodTypes(nCandidates + 1, std::vector<KPDBloodType>(1, BT_AB));

							//Build reduced matrices
							for (int i = 1; i <= nCandidates; i++) {

								int structureNodeDonors = nodeInfoVector[structure[i - 1]].numberOfDonors;

								for (int j = 1; j <= nCandidates; j++) {
									reducedDonorMatrix[i][j].assign(1 + structureNodeDonors, 0);
									reducedUtilityMatrix[i][j].assign(1 + structureNodeDonors, 0.0);
								}

								reducedNodeTypeVector[i] = nodeInfoVector[structure[i - 1]].nodeType;

								reducedDonorBloodTypes[i].assign(1 + structureNodeDonors, BT_AB);
								for (int k = 1; k <= structureNodeDonors; k++) {
									reducedDonorBloodTypes[i][k] = nodeInfoVector[structure[i - 1]].donorBTs[k];
								}
							}

							for (int l = 0; l < edgeSubsetSize; l++) {

								int edgeSubsetDonorNodeIndex = edgeSubsetDonorNodeIndices[l];
								int edgeSubsetCandidateIndex = edgeSubsetCandidateIndices[l];
								int edgeSubsetDonorID = edgeSubsetDonorIDs[l];

								int edgeSubsetDonorNodeID = structure[edgeSubsetDonorNodeIndex];
								int edgeSubsetCandidateID = structure[edgeSubsetCandidateIndex];

								if (edgeFlags[l] != 0) {

									probEdgeSubset = probEdgeSubset *  associatedProbabilitiesMatrix[edgeSubsetDonorNodeID][edgeSubsetCandidateID][edgeSubsetDonorID];

									reducedDonorMatrix[edgeSubsetDonorNodeIndex + 1][edgeSubsetCandidateIndex + 1][edgeSubsetDonorID] = 1;
									reducedIncidenceMatrix[edgeSubsetDonorNodeIndex + 1][edgeSubsetCandidateIndex + 1] = true;
									if (utilityScheme == TRANSPLANTS) {
										if (nodeInfoVector[edgeSubsetCandidateID].nodeType == PAIR) {
											reducedUtilityMatrix[edgeSubsetDonorNodeIndex + 1][edgeSubsetCandidateIndex + 1][edgeSubsetDonorID] = 1;
										}
									}
									else if (utilityScheme == SURVIVAL5YEAR) {
										reducedUtilityMatrix[edgeSubsetDonorNodeIndex + 1][edgeSubsetCandidateIndex + 1][edgeSubsetDonorID] = associated5YearSurvivalMatrix[edgeSubsetDonorNodeID][edgeSubsetCandidateID][edgeSubsetDonorID];
									}
									else if (utilityScheme == SURVIVAL10YEAR) {
										reducedUtilityMatrix[edgeSubsetDonorNodeIndex + 1][edgeSubsetCandidateIndex + 1][edgeSubsetDonorID] = associated10YearSurvivalMatrix[edgeSubsetDonorNodeID][edgeSubsetCandidateID][edgeSubsetDonorID];
									}
									else {
										reducedUtilityMatrix[edgeSubsetDonorNodeIndex + 1][edgeSubsetCandidateIndex + 1][edgeSubsetDonorID] = associatedScoresMatrix[edgeSubsetDonorNodeID][edgeSubsetCandidateID][edgeSubsetDonorID];
									}

									if (addAdvantageToHighPRACandidates && nodeInfoVector[edgeSubsetCandidateID].nodeType == PAIR && nodeInfoVector[edgeSubsetCandidateID].candidatePRA >= praAdvantageCutoff) {
										reducedUtilityMatrix[edgeSubsetDonorNodeIndex + 1][edgeSubsetCandidateIndex + 1][edgeSubsetDonorID] += praAdvantageValue;
									}
								}
								else {
									probEdgeSubset = probEdgeSubset * (1 - associatedProbabilitiesMatrix[edgeSubsetDonorNodeID][edgeSubsetCandidateID][edgeSubsetDonorID]);
								}
							}

							utility += probEdgeSubset*calculatePartialUtility(nCandidates, reducedIncidenceMatrix, reducedUtilityMatrix, reducedNodeTypeVector, reducedDonorBloodTypes);
							//std::cout << utility << std::endl;
						}
					}
				}
			}
		}
	}

	return utility;
}


double KPDGUISimulation::estimateExpectedUtilityWithFallbacks(std::vector<int> &structure) {

	//Parameters
	KPDUtilityScheme utilityScheme = kpdguiParameters->getUtilityScheme();

	bool addAdvantageToHighPRACandidates = kpdguiParameters->getAddAdvantageToHighPRACandidates();
	double praAdvantageCutoff = kpdguiParameters->getPRAAdvantageCutoff();
	double praAdvantageValue = kpdguiParameters->getPRAAdvantageValue();
	
	int numberOfExpectedUtilityIterations = kpdguiParameters->getNumberOfExpectedUtilityIterations();
	
	int nV = (int)structure.size();

	//Initialize submatrices (5 year, 10 year survivals stored in subutility matrix)
	std::vector<std::vector<bool> > subIncidenceMatrix(nV + 1, std::vector<bool>(nV + 1, false));
	std::vector<std::vector<std::vector<int> > > subDonorMatrix(nV + 1, std::vector<std::vector<int> >(nV + 1, std::vector<int>(1, 0)));
	std::vector<std::vector<std::vector<double> > > subUtilityMatrix(nV + 1, std::vector<std::vector<double> >(nV + 1, std::vector<double>(1,0.0)));
	std::vector<std::vector<std::vector<double> > > subProbabilityMatrix(nV + 1, std::vector<std::vector<double> >(nV + 1, std::vector<double>(1, 0.0)));
	
	//AdditionalNodeInfo p;
	//std::vector<AdditionalNodeInfo> subNodeInfoVector(nV + 1, p);
	std::vector<KPDNodeType> subNodeTypeVector(nV + 1, PAIR);
	std::vector<bool> subDonorVector(nV + 1, true);
	//std::vector<double> subProbVertexVector(nV + 1, 0.0);
	//std::vector<int> subRecipIDVector(nV + 1, 0);

	int i = 1, j = 1;

	//Form submatrices
	for (std::vector<int>::iterator itDonors = structure.begin(); itDonors != structure.end(); ++itDonors, i++) {
		
		int numberOfDonors = nodeInfoVector[*itDonors].numberOfDonors;
		
		
		for (std::vector<int>::iterator itCandidates = structure.begin(); itCandidates != structure.end(); ++itCandidates, j++) {
			if (i != j) {
				subIncidenceMatrix[i][j] = incidenceMatrix[*itDonors][*itCandidates];

				for (int k = 1; k <= numberOfDonors; k++) {
					if (associatedDonorMatrix[*itDonors][*itCandidates][k] == 1) {
						subDonorMatrix[i][j][k] = 1;
						subProbabilityMatrix[i][j][k] = associatedProbabilitiesMatrix[*itDonors][*itCandidates][k];
						
						if (utilityScheme == TRANSPLANTS) {
							if (nodeInfoVector[*itCandidates].nodeType == PAIR) {
								subUtilityMatrix[i][j][k] = 1;
							}
						}
						else if (utilityScheme == SURVIVAL5YEAR) {
							subUtilityMatrix[i][j][k] = associated5YearSurvivalMatrix[*itDonors][*itCandidates][k];
						}
						else if (utilityScheme == SURVIVAL10YEAR) {
							subUtilityMatrix[i][j][k] = associated10YearSurvivalMatrix[*itDonors][*itCandidates][k];
						}
						else {
							subUtilityMatrix[i][j][k] = associatedScoresMatrix[*itDonors][*itCandidates][k];
						}

						if (addAdvantageToHighPRACandidates && nodeInfoVector[*itCandidates].nodeType == PAIR && nodeInfoVector[*itCandidates].candidatePRA >= praAdvantageCutoff) {
							subUtilityMatrix[i][j][k] += praAdvantageValue;
						}
					}					
				}
			}
		}

		//subNodeInfoVector[i] = nodeInfoVector[*itDonors];

		//subPairTypeVector[i] = kpdguiRecord->pairInfoVector[*itDonors].pairType;
		//subABDonorVector[i] = (kpdguiRecord->pairInfoVector[*itDonors].donorBT == BT_AB);
		//subRecipIDVector[i] = kpdguiRecord->pairInfoVector[*itDonors].recipID;
		//subProbVertexVector[i] = kpdguiRecord->pairInfoVector[*itDonors].uncertainty;

		j = 1;
	}

	double utility = 0;
	double probability = 0;

	for (int sims = 1; sims <= numberOfExpectedUtilityIterations; sims++) {
		double prob = 1;

		vector<int> availableNodes;
		availableNodes.push_back(0);

		vector<vector<int> > availableDonors;
		availableDonors.assign(nV + 1, vector<int>(1, 0));

		//int numberOfDonorsInCandidateSubset = 0;
		//std::vector<int> subsetDonorNodeIndices;
		//std::vector<int> subsetDonorIDs;

		for (int i = 1; i <= nV; i++) {
			if (rngExpectedUtilitySimulation.runif() <= nodeInfoVector[i].candidateUncertainty) {
				prob = prob * nodeInfoVector[i].candidateUncertainty;

				int numberOfDonors = nodeInfoVector[i].numberOfDonors;
				availableDonors[i].assign(1 + numberOfDonors, 0);

				bool includedDonor = false;
							
				for (int k = 1; k <= numberOfDonors; k++) {
					
					if (rngExpectedUtilitySimulation.runif() <= nodeInfoVector[i].donorUncertainty[k]) {
						prob = prob * nodeInfoVector[i].donorUncertainty[k];
						availableDonors[i][k] = 1;
						includedDonor = true;
					}

					else {
						prob = prob * (1 - nodeInfoVector[i].donorUncertainty[k]);
					}
					//numberOfDonorsInCandidateSubset++;
					//subsetDonorNodeIndices.push_back(i);
					//subsetDonorIDs.push_back(k);
				}

				if (includedDonor) {
					availableNodes.push_back(i);
				}
			}
			else {
				prob = prob * (1 - nodeInfoVector[i].candidateUncertainty);
			}
		}

		int subsetSize = (int) availableNodes.size() - 1;

		if (subsetSize > 1) {

			std::vector<std::vector<bool> > subsubIncidenceMatrix(subsetSize + 1, std::vector<bool>(subsetSize + 1, false));
			//std::vector<std::vector<std::vector<double> > > subsubUtilityMatrix(subsetSize + 1, std::vector<std::vector<double> >(subsetSize + 1, 0));
			//std::vector<KPDPairType> subsubPairTypeVector(subsetSize + 1, PAIR);
			//std::vector<bool> subsubABDonorVector(subsetSize + 1, true);
			//std::vector<int> subsubRecipIDVector(subsetSize + 1, 0);

			//Form subsubmatrices
			/*for (int k = 1; k <= subsetSize; k++) {
				for (int l = 1; l <= subsetSize; l++) {
					if (k != l) {
						if (subIncidenceMatrix[availableNodes[k]][availableNodes[l]] == true) {
							if (rngSimulation.runif() <= subProbabilityMatrix[availableNodes[k]][availableNodes[l]]) {
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

			utility += prob * calculatePartialUtility(subsetSize, subsubIncidenceMatrix, subsubUtilityMatrix, subsubPairTypeVector, subsubABDonorVector);*/
			//utility += calculatePartialUtility(subsetSize, subsubIncidenceMatrix, subsubUtilityMatrix, subsubPairTypeVector, subsubABDonorVector);
		}

		//probability += prob;
	}

	return utility / numberOfExpectedUtilityIterations;
}


double KPDGUISimulation::calculatePartialUtility(int nV, vector<vector<bool> > &incidence, vector<vector<vector<double> > > &utility, vector<KPDNodeType> & nodeTypes, vector<vector<KPDBloodType> > & bloodTypes) {

	//Parameters
	bool allowABBridgeDonors = kpdguiParameters->getAllowABBridgeDonors();

	int maxCycleSize = kpdguiParameters->getMaxCycleSize();
	int maxChainLength = kpdguiParameters->getMaxChainLength();
	int maximum = std::max(maxChainLength + 1, maxCycleSize);

	vector<vector<int> > possibleCyclesOrChains;
	vector<double> utilityOfPossibleCyclesOrChains;

	double utilityValue = 0;

	int start = 1;
	vector<int> visitedVec(nV + 1, 0);
	vector<int> stack_vec;

	while (start <= nV) {
		visitedVec[start] = 1;

		stack_vec.push_back(start);
		int v = getChild(start, stack_vec.back(), visitedVec, incidence);
		while (!stack_vec.empty()) {
			if (v == -1) {
				int top = stack_vec.back();
				stack_vec.pop_back();
				if (top == start) {
					visitedVec[top] = 0;
					break;
				}
				visitedVec[top] = 0;
				v = getChild(top, stack_vec.back(), visitedVec, incidence);
			}
			else {
				visitedVec[v] = 1;
				stack_vec.push_back(v);

				if (incidence[v][start] == true) {
					int multipleADCheck = 0;
					int index = 0;

					vector<int> potentialCycleOrChain;
					
					for (unsigned i = 0; i < stack_vec.size() - 1; i++) {
						potentialCycleOrChain.push_back(stack_vec[i]);
						if (nodeTypes[stack_vec[i]] != PAIR) {
							multipleADCheck++;
							index = i;
						}
					}
					
					if (multipleADCheck <= 1) {
						double tempUtil = 0;
						bool poorOption = false;

						//Chain
						if (multipleADCheck == 1) {
							//Check if chain is of appropriate size
							if ((int)potentialCycleOrChain.size() <= maxChainLength + 1) {
								//Queue up AD to front of chain
								while (index > 0) {
									int tempVec = *(potentialCycleOrChain.begin());
									potentialCycleOrChain.erase(potentialCycleOrChain.begin());
									potentialCycleOrChain.push_back(tempVec);
									index--;
								}

								//Check for AB bridge donor
								if (!allowABBridgeDonors) {
									poorOption = true;
									for (int k = 1; k < bloodTypes[*(potentialCycleOrChain.end() - 1)].size(); k++) {
										if (bloodTypes[*(potentialCycleOrChain.end() - 1)][k] != BT_AB) {
											//If AB bridge donor, contribute minimal utility
											poorOption = false;
										}
									}
								}
							}
							//If not of appropriate size, contribute minimal utility
							else {
								poorOption = true;
							}

							if (poorOption) {
								tempUtil = 0.00001;
							}
							else {
								for (std::vector<int>::iterator it = potentialCycleOrChain.begin(); it != potentialCycleOrChain.end() - 1; it++) {
									int selectedDonor = -1;
									double selectedDonorUtility = 0;

									for (int k = 1; k < utility[*it][*(it + 1)].size(); k++) {
										if (utility[*it][*(it + 1)][k] > selectedDonorUtility) {
											selectedDonor = k;
											selectedDonorUtility = utility[*it][*(it + 1)][k];
										}
									}
									tempUtil += selectedDonorUtility;
								}
							}
						}
						// Cycle 
						else {
							if ((int)potentialCycleOrChain.size() > 3) {
								poorOption = true;
							}

							if (poorOption) {
								tempUtil = 0.00001;
							}
							else {
								for (std::vector<int>::iterator it = potentialCycleOrChain.begin(); it != potentialCycleOrChain.end() - 1; it++) {
									int selectedDonor = -1;
									double selectedDonorUtility = 0;

									for (int k = 1; k < utility[*it][*(it + 1)].size(); k++) {
										if (utility[*it][*(it + 1)][k] > selectedDonorUtility) {
											selectedDonor = k;
											selectedDonorUtility = utility[*it][*(it + 1)][k];
										}
									}
									tempUtil += selectedDonorUtility;
								}
								int selectedDonor = -1;
								double selectedDonorUtility = 0;

								for (int k = 1; k < utility[*(potentialCycleOrChain.end() - 1)][*(potentialCycleOrChain.begin())].size(); k++) {
									if (utility[*(potentialCycleOrChain.end() - 1)][*(potentialCycleOrChain.begin())][k] > selectedDonorUtility) {
										selectedDonor = k;
										selectedDonorUtility = utility[*(potentialCycleOrChain.end() - 1)][*(potentialCycleOrChain.begin())][k];
									}
								}
								tempUtil += selectedDonorUtility;

							}
						}

						possibleCyclesOrChains.push_back(vector<int>(potentialCycleOrChain));
						utilityOfPossibleCyclesOrChains.push_back(tempUtil);
					}
				}

				if (stack_vec.size() >= maximum)
					v = -1;
				else
					v = getChild(start, v, visitedVec, incidence);
			}
		}
		start++;
	}

	if (possibleCyclesOrChains.size() == 1) {
		utilityValue = utilityOfPossibleCyclesOrChains.at(0);
	}

	else if (possibleCyclesOrChains.size() > 1) {

		int nPossibleCycles = (int)possibleCyclesOrChains.size();

		for (int c = 1; c < pow((double)2, nPossibleCycles); c++) {
			double tempU = 0;

			vector<int> cycle_flags(nPossibleCycles, 0);
			int mc = c;
			int kc = 0;
			int countc = 0;
			while (mc != 0) {
				int rc = mc % 2;
				cycle_flags[kc] = rc;
				mc = mc / 2;
				kc++;
			}

			vector<int> checkUniqueness(nV + 1, 0);
			bool validSolution = true;
			double uOfCombination = 0;
			for (int q = 0; q < nPossibleCycles; q++) {
				if (cycle_flags[q] == 1) {
					tempU += utilityOfPossibleCyclesOrChains[q];
					for (vector<int>::iterator it = possibleCyclesOrChains.at(q).begin(); it != possibleCyclesOrChains.at(q).end(); ++it) {
						checkUniqueness[*it]++;
						if (checkUniqueness[*it] > 1) {
							validSolution = false;
						}
					}
				}
			}

			if (validSolution == true && tempU > utilityValue) {
				utilityValue = tempU;
			}
		}
	}

	return utilityValue;
}

vector<double> & KPDGUISimulation::getExpectedUtilityForCurrentMatchRunSets(QProgressDialog * progressBar){

	expectedUtilityOfCurrentMatchRunSets.clear();

	//progressBar->setLabelText("Calculating Utility...");
	//progressBar->setRange(0, currentMatchRunStructures.size());
	//progressBar->setValue(0);

	//int i = 0;
	for (vector<vector<int> >::iterator itStructures = currentMatchRunStructures.begin(); itStructures != currentMatchRunStructures.end(); itStructures++){
		//i++;
		double eu = calculateExpectedUtilityWithFallbacks(*itStructures);
		expectedUtilityOfCurrentMatchRunSets.push_back(eu);

		//progressBar->setValue(i);
		//QApplication::processEvents();
	}

	return expectedUtilityOfCurrentMatchRunSets;
}

vector<double> & KPDGUISimulation::getExpectedUtilityForCurrentMatchRunComponents(QProgressDialog * progressBar){

	expectedUtilityOfCurrentMatchRunComponents.clear();
	//progressBar->setLabelText("Calculating Utility...");
	//progressBar->setRange(0, currentMatchRunStructures.size());
	//progressBar->setValue(0);

	//int i = 0;
	for (vector<vector<int > >::iterator it = currentMatchRunStructures.begin(); it != currentMatchRunStructures.end(); it++){
		//double eu = calculateExpectedUtilityWithFallbacks(*it);
		//i++;

		double eu;

		if (kpdguiParameters->getEstimateExpectedUtility()) {
			eu = estimateExpectedUtilityWithFallbacks(*it);
		}
		else {
			eu = calculateExpectedUtilityWithFallbacks(*it);
		}
		expectedUtilityOfCurrentMatchRunComponents.push_back(eu);

		//progressBar->setValue(i);
		//QApplication::processEvents();
	}

	return expectedUtilityOfCurrentMatchRunComponents;
}

void KPDGUISimulation::getOptimalSolutionForCurrentMatchRun(QProgressDialog * progressBar){

	KPDOptimizationScheme optScheme = kpdguiParameters->getOptimizationScheme();
	int numberOfSolutions = kpdguiParameters->getNumberOfSolutions();

	//progressBar->setLabelText("Finding Optimal Solutions...");
	//progressBar->setRange(0, numberOfSolutions);
	//progressBar->setValue(0);

	selectedSolutions.clear();
	selectedStructures.clear();
	solutionObjectives.clear();

	int nStructures = (int)currentMatchRunStructures.size();
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
				myVars[i] = model.addVar(0.0, 1.0, -1 * utilityOfCurrentMatchRunCyclesAndChains[i - 1], GRB_BINARY, s); //The default is min, hence the -1
			}
		}
		else if (optScheme == KPDOptimizationScheme::MEUC)
		{
			for (int i = 1; i <= nStructures; i++){
				string s = "cycle_" + intToString(i);
				myVars[i] = model.addVar(0.0, 1.0, -1 * expectedUtilityOfCurrentMatchRunCyclesAndChains[i - 1], GRB_BINARY, s); //The default is min, hence the -1
			}
		}
		else if (optScheme == KPDOptimizationScheme::MEUS)
		{
			for (int i = 1; i <= nStructures; i++){
				string s = "cycle_" + intToString(i);
				myVars[i] = model.addVar(0.0, 1.0, -1 * expectedUtilityOfCurrentMatchRunSets[i - 1], GRB_BINARY, s); //The default is min, hence the -1
			}
		}
		else if (optScheme == KPDOptimizationScheme::SCC)
		{
			for (int i = 1; i <= nStructures; i++){
				string s = "cycle_" + intToString(i);
				myVars[i] = model.addVar(0.0, 1.0, -1 * expectedUtilityOfCurrentMatchRunComponents[i - 1], GRB_BINARY, s); //The default is min, hence the -1
			}
		}
		model.update();

		int nVertices = kpdguiRecord->getNumberOfAvailableNodes();
		//Restriction: Each vertex can only appear at most once in solution
		for (int i = 1; i <= nVertices; i++){
			GRBLinExpr expr = 0;
			for (int j = 0; j <= nStructures - 1; j++){
				for (vector<int>::iterator it = currentMatchRunStructures[j].begin(); it != currentMatchRunStructures[j].end(); ++it){
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

		selectedSolutions.push_back(candidateSolution);
		solutionObjectives.push_back(objval);

		progressBar->setValue(iteration);
		QApplication::processEvents();

		while (iteration < numberOfSolutions){
			iteration++;
			GRBLinExpr expr = 0;

			//Add restriction against previously found solution
			for (int j = 0; j <= nStructures - 1; j++){
				bool found = false;
				for (vector<int>::iterator it = selectedSolutions[iteration - 2].begin(); it != selectedSolutions[iteration - 2].end(); ++it){
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

			selectedSolutions.push_back(candidateSolution);
			solutionObjectives.push_back(objval);

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
	return selectedSolutions;
}

vector<double> & KPDGUISimulation::returnSolutionObjectives(){
	return solutionObjectives;
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

	int maxComponentSize = kpdguiParameters->getMaxComponentSize();

	int nVertices = kpdguiRecord->getNumberOfNodes();

	vector<int> currentMatchRunPairs;
	currentMatchRunPairs.push_back(0);
	for (int i = 1; i <= nVertices; i++){
		if (nodeInfoVector[i].nodeType == PAIR){
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
			child = getChildSCCPairsOnly(bfsTree, bfsLevel, currentMatchRunPairs, visited, next, childLevel, numberOfPairs, incidenceMatrix);

			// If (i) the size of the bfsTree is at the limit or (ii) no children, bfsLevel is currently at the next bfsLevel of the previous node
			if ((int)bfsTree.size() == maxComponentSize || (child == -1 && childLevel == bfsLevel.back() + 1)) {
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

				if (judgeReverseTreeSCCPair(currentMatchRunPairs, bfsTree, nVertices, incidenceMatrix)) {
					vector<int> newSCC;
					for (vector<int>::iterator itTree = bfsTree.begin(); itTree != bfsTree.end(); itTree++) {
						newSCC.push_back(currentMatchRunPairs[*itTree]);
					}
					currentMatchRunStructures.push_back(newSCC);
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

	int maxComponentSize = kpdguiParameters->getMaxComponentSize();

	vector<int> orderedNodes;

	vector<int> tempNodes;
	int numberOfPairs = 0;
	int numberOfADs = 0;

	int nVertices = kpdguiRecord->getNumberOfNodes();

	for (int i = 1; i <= nVertices; i++){
		if (nodeInfoVector[i].nodeType == PAIR){
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
			child = getChildSCCWithADs(childIsAdjacentToLowerLevels, listOfBFSTrees, listOfBFSLevels, inducedBFSLevel, orderedNodes, visited, next, nextAD, childLevel, childLevelAD, childCanBeAD, numberOfADs, incidenceMatrix);

			int mostRecentNodeLevel = listOfBFSLevels.back().back();

			if (treeSize == maxComponentSize || (child == orderedNodes.size() && mostRecentNodeLevel + 1 == childLevel)){
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
					currentMatchRunStructures.push_back(newSCC);
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

std::string KPDGUISimulation::intToString(int number){
	std::stringstream ss;	//Create a stringstream
	ss << number;		//Add number to the stream
	return ss.str();	//Return a string with the contents of the stream
}

