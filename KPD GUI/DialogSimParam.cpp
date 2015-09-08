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

	//Max Chain Length
	chainLengthSpinBox->setValue(paramInfo.maxChainLength);
	
	//Utility Scheme
	if (paramInfo.utilScheme == "TRANSPLANTS"){
		int utilIndex = utilComboBox->findText("Transplants");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo.utilScheme == "SURVIVAL5YEAR"){
		int utilIndex = utilComboBox->findText("5 Year Survival");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo.utilScheme == "SURVIVAL10YEAR"){
		int utilIndex = utilComboBox->findText("10 Year Survival");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo.utilScheme == "SCORE"){
		int utilIndex = utilComboBox->findText("Score");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}

	//Optimization Scheme
	if (paramInfo.optScheme == "MUC"){
		int utilIndex = utilComboBox->findText("Utility");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo.optScheme == "MEUC"){
		int utilIndex = utilComboBox->findText("Expected Utility");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo.optScheme == "MEUS"){
		int utilIndex = utilComboBox->findText("Fallbacks");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	else if (paramInfo.optScheme == "SCC"){
		int utilIndex = utilComboBox->findText("Extended Fallbacks");
		if (utilIndex >= 0)
			utilComboBox->setCurrentIndex(utilIndex);
	}
	

	//Additional Checks
	praBox->setChecked(paramInfo.praAdvantage);
	reserveOtoOBox->setChecked(paramInfo.reserveOtoO);
	checkDPBox->setChecked(paramInfo.checkDP);
	compatibleBox->setChecked(paramInfo.includeCompatiblePairs);
	allowABBox->setChecked(paramInfo.includeABBridgeDonors);
	
	//Number of Solutions
	tiebreakBox->setValue(paramInfo.numberOfSolutions);
}
