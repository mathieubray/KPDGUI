#include "KPDGUICrossmatchFunctions.h"

KPDGUICrossmatchFunctions::KPDGUICrossmatchFunctions() {
	
	loadDictionary();
	loadSurvivalParameters();
}

KPDGUICrossmatchFunctions::~KPDGUICrossmatchFunctions() {
	
}

void KPDGUICrossmatchFunctions::loadDictionary() {

	QVector<QVector<QVector<QString> > > dictionaryData = KPDFunctions::loadData("HLADictionary.csv", false);

	foreach(QVector<QVector<QString> > equivalencies, dictionaryData) {
		QString antigen = equivalencies.at(0).at(0);
		QVector<QString> equivalency_list = equivalencies.at(1);
		hlaDictionary.insert(antigen, equivalency_list);
	}
}

void KPDGUICrossmatchFunctions::loadSurvivalParameters() {

	QVector<QVector<QVector<QString> > > survivalData = KPDFunctions::loadData("SurvivalParameters.csv", false);

	foreach(QVector<QVector<QString> > dataRow, survivalData) {

		QString characteristic = dataRow.at(0).at(0);

		QString fiveYear = "5 Year ";
		fiveYear.append(characteristic);

		QString tenYear = "10 Year ";
		tenYear.append(characteristic);

		survivalParameters[fiveYear].push_back(dataRow.at(2).at(0).toDouble());
		survivalParameters[tenYear].push_back(dataRow.at(3).at(0).toDouble());
	}
}

//Checks for a match between donor and candidate
KPDCrossmatchResult KPDGUICrossmatchFunctions::performCrossmatch(KPDGUIDonor * donor, KPDGUICandidate * candidate) {

	//Check BT match;
	if (donor->getBT() == BT_AB) {
		if (candidate->getBT() != BT_AB) {
			return FAILED_CROSSMATCH_BT;
		}
	}
	else if (donor->getBT() == BT_A) {
		if (candidate->getBT() == BT_O || candidate->getBT() == BT_B) {
			return FAILED_CROSSMATCH_BT;
		}
	}
	else if (donor->getBT() == BT_B) {
		if (candidate->getBT() == BT_O || candidate->getBT() == BT_A) {
			return FAILED_CROSSMATCH_BT;
		}
	}

	QVector<int> mismatches = countHLAMismatches(donor, candidate);

	if (mismatches[0] > 0 || mismatches[1] > 0) {
		return FAILED_CROSSMATCH_HLA;
	}

	bool failsOnAdditionalHLA = false;

	foreach(QString antibody, candidate->getHLA()) {

		if (hlaDictionary.contains(antibody)) {

			foreach(QString equivalentAntibody, hlaDictionary[antibody]) {

				foreach(QString antigen, donor->getAdditionalHLA()) {
					if (antigen == equivalentAntibody) {
						failsOnAdditionalHLA = true;
					}
				}
			}
		}
	}

	if (failsOnAdditionalHLA) {
		return FAILED_CROSSMATCH_ADDITIONAL_HLA;
	}

	if (donor->getBT() == BT_O && candidate->getBT() != BT_O) {
		return O_DONOR_TO_NON_O_CANDIDATE;
	}

	return SUCCESSFUL_CROSSMATCH;
}

double KPDGUICrossmatchFunctions::calculateSurvival(KPDGUIDonor * donor, KPDGUICandidate * candidate, int fiveyear) {

	double survival = 0.0;

	//Age
	QVector<double> cAge5yr = survivalParameters["5 Year Recipient Age"];
	QVector<double> cAge10yr = survivalParameters["10 Year Recipient Age"];

	QVector<double> dAge5yr;
	QVector<double> dAge10yr;

	QVector<int> donorAgeChangePoints = { 30,10,10,10,10 };
	int changePoint = 0;

	//qDebug() << "Donor Age: " << donor->getAge();
	//qDebug() << "Candidate Age: " << candidate->getAge();

	int donorsAge = donor->getAge();

	if (candidate->getAge() < 13) {

		dAge5yr = survivalParameters["5 Year Among Recipients Age < 12"];
		dAge10yr = survivalParameters["10 Year Among Recipients Age < 12"];

		survival += fiveyear*(cAge5yr[0]) + (1 - fiveyear)*(cAge10yr[0]);
	}
	else if (candidate->getAge() >= 13 && candidate->getAge() <= 17) {

		dAge5yr = survivalParameters["5 Year Among Recipients 13-17"];
		dAge10yr = survivalParameters["10 Year Among Recipients 13-17"];

		survival += fiveyear*(cAge5yr[1]) + (1 - fiveyear)*(cAge10yr[1]);
	}
	else if (candidate->getAge() >= 18 && candidate->getAge() <= 29) {

		dAge5yr = survivalParameters["5 Year Among Recipients 18-29"];
		dAge10yr = survivalParameters["10 Year Among Recipients 18-29"];

		survival += fiveyear*(cAge5yr[2]) + (1 - fiveyear)*(cAge10yr[2]);
	}
	else if (candidate->getAge() >= 30 && candidate->getAge() <= 39) {

		dAge5yr = survivalParameters["5 Year Among Recipients 30-39"];
		dAge10yr = survivalParameters["10 Year Among Recipients 30-39"];

		survival += fiveyear*(cAge5yr[3]) + (1 - fiveyear)*(cAge10yr[3]);
	}
	else if (candidate->getAge() >= 40 && candidate->getAge() <= 49) {

		dAge5yr = survivalParameters["5 Year Among Recipients 40-49"];
		dAge10yr = survivalParameters["10 Year Among Recipients 40-49"];
	}
	else if (candidate->getAge() >= 50 && candidate->getAge() <= 59) {

		dAge5yr = survivalParameters["5 Year Among Recipients 50-59"];
		dAge10yr = survivalParameters["10 Year Among Recipients 50-59"];

		survival += fiveyear*(cAge5yr[5]) + (1 - fiveyear)*(cAge10yr[5]);
	}
	else if (candidate->getAge() >= 60) {

		dAge5yr = survivalParameters["5 Year Among Recipients 60+"];
		dAge10yr = survivalParameters["10 Year Among Recipients 60+"];

		survival += fiveyear*(cAge5yr[6]) + (1 - fiveyear)*(cAge10yr[6]);
	}

	while (donorsAge > 0 && changePoint <= 3) {
		survival += donorsAge*(fiveyear*(dAge5yr[changePoint]) + (1 - fiveyear)*(dAge10yr[changePoint]));
		donorsAge = donorsAge - donorAgeChangePoints[changePoint];
		changePoint++;
	}

	//Sex Combination
	QVector<double> pSex5yr = survivalParameters["5 Year Donor-Recipient Sex"];
	QVector<double> pSex10yr = survivalParameters["10 Year Donor-Recipient Sex"];
	if (!candidate->getMale() && !donor->getMale()) {
		survival += fiveyear*(pSex5yr[0]) + (1 - fiveyear)*(pSex10yr[0]);
	}
	if (!candidate->getMale() && donor->getMale()) {
		survival += fiveyear*(pSex5yr[1]) + (1 - fiveyear)*(pSex10yr[1]);
	}
	if (candidate->getMale() && donor->getMale()) {
		survival += fiveyear*(pSex5yr[3]) + (1 - fiveyear)*(pSex10yr[3]);
	}

	//HLA Mismatches
	QVector<int> mismatches = countHLAMismatches(donor, candidate);
	QVector<double> pMismatch5yr = survivalParameters["5 Year HLA ABDR Mismatch"];
	QVector<double> pMismatch10yr = survivalParameters["10 Year HLA ABDR Mismatch"];

	if (mismatches[0] == 0 && mismatches[1] == 0) {
		survival += fiveyear*(pMismatch5yr[0]) + (1 - fiveyear)*(pMismatch10yr[0]);
	}
	else if (mismatches[0] >= 1 && mismatches[0] <= 2 && mismatches[1] == 0) {
		survival += fiveyear*(pMismatch5yr[1]) + (1 - fiveyear)*(pMismatch10yr[1]);
	}
	else if (mismatches[0] >= 1 && mismatches[0] <= 2 && mismatches[1] > 0) {
		survival += fiveyear*(pMismatch5yr[2]) + (1 - fiveyear)*(pMismatch10yr[2]);
	}
	else if (mismatches[0] >= 3 && mismatches[0] <= 4 && mismatches[1] == 0) {
		survival += fiveyear*(pMismatch5yr[3]) + (1 - fiveyear)*(pMismatch10yr[3]);
	}
	else if (mismatches[0] >= 3 && mismatches[1] <= 4 && mismatches[1] > 0) {
		survival += fiveyear*(pMismatch5yr[4]) + (1 - fiveyear)*(pMismatch10yr[4]);
	}
	else {
		survival += fiveyear*(pMismatch5yr[5]) + (1 - fiveyear)*(pMismatch10yr[5]);
	}

	//BMI
	double cBMI5yr = survivalParameters["5 Year Recipient BMI"][1];
	double cBMI10yr = survivalParameters["10 Year Recipient BMI"][1];
	double dBMI5yr = survivalParameters["5 Year Donor BMI"][1];
	double dBMI10yr = survivalParameters["10 Year Donor BMI"][1];

	if (candidate->getBMI()>30) {
		survival += fiveyear*(cBMI5yr)+(1 - fiveyear)*(cBMI10yr);
	}
	if (donor->getBMI()>30) {
		survival += fiveyear*(dBMI5yr)+(1 - fiveyear)*(dBMI10yr);
	}

	//Weight Ratio
	double weightRatio = (donor->getWeight()) / (candidate->getWeight());
	QVector<double> pWR5yr = survivalParameters["5 Year Donor-Recipient Weight Ratio"];
	QVector<double> pWR10yr = survivalParameters["10 Year Donor-Recipient Weight Ratio"];

	if (weightRatio < 0.75) {
		survival += fiveyear*(pWR5yr[0]) + (1 - fiveyear)*(pWR10yr[0]);
	}
	else if (weightRatio >= 0.75 && weightRatio < 0.90) {
		survival += fiveyear*(pWR5yr[1]) + (1 - fiveyear)*(pWR10yr[1]);
	}
	else if (weightRatio >= 1.15) {
		survival += fiveyear*(pWR5yr[3]) + (1 - fiveyear)*(pWR10yr[3]);
	}

	//Height Ratio
	double heightRatio = (donor->getHeight()) / (candidate->getHeight());
	QVector<double> pHR5yr = survivalParameters["5 Year Donor-Recipient Height Ratio"];
	QVector<double> pHR10yr = survivalParameters["10 Year Donor-Recipient Height Ratio"];

	if (heightRatio < 0.94) {
		survival += fiveyear*(pHR5yr[0]) + (1 - fiveyear)*(pHR10yr[0]);
	}
	else if (heightRatio >= 0.94 && heightRatio < 1.0) {
		survival += fiveyear*(pHR5yr[1]) + (1 - fiveyear)*(pHR10yr[1]);
	}
	else if (heightRatio >= 1.06) {
		survival += fiveyear*(pHR5yr[2]) + (1 - fiveyear)*(pHR10yr[2]);
	}

	//Race
	QVector<double> cRace5yr = survivalParameters["5 Year Recipient Race"];
	QVector<double> cRace10yr = survivalParameters["10 Year Recipient Race"];
	if (candidate->getRace() == RACE_WHITE) {
		survival += fiveyear*(cRace5yr[0]) + (1 - fiveyear)*(cRace10yr[0]);
	}
	else if (candidate->getRace() == RACE_BLACK) {
		survival += fiveyear*(cRace5yr[1]) + (1 - fiveyear)*(cRace10yr[1]);
	}
	else if (candidate->getRace() == RACE_HISPANIC) {
		survival += fiveyear*(cRace5yr[2]) + (1 - fiveyear)*(cRace10yr[2]);
	}
	else {
		survival += fiveyear*(cRace5yr[3]) + (1 - fiveyear)*(cRace10yr[3]);
	}

	QVector<double> dRace5yr = survivalParameters["5 Year Donor Race"];
	QVector<double> dRace10yr = survivalParameters["10 Year Donor Race"];
	if (donor->getRace() != RACE_BLACK && donor->getRace() != RACE_HISPANIC) {
		survival += fiveyear*(dRace5yr[0]) + (1 - fiveyear)*(dRace10yr[0]);
	}
	else if (donor->getRace() == RACE_BLACK) {
		survival += fiveyear*(dRace5yr[1]) + (1 - fiveyear)*(dRace10yr[1]);
	}
	else if (donor->getRace() == RACE_HISPANIC) {
		survival += fiveyear*(dRace5yr[2]) + (1 - fiveyear)*(dRace10yr[2]);
	}

	//Donor Cigarette Use
	QVector<double> dCigarette5yr = survivalParameters["5 Year Donor Cigarette Use"];
	QVector<double> dCigarette10yr = survivalParameters["10 Year Donor Cigarette Use"];
	if (donor->getCigarette()) {
		survival += fiveyear*(dCigarette5yr[1]) + (1 - fiveyear)*(dCigarette10yr[1]);
	}

	//PRA
	QVector<double> cPRA5yr = survivalParameters["5 Year PRA"];
	QVector<double> cPRA10yr = survivalParameters["10 Year PRA"];
	if (candidate->getPRA() >= 10 && candidate->getPRA() <= 79) {
		survival += fiveyear*(cPRA5yr[1]) + (1 - fiveyear)*(cPRA10yr[1]);
	}
	else if (candidate->getPRA() >= 80 && candidate->getPRA() <= 100) {
		survival += fiveyear*(cPRA5yr[2]) + (1 - fiveyear)*(cPRA10yr[2]);
	}

	//Recipient Diabetes Diagnosis
	double cDiabetes5yr = survivalParameters["5 Year Recipient Diabetes Status"][1];
	double cDiabetes10yr = survivalParameters["10 Year Recipient Diabetes Status"][1];
	if (candidate->getDiabetes()) {
		survival += fiveyear*(cDiabetes5yr)+(1 - fiveyear)*(cDiabetes10yr);
	}

	//Previous Tranpslant
	double cPrevTrans5yr = survivalParameters["5 Year Previous Transplant"][1];
	double cPrevTrans10yr = survivalParameters["10 Year Previous Transplant"][1];
	if (candidate->getPrevTrans()) {
		survival += fiveyear*(cPrevTrans5yr)+(1 - fiveyear)*(cPrevTrans10yr);
	}

	//Time on Dialysis
	QVector<double> cTOD5yr = survivalParameters["5 Year Time on Dialysis"];
	QVector<double> cTOD10yr = survivalParameters["10 Year Time on Dialysis"];
	if (candidate->getTOD() == 0) {
		survival += fiveyear*(cTOD5yr[0]) + (1 - fiveyear)*(cTOD10yr[0]);
	}
	else if (candidate->getTOD() > 0 && candidate->getTOD() <= 1) {
		survival += fiveyear*(cTOD5yr[1]) + (1 - fiveyear)*(cTOD10yr[1]);
	}
	else if (candidate->getTOD() > 1 && candidate->getTOD() <= 2) {
		survival += fiveyear*(cTOD5yr[2]) + (1 - fiveyear)*(cTOD10yr[2]);
	}
	else if (candidate->getTOD() > 2 && candidate->getTOD() <= 3) {
		survival += fiveyear*(cTOD5yr[3]) + (1 - fiveyear)*(cTOD10yr[3]);
	}
	else if (candidate->getTOD() > 3) {
		survival += fiveyear*(cTOD5yr[4]) + (1 - fiveyear)*(cTOD10yr[4]);
	}

	//Hep C Seriology
	double cHepC5yr = survivalParameters["5 Year Recipient Hepatitis C Seriology"][1];
	double cHepC10yr = survivalParameters["10 Year Recipient Hepatitis C Seriology"][1];
	if (candidate->getHepC()) {
		survival += fiveyear*(cHepC5yr)+(1 - fiveyear)*(cHepC10yr);
	}

	//Insurance
	QVector<double> cInsurance5yr = survivalParameters["5 Year Recipient Insurance"];
	QVector<double> cInsurance10yr = survivalParameters["10 Year Recipient Insurance"];

	if (candidate->getInsurance() == PUBLIC) {
		survival += fiveyear*(cInsurance5yr[0]) + (1 - fiveyear)*(cInsurance10yr[0]);
	}
	else if (candidate->getInsurance() == PRIVATE) {
		survival += fiveyear*(cInsurance5yr[1]) + (1 - fiveyear)*(cInsurance10yr[1]);
	}
	else if (candidate->getInsurance() == OTHER_INSURANCE) {
		survival += fiveyear*(cInsurance5yr[2]) + (1 - fiveyear)*(cInsurance10yr[2]);
	}

	//Adjust for Year
	survival += fiveyear*(survivalParameters["5 Year Transplant Year"][2]) + (1 - fiveyear)*(survivalParameters["10 Year Transplant Year"][2]);

	//Calculate Survival
	double expo = exp(survival);
	if (fiveyear == 1) {
		survival = pow(survivalParameters["5 Year Baseline"][0], expo);
	}
	else {
		survival = pow(survivalParameters["10 Year Baseline"][0], expo);
	}

	return survival;

}

QVector<int> KPDGUICrossmatchFunctions::countHLAMismatches(KPDGUIDonor * donor, KPDGUICandidate * candidate) {

	int hlaMismatches = 0;
	int drMismatches = 0;

	foreach(QString antibody, candidate->getHLA()) {

		if (hlaDictionary.contains(antibody)) {

			foreach(QString equivalentAntibody, hlaDictionary[antibody]) {
				if (antibody.mid(0, 1) == "A") {
					foreach(QString antigen, donor->getA()) {

						if (antigen == equivalentAntibody) {
							hlaMismatches++;
						}
					}
				}

				if (antibody.mid(0, 1) == "B") {

					if (antibody.mid(0, 1) == "W") {
						if (equivalentAntibody == "BW4") {
							if (donor->getBW4() == true) {
								hlaMismatches++;
							}
						}
						if (equivalentAntibody == "BW6") {
							if (donor->getBW6() == true) {
								hlaMismatches++;
							}
						}
					}

					else {
						foreach(QString antigen, donor->getB()) {
							if (antigen == equivalentAntibody) {
								hlaMismatches++;
							}
						}
					}
				}

				if (antibody.mid(0, 1) == "C") {
					foreach(QString antigen, donor->getCW()) {
						if (antigen == equivalentAntibody) {
							hlaMismatches++;
						}
					}
				}

				if (antibody.mid(0, 1) == "D") {

					if (equivalentAntibody == "DR51") {
						if (donor->getDR51() == true) {
							hlaMismatches++;
							drMismatches++;
						}
					}
					if (equivalentAntibody == "DR52") {
						if (donor->getDR52() == true) {
							hlaMismatches++;
							drMismatches++;
						}
					}
					if (equivalentAntibody == "DR53") {
						if (donor->getDR53() == true) {
							hlaMismatches++;
							drMismatches++;
						}
					}

					foreach(QString antigen, donor->getDR()) {
						if (antigen == equivalentAntibody) {
							hlaMismatches++;
							drMismatches++;
						}
					}

					foreach(QString antigen, donor->getDQ()) {
						if (antigen == equivalentAntibody) {
							hlaMismatches++;
						}
					}
				}
			}
		}
	}

	QVector<int> mismatches;
	mismatches << hlaMismatches << drMismatches;

	return mismatches;

}

bool KPDGUICrossmatchFunctions::determineDifficultMatch(KPDGUIDonor * donor, KPDGUICandidate * candidate) {

	bool difficultMatch = false;

	if (candidate->getHLA().size() > 10 || donor->getBT() == BT_AB || candidate->getPRA() >= 97) {
		difficultMatch = true;
	}

	return difficultMatch;

}
