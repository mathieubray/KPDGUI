#include <QtGui>

#include "DialogMatch.h"

#include "KPDGUIMatch.h"

//New Candidate Constructor
DialogMatch::DialogMatch(QWidget * parent) : QDialog(parent)
{
	setupUi(this);
	additionalSetup();
}

//Edit Candidate Constructor
DialogMatch::DialogMatch(KPDGUIMatch * match, bool disableMajorEdits, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	donorNameLineEdit->setText(match->getDonor()->getName());
	donorBTLineEdit->setText(KPDFunctions::toString(match->getDonor()->getBT()));
	candidateNameLineEdit->setText(match->getCandidate()->getName());
	candidateBTLineEdit->setText(KPDFunctions::toString(match->getCandidate()->getBT()));
	fiveYearSurvivalLineEdit->setText(QString::number(match->getMatchFiveYearSurvivalProbability()));
	tenYearSurvivalLineEdit->setText(QString::number(match->getMatchTenYearSurvivalProbability()));
	failureProbabilitySpinBox->setValue(1 - match->getMatchSuccessProbability());
	scoreSpinBox->setValue(match->getMatchScore());
	includeCheckBox->setChecked(match->getIncludeMatchInRun());


	additionalSetup();

}

void DialogMatch::additionalSetup() {

}