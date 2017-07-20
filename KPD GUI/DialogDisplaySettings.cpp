
#include "DialogDisplaySettings.h"

#include "KPDGUIDisplaySettings.h"

//Basic Display Dialog Constructor
DialogDisplaySettings::DialogDisplaySettings(QWidget *parent) : QDialog(parent)
{
	setupUi(this);	
	displaySettingsBox->setEnabled(nodeSubsetButton->isChecked());		
}

//Display Dialog Constructor with Preset Values
DialogDisplaySettings::DialogDisplaySettings(KPDGUIDisplaySettings *displaySettings, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	nodeDisplayModeComboBox->setCurrentIndex(KPDFunctions::nodeDisplayModeToInt(displaySettings->getNodeDisplayMode()));

	//Display All Nodes
	allNodesButton->setChecked(displaySettings->getShowAllNodes());
	
	//Display Nodes in Arrangements
	showArrangementsRadioButton->setChecked(displaySettings->getShowNodesInArrangements());
	
	//Display Nodes in Solutions
	showSolutionsRadioButton->setChecked(displaySettings->getShowNodesInSolutions());
	
	//Display Node Subset
	nodeSubsetButton->setChecked(displaySettings->getShowNodeSubset());

	//Node Subset Options
	if (nodeSubsetButton->isChecked()){
		displaySettingsBox->setEnabled(true);

		showExcludedCheckBox->setChecked(displaySettings->getShowExcludedNodes());
		showIncompatibleCheckBox->setChecked(displaySettings->getShowNodesWithNoCompatibilities());
		praCheckBox->setChecked(displaySettings->getShowCandidatesInPRARange());
		praSpinBoxLeft->setValue(displaySettings->getMinPRA());
		praSpinBoxRight->setValue(displaySettings->getMaxPRA());		
	}
	else {
		displaySettingsBox->setEnabled(false);
		
		showExcludedCheckBox->setChecked(true);
		showIncompatibleCheckBox->setChecked(true);
		praCheckBox->setChecked(false);
		praSpinBoxLeft->setValue(0);
		praSpinBoxRight->setValue(100);
		
	}	
}