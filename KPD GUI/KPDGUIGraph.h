#ifndef KPDGUIGRAPH_H
#define KPDGUIGRAPH_H

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <sstream>

#include "gurobi_c++.h"

#include "KPDGUISimulParam.h"
#include "KPDGUIRecord.h"


class KPDGUISimulation {

public:
	KPDGUISimulation(KPDGUIRecord * record, ParamInfoStruct params);
	~KPDGUISimulation();	

	vector<vector<int> > & getCurrentMatchRunCyclesAndChains();
	vector<vector<int> > & getCurrentMatchRunComponents();

	vector<double> & getUtilityForCurrentMatchRunCyclesAndChains();
	vector<double> & getExpectedUtilityForCurrentMatchRunCyclesAndChains();
	vector<double> & getExpectedUtilityForCurrentMatchRunSets();
	vector<double> & getExpectedUtilityForCurrentMatchRunComponents();
		
	void getOptimalSolution();
	
	vector<vector<int> > & returnSolutionSet();
	vector<double> & returnSolutionObjectives();

	QString getSimLog();

	vector<vector<int> > currentMatchRunStructureNodeLists;

	vector<double> utilityOfCurrentMatchRunCyclesAndChains;
	vector<double> expectedUtilityOfCurrentMatchRunCyclesAndChains;
	vector<double> expectedUtilityOfCurrentMatchRunSets;
	vector<double> expectedUtilityOfCurrentMatchRunComponents;
	
private:	
	
	QString simLog;

	KPDGUIRecord * kpdguiRecord;
	ParamInfoStruct kpdguiParameters;	

	vector<vector<int> > SelectedSolutions;
	vector<int> SelectedStructures;
	vector<double> SolutionObjectives;

	int getChild(int start, int v, vector<int> &visitedVector, vector<vector<bool> > &thisIMatrix);
	double calculateExpectedUtility(vector<int> structure);
	double calculateExpectedUtilityWithFB(vector<int> structure);
	double calculatePartialUtility(int nV, vector<vector<bool> > &incidenceMatrix_temp, vector<vector<double> > &subsubUtilityMatrix, vector<int> & subsubPairTypeVector, vector<bool> & subsubABDonorVector);

	std::string intToString(int number);
};


#endif
