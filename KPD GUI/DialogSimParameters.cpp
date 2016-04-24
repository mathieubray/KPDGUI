#include <QtGui>

#include "DialogSimParameters.h"

#include "KPDGUISimParameters.h"


//Basic Simulation Parameter Dialog Constructor
DialogSimParameters::DialogSimParameters(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
}

//Saved Parameters Dialog Constructor
DialogSimParameters::DialogSimParameters(KPDGUISimParameters *paramInfo, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	//Optimization Scheme
	optComboBox->setCurrentIndex(KPDFunctions::optSchemeToInt(paramInfo->getOptimizationScheme()));
	if (paramInfo->getOptimizationScheme() == SCC){
		componentSizeSpinBox->setEnabled(true);
		componentSizeSlider->setEnabled(true);
		estimateEUCheckBox->setEnabled(true);
		numberOfEUSimSpinBox->setEnabled(true);
	}

	//Utility Scheme
	utilComboBox->setCurrentIndex(KPDFunctions::utilSchemeToInt(paramInfo->getUtilityScheme()));
	
	//Max Chain Length
	cycleSizeSpinBox->setValue(paramInfo->getMaxCycleSize());
	chainLengthSpinBox->setValue(paramInfo->getMaxChainLength());
	componentSizeSpinBox->setValue(paramInfo->getMaxComponentSize());
	
	//Numerical Parameters
	praCheckBox->setChecked(paramInfo->getAddAdvantageToHighPRACandidates());
	if (paramInfo->getAddAdvantageToHighPRACandidates()){
		praCutoffSpinBox->setValue(paramInfo->getPRAAdvantageCutoff());
		praAdvantageSpinBox->setValue(paramInfo->getPRAAdvantageValue());
	}
	else {
		praCutoffSpinBox->setValue(100);
		praAdvantageSpinBox->setValue(0);
	}

	solutionsSpinBox->setValue(paramInfo->getNumberOfSolutions());

	estimateEUCheckBox->setChecked(paramInfo->getEstimateExpectedUtility());
	numberOfEUSimSpinBox->setValue(paramInfo->getNumberOfExpectedUtilityIterations());

	//Additional Options
	chainStorageComboBox->setCurrentIndex(KPDFunctions::chainStorageToInt(paramInfo->getChainStorage()));	
	reserveOtoOBox->setChecked(paramInfo->getReserveODonorsForOCandidates());
	checkAdditionalHLABox->setChecked(paramInfo->getCheckAdditionalHLA());
	compatibleBox->setChecked(paramInfo->getIncludeCompatiblePairs());
	excludeABDonorsBox->setChecked(paramInfo->getExcludeABDonorsFromSimulation());
	allowABBridgeBox->setChecked(paramInfo->getAllowABBridgeDonors());
	
}

void DialogSimParameters::enableComponentOptions(int index) {
	if (index == 3) {
		componentSizeSpinBox->setEnabled(true);
		componentSizeSlider->setEnabled(true);
		estimateEUCheckBox->setEnabled(true);
		numberOfEUSimSpinBox->setEnabled(true);

	}
	else {
		componentSizeSpinBox->setEnabled(false);
		componentSizeSlider->setEnabled(false);
		estimateEUCheckBox->setEnabled(false);
		numberOfEUSimSpinBox->setEnabled(false);
	}
}

void DialogSimParameters::enablePRAOptions(bool enabled){
	praCutoffSpinBox->setEnabled(enabled);
	praAdvantageSpinBox->setEnabled(enabled);
}

void DialogSimParameters::enableBridgeDonorOptions(bool enabled){
	allowABBridgeBox->setEnabled(!enabled);
}


