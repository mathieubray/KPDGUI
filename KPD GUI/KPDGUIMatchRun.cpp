#include "KPDGUIMatchRun.h"

KPDGUIMatchRun::KPDGUIMatchRun(QList<KPDGUINode *> nodes, KPDGUIParameters * params){

	//Create progress bar
	progressBar = new QProgressDialog("Setting Up Simulation...", QString(), 0, 100);
	progressBar->setWindowModality(Qt::WindowModal);
	progressBar->setWindowTitle("Simulation Progress");
	progressBar->setAutoClose(false);
	progressBar->show();
	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();
	

	//Retrieve Relevant Parameters
	maxCycleSize = params->getMaxCycleSize();
	maxChainLength = params->getMaxChainLength();
	maxLRSSize = params->getMaxLRSSize();
	maximum = std::max(maxCycleSize, maxChainLength + 1);

	optScheme = params->getOptimizationScheme();
	utilityScheme = params->getUtilityScheme();

	addAdvantageToHighPRACandidates = params->addAdvantageToHighPRACandidates();
	praAdvantageCutoff = params->getPRAAdvantageCutoff();
	praAdvantageValue = params->getPRAAdvantageValue();
	
	estimateEU = params->estimateExpectedUtility();
	numberOfExpectedUtilityIterations = params->getNumberOfExpectedUtilityIterations();
	
	reserveOforO = params->reserveODonorsForOCandidates();
	checkHLA = params->checkAdditionalHLA();
	includeCompatible = params->includeCompatiblePairs();
	excludeABDonors = params->excludeABDonorsFromSimulation();
	allowABBridgeDonors = params->allowABBridgeDonors();


	// Construct Incidence, Probability and Utility Matrices
	generateMatrices(nodes);
	
	
	// Collect All Arrangements
	if (optScheme == LOCALLY_RELEVANT_SUBSETS) {
		collectLRSForCurrentMatchRun();
	}
	else {
		collectCyclesAndChainsForCurrentMatchRun();		
	}
	
	if (matchRunArrangements.size() > 0) {

		// Assign Utility to Each Arrangement
		if (optScheme == CYCLES_AND_CHAINS) {
			assignUtilitiesForCurrentMatchRun();
		}
		else {
			assignExpectedUtilitiesForCurrentMatchRun();
		}

		// Select Optimal Arrangements
		getOptimalSolutionForCurrentMatchRun(params->getOptimizationScheme(), params->getNumberOfSolutions());
	}
	
	// Close Progress Bar
	progressBar->close();
	QApplication::restoreOverrideCursor();
	QApplication::processEvents();

	delete progressBar;
}

KPDGUIMatchRun::~KPDGUIMatchRun(){

	currentMatchRunNodes.clear();

	matchRunNodeVector.clear();
	matchRunNodeTypeVector.clear();

	matchRunDonorIncidenceMatrix.clear();
	matchRunSuccessProbabilitiesMatrix.clear();
	matchRunUtilityMatrix.clear();
	matchRunCrossmatchMatrix.clear();

	matchRunIncidenceMatrix.clear();
	matchRunIncidenceMatrixReduced.clear();

	matchRunArrangements.clear();
	assignedValueOfMatchRunArrangements.clear();

	matchRunSelectedSolutions.clear();
	assignedValueOfMatchRunSolutions.clear();
}


// Generate master matrices for selected nodes
void KPDGUIMatchRun::generateMatrices(QList<KPDGUINode *> nodes) {

	matchRunNumberOfPairs = 0;
	matchRunNumberOfNDDs = 0;

	matchRunNodeVector.push_back(new KPDGUINode());
	matchRunNodeTypeVector.push_back(PAIR);
	
	currentMatchRunNodes.push_back(0);

	std::vector<KPDGUINode *> tempNodeVector;
	std::vector<KPDNodeType> tempNodeTypeVector;
	std::vector<int> tempNodes;

	//matchRunLog = "Available Nodes for Match Run: ";

	// Order nodes with NDDs in front
	foreach(KPDGUINode * node, nodes) {

		// Pairs need to have active candidate and at least one active donor; NDDs need to be active
		if (node->getStatus()) {

			// Can include compatible pairs if compatible option is set
			if (node->getType() == NDD) {

				matchRunNodeVector.push_back(node);
				matchRunNodeTypeVector.push_back(NDD);
				//currentMatchRunNodes.push_back(node->getID());

				matchRunNumberOfNDDs++;
				
				//qDebug() << QString::number(node->getID()) + "(" + node->getNameString() + ")";
			}
			else {
				if (isCompatible(node) && !includeCompatible) {
					//qDebug() << QString::number(node->getID()) + "(" + node->getNameString() + ") Not Included - Compatible Pair";
				}
				//else if (excludeABDonors){

				//}
				else {

					tempNodeVector.push_back(node);
					tempNodeTypeVector.push_back(PAIR);
					//tempNodes.push_back(node->getID());

					matchRunNumberOfPairs++;

					//qDebug() << QString::number(node->getID()) + "(" + node->getNameString() + ")";
				}
			}

			//matchRunLog.append(QString::number(node->getID()) + " ");
		}
	}

	for (int i = 0; i < tempNodeVector.size(); i++) {
		matchRunNodeVector.push_back(tempNodeVector[i]);
		matchRunNodeTypeVector.push_back(tempNodeTypeVector[i]);
		//currentMatchRunNodes.push_back(tempNodes[i]);
	}

	for (int i = 1; i < matchRunNodeVector.size(); i++) {
		currentMatchRunNodes.push_back(i);
		//qDebug() << QString::number(matchRunNodeVector[i]->getID()) << "," << KPDFunctions::toString(matchRunNodeTypeVector[i]) << "," << QString::number(currentMatchRunNodes[i]);
	}

	//matchRunLog.append("(" + QString::number(matchRunNumberOfNDDs) + " NDDs, " + QString::number(matchRunNumberOfPairs) + " Nodes)\n");
	//qDebug() << "(" + QString::number(matchRunNumberOfNDDs) + " NDDs, " + QString::number(matchRunNumberOfPairs) + " Nodes)";
	
	matchRunNumberOfNodes = matchRunNumberOfPairs + matchRunNumberOfNDDs;

	matchRunDonorIncidenceMatrix.assign(1 + matchRunNumberOfNodes, std::vector<std::vector<bool> >(1 + matchRunNumberOfNodes, std::vector<bool>(1, false)));
	matchRunSuccessProbabilitiesMatrix.assign(1 + matchRunNumberOfNodes, std::vector<std::vector<double> >(1 + matchRunNumberOfNodes, std::vector<double>(1, 0.0)));
	matchRunUtilityMatrix.assign(1 + matchRunNumberOfNodes, std::vector<std::vector<double> >(1 + matchRunNumberOfNodes, std::vector<double>(1, 0.0)));
	matchRunCrossmatchMatrix.assign(1 + matchRunNumberOfNodes, std::vector<std::vector<KPDCrossmatchResult> >(1 + matchRunNumberOfNodes, std::vector<KPDCrossmatchResult>(1, FAILED_CROSSMATCH_BT)));
	
	matchRunIncidenceMatrix.assign(1 + matchRunNumberOfNodes, std::vector<bool>(1 + matchRunNumberOfNodes, false));
	matchRunIncidenceMatrixReduced.assign(1 + matchRunNumberOfNodes, std::vector<bool>(1 + matchRunNumberOfNodes, false));

	for (int i = 1; i <= matchRunNumberOfNodes; i++) {

		KPDGUINode * node = matchRunNodeVector[i];
		int numberOfDonors = node->getNumberOfDonors();

		//Initialize matrices
		for (int j = 1; j <= matchRunNumberOfNodes; j++) {

			matchRunDonorIncidenceMatrix[i][j].assign(1 + numberOfDonors, false);
			matchRunSuccessProbabilitiesMatrix[i][j].assign(1 + numberOfDonors, 0.0);
			matchRunUtilityMatrix[i][j].assign(1 + numberOfDonors, 0.0);
			matchRunCrossmatchMatrix[i][j].assign(1 + numberOfDonors, FAILED_CROSSMATCH_BT);

			// Add in implicit edges
			if (i != j) {
				if (matchRunNodeTypeVector[j] == NDD) {

					for (int k = 1; k <= numberOfDonors; k++) {
						if (node->getDonor(k-1)->getStatus()) {

							matchRunIncidenceMatrix[i][j] = true;

							matchRunDonorIncidenceMatrix[i][j][k] = true;
							matchRunSuccessProbabilitiesMatrix[i][j][k] = 1.0;
							matchRunUtilityMatrix[i][j][k] = 0.0; //Unchanged
							matchRunCrossmatchMatrix[i][j][k] = SUCCESSFUL_CROSSMATCH;
						}
					}
				}
			}
		}

		for (int k = 1; k <= numberOfDonors; k++){
			
			KPDGUIDonor * donor = node->getDonor(k - 1);

			// If this specific donor is available
			if (donor->getStatus()) {

				// Go through all matches eminating from the donor
				// Note that these are all donor -> candidate matches
				foreach(KPDGUIMatch * match, donor->getMatches()) {

					KPDCrossmatchResult result = match->getCrossmatchResult();

					// If match is available
					if (match->getInclude()){
						
						// Seek out candidate based on ID
						int candidateNodeID = match->getCandidate()->getID();
						int j = -1;

						for (int l = 1; l <= matchRunNumberOfNodes; l++) {
							if (matchRunNodeVector[l]->getID() == candidateNodeID) {
								j = l;
								break;
							}
						}

						// If candidate is found, and thus available for the match run
						if (j != -1) {

							// Finally, check crossmatch result based on match run options
							bool successful = true;

							if (result == FAILED_CROSSMATCH_ADDITIONAL_HLA_AND_O_TO_NON_O) {
								if (checkHLA || reserveOforO) {
									successful = false;
								}
							}
							if (result == FAILED_CROSSMATCH_ADDITIONAL_HLA) {
								if (checkHLA) {
									successful = false;
								}
							}
							if (result == O_DONOR_TO_NON_O_CANDIDATE) {
								if (reserveOforO) {
									successful = false;
								}
							}
							if (result == FAILED_CROSSMATCH_BT || result == FAILED_CROSSMATCH_HLA) {
								successful = false;
							}

							if (successful) {
								
								matchRunDonorIncidenceMatrix[i][j][k] = true;
								matchRunSuccessProbabilitiesMatrix[i][j][k] = 1 - match->getFailureProbability();

								if (utilityScheme == FIVE_YEAR_SURVIVAL) {
									matchRunUtilityMatrix[i][j][k] = match->getFiveYearSurvival();
								}
								else if (utilityScheme == TEN_YEAR_SURVIVAL) {
									matchRunUtilityMatrix[i][j][k] = match->getTenYearSurvival();
								}
								else if (utilityScheme == HARD_TO_TRANSPLANT) {
									matchRunUtilityMatrix[i][j][k] = match->getTransplantScore();
								}
								else if (utilityScheme == ASSIGNED_SCORE) {
									matchRunUtilityMatrix[i][j][k] = match->getAssignedUtility();
								}
								else {
									matchRunUtilityMatrix[i][j][k] = 1;
								}

								matchRunCrossmatchMatrix[i][j][k] = result;

								matchRunIncidenceMatrix[i][j] = true;
								matchRunIncidenceMatrixReduced[i][j] = true;
							}
						}
					}
				}
			}
		}
	}

	/*for (int i = 1; i <= matchRunNumberOfNodes; i++) {
		
		int donors = matchRunNodeVector[i]->getNumberOfDonors();

		for (int j = 1; j <= matchRunNumberOfNodes; j++) {

			for (int k = 1; k <= donors; k++) {

				//qDebug() << "(" << i << "," << j << "," << k << ")";
				//qDebug() << matchRunDonorIncidenceMatrix[i][j][k] << "," << QString::number(matchRunSuccessProbabilitiesMatrix[i][j][k]) << "," << QString::number(matchRunUtilityMatrix[i][j][k]) << "," << KPDFunctions::toString(matchRunCrossmatchMatrix[i][j][k]);

			}
		}
	}*/
}

void KPDGUIMatchRun::collectCyclesAndChainsForCurrentMatchRun(){

	// Start Progress Bar
	progressBar->setLabelText("Discovering Cycles and Chains...");
	progressBar->setRange(0, matchRunNumberOfNodes);
	progressBar->setValue(0);
	

	// Depth-First Search for Cycles and Chains
	int start = 1;
	std::vector<int> visitedVector(1 + matchRunNumberOfNodes, 0);
	std::vector<int> stack_vec;	

	while (start <= matchRunNumberOfNodes){

		progressBar->setValue(start);

		visitedVector[start] = 1;
		stack_vec.push_back(start);
		int v = getChild(start, start, visitedVector, matchRunIncidenceMatrix);

		while (!stack_vec.empty()){
			if (v == -1){
				int top = stack_vec.back();
				stack_vec.pop_back();
				if (top == start){
					visitedVector[top] = 0;
					break;
				}
				visitedVector[top] = 0;
				v = getChild(top, stack_vec.back(), visitedVector, matchRunIncidenceMatrix);
			}
			else{
				visitedVector[v] = 1;
				stack_vec.push_back(v);

				//Potential Cycle or Chain Found!
				if (matchRunIncidenceMatrix[v][start]){
					
					int multipleNDDCheck = 0;
					int index = 0;

					//Copy Potential Cycle Or Chain
					std::vector<int> potentialCycleOrChain;
					for (unsigned i = 0; i < stack_vec.size(); i++){
						potentialCycleOrChain.push_back(currentMatchRunNodes[stack_vec[i]]);
					}

					//Count Non-Directed Donors; Save Index of Non-Directed Donor
					for (unsigned i = 0; i < potentialCycleOrChain.size(); i++){
						if (matchRunNodeTypeVector[potentialCycleOrChain[i]] == NDD){
							multipleNDDCheck++;
							index = i;
						}
					}

					//If there is 1 NDD, we're dealing with a chain
					if (multipleNDDCheck == 1){
						//Check if size of chain is appropriate
						if ((int)potentialCycleOrChain.size() <= maxChainLength + 1){
							//Queue up AD to front of chain
							while (index > 0){
								int temp = *(potentialCycleOrChain.begin());
								potentialCycleOrChain.erase(potentialCycleOrChain.begin());
								potentialCycleOrChain.push_back(temp);
								index--;
							}

							//If AB bridge donors are allowed, we're all set!
							if (allowABBridgeDonors) {
								matchRunArrangements.push_back(potentialCycleOrChain);
								matchRunArrangementHasNDD.push_back(true);
							}
							else {
								bool exclude = true;

								//If any of the associated donors have a blood type other than AB, then we're good
								for (int k = 1; k <= matchRunNodeVector[*(potentialCycleOrChain.end() - 1)]->getNumberOfDonors(); k++) {
									if (matchRunNodeVector[*(potentialCycleOrChain.end() - 1)]->getDonor(k-1)->getBT() != BT_AB) {
										exclude = false;
									}
								}

								if (!exclude) {
									matchRunArrangements.push_back(potentialCycleOrChain);
									matchRunArrangementHasNDD.push_back(true);
								}
							}
						}
					}

					// If there are no NDDs, we're dealing with a cycle
					else if (multipleNDDCheck == 0){
						//Check if size of cycle is appropriate; if it is, we're good to go!
						if ((int)potentialCycleOrChain.size() <= maxCycleSize){
							matchRunArrangements.push_back(potentialCycleOrChain);
							matchRunArrangementHasNDD.push_back(false);
						}
					}
				}

				if (stack_vec.size() >= maximum)
					v = -1;
				else {
					v = getChild(start, v, visitedVector, matchRunIncidenceMatrix);
				}
			}
		}
		start++;
	}

	//Output
	//matchRunLog << "Cycles and Chains: " << qint32(matchRunArrangements.size()) << "\n";
	//qDebug() << "Cycles and Chains: " << QString::number(matchRunArrangements.size());

	int i = 1;
	for (std::vector<std::vector<int> >::iterator it = matchRunArrangements.begin(); it != matchRunArrangements.end(); it++) {


		KPDNodeType nodeType = matchRunNodeVector[it->at(0)]->getType();

		QString arrangementString = KPDFunctions::toString(nodeType) + " " + QString::number(i) + ": ";


		for (std::vector<int>::iterator it2 = it->begin(); it2 != it->end(); it2++) {

			int id = matchRunNodeVector[*it2]->getID();

			arrangementString.append(QString::number(id));
			arrangementString.append("->");

		}

		arrangementString.chop(2);

		//qDebug() << arrangementString;

		i++;
	}

}

void KPDGUIMatchRun::collectLRSForCurrentMatchRun(){
	
	// Start Progress Bar
	progressBar->setLabelText("Discovering Locally Relevant Subgraphs...");
	progressBar->setRange(0, matchRunNumberOfNodes);
	progressBar->setValue(0);


	//Only need to run NDD sub-routine if there are NDDs in the match run (...herp de derp)
	if (matchRunNumberOfNDDs > 0) {
		getLRSWithNDDs();
	}

	getLRSPairsOnly();
}

void KPDGUIMatchRun::assignUtilitiesForCurrentMatchRun(){
	
	// Start Progress Bar
	progressBar->setLabelText("Calculating Utility...");
	progressBar->setRange(0, matchRunArrangements.size());
	progressBar->setValue(0);
	
	int i = 0;

	// Iterating through cycles and chains...
	for (std::vector<std::vector<int> >::iterator itArrangements = matchRunArrangements.begin(); itArrangements != matchRunArrangements.end(); itArrangements++){
		double util = 0;

		//... and sum over all potential transplants...
		for (std::vector<int>::iterator itNodes = (*itArrangements).begin(); itNodes != (*itArrangements).end() - 1; itNodes++){

			//... using the best potential matching donor to assign the value
			int bestDonorIndex = selectDonor(*itNodes, *(itNodes + 1));

			util += matchRunUtilityMatrix[*itNodes][*(itNodes + 1)][bestDonorIndex];

			// Add additional advantage if specified
			if (addAdvantageToHighPRACandidates && matchRunNodeVector[*(itNodes + 1)]->getCandidate()->getPRA() >= praAdvantageCutoff) {
				util += praAdvantageValue;
			}
		}

		// For cycles, add the final transplant back to the original candidate
		if (matchRunNodeTypeVector[*(itArrangements->begin())] == PAIR) {
			int bestDonorIndex = selectDonor(*(itArrangements->end() - 1), *(itArrangements->begin()));

			util += matchRunUtilityMatrix[*(itArrangements->end() - 1)][*(itArrangements->begin())][bestDonorIndex];

			if (addAdvantageToHighPRACandidates && matchRunNodeVector[*(itArrangements->begin())]->getCandidate()->getPRA() >= praAdvantageCutoff) {
				util += praAdvantageValue;
			}
		}

		assignedValueOfMatchRunArrangements.push_back(util);
		progressBar->setValue(i);
	}
}

void KPDGUIMatchRun::assignExpectedUtilitiesForCurrentMatchRun() {
	
	// Start Progress Bar
	progressBar->setLabelText("Calculating Utility...");
	progressBar->setRange(0, matchRunArrangements.size());
	progressBar->setValue(0);
	
	// Iterating through arrangements...
	int i = 0;
	for (std::vector<std::vector<int> >::iterator itArrangements = matchRunArrangements.begin(); itArrangements != matchRunArrangements.end(); itArrangements++) {
		
		double eu = 0;

		// ... and either estimate or calculate expected utility
		if (estimateEU) {
			eu = estimateExpectedUtility(*itArrangements);
		}
		else {
			eu = calculateExpectedUtility(*itArrangements);
		}

		assignedValueOfMatchRunArrangements.push_back(eu);

		progressBar->setValue(i);
	}

}

void KPDGUIMatchRun::getOptimalSolutionForCurrentMatchRun(KPDOptimizationScheme scheme, int numberOfSolutions){
	
	// Start Progress Bar
	progressBar->setLabelText("Finding Optimal Solutions...");
	progressBar->setRange(0, numberOfSolutions);
	progressBar->setValue(0);


	// If there are no arrangements, no need to do anything
	int nArrangements = (int)matchRunArrangements.size();
	if (nArrangements == 0) return;
		
	GRBEnv *env = 0;	//Created outside try; needs to be recollected;
	GRBVar *vars = 0;	//Created outside try; needs to be recollected;
	GRBVar *myVars = new GRBVar[nArrangements + 1]; //Created outside try; needs to be recollected;	

	int iteration = 1;

	try{
		env = new GRBEnv();
		env->set(GRB_IntParam_Threads, 4); // Limit the threads

		GRBModel model = GRBModel(*env);
		model.getEnv().set(GRB_IntParam_OutputFlag, 0);// 0 means no solver output; 1 otherwise;

		//Set utilities on arrangements
		for (int i = 1; i <= nArrangements; i++){
			std::string s = "cycle_" + KPDFunctions::intToString(i);
			myVars[i] = model.addVar(0.0, 1.0, -1 * assignedValueOfMatchRunArrangements[i - 1], GRB_BINARY, s); //The default is min, hence the -1
		}		
		model.update();

		//Restriction: Each vertex can only appear at most once in solution
		for (int i = 1; i < currentMatchRunNodes.size(); i++){
			int index = currentMatchRunNodes[i];
			GRBLinExpr expr = 0;
			for (int j = 0; j <= nArrangements - 1; j++){
				for (std::vector<int>::iterator it = matchRunArrangements[j].begin(); it != matchRunArrangements[j].end(); ++it){
					if (*it == index){
						expr += myVars[j + 1];
					}
				}
			}
			std::string s = "vertex_" + KPDFunctions::intToString(i);
			model.addConstr(expr, GRB_LESS_EQUAL, 1.0, s); // Disjoint cycles and chains
		}

		// Optimize
		model.optimize();

		double objective = 0.0;

		int optimstatus = model.get(GRB_IntAttr_Status);
		if (optimstatus == GRB_OPTIMAL) { // GRB_OPTIMAL when the MIPGap is reached, default is 1e-4;
			objective = model.get(GRB_DoubleAttr_ObjVal);
		}
		else if (optimstatus == GRB_INF_OR_UNBD) {
			matchRunLog.append("Model is infeasible or unbounded\n");
			return;
		}
		else if (optimstatus == GRB_INFEASIBLE) {
			matchRunLog.append("Model is infeasible\n");
			return;
		}
		else if (optimstatus == GRB_UNBOUNDED) {
			matchRunLog.append("Model is unbounded\n");
			return;
		}
		else {
			matchRunLog.append("Optimization was stopped\n");
			return;
		}

		//Retrieve Solution
		int numvars = model.get(GRB_IntAttr_NumVars);
		vars = model.getVars();

		std::vector<int> selectedSolution;

		for (int j = 0; j < numvars; j++) {
			GRBVar v = vars[j];
			if (v.get(GRB_DoubleAttr_X) == 1){
				selectedSolution.push_back(j);
			}
		}

		matchRunSelectedSolutions.push_back(selectedSolution);
		assignedValueOfMatchRunSolutions.push_back((-1)*objective);
		
		if (numberOfSolutions > 1) {
			//.append(QString::number(iteration) + "- ");
			//matchRunLog.append("Optimal objective: " + QString::number((-1)*objective) + "\n");
		}
		//matchRunLog.append("Optimization complete / ");

		//qDebug() << "Optimal objective: " + QString::number((-1)*objective);
		//qDebug() << "Optimization Complete - Solution " << QString::number(iteration);

		QString solutionString = "Selcted Arrangements: " + QString::number(selectedSolution.at(0) + 1);
		for (std::vector<int>::iterator newIt = selectedSolution.begin() + 1; newIt != selectedSolution.end(); newIt++) {
			solutionString.append("-");
			solutionString.append(QString::number(*newIt + 1));
		}
		//qDebug() << solutionString;

		progressBar->setValue(iteration);

		while (iteration < numberOfSolutions){
			
			GRBLinExpr expr = 0;

			//Add restriction against previously found solution
			for (int j = 0; j <= nArrangements - 1; j++){
				bool found = false;
				for (std::vector<int>::iterator it = matchRunSelectedSolutions[iteration - 1].begin(); it != matchRunSelectedSolutions[iteration - 1].end(); ++it){
					if (*it == j){ found = true; }
				}
				if (found == true){
					expr += (1 - myVars[j + 1]);
				}
				else {
					expr += myVars[j + 1];
				}
			}

			iteration++;

			std::string s = "alternate_" + KPDFunctions::intToString(iteration);
			model.addConstr(expr, GRB_GREATER_EQUAL, 1.0, s); //Remove previous solution

			// Optimize
			model.optimize();

			// Retrieve Value of Solution
			optimstatus = model.get(GRB_IntAttr_Status);
			if (optimstatus == GRB_OPTIMAL) { // GRB_OPTIMAL when the MIPGap is reached, default is 1e-4;
				objective = model.get(GRB_DoubleAttr_ObjVal);
			}
			else if (optimstatus == GRB_INF_OR_UNBD) {
				matchRunLog.append("Model is infeasible or unbounded\n");
				return;
			}
			else if (optimstatus == GRB_INFEASIBLE) {
				matchRunLog.append("Model is infeasible\n");
				return;
			}
			else if (optimstatus == GRB_UNBOUNDED) {
				matchRunLog.append("Model is unbounded\n");
				return;
			}
			else {
				matchRunLog.append("Optimization was stopped\n");
				return;
			}

			// Retrieve Solution
			numvars = model.get(GRB_IntAttr_NumVars);
			vars = model.getVars();

			std::vector<int> selectedSolution;

			for (int j = 0; j < numvars; j++) {
				GRBVar v = vars[j];
				if (v.get(GRB_DoubleAttr_X) == 1){
					selectedSolution.push_back(j);
				}
			}

			matchRunSelectedSolutions.push_back(selectedSolution);
			assignedValueOfMatchRunSolutions.push_back((-1)*objective);


			//matchRunLog.append(QString::number(iteration) + ": ");
			//matchRunLog.append("Optimal objective: " + QString::number((-1)*objective) + "\n");
			//matchRunLog.append("Optimization complete / ");

			//qDebug() << "Optimal objective: " + QString::number((-1)*objective);
			//qDebug() << "Optimization Complete - Solution " << QString::number(iteration);


			QString solutionString = "Selcted Arrangements: " + QString::number(selectedSolution.at(0) + 1);
			for (std::vector<int>::iterator newIt = selectedSolution.begin() + 1; newIt != selectedSolution.end(); newIt++) {
				solutionString.append("-");
				solutionString.append(QString::number(*newIt + 1));
			}
			//qDebug() << solutionString;
			
			progressBar->setValue(iteration);
			//QApplication::processEvents();
		}

	}
	catch (GRBException e) {
		//matchRunLog.append("Error code = " + QString::number(e.getErrorCode()) + "\n");
		//matchRunLog.append(QString::fromStdString(e.getMessage()) + "\n");
	}
	catch (...) {
		//matchRunLog.append("Error during optimization\n");
	}

	delete[] myVars;
	delete[] vars;
	delete env;
}

bool KPDGUIMatchRun::isCompatible(KPDGUINode * node) {

	bool compatible = false;

	QVector<KPDCrossmatchResult> results = node->getCrossmatchResults();
	
	int i = 0;
	foreach(KPDGUIDonor * donor, node->getDonors()) {

		if (donor->getStatus()) {

			KPDCrossmatchResult result = results[i];

			if (result == SUCCESSFUL_CROSSMATCH) {
				compatible = true;
				break;
			}
			if (result == O_DONOR_TO_NON_O_CANDIDATE && !reserveOforO) {
				compatible = true;
				break;
			}
			if (result == FAILED_CROSSMATCH_ADDITIONAL_HLA && !checkHLA) {
				compatible = true;
				break;
			}
			if (result == FAILED_CROSSMATCH_ADDITIONAL_HLA_AND_O_TO_NON_O && !reserveOforO && !checkHLA) {
				compatible = true;
				break;
			}
		}

		i++;
	}
	
	return compatible;
}


int KPDGUIMatchRun::selectDonor(int donorNodeID, int candidateNodeID) {

	double maxUtil = 0.0;
	int maxDonorID = -1; // -1 means no donor is selected

	//Iterate through donors
	for (int donorID = 1; donorID <= matchRunNodeVector[donorNodeID]->getNumberOfDonors(); donorID++) {

		//Only consider donors that match between the donor node and the candidate node
		if (matchRunDonorIncidenceMatrix[donorNodeID][candidateNodeID][donorID]) {

			//If the donor provides more utility than the current max donor, replace with new donor, and update max utility value
			if (matchRunUtilityMatrix[donorNodeID][candidateNodeID][donorID] > maxUtil) {
				maxDonorID = donorID;
				maxUtil = matchRunUtilityMatrix[donorNodeID][candidateNodeID][donorID];
			}
		}

		donorID++;
	}

	return maxDonorID;
}

int KPDGUIMatchRun::getChild(int lower, int current, std::vector<int> &visitedVector, std::vector<std::vector<bool> > &incidence){
	int nV = (int)visitedVector.size() - 1;
	for (int j = lower + 1; j <= nV; j++){
		if (incidence[current][j] == true && visitedVector[j] == 0)
			return j;
	}
	return -1;
}


void KPDGUIMatchRun::getLRSPairsOnly(){
	
	vector<int> pairs;
	pairs.push_back(0);

	for (int i = 1; i <= matchRunNumberOfNodes; i++) {
		if (matchRunNodeTypeVector[currentMatchRunNodes[i]] == PAIR) {
			pairs.push_back(i);
		}
	}

	int numberOfPairs = (int)pairs.size() - 1;

	std::vector<std::vector<bool> > reverseMatrix;
	reverseMatrix.assign(1 + numberOfPairs, std::vector<bool>(1 + numberOfPairs, false));

	for (int i = 1; i <= numberOfPairs; i++) {
		for (int j = 1; j <= numberOfPairs; j++) {
			if (i != j) {
				reverseMatrix[j][i] = matchRunIncidenceMatrixReduced[pairs[i]][pairs[j]];
			}
		}
	}

	//Collect LRSs	
	vector<int> bfsTree;
	vector<int> bfsLevel;
	vector<bool> visited(1 + numberOfPairs, false);

	int next;
	int child;
	int childLevel;

	//Iterate Through Pairs	
	for (int i = 1; i <= numberOfPairs; i++) {
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
			child = getChildLRSPairsOnly(bfsTree, bfsLevel, pairs, visited, next, childLevel);

			// If (i) the size of the bfsTree is at the limit or (ii) no children, bfsLevel is currently at the next bfsLevel of the previous node
			if ((int)bfsTree.size() == maxLRSSize || (child == -1 && childLevel == bfsLevel.back() + 1)) {
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

				int treeSize = (int)bfsTree.size();

				std::vector<bool> reverseVisited;
				reverseVisited.assign(1 + numberOfPairs, false);

				std::queue<int> reverseBFSTree;
				reverseBFSTree.push(bfsTree[0]);
				reverseVisited[bfsTree[0]] = true;

				int curr = 1;
				while (!reverseBFSTree.empty()) {
					int u = reverseBFSTree.front();
					reverseBFSTree.pop();

					for (int k = curr; k < treeSize; k++) {
						if (reverseVisited[bfsTree[k]] == false && reverseMatrix[u][bfsTree[k]] == true) {
							reverseVisited[bfsTree[k]] = true;
							reverseBFSTree.push(bfsTree[k]);
						}
					}
				}

				bool reverseTreeIsConnected = true;

				for (int k = 0; k < treeSize; k++) {
					if (!reverseVisited[bfsTree[k]]) {
						reverseTreeIsConnected = false;
						break;
					}
				}

				if (reverseTreeIsConnected) {

					std::vector<int> newLRS;
					for (std::vector<int>::iterator itTree = bfsTree.begin(); itTree != bfsTree.end(); itTree++) {
						newLRS.push_back(currentMatchRunNodes[pairs[*itTree]]);
					}

					if (validateLRSBounds(newLRS)) {
						matchRunArrangements.push_back(newLRS);
						matchRunArrangementHasNDD.push_back(false);
					}
				}

				next = child + 1;
			}
		}
	}
}


int KPDGUIMatchRun::getChildLRSPairsOnly(std::vector<int> &tree, std::vector<int> &level, std::vector<int> &pairs, std::vector<bool> &visited, int next, int childLevel) {

	int size = (int)pairs.size() - 1;

	for (int child = next; child <= size; child++) {
		//Can only visit children not already visited
		if (visited[child] == false) {
			//Go through previous nodes
			for (int i = 0; i<(int)level.size(); i++) {
				//At low levels, make sure potential node is not a direct successor
				if (level[i] < childLevel - 1) {
					if (matchRunIncidenceMatrixReduced[pairs[tree[i]]][pairs[child]]) {
						break;
					}
				}
				//At previous level, if potential node is a successor, it is the next child
				if (level[i] == childLevel - 1) {
					if (matchRunIncidenceMatrixReduced[pairs[tree[i]]][pairs[child]]) {
						return child;
					}
				}
			}
		}
	}

	return -1;
}

void KPDGUIMatchRun::getLRSWithNDDs(){
		
	vector<vector<int> > listOfBFSTrees;
	vector<vector<int> > listOfBFSLevels;
	vector<int> inducedBFSLevel;

	vector<vector<bool> > adjacentToLowerLevels;

	vector<bool> visited(matchRunNumberOfNodes, false);

	int child;
	int next;
	int nextNDD;

	int childLevel;
	int childLevelNDD;
	int treeSize;

	bool childCanBeNDD;
	bool childIsAdjacentToLowerLevels;

	for (int i = 0; i < matchRunNumberOfNDDs; i++) {

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

		next = matchRunNumberOfNDDs; //First regular pair
		nextNDD = i + 1;
		childLevel = 1;
		childLevelNDD = 1;
		childCanBeNDD = false;

		while (!listOfBFSTrees.empty()) {

			child = getChildLRSWithNDDs(childIsAdjacentToLowerLevels, listOfBFSTrees, listOfBFSLevels, inducedBFSLevel,
				visited, next, nextNDD, childLevel, childLevelNDD, childCanBeNDD);

			if (treeSize == maxChainLength || (child == matchRunNumberOfNodes && listOfBFSLevels.back().back() + 1 == childLevel)) {
				if (listOfBFSTrees.back().back() < matchRunNumberOfNDDs) {
					if (listOfBFSTrees.size() > 1) {
						//If previous super tree level is one higher than the super tree level before it
						if (inducedBFSLevel.back() == inducedBFSLevel[inducedBFSLevel.size() - 2] + 1) {
							//Assign the before super tree level to child level
							childLevel = listOfBFSLevels[listOfBFSLevels.size() - 2].back() + 1;
							//Assign the most recent super tree level to child level NDD
							childLevelNDD = inducedBFSLevel.back();

							//Assign next to the first listed pair
							next = matchRunNumberOfNDDs;
						}
						else {
							childLevel = listOfBFSLevels[listOfBFSLevels.size() - 2].back();
							childLevelNDD = inducedBFSLevel.back();

							next = std::max(matchRunNumberOfNDDs, listOfBFSTrees[listOfBFSTrees.size() - 2].back() + 1);
						}
					}

					inducedBFSLevel.pop_back();

					nextNDD = listOfBFSTrees.back().back() + 1;
					childCanBeNDD = true;

					visited[listOfBFSTrees.back().back()] = false;

					listOfBFSTrees.pop_back();
					listOfBFSLevels.pop_back();
					adjacentToLowerLevels.pop_back();
				}

				else {
					nextNDD = matchRunNumberOfNDDs;
					next = listOfBFSTrees.back().back() + 1;
					if (listOfBFSLevels.back().back() == listOfBFSLevels.back()[listOfBFSLevels.back().size() - 2] + 1) {
						childLevelNDD = inducedBFSLevel.back() + 1;
					}
					else {
						childLevelNDD = inducedBFSLevel.back();
					}

					childLevel = listOfBFSLevels.back().back();

					if (adjacentToLowerLevels.back().back() == true) {
						childCanBeNDD = false;
					}

					visited[listOfBFSTrees.back().back()] = false;
					listOfBFSTrees.back().pop_back();
					listOfBFSLevels.back().pop_back();
					adjacentToLowerLevels.back().pop_back();
				}
				treeSize--;
			}

			else if (child == matchRunNumberOfNodes && listOfBFSLevels.back().back() == childLevel) {
				next = matchRunNumberOfNDDs;
				nextNDD = i + 1;
				childLevel = childLevel + 1;
				childLevelNDD = childLevelNDD + 1;
			}

			else {
				if (child < matchRunNumberOfNDDs) {

					vector<int> newBFSTree;
					newBFSTree.push_back(child);
					listOfBFSTrees.push_back(newBFSTree);

					vector<int> newBFSLevel;
					newBFSLevel.push_back(0);
					listOfBFSLevels.push_back(newBFSLevel);

					inducedBFSLevel.push_back(childLevelNDD);

					vector<bool> newAdjacencyList;
					newAdjacencyList.push_back(childIsAdjacentToLowerLevels);
					adjacentToLowerLevels.push_back(newAdjacencyList);

					next = matchRunNumberOfNDDs;
					nextNDD = child + 1;
					childLevel = 0;

					if (childIsAdjacentToLowerLevels == false) {
						childCanBeNDD = false;
					}
				}

				else {
					listOfBFSTrees.back().push_back(child);
					listOfBFSLevels.back().push_back(childLevel);
					if (childCanBeNDD == true) {
						adjacentToLowerLevels.back().push_back(false);
					}
					else {
						adjacentToLowerLevels.back().push_back(childIsAdjacentToLowerLevels);

						if (childIsAdjacentToLowerLevels == true || (listOfBFSTrees.size() == 1 && listOfBFSTrees.front().size() == 2)) {
							childCanBeNDD = true;
						}
					}

					next = child + 1;
					nextNDD = listOfBFSTrees.back().at(0) + 1;
					childLevelNDD = inducedBFSLevel.back();
				}

				treeSize++;
				visited[child] = true;
				if (childCanBeNDD == true) {
					vector<int> newLRS;

					for (int i = 0; i < (int)listOfBFSTrees.size(); i++) {
						for (int j = 0; j < (int)listOfBFSTrees[i].size(); j++) {
							newLRS.push_back(currentMatchRunNodes[listOfBFSTrees[i][j] + 1]);
						}
					}

					if (validateLRSBounds(newLRS)) {
						matchRunArrangements.push_back(newLRS);
						matchRunArrangementHasNDD.push_back(true);
					}
				}
			}
		}
	}
}


int KPDGUIMatchRun::getChildLRSWithNDDs(bool &childIsAdjacentToLowerLevels, std::vector<std::vector<int> > &trees, std::vector<std::vector<int> > &levels, std::vector<int> &inducedLevels,
	std::vector<bool> &visited, int &next, int &nextNDD, int &childLevel, int &childLevelNDD, bool &childCanBeNDD) {

	bool breakFlag;

	if (childCanBeNDD && !(inducedLevels.size() == 1 && childLevelNDD == 0)) {
		//Iterate through NDDs as potential child
		for (int child = nextNDD; child < matchRunNumberOfNDDs; child++) {
			if (visited[child] == false) {
				breakFlag = false;

				childIsAdjacentToLowerLevels = false;

				for (int i = 0; i < (int)trees.size(); i++) {
					if (inducedLevels[i] < childLevelNDD - 1) {
						for (int j = 0; j < (int)trees[i].size(); j++) {
							int node = trees[i][j] + 1;
							int potentialChild = child + 1;

							if (matchRunIncidenceMatrixReduced[node][potentialChild] || matchRunIncidenceMatrixReduced[potentialChild][node]) {
								breakFlag = true;
								break;
							}
						}
					}
					else if (inducedLevels[i] == childLevelNDD - 1) {
						if (trees[i][0] < child) {
							for (int j = 0; j < (int)trees[i].size(); j++) {
								int node = trees[i][j] + 1;
								int potentialChild = child + 1;

								if (matchRunIncidenceMatrixReduced[node][potentialChild]) {
									breakFlag = true;
									break;
								}

								if (matchRunIncidenceMatrixReduced[potentialChild][node]) {
									childIsAdjacentToLowerLevels = true;
								}
							}
						}
						else {
							for (int j = 0; j < (int)trees[i].size(); j++) {
								int node = trees[i][j] + 1;
								int potentialChild = child + 1;

								if (matchRunIncidenceMatrixReduced[potentialChild][node]) {
									breakFlag = true;
									break;
								}

								if (matchRunIncidenceMatrixReduced[node][potentialChild]) {
									childIsAdjacentToLowerLevels = true;
								}
							}
						}
					}

					if (breakFlag) {
						break;
					}
				}

				if (breakFlag == false) {
					return child;
				}
			}
		}
	}

	if (!(levels.back().size() == 1 && childLevel == 0)) {
		//Start at "Next", iterate through all pairs.
		for (int child = next; child < matchRunNumberOfNodes; child++) {
			if (visited[child] == false) {
				breakFlag = false;

				childIsAdjacentToLowerLevels = false;

				for (int i = 0; i < (int)trees.size(); i++) {
					//Iterator is at last trees.
					if (i == int(trees.size()) - 1) {
						//Iterate through current trees
						for (int j = 0; j < (int)trees[i].size(); j++) {

							//Current Node is at a low level
							if (levels[i][j] < childLevel - 1) {
								int node = trees[i][j] + 1;
								int potentialChild = child + 1;

								if (matchRunIncidenceMatrixReduced[node][potentialChild]) {
									breakFlag = true;
									break;
								}
							}

							//Current node is at previous level
							else if (levels[i][j] == childLevel - 1) {
								int node = trees[i][j] + 1;
								int potentialChild = child + 1;

								if (matchRunIncidenceMatrixReduced[node][potentialChild]) {
									return child;
								}
							}
						}
					}
					//Induced BFS level is at low level
					else if (inducedLevels[i] < inducedLevels.back() - 1) {
						for (int j = 0; j < (int)trees[i].size(); j++) {
							int node = trees[i][j] + 1;
							int potentialChild = child + 1;

							if (matchRunIncidenceMatrixReduced[node][potentialChild] || matchRunIncidenceMatrixReduced[potentialChild][node]) {
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
							for (int j = 0; j < (int)trees[i].size(); j++) {
								int node = trees[i][j] + 1;
								int potentialChild = child + 1;

								if (matchRunIncidenceMatrixReduced[node][potentialChild]) {
									breakFlag = true;
									break;
								}

								if (matchRunIncidenceMatrixReduced[potentialChild][node]) {
									childIsAdjacentToLowerLevels = true;
								}
							}
						}
						else {
							//Iterate through nodes 
							for (int j = 0; j < (int)trees[i].size(); j++) {
								int node = trees[i][j] + 1;
								int potentialChild = child + 1;

								if (matchRunIncidenceMatrixReduced[potentialChild][node]) {
									breakFlag = true;
									break;
								}

								if (matchRunIncidenceMatrixReduced[node][potentialChild]) {
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
							for (int j = 0; j < (int)trees[i].size(); j++) {
								int node = trees[i][j] + 1;
								int potentialChild = child + 1;

								if (matchRunIncidenceMatrixReduced[node][potentialChild]) {
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

	return matchRunNumberOfNodes;
}


bool KPDGUIMatchRun::validateLRSBounds(std::vector<int> & arrangement) {

	// Obtain matrix of shortest path between any two nodes

	int arrangementSize = (int)arrangement.size();

	if (arrangementSize <= 1) {
		return false;
	}

	std::vector<std::vector<int> > shortestPathLengths(arrangementSize, std::vector<int>(arrangementSize, matchRunNumberOfNodes));

	for (int i = 0; i < arrangementSize; i++) {
		shortestPathLengths[i][i] = 0;
	}

	for (int i = 1; i < arrangementSize; i++) {
		for (int j = 0; j < i; j++) {

			for (int q = 0; q <= i - 1; q++) {
				if (matchRunIncidenceMatrix[arrangement[q]][arrangement[i]]) {
					shortestPathLengths[j][i] = std::min(matchRunNumberOfNodes, shortestPathLengths[j][q] + 1);
				}
			}

			for (int q = 0; q <= i - 1; q++) {
				if (matchRunIncidenceMatrix[arrangement[i]][arrangement[q]]) {
					shortestPathLengths[i][j] = std::min(matchRunNumberOfNodes, shortestPathLengths[q][j] + 1);
				}
			}

		}
		for (int j = 0; j < i; j++) {
			for (int k = 0; k < j; k++) {
				shortestPathLengths[j][k] = std::min(shortestPathLengths[j][k], shortestPathLengths[j][i] + shortestPathLengths[i][k]);
				shortestPathLengths[k][j] = std::min(shortestPathLengths[k][j], shortestPathLengths[k][i] + shortestPathLengths[i][j]);
			}
		}
	}

	vector<bool> visited(arrangementSize, false);
	vector<int> stack;
	visited[0] = true;
	stack.push_back(0);
	int connections = 1;
	while (!stack.empty()) {
		for (int i = 0; i < arrangementSize; i++) {
			if (!visited[i]) {
				if (matchRunNodeTypeVector[arrangement[stack.front()]] != PAIR) {
					if (shortestPathLengths[stack.front()][i] <= maxChainLength + 1) {
						visited[i] = true;
						stack.push_back(i);
						connections++;
					}
				}
				else {
					if ((matchRunNodeTypeVector[arrangement[i]] == PAIR && shortestPathLengths[i][stack.front()] + shortestPathLengths[stack.front()][i] <= maxCycleSize) ||
						(matchRunNodeTypeVector[arrangement[i]] != PAIR && shortestPathLengths[i][stack.front()] <= maxChainLength + 1)) {

						visited[i] = true;
						stack.push_back(i);
						connections++;
					}
				}
			}
		}
		stack.erase(stack.begin());
	}

	return connections == arrangementSize;
}


double KPDGUIMatchRun::calculateExpectedUtility(std::vector<int> & arrangement) {

	int N = (int)arrangement.size();
	double utility = 0;

	//Collect and count all available donors within the arrangement
	std::vector<int> donorNodeIndices;
	std::vector<int> donorIndices;
	donorNodeIndices.push_back(0);
	donorIndices.push_back(0);

	int numberOfDonors = 0;

	int i = 1;
	for (std::vector<int>::iterator arrangementIt = arrangement.begin(); arrangementIt != arrangement.end(); arrangementIt++) {

		for (int k = 1; k <= matchRunNodeVector[*arrangementIt]->getNumberOfDonors(); k++) {
			donorNodeIndices.push_back(i);
			donorIndices.push_back(k);
			numberOfDonors++;
		}
		i++;
	}

	//Iterates through each possible subset of nodes
	for (int d = 3; d < pow((double)2, numberOfDonors); d++) {

		std::vector<int> nodeFlags(numberOfDonors + 1, 0);

		int donorSubsetSize = KPDFunctions::setFlags(d, nodeFlags);

		//Must be at least 2 nodes
		if (donorSubsetSize > 1) {

			std::vector<std::vector<bool> > subsetDonorAvailability(1 + N, std::vector<bool>(1, false));
			std::vector<bool> subsetCandidateAvailability(1 + N, false);

			for (int i = 1; i <= N; i++) {
				int nodeNumberOfDonors = matchRunNodeVector[arrangement[i - 1]]->getNumberOfDonors();
				subsetDonorAvailability[i].assign(1 + nodeNumberOfDonors, false);
			}

			//Iterate through nodes and mark availability
			for (int flag = 1; flag <= numberOfDonors; flag++) {

				int nodeIndex = donorNodeIndices[flag];
				int nodeID = arrangement[nodeIndex - 1];

				int donorID = donorIndices[flag];

				if (nodeFlags[flag] != 0) {
					subsetDonorAvailability[nodeIndex][donorID] = true;
					subsetCandidateAvailability[nodeIndex] = true;
				}
			}

			double probSubset = 1;

			//Calculate probability of subset
			for (int i = 1; i <= N; i++) {
				int nodeID = arrangement[i - 1];

				double probNode = 1;

				//Update with probability of candidate subset
				if (matchRunNodeTypeVector[nodeID] != PAIR) {
					for (int k = 1; k <= matchRunNodeVector[nodeID]->getNumberOfDonors(); k++) {
						if (subsetDonorAvailability[i][k]) {
							probNode = probNode * (1 - matchRunNodeVector[nodeID]->getDonor(k-1)->getFailureProbability());
						}
						else {
							probNode = probNode * (1 - (1 - matchRunNodeVector[nodeID]->getDonor(k-1)->getFailureProbability()));
						}
					}
				}

				if (matchRunNodeTypeVector[nodeID] == PAIR) {

					if (subsetCandidateAvailability[i]) {

						for (int k = 1; k <= matchRunNodeVector[nodeID]->getNumberOfDonors(); k++) {
							if (subsetDonorAvailability[i][k]) {
								probNode = probNode * (1 - matchRunNodeVector[nodeID]->getDonor(k-1)->getFailureProbability());
							}
							else {
								probNode = probNode * (1 - (1 - matchRunNodeVector[nodeID]->getDonor(k-1)->getFailureProbability()));
							}
						}

						probNode = probNode * (1 - matchRunNodeVector[nodeID]->getCandidate()->getFailureProbability());
					}
					else {

						for (int k = 1; k <= matchRunNodeVector[nodeID]->getNumberOfDonors(); k++) {
							probNode = probNode * (1 - (1 - matchRunNodeVector[nodeID]->getDonor(k-1)->getFailureProbability()));
						}

						probNode = 1 - (1 - matchRunNodeVector[nodeID]->getCandidate()->getFailureProbability()) * (1 - probNode);
					}
				}

				probSubset = probSubset * probNode;
			}

			if (probSubset > 0) {

				std::vector<int> edgeSubsetCandidateIndices;
				std::vector<int> edgeSubsetDonorNodeIndices;
				std::vector<int> edgeSubsetDonorIDs;

				edgeSubsetCandidateIndices.push_back(0);
				edgeSubsetDonorNodeIndices.push_back(0);
				edgeSubsetDonorIDs.push_back(0);

				int numberOfEdgesInDonorSubset = 0;

				//Collect possible edges
				for (int i = 1; i <= N; i++) {
					int donorNodeID = arrangement[i - 1];
					for (int j = 1; j <= N; j++) {
						if (i != j) {

							int candidateNodeID = arrangement[j - 1];

							if (matchRunIncidenceMatrix[donorNodeID][candidateNodeID] && matchRunNodeTypeVector[candidateNodeID] == PAIR) {

								for (int k = 1; k <= matchRunNodeVector[donorNodeID]->getNumberOfDonors(); k++) {
									if (subsetDonorAvailability[i][k] && subsetCandidateAvailability[j] && matchRunDonorIncidenceMatrix[donorNodeID][candidateNodeID][k]) {
										edgeSubsetDonorNodeIndices.push_back(i);
										edgeSubsetCandidateIndices.push_back(j);
										edgeSubsetDonorIDs.push_back(k);

										numberOfEdgesInDonorSubset++;
									}
								}
							}
						}
					}
				}

				// Iterate through every possible combination of edges
				for (int e = 1; e < pow((double)2, numberOfEdgesInDonorSubset); e++) {

					std::vector<int> edgeFlags(1 + numberOfEdgesInDonorSubset, 0);

					int edgeSubsetSize = KPDFunctions::setFlags(e, edgeFlags);

					double probEdgeSubset = probSubset;

					std::vector<std::vector<bool> > reducedIncidenceMatrix(1 + N, std::vector<bool>(1 + N, false));
					std::vector<std::vector<std::vector<bool> > > reducedDonorIncidenceMatrix(1 + N, std::vector<std::vector<bool> >(1 + N, std::vector<bool>(1, false)));
					std::vector<std::vector<std::vector<double> > > reducedUtilityMatrix(1 + N, std::vector<std::vector<double> >(1 + N, std::vector<double>(1, 0.0)));

					std::vector<KPDNodeType> reducedNodeTypeVector(1 + N, PAIR);
					std::vector<std::vector<KPDBloodType> > reducedDonorBloodTypes(1 + N, std::vector<KPDBloodType>(1, BT_AB));

					//Build reduced matrices
					for (int i = 1; i <= N; i++) {

						int donorNodeID = arrangement[i - 1];

						int arrangementNodeDonors = matchRunNodeVector[donorNodeID]->getNumberOfDonors();

						for (int j = 1; j <= N; j++) {
							reducedDonorIncidenceMatrix[i][j].assign(1 + arrangementNodeDonors, false);
							reducedUtilityMatrix[i][j].assign(1 + arrangementNodeDonors, 0.0);

							//Implicit backward edges
							int candidateNodeID = arrangement[j - 1];
							if (matchRunNodeTypeVector[donorNodeID] == PAIR && matchRunNodeTypeVector[candidateNodeID] != PAIR) {
								reducedIncidenceMatrix[i][j] = true;
							}
						}

						reducedNodeTypeVector[i] = matchRunNodeTypeVector[donorNodeID];

						reducedDonorBloodTypes[i].assign(1 + arrangementNodeDonors, BT_AB);
						for (int k = 1; k <= arrangementNodeDonors; k++) {
							reducedDonorBloodTypes[i][k] = matchRunNodeVector[donorNodeID]->getDonor(k-1)->getBT();
						}
					}

					for (int l = 1; l <= numberOfEdgesInDonorSubset; l++) {

						int edgeSubsetDonorNodeIndex = edgeSubsetDonorNodeIndices[l];
						int edgeSubsetCandidateNodeIndex = edgeSubsetCandidateIndices[l];
						int edgeSubsetDonorID = edgeSubsetDonorIDs[l];

						int edgeSubsetDonorNodeID = arrangement[edgeSubsetDonorNodeIndex - 1];
						int edgeSubsetCandidateNodeID = arrangement[edgeSubsetCandidateNodeIndex - 1];

						if (edgeFlags[l] != 0) {

							probEdgeSubset = probEdgeSubset * matchRunSuccessProbabilitiesMatrix[edgeSubsetDonorNodeID][edgeSubsetCandidateNodeID][edgeSubsetDonorID];

							reducedDonorIncidenceMatrix[edgeSubsetDonorNodeIndex][edgeSubsetCandidateNodeIndex][edgeSubsetDonorID] = true;
							reducedIncidenceMatrix[edgeSubsetDonorNodeIndex][edgeSubsetCandidateNodeIndex] = true;
							reducedUtilityMatrix[edgeSubsetDonorNodeIndex][edgeSubsetCandidateNodeIndex][edgeSubsetDonorID] = matchRunUtilityMatrix[edgeSubsetDonorNodeID][edgeSubsetCandidateNodeID][edgeSubsetDonorID];

							if (addAdvantageToHighPRACandidates && matchRunNodeTypeVector[edgeSubsetCandidateNodeID] == PAIR && matchRunNodeVector[edgeSubsetCandidateNodeID]->getCandidate()->getPRA() >= praAdvantageCutoff) {
								reducedUtilityMatrix[edgeSubsetDonorNodeIndex + 1][edgeSubsetCandidateNodeIndex + 1][edgeSubsetDonorID] += praAdvantageValue;
							}
						}
						else {
							probEdgeSubset = probEdgeSubset * (1 - matchRunSuccessProbabilitiesMatrix[edgeSubsetDonorNodeID][edgeSubsetCandidateNodeID][edgeSubsetDonorID]);
						}
					}


					if (probEdgeSubset > 0) {

						double addUtil = calculatePartialUtility(N, reducedIncidenceMatrix, reducedUtilityMatrix, reducedNodeTypeVector, reducedDonorBloodTypes);

						if (addUtil > 0) {
							utility += probEdgeSubset*addUtil;
						}
					}
				}
			}
		}
	}

	return utility;
}

double KPDGUIMatchRun::estimateExpectedUtility(std::vector<int> &arrangement) {

	int N = (int)arrangement.size();

	double expUtility = 0;

	QTime t;
	t.start();

	for (int sims = 1; sims <= numberOfExpectedUtilityIterations; sims++) {

		//Initialize random matrices
		std::vector<std::vector<bool> > randomIncidenceMatrix(1 + N, std::vector<bool>(1 + N, false));
		std::vector<std::vector<std::vector<bool> > > randomDonorIncidenceMatrix(1 + N, std::vector<std::vector<bool> >(1 + N, std::vector<bool>(1, false)));
		std::vector<std::vector<std::vector<double> > > randomUtilityMatrix(1 + N, std::vector<std::vector<double> >(1 + N, std::vector<double>(1, 0.0)));

		std::vector<bool> randomCandidateAvailabilityVector(1 + N, false);
		std::vector<std::vector<bool> > randomDonorAvailabilityVector(1 + N, std::vector<bool>(1, false));

		std::vector<KPDNodeType> subNodeTypeVector(1 + N, PAIR);
		std::vector<std::vector<KPDBloodType> > subDonorBloodTypeVector(1 + N, std::vector<KPDBloodType>(1, BT_AB));

		int i = 1;

		//Simulate candidate and donor availabilities, retrive donor information
		for (std::vector<int>::iterator itNodes = arrangement.begin(); itNodes != arrangement.end(); ++itNodes, i++) {

			//Store node type
			subNodeTypeVector[i] = matchRunNodeTypeVector[*itNodes];

			//Randomly generate donor availability (and store donor blood types)
			int numDonors = matchRunNodeVector[*itNodes]->getNumberOfDonors();

			randomDonorAvailabilityVector[i].assign(1 + numDonors, false);
			subDonorBloodTypeVector[i].assign(1 + numDonors, BT_AB);

			for (int k = 1; k <= numDonors; k++) {

				if (KPDFunctions::getRandomValue(t.elapsed()) < (1 - matchRunNodeVector[*itNodes]->getDonor(k-1)->getFailureProbability())) {
					randomDonorAvailabilityVector[i][k] = true;

					if (matchRunNodeTypeVector[*itNodes] != PAIR) { // Add marker for NDD availability (acts as a shortcut for the next section)
						randomCandidateAvailabilityVector[i] = true;
					}

				}
				subDonorBloodTypeVector[i][k] = matchRunNodeVector[*itNodes]->getDonor(k-1)->getBT();
			}

			//Randomly generate candidate availability for PAIRs
			if (matchRunNodeTypeVector[*itNodes] == PAIR) {
				if (KPDFunctions::getRandomValue(t.elapsed()) < (1 - matchRunNodeVector[*itNodes]->getCandidate()->getFailureProbability())) {
					randomCandidateAvailabilityVector[i] = true;
				}
			}
		}

		//Iterate through donor-candidate combinations and randomly generate realized transplants
		int j = 1;
		i = 1;

		for (std::vector<int>::iterator itDonors = arrangement.begin(); itDonors != arrangement.end(); ++itDonors, i++) {

			int numDonors = matchRunNodeVector[*itDonors]->getNumberOfDonors();

			for (std::vector<int>::iterator itCandidates = arrangement.begin(); itCandidates != arrangement.end(); ++itCandidates, j++) {

				randomDonorIncidenceMatrix[i][j].assign(1 + numDonors, 0);
				randomUtilityMatrix[i][j].assign(1 + numDonors, 0.0);

				if (i != j) {

					//If both nodes are available
					if (randomCandidateAvailabilityVector[i] && randomCandidateAvailabilityVector[j]) {

						//If donor node is a PAIR and candidate node is a NDD or BRIDGE_DONOR, 
						//insert implicit backward edges from all available donors toward the NDD/BRIDGE node, and set the incidence matrix to true
						if (subNodeTypeVector[i] == PAIR && subNodeTypeVector[j] != PAIR) {
							for (int k = 1; k <= numDonors; k++) {
								if (randomDonorAvailabilityVector[i][k]) {
									randomDonorIncidenceMatrix[i][j][k] = true;
									randomIncidenceMatrix[i][j] = true;
								}
							}
						}
						//If candidate node is a PAIR, generate random matches
						else if (subNodeTypeVector[j] == PAIR) {

							//Iterate through donors
							for (int k = 1; k <= numDonors; k++) {
								// For existing original matches, and for donors that are available, randomly generate matches
								if (matchRunDonorIncidenceMatrix[*itDonors][*itCandidates][k] && randomDonorAvailabilityVector[i][k]) {

									if (KPDFunctions::getRandomValue(t.elapsed()) < matchRunSuccessProbabilitiesMatrix[*itDonors][*itCandidates][k]) {
										randomDonorIncidenceMatrix[i][j][k] = 1;
										randomUtilityMatrix[i][j][k] = matchRunUtilityMatrix[*itDonors][*itCandidates][k];

										if (addAdvantageToHighPRACandidates && matchRunNodeVector[*itCandidates]->getCandidate()->getPRA() >= praAdvantageCutoff && matchRunNodeTypeVector[*itCandidates] == PAIR) {
											randomUtilityMatrix[i][j][k] += praAdvantageValue;
										}

										// Set incidence matrix to true
										randomIncidenceMatrix[i][j] = true;
									}
								}
							}
						}
					}
				}
			}

			j = 1;
		}

		//After generating matrices, calculate utility
		double partialUtil = calculatePartialUtility(N, randomIncidenceMatrix, randomUtilityMatrix, subNodeTypeVector, subDonorBloodTypeVector);
		expUtility += partialUtil;
	}

	//Expected utility is the average of the calculated utility values over the number of iterations
	return expUtility / numberOfExpectedUtilityIterations;
}


double KPDGUIMatchRun::calculatePartialUtility(int nV, std::vector<std::vector<bool> > &incidence, std::vector<std::vector<std::vector<double> > > &utility, 
	std::vector<KPDNodeType> & nodeTypes, std::vector<std::vector<KPDBloodType> > & donorBloodTypes) {

	std::vector<std::vector<int> > possibleCyclesOrChains;
	std::vector<double> utilityOfPossibleCyclesOrChains;

	int maximum = std::max(maxChainLength + 1, maxCycleSize);

	double utilityValue = 0;

	int start = 1;
	std::vector<int> visitedVec(nV + 1, 0);
	std::vector<int> stack_vec;

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
					int multipleNDDCheck = 0;
					int index = 0;

					std::vector<int> potentialCycleOrChain;

					for (unsigned i = 0; i < stack_vec.size(); i++) {
						potentialCycleOrChain.push_back(stack_vec[i]);
						if (nodeTypes[stack_vec[i]] != PAIR) {
							multipleNDDCheck++;
							index = i;
						}
					}

					double tempUtil = 0;

					if (multipleNDDCheck == 1 && (int)potentialCycleOrChain.size() <= maxChainLength + 1) {

						while (index > 0) {
							int tempVec = *(potentialCycleOrChain.begin());
							potentialCycleOrChain.erase(potentialCycleOrChain.begin());
							potentialCycleOrChain.push_back(tempVec);
							index--;
						}

						if (!allowABBridgeDonors) {
							bool nonABBridgeDonor = false;
							for (int k = 1; k < (int)donorBloodTypes[*(potentialCycleOrChain.end() - 1)].size(); k++) {
								if (donorBloodTypes[*(potentialCycleOrChain.end() - 1)][k] != BT_AB) {
									nonABBridgeDonor = true;
								}
							}

							if (nonABBridgeDonor) {
								for (std::vector<int>::iterator it = potentialCycleOrChain.begin(); it != potentialCycleOrChain.end() - 1; it++) {
									double selectedDonorUtility = 0;

									for (int k = 1; k < (int)utility[*it][*(it + 1)].size(); k++) {
										if (utility[*it][*(it + 1)][k] > selectedDonorUtility) {
											selectedDonorUtility = utility[*it][*(it + 1)][k];
										}
									}
									tempUtil += selectedDonorUtility;
								}

								possibleCyclesOrChains.push_back(std::vector<int>(potentialCycleOrChain));
								utilityOfPossibleCyclesOrChains.push_back(tempUtil);

							}
						}
						else {
							for (std::vector<int>::iterator it = potentialCycleOrChain.begin(); it != potentialCycleOrChain.end() - 1; it++) {
								double selectedDonorUtility = 0;

								for (int k = 1; k < (int)utility[*it][*(it + 1)].size(); k++) {
									if (utility[*it][*(it + 1)][k] > selectedDonorUtility) {
										selectedDonorUtility = utility[*it][*(it + 1)][k];
									}
								}
								tempUtil += selectedDonorUtility;
							}

							possibleCyclesOrChains.push_back(std::vector<int>(potentialCycleOrChain));
							utilityOfPossibleCyclesOrChains.push_back(tempUtil);
						}
					}

					else if ((int)potentialCycleOrChain.size() <= maxCycleSize) {

						for (std::vector<int>::iterator it = potentialCycleOrChain.begin(); it != potentialCycleOrChain.end() - 1; it++) {
							double selectedDonorUtility = 0;

							for (int k = 1; k < (int)utility[*it][*(it + 1)].size(); k++) {
								if (utility[*it][*(it + 1)][k] > selectedDonorUtility) {
									selectedDonorUtility = utility[*it][*(it + 1)][k];
								}
							}
							tempUtil += selectedDonorUtility;
						}

						double selectedDonorUtility = 0;

						for (int k = 1; k < (int)utility[*(potentialCycleOrChain.end() - 1)][*(potentialCycleOrChain.begin())].size(); k++) {
							if (utility[*(potentialCycleOrChain.end() - 1)][*(potentialCycleOrChain.begin())][k] > selectedDonorUtility) {
								selectedDonorUtility = utility[*(potentialCycleOrChain.end() - 1)][*(potentialCycleOrChain.begin())][k];
							}
						}
						tempUtil += selectedDonorUtility;

						possibleCyclesOrChains.push_back(std::vector<int>(potentialCycleOrChain));
						utilityOfPossibleCyclesOrChains.push_back(tempUtil);

					}
				}

				if ((int)stack_vec.size() >= maximum)
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

			std::vector<int> cycleFlags(1 + nPossibleCycles, 0);

			int numberOfCyclesInPossibleSolutions = KPDFunctions::setFlags(c, cycleFlags);

			std::vector<int> checkUniqueness(nV + 1, 0);
			bool validSolution = true;
			for (int q = 0; q < nPossibleCycles; q++) {
				if (cycleFlags[q + 1] == 1) {
					tempU += utilityOfPossibleCyclesOrChains[q];
					for (std::vector<int>::iterator it = possibleCyclesOrChains.at(q).begin(); it != possibleCyclesOrChains.at(q).end(); ++it) {
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

QVector<QVector<KPDGUINode *> > KPDGUIMatchRun::getMatchRunArrangementNodes() {

	QVector<QVector<KPDGUINode *> > arrangements;

	for (std::vector<std::vector<int> >::iterator arrangementIt = matchRunArrangements.begin(); arrangementIt != matchRunArrangements.end(); arrangementIt++) {

		QVector<KPDGUINode *> newArrangement;

		for (std::vector<int>::iterator nodeIt = arrangementIt->begin(); nodeIt != arrangementIt->end(); nodeIt++) {

			newArrangement << matchRunNodeVector[*nodeIt];
		}

		arrangements << newArrangement;
	}

	return arrangements;

}

QVector<QVector<KPDGUIMatch *> > KPDGUIMatchRun::getMatchRunArrangementMatches() {

	QVector<QVector<KPDGUIMatch *> > arrangementMatchLists;

	int i = 1;
	for (std::vector<std::vector<int> >::iterator arrangementIt = matchRunArrangements.begin(); arrangementIt != matchRunArrangements.end(); arrangementIt++) {

		QVector<KPDGUIMatch *> arrangementMatches;

		bool arrangementHasNDD = matchRunArrangementHasNDD[i - 1];

		std::vector<int> arrangementNodeList = *arrangementIt;

		if (optScheme == CYCLES_AND_CHAINS) {

			for (int j = 0; j < arrangementNodeList.size() - 1; j++) {

				KPDGUINode * firstNode = matchRunNodeVector[arrangementNodeList[j] ];
				KPDGUINode * secondNode = matchRunNodeVector[arrangementNodeList[j + 1] ];

				QVector<KPDGUIDonor *> donors = firstNode->getDonors();

				foreach(KPDGUIDonor * donor, donors) {
					KPDGUIMatch * match = donor->findMatchingCandidate(secondNode->getCandidate());
					if (match != NULL) {
						if (match->getInclude()) {
							arrangementMatches << match;
						}
					}
				}
			}

			// Final match for cycles
			if (!arrangementHasNDD) {

				KPDGUINode * firstNode = matchRunNodeVector[arrangementNodeList.back()];
				KPDGUINode * secondNode = matchRunNodeVector[arrangementNodeList.front()];

				QVector<KPDGUIDonor *> donors = firstNode->getDonors();

				foreach(KPDGUIDonor * donor, donors) {
					KPDGUIMatch * match = donor->findMatchingCandidate(secondNode->getCandidate());
					if (match != NULL) {
						if (match->getInclude()) {
							arrangementMatches << match;
						}
					}
				}
			}
		}

		else {

			for (int j = 0; j < arrangementNodeList.size(); j++) {
				KPDGUINode * firstNode = matchRunNodeVector[arrangementNodeList[j]];
				QVector<KPDGUIDonor *> donors = firstNode->getDonors();

				for (int k = 0; k < arrangementNodeList.size(); k++) {
					if (j != k) {
						KPDGUINode * secondNode = matchRunNodeVector[arrangementNodeList[k]];

						foreach(KPDGUIDonor * donor, donors) {
							KPDGUIMatch * match = donor->findMatchingCandidate(secondNode->getCandidate());
							if (match != NULL) {
								if (match->getInclude()) {
									arrangementMatches << match;
								}
							}
						}
					}
				}
			}
		}

		arrangementMatchLists.push_back(arrangementMatches);

		i++;
	}

	return arrangementMatchLists;
	
}

QVector<double> KPDGUIMatchRun::getAssignedValueOfMatchRunArrangements() {

	QVector<double> values;

	for (std::vector<double>::iterator arrangementIt = assignedValueOfMatchRunArrangements.begin(); arrangementIt != assignedValueOfMatchRunArrangements.end(); arrangementIt++) {
		values << *arrangementIt;
	}

	return values;

}

QVector<QVector<int> > KPDGUIMatchRun::getMatchRunSelectedSolutions() {

	QVector<QVector<int> > solutions;

	for (std::vector<std::vector<int> >::iterator solutionIt = matchRunSelectedSolutions.begin(); solutionIt != matchRunSelectedSolutions.end(); solutionIt++) {

		QVector<int> newSolution;

		for (std::vector<int>::iterator arrangementIt = solutionIt->begin(); arrangementIt != solutionIt->end(); arrangementIt++) {

			newSolution << *arrangementIt;

		}

		solutions << newSolution;
	}

	return solutions;

}

QVector<double> KPDGUIMatchRun::getAssignedValueOfMatchRunSolutions() {

	QVector<double> values;

	for (std::vector<double>::iterator solutionIt = assignedValueOfMatchRunSolutions.begin(); solutionIt != assignedValueOfMatchRunSolutions.end(); solutionIt++) {
		values << *solutionIt;
	}

	return values;

}

QString KPDGUIMatchRun::printLog() {
	return matchRunLog;
}




