
#include "DialogMatch.h"

#include "KPDGUIMatch.h"

// New Match
DialogMatch::DialogMatch(QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	additionalInformationButton->setVisible(false);

	additionalInformation = false;
}

// Edit Match
DialogMatch::DialogMatch(KPDGUIMatch * match, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	setWindowTitle("Edit Match: " + match->getDonor()->getName() + " - " + match->getCandidate()->getName());

	//Donor Name
	donorLineEdit->setText(match->getDonor()->getName());
	
	//Candidate Name
	candidateLineEdit->setText(match->getCandidate()->getName());

	//Crossmatch Result
	crossmatchLineEdit->setText(KPDFunctions::toString(match->getCrossmatchResult()));

	//Include in Match Run
	includeCheckBox->setChecked(match->getInclude());

	//Five Year Survival
	fiveYearSurvivalLineEdit->setText(QString::number(floor(match->getFiveYearSurvival() * 1000 + 0.5) / 1000));
	
	//Ten Year Survival
	tenYearSurvivalLineEdit->setText(QString::number(floor(match->getTenYearSurvival() * 1000 + 0.5) / 1000));

	//Failure Probability
	probabilitySpinBox->setValue(match->getFailureProbability());

	//Assigned Transplant Score
	scoreSpinBox->setValue(match->getAssignedUtility());

	//Match Difficulty
	difficultToMatchBox->setChecked(match->getTransplantScore() == 1);


	additionalInformation = false;
}

bool DialogMatch::getAdditionalInformation() {
	return (additionalInformation);
}

void DialogMatch::setAdditionalInformation() {
	additionalInformation = true;
}


