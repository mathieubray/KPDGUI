
#include "KPDGUIDisplaySettings.h"

KPDGUIDisplaySettings::KPDGUIDisplaySettings(){
	showAllPairs = true;
	showPairSubset = false;
	showPairsInSolutions = false;
	showPairsInStructures = false;
	showPairsOnHold = true;
	showPairsWithNoCompatibilities = true;
	showPairsOfMinPRA = false;
	showPairsOfMaxPRA = false;

	minPRA = 0;
	maxPRA = 100;

	arrowDisplayMode = WITHIN_SELECTION;
}

KPDGUIDisplaySettings::~KPDGUIDisplaySettings(){

}

bool KPDGUIDisplaySettings::changeDisplaySettings(DialogDisplaySettings * d){

	showAllPairs = d->allPairsButton->isChecked();
	showPairSubset = d->pairSubsetButton->isChecked();
	showPairsInStructures = d->showStructuresRadioButton->isChecked();
	showPairsInSolutions = d->showSolutionsRadioButton->isChecked();
	showPairsOnHold = d->showHoldCheckBox->isChecked();
	showPairsWithNoCompatibilities = d->showIncompatibleCheckBox->isChecked();
	showPairsOfMinPRA = d->minPRACheckBox->isChecked();
	showPairsOfMaxPRA = d->maxPRACheckBox->isChecked();

	minPRA = d->minPRASpinBox->value();
	maxPRA = d->maxPRASpinBox->value();

	return true;
}

bool KPDGUIDisplaySettings::getShowAllPairs() const {
	return showAllPairs;
}

bool KPDGUIDisplaySettings::getShowPairSubset() const {
	return showPairSubset;
}

bool KPDGUIDisplaySettings::getShowPairsInStructures() const {
	return showPairsInStructures;
}

bool KPDGUIDisplaySettings::getShowPairsInSolutions() const {
	return showPairsInSolutions;
}

bool KPDGUIDisplaySettings::getShowPairsOnHold() const {
	return showPairsOnHold;
}

bool KPDGUIDisplaySettings::getShowPairsWithNoCompatibilities() const {
	return showPairsWithNoCompatibilities;
}

bool KPDGUIDisplaySettings::getShowPairsOfMinPRA() const {
	return showPairsOfMinPRA;
}

bool KPDGUIDisplaySettings::getShowPairsOfMaxPRA() const {
	return showPairsOfMaxPRA;
}

int KPDGUIDisplaySettings::getMinPRA() const {
	return minPRA;
}

int KPDGUIDisplaySettings::getMaxPRA() const {
	return maxPRA;
}

KPDArrowDisplayMode KPDGUIDisplaySettings::getArrowDisplayMode() const {
	return arrowDisplayMode;
}

void KPDGUIDisplaySettings::setShowAllPairs(bool show){
	showAllPairs = show;
}

void KPDGUIDisplaySettings::setShowPairSubset(bool show){
	showPairSubset = show;
}

void KPDGUIDisplaySettings::setShowPairsInStructures(bool show){
	showPairsInStructures = show;
}

void KPDGUIDisplaySettings::setShowPairsInSolutions(bool show){
	showPairsInSolutions = show;
}

void KPDGUIDisplaySettings::setShowPairsOnHold(bool show){
	showPairsOnHold = show;
}

void KPDGUIDisplaySettings::setShowPairsWithNoCompatibilities(bool show){
	showPairsWithNoCompatibilities = show;
}

void KPDGUIDisplaySettings::setShowPairsOfMinPRA(bool show){
	showPairsOfMinPRA = show;
}

void KPDGUIDisplaySettings::setShowPairsOfMaxPRA(bool show){
	showPairsOfMaxPRA = show;
}

void KPDGUIDisplaySettings::setMinPRA(int pra){
	minPRA = pra;
}

void KPDGUIDisplaySettings::setMaxPRA(int pra){
	maxPRA = pra;
}

void KPDGUIDisplaySettings::setArrowDisplayMode(KPDArrowDisplayMode mode){
	arrowDisplayMode = mode;
}

QDataStream &operator<<(QDataStream &out, const KPDGUIDisplaySettings & settings)
{
	out << settings.getShowAllPairs() << settings.getShowPairSubset() 
		<< settings.getShowPairsInSolutions() << settings.getShowPairsInStructures()
		<< settings.getShowPairsOnHold() << settings.getShowPairsWithNoCompatibilities() 
		<< settings.getShowPairsOfMinPRA() << settings.getShowPairsOfMaxPRA();

	out << qint32(settings.getMinPRA()) << qint32(settings.getMaxPRA());

	out << qint32(KPDFunctions::arrowDisplayModeToInt(settings.getArrowDisplayMode()));
	
	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUIDisplaySettings & settings)
{
	bool showAllPairs;
	bool showPairSubset;
	bool showPairsInSolutions;
	bool showPairsInStructures;
	bool showPairsOnHold;
	bool showPairsWithNoCompatibilities;
	bool showPairsOfMinPRA;
	bool showPairsOfMaxPRA;

	int minPRA;
	int maxPRA;

	int mode;
	
	in >> showAllPairs >> showPairSubset >> showPairsInSolutions >> showPairsInStructures
		>> showPairsOnHold >> showPairsWithNoCompatibilities >> showPairsOfMinPRA >> showPairsOfMaxPRA;

	in >> minPRA >> maxPRA;

	in >> mode;

	settings.setShowAllPairs(showAllPairs);
	settings.setShowPairSubset(showPairSubset);
	settings.setShowPairsInSolutions(showPairsInSolutions);
	settings.setShowPairsInStructures(showPairsInStructures);
	settings.setShowPairsOnHold(showPairsOnHold);
	settings.setShowPairsWithNoCompatibilities(showPairsWithNoCompatibilities);
	settings.setShowPairsOfMinPRA(showPairsOfMinPRA);
	settings.setShowPairsOfMaxPRA(showPairsOfMaxPRA);

	settings.setMinPRA(minPRA);
	settings.setMaxPRA(maxPRA);

	settings.setArrowDisplayMode(KPDFunctions::intToArrowDisplayMode(mode));

	return in;

}