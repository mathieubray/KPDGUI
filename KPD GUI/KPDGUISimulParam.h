#ifndef KPDGUISIMULPARAM_H
#define KPDGUISIMULPARAM_H

#include <string>

#include "Structs.h"

class KPDGUISimulParam {

private:

	bool parametersSet;

	//Simulation Settings
	KPDOptimizationScheme optScheme; //MUC, MEUC, MEUS, SCC
	KPDUtilityScheme utilityScheme; // TRANSPLANTS, SURVIVAL5YEAR, SURVIVAL10YEAR, SCORE
	int maxChainLength;
	
	//Numerical Parameters
	double pairFailureRate;
	double adFailureRate;
	double exogenousFailureRate;	
		
	bool addAdvantageToHighPRACandidates;
	int praAdvantageCutoff;
	double praAdvantageValue;

	int numberOfSolutions;

	//Additional Options
	QString chainStorage; // FIRST, LAST, NONE
	bool reserveODonorsForOCandidates;	
	bool checkDP;
	bool includeCompatiblePairs;
	bool excludeABDonorsFromSimulation;
	bool allowABBridgeDonors;
	

public:
	KPDGUISimulParam();
	~KPDGUISimulParam();

	void processParams(ParamInfoStruct paramInfo);

	bool getParametersSet();
	void setParametersSet(bool flag);
	
	//Simulation Settings
	KPDOptimizationScheme getOptimizationScheme();
	KPDUtilityScheme getUtilityScheme();	
	int getMaxChainLength();

	//Numerical Parameters
	double getPairFailureRate();
	double getADFailureRate();
	double getExogenousFailureRate();

	bool getAddAdvantageToHighPRACandidates();
	int getPRAAdvantageCutoff();
	double getPRAAdvantageValue();

	int getNumberOfSolutions();
	
	//Additional Options
	QString getChainStorage();
	bool getReserveODonorsForOCandidates();
	bool getCheckDP();
	bool getIncludeCompatiblePairs();
	bool getExcludeABDonorsFromSimulation();
	bool getAllowABbridgeDonors();	

	QString toString();
};


#endif