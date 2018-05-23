#include "ParameterInfo.h"

ParameterInfo::ParameterInfo(){

}

ParameterInfo::~ParameterInfo(){

}

KPDOptimizationScheme ParameterInfo::getOptScheme() const{
	return optScheme;
}

KPDUtilityScheme ParameterInfo::getUtilityScheme() const{
	return utilityScheme;
}

int ParameterInfo::getMaxSize() const{
	return maxSize;
}

double ParameterInfo::getPairFailureRate() const{
	return pairFailureRate;
}

double ParameterInfo::getADFailureRate() const{
	return adFailureRate;
}

double ParameterInfo::getExogenousFailureRate() const{
	return exogenousFailureRate;
}

bool ParameterInfo::getAddAdvantageToHighPRACandidates() const{
	return addAdvantageToHighPRACandidates;
}

int ParameterInfo::getPRAAdvantageCutoff() const{
	return praAdvantageCutoff;
}

double ParameterInfo::getPRAAdvantageValue() const{
	return praAdvantageValue;
}

int ParameterInfo::getNumberOfSolutions() const{
	return numberOfSolutions;
}

int ParameterInfo::getNumberOfEUSimulations() const{
	return numberOfEUSimulations;
}

QString ParameterInfo::getChainStorage() const{
	return chainStorage;
}

bool ParameterInfo::getReserveODonorsForOCandidates() const{
	return reserveODonorsForOCandidates;
}

bool ParameterInfo::getCheckAdditionalHLA() const{
	return checkAdditionalHLA;
}

bool ParameterInfo::getIncludeCompatiblePairs() const{
	return includeCompatiblePairs;
}

bool ParameterInfo::getExcludeABDonorsFromSimulation() const{
	return excludeABDonorsFromSimulation;
}

bool ParameterInfo::getAllowABBridgeDonors() const{
	return allowABBridgeDonors;
}

//Setters
void ParameterInfo::setOptScheme(KPDOptimizationScheme scheme){
	optScheme = scheme;
}

void ParameterInfo::setUtilityScheme(KPDUtilityScheme scheme){
	utilityScheme = scheme;
}

void ParameterInfo::setMaxSize(int size){
	maxSize = size;
}

void ParameterInfo::setPairFailureRate(double rate){
	pairFailureRate = rate;
}

void ParameterInfo::setADFailureRate(double rate){
	adFailureRate = rate;
}

void ParameterInfo::setExogenousFailureRate(double rate){
	exogenousFailureRate = rate;
}

void ParameterInfo::setAddAdvantagetoHighPRACandidates(bool flag){
	addAdvantageToHighPRACandidates = flag;
}

void ParameterInfo::setPRAAdvantageCutoff(int cutoff){
	praAdvantageCutoff = cutoff;
}

void ParameterInfo::setPRAAdvantageValue(double value){
	praAdvantageValue = value;
}

void ParameterInfo::setNumberOfSolutions(int solutions){
	numberOfSolutions = solutions;
}

void ParameterInfo::setNumberOfEUSimulations(int simulations){
	numberOfEUSimulations = simulations;
}

void ParameterInfo::setChainStorage(QString storage){
	chainStorage = storage;
}

void ParameterInfo::setReserveODonorsForOCandidates(bool flag){
	reserveODonorsForOCandidates = flag;
}

void ParameterInfo::setCheckAdditionalHLA(bool flag){
	checkAdditionalHLA = flag;
}

void ParameterInfo::setIncludeCompatiblePairs(bool flag){
	includeCompatiblePairs = flag;
}

void ParameterInfo::setExcludeABDonorsFromSimulation(bool flag){
	excludeABDonorsFromSimulation = flag;
}

void ParameterInfo::setAllowABBridgeDonors(bool flag){
	allowABBridgeDonors = flag;
}