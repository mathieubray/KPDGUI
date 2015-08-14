#include <QtGui>

#include "DialogDisplay.h"

//Basic Display Dialog Constructor
DisplayDialog::DisplayDialog(QWidget *parent) : QDialog(parent)
{
	setupUi(this);
	
	displaySettingsBox->setEnabled(pairSubsetButton->isChecked());
		
}

//Display Dialog Constructor with Preset Values
DisplayDialog::DisplayDialog(DisplaySettingsStruct * displaySettings, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	//Display All Pairs
	allPairsButton->setChecked(displaySettings->showAllPairs);
	
	//Display Pairs in Structures
	showStructuresRadioButton->setChecked(displaySettings->showPairsInStructures);
	
	//Display Pairs in Solutions
	showSolutionsRadioButton->setChecked(displaySettings->showPairsInSolutions);
	
	//Display Pair Subset
	pairSubsetButton->setChecked(displaySettings->showPairSubset);

	//Pair Subset Options
	if (pairSubsetButton->isChecked()){
		displaySettingsBox->setEnabled(true);

		showHoldCheckBox->setChecked(displaySettings->showPairsOnHold);
		showIncompatibleCheckBox->setChecked(displaySettings->showPairsWithNoCompatibilities);
		maxPRACheckBox->setChecked(displaySettings->showPairsOfMaxPRA);
		maxPRASpinBox->setValue(displaySettings->maxPRA);
		minPRACheckBox->setChecked(displaySettings->showPairsOfMinPRA);
		minPRASpinBox->setValue(displaySettings->minPRA);
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