
#include "KPDGUIDisplaySettings.h"

KPDGUIDisplaySettings::KPDGUIDisplaySettings(){

	nodeDisplayMode = DONOR_DISPLAY_MULTIPLE;

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

	filterSuccessfulMatches = true;
	filterOtoNonOMatches = true;
	filterFailedMatchesAdditionalHLA = true;
	filterFailedMatchesCrossmatch = true;

	highlightMatchesToAvoid = true;

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

bool KPDGUIDisplaySettings::changeDisplaySettings(KPDGUIDisplaySettings * d) {

	nodeDisplayMode = d->getNodeDisplayMode();

	showAllNodes = d->getShowAllNodes();
	showNodeSubset = d->getShowNodeSubset();
	showNodesInArrangements = d->getShowNodesInArrangements();
	showNodesInSolutions = d->getShowNodesInSolutions();
	showExcludedNodes = d->getShowExcludedNodes();
	showNodesWithNoCompatibilities = d->getShowNodesWithNoCompatibilities();
	showCandidatesInPRARange = d->getShowCandidatesInPRARange();

	int leftPRAVal = d->getMinPRA();
	int rightPRAVal = d->getMaxPRA();

	minPRA = leftPRAVal;
	maxPRA = rightPRAVal;
	
	matchDisplayMode = d->getMatchDisplayMode();

	filterSuccessfulMatches = d->getFilterSuccessfulMatches();
	filterOtoNonOMatches = d->getFilterOtoNonOMatches();
	filterFailedMatchesAdditionalHLA = d->getFilterFailedMatchesAdditionalHLA();
	filterFailedMatchesCrossmatch = d->getFilterFailedMatchesCrossmatch();

	highlightMatchesToAvoid = d->getHighlightMatchesToAvoid();

	return true;
}

KPDDonorDisplayMode KPDGUIDisplaySettings::getNodeDisplayMode() const {
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

bool KPDGUIDisplaySettings::getFilterSuccessfulMatches() const {
	return filterSuccessfulMatches;
}

bool KPDGUIDisplaySettings::getFilterOtoNonOMatches() const {
	return filterOtoNonOMatches;
}

bool KPDGUIDisplaySettings::getFilterFailedMatchesAdditionalHLA() const {
	return filterFailedMatchesAdditionalHLA;
}

bool KPDGUIDisplaySettings::getFilterFailedMatchesCrossmatch() const {
	return filterFailedMatchesCrossmatch;
}

bool KPDGUIDisplaySettings::getHighlightMatchesToAvoid() const {
	return highlightMatchesToAvoid;
}

void KPDGUIDisplaySettings::setNodeDisplayMode(KPDDonorDisplayMode mode) {
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

void KPDGUIDisplaySettings::setFilterSuccessfulMatches(bool show) {
	filterSuccessfulMatches = show;
}

void KPDGUIDisplaySettings::setFilterOtoNonOMatches(bool show) {
	filterOtoNonOMatches = show;
}

void KPDGUIDisplaySettings::setFilterFailedMatchesAdditionalHLA(bool show) {
	filterFailedMatchesAdditionalHLA = show;
}

void KPDGUIDisplaySettings::setFilterFailedMatchesCrossmatch(bool show) {
	filterFailedMatchesCrossmatch = show;
}

void KPDGUIDisplaySettings::setHightlightMatchesToAvoid(bool flag) {
	highlightMatchesToAvoid = flag;
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

	out << settings.getFilterSuccessfulMatches() << settings.getFilterOtoNonOMatches() 
		<< settings.getFilterFailedMatchesAdditionalHLA() << settings.getFilterFailedMatchesCrossmatch();

	out << settings.getHighlightMatchesToAvoid();
	
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

	bool filterSuccessfulMatches;
	bool filterOtoNonOMatches;
	bool filterFailedMatchesAdditionalHLA;
	bool filterFailedMatchesCrossmatch;

	bool highlightMatchesToAvoid;
	
	in >> nodeDisplayMode;

	in >> showAllNodes >> showNodeSubset  >> showNodesInArrangements >> showNodesInSolutions
		>> showExcludedNodes >> showNodesWithNoCompatibilities >> showCandidatesInPRARange;

	in >> minPRA >> maxPRA;

	in >> matchDisplayMode;

	in >> filterSuccessfulMatches >> filterOtoNonOMatches 
		>> filterFailedMatchesAdditionalHLA >> filterFailedMatchesCrossmatch;

	in >> highlightMatchesToAvoid;

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

	settings.setFilterSuccessfulMatches(filterSuccessfulMatches);
	settings.setFilterOtoNonOMatches(filterOtoNonOMatches);
	settings.setFilterFailedMatchesAdditionalHLA(filterFailedMatchesAdditionalHLA);
	settings.setFilterFailedMatchesCrossmatch(filterFailedMatchesCrossmatch);

	settings.setHightlightMatchesToAvoid(highlightMatchesToAvoid);

	return in;

}