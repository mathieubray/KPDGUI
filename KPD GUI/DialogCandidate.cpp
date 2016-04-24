#include <QtGui>

#include "DialogCandidate.h"

#include "KPDGUICandidate.h"

#include "MultiSelectCompleter.h"

//New Candidate Constructor
DialogCandidate::DialogCandidate(QWidget * parent) : QDialog(parent)
{
	setupUi(this);
	additionalSetup();
}

//Edit Candidate Constructor
DialogCandidate::DialogCandidate(KPDGUICandidate * candidate, bool disableMajorEdits, QWidget *parent) : QDialog(parent)
{
	setupUi(this);
	additionalSetup();

	setWindowTitle("Edit Candidate Information");

	//Candidate Name
	candidateNameLineEdit->setText(candidate->getName());

	//Candidate Age
	candidateAgeSpinBox->setValue(candidate->getAge());

	//Candidate Blood Type
	candidateBTComboBox->setCurrentIndex(KPDFunctions::bloodTypeToInt(candidate->getBT()));

	//Candidate PRA
	candidatePRASpinBox->setValue(candidate->getPRA());

	//Candidate Failure Probability
	candidateFailureProbabilitySpinBox->setValue(candidate->getFailureProbability());

	//Candidate Status
	candidateStatusCheckBox->setChecked(candidate->getStatus());

	//Candidate HLA
	QString antibodyString = "";
	foreach(QString antibody, candidate->getHLA()) {
		antibodyString.append(antibody);
		antibodyString.append(";");
	}
	antibodyString.chop(1);
	candidateHLALineEdit->setText(antibodyString);

	

	//Excluded Donors
	QString excludedDonorsString = "";
	foreach(int donor, candidate->getExcludedDonors()){
		excludedDonorsString.append(QString::number(donor));
		excludedDonorsString.append(";");
	}
	excludedDonorsString.chop(1);
	excludedDonorLineEdit->setText(excludedDonorsString);

	//Candidate Gender
	if (candidate->getMale()) { candidateGenderComboBox->setCurrentIndex(0); }
	else { candidateGenderComboBox->setCurrentIndex(1); }
	
	//Candidate Height
	double candidateHeight = sqrt(candidate->getWeight() / (candidate->getBMI()));
	candidateHeightSpinBox->setValue(candidateHeight);

	//Candidate Weight
	candidateWeightSpinBox->setValue(candidate->getWeight());

	//Candidate Diabetes
	candidateDiabetesCheckBox->setChecked(candidate->getDiabetes());

	//Candidate Hepatitis C
	candidateHepCCheckBox->setChecked(candidate->getHepC());

	//Candidate Race
	candidateRaceComboBox->setCurrentIndex(KPDFunctions::raceToInt(candidate->getRace()));
	
	//Candidate Time On Dialysis
	candidateTODSpinBox->setValue(candidate->getTOD());

	//Candidate Previous Transplant
	candidatePrevTransCheckBox->setChecked(candidate->getPrevTrans());	

	if (disableMajorEdits){

		candidateBTComboBox->setEnabled(false);
		candidatePRASpinBox->setEnabled(false);
		praSlider->setEnabled(false);

		excludedDonorLineEdit->setEnabled(false);
		candidateHLALineEdit->setEnabled(false);
	}

	//Comment
	commentTextEdit->setText(candidate->getComment());
}

void DialogCandidate::additionalSetup(){
	
	//Comment Tab
	commentTextEdit = new QTextEdit();
	moreRecipInfo->addTab(commentTextEdit, "Comments");

	//HLA Completer
	QString hla = "A1,A2,A3,A9,A10,A11,A19,A23,A24,A25,A26,A28,A29,A30,A31,A32,A33,A34,A36,A43,A66,A68,A69,A74,A80,A203,A210,A2403,A6601,A6602,B5,B7,B8,B12,B13,B14,B15,B16,B17,B18,B21,B22,B27,B35,B37,B38,B39,B40,B41,B42,B44,B45,B46,B47,B48,B49,B50,B51,B52,B53,B54,B55,B56,B57,B58,B59,B60,B61,B62,B63,B64,B65,B67,B70,B71,B72,B73,B75,B76,B77,B78,B81,B82,B703,B804,B1304,B2708,B3901,B3902,B3905,B4005,B5102,B5103,B8201,BW4,BW6,CW1,CW2,CW3,CW4,CW5,CW6,CW7,CW8,CW9,CW10,CW12,CW13,CW14,CW15,CW16,CW17,CW18,DQ1,DQ2,DQ3,DQ4,DQ5,DQ6,DQ7,DQ8,DQ9,DQB1,DQB2,DQB3,DQB4,DQB5,DQB6,DQB7,DQB8,DQB9,DR1,DR2,DR3,DR4,DR5,DR6,DR7,DR8,DR9,DR10,DR11,DR12,DR13,DR14,DR15,DR16,DR17,DR18,DR103,DR1403,DR1404,DR51,DR52,DR53";
	QStringList hlaList = hla.split(",");

	MultiSelectCompleter * hlaCompleter = new MultiSelectCompleter(hlaList, this);

	candidateHLALineEdit->setCompleter(hlaCompleter);

}