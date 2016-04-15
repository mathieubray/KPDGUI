
#include "KPDGUIDisplaySettings.h"

KPDGUIDisplaySettings::KPDGUIDisplaySettings(){
	showAllNodes = true;
	showNodeSubset = false;
	showNodesInSolutions = false;
	showNodesInStructures = false;
	showNodesOnHold = true;
	showNodesWithNoCompatibilities = true;
	showCandidatesInPRARange = false;

	minPRA = 0;
	maxPRA = 100;

	matchDisplayMode = WITHIN_SELECTION;
}

KPDGUIDisplaySettings::~KPDGUIDisplaySettings(){

}

bool KPDGUIDisplaySettings::changeDisplaySettings(DialogDisplaySettings * d){

	showAllNodes = d->allNodesButton->isChecked();
	showNodeSubset = d->nodeSubsetButton->isChecked();
	showNodesInStructures = d->showStructuresRadioButton->isChecked();
	showNodesInSolutions = d->showSolutionsRadioButton->isChecked();
	showNodesOnHold = d->showHoldCheckBox->isChecked();
	showNodesWithNoCompatibilities = d->showIncompatibleCheckBox->isChecked();
	showCandidatesInPRARange = d->praCheckBox->isChecked();

	int leftPRAVal = d->praSpinBoxLeft->value();
	int rightPRAVal = d->praSpinBoxRight->value();

	if (leftPRAVal < rightPRAVal) {
		minPRA = leftPRAVal;
		maxPRA = rightPRAVal;
	}
	else {
		minPRA = rightPRAVal;
		maxPRA = leftPRAVal;
	}	

	return true;
}

bool KPDGUIDisplaySettings::getShowAllNodes() const {
	return showAllNodes;
}

bool KPDGUIDisplaySettings::getShowNodeSubset() const {
	return showNodeSubset;
}

bool KPDGUIDisplaySettings::getShowNodesInStructures() const {
	return showNodesInStructures;
}

bool KPDGUIDisplaySettings::getShowNodesInSolutions() const {
	return showNodesInSolutions;
}

bool KPDGUIDisplaySettings::getShowNodesOnHold() const {
	return showNodesOnHold;
}

bool KPDGUIDisplaySettings::getShowNodesWithNoCompatibilities() const {
	return showNodesWithNoCompatibilities;
}

bool KPDGUIDisplaySettings::getShowCandidatesInPRARange() const {
	return showCandidatesInPRARange;
}

int KPDGUIDisplaySettings::getMinPRA() const {
	return minPRA;
}

int KPDGUIDisplaySettings::getMaxPRA() const {
	return maxPRA;
}

KPDMatchDisplayMode KPDGUIDisplaySettings::getMatchDisplayMode() const {
	return matchDisplayMode;
}

void KPDGUIDisplaySettings::setShowAllNodes(bool show){
	showAllNodes = show;
}

void KPDGUIDisplaySettings::setShowNodeSubset(bool show){
	showNodeSubset = show;
}

void KPDGUIDisplaySettings::setShowNodesInStructures(bool show){
	showNodesInStructures = show;
}

void KPDGUIDisplaySettings::setShowNodesInSolutions(bool show){
	showNodesInSolutions = show;
}

void KPDGUIDisplaySettings::setShowNodesOnHold(bool show){
	showNodesOnHold = show;
}

void KPDGUIDisplaySettings::setShowNodesWithNoCompatibilities(bool show){
	showNodesWithNoCompatibilities = show;
}

void KPDGUIDisplaySettings::setShowCandidatesInPRARange(bool show){
	showCandidatesInPRARange = show;
}

void KPDGUIDisplaySettings::setMinPRA(int pra){
	minPRA = pra;
}

void KPDGUIDisplaySettings::setMaxPRA(int pra){
	maxPRA = pra;
}

void KPDGUIDisplaySettings::setMatchDisplayMode(KPDMatchDisplayMode mode){
	matchDisplayMode = mode;
}

QDataStream &operator<<(QDataStream &out, const KPDGUIDisplaySettings & settings)
{
	out << settings.getShowAllNodes() << settings.getShowNodeSubset()
		<< settings.getShowNodesInSolutions() << settings.getShowNodesInStructures()
		<< settings.getShowNodesOnHold() << settings.getShowNodesWithNoCompatibilities()
		<< settings.getShowCandidatesInPRARange();

	out << qint32(settings.getMinPRA()) << qint32(settings.getMaxPRA());

	out << qint32(KPDFunctions::matchDisplayModeToInt(settings.getMatchDisplayMode()));
	
	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUIDisplaySettings & settings)
{
	bool showAllNodes;
	bool showNodeSubset;
	bool showNodesInSolutions;
	bool showNodesInStructures;
	bool showNodesOnHold;
	bool showNodesWithNoCompatibilities;
	bool showCandidatesInPRARange;

	int minPRA;
	int maxPRA;

	int mode;
	
	in >> showAllNodes >> showNodeSubset >> showNodesInSolutions >> showNodesInStructures
		>> showNodesOnHold >> showNodesWithNoCompatibilities >> showCandidatesInPRARange;

	in >> minPRA >> maxPRA;

	in >> mode;

	settings.setShowAllNodes(showAllNodes);
	settings.setShowNodeSubset(showNodeSubset);
	settings.setShowNodesInSolutions(showNodesInSolutions);
	settings.setShowNodesInStructures(showNodesInStructures);
	settings.setShowNodesOnHold(showNodesOnHold);
	settings.setShowNodesWithNoCompatibilities(showNodesWithNoCompatibilities);
	settings.setShowCandidatesInPRARange(showCandidatesInPRARange);

	settings.setMinPRA(minPRA);
	settings.setMaxPRA(maxPRA);

	settings.setMatchDisplayMode(KPDFunctions::intToMatchDisplayMode(mode));

	return in;

}