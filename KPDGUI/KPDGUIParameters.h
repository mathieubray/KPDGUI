#ifndef KPDGUIPARAMETERS_H
#define KPDGUIPARAMETERS_H

#include "DialogSimParameters.h"
#include "KPDGUIEnumsFunctions.h"

class KPDGUIParameters {

public:
	KPDGUIParameters();
	~KPDGUIParameters();

	void changeParameters(DialogSimParameters * d);
	void copyParameters(KPDGUIParameters * d);

	bool parametersHaveBeenUpdated();
	void setParametersHaveBeenUpdatedFlag(bool flag);

	QString toString();

	//Getters

	bool getSaveSolution() const;
	QString getSaveSolutionFolder() const;

	bool getCollectArrangements() const;
	int getCollectArrangementsCutoff() const;

	bool getHighlightTopSolution() const;

	KPDOptimizationScheme getOptimizationScheme() const;
	KPDUtilityScheme getUtilityScheme() const;

	int getMaxCycleSize() const;
	int getMaxChainLength() const;
	int getMaxLRSSize() const;

	int getNumberOfSolutions() const;

	bool addAdvantageToHighPRACandidates() const;
	int getPRAAdvantageCutoff() const;
	double getPRAAdvantageValue() const;

	bool estimateExpectedUtility() const;
	int getNumberOfExpectedUtilityIterations() const;

	bool reserveODonorsForOCandidates() const;
	bool checkAdditionalHLA() const;
	bool includeCompatiblePairs() const;
	bool excludeABDonorsFromSimulation() const;
	bool allowABBridgeDonors() const;

	//Setters
	void setSaveSolution(bool save);
	void setSaveSolutionFolder(QString folder);

	void setCollectArrangements(bool collect);
	void setCollectArrangementsCutoff(int cutoff);

	void setHighlightTopSolution(bool highlight);

	void setOptimizationScheme(KPDOptimizationScheme scheme);
	void setUtilityScheme(KPDUtilityScheme scheme);

	void setMaxCycleSize(int size);
	void setMaxChainLength(int length);
	void setMaxLRSSize(int size);

	void setNumberOfSolutions(int solutions);

	void setAddAdvantagetoHighPRACandidatesFlag(bool flag);
	void setPRAAdvantageCutoff(int cutoff);
	void setPRAAdvantageValue(double value);

	void setEstimateExpectedUtilityFlag(bool flag);
	void setNumberOfExpectedUtilityIterations(int iterations);

	void setReserveODonorsForOCandidatesFlag(bool flag);
	void setCheckAdditionalHLAFlag(bool flag);
	void setIncludeCompatiblePairsFlag(bool flag);
	void setExcludeABDonorsFromSimulationFlag(bool flag);
	void setAllowABBridgeDonorsFlag(bool flag);

private:

	bool parametersUpdated;

	bool saveSolution;
	QString saveSolutionFolder;

	bool collectArrangements;
	int collectArrangementsCutoff;

	bool highlightTopSolution;

	//Simulation Settings
	KPDOptimizationScheme optimizationScheme;
	KPDUtilityScheme utilityScheme;
	
	int maxCycleSize;
	int maxChainLength;
	int maxLRSSize;
	
	int numberOfSolutions;
	
	//Numerical Parameters		
	bool addAdvantage;
	int advantageCutoff;
	double advantageValue;
	
	bool estimateEU;
	int numberOfEUIterations;

	bool reserveOforO;	
	bool checkHLA;
	bool includeCompatible;
	bool excludeABDonors;
	bool allowABBridge;

};

QDataStream &operator<<(QDataStream &out, const KPDGUIParameters & parameters);

QDataStream &operator>>(QDataStream &in, KPDGUIParameters & parameters);


#endif