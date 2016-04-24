#include "KPDGUISimParameters.h"

KPDGUISimParameters::KPDGUISimParameters(){
	
	//Default Parameters

	parametersHaveBeenUpdated = false;

	//Simulation Settings
	optScheme = MUC;
	utilityScheme = TRANSPLANTS;	
	
	maxCycleSize = 3;
	maxChainLength = 3;
	maxComponentSize = 4;
	
	//Numerical Parameters		
	addAdvantageToHighPRACandidates = false;
	praAdvantageCutoff = 100;
	praAdvantageValue = 0.0;

	numberOfSolutions = 1;
	
	estimateExpectedUtility = false;
	numberOfExpectedUtilityIterations = 100;

	//Additional Options
	chainStorage = AS_FOUND;
	reserveODonorsForOCandidates = false;	
	checkAdditionalHLA = false;
	includeCompatiblePairs = false;
	excludeABDonorsFromSimulation = false;
	allowABBridgeDonors = false;
	
}

KPDGUISimParameters::~KPDGUISimParameters(){
	
}


void KPDGUISimParameters::changeParameters(DialogSimParameters * d){

	parametersHaveBeenUpdated = true;

	optScheme = KPDFunctions::intToOptScheme(d->optComboBox->currentIndex());
	utilityScheme = KPDFunctions::intToUtilScheme(d->utilComboBox->currentIndex());
	
	maxCycleSize = d->cycleSizeSpinBox->value();
	maxChainLength = d->chainLengthSpinBox->value();
	maxComponentSize = d->componentSizeSpinBox->value();

	addAdvantageToHighPRACandidates = d->praCheckBox->isChecked();
	praAdvantageCutoff = d->praCutoffSpinBox->value();
	praAdvantageValue = d->praAdvantageSpinBox->value();

	numberOfSolutions = d->solutionsSpinBox->value();
	
	estimateExpectedUtility = d->estimateEUCheckBox->isChecked();
	numberOfExpectedUtilityIterations = d->numberOfEUSimSpinBox->value();

	chainStorage = KPDFunctions::intToChainStorage(d->chainStorageComboBox->currentIndex());
	reserveODonorsForOCandidates = d->reserveOtoOBox->isChecked();
	checkAdditionalHLA = d->checkAdditionalHLABox->isChecked();
	includeCompatiblePairs = d->compatibleBox->isChecked();
	excludeABDonorsFromSimulation = d->excludeABDonorsBox->isChecked();
	allowABBridgeDonors = d->allowABBridgeBox->isChecked();
	
}

void KPDGUISimParameters::copyParameters(KPDGUISimParameters * d){
	optScheme = d->getOptimizationScheme();
	utilityScheme = d->getUtilityScheme();
	
	maxCycleSize = d->getMaxCycleSize();
	maxChainLength = d->getMaxChainLength();
	maxComponentSize = d->getMaxComponentSize();
	
	addAdvantageToHighPRACandidates = d->getAddAdvantageToHighPRACandidates();
	praAdvantageCutoff = d->getPRAAdvantageCutoff();
	praAdvantageValue = d->getPRAAdvantageValue();

	numberOfSolutions = d->getNumberOfSolutions();

	estimateExpectedUtility = d->getEstimateExpectedUtility();
	numberOfExpectedUtilityIterations = d->getNumberOfExpectedUtilityIterations();

	chainStorage = d->getChainStorage();
	reserveODonorsForOCandidates = d->getReserveODonorsForOCandidates();
	checkAdditionalHLA = d->getCheckAdditionalHLA();
	includeCompatiblePairs = d->getIncludeCompatiblePairs();
	excludeABDonorsFromSimulation = d->getExcludeABDonorsFromSimulation();
	allowABBridgeDonors = d->getAllowABBridgeDonors();
}

bool KPDGUISimParameters::getParametersHaveBeenUpdated(){
	return parametersHaveBeenUpdated;
}

void KPDGUISimParameters::setParametersHaveBeenUpdated(bool flag){
	parametersHaveBeenUpdated = flag;
}

QString KPDGUISimParameters::toString(){
	QString parameterString = "";

	if (optScheme == KPDOptimizationScheme::MUC){
		parameterString.append("Optimize based on Maximum Utility\n");
	}
	else if (optScheme == KPDOptimizationScheme::MEUC){
		parameterString.append("Optimize based on Maximum Expected Utility\n");
	}
	else if (optScheme == KPDOptimizationScheme::MEUS){
		parameterString.append("Optimize based on Maximum Expected Utility with Fallbacks\n");
	}
	else if (optScheme == KPDOptimizationScheme::SCC){
		parameterString.append("Optimize based on Maximum Expected Utility with Extended Fallbacks\n");
	}

	if (utilityScheme == KPDUtilityScheme::SCORE){
		parameterString.append("Utility Based On Assigned Score\n");
	}
	else if (utilityScheme == KPDUtilityScheme::SURVIVAL5YEAR){
		parameterString.append("Utility Based On 5-Year Graft Survival\n");
	}
	else if (utilityScheme == KPDUtilityScheme::SURVIVAL10YEAR){
		parameterString.append("Utility Based On 10-Year Graft Survival\n");
	}
	else {
		parameterString.append("Utility Based On # Of Transplants\n");
	}

	if (optScheme != KPDOptimizationScheme::SCC){
		parameterString.append("Maximum Cycle Size: " + QString::number(maxCycleSize) + "\n");
		parameterString.append("Maximum Chain Length: " + QString::number(maxChainLength) + "\n");
	}
	else {
		parameterString.append("Maximum Locally Relevant Subgraph Size: " + QString::number(maxComponentSize) + "\n");
		parameterString.append("Maximum Sub-cycle Size: " + QString::number(maxCycleSize) + "\n");
		parameterString.append("Maximum Sub-chain Length: " + QString::number(maxChainLength) + "\n");
	}

	if (numberOfSolutions > 1){
		parameterString.append(numberOfSolutions + " Alternate Solutions Produced\n");
	}

	if (estimateExpectedUtility) {
		if (optScheme == KPDOptimizationScheme::SCC) {
			parameterString.append(QString::number(numberOfExpectedUtilityIterations) + " Simulations used to Calculate Expected Utility\n");
		}
	}

	if (addAdvantageToHighPRACandidates){
		parameterString.append("Add Advantage To High PRA Recipients: Extra " + QString::number(praAdvantageValue) + " for PRA Above " + QString::number(praAdvantageCutoff) + "\n");
	}
	else {
		parameterString.append("No Added Advantage For High PRA Recipients\n");
	}

	if (chainStorage == CHAINS_FIRST){
		parameterString.append("Structures with ADs are Stored First Among Possible Structures");
	}
	else if (chainStorage == CHAINS_LAST){
		parameterString.append("Structures with ADs are Stored Last Among Possible Structures");
	}

	if (reserveODonorsForOCandidates){
		parameterString.append("O Donors Reserved For O Recipients\n");
	}
	else {
		parameterString.append("O Donors Not Explicitly Reserved For O Recipients\n");
	}

	if (checkAdditionalHLA){
		parameterString.append("Check Additional HLA Information (DP)\n");
	}
	else {
		parameterString.append("Do Not Check Additional HLA Information\n");
	}

	if (includeCompatiblePairs){
		parameterString.append("Include Compatible Pairs In Match Runs\n");
	}
	else {
		parameterString.append("Do Not Include Compatible Pairs In Match Runs\n");
	}

	if (excludeABDonorsFromSimulation){
		parameterString.append("Exclude AB Donors from Simulation");
	}
	else {
		if (allowABBridgeDonors){
			parameterString.append("Allow AB Bridge Donors\n");
		}
		else {
			parameterString.append("Do Not Allow AB Bridge Donors\n");
		}
	}

	return parameterString;
}

KPDOptimizationScheme KPDGUISimParameters::getOptimizationScheme() const {
	return optScheme;
}

KPDUtilityScheme KPDGUISimParameters::getUtilityScheme() const {
	return utilityScheme;
}

int KPDGUISimParameters::getMaxCycleSize() const {
	return maxCycleSize;
}

int KPDGUISimParameters::getMaxChainLength() const {
	return maxChainLength;
}

int KPDGUISimParameters::getMaxComponentSize() const {
	return maxComponentSize;
}

bool KPDGUISimParameters::getAddAdvantageToHighPRACandidates() const {
	return addAdvantageToHighPRACandidates;
}

int KPDGUISimParameters::getPRAAdvantageCutoff() const {
	return praAdvantageCutoff;
}

double KPDGUISimParameters::getPRAAdvantageValue() const {
	return praAdvantageValue;
}

int KPDGUISimParameters::getNumberOfSolutions() const {
	return numberOfSolutions;
}

bool KPDGUISimParameters::getEstimateExpectedUtility() const {
	return estimateExpectedUtility;
}

int KPDGUISimParameters::getNumberOfExpectedUtilityIterations() const {
	return numberOfExpectedUtilityIterations;
}

KPDChainStorage KPDGUISimParameters::getChainStorage() const {
	return chainStorage;
}

bool KPDGUISimParameters::getReserveODonorsForOCandidates() const {
	return reserveODonorsForOCandidates;
}

bool KPDGUISimParameters::getCheckAdditionalHLA() const {
	return checkAdditionalHLA;
}

bool KPDGUISimParameters::getIncludeCompatiblePairs() const {
	return includeCompatiblePairs;
}

bool KPDGUISimParameters::getExcludeABDonorsFromSimulation() const {
	return excludeABDonorsFromSimulation;
}

bool KPDGUISimParameters::getAllowABBridgeDonors() const {
	return allowABBridgeDonors;
}

void KPDGUISimParameters::setOptimizationScheme(KPDOptimizationScheme scheme){
	optScheme = scheme;
}

void KPDGUISimParameters::setUtilityScheme(KPDUtilityScheme scheme){
	utilityScheme = scheme;
}

void KPDGUISimParameters::setMaxCycleSize(int size){
	maxCycleSize = size;
}

void KPDGUISimParameters::setMaxChainLength(int length) {
	maxChainLength = length;
}

void KPDGUISimParameters::setMaxComponentSize(int size) {
	maxComponentSize = size;
}

void KPDGUISimParameters::setAddAdvantagetoHighPRACandidates(bool flag){
	addAdvantageToHighPRACandidates = flag;
}

void KPDGUISimParameters::setPRAAdvantageCutoff(int cutoff){
	praAdvantageCutoff = cutoff;
}

void KPDGUISimParameters::setPRAAdvantageValue(double value){
	praAdvantageValue = value;
}

void KPDGUISimParameters::setNumberOfSolutions(int solutions){
	numberOfSolutions = solutions;
}

void KPDGUISimParameters::setEstimateExpectedUtility(bool estimate) {
	estimateExpectedUtility = estimate;
}

void KPDGUISimParameters::setNumberOfExpectedUtilityIterations(int iterations){
	numberOfExpectedUtilityIterations = iterations;
}

void KPDGUISimParameters::setChainStorage(KPDChainStorage storage){
	chainStorage = storage;
}

void KPDGUISimParameters::setReserveODonorsForOCandidates(bool flag){
	reserveODonorsForOCandidates = flag;
}

void KPDGUISimParameters::setCheckAdditionalHLA(bool flag){
	checkAdditionalHLA = flag;
}

void KPDGUISimParameters::setIncludeCompatiblePairs(bool flag){
	includeCompatiblePairs = flag;
}

void KPDGUISimParameters::setExcludeABDonorsFromSimulation(bool flag){
	excludeABDonorsFromSimulation = flag;
}

void KPDGUISimParameters::setAllowABBridgeDonors(bool flag){
	allowABBridgeDonors = flag;
}


QDataStream &operator<<(QDataStream &out, const KPDGUISimParameters & parameters)
{
	out << qint32(KPDFunctions::optSchemeToInt(parameters.getOptimizationScheme()));
	out << qint32(KPDFunctions::utilSchemeToInt(parameters.getUtilityScheme()));

	out << qint32(parameters.getMaxCycleSize());
	out << qint32(parameters.getMaxChainLength());
	out << qint32(parameters.getMaxComponentSize());

	out << parameters.getAddAdvantageToHighPRACandidates();
	out << qint32(parameters.getPRAAdvantageCutoff());
	out << qreal(parameters.getPRAAdvantageValue());

	out << qint32(parameters.getNumberOfSolutions());

	out << parameters.getEstimateExpectedUtility();
	out << qint32(parameters.getNumberOfExpectedUtilityIterations());

	out << qint32(KPDFunctions::chainStorageToInt(parameters.getChainStorage()));
	out << parameters.getReserveODonorsForOCandidates();
	out << parameters.getCheckAdditionalHLA();
	out << parameters.getIncludeCompatiblePairs();
	out << parameters.getExcludeABDonorsFromSimulation();
	out << parameters.getAllowABBridgeDonors();

	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUISimParameters & parameters)
{
	int opt;
	int util;

	int cycleSize;
	int chainLength;
	int componentSize;

	int numberOfSolutions;

	bool estimateExpectedUtility;
	int numberOfExpectedUtilityIterations;

	bool addAdvantageToHighPRACandidates;
	int praAdvantageCutoff;
	double praAdvantageValue;

	int chainStorage;
	bool reserveODonorsForOCandidates;
	bool checkAdditionalHLA;
	bool includeCompatiblePairs;
	bool excludeABDonorsFromSimulation;
	bool allowABBridgeDonors;
	
	in >> opt >> util >> cycleSize >> chainLength >> componentSize;

	in >> numberOfSolutions >> estimateExpectedUtility >> numberOfExpectedUtilityIterations;

	in >> addAdvantageToHighPRACandidates >> praAdvantageCutoff >> praAdvantageValue;

	in >> chainStorage >> reserveODonorsForOCandidates >> checkAdditionalHLA 
		>> includeCompatiblePairs >> excludeABDonorsFromSimulation >> allowABBridgeDonors;


	parameters.setOptimizationScheme(KPDFunctions::intToOptScheme(opt));
	parameters.setUtilityScheme(KPDFunctions::intToUtilScheme(util));
	parameters.setMaxCycleSize(cycleSize);
	parameters.setMaxChainLength(chainLength);
	parameters.setMaxComponentSize(componentSize);
	parameters.setNumberOfSolutions(numberOfSolutions);
	parameters.setEstimateExpectedUtility(estimateExpectedUtility);
	parameters.setNumberOfExpectedUtilityIterations(numberOfExpectedUtilityIterations);
	parameters.setAddAdvantagetoHighPRACandidates(addAdvantageToHighPRACandidates);
	parameters.setPRAAdvantageCutoff(praAdvantageCutoff);
	parameters.setPRAAdvantageValue(praAdvantageValue);
	parameters.setChainStorage(KPDFunctions::intToChainStorage(chainStorage));
	parameters.setReserveODonorsForOCandidates(reserveODonorsForOCandidates);
	parameters.setCheckAdditionalHLA(checkAdditionalHLA);
	parameters.setIncludeCompatiblePairs(includeCompatiblePairs);
	parameters.setExcludeABDonorsFromSimulation(excludeABDonorsFromSimulation);
	parameters.setAllowABBridgeDonors(allowABBridgeDonors);

	return in;

}