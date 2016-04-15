#ifndef KPDGUISIMULATION_H
#define KPDGUISIMULATION_H

#include <vector>
#include <set>
#include <queue>
#include <map>
#include <iostream>
#include <sstream>

#include "gurobi_c++.h"

#include "KPDGUISimParameters.h"
#include "KPDGUIRecord.h"

#include "RNG.h"


class KPDGUISimulation {

public:
	KPDGUISimulation(KPDGUIRecord * record, KPDGUISimParameters * params);
	~KPDGUISimulation();	

	int selectDonor(int donorNodeID, int candidateNodeID);

	vector<vector<int> > & getCurrentMatchRunCyclesAndChains(QProgressDialog * progressBar);
	vector<vector<int> > & getCurrentMatchRunComponentsNaive(QProgressDialog * progressBar);
	vector<vector<int> > & getCurrentMatchRunComponentsNew(QProgressDialog * progressBar);

	vector<double> & getUtilityForCurrentMatchRunCyclesAndChains(QProgressDialog * progressBar);
	vector<double> & getExpectedUtilityForCurrentMatchRunCyclesAndChains(QProgressDialog * progressBar);
	vector<double> & getExpectedUtilityForCurrentMatchRunSets(QProgressDialog * progressBar);
	vector<double> & getExpectedUtilityForCurrentMatchRunComponents(QProgressDialog * progressBar);
		
	void getOptimalSolutionForCurrentMatchRun(QProgressDialog * progressBar);
	
	vector<vector<int> > & returnSolutionSet();
	vector<double> & returnSolutionObjectives();

	QString getSimLog();

	vector<int> currentMatchRunNodes;
	vector<vector<int> > currentMatchRunStructures;

	vector<double> utilityOfCurrentMatchRunCyclesAndChains;
	vector<double> expectedUtilityOfCurrentMatchRunCyclesAndChains;
	vector<double> expectedUtilityOfCurrentMatchRunSets;
	vector<double> expectedUtilityOfCurrentMatchRunComponents;
	
private:	
	
	QString simLog;

	KPDGUIRecord * kpdguiRecord;
	KPDGUISimParameters * kpdguiParameters;	

	std::vector<std::vector <bool> > incidenceMatrix;
	std::vector<std::vector<std::vector<int> > > associatedDonorMatrix;
	std::vector<std::vector<std::vector<double> > > associatedScoresMatrix;
	std::vector<std::vector<std::vector<double> > > associated5YearSurvivalMatrix;
	std::vector<std::vector<std::vector<double> > > associated10YearSurvivalMatrix;
	std::vector<std::vector<std::vector<double> > > associatedProbabilitiesMatrix;
	std::vector<std::vector<std::vector<int> > > associatedLabCrossmatchesMatrix;
	std::vector<AdditionalNodeInfo> nodeInfoVector;

	vector<vector<int> > selectedSolutions;
	vector<int> selectedStructures;
	vector<double> solutionObjectives;

	int getChild(int start, int v, vector<int> &visitedVector, vector<vector<bool> > &incidence);

	void getSCCPairsOnly(QProgressDialog * progressBar);
	int getChildSCCPairsOnly(std::vector<int> &tree, std::vector<int> &level, std::vector<int> &pairs, std::vector<bool> &visited, int next, int childLevel, int nodes, std::vector<std::vector<bool> > &incidence);
	void getSCCWithADs(QProgressDialog * progressBar);
	int getChildSCCWithADs(bool &childIsAdjacentToLowerLevels, std::vector<std::vector<int> > &trees, std::vector<std::vector<int> > &levels, std::vector<int> &inducedLevels, std::vector<int> &ordered, std::vector<bool> &visited, int &next, int &nextAD, int &childLevel, int &childLevelAD, bool &childCanBeAD, int &ads, std::vector<std::vector<bool> > &incidence);

	bool judgeReverseTreeSCCPair(std::vector<int> &pairs, std::vector<int> &tree, int size, std::vector<std::vector<bool> > &incidence);

	double calculateExpectedUtility(vector<int> structure, KPDUtilityScheme scheme);
	double calculateExpectedUtilityWithFallbacks(vector<int> structure);
	double estimateExpectedUtilityWithFallbacks(std::vector<int> &structure);

	double calculatePartialUtility(int nV, vector<vector<bool> > &incidence, vector<vector<vector<double> > > &utility, vector<KPDNodeType> & nodeTypes, vector<vector<KPDBloodType> > & bloodTypes);

	std::string intToString(int number);

	RNG rngExpectedUtilitySimulation;
};


#endif
