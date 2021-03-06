


void KPDGUIRecord::insert(KPDGUINode * node, bool fromSavedFile){

	if (!fromSavedFile){
		node->setInternalID(id_code);
		id_code++;
	}

	pairs.insert(node->getInternalID(), node);
}

void KPDGUIRecord::insertArrow(KPDGUIArrow * arrow){
	arrows.insert(arrow);
}

KPDGUINode * KPDGUIRecord::getNode(int id){
	return pairs[id];
}

KPDGUINode * KPDGUIRecord::getNodeFromIndex(int i){
	QList<int> idList = pairs.keys();
	int id = idList.at(i);
	return pairs[id];
}

int KPDGUIRecord::size(){
	return pairs.size();
}

void KPDGUIRecord::clear(){
	pairs.clear();
	arrows.clear();
}

QList<KPDGUINode *> KPDGUIRecord::getPairs(){
	return pairs.values();
}

int KPDGUIRecord::getBaselineIDCode(){
	return id_code;
}

void KPDGUIRecord::setBaselineIDCode(int code){
	id_code = code;
}

// Generate master matrices for selected pairs
void KPDGUIRecord::generateMatrices(ParamInfoStruct params, QProgressDialog * progress){

	clearMatrices();

	//Parameters
	double pairFailureRate = params.pairFailureRate;
	double adFailureRate = params.adFailureRate;
	double exogenousFailureRate = params.exogenousFailureRate;

	bool reserveODonorsForOCandidates = params.reserveODonorsForOCandidates;
	bool checkDP = params.checkDP;
	
	
	QVector<KPDGUINode *> availablePairs;
	
	foreach(KPDGUINode * node, pairs.values()){
		if (!node->isOnHold()){
			availablePairs.push_back(node);
		}
	}

	int nVertices = availablePairs.size();

	progress->setRange(0, nVertices+nVertices*nVertices);
	progress->setValue(0);
	int progressBarValue = 0;

	viableTransplantMatrix.assign(1 + nVertices, std::vector<int>(1 + nVertices, 0));
	scoreMatrix.assign(1 + nVertices, std::vector<double>(1 + nVertices, 0.0));
	survival5yearMatrix.assign(1 + nVertices, std::vector<double>(1 + nVertices, 0.0));
	survival10yearMatrix.assign(1 + nVertices, std::vector<double>(1 + nVertices, 0.0));
	probabilityMatrix.assign(1 + nVertices, std::vector<double>(1 + nVertices, 0.0));
	labCrossmatchMatrix.assign(1 + nVertices, std::vector<int>(1 + nVertices, 0));
	incidenceMatrix.assign(1 + nVertices, std::vector<bool>(1 + nVertices, false));

	AdditionalPairInfo p;
	pairInfoVector.assign(1 + nVertices, p);
	
	for (int i = 1; i <= nVertices; i++){

		//Pair ID
		pairInfoVector[i].pairID = availablePairs.at(i - 1)->getInternalID();
		
		//For ADs
		if (availablePairs.at(i-1)->getType() == AD){ 
			pairInfoVector[i].pairType = KPDPairType::AD;
			pairInfoVector[i].uncertainty = 1-adFailureRate; 
		}
		//For Pairs
		else {
			pairInfoVector[i].pairType = KPDPairType::PAIR;
			pairInfoVector[i].uncertainty = 1-pairFailureRate;

			//Recipient Blood Type and PRA
			pairInfoVector[i].recipBT = availablePairs.at(i - 1)->getRecipBT();
			pairInfoVector[i].recipPRA = availablePairs.at(i - 1)->getRecipPRA();
		}

		//Donor Blood Type
		pairInfoVector[i].donorBT=availablePairs.at(i - 1)->getDonorBT();	

		progressBarValue++;
		progress->setValue(progressBarValue);
		QApplication::processEvents();
	}

	for (int i = 1; i <= nVertices; i++){
		for (int j = 1; j <= nVertices; j++){
			if (i != j) {
				// AD
				if (availablePairs.at(j - 1)->getType() == AD){
					viableTransplantMatrix[i][j] = 0;
					scoreMatrix[i][j] = 0.0;
					survival5yearMatrix[i][j] = 1.0;
					survival10yearMatrix[i][j] = 1.0;
					probabilityMatrix[i][j] = 1.0;
					labCrossmatchMatrix[i][j] = 1;
					incidenceMatrix[i][j] = true;
				}
				// Pair
				else  {
					if (isMatch(availablePairs.at(i - 1), availablePairs.at(j - 1), reserveODonorsForOCandidates, checkDP)){

						double praVal = availablePairs.at(j - 1)->getRecipPRA();
						double probVal;

						viableTransplantMatrix[i][j] = 1;
						scoreMatrix[i][j] = praVal / 10;
						survival5yearMatrix[i][j] = survival(availablePairs.at(i - 1), availablePairs.at(j - 1), 1);
						survival10yearMatrix[i][j] = survival(availablePairs.at(i - 1), availablePairs.at(j - 1), 0);

						if (praVal < 25){
							probVal = 0.95;
						}
						else if (praVal >= 25 && praVal < 50){
							probVal = 0.8;
						}
						else if (praVal >= 50 && praVal < 75){
							probVal = 0.65;
						}
						else {
							probVal = 0.5;
						}
						probabilityMatrix[i][j] = std::max(probVal - exogenousFailureRate, 0.01);

						incidenceMatrix[i][j] = true;
					}
				}
			}

			progressBarValue++;
			progress->setValue(progressBarValue);
			QApplication::processEvents();
		}		
	}
}

void KPDGUIRecord::deleteNodeFromRecord(int id){
	pairs.remove(id);	
}

void KPDGUIRecord::loadDictionary(){

	QVector<QVector<QVector<QString> > > dic_rows;

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
			dic_rows.push_back(row);
		}
		i++;
	}

	foreach(QVector<QVector<QString> > equivalencies, dic_rows){
		QString antigen = equivalencies.at(0).at(0);
		QVector<QString> equivalency_list = equivalencies.at(1);
		hla_dictionary.insert(antigen, equivalency_list);
	}
}

void KPDGUIRecord::clearMatrices(){
	viableTransplantMatrix.clear(); probabilityMatrix.clear(); labCrossmatchMatrix.clear(); incidenceMatrix.clear();
	survival5yearMatrix.clear(); survival10yearMatrix.clear(); scoreMatrix.clear(); pairInfoVector.clear();
}

//Checks for a match between donor and candidate
bool KPDGUIRecord::isMatch(Donor * donor, Candidate * candidate, bool reserveOtoO, bool checkDP){

	if (donor->BT != "AB" && donor->BT != "B" && donor->BT != "A" && donor->BT != "O"){
		return false;
	}

	if (candidate->BT != "AB" && candidate->BT != "B" && candidate->BT != "A" && candidate->BT != "O"){
		return false;
	}

	//Check BT match;
	if (donor->BT == "AB"){
		if (candidate->BT != "AB"){
			return false;
		}
	}
	else if (donor->BT == "A"){
		if (candidate->BT == "O" || candidate->BT == "B"){
			return false;
		}
	}
	else if (donor->BT == "B"){
		if (candidate->BT == "O" || candidate->BT == "A"){
			return false;
		}
	}

	if (reserveOtoO == true){
		if (donor->BT == "O"){
			if (candidate->BT != "O"){
				return false;
			}
		}
	}

	foreach(QString antibody, candidate->antibodies)
	{
		if (hla_dictionary.contains(antibody)){

			foreach(QString equivalentAntibody, hla_dictionary[antibody]){
				if (antibody.mid(0, 1) == "A"){
					foreach(QString antigen, donor->donorA){
						if (antigen == equivalentAntibody){
							return false;
						}
					}
				}

				if (antibody.mid(0, 1) == "B"){

					if (antibody.mid(0, 1) == "W"){
						if (equivalentAntibody == "BW4"){
							if (donor->donorBW4 == true){
								return false;
							}
						}
						if (equivalentAntibody == "BW6"){
							if (donor->donorBW6 == true){
								return false;
							}
						}
					}

					else {
						foreach(QString antigen, donor->donorB){
							if (antigen == equivalentAntibody){
								return false;
							}
						}
					}
				}

				if (antibody.mid(0, 1) == "C"){
					foreach(QString antigen, donor->donorCW){
						if (antigen == equivalentAntibody){
							return false;
						}
					}
				}

				if (antibody.mid(0, 1) == "D"){

					if (equivalentAntibody == "DR51"){
						if (donor->donorDR51 == true){
							return false;
						}
					}
					if (equivalentAntibody == "DR52"){
						if (donor->donorDR52 == true){
							return false;
						}
					}
					if (equivalentAntibody == "DR53"){
						if (donor->donorDR53 == true){
							return false;
						}
					}

					foreach(QString antigen, donor->donorDR){
						if (antigen == equivalentAntibody){
							return false;
						}
					}

					foreach(QString antigen, donor->donorDQ){
						if (antigen == equivalentAntibody){
							return false;
						}
					}

					foreach(QString antigen, donor->donorDP){
						if (antigen == equivalentAntibody){
							return false;
						}
					}
				}
			}
		}

		if (checkDP){
			foreach(QString antigen, donor->donorDP){
				if (antigen == antibody){
					return false;
				}
			}
		}
	}

	return true;
}

bool KPDGUIRecord::isMatch(KPDGUINode * donor, KPDGUINode * candidate, bool reserveOtoO, bool checkDP)
{
	if (donor == candidate){
		return false;
	}

	return isMatch(donor->getDonorPtr(), candidate->getCandidatePtr(), reserveOtoO, checkDP);
}

int KPDGUIRecord::getNumberOfVertices(){
	return pairInfoVector.size() - 1;
}


double KPDGUIRecord::survival(KPDGUINode * d, KPDGUINode * c, int fiveyear){

	Donor * donor = d->getDonorPtr();
	Candidate * candidate = c->getCandidatePtr();
	double survival = 0.0;

	//Age
	double cAge5yr[4] = { -0.047, 0.042, 0.032, 0.013 }; // ={-0.04892, 0.04142, 0.03401, 0.01230 };
	double cAge10yr[4] = { -0.045, 0.048, 0.031, 0.011 }; // ={-0.04697, 0.04719, 0.03313, 0.00918 };

	int candidatesAge = candidate->age;
	survival += candidatesAge*(fiveyear*(cAge5yr[0]) + (1 - fiveyear)*(cAge10yr[0]));
	candidatesAge = candidatesAge - 35;
	if (candidatesAge>0){
		survival += candidatesAge*(fiveyear*(cAge5yr[1]) + (1 - fiveyear)*(cAge10yr[1]));
	}
	candidatesAge = candidatesAge - 15;
	if (candidatesAge>0){
		survival += candidatesAge*(fiveyear*(cAge5yr[2]) + (1 - fiveyear)*(cAge10yr[2]));
	}
	candidatesAge = candidatesAge - 15;
	if (candidatesAge>0){
		survival += candidatesAge*(fiveyear*(cAge5yr[3]) + (1 - fiveyear)*(cAge10yr[3]));
	}

	double dAge5yr[2] = { 0.006, 0.015 }; // ={0.00618, 0.01525}
	double dAge10yr[2] = { 0.007, 0.011 }; // ={0.00690, 0.01122}
	int donorsAge = donor->age;
	survival += donorsAge*(fiveyear*(dAge5yr[0]) + (1 - fiveyear)*(dAge10yr[0]));
	donorsAge = donorsAge - 50;
	if (donorsAge>50){
		survival += donorsAge*(fiveyear*(dAge5yr[1]) + (1 - fiveyear)*(dAge10yr[1]));
	}

	//Gender
	double pGender5yr[3] = { -0.041, 0.032, -0.207 }; //={-0.04262, 0.00328, -0.18558}
	double pGender10yr[3] = { -0.040, 0.026, -0.158 }; //={-0.03518, 0.00490, -0.13700}
	if (candidate->genderMale == false && donor->genderMale == false){
		survival += fiveyear*(pGender5yr[0]) + (1 - fiveyear)*(pGender10yr[0]);
	}
	if (candidate->genderMale == false && donor->genderMale == true){
		survival = fiveyear*(pGender5yr[1]) + (1 - fiveyear)*(pGender10yr[1]);
	}
	if (candidate->genderMale == true && donor->genderMale == true){
		survival = fiveyear*(pGender5yr[2]) + (1 - fiveyear)*(pGender10yr[2]);
	}

	//Race
	double cRace5yr[3] = { 0.244, -0.173, -0.285 }; // = {0.34488, -0.10756, -0.24230}
	double cRace10yr[3] = { 0.191, -0.225, -0.305 }; // = {0.28837,-0.15943, -0.26188}
	QString race = (candidate->race).at(0);
	if (race == "B"){
		survival += fiveyear*(cRace5yr[0]) + (1 - fiveyear)*(cRace10yr[0]);
	}
	else if (race == "H"){
		survival += fiveyear*(cRace5yr[1]) + (1 - fiveyear)*(cRace10yr[1]);
	}
	else if (race != "W"){
		survival += fiveyear*(cRace5yr[2]) + (1 - fiveyear)*(cRace10yr[2]);
	}

	//HLA Mismatches
	double pNoMismatch5yr = -0.171 - 0.033; // = -0.17044-0.02501
	double pNoMismatch10yr = -0.181 - 0.042; // = -0.17875-0.03689
	survival += fiveyear*(pNoMismatch5yr)+(1 - fiveyear)*(pNoMismatch10yr);

	//PRA
	double cPRA5yr[2] = { 0.053, 0.291 }; // = {0.19014, 0.56558 };
	double cPRA10yr[2] = { 0.077, 0.313 }; // = {0.20792, 0.56931};
	if (candidate->pra >= 10 && candidate->pra <= 79){
		survival += fiveyear*(cPRA5yr[0]) + (1 - fiveyear)*(cPRA10yr[0]);
	}
	else if (candidate->pra >= 80 && candidate->pra <= 100){
		survival += fiveyear*(cPRA5yr[1]) + (1 - fiveyear)*(cPRA10yr[1]);
	}

	//Recipient Diabetes Diagnosis
	double cDiabetes5yr = 0.288; // = 0.30626;
	double cDiabetes10yr = 0.393; // = 0.40779;
	if (candidate->diabetes == true){
		survival += fiveyear*(cDiabetes5yr)+(1 - fiveyear)*(cDiabetes10yr);
	}

	//Previous Tranpslant
	double cPrevTrans5yr = 0.415;
	double cPrevTrans10yr = 0.404;
	//cout << candidate->prevTrans << endl;
	if (candidate->prevTrans == true){
		survival += fiveyear*(cPrevTrans5yr)+(1 - fiveyear)*(cPrevTrans10yr);
	}

	//BMI
	double cBMI5yr = 0.144; // = 0.13590;
	double cBMI10yr = 0.141; // = 0.13398;
	double dBMI5yr = 0.107; // = 0.10955;
	double dBMI10yr = 0.108; // = 0.11391;
	if (candidate->BMI>30){
		survival += fiveyear*(cBMI5yr)+(1 - fiveyear)*(cBMI10yr);
	}
	if (donor->BMI>30){
		survival += fiveyear*(dBMI5yr)+(1 - fiveyear)*(dBMI10yr);
	}

	//Time on Dialysis
	double cTOD5yr[5] = { -0.443, -0.323, -0.186, -0.040, 0.127 };
	double cTOD10yr[5] = { -0.396, -0.316, -0.179, -0.012, 0.151 };
	if (candidate->TOD == 0){
		survival += fiveyear*(cTOD5yr[0]) + (1 - fiveyear)*(cTOD10yr[0]);
	}
	else if (candidate->TOD>0 && candidate->TOD <= 0.5){
		survival += fiveyear*(cTOD5yr[1]) + (1 - fiveyear)*(cTOD10yr[1]);
	}
	else if (candidate->TOD>0.5 && candidate->TOD <= 1){
		survival += fiveyear*(cTOD5yr[2]) + (1 - fiveyear)*(cTOD10yr[2]);
	}
	else if (candidate->TOD>2 && candidate->TOD <= 3){
		survival += fiveyear*(cTOD5yr[3]) + (1 - fiveyear)*(cTOD10yr[3]);
	}
	else if (candidate->TOD>3){
		survival += fiveyear*(cTOD5yr[4]) + (1 - fiveyear)*(cTOD10yr[4]);
	}

	//Weight Ratio
	double weightRatio = (donor->weight) / (candidate->weight);
	double pWR5yr[3] = { 0.133, 0.079, 0.038 }; // = { 0.11641, 0.07311, 0.05486};
	double pWR10yr[3] = { 0.109, 0.094, 0.066 }; // = { 0.09756, 0.09150, 0.08041};

	if (weightRatio < 0.75){
		survival += fiveyear*(pWR5yr[0]) + (1 - fiveyear)*(pWR10yr[0]);
	}
	else if (weightRatio >= 0.75 && weightRatio <0.90){
		survival += fiveyear*(pWR5yr[1]) + (1 - fiveyear)*(pWR10yr[1]);
	}
	else if (weightRatio >= 1.15){
		survival += fiveyear*(pWR5yr[2]) + (1 - fiveyear)*(pWR10yr[2]);
	}

	//Hep C Seriology
	double cHepC5yr = 0.466;
	double cHepC10yr = 0.427;
	if (candidate->hepC == true){
		survival += fiveyear*(cHepC5yr)+(1 - fiveyear)*(cHepC10yr);
	}

	double expo = exp(survival);
	if (fiveyear == 1){
		survival = pow(0.55013, expo);
	}
	else {
		survival = pow(0.41840, expo);
	}

	return survival;
}
