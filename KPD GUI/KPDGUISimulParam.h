#ifndef KPDGUISIMULPARAM_H
#define KPDGUISIMULPARAM_H

#include <string>

#include "Structs.h"

using namespace std;

class KPDGUISimulParam {

private:

	bool parametersSet;

	//Simulation Settings
	string outputFolderName;
	string allocScheme; //DPD, NEAD
	string utilityScheme; // Score, Survival5Year, Survival10Year, Transplants
	//string pairEntryScheme; //All, Subset, Fixed, Poisson
	//string adEntryScheme; //All, Subset, Fixed, Chance
	//string samplingScheme; // With, Without (replacement)
	//int pairSelectionSeed;
	//int simulationConditionsSeed;

	//Numerical Parameters	
	//int simulations;
	//int months;
	//double arrivals;
	//double ads;
	int maxChainLength;
	//double attritionRate;
	//double renegeRate;
	//double pairFailureRate;
	//double probReturnToPool;
	//double exogenousFailureRate;
	int tiebreakIterations;

	//Optimization Settings
	bool muc;
	bool meuc;
	bool meus;
	bool scc;
	//bool fallbacks;

	//Data Configuration and Files
	string data_configuration; // Ashlagi, APD Match Run, Michigan, Match Run, Combined
	//string candidate_file;
	//string donor_file;
	//string pair_file;
	//string info_file;
	//string exInfo_file;
	//string ndd_file;
	//string samePatient_file;
	//string comp_file;
	//string weight_file;

	//Output Suppression
	bool outputEdgeInfo;
	bool outputExchangeInfo;
	bool outputCycleInfo;
	bool outputSimInfo;
	bool outputPopulationStats;

	//Additional Flags
	bool praAdvantage;
	bool reserveOtoO;
	bool randomPairFailure;
	string chainstorage;
	bool checkDP;
	bool includeCompatiblePairs;
	bool includeABbridgeDonors;

public:
	KPDGUISimulParam();
	~KPDGUISimulParam();

	void processParams(ParamInfoStruct paramInfo);
	//void printSpecs();

	bool getParametersSet();
	void setParametersSet(bool flag);
	
	//stringstream specs;

	//Simulation Settings
	string getOutputFolderName();
	string getAllocationScheme();
	string getUtilityScheme();
	//string getPairEntryScheme();
	//string getADEntryScheme();
	//string getSamplingScheme();
	//int getPairSelectionSeed();
	//int getSimulationConditionsSeed();

	//Numerical Parameters
	//int getSimulations();
	//int getMonths();
	//double getArrivals();
	//double getADs();
	int getMaxChainLength();
	//double getAttritionRate();
	//double getRenegeRate();
	//double getPairFailureRate();
	//double getProbReturnToPool();
	//double getExogenousFailureRate();
	int getTiebreakIterations();

	//Optimization Settings
	bool getMUC();
	bool getMEUC();
	bool getMEUS();
	bool getSCC();
	//bool getFallbacks();

	//Data Configuration and Files
	string getDataConfiguration();
	//string getCandidateFile();
	//string getDonorFile();
	//string getPairFile();
	//string getInfoFile();
	//string getExtraInfoFile();
	//string getNDDFile();
	//string getSamePatientFile();
	//string getCompFile();
	//string getWeightFile();

	//Output Suppression
	bool getOutputEdgeFlag();
	bool getOutputExchangeFlag();
	bool getOutputCycleFlag();
	bool getOutputSimFlag();
	bool getOutputPopStatsFlag();

	//Additional Flags
	bool getPRAadvantage();
	bool getReserveOtoO();
	bool getRandomPairFailure();
	string getChainStorage();
	bool getCheckDP();
	bool getIncludeCompatiblePairsFlag();
	bool getIncludeABbridgeDonorsFlag();

	QString toString();
};


#endif