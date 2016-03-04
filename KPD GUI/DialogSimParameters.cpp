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
		sizeLabel->setText("Maximum Component Size");
	}
	/*if (paramInfo->getOptimizationScheme() == KPDOptimizationScheme::MUC){
		int optIndex = optComboBox->findText("Utility");
		if (optIndex >= 0)
			optComboBox->setCurrentIndex(optIndex);
	}
	else if (paramInfo->getOptimizationScheme() == KPDOptimizationScheme::MEUC){
		int optIndex = optComboBox->findText("Expected Utility");
		if (optIndex >= 0)
			optComboBox->setCurrentIndex(optIndex);
	}
	else if (paramInfo->getOptimizationScheme() == KPDOptimizationScheme::MEUS){
		int optIndex = optComboBox->findText("Fallbacks");
		if (optIndex >= 0)
			optComboBox->setCurrentIndex(optIndex);
	}
	else if (paramInfo->getOptimizationScheme() == KPDOptimizationScheme::SCC){
		int optIndex = optComboBox->findText("Extended Fallbacks");
		if (optIndex >= 0){
			optComboBox->setCurrentIndex(optIndex);
			sizeLabel->setText("Maximum Component Size");
		}
	}*/

	//Utility Scheme
	utilComboBox->setCurrentIndex(KPDFunctions::utilSchemeToInt(paramInfo->getUtilityScheme()));
	/*if (paramInfo->getUtilityScheme() == KPDUtilityScheme::TRANSPLANTS){
		int utilIndex = utilComboBox->findText("Transplants");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo->getUtilityScheme() == KPDUtilityScheme::SURVIVAL5YEAR){
		int utilIndex = utilComboBox->findText("5 Year Survival");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo->getUtilityScheme() == KPDUtilityScheme::SURVIVAL10YEAR){
		int utilIndex = utilComboBox->findText("10 Year Survival");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo->getUtilityScheme() == KPDUtilityScheme::SCORE){
		int utilIndex = utilComboBox->findText("Score");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}*/

	//Max Chain Length
	sizeSpinBox->setValue(paramInfo->getMaxSize());

	//Numerical Parameters
	pairFailureRateSpinBox->setValue(paramInfo->getPairFailureRate());
	adFailureRateSpinBox->setValue(paramInfo->getADFailureRate());
	exogenousFailureRateSpinBox->setValue(paramInfo->getExogenousFailureRate());

	praBox->setChecked(paramInfo->getAddAdvantageToHighPRACandidates());
	if (paramInfo->getAddAdvantageToHighPRACandidates()){
		praCutoffSpinBox->setValue(paramInfo->getPRAAdvantageCutoff());
		praAdvantageSpinBox->setValue(paramInfo->getPRAAdvantageValue());
	}
	else {
		praCutoffSpinBox->setValue(100);
		praAdvantageSpinBox->setValue(0);
	}

	solutionsSpinBox->setValue(paramInfo->getNumberOfSolutions());
	euSimSpinBox->setValue(paramInfo->getNumberOfEUSimulations());

	//Additional Options
	chainStorageComboBox->setCurrentIndex(KPDFunctions::chainStorageToInt(paramInfo->getChainStorage()));
	/*if (paramInfo->getChainStorage() == "NONE"){
		int chainStorageIndex = chainStorageComboBox->findText("As They Are Found");
		if (chainStorageIndex >= 0)
			chainStorageComboBox->setCurrentIndex(chainStorageIndex);
	}
	else if (paramInfo->getChainStorage() == "FIRST"){
		int chainStorageIndex = chainStorageComboBox->findText("First");
		if (chainStorageIndex >= 0)
			chainStorageComboBox->setCurrentIndex(chainStorageIndex);
	}
	else if (paramInfo->getChainStorage() == "LAST"){
		int chainStorageIndex = chainStorageComboBox->findText("Last");
		if (chainStorageIndex >= 0)
			chainStorageComboBox->setCurrentIndex(chainStorageIndex);
	}*/

	reserveOtoOBox->setChecked(paramInfo->getReserveODonorsForOCandidates());
	checkAdditionalHLABox->setChecked(paramInfo->getCheckAdditionalHLA());
	compatibleBox->setChecked(paramInfo->getIncludeCompatiblePairs());
	excludeABDonorsBox->setChecked(paramInfo->getExcludeABDonorsFromSimulation());
	allowABBridgeBox->setChecked(paramInfo->getAllowABBridgeDonors());
	
}

void DialogSimParameters::enablePRAOptions(bool enabled){
	praCutoffSpinBox->setEnabled(enabled);
	praAdvantageSpinBox->setEnabled(enabled);
}

void DialogSimParameters::enableBridgeDonorOptions(bool enabled){
	allowABBridgeBox->setEnabled(!enabled);
}

void DialogSimParameters::changeLabel(int index){
	if (index == 3){		
		sizeLabel->setText("Maximum Component Size");
		euSimSpinBox->setEnabled(true);
	}
	else {
		sizeLabel->setText("Maximum Chain Length");
		euSimSpinBox->setEnabled(false);
	}	
}
