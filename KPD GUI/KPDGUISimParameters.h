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

	bool getParametersSet();
	void setParametersSet(bool flag);

	QString toString();

	//Getters
	KPDOptimizationScheme getOptimizationScheme() const;
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

	KPDChainStorage getChainStorage() const;
	bool getReserveODonorsForOCandidates() const;
	bool getCheckAdditionalHLA() const;
	bool getIncludeCompatiblePairs() const;
	bool getExcludeABDonorsFromSimulation() const;
	bool getAllowABBridgeDonors() const;

	//Setters
	void setOptimizationScheme(KPDOptimizationScheme scheme);
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

	void setChainStorage(KPDChainStorage storage);
	void setReserveODonorsForOCandidates(bool flag);
	void setCheckAdditionalHLA(bool flag);
	void setIncludeCompatiblePairs(bool flag);
	void setExcludeABDonorsFromSimulation(bool flag);
	void setAllowABBridgeDonors(bool flag);

private:

	bool parametersSet;

	//Simulation Settings
	KPDOptimizationScheme optScheme;
	KPDUtilityScheme utilityScheme;
	int maxSize; //Max Chain Length for MUC, MEUC, MEUS; Max Component Size for SCC
	
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