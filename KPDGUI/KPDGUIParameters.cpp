#include "KPDGUIParameters.h"

KPDGUIParameters::KPDGUIParameters(){
	
	//Default Parameters

	parametersUpdated = false;

	//Simulation Settings
	optimizationScheme = LOCALLY_RELEVANT_SUBGRAPHS;
	utilityScheme = TRANSPLANTS;	
	
	maxCycleSize = 3;
	maxChainLength = 3;
	maxLRSSize = 4;

	collectArrangements = true;
	collectArrangementsCutoff = 200;
	
	//Numerical Parameters		
	addAdvantage = false;
	advantageCutoff = 100;
	advantageValue = 0.0;

	numberOfSolutions = 1;
	
	estimateEU = false;
	numberOfEUIterations = 100;

	//Additional Options
	reserveOforO = false;	
	checkHLA = false;
	includeCompatible = false;
	excludeABDonors = false;
	allowABBridge = false;
	
}

KPDGUIParameters::~KPDGUIParameters(){
	
}


void KPDGUIParameters::changeParameters(DialogSimParameters * d){

	parametersUpdated = true;

	optimizationScheme = KPDFunctions::intToOptScheme(d->optComboBox->currentIndex());
	utilityScheme = KPDFunctions::intToUtilScheme(d->utilComboBox->currentIndex());
	
	maxCycleSize = d->cycleSizeSpinBox->value();
	maxChainLength = d->chainLengthSpinBox->value();
	maxLRSSize = d->lrsSizeSpinBox->value();

	collectArrangements = d->collectArrangementsCheckBox->isChecked();
	collectArrangementsCutoff = d->collectArrangementsSpinBox->value();

	addAdvantage = d->praCheckBox->isChecked();
	advantageCutoff = d->praCutoffSpinBox->value();
	advantageValue = d->praAdvantageSpinBox->value();

	numberOfSolutions = d->solutionsSpinBox->value();
	
	estimateEU = d->estimateEUCheckBox->isChecked();
	numberOfEUIterations = d->numberOfEUSimSpinBox->value();

	reserveOforO = d->reserveOtoOBox->isChecked();
	checkHLA = d->checkAdditionalHLABox->isChecked();
	includeCompatible = d->compatibleBox->isChecked();
	excludeABDonors = d->excludeABDonorsBox->isChecked();
	allowABBridge = d->allowABBridgeBox->isChecked();
	
}

void KPDGUIParameters::copyParameters(KPDGUIParameters * d){

	optimizationScheme = d->getOptimizationScheme();
	utilityScheme = d->getUtilityScheme();
	
	maxCycleSize = d->getMaxCycleSize();
	maxChainLength = d->getMaxChainLength();
	maxLRSSize = d->getMaxLRSSize();

	collectArrangements = d->getCollectArrangements();
	collectArrangementsCutoff = d->getCollectArrangementsCutoff();
	
	addAdvantage = d->addAdvantageToHighPRACandidates();
	advantageCutoff = d->getPRAAdvantageCutoff();
	advantageValue = d->getPRAAdvantageValue();

	numberOfSolutions = d->getNumberOfSolutions();

	estimateEU = d->estimateExpectedUtility();
	numberOfEUIterations = d->getNumberOfExpectedUtilityIterations();

	reserveOforO = d->reserveODonorsForOCandidates();
	checkHLA = d->checkAdditionalHLA();
	includeCompatible = d->includeCompatiblePairs();
	excludeABDonors = d->excludeABDonorsFromSimulation();
	allowABBridge = d->allowABBridgeDonors();
}

bool KPDGUIParameters::parametersHaveBeenUpdated(){

	return parametersUpdated;
}

void KPDGUIParameters::setParametersHaveBeenUpdatedFlag(bool flag){

	parametersUpdated = flag;
}

QString KPDGUIParameters::toString(){
	QString parameterString = "";

	parameterString.append("Optimization Based On " + KPDFunctions::toString(optimizationScheme) + "\n");

	parameterString.append("Utility Based On " + KPDFunctions::toString(utilityScheme) + "\n");

	if (optimizationScheme != KPDOptimizationScheme::LOCALLY_RELEVANT_SUBGRAPHS){
		parameterString.append("Maximum Cycle Size: " + QString::number(maxCycleSize) + "\n");
		parameterString.append("Maximum Chain Length: " + QString::number(maxChainLength) + "\n");
	}
	else {
		parameterString.append("Maximum Locally Relevant Subgraph Size: " + QString::number(maxLRSSize) + "\n");
		parameterString.append("Maximum Sub-Cycle Size: " + QString::number(maxCycleSize) + "\n");
		parameterString.append("Maximum Sub-Chain Length: " + QString::number(maxChainLength) + "\n");
	}

	if (collectArrangements) {
		parameterString.append("Collecting a Maximum of " + QString::number(collectArrangementsCutoff) + " Arrangements For Display\n");
	}
	else {
		parameterString.append("Not Collecting Arrangemetns for Display");
	}

	if (numberOfSolutions > 1){
		parameterString.append(numberOfSolutions + " Alternate Solutions Produced\n");
	}

	if (estimateEU && optimizationScheme != CYCLES_AND_CHAINS){
		parameterString.append(QString::number(numberOfEUIterations) + " Iterations To Estimate Expected Utility\n");		
	}

	if (addAdvantage){
		parameterString.append("Add Advantage To High PRA Recipients: Extra " + QString::number(advantageValue) + " for PRA Above " + QString::number(advantageCutoff) + "\n");
	}
	else {
		parameterString.append("No Added Advantage For High PRA Recipients\n");
	}
	
	if (reserveOforO){
		parameterString.append("O Donors Reserved For O Recipients\n");
	}
	else {
		parameterString.append("O Donors Not Explicitly Reserved For O Recipients\n");
	}

	if (checkHLA){
		parameterString.append("Check Additional HLA Information (DP)\n");
	}
	else {
		parameterString.append("Do Not Check Additional HLA Information\n");
	}

	if (includeCompatible){
		parameterString.append("Include Compatible Pairs In Match Runs\n");
	}
	else {
		parameterString.append("Do Not Include Compatible Pairs In Match Runs\n");
	}

	if (excludeABDonors){
		parameterString.append("Exclude AB Donors from Simulation");
	}
	else {
		if (allowABBridge){
			parameterString.append("Allow AB Bridge Donors\n");
		}
		else {
			parameterString.append("Do Not Allow AB Bridge Donors\n");
		}
	}

	return parameterString;
}

KPDOptimizationScheme KPDGUIParameters::getOptimizationScheme() const {
	return optimizationScheme;
}

KPDUtilityScheme KPDGUIParameters::getUtilityScheme() const {
	return utilityScheme;
}

int KPDGUIParameters::getMaxCycleSize() const {
	return maxCycleSize;
}

int KPDGUIParameters::getMaxChainLength() const {
	return maxChainLength;
}

int KPDGUIParameters::getMaxLRSSize() const {
	return maxLRSSize;
}

bool KPDGUIParameters::getCollectArrangements() const {
	return collectArrangements;
}

int KPDGUIParameters::getCollectArrangementsCutoff() const {
	return collectArrangementsCutoff;
}

bool KPDGUIParameters::addAdvantageToHighPRACandidates() const {
	return addAdvantage;
}

int KPDGUIParameters::getPRAAdvantageCutoff() const {
	return advantageCutoff;
}

double KPDGUIParameters::getPRAAdvantageValue() const {
	return advantageValue;
}

int KPDGUIParameters::getNumberOfSolutions() const {
	return numberOfSolutions;
}

bool KPDGUIParameters::estimateExpectedUtility() const {
	return estimateEU;
}

int KPDGUIParameters::getNumberOfExpectedUtilityIterations() const {
	return numberOfEUIterations;
}

bool KPDGUIParameters::reserveODonorsForOCandidates() const {
	return reserveOforO;
}

bool KPDGUIParameters::checkAdditionalHLA() const {
	return checkHLA;
}

bool KPDGUIParameters::includeCompatiblePairs() const {
	return includeCompatible;
}

bool KPDGUIParameters::excludeABDonorsFromSimulation() const {
	return excludeABDonors;
}

bool KPDGUIParameters::allowABBridgeDonors() const {
	return allowABBridge;
}

void KPDGUIParameters::setOptimizationScheme(KPDOptimizationScheme scheme){
	optimizationScheme = scheme;
}

void KPDGUIParameters::setUtilityScheme(KPDUtilityScheme scheme){
	utilityScheme = scheme;
}

void KPDGUIParameters::setMaxCycleSize(int size){
	maxCycleSize = size;
}

void KPDGUIParameters::setMaxChainLength(int length) {
	maxChainLength = length;
}

void KPDGUIParameters::setMaxLRSSize(int size) {
	maxLRSSize = size;
}

void KPDGUIParameters::setCollectArrangements(bool collect) {
	collectArrangements = collect;
}

void KPDGUIParameters::setCollectArrangementsCutoff(int cutoff) {
	collectArrangementsCutoff = cutoff;
}

void KPDGUIParameters::setAddAdvantagetoHighPRACandidatesFlag(bool flag){
	addAdvantage = flag;
}

void KPDGUIParameters::setPRAAdvantageCutoff(int cutoff){
	advantageCutoff = cutoff;
}

void KPDGUIParameters::setPRAAdvantageValue(double value){
	advantageValue = value;
}

void KPDGUIParameters::setNumberOfSolutions(int solutions){
	numberOfSolutions = solutions;
}

void KPDGUIParameters::setEstimateExpectedUtilityFlag(bool flag) {
	estimateEU = flag;
}

void KPDGUIParameters::setNumberOfExpectedUtilityIterations(int iterations){
	numberOfEUIterations = iterations;
}

void KPDGUIParameters::setReserveODonorsForOCandidatesFlag(bool flag){
	reserveOforO = flag;
}

void KPDGUIParameters::setCheckAdditionalHLAFlag(bool flag){
	checkHLA = flag;
}

void KPDGUIParameters::setIncludeCompatiblePairsFlag(bool flag){
	includeCompatible = flag;
}

void KPDGUIParameters::setExcludeABDonorsFromSimulationFlag(bool flag){
	excludeABDonors = flag;
}

void KPDGUIParameters::setAllowABBridgeDonorsFlag(bool flag){
	allowABBridge = flag;
}


QDataStream &operator<<(QDataStream &out, const KPDGUIParameters & parameters)
{
	out << qint32(KPDFunctions::optSchemeToInt(parameters.getOptimizationScheme()));
	out << qint32(KPDFunctions::utilSchemeToInt(parameters.getUtilityScheme()));

	out << qint32(parameters.getMaxCycleSize());
	out << qint32(parameters.getMaxChainLength());
	out << qint32(parameters.getMaxLRSSize());

	out << parameters.getCollectArrangements();
	out << qint32(parameters.getCollectArrangementsCutoff());
	
	out << qint32(parameters.getNumberOfSolutions());

	out << parameters.estimateExpectedUtility();
	out << qint32(parameters.getNumberOfExpectedUtilityIterations());

	out << parameters.addAdvantageToHighPRACandidates();
	out << qint32(parameters.getPRAAdvantageCutoff());
	out << qreal(parameters.getPRAAdvantageValue());

	out << parameters.reserveODonorsForOCandidates();
	out << parameters.checkAdditionalHLA();
	out << parameters.includeCompatiblePairs();
	out << parameters.excludeABDonorsFromSimulation();
	out << parameters.allowABBridgeDonors();

	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUIParameters & parameters)
{
	int opt;
	int util;

	int cycleSize;
	int chainLength;
	int lrsSize;

	bool collect;
	int collectCutoff;

	int numberOfSolutions;

	bool estimateEU;
	int numberOfEUIterations;

	bool addAdvantage;
	int advantageCutoff;
	double advantageValue;

	bool reserveOforO;
	bool checkHLA;
	bool includeCompatible;
	bool excludeABDonors;
	bool allowABBridge;
	
	in >> opt >> util >> cycleSize >> chainLength >> lrsSize;

	in >> collect >> collectCutoff;

	in >> numberOfSolutions >> estimateEU >> numberOfEUIterations;

	in >> addAdvantage >> advantageCutoff >> advantageValue;

	in >> reserveOforO >> checkHLA >> includeCompatible >> excludeABDonors >> allowABBridge;

	parameters.setOptimizationScheme(KPDFunctions::intToOptScheme(opt));
	parameters.setUtilityScheme(KPDFunctions::intToUtilScheme(util));
	parameters.setMaxCycleSize(cycleSize);
	parameters.setMaxChainLength(chainLength);
	parameters.setMaxLRSSize(lrsSize);
	parameters.setCollectArrangements(collect);
	parameters.setCollectArrangementsCutoff(collectCutoff);
	parameters.setNumberOfSolutions(numberOfSolutions);
	parameters.setEstimateExpectedUtilityFlag(estimateEU);
	parameters.setNumberOfExpectedUtilityIterations(numberOfEUIterations);
	parameters.setAddAdvantagetoHighPRACandidatesFlag(addAdvantage);
	parameters.setPRAAdvantageCutoff(advantageCutoff);
	parameters.setPRAAdvantageValue(advantageValue);
	parameters.setReserveODonorsForOCandidatesFlag(reserveOforO);
	parameters.setCheckAdditionalHLAFlag(checkHLA);
	parameters.setIncludeCompatiblePairsFlag(includeCompatible);
	parameters.setExcludeABDonorsFromSimulationFlag(excludeABDonors);
	parameters.setAllowABBridgeDonorsFlag(allowABBridge);

	return in;

}