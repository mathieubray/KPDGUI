#include "KPDGUISimParameters.h"

KPDGUISimParameters::KPDGUISimParameters(){
	//Default Parameters

	parametersSet = false;

	//Simulation Settings
	optScheme = KPDOptimizationScheme::MUC;
	utilityScheme = KPDUtilityScheme::TRANSPLANTS;	
	maxSize = 2;
	
	//Numerical Parameters
	pairFailureRate = 0.1;
	adFailureRate = 0.0;
	exogenousFailureRate = 0.0;	
		
	addAdvantageToHighPRACandidates = false;
	praAdvantageCutoff = 100;
	praAdvantageValue = 0.0;

	numberOfSolutions = 1;
	numberOfEUSimulations = 100;

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

	parametersSet = true;

	optScheme = KPDFunctions::intToOptScheme(d->optComboBox->currentIndex());
	utilityScheme = KPDFunctions::intToUtilScheme(d->utilComboBox->currentIndex());
	maxSize = d->sizeSpinBox->value();

	pairFailureRate = d->pairFailureRateSpinBox->value();
	adFailureRate = d->adFailureRateSpinBox->value();
	exogenousFailureRate = d->exogenousFailureRateSpinBox->value();

	addAdvantageToHighPRACandidates = d->praBox->isChecked();
	praAdvantageCutoff = d->praCutoffSpinBox->value();
	praAdvantageValue = d->praAdvantageSpinBox->value();

	numberOfSolutions = d->solutionsSpinBox->value();
	numberOfEUSimulations = d->euSimSpinBox->value();

	/*QString chainStorage = d->chainStorageComboBox->currentText();
	if (chainStorage == "As They Are Found"){
		chainStorage = "NONE";
	}
	else if (chainStorage == "First"){
		chainStorage = "FIRST";
	}
	else if (chainStorage == "Last"){
		chainStorage = "LAST";
	}*/
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
	maxSize = d->getMaxSize();

	pairFailureRate = d->getPairFailureRate();
	adFailureRate = d->getADFailureRate();
	exogenousFailureRate = d->getExogenousFailureRate();

	addAdvantageToHighPRACandidates = d->getAddAdvantageToHighPRACandidates();
	praAdvantageCutoff = d->getPRAAdvantageCutoff();
	praAdvantageValue = d->getPRAAdvantageValue();

	numberOfSolutions = d->getNumberOfSolutions();
	numberOfEUSimulations = d->getNumberOfEUSimulations();

	chainStorage = d->getChainStorage();
	reserveODonorsForOCandidates = d->getReserveODonorsForOCandidates();
	checkAdditionalHLA = d->getCheckAdditionalHLA();
	includeCompatiblePairs = d->getIncludeCompatiblePairs();
	excludeABDonorsFromSimulation = d->getExcludeABDonorsFromSimulation();
	allowABBridgeDonors = d->getAllowABBridgeDonors();
}

bool KPDGUISimParameters::getParametersSet(){
	return parametersSet;
}

void KPDGUISimParameters::setParametersSet(bool flag){
	parametersSet = flag;
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
		parameterString.append("Maximum Chain Length: " + QString::number(maxSize) + "\n");
	}
	else {
		parameterString.append("Maximum Locally Relevant Subgraph Size: " + QString::number(maxSize) + "\n");
	}

	parameterString.append("Pair Failure Rate: " + QString::number(pairFailureRate) + "\n");
	parameterString.append("AD Failure Rate: " + QString::number(adFailureRate) + "\n");
	parameterString.append("Exogenous Match Failure Rate: " + QString::number(exogenousFailureRate) + "\n");
	if (numberOfSolutions > 1){
		parameterString.append(numberOfSolutions + " Alternate Solutions Will Be Produced\n");
	}
	if (optScheme == KPDOptimizationScheme::SCC){
		parameterString.append(numberOfEUSimulations + " Simulations used to Calculate Expected Utility\n");
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

int KPDGUISimParameters::getMaxSize() const {
	return maxSize;
}

double KPDGUISimParameters::getPairFailureRate() const {
	return pairFailureRate;
}

double KPDGUISimParameters::getADFailureRate() const {
	return adFailureRate;
}

double KPDGUISimParameters::getExogenousFailureRate() const {
	return exogenousFailureRate;
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

int KPDGUISimParameters::getNumberOfEUSimulations() const {
	return numberOfEUSimulations;
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

void KPDGUISimParameters::setMaxSize(int size){
	maxSize = size;
}

void KPDGUISimParameters::setPairFailureRate(double rate){
	pairFailureRate = rate;
}

void KPDGUISimParameters::setADFailureRate(double rate){
	adFailureRate = rate;
}

void KPDGUISimParameters::setExogenousFailureRate(double rate){
	exogenousFailureRate = rate;
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

void KPDGUISimParameters::setNumberOfEUSimulations(int simulations){
	numberOfEUSimulations = simulations;
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
	out << qint32(parameters.getMaxSize());

	out << qreal(parameters.getPairFailureRate());
	out << qreal(parameters.getADFailureRate());
	out << qreal(parameters.getExogenousFailureRate());

	out << parameters.getAddAdvantageToHighPRACandidates();
	out << qint32(parameters.getPRAAdvantageCutoff());
	out << qreal(parameters.getPRAAdvantageValue());

	out << qint32(parameters.getNumberOfSolutions());
	out << qint32(parameters.getNumberOfEUSimulations());

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
	int size;

	double pairFailureRate;
	double adFailureRate;
	double exogenousFailureRate;

	int numberOfSolutions;
	int numberOfEUSimulations;

	bool addAdvantageToHighPRACandidates;
	int praAdvantageCutoff;
	double praAdvantageValue;

	int chainStorage;
	bool reserveODonorsForOCandidates;
	bool checkAdditionalHLA;
	bool includeCompatiblePairs;
	bool excludeABDonorsFromSimulation;
	bool allowABBridgeDonors;
	
	in >> opt >> util >> size;
	in >> pairFailureRate >> adFailureRate >> exogenousFailureRate;

	in >> numberOfSolutions >> numberOfEUSimulations;

	in >> addAdvantageToHighPRACandidates >> praAdvantageCutoff >> praAdvantageValue;

	in >> chainStorage >> reserveODonorsForOCandidates >> checkAdditionalHLA 
		>> includeCompatiblePairs >> excludeABDonorsFromSimulation >> allowABBridgeDonors;


	parameters.setOptimizationScheme(KPDFunctions::intToOptScheme(opt));
	parameters.setUtilityScheme(KPDFunctions::intToUtilScheme(util));
	parameters.setMaxSize(size);
	parameters.setPairFailureRate(pairFailureRate);
	parameters.setADFailureRate(adFailureRate);
	parameters.setExogenousFailureRate(exogenousFailureRate);
	parameters.setNumberOfSolutions(numberOfSolutions);
	parameters.setNumberOfEUSimulations(numberOfEUSimulations);
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