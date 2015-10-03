#include "KPDGUISimulParam.h"

KPDGUISimulParam::KPDGUISimulParam(){
	//Default Parameters

	parametersSet = false;

	//Simulation Settings
	optScheme = KPDOptimizationScheme::MUC;
	utilityScheme = KPDUtilityScheme::TRANSPLANTS;	
	maxChainLength = 2;
	
	//Numerical Parameters
	pairFailureRate = 0.1;
	adFailureRate = 0.0;
	exogenousFailureRate = 0.0;	
		
	addAdvantageToHighPRACandidates = false;
	praAdvantageCutoff = 100;
	praAdvantageValue = 0.0;

	numberOfSolutions = 1;

	//Additional Options
	chainStorage = "NONE";
	reserveODonorsForOCandidates = false;	
	checkDP = false;
	includeCompatiblePairs = false;
	excludeABDonorsFromSimulation = false;
	allowABBridgeDonors = false;
	
}

KPDGUISimulParam::~KPDGUISimulParam(){

}


void KPDGUISimulParam::processParams(ParamInfoStruct paramInfo){

	parametersSet = true;

	optScheme = paramInfo.optScheme;
	utilityScheme = paramInfo.utilityScheme;
	maxChainLength = paramInfo.maxChainLength;

	pairFailureRate = paramInfo.pairFailureRate;
	adFailureRate = paramInfo.adFailureRate;
	exogenousFailureRate = paramInfo.exogenousFailureRate;

	addAdvantageToHighPRACandidates = paramInfo.addAdvantageToHighPRACandidates;
	praAdvantageCutoff = paramInfo.praAdvantageCutoff;
	praAdvantageValue = paramInfo.praAdvantageValue;

	numberOfSolutions = paramInfo.numberOfSolutions;

	chainStorage = paramInfo.chainStorage;
	reserveODonorsForOCandidates = paramInfo.reserveODonorsForOCandidates;
	checkDP = paramInfo.checkDP;
	includeCompatiblePairs = paramInfo.includeCompatiblePairs;
	excludeABDonorsFromSimulation = paramInfo.excludeABDonorsFromSimulation;
	allowABBridgeDonors = paramInfo.allowABBridgeDonors;
	
}

bool KPDGUISimulParam::getParametersSet(){
	return parametersSet;
}

void KPDGUISimulParam::setParametersSet(bool flag){
	parametersSet = flag;
}

KPDOptimizationScheme KPDGUISimulParam::getOptimizationScheme(){
	return optScheme;
}

KPDUtilityScheme KPDGUISimulParam::getUtilityScheme(){
	return utilityScheme;
}

int KPDGUISimulParam::getMaxChainLength(){
	return maxChainLength;
}

double KPDGUISimulParam::getPairFailureRate(){
	return pairFailureRate;
}

double KPDGUISimulParam::getADFailureRate(){
	return adFailureRate;
}

double KPDGUISimulParam::getExogenousFailureRate(){
	return exogenousFailureRate;
}

bool KPDGUISimulParam::getAddAdvantageToHighPRACandidates(){
	return addAdvantageToHighPRACandidates;
}

int KPDGUISimulParam::getPRAAdvantageCutoff(){
	return praAdvantageCutoff;
}

double KPDGUISimulParam::getPRAAdvantageValue(){
	return praAdvantageValue;
}

int KPDGUISimulParam::getNumberOfSolutions(){
	return numberOfSolutions;
}

QString KPDGUISimulParam::getChainStorage(){
	return chainStorage;
}

bool KPDGUISimulParam::getReserveODonorsForOCandidates(){
	return reserveODonorsForOCandidates;
}

bool KPDGUISimulParam::getCheckDP(){
	return checkDP;
}

bool KPDGUISimulParam::getIncludeCompatiblePairs(){
	return includeCompatiblePairs;
}

bool KPDGUISimulParam::getExcludeABDonorsFromSimulation(){
	return excludeABDonorsFromSimulation;
}

bool KPDGUISimulParam::getAllowABbridgeDonors(){
	return allowABBridgeDonors;
}

QString KPDGUISimulParam::toString(){
	QString parameterString = "";

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
	
	parameterString.append("Maximum Chain Length: " + QString::number(maxChainLength) + "\n");

	parameterString.append("Pair Failure Rate: " + QString::number(pairFailureRate) + "\n");
	parameterString.append("AD Failure Rate: " + QString::number(adFailureRate) + "\n");
	parameterString.append("Exogenous Match Failure Rate: " + QString::number(exogenousFailureRate) + "\n");
	if (numberOfSolutions > 1){
		parameterString.append(numberOfSolutions + " Alternate Solutions Will Be Produced\n");
	}
	
	if (addAdvantageToHighPRACandidates){
		parameterString.append("Add Advantage To High PRA Recipients: Extra " + QString::number(praAdvantageValue) + " for PRA Above " + QString::number(praAdvantageCutoff) + "\n");		
	}
	else {
		parameterString.append("No Added Advantage For High PRA Recipients\n");
	}

	if (chainStorage == "FIRST"){
		parameterString.append("Structures with ADs are Stored First Among Possible Structures");
	}
	else if (chainStorage == "LAST"){
		parameterString.append("Structures with ADs are Stored Last Among Possible Structures");
	}
	
	if (reserveODonorsForOCandidates){
		parameterString.append("O Donors Reserved For O Recipients\n");
	}
	else {
		parameterString.append("O Donors Not Explicitly Reserved For O Recipients\n");
	}
	
	if (checkDP){
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