#ifndef KPDGUIMATCHRUN_H
#define KPDGUIMATCHRUN_H

#include "gurobi_c++.h"

#include "KPDGUIParameters.h"
#include "KPDGUINode.h"
#include "KPDGUIMatch.h"
#include "KPDGUICrossmatchFunctions.h"
#include "KPDGUIRNG.h"

#include <vector>
#include <set>
#include <queue>
#include <map>

#include <QtGui>
#include <QtWidgets>

class KPDGUIMatchRun {

private:

	QProgressDialog * progressBar;
	
	//Node Information
	std::vector<KPDGUINode *> matchRunNodeVector;
	std::vector<KPDNodeType> matchRunNodeTypeVector;
	
	std::vector<std::vector<std::vector<bool> > > matchRunDonorIncidenceMatrix;
	std::vector<std::vector<std::vector<double> > > matchRunSuccessProbabilitiesMatrix;
	std::vector<std::vector<std::vector<double> > > matchRunUtilityMatrix;
	std::vector<std::vector<std::vector<KPDCrossmatchResult> > > matchRunCrossmatchMatrix;
	
	std::vector<std::vector<bool> > matchRunIncidenceMatrix;
	std::vector<std::vector<bool> > matchRunIncidenceMatrixReduced;


	//Match Run Information
	int matchRunNumberOfPairs;
	int matchRunNumberOfNDDs;
	int matchRunNumberOfNodes;

	std::vector<int> currentMatchRunNodes;


	//Match Run Results
	std::vector<std::vector<int> > matchRunArrangements;
	std::vector<bool> matchRunArrangementHasNDD;
	std::vector<double> assignedValueOfMatchRunArrangements;
	
	std::vector<std::vector<int> > matchRunSelectedSolutions;
	std::vector<double> assignedValueOfMatchRunSolutions;


	//Relevant Parameters
	int maxCycleSize;
	int maxChainLength;
	int maximum;
	int maxLRSSize;

	KPDOptimizationScheme optScheme;
	KPDUtilityScheme utilityScheme;

	bool addAdvantageToHighPRACandidates;
	double praAdvantageCutoff;
	double praAdvantageValue;

	bool estimateEU;
	int numberOfExpectedUtilityIterations;

	bool reserveOforO;
	bool checkHLA;
	bool includeCompatible;
	bool excludeABDonors;
	bool allowABBridgeDonors;

	
	//Helper Functions for Collecting Arrangements
	bool isCompatible(KPDGUINode * node);

	int selectDonor(int donorNodeID, int candidateNodeID);
	int getChild(int start, int v, std::vector<int> &visitedVector, std::vector<std::vector<bool> > &incidence);

	void getLRSPairsOnly();
	int getChildLRSPairsOnly(std::vector<int> &tree, std::vector<int> &level, std::vector<int> &pairs, std::vector<bool> &visited, int next, int childLevel);
	
	void getLRSWithNDDs();
	int getChildLRSWithNDDs(bool &childIsAdjacentToLowerLevels, std::vector<std::vector<int> > &trees, std::vector<std::vector<int> > &levels, std::vector<int> &inducedLevels,
		std::vector<bool> &visited, int &next, int &nextNDD, int &childLevel, int &childLevelNDD, bool &childCanBeNDD);
	
	bool validateLRSBounds(std::vector<int> &arrangement);


	//Helper Functions for Assigning Expected Utilities
	double calculateExpectedUtility(std::vector<int> &arrangement);
	double estimateExpectedUtility(std::vector<int> &arrangement);
	double calculatePartialUtility(int nV, std::vector<std::vector<bool> > & incidence, std::vector<std::vector<std::vector<double> > > & utility, std::vector<KPDNodeType> & nodeTypes, std::vector<std::vector<KPDBloodType> > & donorBloodTypes);

	QString matchRunNodeList;
	QString matchRunMatchList;

	QString matchRunLog;

public:
	KPDGUIMatchRun(QList<KPDGUINode *> nodes, KPDGUIParameters * params, QProgressDialog * progress);
	~KPDGUIMatchRun();	

	//Use Pool Information to Generate Matrices
	void generateMatrices(QList<KPDGUINode *> nodes);

	//Collect Arrangements (Cycles & Chains, or LRSs)
	void collectCyclesAndChainsForCurrentMatchRun();
	void collectLRSForCurrentMatchRun();

	//Assign Expected Utilities
	void assignUtilitiesForCurrentMatchRun();
	void assignExpectedUtilitiesForCurrentMatchRun();
	
	//Select Arrangements by Optimization
	void getOptimalSolutionForCurrentMatchRun(KPDOptimizationScheme scheme, int numberOfSolutions);

	//Retrieve Match Run Results
	QVector<QVector<KPDGUINode *> > getMatchRunArrangementNodes();
	QVector<QVector<KPDGUIMatch *> > getMatchRunArrangementMatches();
	QVector<double> getAssignedValueOfMatchRunArrangements();

	QVector<QVector<int> > getMatchRunSelectedSolutions();
	QVector<double> getAssignedValueOfMatchRunSolutions();
	

	//Output

	QString getNodeListString();
	QString getMatchListString();

	QString printLog();	

};


#endif
