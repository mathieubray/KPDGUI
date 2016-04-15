#include "KPDGUIRecord.h"

KPDGUIRecord::KPDGUIRecord()
{
	baselineID = 1;

	loadDictionary();
	loadSurvivalParameters();
}

KPDGUIRecord::~KPDGUIRecord(){

}

int KPDGUIRecord::getBaselineIDCode() {
	return baselineID;
}

void KPDGUIRecord::setBaselineIDCode(int code) {
	baselineID = code;
}

void KPDGUIRecord::insertNode(KPDGUINode * node, bool fromSavedFile) {

	if (!fromSavedFile) {
		node->setNodeID(baselineID);
		baselineID++;
	}

	nodes.insert(node->getNodeID(), node);
}

void KPDGUIRecord::insertMatch(KPDGUIMatch * arrow) {

	int fromID = arrow->getFromNode()->getNodeID();
	fromMatches.insert(fromID, arrow);

	int toID = arrow->getToNode()->getNodeID();
	toMatches.insert(toID, arrow);
}



KPDGUINode * KPDGUIRecord::getNode(int nodeID){
	if (nodes.keys().contains(nodeID)){
		return nodes[nodeID];
	}
	else {
		return NULL;
	}
}

KPDGUINode * KPDGUIRecord::getNodeFromIndex(int i){
	QList<int> idList = nodes.keys();
	int id = idList.at(i);
	return nodes[id];
}

int KPDGUIRecord::getNumberOfNodes(){
	return nodes.size();
}

int KPDGUIRecord::getNumberOfAvailableNodes() {
	return availableNodes.size();
}

QList<KPDGUINode *> KPDGUIRecord::getNodes(){
	return nodes.values();
}



// Generate master matrices for selected nodes
void KPDGUIRecord::generateMatrices(KPDGUISimParameters * params, QProgressDialog * progress){

	clearMatrices();

	//Parameters
	//double defaultDonorFailureRate = params->getDefaultDonorFailureRate();
	//double defaultCandidateFailureRate = params->getDefaultCandidateFailureRate();
	//double defaultADFailureRate = params->getDefaultADFailureRate();
	double exogenousFailureRate = params->getExogenousFailureRate();
	bool reserveODonorsForOCandidates = params->getReserveODonorsForOCandidates();
	bool checkAdditionalHLA = params->getCheckAdditionalHLA();
		
	//QVector<KPDGUINode *> availableNodes;
	availableNodes.clear();

	foreach(KPDGUINode * node, nodes.values()){
		if (!node->getNodeStatus()){
			availableNodes.push_back(node);
		}
	}

	int N = availableNodes.size();

	//progress->setRange(0, nNodes + nNodes*nNodes);
	//progress->setValue(0);
	//int progressBarValue = 0;
	
	incidenceMatrix.assign(1 + N, std::vector<bool>(1 + N, false));
	associatedDonorMatrix.assign(1 + N, std::vector<std::vector<int> >(1 + N, std::vector<int>(1, 0)));
	associatedScoresMatrix.assign(1 + N, std::vector<std::vector<double> >(1 + N, std::vector<double>(1, 0.0)));
	associated5YearSurvivalMatrix.assign(1 + N, std::vector<std::vector<double> >(1 + N, std::vector<double>(1, 0.0)));
	associated10YearSurvivalMatrix.assign(1 + N, std::vector<std::vector<double> >(1 + N, std::vector<double>(1, 0.0)));
	associatedProbabilitiesMatrix.assign(1 + N, std::vector<std::vector<double> >(1 + N, std::vector<double>(1, 0.0)));
	
	AdditionalNodeInfo p;
	nodeInfoVector.assign(1 + N, p);
	
	for (int i = 1; i <= N; i++){

		KPDGUINode * currentNode = availableNodes.at(i - 1);
		int numberOfDonors = currentNode->getNumberOfDonors();

		//Node ID
		nodeInfoVector[i].nodeID = currentNode->getNodeID();
		
		//For ADs
		if (currentNode->getNodeType() == AD){ 
			KPDGUIDonorInfo * ad = currentNode->getDonor(0);

			nodeInfoVector[i].nodeType = AD;

			nodeInfoVector[i].donorBTs.push_back(ad->getBT());
			nodeInfoVector[i].donorUncertainty.push_back(1 - ad->getFailureProbability()); 
		}

		//For Pairs
		else {
			KPDGUICandidateInfo * candidate = currentNode->getCandidate();

			nodeInfoVector[i].nodeType = PAIR;
			
			//Candidate Blood Type and PRA
			nodeInfoVector[i].candidateBT = candidate->getBT();
			nodeInfoVector[i].candidatePRA = candidate->getPRA();
			nodeInfoVector[i].candidateUncertainty = 1 - candidate->getFailureProbability();
			
			//Donor Blood Types and PRA
			for (int k = 1; k <= numberOfDonors; k++) {
				KPDGUIDonorInfo * donor = currentNode->getDonor(k - 1);

				nodeInfoVector[i].donorBTs.push_back(donor->getBT());
				nodeInfoVector[i].donorUncertainty.push_back(1 - donor->getFailureProbability());
			}
		}
		
		//progressBarValue++;
		//progress->setValue(progressBarValue);
		//QApplication::processEvents();
	}

	for (int i = 1; i <= N; i++){

		KPDGUINode * donorNode = availableNodes.at(i - 1);
		int numberOfDonors = donorNode->getNumberOfDonors();

		for (int j = 1; j <= N; j++){

			associatedDonorMatrix[i][j].assign(1 + numberOfDonors, 0);
			associatedScoresMatrix[i][j].assign(1 + numberOfDonors, 0.0);
			associated5YearSurvivalMatrix[i][j].assign(1 + numberOfDonors, 0.0);
			associated10YearSurvivalMatrix[i][j].assign(1 + numberOfDonors, 0.0);
			associatedProbabilitiesMatrix[i][j].assign(1 + numberOfDonors, 0.0);

			if (i != j) {
				KPDGUINode * candidateNode = availableNodes.at(j - 1);
				
				// Pairing -> AD (Implicit Backward Edge from all Donors to the AD)
				if (donorNode->getNodeType() == PAIR && candidateNode->getNodeType() == AD){
					incidenceMatrix[i][j] = true;

					for (int k = 1; k <= numberOfDonors; k++) {
						associatedDonorMatrix[i][j][k] = 1;
						associatedProbabilitiesMatrix[i][j][k] = 1.0;
					}
				}
				// Pairing
				else if (candidateNode->getNodeType() == PAIR)  {
					
					KPDGUICandidateInfo * candidate = candidateNode->getCandidate();
					double pra = candidate->getPRA();

					for (int k = 1; k <= numberOfDonors; k++) {

						KPDGUIDonorInfo * donor = donorNode->getDonor(k - 1);						
						
						if (isMatch(donor, candidate, reserveODonorsForOCandidates, checkAdditionalHLA)) {

							incidenceMatrix[i][j] = true;
							associatedDonorMatrix[i][j][k] = 1;

							if (pra == 100 || candidateNode->getCandidate()->getHLA().size() >= 10 || candidateNode->getCandidate()->getBT() == BT_AB) {
								associatedScoresMatrix[i][j][k] = 1;
							}
							else {
								associatedScoresMatrix[i][j][k] = 0.0001;
							}
							associated5YearSurvivalMatrix[i][j][k] = calculateSurvival(donor, candidateNode->getCandidate(), 1);
							associated10YearSurvivalMatrix[i][j][k] = calculateSurvival(donor, candidateNode->getCandidate(), 0);
							associatedProbabilitiesMatrix[i][j][k] = 0.95;
						}
					}
				}
			}

			//progressBarValue++;
			//progress->setValue(progressBarValue);
			//QApplication::processEvents();
		}		
	}

	recordLog = "Available Nodes for Match Run: ";

	int nPairs = 0;
	int nADs = 0;

	foreach(KPDGUINode * node, availableNodes){
		recordLog.append(QString::number(node->getNodeID()) + " ");

		if (node->getNodeType() == AD){
			nADs++;
		}
		else {
			nPairs++;
		}
	}
	recordLog.append("(" + QString::number(nADs) + " ADs, " + QString::number(nPairs) + " Nodes)\n");
}

std::vector<std::vector<bool> > KPDGUIRecord::getIncidenceMatrix() {
	std::vector<std::vector<bool> > incidenceMatrixClone(incidenceMatrix);

	return incidenceMatrixClone;
}

std::vector<std::vector<std::vector<int> > > KPDGUIRecord::getAssociatedDonorMatrix() {
	std::vector<std::vector<std::vector<int> > > associatedDonorsMatrixClone(associatedDonorMatrix);
	//Already offset

	return associatedDonorsMatrixClone;
}
std::vector<std::vector<std::vector<double> > > KPDGUIRecord::getAssociatedScoresMatrix() {
	std::vector<std::vector<std::vector<double> > > associatedScoresMatrixClone(associatedScoresMatrix);
	//Already offset

	return associatedScoresMatrixClone;
}

std::vector<std::vector<std::vector<double> > > KPDGUIRecord::getAssociated5YearSurvivalMatrix() {
	std::vector<std::vector<std::vector<double> > > associated5YearSurvivalMatrixClone(associated5YearSurvivalMatrix);
	//Already offset

	return associated5YearSurvivalMatrixClone;
}

std::vector<std::vector<std::vector<double> > > KPDGUIRecord::getAssociated10YearSurvivalMatrix() {
	std::vector<std::vector<std::vector<double> > > associated10YearSurvivalMatrixClone(associated10YearSurvivalMatrix);
	//Already offset

	return associated10YearSurvivalMatrixClone;
}

std::vector<std::vector<std::vector<double> > > KPDGUIRecord::getAssociatedProbabilitiesMatrix() {
	std::vector<std::vector<std::vector<double> > > associatedProbabilitiesMatrixClone(associatedProbabilitiesMatrix);
	//Already offset

	return associatedProbabilitiesMatrixClone;
}

std::vector<AdditionalNodeInfo> KPDGUIRecord::getNodeInfoVector() {
	std::vector<AdditionalNodeInfo> nodeInfoVectorClone(nodeInfoVector);

	return nodeInfoVectorClone;
}

/*void KPDGUIRecord::deleteNodeFromRecord(int id){
	nodes.remove(id);	
}*/

void KPDGUIRecord::loadDictionary(){

	QVector<QVector<QVector<QString> > > dictionaryData;

	QFile iFile("data/dictionary.csv");
	if (!iFile.open(QIODevice::ReadOnly)){
		std::cerr << "Cannot Open File For Reading: " << qPrintable(iFile.errorString()) << std::endl;
	}
	QTextStream fileStream(&iFile);

	int i = 0;
	while (!fileStream.atEnd()){
		QString line = fileStream.readLine();
		QStringList lineStream = line.split(',');

		if (i >= 0){
			QVector<QVector<QString> > row;
			int flag = 1;
			QVector<QString> field;

			foreach(QString token, lineStream){
				if (token.length() == 0 && flag == 1){
					field.push_back("NULL");
					row.push_back(field);
					field.clear();
				}

				else if (token.indexOf("\"") == 0){ //if equal to \";
					field.push_back(token.remove(0, 1));
					flag = 0;
				}

				else if (flag == 1){
					field.push_back(token);
					row.push_back(field);
					field.clear();
				}

				else{
					if (token.length()>0){
						if (token.indexOf("\"") == token.length() - 1){ //if equal to \";
							field.push_back(token.remove(token.length() - 1, 1));
							row.push_back(field);
							field.clear();
							flag = 1;
						}

						else {
							field.push_back(token);
						}
					}
				}
			}
			dictionaryData.push_back(row);
		}
		i++;
	}

	foreach(QVector<QVector<QString> > equivalencies, dictionaryData){
		QString antigen = equivalencies.at(0).at(0);
		QVector<QString> equivalency_list = equivalencies.at(1);
		hlaDictionary.insert(antigen, equivalency_list);
	}
}

void KPDGUIRecord::loadSurvivalParameters() {

	QVector<QVector<QVector<QString> > > survivalData;

	QFile iFile("data/parameters.csv");
	if (!iFile.open(QIODevice::ReadOnly)) {
		std::cerr << "Cannot Open File For Reading: " << qPrintable(iFile.errorString()) << std::endl;
	}
	QTextStream fileStream(&iFile);

	int i = 0;
	while (!fileStream.atEnd()) {
		QString line = fileStream.readLine();
		QStringList lineStream = line.split(',');

		if (i >= 0) {
			QVector<QVector<QString> > row;
			int flag = 1;
			QVector<QString> field;

			foreach(QString token, lineStream) {
				if (token.length() == 0 && flag == 1) {
					field.push_back("NULL");
					row.push_back(field);
					field.clear();
				}

				else if (token.indexOf("\"") == 0) { //if equal to \";
					field.push_back(token.remove(0, 1));
					flag = 0;
				}

				else if (flag == 1) {
					field.push_back(token);
					row.push_back(field);
					field.clear();
				}

				else {
					if (token.length()>0) {
						if (token.indexOf("\"") == token.length() - 1) { //if equal to \";
							field.push_back(token.remove(token.length() - 1, 1));
							row.push_back(field);
							field.clear();
							flag = 1;
						}

						else {
							field.push_back(token);
						}
					}
				}
			}
			survivalData.push_back(row);
		}
		i++;
	}

	foreach(QVector<QVector<QString> > dataRow, survivalData) {

		if (dataRow.at(0).at(0) == "recipAge") {
			survivalParameters["recipAge5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["recipAge10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "donorAge") {
			survivalParameters["donorAge5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["donorAge10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "pairGender") {
			survivalParameters["pairGender5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["pairGender10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "recipRace") {
			survivalParameters["recipRace5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["recipRace10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "pairHLA") {
			survivalParameters["pairHLA5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["pairHLA10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "recipPRA") {
			survivalParameters["recipPRA5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["recipPRA10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "recipDiabetes") {
			survivalParameters["recipDiabetes5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["recipDiabetes10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "recipPrevTrans") {
			survivalParameters["recipPrevTrans5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["recipPrevTrans10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "recipBMI") {
			survivalParameters["recipBMI5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["recipBMI10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "donorBMI") {
			survivalParameters["donorBMI5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["donorBMI10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "recipTOD") {
			survivalParameters["recipTOD5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["recipTOD10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "pairWeightRatio") {
			survivalParameters["pairWeightRatio5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["pairWeightRatio10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "recipHepC") {
			survivalParameters["recipHepC5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["recipHepC10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
		else if (dataRow.at(0).at(0) == "baseline") {
			survivalParameters["baseline5yr"].push_back(dataRow.at(2).at(0).toDouble());
			survivalParameters["baseline10yr"].push_back(dataRow.at(3).at(0).toDouble());
		}
	}
	
	recordLog.append("Survival Parameters Set\n");
}

void KPDGUIRecord::clearMatrices(){
	
	incidenceMatrix.clear();
	associatedDonorMatrix.clear();
	associatedScoresMatrix.clear();
	associated5YearSurvivalMatrix.clear();
	associated10YearSurvivalMatrix.clear();
	associatedProbabilitiesMatrix.clear();
	nodeInfoVector.clear();
}

void KPDGUIRecord::clearRecord() {
	nodes.clear();
	fromMatches.clear();
	toMatches.clear();
}

//Checks for a match between donor and candidate
bool KPDGUIRecord::isMatch(KPDGUIDonorInfo * donor, KPDGUICandidateInfo * candidate, bool reserveOtoO, bool checkAdditionalHLA){

	if (donor->getBT() != BT_AB && donor->getBT() != BT_B && donor->getBT() != BT_A && donor->getBT() != BT_O){
		return false;
	}

	if (candidate->getBT() != BT_AB && candidate->getBT() != BT_B && candidate->getBT() != BT_A && candidate->getBT() != BT_O){
		return false;
	}

	//Check Exclusion
	//if (candidate->getExcludedDonors().contains(donorID)){
		//return false;
	//}

	//Check BT match;
	if (donor->getBT() == BT_AB){
		if (candidate->getBT() != BT_AB){
			return false;
		}
	}
	else if (donor->getBT() == BT_A){
		if (candidate->getBT() == BT_O || candidate->getBT() == BT_B){
			return false;
		}
	}
	else if (donor->getBT() == BT_B){
		if (candidate->getBT() == BT_O || candidate->getBT() == BT_A){
			return false;
		}
	}

	if (reserveOtoO){
		if (donor->getBT() == BT_O){
			if (candidate->getBT() != BT_O){
				return false;
			}
		}
	}

	foreach(QString antibody, candidate->getHLA()){

		if (hlaDictionary.contains(antibody)){

			foreach(QString equivalentAntibody, hlaDictionary[antibody]){
				if (antibody.mid(0, 1) == "A"){
					foreach(QString antigen, donor->getA()){
						if (antigen == equivalentAntibody){
							return false;
						}
					}
				}

				if (antibody.mid(0, 1) == "B"){

					if (antibody.mid(0, 1) == "W"){
						if (equivalentAntibody == "BW4"){
							if (donor->getBW4() == true){
								return false;
							}
						}
						if (equivalentAntibody == "BW6"){
							if (donor->getBW6() == true){
								return false;
							}
						}
					}

					else {
						foreach(QString antigen, donor->getB()){
							if (antigen == equivalentAntibody){
								return false;
							}
						}
					}
				}

				if (antibody.mid(0, 1) == "C"){
					foreach(QString antigen, donor->getCW()){
						if (antigen == equivalentAntibody){
							return false;
						}
					}
				}

				if (antibody.mid(0, 1) == "D"){

					if (equivalentAntibody == "DR51"){
						if (donor->getDR51() == true){
							return false;
						}
					}
					if (equivalentAntibody == "DR52"){
						if (donor->getDR52() == true){
							return false;
						}
					}
					if (equivalentAntibody == "DR53"){
						if (donor->getDR53() == true){
							return false;
						}
					}

					foreach(QString antigen, donor->getDR()){
						if (antigen == equivalentAntibody){
							return false;
						}
					}

					foreach(QString antigen, donor->getDQ()){
						if (antigen == equivalentAntibody){
							return false;
						}
					}
				}
			}
		}

		if (checkAdditionalHLA){
			foreach(QString antigen, donor->getAdditionalHLA()){
				if (antigen == antibody){
					return false;
				}
			}
		}
	}

	return true;
}

bool KPDGUIRecord::isMatch(KPDGUINode * donorNode, KPDGUINode * candidateNode, int donor, bool reserveOtoO, bool checkAdditionalHLA)
{
	return isMatch(donorNode->getDonor(donor), candidateNode->getCandidate(), reserveOtoO, checkAdditionalHLA);
}

double KPDGUIRecord::calculateSurvival(KPDGUIDonorInfo * donor, KPDGUICandidateInfo * candidate, int fiveyear) {
	double survival = 0.0;

	//Age
	QVector<double> cAge5yr = survivalParameters["recipAge5yr"];
	QVector<double> cAge10yr = survivalParameters["recipAge10yr"];

	int candidatesAge = candidate->getAge();
	survival += candidatesAge*(fiveyear*(cAge5yr[0]) + (1 - fiveyear)*(cAge10yr[0]));
	candidatesAge = candidatesAge - 35;
	if (candidatesAge>0) {
		survival += candidatesAge*(fiveyear*(cAge5yr[1]) + (1 - fiveyear)*(cAge10yr[1]));
	}
	candidatesAge = candidatesAge - 15;
	if (candidatesAge>0) {
		survival += candidatesAge*(fiveyear*(cAge5yr[2]) + (1 - fiveyear)*(cAge10yr[2]));
	}
	candidatesAge = candidatesAge - 15;
	if (candidatesAge>0) {
		survival += candidatesAge*(fiveyear*(cAge5yr[3]) + (1 - fiveyear)*(cAge10yr[3]));
	}

	QVector<double> dAge5yr = survivalParameters["donorAge5yr"];
	QVector<double> dAge10yr = survivalParameters["donorAge10yr"];

	int donorsAge = donor->getAge();
	survival += donorsAge*(fiveyear*(dAge5yr[0]) + (1 - fiveyear)*(dAge10yr[0]));
	donorsAge = donorsAge - 50;
	if (donorsAge>50) {
		survival += donorsAge*(fiveyear*(dAge5yr[1]) + (1 - fiveyear)*(dAge10yr[1]));
	}

	//Gender
	QVector<double> pGender5yr = survivalParameters["pairGender5yr"];
	QVector<double> pGender10yr = survivalParameters["pairGender10yr"];
	if (candidate->getMale() == false && donor->getMale() == false) {
		survival += fiveyear*(pGender5yr[0]) + (1 - fiveyear)*(pGender10yr[0]);
	}
	if (candidate->getMale() == false && donor->getMale()) {
		survival += fiveyear*(pGender5yr[1]) + (1 - fiveyear)*(pGender10yr[1]);
	}
	if (candidate->getMale() && donor->getMale()) {
		survival += fiveyear*(pGender5yr[2]) + (1 - fiveyear)*(pGender10yr[2]);
	}

	//Race
	QVector<double> cRace5yr = survivalParameters["recipRace5yr"];
	QVector<double> cRace10yr = survivalParameters["recipRace10yr"];
	if (candidate->getRace() == RACE_BLACK) {
		survival += fiveyear*(cRace5yr[0]) + (1 - fiveyear)*(cRace10yr[0]);
	}
	else if (candidate->getRace() == RACE_HISPANIC) {
		survival += fiveyear*(cRace5yr[1]) + (1 - fiveyear)*(cRace10yr[1]);
	}
	else if (candidate->getRace() == RACE_WHITE) {
		survival += fiveyear*(cRace5yr[2]) + (1 - fiveyear)*(cRace10yr[2]);
	}

	//HLA Mismatches
	double pNoMismatch5yr = survivalParameters["pairHLA5yr"][0];
	double pNoMismatch10yr = survivalParameters["pairHLA10yr"][0];
	survival += fiveyear*(pNoMismatch5yr)+(1 - fiveyear)*(pNoMismatch10yr);

	//PRA
	QVector<double> cPRA5yr = survivalParameters["recipPRA5yr"];
	QVector<double> cPRA10yr = survivalParameters["recipPRA10yr"];
	if (candidate->getPRA() >= 10 && candidate->getPRA() <= 79) {
		survival += fiveyear*(cPRA5yr[0]) + (1 - fiveyear)*(cPRA10yr[0]);
	}
	else if (candidate->getPRA() >= 80 && candidate->getPRA() <= 100) {
		survival += fiveyear*(cPRA5yr[1]) + (1 - fiveyear)*(cPRA10yr[1]);
	}

	//Recipient Diabetes Diagnosis
	double cDiabetes5yr = survivalParameters["recipDiabetes5yr"][0];
	double cDiabetes10yr = survivalParameters["recipDiabetes10yr"][0];
	if (candidate->getDiabetes()) {
		survival += fiveyear*(cDiabetes5yr)+(1 - fiveyear)*(cDiabetes10yr);
	}

	//Previous Tranpslant
	double cPrevTrans5yr = survivalParameters["recipPrevTrans5yr"][0];
	double cPrevTrans10yr = survivalParameters["recipPrevTrans10yr"][0];
	if (candidate->getPrevTrans()) {
		survival += fiveyear*(cPrevTrans5yr)+(1 - fiveyear)*(cPrevTrans10yr);
	}

	//BMI
	double cBMI5yr = survivalParameters["recipBMI5yr"][0];
	double cBMI10yr = survivalParameters["recipBMI10yr"][0];
	double dBMI5yr = survivalParameters["donorBMI5yr"][0];
	double dBMI10yr = survivalParameters["donorBMI10yr"][0];
	if (candidate->getBMI()>30) {
		survival += fiveyear*(cBMI5yr)+(1 - fiveyear)*(cBMI10yr);
	}
	if (donor->getBMI()>30) {
		survival += fiveyear*(dBMI5yr)+(1 - fiveyear)*(dBMI10yr);
	}

	//Time on Dialysis
	QVector<double> cTOD5yr = survivalParameters["recipTOD5yr"];
	QVector<double> cTOD10yr = survivalParameters["recipTOD10yr"];
	if (candidate->getTOD() == 0) {
		survival += fiveyear*(cTOD5yr[0]) + (1 - fiveyear)*(cTOD10yr[0]);
	}
	else if (candidate->getTOD()>0 && candidate->getTOD() <= 0.5) {
		survival += fiveyear*(cTOD5yr[1]) + (1 - fiveyear)*(cTOD10yr[1]);
	}
	else if (candidate->getTOD()>0.5 && candidate->getTOD() <= 1) {
		survival += fiveyear*(cTOD5yr[2]) + (1 - fiveyear)*(cTOD10yr[2]);
	}
	else if (candidate->getTOD()>2 && candidate->getTOD() <= 3) {
		survival += fiveyear*(cTOD5yr[3]) + (1 - fiveyear)*(cTOD10yr[3]);
	}
	else if (candidate->getTOD()>3) {
		survival += fiveyear*(cTOD5yr[4]) + (1 - fiveyear)*(cTOD10yr[4]);
	}

	//Weight Ratio
	double weightRatio = (donor->getWeight()) / (candidate->getWeight());
	QVector<double> pWR5yr = survivalParameters["pairWeightRatio5yr"];
	QVector<double> pWR10yr = survivalParameters["pairWeightRatio10yr"];

	if (weightRatio < 0.75) {
		survival += fiveyear*(pWR5yr[0]) + (1 - fiveyear)*(pWR10yr[0]);
	}
	else if (weightRatio >= 0.75 && weightRatio <0.90) {
		survival += fiveyear*(pWR5yr[1]) + (1 - fiveyear)*(pWR10yr[1]);
	}
	else if (weightRatio >= 1.15) {
		survival += fiveyear*(pWR5yr[2]) + (1 - fiveyear)*(pWR10yr[2]);
	}

	//Hep C Seriology
	double cHepC5yr = survivalParameters["recipHepC5yr"][0];
	double cHepC10yr = survivalParameters["recipHepC10yr"][0];
	if (candidate->getHepC()) {
		survival += fiveyear*(cHepC5yr)+(1 - fiveyear)*(cHepC10yr);
	}

	double expo = exp(survival);
	if (fiveyear == 1) {
		survival = pow(survivalParameters["baseline5yr"][0], expo);
	}
	else {
		survival = pow(survivalParameters["baseline10yr"][0], expo);
	}

	return survival;
}

double KPDGUIRecord::calculateSurvival(KPDGUINode *  donorNode, KPDGUINode * candidateNode, int donor, int fiveyear){

	return calculateSurvival(donorNode->getDonor(donor), candidateNode->getCandidate(), fiveyear);
	
}


QString KPDGUIRecord::getRecordLog(){
	return recordLog;
}
