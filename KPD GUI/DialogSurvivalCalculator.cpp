

#include "DialogSurvivalCalculator.h"

DialogSurvivalCalculator::DialogSurvivalCalculator(KPDGUIMatch * match, KPDGUIDashboardList * donorDashboard, KPDGUIDashboardList * candidateDashboard, KPDGUICrossmatchFunctions * functions, QWidget * parent) : QDialog(parent)
{
	donor = new KPDGUIDonor();
	candidate = new KPDGUICandidate();

	crossmatchFunctions = functions;

	setupUi(this);

	connect(this, SIGNAL(survivalSignal()), this, SLOT(updateSurvival()));

	additionalSetup(donorDashboard, candidateDashboard);

	updateDonorInfo(match->getDonor());
	updateCandidateInfo(match->getCandidate());

	//qDebug() << "From the Match: " << match->getFiveYearSurvival() << match->getTenYearSurvival();
	//qDebug() << "Calculated: " << crossmatchFunctions->calculateSurvival(match->getDonor(), match->getCandidate(), true) << crossmatchFunctions->calculateSurvival(match->getDonor(), match->getCandidate(), false);
	//qDebug() << "Updated Info: " << crossmatchFunctions->calculateSurvival(donor, candidate, true) << crossmatchFunctions->calculateSurvival(donor, candidate, false);

	updateSurvival();
}


DialogSurvivalCalculator::DialogSurvivalCalculator(KPDGUIDashboardList * donorDashboard, KPDGUIDashboardList * candidateDashboard, KPDGUICrossmatchFunctions * functions, QWidget * parent) : QDialog(parent)
{
	donor = new KPDGUIDonor();
	candidate = new KPDGUICandidate();

	crossmatchFunctions = functions;

	setupUi(this);

	connect(this, SIGNAL(survivalSignal()), this, SLOT(updateSurvival()));

	additionalSetup(donorDashboard, candidateDashboard);

	updateSurvival();
}

DialogSurvivalCalculator::~DialogSurvivalCalculator() {

	delete donor;
	delete candidate;
}

void DialogSurvivalCalculator::updateDonorAge(int age) {

	donor->setAge(age);

	//qDebug() << "Updated Donor Age!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorBT(int btIndex) {

	KPDBloodType bt = KPDFunctions::intToBloodType(btIndex);

	donor->setBT(bt);

	//qDebug() << "Updated Donor BT!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorA() {
	
	QString hla1 = donorHLAA1ComboBox->currentText();
	QString hla2 = donorHLAA2ComboBox->currentText();

	QVector<QString> hlaList;

	if (hla1 != "") {
		hlaList << hla1;
	}
	if (hla2 != "") {
		hlaList << hla2;
	}
	
	donor->setA(hlaList);


	//qDebug() << "Updated Donor HLA A!";

	emit survivalSignal();
}


void DialogSurvivalCalculator::updateDonorB() {

	QString hla1 = donorHLAB1ComboBox->currentText();
	QString hla2 = donorHLAB2ComboBox->currentText();

	QVector<QString> hlaList;

	if (hla1 != "") {
		hlaList << hla1;
	}
	if (hla2 != "") {
		hlaList << hla2;
	}

	donor->setB(hlaList);

	//qDebug() << "Updated Donor HLA B!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorCW() {

	QString hla1 = donorHLACW1ComboBox->currentText();
	QString hla2 = donorHLACW2ComboBox->currentText();

	QVector<QString> hlaList;

	if (hla1 != "") {
		hlaList << hla1;
	}
	if (hla2 != "") {
		hlaList << hla2;
	}

	donor->setCW(hlaList);

	//qDebug() << "Updated Donor HLA CW!";

	emit survivalSignal();
}


void DialogSurvivalCalculator::updateDonorDQ() {

	QString hla1 = donorHLADQ1ComboBox->currentText();
	QString hla2 = donorHLADQ2ComboBox->currentText();

	QVector<QString> hlaList;

	if (hla1 != "") {
		hlaList << hla1;
	}
	if (hla2 != "") {
		hlaList << hla2;
	}

	donor->setDQ(hlaList);

	//qDebug() << "Updated Donor HLA DQ!";

	emit survivalSignal();
}


void DialogSurvivalCalculator::updateDonorDR() {

	QString hla1 = donorHLADR1ComboBox->currentText();
	QString hla2 = donorHLADR2ComboBox->currentText();

	QVector<QString> hlaList;

	if (hla1 != "") {
		hlaList << hla1;
	}
	if (hla2 != "") {
		hlaList << hla2;
	}

	donor->setDR(hlaList);

	//qDebug() << "Updated Donor HLA DR!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorBW4(bool hla) {

	donor->setBW4(hla);

	//qDebug() << "Updated Donor HLA BW4!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorBW6(bool hla) {

	donor->setBW6(hla);

	//qDebug() << "Updated Donor HLA BW6!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorDR51(bool hla) {
	
	donor->setDR51(hla);

	//qDebug() << "Updated Donor HLA DR51!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorDR52(bool hla) {

	donor->setDR52(hla);

	//qDebug() << "Updated Donor HLA DR52!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorDR53(bool hla) {

	donor->setDR53(hla);

	//qDebug() << "Updated Donor HLA DR53!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateAdditionalDonorHLA(QString hla) {

	QVector<QString> hlaList = hla.split(";").toVector();

	donor->setAdditionalDonorHLA(hlaList);

	//qDebug() << "Updated Donor HLA Additional HLA!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorRace(int raceIndex) {

	KPDRace race = KPDFunctions::intToRace(raceIndex);

	donor->setRace(race);

	//qDebug() << "Updated Donor HLA Race!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorGender(int genderIndex) {

	if (genderIndex == 0) {
		donor->setMale(true);
	}
	else {
		donor->setMale(false);
	}

	//qDebug() << "Updated Donor HLA Gender!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorWeight(double weight) {

	donor->setWeight(weight);

	//qDebug() << "Updated Donor Weight!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorHeight(double height) {

	donor->setHeight(height);

	//qDebug() << "Updated Donor Height!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateDonorCigaretteUse(bool cigarette) {

	donor->setCigarette(cigarette);

	//qDebug() << "Updated Donor Cigarette!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidateAge(int age){

	candidate->setAge(age);

	//qDebug() << "Updated Candidate Age!";


	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidatePRA(int pra){

	candidate->setPRA(pra);

	//qDebug() << "Updated Candidate PRA!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidateBT(int btIndex) {

	KPDBloodType bt = KPDFunctions::intToBloodType(btIndex);

	candidate->setBT(bt);

	//qDebug() << "Updated Candidate BT!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidateHLA(QString hla){

	QVector<QString> hlaList = hla.split(";").toVector();

	candidate->setHLA(hlaList);

	//qDebug() << "Updated Candidate HLA!";
	
	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidateGender(int genderIndex) {

	if (genderIndex == 0) {
		candidate->setMale(true);
	}
	else {
		candidate->setMale(false);
	}

	//qDebug() << "Updated Candidate Gender!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidateRace(int raceIndex) {

	KPDRace race = KPDFunctions::intToRace(raceIndex);

	candidate->setRace(race);

	//qDebug() << "Updated Candidate Race!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidateDiabetes(bool diabetes) {

	candidate->setDiabetes(diabetes);

	//qDebug() << "Updated Candidate Diabetes!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidateWeight(double weight) {

	candidate->setWeight(weight);

	//qDebug() << "Updated Candidate Weight!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidateHeight(double height) {

	candidate->setHeight(height);

	//qDebug() << "Updated Candidate Height!";


	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidatePrevTrans(bool prevTrans) {

	candidate->setPrevTrans(prevTrans);

	//qDebug() << "Updated Candidate Previous Transplant!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidateTOD(double TOD) {

	candidate->setTOD(TOD);

	//qDebug() << "Updated Candidate TOD!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidateHepC(bool hepC) {

	candidate->setHepC(hepC);

	//qDebug() << "Updated Candidate Hep C!";

	emit survivalSignal();
}

void DialogSurvivalCalculator::updateCandidateInsurance(int insuranceIndex) {

	KPDInsurance insurance = KPDFunctions::intToInsurance(insuranceIndex);

	candidate->setInsurance(insurance);

	//qDebug() << "Updated Candidate Insurance!";

	emit survivalSignal();

}

void DialogSurvivalCalculator::selectDonor(QListWidgetItem * item) {

	KPDGUIDonor * newDonor = donorMap.value(item);

	updateDonorInfo(newDonor);
}

void DialogSurvivalCalculator::updateDonorInfo(KPDGUIDonor * newDonor) {
		
	blockSignals(true);
	
	//Age
	donorAgeSpinBox->setValue(newDonor->getAge());

	//Blood Type
	donorBTComboBox->setCurrentIndex(KPDFunctions::bloodTypeToInt(newDonor->getBT()));

	//Gender

	if (newDonor->getMale()) { donorGenderComboBox->setCurrentIndex(0); }
	else { donorGenderComboBox->setCurrentIndex(1); }

	//Race
	donorRaceComboBox->setCurrentIndex(KPDFunctions::raceToInt(newDonor->getRace()));

	//Height
	donorHeightSpinBox->setValue(newDonor->getHeight());

	//Weight
	donorWeightSpinBox->setValue(newDonor->getWeight());

	//Cigarette
	donorCigaretteCheckBox->setChecked(newDonor->getCigarette());

	//HLA
	if (newDonor->getA().size() >= 1) {
		int hlaA1index = donorHLAA1ComboBox->findText(newDonor->getA().at(0));
		if (hlaA1index >= 0) {
			donorHLAA1ComboBox->setCurrentIndex(hlaA1index);
		}
		if (newDonor->getA().size() >= 2) {
			int hlaA2index = donorHLAA2ComboBox->findText(newDonor->getA().at(1));
			if (hlaA2index >= 0) {
				donorHLAA2ComboBox->setCurrentIndex(hlaA2index);
			}
		}
	}
	if (newDonor->getB().size() >= 1) {
		int hlaB1index = donorHLAB1ComboBox->findText(newDonor->getB().at(0));
		if (hlaB1index >= 0) {
			donorHLAB1ComboBox->setCurrentIndex(hlaB1index);
		}
		if (newDonor->getB().size() >= 2) {
			int hlaB2index = donorHLAB2ComboBox->findText(newDonor->getB().at(1));
			if (hlaB2index >= 0) {
				donorHLAB2ComboBox->setCurrentIndex(hlaB2index);
			}
		}
	}
	if (newDonor->getCW().size() >= 1) {
		int hlaCW1index = donorHLACW1ComboBox->findText(newDonor->getCW().at(0));
		if (hlaCW1index >= 0) {
			donorHLACW1ComboBox->setCurrentIndex(hlaCW1index);
		}
		if (newDonor->getCW().size() >= 2) {
			int hlaCW2index = donorHLACW2ComboBox->findText(newDonor->getCW().at(1));
			if (hlaCW2index >= 0) {
				donorHLACW2ComboBox->setCurrentIndex(hlaCW2index);
			}
		}
	}
	if (newDonor->getDQ().size() >= 1) {
		int hlaDQ1index = donorHLADQ1ComboBox->findText(newDonor->getDQ().at(0));
		if (hlaDQ1index >= 0) {
			donorHLADQ1ComboBox->setCurrentIndex(hlaDQ1index);
		}
		if (newDonor->getDQ().size() >= 2) {
			int hlaDQ2index = donorHLADQ2ComboBox->findText(newDonor->getDQ().at(1));
			if (hlaDQ2index >= 0) {
				donorHLADQ2ComboBox->setCurrentIndex(hlaDQ2index);
			}
		}
	}
	if (newDonor->getDR().size() >= 1) {
		int hlaDR1index = donorHLADR1ComboBox->findText(newDonor->getDR().at(0));
		if (hlaDR1index >= 0) {
			donorHLADR1ComboBox->setCurrentIndex(hlaDR1index);
		}
		if (newDonor->getDR().size() >= 2) {
			int hlaDR2index = donorHLADR2ComboBox->findText(newDonor->getDR().at(1));
			if (hlaDR2index >= 0) {
				donorHLADR2ComboBox->setCurrentIndex(hlaDR2index);
			}
		}
	}

	donorBW4CheckBox->setChecked(newDonor->getBW4());
	donorBW6CheckBox->setChecked(newDonor->getBW6());
	donorDR51CheckBox->setChecked(newDonor->getDR51());
	donorDR52CheckBox->setChecked(newDonor->getDR52());
	donorDR53CheckBox->setChecked(newDonor->getDR53());

	//Additional Donor HLA
	QString additionalDonorHLAString = "";
	foreach(QString additionalDonorHLA, newDonor->getAdditionalHLA()) {
		additionalDonorHLAString.append(additionalDonorHLA);
		additionalDonorHLAString.append(";");
	}
	additionalDonorHLAString.chop(1);
	donorHLALineEdit->setText(additionalDonorHLAString);

	blockSignals(false);

	updateSurvival();
}

void DialogSurvivalCalculator::selectCandidate(QListWidgetItem * item) {
	
	KPDGUICandidate * newCandidate = candidateMap.value(item);

	updateCandidateInfo(newCandidate);
}

void DialogSurvivalCalculator::updateCandidateInfo(KPDGUICandidate * newCandidate) {
	
	blockSignals(true);
	
	//Candidate Age
	candidateAgeSpinBox->setValue(newCandidate->getAge());

	//Candidate Blood Type
	candidateBTComboBox->setCurrentIndex(KPDFunctions::bloodTypeToInt(newCandidate->getBT()));

	//Candidate PRA
	candidatePRASpinBox->setValue(newCandidate->getPRA());

	//Candidate HLA
	QString antibodyString = "";
	foreach(QString antibody, newCandidate->getHLA()) {
		antibodyString.append(antibody);
		antibodyString.append(";");
	}
	antibodyString.chop(1);
	candidateHLALineEdit->setText(antibodyString);

	//Candidate Gender
	if (newCandidate->getMale()) { candidateGenderComboBox->setCurrentIndex(0); }
	else { candidateGenderComboBox->setCurrentIndex(1); }

	//Candidate Height
	candidateHeightSpinBox->setValue(newCandidate->getHeight());

	//Candidate Weight
	candidateWeightSpinBox->setValue(newCandidate->getWeight());

	//Candidate Diabetes
	candidateDiabetesCheckBox->setChecked(newCandidate->getDiabetes());

	//Candidate Hepatitis C
	candidateHepCCheckBox->setChecked(newCandidate->getHepC());

	//Candidate Race
	candidateRaceComboBox->setCurrentIndex(KPDFunctions::raceToInt(newCandidate->getRace()));

	//Candidate Time On Dialysis
	candidateTODSpinBox->setValue(newCandidate->getTOD());

	//Candidate Previous Transplant
	candidatePrevTransCheckBox->setChecked(newCandidate->getPrevTrans());

	//Candidate Insurance
	candidateInsuranceComboBox->setCurrentIndex(KPDFunctions::insuranceToInt(newCandidate->getInsurance()));

	blockSignals(false);

	updateSurvival();
}

void DialogSurvivalCalculator::updateSurvival() {
					
	double fiveYearSurvival = crossmatchFunctions->calculateSurvival(donor, candidate, true);
	double tenYearSurvival = crossmatchFunctions->calculateSurvival(donor, candidate, false);

	KPDCrossmatchResult crossmatchResult = crossmatchFunctions->performCrossmatch(donor, candidate);

	double newFiveYearSurvival = floor(fiveYearSurvival * 1000 + 0.5) / 1000;
	double newTenYearSurvival = floor(tenYearSurvival * 1000 + 0.5) / 1000;
	
	double currentFiveYearSurvival;
	double currentTenYearSurvival;

	if (fiveYearTextEdit->toPlainText() == "") {
		currentFiveYearSurvival = newFiveYearSurvival;
		currentTenYearSurvival = newTenYearSurvival;
	}
	else {
		currentFiveYearSurvival = fiveYearTextEdit->toPlainText().toDouble();
		currentTenYearSurvival = tenYearTextEdit->toPlainText().toDouble();
	}

	fiveYearTextEdit->setText(QString::number(newFiveYearSurvival));
	tenYearTextEdit->setText(QString::number(newTenYearSurvival));

	crossmatchTextEdit->setText(KPDFunctions::toString(crossmatchResult));

	if (newFiveYearSurvival > currentFiveYearSurvival) {
		survivalArrowTextEdit->setTextColor(QColor(51, 255, 51));
		survivalArrowTextEdit->setText(QChar(0x25B2));
	}
	else if (newFiveYearSurvival < currentFiveYearSurvival) {
		survivalArrowTextEdit->setTextColor(QColor(255, 51, 51));
		survivalArrowTextEdit->setText(QChar(0x25BC));
	}
	else {
		survivalArrowTextEdit->setText("");
	}

	
}

void DialogSurvivalCalculator::additionalSetup(KPDGUIDashboardList * donorDashboard, KPDGUIDashboardList * candidateDashboard) {
	
	// Fill Donor Information List
	QVector<QTreeWidgetItem*> donors = donorDashboard->getDashboardItems();

	foreach(QTreeWidgetItem * d, donors) {
		KPDGUIDonorWrapper * wrapper = dynamic_cast<KPDGUIDonorWrapper *>(d);
		if (wrapper) {

			KPDGUIDonor * newDonor = wrapper->getDonor();

			QListWidgetItem * newListItem = new QListWidgetItem();
			newListItem->setText(newDonor->donorString());

			donorList->addItem(newListItem);

			donorMap.insert(newListItem, newDonor);

		}
	}

	// Fill Candidate Information List
	QVector<QTreeWidgetItem *> candidates = candidateDashboard->getDashboardItems();

	foreach(QTreeWidgetItem * c, candidates) {
		KPDGUICandidateWrapper * wrapper = dynamic_cast<KPDGUICandidateWrapper *>(c);
		if (wrapper) {

			KPDGUICandidate * newCandidate = wrapper->getCandidate();

			QListWidgetItem * newListItem = new QListWidgetItem();
			newListItem->setText(newCandidate->candidateString());

			candidateList->addItem(newListItem);

			candidateMap.insert(newListItem, newCandidate);

		}
	}

	//HLA Selecters
	QStringList hlaList = HLA_LIST.split(",");

	donorHLAA1ComboBox->addItem("");
	donorHLAA2ComboBox->addItem("");
	donorHLAB1ComboBox->addItem("");
	donorHLAB2ComboBox->addItem("");
	donorHLACW1ComboBox->addItem("");
	donorHLACW2ComboBox->addItem("");
	donorHLADQ1ComboBox->addItem("");
	donorHLADQ2ComboBox->addItem("");
	donorHLADR1ComboBox->addItem("");
	donorHLADR2ComboBox->addItem("");

	QStringList hlaAList = hlaList.filter(QRegularExpression("^A"));
	foreach(QString hla, hlaAList) {
		donorHLAA1ComboBox->addItem(hla);
		donorHLAA2ComboBox->addItem(hla);
	}

	QStringList hlaBList = hlaList.filter(QRegularExpression("^B"));
	foreach(QString hla, hlaBList) {
		if (hla != "BW4" && hla != "BW6") {
			donorHLAB1ComboBox->addItem(hla);
			donorHLAB2ComboBox->addItem(hla);
		}
	}

	QStringList hlaCWList = hlaList.filter(QRegularExpression("^CW"));
	foreach(QString hla, hlaCWList) {
		donorHLACW1ComboBox->addItem(hla);
		donorHLACW2ComboBox->addItem(hla);
	}

	QStringList hlaDQList = hlaList.filter(QRegularExpression("^DQ"));
	foreach(QString hla, hlaDQList) {
		donorHLADQ1ComboBox->addItem(hla);
		donorHLADQ2ComboBox->addItem(hla);
	}

	QStringList hlaDRList = hlaList.filter(QRegularExpression("^DR"));
	foreach(QString hla, hlaDRList) {
		if (hla != "DR51" && hla != "DR52" && hla != "DR53") {
			donorHLADR1ComboBox->addItem(hla);
			donorHLADR2ComboBox->addItem(hla);
		}
	}

	KPDGUIHLASelecter * donorHLACompleter = new KPDGUIHLASelecter(hlaList, this);
	donorHLALineEdit->setCompleter(donorHLACompleter);
	
	KPDGUIHLASelecter * candidateHLACompleter = new KPDGUIHLASelecter(hlaList, this);
	candidateHLALineEdit->setCompleter(candidateHLACompleter);
}
