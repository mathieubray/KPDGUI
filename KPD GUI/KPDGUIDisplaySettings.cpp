
#include "KPDGUIDisplaySettings.h"

KPDGUIDisplaySettings::KPDGUIDisplaySettings(){

	nodeDisplayMode = SEPARATE_DONOR_CANDIDATE;

	showAllNodes = true;
	showNodeSubset = false;
	showNodesInArrangements = false;
	showNodesInSolutions = false;
	showExcludedNodes = true;
	showNodesWithNoCompatibilities = true;
	showCandidatesInPRARange = false;

	minPRA = 0;
	maxPRA = 100;

	matchDisplayMode = WITHIN_SELECTION;
}

KPDGUIDisplaySettings::~KPDGUIDisplaySettings(){

}

bool KPDGUIDisplaySettings::changeDisplaySettings(DialogDisplaySettings * d){

	nodeDisplayMode = KPDFunctions::intToNodeDisplayMode(d->nodeDisplayModeComboBox->currentIndex());

	showAllNodes = d->allNodesButton->isChecked();
	showNodeSubset = d->nodeSubsetButton->isChecked();
	showNodesInArrangements = d->showArrangementsRadioButton->isChecked();
	showNodesInSolutions = d->showSolutionsRadioButton->isChecked();
	showExcludedNodes = d->showExcludedCheckBox->isChecked();
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

KPDNodeDisplayMode KPDGUIDisplaySettings::getNodeDisplayMode() const {
	return nodeDisplayMode;
}

bool KPDGUIDisplaySettings::getShowAllNodes() const {
	return showAllNodes;
}

bool KPDGUIDisplaySettings::getShowNodeSubset() const {
	return showNodeSubset;
}

bool KPDGUIDisplaySettings::getShowNodesInArrangements() const {
	return showNodesInArrangements;
}

bool KPDGUIDisplaySettings::getShowNodesInSolutions() const {
	return showNodesInSolutions;
}

bool KPDGUIDisplaySettings::getShowExcludedNodes() const {
	return showExcludedNodes;
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

void KPDGUIDisplaySettings::setNodeDisplayMode(KPDNodeDisplayMode mode) {
	nodeDisplayMode = mode;
}

void KPDGUIDisplaySettings::setShowAllNodes(bool show){
	showAllNodes = show;
}

void KPDGUIDisplaySettings::setShowNodeSubset(bool show){
	showNodeSubset = show;
}

void KPDGUIDisplaySettings::setShowNodesInArrangements(bool show){
	showNodesInArrangements = show;
}

void KPDGUIDisplaySettings::setShowNodesInSolutions(bool show){
	showNodesInSolutions = show;
}

void KPDGUIDisplaySettings::setShowExcludedNodes(bool show){
	showExcludedNodes = show;
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

QDataStream &operator<<(QDataStream &out, const KPDGUIDisplaySettings &settings)
{
	out << qint32(KPDFunctions::nodeDisplayModeToInt(settings.getNodeDisplayMode()));

	out << settings.getShowAllNodes() << settings.getShowNodeSubset()
		<< settings.getShowNodesInSolutions() << settings.getShowNodesInArrangements()
		<< settings.getShowExcludedNodes() << settings.getShowNodesWithNoCompatibilities()
		<< settings.getShowCandidatesInPRARange();

	out << qint32(settings.getMinPRA()) << qint32(settings.getMaxPRA());

	out << qint32(KPDFunctions::matchDisplayModeToInt(settings.getMatchDisplayMode()));
	
	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUIDisplaySettings &settings)
{
	int nodeDisplayMode;

	bool showAllNodes;
	bool showNodeSubset;
	bool showNodesInArrangements;
	bool showNodesInSolutions;
	bool showExcludedNodes;
	bool showNodesWithNoCompatibilities;
	bool showCandidatesInPRARange;

	int minPRA;
	int maxPRA;

	int matchDisplayMode;
	
	in >> nodeDisplayMode;

	in >> showAllNodes >> showNodeSubset  >> showNodesInArrangements >> showNodesInSolutions
		>> showExcludedNodes >> showNodesWithNoCompatibilities >> showCandidatesInPRARange;

	in >> minPRA >> maxPRA;

	in >> matchDisplayMode;

	settings.setNodeDisplayMode(KPDFunctions::intToNodeDisplayMode(nodeDisplayMode));

	settings.setShowAllNodes(showAllNodes);
	settings.setShowNodeSubset(showNodeSubset);
	settings.setShowNodesInArrangements(showNodesInArrangements);
	settings.setShowNodesInSolutions(showNodesInSolutions);
	settings.setShowExcludedNodes(showExcludedNodes);
	settings.setShowNodesWithNoCompatibilities(showNodesWithNoCompatibilities);
	settings.setShowCandidatesInPRARange(showCandidatesInPRARange);

	settings.setMinPRA(minPRA);
	settings.setMaxPRA(maxPRA);

	settings.setMatchDisplayMode(KPDFunctions::intToMatchDisplayMode(matchDisplayMode));

	return in;

}