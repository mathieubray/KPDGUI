#include <QtGui>

#include "DialogSimParam.h"

//Basic Simulation Parameter Dialog Constructor
SimParamDialog::SimParamDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
}

//Saved Parameters Dialog Constructor
SimParamDialog::SimParamDialog(ParamInfoStruct paramInfo, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	//Optimization Scheme
	if (paramInfo.optScheme == KPDOptimizationScheme::MUC){
		int utilIndex = utilComboBox->findText("Utility");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo.optScheme == KPDOptimizationScheme::MEUC){
		int utilIndex = utilComboBox->findText("Expected Utility");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo.optScheme == KPDOptimizationScheme::MEUS){
		int utilIndex = utilComboBox->findText("Fallbacks");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo.optScheme == KPDOptimizationScheme::SCC){
		int utilIndex = utilComboBox->findText("Extended Fallbacks");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}

	//Utility Scheme
	if (paramInfo.utilityScheme == KPDUtilityScheme::TRANSPLANTS){
		int utilIndex = utilComboBox->findText("Transplants");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo.utilityScheme == KPDUtilityScheme::SURVIVAL5YEAR){
		int utilIndex = utilComboBox->findText("5 Year Survival");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo.utilityScheme == KPDUtilityScheme::SURVIVAL10YEAR){
		int utilIndex = utilComboBox->findText("10 Year Survival");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo.utilityScheme == KPDUtilityScheme::SCORE){
		int utilIndex = utilComboBox->findText("Score");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}

	//Max Chain Length
	chainLengthSpinBox->setValue(paramInfo.maxChainLength);

	//Numerical Parameters
	pairFailureRateSpinBox->setValue(paramInfo.pairFailureRate);
	adFailureRateSpinBox->setValue(paramInfo.adFailureRate);
	exogenousFailureRateSpinBox->setValue(paramInfo.exogenousFailureRate);

	praBox->setChecked(paramInfo.addAdvantageToHighPRACandidates);
	if (paramInfo.addAdvantageToHighPRACandidates){
		praCutoffSpinBox->setValue(paramInfo.praAdvantageCutoff);
		praAdvantageSpinBox->setValue(paramInfo.praAdvantageValue);
	}
	else {
		praCutoffSpinBox->setValue(100);
		praAdvantageSpinBox->setValue(0);
	}

	solutionsSpinBox->setValue(paramInfo.numberOfSolutions);

	//Additional Options
	
	if (paramInfo.chainStorage == "NONE"){
		int chainStorageIndex = chainStorageComboBox->findText("As They Are Found");
		if (chainStorageIndex >= 0)
			chainStorageComboBox->setCurrentIndex(chainStorageIndex);
	}
	else if (paramInfo.chainStorage == "FIRST"){
		int chainStorageIndex = chainStorageComboBox->findText("First");
		if (chainStorageIndex >= 0)
			chainStorageComboBox->setCurrentIndex(chainStorageIndex);
	}
	else if (paramInfo.chainStorage == "LAST"){
		int chainStorageIndex = chainStorageComboBox->findText("Last");
		if (chainStorageIndex >= 0)
			chainStorageComboBox->setCurrentIndex(chainStorageIndex);
	}

	reserveOtoOBox->setChecked(paramInfo.reserveODonorsForOCandidates);
	checkDPBox->setChecked(paramInfo.checkDP);
	compatibleBox->setChecked(paramInfo.includeCompatiblePairs);
	excludeABDonorsBox->setChecked(paramInfo.excludeABDonorsFromSimulation);
	allowABBridgeBox->setChecked(paramInfo.allowABBridgeDonors);
	
}

void SimParamDialog::enablePRAOptions(bool enabled){
	praCutoffSpinBox->setEnabled(enabled);
	praAdvantageSpinBox->setEnabled(enabled);
}

void SimParamDialog::enableBridgeDonorOptions(bool enabled){
	allowABBridgeBox->setEnabled(!enabled);
}
