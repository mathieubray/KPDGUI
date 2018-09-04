
#include "DialogSimParameters.h"

#include "KPDGUIParameters.h"


//Basic Simulation Parameter Dialog Constructor
DialogSimParameters::DialogSimParameters(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
}

//Saved Parameters Dialog Constructor
DialogSimParameters::DialogSimParameters(KPDGUIParameters *paramInfo, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	saveSolutionCheckBox->setChecked(paramInfo->getSaveSolution());
	folderLineEdit->setText(paramInfo->getSaveSolutionFolder());

	highlightTopSolutionCheckBox->setChecked(paramInfo->getHighlightTopSolution());

	collectArrangementsCheckBox->setChecked(paramInfo->getCollectArrangements());
	collectArrangementsSpinBox->setValue(paramInfo->getCollectArrangementsCutoff());	

	// Simulation Settings
	optComboBox->setCurrentIndex(KPDFunctions::optSchemeToInt(paramInfo->getOptimizationScheme()));
	
	enableOptimizationOptions(optComboBox->currentIndex());

	utilComboBox->setCurrentIndex(KPDFunctions::utilSchemeToInt(paramInfo->getUtilityScheme()));
	
	cycleSizeSpinBox->setValue(paramInfo->getMaxCycleSize());
	chainLengthSpinBox->setValue(paramInfo->getMaxChainLength());
	lrsSizeSpinBox->setValue(paramInfo->getMaxLRSSize());

	solutionsSpinBox->setValue(paramInfo->getNumberOfSolutions());

	
	//Additional Options
	praCheckBox->setChecked(paramInfo->addAdvantageToHighPRACandidates());
	if (paramInfo->addAdvantageToHighPRACandidates()){
		praCutoffSpinBox->setValue(paramInfo->getPRAAdvantageCutoff());
		praAdvantageSpinBox->setValue(paramInfo->getPRAAdvantageValue());
	}
	else {
		praCutoffSpinBox->setValue(100);
		praAdvantageSpinBox->setValue(0);
	}
	
	enablePRAOptions(praCheckBox->isChecked());

	estimateEUCheckBox->setChecked(paramInfo->estimateExpectedUtility());
	numberOfEUSimSpinBox->setValue(paramInfo->getNumberOfExpectedUtilityIterations());
	
	enableEstimateEUOptions(estimateEUCheckBox->isChecked());

	reserveOtoOBox->setChecked(paramInfo->reserveODonorsForOCandidates());
	checkAdditionalHLABox->setChecked(paramInfo->checkAdditionalHLA());
	compatibleBox->setChecked(paramInfo->includeCompatiblePairs());
	excludeABDonorsBox->setChecked(paramInfo->excludeABDonorsFromSimulation());
	allowABBridgeBox->setChecked(paramInfo->allowABBridgeDonors());
	
	enableBridgeDonorOptions(excludeABDonorsBox->isChecked());
	
}

void DialogSimParameters::browse() {
	
	QString folderName = QFileDialog::getExistingDirectory(this, "Open Folder", "", QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);
	folderLineEdit->setText(folderName);
	
}

// Change settings based on optimization scheme
void DialogSimParameters::enableOptimizationOptions(int index) {	

	if (index==0) {
		lrsSizeSpinBox->setEnabled(false);
		lrsSizeSlider->setEnabled(false);
		estimateEUCheckBox->setEnabled(false);
	}

	if (index == 1) {
		lrsSizeSpinBox->setEnabled(false);
		lrsSizeSlider->setEnabled(false);
		estimateEUCheckBox->setEnabled(true);
	}
	
	if (index == 2) {
		lrsSizeSpinBox->setEnabled(true);
		lrsSizeSlider->setEnabled(true);
		estimateEUCheckBox->setEnabled(true);
	}

	enableEstimateEUOptions(estimateEUCheckBox->isEnabled() && estimateEUCheckBox->isChecked());
}

// Change settings based on whether PRA advantage is specified
void DialogSimParameters::enablePRAOptions(bool enabled){
	praCutoffSpinBox->setEnabled(enabled);
	praAdvantageSpinBox->setEnabled(enabled);
}

// Change settings based on whether AB donors are allowed in the match run
void DialogSimParameters::enableBridgeDonorOptions(bool enabled){
	allowABBridgeBox->setEnabled(!enabled);
}

// Change settings based on whether expected utility estimation is specified
void DialogSimParameters::enableEstimateEUOptions(bool enabled) {
	numberOfEUSimSpinBox->setEnabled(enabled);
}


