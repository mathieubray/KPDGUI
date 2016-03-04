#ifndef PARAMETERINFO_H
#define PARAMETERINFO_H

#include <qstring.h>
#include <qvector.h>

#include "DialogSimParameters.h"

class ParameterInfo {

public:
	ParameterInfo();
	~ParameterInfo();

	//Getters
	KPDOptimizationScheme getOptScheme() const;
	KPDUtilityScheme getUtilityScheme() const;
	int getMaxSize() const;

	double getPairFailureRate() const;
	double getADFailureRate() const;
	double getExogenousFailureRate() const;

	bool getAddAdvantageToHighPRACandidates() const;
	int getPRAAdvantageCutoff() const;
	double getPRAAdvantageValue() const;

	int getNumberOfSolutions() const;
	int getNumberOfEUSimulations() const;

	QString getChainStorage() const;
	bool getReserveODonorsForOCandidates() const;
	bool getCheckAdditionalHLA() const;
	bool getIncludeCompatiblePairs() const;
	bool getExcludeABDonorsFromSimulation() const;
	bool getAllowABBridgeDonors() const;

	//Setters
	void setOptScheme(KPDOptimizationScheme scheme);
	void setUtilityScheme(KPDUtilityScheme scheme);
	void setMaxSize(int size);

	void setPairFailureRate(double rate);
	void setADFailureRate(double rate);
	void setExogenousFailureRate(double rate);

	void setAddAdvantagetoHighPRACandidates(bool flag);
	void setPRAAdvantageCutoff(int cutoff);
	void setPRAAdvantageValue(double value);

	void setNumberOfSolutions(int solutions);
	void setNumberOfEUSimulations(int simulations);

	void setChainStorage(QString storage);
	void setReserveODonorsForOCandidates(bool flag);
	void setCheckAdditionalHLA(bool flag);
	void setIncludeCompatiblePairs(bool flag);
	void setExcludeABDonorsFromSimulation(bool flag);
	void setAllowABBridgeDonors(bool flag);


private:
	//Simulation Settings
	KPDOptimizationScheme optScheme;
	KPDUtilityScheme utilityScheme;
	int maxSize; //Chain Length for MUC, MEUC, MEUS, Number of Nodes for SCC

	//Numerical Parameters
	double pairFailureRate;
	double adFailureRate;
	double exogenousFailureRate;

	bool addAdvantageToHighPRACandidates;
	int praAdvantageCutoff;
	double praAdvantageValue;

	int numberOfSolutions;
	int numberOfEUSimulations;

	//Additional Options
	QString chainStorage;
	bool reserveODonorsForOCandidates;
	bool checkAdditionalHLA;
	bool includeCompatiblePairs;
	bool excludeABDonorsFromSimulation;
	bool allowABBridgeDonors;

};

#endif