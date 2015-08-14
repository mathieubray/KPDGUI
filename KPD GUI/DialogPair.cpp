#include <QtGui>

#include "DialogPair.h"

//New Pair Constructor
PairDialog::PairDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
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
	
	//Recipient Sensitized
	recipSensitizedCheckBox->setChecked(candidate->sensitized);
	
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

	//Comment
	commentTextEdit->setText(comment);

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
		recipSensitizedCheckBox->setEnabled(false);
	}

}