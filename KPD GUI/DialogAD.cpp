#include <QtGui>

#include "DialogAD.h"

//New AD Constructor
AltruisticDonorDialog::AltruisticDonorDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
}

//Edit AD Constructor
AltruisticDonorDialog::AltruisticDonorDialog(int id, Donor * donor, QString comment, bool disableMajorEdits, QWidget *parent) : QDialog(parent)
{
	setupUi(this);
	
	setWindowTitle("Edit AD Information - " + QString::number(id));

	//Name
	donorNameLineEdit->setText(donor->name);

	//Age
	donorAgeSpinBox->setValue(donor->age);

	//Blood Type
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

	//Gender
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

	//Weight
	donorWeightSpinBox->setValue(donor->weight);

	//HLA
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
	}

	//Comments
	commentTextEdit->setText(comment);
}