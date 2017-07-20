
#include "DialogCandidate.h"

#include "KPDGUICandidate.h"

//New Candidate Constructor
DialogCandidate::DialogCandidate(QWidget * parent) : QDialog(parent)
{
	setupUi(this);
	additionalSetup();
}

//Edit Candidate Constructor
DialogCandidate::DialogCandidate(KPDGUICandidate * candidate, QWidget *parent) : QDialog(parent)
{
	setupUi(this);
	additionalSetup();

	setWindowTitle("Edit - " + candidate->getName() + " (" + QString::number(candidate->getID()) + ")");

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

	//Candidate Gender
	if (candidate->getMale()) { candidateGenderComboBox->setCurrentIndex(0); }
	else { candidateGenderComboBox->setCurrentIndex(1); }
	
	//Candidate Height
	candidateHeightSpinBox->setValue(candidate->getHeight());

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

	//Candidate Insurance
	candidateInsuranceComboBox->setCurrentIndex(KPDFunctions::insuranceToInt(candidate->getInsurance()));

	//Comment
	commentTextEdit->setText(candidate->getComment());
}

void DialogCandidate::additionalSetup(){
	
	//Comment Tab
	commentTextEdit = new QTextEdit();
	moreRecipInfo->addTab(commentTextEdit, "Comments");

	//HLA Selecter
	KPDGUIHLASelecter * hlaCompleter = new KPDGUIHLASelecter(HLA_LIST.split(","), this);
	candidateHLALineEdit->setCompleter(hlaCompleter);

}