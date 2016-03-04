#include <QtGui>

#include "DialogDisplaySettings.h"

#include "KPDGUIDisplaySettings.h"


//Basic Display Dialog Constructor
DialogDisplaySettings::DialogDisplaySettings(QWidget *parent) : QDialog(parent)
{
	setupUi(this);	
	displaySettingsBox->setEnabled(pairSubsetButton->isChecked());		
}

//Display Dialog Constructor with Preset Values
DialogDisplaySettings::DialogDisplaySettings(KPDGUIDisplaySettings *displaySettings, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	//Display All Pairs
	allPairsButton->setChecked(displaySettings->getShowAllPairs());
	
	//Display Pairs in Structures
	showStructuresRadioButton->setChecked(displaySettings->getShowPairsInStructures());
	
	//Display Pairs in Solutions
	showSolutionsRadioButton->setChecked(displaySettings->getShowPairsInSolutions());
	
	//Display Pair Subset
	pairSubsetButton->setChecked(displaySettings->getShowPairSubset());

	//Pair Subset Options
	if (pairSubsetButton->isChecked()){
		displaySettingsBox->setEnabled(true);

		showHoldCheckBox->setChecked(displaySettings->getShowPairsOnHold());
		showIncompatibleCheckBox->setChecked(displaySettings->getShowPairsWithNoCompatibilities());
		maxPRACheckBox->setChecked(displaySettings->getShowPairsOfMaxPRA());
		maxPRASpinBox->setValue(displaySettings->getMaxPRA());
		minPRACheckBox->setChecked(displaySettings->getShowPairsOfMinPRA());
		minPRASpinBox->setValue(displaySettings->getMinPRA());
	}
	else {
		displaySettingsBox->setEnabled(false);
		
		showHoldCheckBox->setChecked(true);
		showIncompatibleCheckBox->setChecked(true);
		maxPRACheckBox->setChecked(false);
		maxPRASpinBox->setValue(100);
		minPRACheckBox->setChecked(false);
		minPRASpinBox->setValue(0);
	}
	
}