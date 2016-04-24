#ifndef KPDGUISIMPARAMETERS_H
#define KPDGUISIMPARAMETERS_H

#include "DialogSimParameters.h"
#include "EnumsFunctions.h"

class KPDGUISimParameters {

public:
	KPDGUISimParameters();
	~KPDGUISimParameters();

	void changeParameters(DialogSimParameters * d);
	void copyParameters(KPDGUISimParameters * d);

	bool getParametersHaveBeenUpdated();
	void setParametersHaveBeenUpdated(bool flag);

	QString toString();

	//Getters
	KPDOptimizationScheme getOptimizationScheme() const;
	KPDUtilityScheme getUtilityScheme() const;

	int getMaxCycleSize() const;
	int getMaxChainLength() const;
	int getMaxComponentSize() const;

	bool getAddAdvantageToHighPRACandidates() const;
	int getPRAAdvantageCutoff() const;
	double getPRAAdvantageValue() const;

	int getNumberOfSolutions() const;

	bool getEstimateExpectedUtility() const;
	int getNumberOfExpectedUtilityIterations() const;

	KPDChainStorage getChainStorage() const;
	bool getReserveODonorsForOCandidates() const;
	bool getCheckAdditionalHLA() const;
	bool getIncludeCompatiblePairs() const;
	bool getExcludeABDonorsFromSimulation() const;
	bool getAllowABBridgeDonors() const;

	//Setters
	void setOptimizationScheme(KPDOptimizationScheme scheme);
	void setUtilityScheme(KPDUtilityScheme scheme);

	void setMaxCycleSize(int size);
	void setMaxChainLength(int length);
	void setMaxComponentSize(int size);

	void setAddAdvantagetoHighPRACandidates(bool flag);
	void setPRAAdvantageCutoff(int cutoff);
	void setPRAAdvantageValue(double value);

	void setNumberOfSolutions(int solutions);

	void setEstimateExpectedUtility(bool estimate);
	void setNumberOfExpectedUtilityIterations(int iterations);

	void setChainStorage(KPDChainStorage storage);
	void setReserveODonorsForOCandidates(bool flag);
	void setCheckAdditionalHLA(bool flag);
	void setIncludeCompatiblePairs(bool flag);
	void setExcludeABDonorsFromSimulation(bool flag);
	void setAllowABBridgeDonors(bool flag);

private:

	bool parametersHaveBeenUpdated;

	//Simulation Settings
	KPDOptimizationScheme optScheme;
	KPDUtilityScheme utilityScheme;
	
	int maxCycleSize;
	int maxChainLength;
	int maxComponentSize;

	//Numerical Parameters		
	bool addAdvantageToHighPRACandidates;
	int praAdvantageCutoff;
	double praAdvantageValue;

	int numberOfSolutions;

	bool estimateExpectedUtility;
	int numberOfExpectedUtilityIterations;

	//Additional Options
	KPDChainStorage chainStorage;
	bool reserveODonorsForOCandidates;	
	bool checkAdditionalHLA;
	bool includeCompatiblePairs;
	bool excludeABDonorsFromSimulation;
	bool allowABBridgeDonors;

};

QDataStream &operator<<(QDataStream &out, const KPDGUISimParameters & parameters);

QDataStream &operator>>(QDataStream &in, KPDGUISimParameters & parameters);


#endif