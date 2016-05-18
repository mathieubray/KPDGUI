#include <QtGui>

#include "DialogPair.h"

//New Pair Constructor
PairDialog::PairDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
	additionalSetup();
}

//Edit Pair Constructor
PairDialog::PairDialog(int id, Donor * donor, Candidate * candidate, QString comment, bool disableMajorEdits, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	setWindowTitle("Edit Pair Information - " + QString::number(id));

	//Donor Name
	donorNameLineEdit->setText(donor->name);
	
	//Donor Age
	donorAgeSpinBox->setValue(donor->age);
	
	//Donor Blood Type
	if (donor->BT == "O"){
		int btIndex = donorBTComboBox->findText("O");
		if (btIndex >= 0){
			donorBTComboBox->setCurrentIndex(btIndex);
		}
	}
	else if (donor->BT == "A"){
		int btIndex = donorBTComboBox->findText("A");
		if (btIndex >= 0){
			donorBTComboBox->setCurrentIndex(btIndex);
		}
	}
	else if (donor->BT == "B"){
		int btIndex = donorBTComboBox->findText("B");
		if (btIndex >= 0){
			donorBTComboBox->setCurrentIndex(btIndex);
		}
	}
	else if (donor->BT == "AB"){
		int btIndex = donorBTComboBox->findText("AB");
		if (btIndex >= 0){
			donorBTComboBox->setCurrentIndex(btIndex);
		}
	}

	//Donor Gender
	if (donor->genderMale == true){
		int genderIndex = donorGenderComboBox->findText("Male");
		if (genderIndex >= 0){
			donorGenderComboBox->setCurrentIndex(genderIndex);
		}
	}
	else {
		int genderIndex = donorGenderComboBox->findText("Female");
		if (genderIndex >= 0){
			donorGenderComboBox->setCurrentIndex(genderIndex);
		}
	}

	//Donor Height
	double donorHeight = sqrt(donor->weight / ( donor->BMI));
	donorHeightSpinBox->setValue(donorHeight);

	//Donor Weight
	donorWeightSpinBox->setValue(donor->weight);

	//Donor HLA
	if (donor->donorA.size() >= 1){
		donorA1LineEdit->setText(donor->donorA[0]);
		if (donor->donorA.size() >= 2){
			donorA2LineEdit->setText(donor->donorA[1]);
		}
	}
	if (donor->donorB.size() >= 1){
		donorB1lineEdit->setText(donor->donorB[0]);
		if (donor->donorB.size() >= 2){
			donorB2LineEdit->setText(donor->donorB[1]);
		}
	}
	if (donor->donorCW.size() >= 1){
		donorCW1LineEdit->setText(donor->donorCW[0]);
		if (donor->donorCW.size() >= 2){
			donorCW2LineEdit->setText(donor->donorCW[1]);
		}
	}
	if (donor->donorDP.size() >= 1){
		donorDP1LineEdit->setText(donor->donorDP[0]);
		if (donor->donorDP.size() >= 2){
			donorDP2LineEdit->setText(donor->donorDP[1]);
		}
	}
	if (donor->donorDQ.size() >= 1){
		donorDQ1LineEdit->setText(donor->donorDQ[0]);
		if (donor->donorDQ.size() >= 2){
			donorDQ2LineEdit->setText(donor->donorDQ[1]);
		}
	}
	if (donor->donorDR.size() >= 1){
		donorDR1LineEdit->setText(donor->donorDR[0]);
		if (donor->donorDR.size() >= 2){
			donorDR2LineEdit->setText(donor->donorDR[1]);
		}
	}
	donorBW4CheckBox->setChecked(donor->donorBW4);
	donorBW6CheckBox->setChecked(donor->donorBW6);
	donorDR51CheckBox->setChecked(donor->donorDR51);
	donorDR52CheckBox->setChecked(donor->donorDR52);
	donorDR53CheckBox->setChecked(donor->donorDR53);

	//Recipient Name
	recipNameLineEdit->setText(candidate->name); 
	
	//Recipient Age
	recipAgeSpinBox->setValue(candidate->age);
	
	//Recipient Blood Type
	if (candidate->BT == "O"){
		int btIndex = recipBTComboBox->findText("O");
		if (btIndex >= 0){
			recipBTComboBox->setCurrentIndex(btIndex);
		}
	}
	else if (candidate->BT == "A"){
		int btIndex = recipBTComboBox->findText("A");
		if (btIndex >= 0){
			recipBTComboBox->setCurrentIndex(btIndex);
		}
	}
	else if (candidate->BT == "B"){
		int btIndex = recipBTComboBox->findText("B");
		if (btIndex >= 0){
			recipBTComboBox->setCurrentIndex(btIndex);
		}
	}
	else if (candidate->BT == "AB"){
		int btIndex = recipBTComboBox->findText("AB");
		if (btIndex >= 0){
			recipBTComboBox->setCurrentIndex(btIndex);
		}
	}

	//Recipient Gender
	if (candidate->genderMale == true){
		int genderIndex = donorGenderComboBox->findText("Male");
		if (genderIndex >= 0){
			donorGenderComboBox->setCurrentIndex(genderIndex);
		}
	}
	else {
		int genderIndex = donorGenderComboBox->findText("Female");
		if (genderIndex >= 0){
			donorGenderComboBox->setCurrentIndex(genderIndex);
		}
	}

	//Recipient Height
	double recipHeight = sqrt(candidate->weight/( candidate->BMI));
	recipHeightSpinBox->setValue(recipHeight);

	//Recipient Weight
	recipWeightSpinBox->setValue(candidate->weight);

	//Recipient PRA
	recipPRASpinBox->setValue(candidate->pra);
	
	//Recipient Diabetes
	recipDiabetesCheckBox->setChecked(candidate->diabetes);
	
	//Recipient Hepatitis C
	recipHepCCheckBox->setChecked(candidate->hepC);
	
	//Recipient Race
	if (candidate->race == "White"){
		int raceIndex = recipRaceComboBox->findText("White");
		if (raceIndex >= 0){
			recipRaceComboBox->setCurrentIndex(raceIndex);
		}
	}
	else if (candidate->race == "Black"){
		int raceIndex = recipRaceComboBox->findText("Black");
		if (raceIndex >= 0){
			recipRaceComboBox->setCurrentIndex(raceIndex);
		}
	}
	else if (candidate->race == "Hispanic"){
		int raceIndex = recipRaceComboBox->findText("Hispanic");
		if (raceIndex >= 0){
			recipRaceComboBox->setCurrentIndex(raceIndex);
		}
	}
	else if (candidate->race == "Other"){
		int raceIndex = recipRaceComboBox->findText("Other");
		if (raceIndex >= 0){
			recipRaceComboBox->setCurrentIndex(raceIndex);
		}
	}

	//Recipient Time On Dialysis
	recipTODSpinBox->setValue(candidate->TOD);

	//Recipient Previous Transplant
	recipPrevTransCheckBox->setChecked(candidate->prevTrans);
	
	//Recipient HLA
	QString antibodyString = "";
	foreach(QString antibody, candidate->antibodies){
		antibodyString.append(antibody);
		antibodyString.append(";");
	}
	antibodyString.chop(1);
	recipHLALineEdit->setText(antibodyString);

	if (disableMajorEdits){
		donorBTComboBox->setEnabled(false);

		donorA1LineEdit->setEnabled(false);
		donorA2LineEdit->setEnabled(false);

		donorB1lineEdit->setEnabled(false);
		donorB2LineEdit->setEnabled(false);
		donorCW1LineEdit->setEnabled(false);
		donorCW2LineEdit->setEnabled(false);
		donorDP1LineEdit->setEnabled(false);
		donorDP2LineEdit->setEnabled(false);
		donorDQ1LineEdit->setEnabled(false);
		donorDQ2LineEdit->setEnabled(false);
		donorDR1LineEdit->setEnabled(false);
		donorDR2LineEdit->setEnabled(false);

		donorBW4CheckBox->setEnabled(false);
		donorBW6CheckBox->setEnabled(false);
		donorDR51CheckBox->setEnabled(false);
		donorDR52CheckBox->setEnabled(false);
		donorDR53CheckBox->setEnabled(false);

		donorHLALineEdit->setEnabled(false);

		recipBTComboBox->setEnabled(false);
		recipPRASpinBox->setEnabled(false);
		praSlider->setEnabled(false);

		recipHLALineEdit->setEnabled(false);		
	}

	//Comment
	commentTextEdit->setText(comment);

	additionalSetup();

}

void PairDialog::additionalSetup() {
	//HLA Completers
	QString hla = "A1,A2,A3,A9,A10,A11,A19,A23,A24,A25,A26,A28,A29,A30,A31,A32,A33,A34,A36,A43,A66,A68,A69,A74,A80,A203,A210,A2403,A6601,A6602,B5,B7,B8,B12,B13,B14,B15,B16,B17,B18,B21,B22,B27,B35,B37,B38,B39,B40,B41,B42,B44,B45,B46,B47,B48,B49,B50,B51,B52,B53,B54,B55,B56,B57,B58,B59,B60,B61,B62,B63,B64,B65,B67,B70,B71,B72,B73,B75,B76,B77,B78,B81,B82,B703,B804,B1304,B2708,B3901,B3902,B3905,B4005,B5102,B5103,B8201,BW4,BW6,CW1,CW2,CW3,CW4,CW5,CW6,CW7,CW8,CW9,CW10,CW12,CW13,CW14,CW15,CW16,CW17,CW18,DQ1,DQ2,DQ3,DQ4,DQ5,DQ6,DQ7,DQ8,DQ9,DQB1,DQB2,DQB3,DQB4,DQB5,DQB6,DQB7,DQB8,DQB9,DR1,DR2,DR3,DR4,DR5,DR6,DR7,DR8,DR9,DR10,DR11,DR12,DR13,DR14,DR15,DR16,DR17,DR18,DR103,DR1403,DR1404,DR51,DR52,DR53";
	QStringList hlaList = hla.split(",");
	
	QStringList hlaAList = hlaList.filter(QRegularExpression("^A"));
	donorA1LineEdit->setCompleter(new MultiSelectCompleter(hlaAList,this));
	donorA2LineEdit->setCompleter(new MultiSelectCompleter(hlaAList,this));
	
	QStringList hlaBList = hlaList.filter(QRegularExpression("^B"));
	hlaBList.removeAt(hlaBList.indexOf("BW4"));
	hlaBList.removeAt(hlaBList.indexOf("BW6"));
	donorB1lineEdit->setCompleter(new MultiSelectCompleter(hlaBList, this));
	donorB2LineEdit->setCompleter(new MultiSelectCompleter(hlaBList, this));
	
	QStringList hlaCWList = hlaList.filter(QRegularExpression("^CW"));
	donorCW1LineEdit->setCompleter(new MultiSelectCompleter(hlaCWList, this));
	donorCW2LineEdit->setCompleter(new MultiSelectCompleter(hlaCWList, this));
	

	QStringList hlaDQList = hlaList.filter(QRegularExpression("^DQ"));
	donorDQ1LineEdit->setCompleter(new MultiSelectCompleter(hlaDQList, this));
	donorDQ2LineEdit->setCompleter(new MultiSelectCompleter(hlaDQList, this));
	

	QStringList hlaDRList = hlaList.filter(QRegularExpression("^DR"));
	hlaDRList.removeAt(hlaDRList.indexOf("DR51"));
	hlaDRList.removeAt(hlaDRList.indexOf("DR52"));
	hlaDRList.removeAt(hlaDRList.indexOf("DR53"));
	donorDR1LineEdit->setCompleter(new MultiSelectCompleter(hlaDRList, this));
	donorDR2LineEdit->setCompleter(new MultiSelectCompleter(hlaDRList, this));

	donorHLALineEdit->setCompleter(new MultiSelectCompleter(hlaList, this));
	recipHLALineEdit->setCompleter(new MultiSelectCompleter(hlaList, this));
}