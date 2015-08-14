#ifndef KPDGUIGRAPH_H
#define KPDGUIGRAPH_H

#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <sstream>

#include "gurobi_c++.h"

#include "KPDGUISimulParam.h"
#include "Structs.h"

using namespace std;

//struct PairInfo;

// Struct contains pair information
/*struct PairInfo {
	int pairLabel;   //Original ID from input file

	int pairID;		//Identifies this vertex outside the implementation (not used within the Graph class for implementation)
	int poolID;		//Identifies this vertex inside the Graph class
	int donorType;	//0: regular; 1: AL; 2: BD;

	int donorID;
	string donorBT;
	int donorAge;
	bool donorMale;
	string donorRace;
	double donorWeight;
	double donorBMI;

	int recipID;
	string recipBT;
	int recipAge;
	bool recipMale;
	string recipRace;
	bool recipDiabetes;
	double recipWeight;
	double recipBMI;
	double recipPRA;
	bool recipPrevTrans;
	double recipTOD;
	bool recipHepC;

	double uncertainty;
	vector<int> pairAvailabilityVector;
	vector<int> pairAttritionVector;
	vector<int> pairRenegeVector;
	vector<int> pairSTBDRenegeVector;
	int levelCode;
};*/

//Lists of functions, constants used by the "Graph" class
//Details for individual functions given by their declaration
template <typename VertexType >
class Graph {

public:
	Graph(int sID, string strategy, KPDGUISimulParam * params);
	~Graph();
	void clear();
	//void clearResults();

	stringstream simLog;

	VertexType *addVertex(int pairID, Pair pair);
	VertexType *removeVertex(int pairID);

	//VertexType *getVertexByPairID(int pairID);
	//VertexType *getVertexByPoolID(int poolID);

	int getTotalNumberVertices();
	//int getTotalNumberVerticesEver();
	int getTotalNumberEdges();

	/*vector<VertexType *> &getPoolIDVector();

	vector<vector <int > > &getViableTransplantMatrix();
	vector<vector <double > > &getScoreMatrix();
	vector<vector <double > > &getSurvival5yearMatrix();
	vector<vector <double > > &getSurvival10yearMatrix();
	vector<vector <double > > &getProbabilityMatrix();
	vector<vector <int> > &getLabCrossmatchMatrix();
	vector<vector <bool> > &getIncidenceMatrix();
	vector<PairInfo> &getPairVector(); */

	int getPoolID(int pairID);
	int getPairID(int poolID);

	//By pairID
	void addEdge(int start, int end);
	void addEdgeViableTransplant(int start, int end, int viableTransplant);
	void addEdgeScore(int start, int end, double score);
	void addEdge5yearSurvival(int start, int end, double survival);
	void addEdge10yearSurvival(int start, int end, double survival);
	void addEdgeProbability(int start, int end, double probability);
	void addEdgeLabCrossmatch(int start, int end, int labCrossmatch);

	//By poolID
	void addEdgeByPoolID(int start, int end);
	void addEdgeViableTransplantByPoolID(int start, int end, int viableTransplant);
	void addEdgeScoreByPoolID(int start, int end, double utility);
	void addEdgeSurvival5yearByPoolID(int start, int end, double survival);
	void addEdgeSurvival10yearByPoolID(int start, int end, double survival);
	void addEdgeProbabilityByPoolID(int start, int end, double probability);
	void addEdgeLabCrossmatchByPoolID(int start, int end, int labCrossmatch);

	void removeEdge(int start, int end);
	void removeEdgeByPoolID(int start, int end);

	void removeEdgesFrom(int pairID);			//Remove all the edges starting from vertex pairID
	void removeEdgesTo(int pairID);				//Remove all the edges ending at vertex pairID
	void addEdgesTo(int pairID);				//Add edges from all vertices to vertex pairID
	void correctBridgeDonors();

	void setLastMonth();

	vector<vector<int> > &getAllEC();
	vector<vector<int> > &getAllES();
	vector<vector<int > > &getAllSCC();

	double calculateExpectation(string utility, bool chain, vector<int> transplants);
	double calculateExpectationFB(bool chain, vector<int> transplants,
		vector<vector<double> > &subUtilityMatrix, vector<vector<double> > &subProbabilityMatrix, vector<double> &subProbVertexVector);

	vector<double> & getUForAllEC();		// Has to be called after getAllEC() was called;
	vector<double> & getEUForAllEC();		// Has to be called after getAllEC() was called;
	vector<double> & getEUForAllES();		// Has to be called after getAllES() was called;
	vector<double> & getEUForAllSCC();		// Has to be called after getAllSCC() was called;

	double getPartialUtility(int nV, vector<vector<bool> > &incidenceMatrix_temp, vector<vector<double> > &subsubUtilityMatrix, vector<int> & subsubStatusVector);

	//void getLongestCycle (int nV, vector<int> & longestVec, vector<vector<bool> > & incidenceMatrix_temp);

	double getEUForFB(vector<int> &FB, vector<vector<bool> > &subIncidenceMatrix, vector<vector<double> > &subUtilityMatrix,
		vector<vector<double> > &subProbabilityMatrix, vector<double> &subProbVertexVector, vector<int> &subStatusVector, bool debug);


	int getMUCInFB(int nV, vector<vector<bool> > &incidenceMatrix_temp, vector<vector<double> > &subUtilityMatrix, vector<int> &subStatusVector, vector<int> &indexToPoolIDVector);

	double getMaxUtilityInFB(int nV, vector<vector<bool> > & incidenceMatrix_temp, vector<vector<double> > &subUtilityMatrix);

	void outputCycles();

	//void getMUC();
	//void getMEUC();
	//void getMEUS();
	//void getMEUSCC();

	void getOptimalSolution(string scheme);
	vector<vector<int> > & returnSolutionSet();
	vector<int> & returnOptimalSolution();
	vector<double> & returnSolutionObjectives();

	void getFB(int nV, vector<int> & indexToPoolIDVector);

	void getTransplantStats(int dPoolID, int rPoolID);

	void simulation(int month);
	void simulation_fallbacks(int month);

	void attrition(int month);

	string intToString(int number);

	string getSimLog();

private:
	
	int KPD_simuID;
	string KPD_strategy;
	string KPD_scheme;

	double min;		//Minimum criterion
	double avg;		//Average criterion
	double plab;	//If lab crossmatch says yes, then edge prob = plab;

	int nVertices;
	//int nVEver;
	int nEdges;

	int maxLength; int maxChainLength;
	bool last_month;
	bool includeBridgeDonors; string dataconfig;
	double att_rate; double renege_rate; double short_renege_rate;
	string outputName; string chain_storage; string utilityScheme;
	bool praAdvantage; int tiebreakIterations; bool includeABbridgeDonors;
	bool outputEdgeInfo; bool outputExchangeInfo; bool outputCycleInfo; bool outputSimInfo;

	map<int, VertexType *> pairIDMap;
	vector<VertexType *> poolIDVector; //Key is poolID, Value is pairID */

	vector<vector <int> > viableTransplantMatrix;
	vector<vector <double > > scoreMatrix;
	vector<vector <double > > survival5yearMatrix;
	vector<vector <double > > survival10yearMatrix;
	vector<vector <double > > probabilityMatrix;
	vector<vector <int> > labCrossmatchMatrix;
	vector<vector <bool> > incidenceMatrix;
	vector<VertexType *> pairVector;

	vector<vector<int> > allEC;
	vector<vector<int> > allFB;

	vector<double> UofAllEC;
	vector<double> EUofAllEC;
	vector<double> EUofAllES;
	vector<double> EUofAllSCC;
	vector<double> UofAllFB;

	//Stats * stats;

	map<string, vector<int> > resultsDemoMap;
	vector<vector<double> > transplantDemo;

	int MR_CurrentNo;
	vector<vector<double> > Record_Edge_Level;
	vector<vector<double> > Record_Exchange_Level;

	vector<vector<int> > SelectedSolutions;
	vector<int> SelectedStructures;
	vector<double> SolutionObjectives;
	vector<int> FB;

	int getChild(int start, int v, vector<int> &visitedVector, vector<vector<bool> > &thisIMatrix);

};

//Constructor
// int sID = Simulation Number
// string strategy = MUC/MEUC/MEUS/SCC
// string scheme = DPD/NEAD
// string output = Output file name
template <typename VertexType >
Graph<VertexType>::Graph(int sID, string strategy, KPDGUISimulParam * params){

	KPD_simuID = sID;
	KPD_strategy = strategy;
	KPD_scheme = params->getAllocationScheme();
	nVertices = 0;
	//nVEver = 0; 
	nEdges = 0;

	//Default Values
	maxLength = 3;
	min = -1;
	avg = -1;
	dataconfig = params->getDataConfiguration();
	maxChainLength = params->getMaxChainLength() + 1;
	outputName = params->getOutputFolderName();
	//att_rate = params->getAttritionRate();
	//renege_rate = params->getRenegeRate();
	chain_storage = params->getChainStorage();
	utilityScheme = params->getUtilityScheme();
	praAdvantage = params->getPRAadvantage();
	tiebreakIterations = params->getTiebreakIterations();
	includeABbridgeDonors = params->getIncludeABbridgeDonorsFlag();
	outputEdgeInfo = params->getOutputEdgeFlag();
	outputExchangeInfo = params->getOutputExchangeFlag();
	outputCycleInfo = params->getOutputCycleFlag();
	outputSimInfo = params->getOutputSimFlag();
	short_renege_rate = 0.005;
	last_month = false;

	//stats = stats_object;

	if (KPD_scheme.compare("NEAD") == 0){ includeBridgeDonors = true; }
	else { includeBridgeDonors = false; }

	// As a convention, we count from 1. As a result, the first element in the vector (with 0 index) was set to NULL
	poolIDVector.push_back(0);

	viableTransplantMatrix.assign(1 + nVertices, vector<int>(1 + nVertices, 0));
	scoreMatrix.assign(1 + nVertices, vector<double>(1 + nVertices, 0.0));
	survival5yearMatrix.assign(1 + nVertices, vector<double>(1 + nVertices, 0.0));
	survival10yearMatrix.assign(1 + nVertices, vector<double>(1 + nVertices, 0.0));
	probabilityMatrix.assign(1 + nVertices, vector<double>(1 + nVertices, 0.0));
	labCrossmatchMatrix.assign(1 + nVertices, vector<int>(1 + nVertices, 0));
	incidenceMatrix.assign(1 + nVertices, vector<bool>(1 + nVertices, false));
	pairVector.assign(1 + nVertices, new Pair());

	MR_CurrentNo = 0;
}

//Clear Graph
template <typename VertexType>
Graph<VertexType>::~Graph(){

	//Output file for each simulation
	if (outputEdgeInfo == true){
		string edgeFileName;
		if (dataconfig.compare("APD MATCH RUN") == 0){
			edgeFileName = "output/" + outputName + "/MatchRun" + intToString(maxChainLength - 1) + "/EdgeSimuID_" + intToString(KPD_simuID) + "_" + KPD_strategy + ".csv";
		}
		else {
			edgeFileName = "output/" + outputName + "/" + KPD_strategy + "/EdgeSimuID_" + intToString(KPD_simuID) + "_" + KPD_strategy + ".csv";
		}
		ofstream oFileEdge(edgeFileName.c_str());
		stringstream ss_edge_out;
		ss_edge_out << "MatchRun,CycleID,Donor,Recip,Pair1Type,Pair2Type,LabCrossMatch,Pair1Available,Pair2Available,TransplantProb,Pair1Prob,Pair2Prob,Score,Surv5Year,Surv10Year" << endl;
		for (typename vector<vector<double> >::iterator it = Record_Edge_Level.begin(); it != Record_Edge_Level.end(); it++){
			for (typename vector<double>::iterator it2 = it->begin(); it2 != it->end() - 1; it2++){
				ss_edge_out << *it2 << ",";
			}
			ss_edge_out << *(it->end() - 1) << endl;
		}
		oFileEdge << ss_edge_out.str();
		oFileEdge.close();
	}

	if (outputExchangeInfo == true){
		string exchangeFileName;
		if (dataconfig.compare("APD MATCH RUN") == 0){
			exchangeFileName = "output/" + outputName + "/MatchRun" + intToString(maxChainLength - 1) + "/ExchangeSimuID_" + intToString(KPD_simuID) + "_" + KPD_strategy + ".csv";
		}
		else {
			exchangeFileName = "output/" + outputName + "/" + KPD_strategy + "/ExchangeSimuID_" + intToString(KPD_simuID) + "_" + KPD_strategy + ".csv";
		}
		ofstream oFileExchange(exchangeFileName.c_str());
		stringstream ss_exchange_out;
		ss_exchange_out << "MatchRun,CycleID,Chain,Transplants,Score,Surv5Year,Surv10Year,ChainID1,ChainID2,ChainID3,ChainID4,ChainID5,ChainID6" << endl;
		for (typename vector<vector<double> >::iterator it = Record_Exchange_Level.begin(); it != Record_Exchange_Level.end(); it++){
			for (typename vector<double>::iterator it2 = it->begin(); it2 != it->end() - 1; it2++){
				ss_exchange_out << *it2 << ",";
			}
			ss_exchange_out << *(it->end() - 1) << endl;
		}
		oFileExchange << ss_exchange_out.str();
		oFileExchange.close();
	}

	if (outputSimInfo == true){
		/*string simFile = "output/" + outputName + "/Logfiles/simulationLog_" + intToString(KPD_simuID) + "_" + KPD_strategy + ".txt";
		ofstream oFileSim(simFile.c_str());
		oFileSim << simLog.str();
		oFileSim.close();*/
	}

	pairIDMap.clear();
	poolIDVector.clear();

	viableTransplantMatrix.clear();
	scoreMatrix.clear();
	survival5yearMatrix.clear();
	survival10yearMatrix.clear();
	probabilityMatrix.clear();
	labCrossmatchMatrix.clear();
	incidenceMatrix.clear();
	pairVector.clear();

	allEC.clear();
	allFB.clear();

	UofAllEC.clear();
	EUofAllEC.clear();
	EUofAllES.clear();
	UofAllFB.clear();
	EUofAllSCC.clear();

	SelectedSolutions.clear();
	SelectedStructures.clear();
	SolutionObjectives.clear();

	FB.clear();

	Record_Edge_Level.clear();
	Record_Exchange_Level.clear();
}

//Adds pair/AD to current simulation
template <typename VertexType >
VertexType *Graph<VertexType>::addVertex(int pairID, Pair pair){

	VertexType *vertex = new VertexType();
	vertex->pairID = pairID;
	vertex->poolID = nVertices + 1;
	vertex->uncertainty = pair.uncertainty;

	vertex->pairLabel = pair.pairLabel;

	vertex->donorID = pair.donorID;
	vertex->donorType = pair.donorType;
	vertex->donorBT = pair.donorBT;
	vertex->donorAge = pair.donorAge;
	vertex->donorBMI = pair.donorBMI;
	vertex->donorMale = pair.donorMale;
	vertex->donorWeight = pair.donorWeight;

	vertex->recipID = pair.recipID;
	vertex->recipBT = pair.recipBT;
	vertex->recipPRA = pair.recipPRA;
	vertex->recipAge = pair.recipAge;
	vertex->recipBMI = pair.recipBMI;
	vertex->recipDiabetes = pair.recipDiabetes;
	vertex->recipMale = pair.recipMale;
	vertex->recipWeight = pair.recipWeight;
	vertex->recipRace = pair.recipRace;
	vertex->recipPrevTrans = pair.recipPrevTrans;
	vertex->recipTOD = pair.recipTOD;
	vertex->recipHepC = pair.recipHepC;
	vertex->pairAvailabilityVector = pair.pairAvailabilityVector;
	vertex->pairAttritionVector = pair.pairAttritionVector;
	vertex->pairRenegeVector = pair.pairRenegeVector;
	vertex->pairSTBDRenegeVector = pair.pairSTBDRenegeVector;

	pairIDMap[pairID] = vertex;
	poolIDVector.push_back(vertex);
	nVertices++;
	//nVEver++;

	//Extend the matrices
	for (int i = 1; i<nVertices; i++){
		viableTransplantMatrix[i].push_back(0);
		scoreMatrix[i].push_back(0.0);
		survival5yearMatrix[i].push_back(0.0);
		survival10yearMatrix[i].push_back(0.0);
		probabilityMatrix[i].push_back(0.0);
		labCrossmatchMatrix[i].push_back(0);
		incidenceMatrix[i].push_back(false);
	}

	viableTransplantMatrix.push_back(vector<int>(1 + nVertices, 0));
	scoreMatrix.push_back(vector<double>(1 + nVertices, 0));
	survival5yearMatrix.push_back(vector<double>(1 + nVertices, 0));
	survival10yearMatrix.push_back(vector<double>(1 + nVertices, 0));
	probabilityMatrix.push_back(vector<double>(1 + nVertices, 0));
	labCrossmatchMatrix.push_back(vector<int>(1 + nVertices, 0));
	incidenceMatrix.push_back(vector<bool>(1 + nVertices, false));
	pairVector.push_back(vertex);

	return vertex;
}

//Removes vertex from current simulation
template <typename VertexType >
VertexType *Graph<VertexType>::removeVertex(int pairID){

	int id = getPoolID(pairID);

	int nEdgeLost = 0;
	for (int i = 1; i <= nVertices; i++)
		nEdgeLost += viableTransplantMatrix[id][i];
	for (int i = 1; i <= nVertices; i++)
		nEdgeLost += viableTransplantMatrix[i][id];
	nEdges -= nEdgeLost;

	for (int i = 1; i <= nVertices; i++){
		viableTransplantMatrix[i].erase(viableTransplantMatrix[i].begin() + id);
		scoreMatrix[i].erase(scoreMatrix[i].begin() + id);
		survival5yearMatrix[i].erase(survival5yearMatrix[i].begin() + id);
		survival10yearMatrix[i].erase(survival10yearMatrix[i].begin() + id);
		probabilityMatrix[i].erase(probabilityMatrix[i].begin() + id);
		labCrossmatchMatrix[i].erase(labCrossmatchMatrix[i].begin() + id);
		incidenceMatrix[i].erase(incidenceMatrix[i].begin() + id);
	}
	viableTransplantMatrix.erase(viableTransplantMatrix.begin() + id);
	scoreMatrix.erase(scoreMatrix.begin() + id);
	survival5yearMatrix.erase(survival5yearMatrix.begin() + id);
	survival10yearMatrix.erase(survival10yearMatrix.begin() + id);
	probabilityMatrix.erase(probabilityMatrix.begin() + id);
	labCrossmatchMatrix.erase(labCrossmatchMatrix.begin() + id);
	incidenceMatrix.erase(incidenceMatrix.begin() + id);
	pairVector.erase(pairVector.begin() + id);

	VertexType *removed = pairIDMap[pairID];

	for (int temp = removed->poolID; temp<nVertices; temp++){
		poolIDVector[temp] = poolIDVector[temp + 1];
		poolIDVector[temp]->poolID = temp;
	}
	poolIDVector.pop_back();
	pairIDMap.erase(pairID);
	nVertices--;

	return removed;
}

/*
//Getter functions
template <typename VertexType >
VertexType *Graph<VertexType>::getVertexByPairID(int pairID){
return pairIDMap[pairID];
}

template <typename VertexType >
VertexType *Graph<VertexType>::getVertexByPoolID(int poolID){
return poolIDVector[poolID];
}
*/

template <typename VertexType >
int Graph<VertexType>::getTotalNumberVertices(){
	return nVertices;
}
/*
template <typename VertexType >
int Graph<VertexType>::getTotalNumberVerticesEver(){
return nVEver;
}
*/
template <typename VertexType >
int Graph<VertexType>::getTotalNumberEdges(){
	return nEdges;
}
/*
template <typename VertexType >
vector<VertexType *> &Graph<VertexType>::getPoolIDVector(){
return poolIDVector;
}

template <typename VertexType >
vector<vector<int> > &Graph<VertexType>::getViableTransplantMatrix(){
return viableTransplantMatrix;
}

template <typename VertexType >
vector<vector<double> > &Graph<VertexType>::getScoreMatrix(){
return scoreMatrix;
}

template <typename VertexType >
vector<vector<double> > &Graph<VertexType>::getSurvival5yearMatrix(){
return survival5yearMatrix;
}

template <typename VertexType >
vector<vector<double> > &Graph<VertexType>::getSurvival10yearMatrix(){
return survival10yearMatrix;
}

template <typename VertexType >
vector<vector<double> > &Graph<VertexType>::getProbabilityMatrix(){
return probabilityMatrix;
}

template <typename VertexType >
vector<vector<int> > &Graph<VertexType>::getLabCrossmatchMatrix(){
return labCrossmatchMatrix;
}

template <typename VertexType >
vector<vector<bool> > &Graph<VertexType>::getIncidenceMatrix(){
return incidenceMatrix;
}

template <typename VertexType >
vector<PairInfo> &Graph<VertexType>::getPairVector(){
return pairVector;
}
*/
template <typename VertexType >
int Graph<VertexType>::getPoolID(int pairID){
	return pairIDMap.find(pairID)->second->poolID;
}

template <typename VertexType >
int Graph<VertexType>::getPairID(int poolID){
	return poolIDVector[poolID]->pairID;
}

//Adds values to matrices in current simulation
template <typename VertexType >
void Graph<VertexType>::addEdge(int start, int end){
	if (pairVector[getPoolID(end)]->donorType != 2){
		incidenceMatrix[getPoolID(start)][getPoolID(end)] = true;
		nEdges++;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdgeViableTransplant(int start, int end, int viableTransplant){
	if (pairVector[getPoolID(end)]->donorType != 2){
		viableTransplantMatrix[getPoolID(start)][getPoolID(end)] = viableTransplant;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdgeScore(int start, int end, double score){
	if (pairVector[getPoolID(end)]->donorType != 2){
		scoreMatrix[getPoolID(start)][getPoolID(end)] = score;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdge5yearSurvival(int start, int end, double survival){
	if (pairVector[getPoolID(end)]->donorType != 2){
		survival5yearMatrix[getPoolID(start)][getPoolID(end)] = survival;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdge10yearSurvival(int start, int end, double survival){
	if (pairVector[getPoolID(end)]->donorType != 2){
		survival10yearMatrix[getPoolID(start)][getPoolID(end)] = survival;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdgeProbability(int start, int end, double probability){
	if (pairVector[getPoolID(end)]->donorType != 2){
		probabilityMatrix[getPoolID(start)][getPoolID(end)] = probability;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdgeLabCrossmatch(int start, int end, int labCrossmatch){
	if (pairVector[getPoolID(end)]->donorType != 2){
		labCrossmatchMatrix[getPoolID(start)][getPoolID(end)] = labCrossmatch;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdgeByPoolID(int start, int end){
	if (pairVector[end]->donorType != 2){
		incidenceMatrix[start][end] = true;
		nEdges++;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdgeViableTransplantByPoolID(int start, int end, int viableTransplant){
	if (pairVector[end]->donorType != 2){
		viableTransplantMatrix[start][end] = viableTransplant;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdgeScoreByPoolID(int start, int end, double score){
	if (pairVector[end]->donorType != 2){
		scoreMatrix[start][end] = score;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdgeSurvival5yearByPoolID(int start, int end, double survival){
	if (pairVector[end]->donorType != 2){
		survival5yearMatrix[start][end] = survival;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdgeSurvival10yearByPoolID(int start, int end, double survival){
	if (pairVector[end]->donorType != 2){
		survival10yearMatrix[start][end] = survival;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdgeProbabilityByPoolID(int start, int end, double probability){
	if (pairVector[end]->donorType != 2){
		probabilityMatrix[start][end] = probability;
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdgeLabCrossmatchByPoolID(int start, int end, int labCrossmatch){
	if (pairVector[end]->donorType != 2){
		labCrossmatchMatrix[start][end] = labCrossmatch;
	}
}

//Removes values from matrices in current simulation
template <typename VertexType >
void Graph<VertexType>::removeEdge(int start, int end){
	viableTransplantMatrix[getPoolID(start)][getPoolID(end)] = 0;
	scoreMatrix[getPoolID(start)][getPoolID(end)] = 0;
	survival5yearMatrix[getPoolID(start)][getPoolID(end)] = 0;
	survival10yearMatrix[getPoolID(start)][getPoolID(end)] = 0;
	probabilityMatrix[getPoolID(start)][getPoolID(end)] = 0;
	labCrossmatchMatrix[getPoolID(start)][getPoolID(end)] = 0;
	incidenceMatrix[getPoolID(start)][getPoolID(end)] = false;
	nEdges--;
}

template <typename VertexType >
void Graph<VertexType>::removeEdgeByPoolID(int start, int end){

	viableTransplantMatrix[start][end] = 0;
	scoreMatrix[start][end] = 0;
	survival5yearMatrix[start][end] = 0;
	survival10yearMatrix[start][end] = 0;
	probabilityMatrix[start][end] = 0;
	labCrossmatchMatrix[start][end] = 0;
	incidenceMatrix[start][end] = false;
	nEdges--;
}

template <typename VertexType >
void Graph<VertexType>::removeEdgesFrom(int pairID){
	int row = getPoolID(pairID);
	for (int i = 1; i <= nVertices; i++) {
		if (incidenceMatrix[row][i] == true){
			viableTransplantMatrix[row][i] = 0;
			scoreMatrix[row][i] = 0;
			survival5yearMatrix[row][i] = 0;
			survival10yearMatrix[row][i] = 0;
			probabilityMatrix[row][i] = 0;
			labCrossmatchMatrix[row][i] = 0;
			incidenceMatrix[row][i] = false;
			nEdges--;
		}
	}
}

template <typename VertexType >
void Graph<VertexType>::removeEdgesTo(int pairID){
	int col = getPoolID(pairID);

	for (int i = 1; i <= nVertices; i++) {
		if (incidenceMatrix[i][col] == true){
			viableTransplantMatrix[i][col] = 0;
			scoreMatrix[i][col] = 0;
			survival5yearMatrix[i][col] = 0;
			survival10yearMatrix[i][col] = 0;
			probabilityMatrix[i][col] = 0;
			labCrossmatchMatrix[i][col] = 0;
			incidenceMatrix[i][col] = false;
			nEdges--;
		}
	}
}

template <typename VertexType >
void Graph<VertexType>::addEdgesTo(int pairID){
	int col = getPoolID(pairID);

	for (int i = 1; i <= nVertices; i++) {
		if (i != col && pairVector[i]->donorType == 0){
			viableTransplantMatrix[i][col] = 0;
			scoreMatrix[i][col] = 0;
			survival5yearMatrix[i][col] = 1;
			survival10yearMatrix[i][col] = 1;
			probabilityMatrix[i][col] = 1;
			labCrossmatchMatrix[i][col] = 1;
			incidenceMatrix[i][col] = true;
			nEdges++;
		}
	}
}

//Corrects bridge donor probabilities and viabilities for future match runs in current simulation
template <typename VertexType >
void Graph<VertexType>::correctBridgeDonors(){
	for (int i = 1; i <= nVertices; i++){
		if (pairVector[i]->donorType == 2){
			removeEdgesTo(getPairID(i));
			addEdgesTo(getPairID(i));
			pairVector[i]->uncertainty = 1.0;
		}
	}
}

template <typename VertexType >
void Graph<VertexType>::setLastMonth(){
	last_month = true;
}

//Helper function for graph searching	
template <typename VertexType>
int Graph<VertexType>::getChild(int lower, int current, vector<int> &visitedVector, vector<vector<bool> > & thisIMatrix){
	int nV = (int)visitedVector.size() - 1;
	for (int j = lower + 1; j <= nV; j++){
		if (thisIMatrix[current][j] == true && visitedVector[j] == 0)
			return j;
	}
	return -1;
}

template <typename VertexType>
vector<vector<int> > &Graph<VertexType>::getAllEC(){

	allEC.clear();
	
	int N = getTotalNumberVertices();

	/*for (int i = 1; i <= N; i++){
		for (int j = 1; j <= N; j++){
			simLog << i << "," << j << ":" << incidenceMatrix[i][j];
		}
	}*/

	vector<vector<int> > storedCycles;

	int start = 1;
	vector<int> visitedVector(nVertices + 1, 0);
	vector<int> stack_vec;

	int max;
	if (maxLength > maxChainLength){
		max = maxLength;
	}
	else {
		max = maxChainLength;
	}

	//Depth-first search of graph
	while (start <= nVertices){
		visitedVector[start] = 1;
		stack_vec.push_back(start);
		int v = getChild(start, start, visitedVector, incidenceMatrix);
		while (!stack_vec.empty()){
			
			if (v == -1){
				int top = stack_vec.back();
				stack_vec.pop_back();
				if (top == start){
					visitedVector[top] = 0;
					break;
				}
				visitedVector[top] = 0;
				v = getChild(top, stack_vec.back(), visitedVector, incidenceMatrix);
			}
			else{
				visitedVector[v] = 1;
				stack_vec.push_back(v);

				if (incidenceMatrix[v][start] == true){
					int chaintest = 0;
					string bridgeDonorBT;
					vector<int> recipids;
					bool repeatedRecip = false;
					//Checks for multiple recipients within cycle/chain
					for (typename vector<int>::iterator it = stack_vec.begin(); it != stack_vec.end(); ++it){
						if (dataconfig.compare("APD MATCH RUN") == 0){
							recipids.push_back(pairVector[*it]->recipID);
						}
						if (pairVector[*it]->donorType != 0){
							chaintest++;
							if (it == stack_vec.begin()){
								bridgeDonorBT = pairVector[*(stack_vec.end() - 1)]->donorBT;
							}
							else {
								bridgeDonorBT = pairVector[*(it - 1)]->donorBT;
							}

						}
					}

					if (dataconfig.compare("APD MATCH RUN") == 0){
						sort(recipids.begin(), recipids.end());
						for (int p = 0; p<recipids.size() - 1; p++){
							if (recipids[p] == recipids[p + 1]){
								repeatedRecip = true;
							}
						}
					}
					if (repeatedRecip == false){
						for (typename vector<int>::iterator debugit = stack_vec.begin(); debugit != stack_vec.end(); ++debugit){
							////qDebug() << *debugit;
						}
						

						if (chaintest == 1 && stack_vec.size() <= maxChainLength){
							//Bridge donors ending in AB need to be checked
							if (includeABbridgeDonors == true || (includeABbridgeDonors == false && bridgeDonorBT.compare("AB") != 0)){
								////qDebug() << "Included";
								if (chain_storage.compare("LAST") == 0){
									storedCycles.push_back(vector<int >(stack_vec.begin(), stack_vec.end()));
								}
								else {
									allEC.push_back(vector<int >(stack_vec.begin(), stack_vec.end()));
								}
							}
						}
						else if (chaintest == 0 && stack_vec.size() <= maxLength){
							////qDebug() << "Included";
							if (chain_storage.compare("FIRST") == 0){
								storedCycles.push_back(vector<int >(stack_vec.begin(), stack_vec.end()));
							}
							else {
								allEC.push_back(vector<int >(stack_vec.begin(), stack_vec.end()));
							}
						}
						////qDebug() << "------------";
					}
				}

				//Cycle or chain?
				bool chain = false;
				for (typename vector<int>::iterator it = stack_vec.begin(); it != stack_vec.end(); ++it){
					if (pairVector[*it]->donorType != 0){
						chain = true;
					}
				}
				/*if (chain == true){
					if (stack_vec.size() >= maxChainLength)
						v = -1;
					else {
						v = getChild(start, v, visitedVector, incidenceMatrix);
					}
						
				}
				else {
					if (stack_vec.size() >= maxLength)
						v = -1;
					else {
						v = getChild(start, v, visitedVector, incidenceMatrix);
					}
				}*/
				if (stack_vec.size() >= max)
					v = -1;
				else {
					v = getChild(start, v, visitedVector, incidenceMatrix);
				}
			}
		}
		start++;
	}

	if (storedCycles.size()>0){
		for (vector<vector<int> >::iterator it = storedCycles.begin(); it != storedCycles.end(); ++it){
			allEC.push_back(*it);
		}
	}

	//simLog << allEC.size();

	return allEC;
}

// Coerces cycles into sets
template <typename VertexType>
vector<vector<int> > &Graph<VertexType>::getAllES(){

	getAllEC();
	set<set<int> > tempES;
	for (typename vector<vector<int> >::iterator it = allEC.begin(); it != allEC.end(); it++){
		tempES.insert(set<int>(it->begin(), it->end()));
	}
	allEC.clear();
	for (typename set<set<int> >::iterator it = tempES.begin(); it != tempES.end(); it++){
		allEC.push_back(vector<int>(it->begin(), it->end()));
	}
	return allEC;
}

// Searches graphs for connected components
template <typename VertexType>
vector<vector<int > > &Graph<VertexType> ::getAllSCC(){

	allEC.clear();

	//Size 2 components
	//
	for (int i = 1; i <= nVertices - 1; i++){
		for (int j = i + 1; j <= nVertices; j++){
			if (incidenceMatrix[i][j] == true && incidenceMatrix[j][i] == true){
				int nV = 2;
				vector<vector<bool> > subIncidenceMatrix(nV + 1, vector<bool>(nV + 1, false));
				vector<vector<double> > subUtilityMatrix(nV + 1, vector<double>(nV + 1, 0));
				subIncidenceMatrix[1][2] = incidenceMatrix[i][j];
				subIncidenceMatrix[2][1] = incidenceMatrix[j][i];

				subUtilityMatrix[1][2] = viableTransplantMatrix[i][j];
				subUtilityMatrix[2][1] = viableTransplantMatrix[j][i];

				if (getMaxUtilityInFB(nV, subIncidenceMatrix, subUtilityMatrix) > 0){
					vector<int > temp;
					temp.push_back(i); temp.push_back(j);
					allEC.push_back(temp);
				}
			}
		}
	}

	//Size 3 components
	for (int i = 1; i <= nVertices - 2; i++){
		for (int j = i + 1; j <= nVertices - 1; j++){
			for (int k = j + 1; k <= nVertices; k++){
				//i to j
				if (incidenceMatrix[i][j] == false && (incidenceMatrix[i][k] == false || incidenceMatrix[k][j] == false))
					continue;
				//i to k
				if (incidenceMatrix[i][k] == false && (incidenceMatrix[i][j] == false || incidenceMatrix[j][k] == false))
					continue;
				//j to i
				if (incidenceMatrix[j][i] == false && (incidenceMatrix[j][k] == false || incidenceMatrix[k][i] == false))
					continue;
				//j to k
				if (incidenceMatrix[j][k] == false && (incidenceMatrix[j][i] == false || incidenceMatrix[i][k] == false))
					continue;
				//k to i
				if (incidenceMatrix[k][i] == false && (incidenceMatrix[k][j] == false || incidenceMatrix[j][i] == false))
					continue;
				//k to j
				if (incidenceMatrix[k][j] == false && (incidenceMatrix[k][i] == false || incidenceMatrix[i][j] == false))
					continue;

				int nV = 3;
				vector<vector<bool> > subIncidenceMatrix(nV + 1, vector<bool>(nV + 1, false));
				vector<vector<double> > subUtilityMatrix(nV + 1, vector<double>(nV + 1, 0));
				subIncidenceMatrix[1][2] = incidenceMatrix[i][j];
				subUtilityMatrix[1][2] = viableTransplantMatrix[i][j];
				subIncidenceMatrix[2][1] = incidenceMatrix[j][i];
				subUtilityMatrix[2][1] = viableTransplantMatrix[j][i];
				subIncidenceMatrix[1][3] = incidenceMatrix[i][k];
				subUtilityMatrix[1][3] = viableTransplantMatrix[i][k];
				subIncidenceMatrix[3][1] = incidenceMatrix[k][i];
				subUtilityMatrix[3][1] = viableTransplantMatrix[k][i];
				subIncidenceMatrix[2][3] = incidenceMatrix[j][k];
				subUtilityMatrix[2][3] = viableTransplantMatrix[j][k];
				subIncidenceMatrix[3][2] = incidenceMatrix[k][j];
				subUtilityMatrix[3][2] = viableTransplantMatrix[k][j];

				if (getMaxUtilityInFB(nV, subIncidenceMatrix, subUtilityMatrix) > 0){
					vector<int > temp;
					temp.push_back(i); temp.push_back(j); temp.push_back(k);
					allEC.push_back(temp);
				}
			}
		}
	}

	//Size 4 components
	if (maxChainLength >= 4){
		for (int i = 1; i <= nVertices - 3; i++){
			for (int j = i + 1; j <= nVertices - 2; j++){
				for (int k = j + 1; k <= nVertices - 1; k++){
					for (int l = k + 1; l <= nVertices; l++){
						// i to j
						if (incidenceMatrix[i][j] == false && (incidenceMatrix[i][k] == false || incidenceMatrix[k][j] == false)
							&& (incidenceMatrix[i][l] == false || incidenceMatrix[l][j] == false)
							&& (incidenceMatrix[i][k] == false || incidenceMatrix[k][l] == false || incidenceMatrix[l][j] == false)
							&& (incidenceMatrix[i][l] == false || incidenceMatrix[l][k] == false || incidenceMatrix[k][j] == false))
							continue;
						// i to k
						if (incidenceMatrix[i][k] == false && (incidenceMatrix[i][j] == false || incidenceMatrix[j][k] == false)
							&& (incidenceMatrix[i][l] == false || incidenceMatrix[l][k] == false)
							&& (incidenceMatrix[i][l] == false || incidenceMatrix[l][j] == false || incidenceMatrix[j][k] == false)
							&& (incidenceMatrix[i][j] == false || incidenceMatrix[j][l] == false || incidenceMatrix[l][k] == false))
							continue;
						// i to l
						if (incidenceMatrix[i][l] == false && (incidenceMatrix[i][j] == false || incidenceMatrix[j][l] == false)
							&& (incidenceMatrix[i][k] == false || incidenceMatrix[k][l] == false)
							&& (incidenceMatrix[i][j] == false || incidenceMatrix[j][k] == false || incidenceMatrix[k][l] == false)
							&& (incidenceMatrix[i][k] == false || incidenceMatrix[k][j] == false || incidenceMatrix[j][l] == false))
							continue;
						// j to i
						if (incidenceMatrix[j][i] == false && (incidenceMatrix[j][k] == false || incidenceMatrix[k][i] == false)
							&& (incidenceMatrix[j][l] == false || incidenceMatrix[l][i] == false)
							&& (incidenceMatrix[j][k] == false || incidenceMatrix[k][l] == false || incidenceMatrix[l][i] == false)
							&& (incidenceMatrix[j][l] == false || incidenceMatrix[l][k] == false || incidenceMatrix[k][i] == false))
							continue;
						// j to k
						if (incidenceMatrix[j][k] == false && (incidenceMatrix[j][i] == false || incidenceMatrix[i][k] == false)
							&& (incidenceMatrix[j][l] == false || incidenceMatrix[l][k] == false)
							&& (incidenceMatrix[j][i] == false || incidenceMatrix[i][l] == false || incidenceMatrix[l][k] == false)
							&& (incidenceMatrix[j][l] == false || incidenceMatrix[l][i] == false || incidenceMatrix[i][k] == false))
							continue;
						// j to l
						if (incidenceMatrix[j][l] == false && (incidenceMatrix[j][i] == false || incidenceMatrix[i][l] == false)
							&& (incidenceMatrix[j][k] == false || incidenceMatrix[k][l] == false)
							&& (incidenceMatrix[j][i] == false || incidenceMatrix[i][k] == false || incidenceMatrix[k][l] == false)
							&& (incidenceMatrix[j][k] == false || incidenceMatrix[k][i] == false || incidenceMatrix[i][l] == false))
							continue;
						// k to i
						if (incidenceMatrix[k][i] == false && (incidenceMatrix[k][j] == false || incidenceMatrix[j][i] == false)
							&& (incidenceMatrix[k][l] == false || incidenceMatrix[l][i] == false)
							&& (incidenceMatrix[k][j] == false || incidenceMatrix[j][l] == false || incidenceMatrix[l][i] == false)
							&& (incidenceMatrix[k][l] == false || incidenceMatrix[l][j] == false || incidenceMatrix[j][i] == false))
							continue;
						// k to j
						if (incidenceMatrix[k][j] == false && (incidenceMatrix[k][i] == false || incidenceMatrix[i][j] == false)
							&& (incidenceMatrix[k][l] == false || incidenceMatrix[l][j] == false)
							&& (incidenceMatrix[k][i] == false || incidenceMatrix[i][l] == false || incidenceMatrix[l][j] == false)
							&& (incidenceMatrix[k][l] == false || incidenceMatrix[l][i] == false || incidenceMatrix[i][j] == false))
							continue;
						// k to l
						if (incidenceMatrix[k][l] == false && (incidenceMatrix[k][i] == false || incidenceMatrix[i][l] == false)
							&& (incidenceMatrix[k][j] == false || incidenceMatrix[j][l] == false)
							&& (incidenceMatrix[k][i] == false || incidenceMatrix[i][j] == false || incidenceMatrix[j][l] == false)
							&& (incidenceMatrix[k][j] == false || incidenceMatrix[j][i] == false || incidenceMatrix[i][l] == false))
							continue;
						// l to i
						if (incidenceMatrix[l][i] == false && (incidenceMatrix[l][j] == false || incidenceMatrix[j][i] == false)
							&& (incidenceMatrix[l][k] == false || incidenceMatrix[k][i] == false)
							&& (incidenceMatrix[l][j] == false || incidenceMatrix[j][k] == false || incidenceMatrix[k][i] == false)
							&& (incidenceMatrix[l][k] == false || incidenceMatrix[k][j] == false || incidenceMatrix[j][i] == false))
							continue;
						// l to j
						if (incidenceMatrix[l][j] == false && (incidenceMatrix[l][i] == false || incidenceMatrix[i][j] == false)
							&& (incidenceMatrix[l][k] == false || incidenceMatrix[k][j] == false)
							&& (incidenceMatrix[l][i] == false || incidenceMatrix[i][k] == false || incidenceMatrix[k][j] == false)
							&& (incidenceMatrix[l][k] == false || incidenceMatrix[k][i] == false || incidenceMatrix[i][j] == false))
							continue;
						// l to k
						if (incidenceMatrix[l][k] == false && (incidenceMatrix[l][i] == false || incidenceMatrix[i][k] == false)
							&& (incidenceMatrix[l][j] == false || incidenceMatrix[j][k] == false)
							&& (incidenceMatrix[l][i] == false || incidenceMatrix[i][j] == false || incidenceMatrix[j][k] == false)
							&& (incidenceMatrix[l][j] == false || incidenceMatrix[j][i] == false || incidenceMatrix[i][k] == false))
							continue;

						int nV = 4;
						vector<vector<bool> > subIncidenceMatrix(nV + 1, vector<bool>(nV + 1, false));
						vector<vector<double> > subUtilityMatrix(nV + 1, vector<double>(nV + 1, 0));
						subIncidenceMatrix[1][2] = incidenceMatrix[i][j];
						subUtilityMatrix[1][2] = viableTransplantMatrix[i][j];
						subIncidenceMatrix[2][1] = incidenceMatrix[j][i];
						subUtilityMatrix[2][1] = viableTransplantMatrix[j][i];
						subIncidenceMatrix[1][3] = incidenceMatrix[i][k];
						subUtilityMatrix[1][3] = viableTransplantMatrix[i][k];
						subIncidenceMatrix[3][1] = incidenceMatrix[k][i];
						subUtilityMatrix[3][1] = viableTransplantMatrix[k][i];
						subIncidenceMatrix[1][4] = incidenceMatrix[i][l];
						subUtilityMatrix[1][4] = viableTransplantMatrix[i][l];
						subIncidenceMatrix[4][1] = incidenceMatrix[l][i];
						subUtilityMatrix[4][1] = viableTransplantMatrix[l][i];
						subIncidenceMatrix[2][3] = incidenceMatrix[j][k];
						subUtilityMatrix[2][3] = viableTransplantMatrix[j][k];
						subIncidenceMatrix[3][2] = incidenceMatrix[k][j];
						subUtilityMatrix[3][2] = viableTransplantMatrix[k][j];
						subIncidenceMatrix[2][4] = incidenceMatrix[j][l];
						subUtilityMatrix[2][4] = viableTransplantMatrix[j][l];
						subIncidenceMatrix[4][2] = incidenceMatrix[l][j];
						subUtilityMatrix[4][2] = viableTransplantMatrix[l][j];
						subIncidenceMatrix[3][4] = incidenceMatrix[k][l];
						subUtilityMatrix[3][4] = viableTransplantMatrix[k][l];
						subIncidenceMatrix[4][3] = incidenceMatrix[l][k];
						subUtilityMatrix[4][3] = viableTransplantMatrix[l][k];

						if (getMaxUtilityInFB(nV, subIncidenceMatrix, subUtilityMatrix) > 0){
							vector<int > temp;
							temp.push_back(i); temp.push_back(j); temp.push_back(k); temp.push_back(l);
							allEC.push_back(temp);
						}
					}
				}
			}
		}
	}
	return allEC;
}

template <typename VertexType>
double Graph<VertexType>::calculateExpectation(string utility, bool chain, vector<int> transplants){
	double expUtility = 0.0;
	double cycleProb = 1.0;
	double cycleUtil = 0.0;

	//Chain
	if (chain == true){
		//Utility based on number of transplants
		if (utility.compare("TRANSPLANTS") == 0){
			cycleUtil = viableTransplantMatrix[*(transplants.begin())][*(transplants.begin() + 1)];
		}
		//Utility based on 5 year survival
		else if (utility.compare("SURVIVAL5YEAR") == 0){
			cycleUtil = survival5yearMatrix[*(transplants.begin())][*(transplants.begin() + 1)];
		}
		//Utility based on 10 year survival
		else if (utility.compare("SURVIVAL10YEAR") == 0){
			cycleUtil = survival10yearMatrix[*(transplants.begin())][*(transplants.begin() + 1)];
		}
		//Utility based on other specified scoring matrix
		else {
			cycleUtil = scoreMatrix[*(transplants.begin())][*(transplants.begin() + 1)];
		}
		cycleProb = pairVector[*(transplants.begin())]->uncertainty*pairVector[*(transplants.begin() + 1)]->uncertainty*probabilityMatrix[*(transplants.begin())][*(transplants.begin() + 1)];

		if (transplants.size() == 2){
			expUtility = cycleProb*cycleUtil;
		}

		//Longer Chains
		else if (transplants.size()>2){
			for (typename vector<int >::iterator it = transplants.begin() + 1; it != transplants.end() - 2; ++it){
				//Probability of continuing to next transplant
				double probContinue = pairVector[*(it + 1)]->uncertainty*probabilityMatrix[*it][*(it + 1)];
				expUtility += (1 - probContinue)*cycleUtil*cycleProb;

				cycleProb = cycleProb*probContinue;

				//Add additional utility from new transplant
				if (utility.compare("TRANSPLANTS") == 0){
					cycleUtil += viableTransplantMatrix[*it][*(it + 1)];
				}
				else if (utility.compare("SURVIVAL5YEAR") == 0){
					cycleUtil += survival5yearMatrix[*it][*(it + 1)];
				}
				else if (utility.compare("SURVIVAL10YEAR") == 0){
					cycleUtil += survival10yearMatrix[*it][*(it + 1)];
				}
				else {
					cycleUtil += scoreMatrix[*it][*(it + 1)];
				}
				//expUtility+=cycleUtil*cycleProb;
			}

			//Final transplant
			double probContinue = pairVector[*(transplants.end() - 1)]->uncertainty*probabilityMatrix[*(transplants.end() - 2)][*(transplants.end() - 1)];
			expUtility += (1 - probContinue)*cycleUtil*cycleProb;

			cycleProb = cycleProb*probContinue;
			if (utility.compare("TRANSPLANTS") == 0){
				cycleUtil += viableTransplantMatrix[*(transplants.end() - 2)][*(transplants.end() - 1)];
			}
			else if (utility.compare("SURVIVAL5YEAR") == 0){
				cycleUtil += survival5yearMatrix[*(transplants.end() - 2)][*(transplants.end() - 1)];
			}
			else if (utility.compare("SURVIVAL10YEAR") == 0){
				cycleUtil += survival10yearMatrix[*(transplants.end() - 2)][*(transplants.end() - 1)];
			}
			else {
				cycleUtil += scoreMatrix[*(transplants.end() - 2)][*(transplants.end() - 1)];
			}

			expUtility += cycleUtil*cycleProb;
		}
	}

	//Cycles
	else{
		//Calculates cycle probability and cycle utility
		cycleProb = pairVector[*(transplants.begin())]->uncertainty;
		for (typename vector<int >::iterator it = transplants.begin(); it != transplants.end() - 1; ++it){
			cycleProb = cycleProb*pairVector[*(it + 1)]->uncertainty*probabilityMatrix[*it][*(it + 1)];
			if (utility.compare("TRANSPLANTS") == 0){
				cycleUtil += viableTransplantMatrix[*it][*(it + 1)];
			}
			else if (utility.compare("SURVIVAL5YEAR") == 0){
				cycleUtil += survival5yearMatrix[*it][*(it + 1)];
			}
			else if (utility.compare("SURVIVAL10YEAR") == 0){
				cycleUtil += survival10yearMatrix[*it][*(it + 1)];
			}
			else {
				cycleUtil += scoreMatrix[*it][*(it + 1)];
			}
		}
		cycleProb = cycleProb*probabilityMatrix[*(transplants.end() - 1)][*(transplants.begin())];
		if (utility.compare("TRANSPLANTS") == 0){
			cycleUtil += viableTransplantMatrix[*(transplants.end() - 1)][*(transplants.begin())];
		}
		else if (utility.compare("SURVIVAL5YEAR") == 0){
			cycleUtil += survival5yearMatrix[*(transplants.end() - 1)][*(transplants.begin())];
		}
		else if (utility.compare("SURVIVAL10YEAR") == 0){
			cycleUtil += survival10yearMatrix[*(transplants.end() - 1)][*(transplants.begin())];
		}
		else {
			cycleUtil += scoreMatrix[*(transplants.end() - 1)][*(transplants.begin())];
		}

		expUtility = cycleProb*cycleUtil;
		////qDebug() << cycleProb << "," << cycleUtil;

	}

	return expUtility;
}

template <typename VertexType>
double Graph<VertexType>::calculateExpectationFB(bool chain, vector<int> transplants,
	vector<vector<double> > &subUtilityMatrix, vector<vector<double> > &subProbabilityMatrix, vector<double> &subProbVertexVector){
	double expUtility = 0.0;
	double cycleProb = 1.0;
	double cycleUtil = 0.0;

	//Chain
	if (chain == true){
		int numTransplants = 1;
		cycleUtil = subUtilityMatrix[*(transplants.begin())][*(transplants.begin() + 1)];
		cycleProb = subProbVertexVector[*(transplants.begin())] * subProbVertexVector[*(transplants.begin() + 1)] * subProbabilityMatrix[*(transplants.begin())][*(transplants.begin() + 1)];

		//Chain from AD to Pair
		if (transplants.size() == 2){
			expUtility = cycleProb*cycleUtil;
		}
		//Longer chain
		else if (transplants.size()>2){
			for (typename vector<int >::iterator it = transplants.begin() + 1; it != transplants.end() - 2; ++it){
				numTransplants++;
				//Probability of continuing the chain
				double probContinue = subProbVertexVector[*(it + 1)] * subProbabilityMatrix[*it][*(it + 1)];
				expUtility += (1 - probContinue)*cycleUtil*cycleProb;
				cycleProb = cycleProb*probContinue;
				cycleUtil += subUtilityMatrix[*it][*(it + 1)];
			}
		}
		cycleProb = cycleProb*subProbVertexVector[*(transplants.end() - 1)] * subProbabilityMatrix[*(transplants.end() - 2)][*(transplants.end() - 1)];
		cycleUtil += subUtilityMatrix[*(transplants.end() - 2)][*(transplants.end() - 1)];
		expUtility += cycleUtil*cycleProb;
	}

	//Cycle
	else{
		cycleProb = subProbVertexVector[*(transplants.begin())];
		for (typename vector<int >::iterator it = transplants.begin(); it != transplants.end() - 1; ++it){
			cycleProb = cycleProb*subProbVertexVector[*(it + 1)] * subProbabilityMatrix[*it][*(it + 1)];
			cycleUtil += subUtilityMatrix[*it][*(it + 1)];
		}
		cycleProb = cycleProb*subProbabilityMatrix[*(transplants.end() - 1)][*(transplants.begin())];
		cycleUtil += subUtilityMatrix[*(transplants.end() - 1)][*(transplants.begin())];
		expUtility = cycleProb*cycleUtil;
	}

	return expUtility;
}

//Utility values for all chains/cycles
template <typename VertexType>
vector<double> & Graph<VertexType>::getUForAllEC(){
	UofAllEC.clear();
	for (typename vector<vector<int> >::iterator it = allEC.begin(); it != allEC.end(); it++){
		double u = 0;
		//Sums over all utility values
		for (typename vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end() - 1; it2++){
			//Transplants
			if (utilityScheme.compare("TRANSPLANTS") == 0){
				double advantage = 0.0;
				if (praAdvantage == true && pairVector[*(it2 + 1)]->donorType == 0){
					if (pairVector[*(it2 + 1)]->recipPRA >= 80){
						advantage = 0.1;
					}
				}
				u += viableTransplantMatrix[*it2][*(it2 + 1)] + advantage;
			}
			//5 year survival
			else if (utilityScheme.compare("SURVIVAL5YEAR") == 0){
				u += survival5yearMatrix[*it2][*(it2 + 1)];
			}
			//10 year survival
			else if (utilityScheme.compare("SURVIVAL10YEAR") == 0){
				u += survival10yearMatrix[*it2][*(it2 + 1)];
			}
			//Other utility specification
			else {
				u += scoreMatrix[*it2][*(it2 + 1)];
			}
		}
		if (utilityScheme.compare("TRANSPLANTS") == 0){
			double advantage = 0.0;
			if (praAdvantage == true && pairVector[*(it->begin())]->donorType == 0){
				if (pairVector[*(it->begin())]->recipPRA >= 80){
					advantage = 0.1;
				}
			}
			u = u + viableTransplantMatrix[*(it->end() - 1)][*(it->begin())] + advantage;
		}
		else if (utilityScheme.compare("SURVIVAL5YEAR") == 0){
			u = u + survival5yearMatrix[*(it->end() - 1)][*(it->begin())];
		}
		else if (utilityScheme.compare("SURVIVAL10YEAR") == 0){
			u = u + survival10yearMatrix[*(it->end() - 1)][*(it->begin())];
		}
		else {
			u = u + scoreMatrix[*(it->end() - 1)][*(it->begin())];
		}
		UofAllEC.push_back(u);
	}
	
	return UofAllEC;
}

//Expected utility values for all chains/cycles
template <typename VertexType>
vector<double> & Graph<VertexType>::getEUForAllEC(){
	EUofAllEC.clear();

	int i = 0;
	for (typename vector<vector<int> >::iterator it = allEC.begin(); it != allEC.end(); it++){
		bool chain = false;

		//Queue up AD to front of chain
		for (int q = 0; q<(*it).size(); q++){
			if (chain == false){
				int queue = *((*it).begin());
				(*it).erase((*it).begin());
				(*it).push_back(queue);

				if (pairVector[*((*it).begin())]->donorType != 0){
					chain = true;
				}
			}
		}

		double eu = calculateExpectation(utilityScheme, chain, *it);
		EUofAllEC.push_back(eu);

		////qDebug() << i << ":" << eu;
		////qDebug() << "------------------------";
	}
	return EUofAllEC;
}

//Expected utility values for all sets
template <typename VertexType>
vector<double> & Graph<VertexType>::getEUForAllES(){

	EUofAllES.clear();

	int length;
	if (maxLength>maxChainLength){
		length = maxLength;
	}
	else{
		length = maxChainLength;
	}

	//Initialize submatrices (5 year, 10 year survivals stored in subutility matrix)
	vector<vector<bool> > subIncidenceMatrix(length + 1, vector<bool>(length + 1, false));
	vector<vector<double> > subUtilityMatrix(length + 1, vector<double>(length + 1, 0));
	vector<vector<double> > subProbabilityMatrix(length + 1, vector<double>(length + 1, 0));
	vector<double> subProbVertexVector(length + 1, 0.0);
	vector<int> subStatusVector(length + 1, 0);

	int i = 0;

	for (typename vector<vector<int> >::iterator it = allEC.begin(); it != allEC.end(); it++){
		bool debug = false;
		if (i == 5){ debug = true; }
		double u = getEUForFB(*it, subIncidenceMatrix, subUtilityMatrix, subProbabilityMatrix, subProbVertexVector, subStatusVector, debug);
		EUofAllES.push_back(u);
		//simLog << i << ":" << u << endl;
		i++;
	}
	//simLog << "--------------------------" << endl;
	return EUofAllES;
}

//Expected utility values for all components
template <typename VertexType>
vector<double> & Graph<VertexType>::getEUForAllSCC(){

	EUofAllSCC.clear();

	//Initialize submatrices (5 year, 10 year survivals stored in subutility matrix)
	vector<vector<bool> > subIncidenceMatrix(maxChainLength + 1, vector<bool>(maxChainLength + 1, false));
	vector<vector<double> > subUtilityMatrix(maxChainLength + 1, vector<double>(maxChainLength + 1, 0));
	vector<vector<double> > subProbabilityMatrix(maxChainLength + 1, vector<double>(maxChainLength + 1, 0));
	vector<double> subProbVertexVector(maxChainLength + 1, 0.0);
	vector<int> subStatusVector(maxChainLength + 1, 0);

	for (typename vector<vector<int > >::iterator it = allEC.begin(); it != allEC.end(); it++){
		double u = getEUForFB(*it, subIncidenceMatrix, subUtilityMatrix, subProbabilityMatrix, subProbVertexVector, subStatusVector, false);
		EUofAllSCC.push_back(u);
	}
	return EUofAllSCC;
}

//Helper function for fallback options
template <typename VertexType>
double Graph<VertexType>::getPartialUtility(int nV, vector<vector<bool> > & incidenceMatrix_temp, vector<vector<double> > &subsubUtilityMatrix, vector<int> & subsubStatusVector){

	int start = 1;
	vector<vector<int> > possibleCycles;
	vector<double> UofPossibleCycles;
	double utility = 0;
	double utilEstimate = 0;
	vector<int> visitedVec(nV + 1, 0);
	vector<int> stack_vec;

	while (start <= nV){
		visitedVec[start] = 1;
		stack_vec.push_back(start);
		int v = getChild(start, stack_vec.back(), visitedVec, incidenceMatrix_temp);
		while (!stack_vec.empty()){
			if (v == -1){
				int top = stack_vec.back();
				stack_vec.pop_back();
				if (top == start) {
					visitedVec[top] = 0;
					break;
				}
				visitedVec[top] = 0;
				v = getChild(top, stack_vec.back(), visitedVec, incidenceMatrix_temp);
			}
			else{
				visitedVec[v] = 1;
				stack_vec.push_back(v);

				if (incidenceMatrix_temp[v][start] == true){
					int chaintest = 0;
					for (typename vector<int>::iterator it = stack_vec.begin(); it != stack_vec.end(); ++it){
						if (subsubStatusVector[*it] != 0){
							chaintest++;
						}
					}
					if (chaintest <= 1){
						possibleCycles.push_back(vector<int>(stack_vec.begin(), stack_vec.end()));

						double temp = 0;
						for (int i = 0; i < stack_vec.size() - 1; i++)
							temp = temp + subsubUtilityMatrix[stack_vec[i]][stack_vec[i + 1]];
						temp = temp + subsubUtilityMatrix[stack_vec.back()][start];
						UofPossibleCycles.push_back(temp);
						if (temp > utilEstimate){ utilEstimate = temp; }

					}
				}

				bool chain = false;
				for (typename vector<int>::iterator it = stack_vec.begin(); it != stack_vec.end(); ++it){
					if (subsubStatusVector[*it] != 0){
						chain = true;
					}
				}

				if (chain == true){
					if (stack_vec.size() >= maxChainLength)
						v = -1;
					else
						v = getChild(start, v, visitedVec, incidenceMatrix_temp);
				}
				else {
					if (stack_vec.size() >= maxLength)
						v = -1;
					else
						v = getChild(start, v, visitedVec, incidenceMatrix_temp);
				}
			}
		}
		start++;
	}

	if (maxChainLength > 4){
		//simLog << "Entered Here" << endl;
		utility = utilEstimate;
	}

	else if (possibleCycles.size() == 1){
		utility = UofPossibleCycles.at(0);

		/*for (typename vector<int>::iterator it = possibleCycles.at(0).begin(); it != possibleCycles.at(0).end() - 1; it++){
		utility += subsubUtilityMatrix[*it][*(it + 1)];
		}
		utility += subsubUtilityMatrix[*(possibleCycles.at(0).end() - 1)][*(possibleCycles.at(0).begin())];*/
	}

	else if (possibleCycles.size() > 1){

		int nPossibleCycles = (int)possibleCycles.size();

		/*for (typename vector<vector<int> >::iterator it = possibleCycles.begin(); it != possibleCycles.end(); it++){
		double u = 0;
		for (typename vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end() - 1; it2++){
		u += subsubUtilityMatrix[*it2][*(it2 + 1)];
		}
		u += subsubUtilityMatrix[*(it->end() - 1)][*(it->begin())];
		UofPossibleCycles.push_back(u);
		}*/

		for (int c = 1; c < pow((double)2, nPossibleCycles); c++){
			double tempU = 0;

			vector<int> cycleVec_flags(nPossibleCycles, 0);
			int mc = c;
			int kc = 0;
			int countc = 0;
			while (mc != 0){
				int rc = mc % 2;
				cycleVec_flags[kc] = rc;
				mc = mc / 2;
				kc++;
			}

			vector<int> checkUniqueness(nV + 1, 0);
			bool validSolution = true;
			double uOfCombination = 0;
			for (int q = 0; q < nPossibleCycles; q++){
				if (cycleVec_flags[q] == 1){
					tempU += UofPossibleCycles[q];
					for (typename vector<int>::iterator it3 = possibleCycles.at(q).begin(); it3 != possibleCycles.at(q).end(); ++it3){
						if (checkUniqueness[*it3] == 0){
							checkUniqueness[*it3]++;
						}
						else if (checkUniqueness[*it3] == 1){
							validSolution = false;
						}
					}
				}
			}

			if (validSolution == true && tempU > utility){
				utility = tempU;
			}
		}
	}

	return utility;
}

//Returns the longest complete cycle/chain within a set/component
/*
template <typename VertexType>
void Graph<VertexType>::getLongestCycle (int nV, vector<int> & longestVec,vector<vector<bool> > & incidenceMatrix_temp){

int start = 1; int size = 0;
vector<int> visitedVec(nV+1,0);
vector<int> stack_vec;

longestVec.clear();

while(start<=nV){
visitedVec[start] = 1;
stack_vec.push_back(start);
int v = getChild(start, stack_vec.back(), visitedVec, incidenceMatrix_temp);
while( !stack_vec.empty()){
if(v == -1){
int top=stack_vec.back();
stack_vec.pop_back();
if(top == start) {
visitedVec[top] = 0;
break;
}
visitedVec[top] = 0;
v = getChild(top,stack_vec.back(),visitedVec,incidenceMatrix_temp);
} else{
visitedVec[v] = 1;
stack_vec.push_back(v);
if(incidenceMatrix_temp[v][start] == 1){
if (stack_vec.size()>size) {
size = (int) stack_vec.size();
longestVec.clear();
longestVec.assign(stack_vec.begin(),stack_vec.end());
}
}
v=getChild(start, stack_vec.back(),visitedVec, incidenceMatrix_temp);
}
}
start++;
}
}
*/

//Expected utility of fallback options
template <typename VertexType>
double Graph<VertexType>::getEUForFB(vector<int> &FB, vector<vector<bool> > &subIncidenceMatrix, vector<vector<double> > &subUtilityMatrix,
	vector<vector<double> > &subProbabilityMatrix, vector<double> &subProbVertexVector, vector<int> &subStatusVector, bool debug){
	int nV = (int)FB.size();
	double utility = 0;

	int i = 1, j = 1;

	//Form submatrices
	for (typename vector<int>::iterator it = FB.begin(); it != FB.end(); ++it, i++){
		for (typename vector<int>::iterator it2 = FB.begin(); it2 != FB.end(); ++it2, j++){
			if (i != j){
				subIncidenceMatrix[i][j] = incidenceMatrix[*it][*it2];
				subProbabilityMatrix[i][j] = probabilityMatrix[*it][*it2];
				if (utilityScheme.compare("TRANSPLANTS") == 0){
					subUtilityMatrix[i][j] = viableTransplantMatrix[*it][*it2];
				}
				else if (utilityScheme.compare("SURVIVAL5YEAR") == 0){
					subUtilityMatrix[i][j] = survival5yearMatrix[*it][*it2];
				}
				else if (utilityScheme.compare("SURVIVAL10YEAR") == 0){
					subUtilityMatrix[i][j] = survival10yearMatrix[*it][*it2];
				}
				else {
					subUtilityMatrix[i][j] = scoreMatrix[*it][*it2];
				}
			}
		}
		subProbVertexVector[i] = pairVector[*it]->uncertainty;
		subStatusVector[i] = pairVector[*it]->donorType;
		j = 1;
	}

	int possibleConfigs = 0;

	//Iterates through each possible subset of vertices
	for (int v = 3; v< pow((double)2, nV); v++){
		vector<int> vertexVec_flags(nV + 1, 0);
		int mv = v;
		int kv = 1;
		int countv = 0;
		while (mv != 0){
			int rv = mv % 2;
			if (rv == 1) {
				countv++;
				vertexVec_flags[kv] = countv;
			}
			mv = mv / 2;
			kv++;
		}

		//Must have at least 2 pairs/ADs
		if (countv>1){
			double probVertexSubset = 1;
			for (int q = 1; q<nV + 1; q++){
				//If vertex is included in this subset, include probability
				if (vertexVec_flags[q] != 0){
					probVertexSubset = probVertexSubset*subProbVertexVector[q];
				}
				//If vertex is not included in this subset, include 1-probability
				else{
					probVertexSubset = probVertexSubset*(1 - subProbVertexVector[q]);
				}
			}

			//Form sub-sub matrices
			vector<vector<bool> > subsubIncidenceMatrix(countv + 1, vector<bool>(countv + 1, false));
			vector<vector<double> > subsubUtilityMatrix(countv + 1, vector<double>(countv + 1, 0));
			vector<vector<double> > subsubProbabilityMatrix(countv + 1, vector<double>(countv + 1, 0));
			vector<int> subsubStatusVector(countv + 1, 0);

			int nE = 0;
			vector<vector<int> > edgeMatrix; edgeMatrix.push_back(vector<int>(0));
			vector<double> edgeProbVec; edgeProbVec.push_back(0);

			for (int imb = 1; imb<countv + 1; imb++){
				for (int jmb = 1; jmb<countv + 1; jmb++){
					if (imb != jmb){
						int posi = 0;
						while (vertexVec_flags[posi] != imb){
							posi++;
						}
						int posj = 0;
						while (vertexVec_flags[posj] != jmb){
							posj++;
						}
						subsubIncidenceMatrix[imb][jmb] = subIncidenceMatrix[posi][posj];
						subsubUtilityMatrix[imb][jmb] = subUtilityMatrix[posi][posj];
						subsubProbabilityMatrix[imb][jmb] = subProbabilityMatrix[posi][posj];
						if (subsubIncidenceMatrix[imb][jmb] == true){
							vector<int> temp_vec(3, 0);
							temp_vec[1] = imb; temp_vec[2] = jmb;
							edgeMatrix.push_back(temp_vec);
							edgeProbVec.push_back(1 - subsubProbabilityMatrix[imb][jmb]);
							nE++;
						}
					}
				}
			}

			for (int imb = 1; imb<countv + 1; imb++){
				int posi = 0;
				while (vertexVec_flags[posi] != imb){
					posi++;
				}
				subsubStatusVector[imb] = subStatusVector[posi];
			}

			// Iterate through every possible combination of edges
			double partialUtility = 0;
			for (int n = 3; n< pow((double)2, nE); n++){
				vector<vector<bool> > incidenceMatrix_temp(countv + 1, vector<bool>(countv + 1, false));
				vector<double> edgeProbVec_temp(edgeProbVec);
				int m = n;
				int k = 1;
				int count = 0;
				while (m != 0){
					int r = m % 2;
					if (r == 1) {
						incidenceMatrix_temp[edgeMatrix[k][1]][edgeMatrix[k][2]] = true;
						edgeProbVec_temp[k] = 1 - edgeProbVec[k];
						count++;
					}
					m = m / 2;
					k++;
				}
				//Calculate probability of subset
				if (count > 1){
					double probability = 1;
					for (int j = 1; j < edgeProbVec_temp.size(); j++){
						probability = probability*edgeProbVec_temp[j];
					}

					double calc = probability*getPartialUtility(countv, incidenceMatrix_temp, subsubUtilityMatrix, subsubStatusVector);
					if (debug == true){
						////qDebug() << calc;
					}
					partialUtility = partialUtility + calc;
				}
			}
			//if (debug==true){
			//	//qDebug() << partialUtility*probVertexSubset;
			//}
			utility = utility + partialUtility*probVertexSubset;
		}
	}
	//simLog << "--------------------------" << endl;
	return utility;
}

//Get max utility cycle solution in FB
template <typename VertexType>
int Graph<VertexType>::getMUCInFB(int nV, vector<vector<bool> > &incidenceMatrix_temp, vector<vector<double> > &subUtilityMatrix, vector<int> &subStatusVector, vector<int> &indexToPoolIDVector){

	allFB.clear();
	UofAllFB.clear();

	vector<vector<int> > storedCycles;

	int start = 1;
	vector<int> visitedVector(nV + 1, 0);
	vector<int> stack_vec;

	//Depth first search of set/component
	while (start <= nV){
		visitedVector[start] = 1;
		stack_vec.push_back(start);
		int v = getChild(start, start, visitedVector, incidenceMatrix_temp);
		while (!stack_vec.empty()){
			if (v == -1){
				int top = stack_vec.back();
				stack_vec.pop_back();
				if (top == start){
					visitedVector[top] = 0;
					break;
				}
				visitedVector[top] = 0;
				v = getChild(top, stack_vec.back(), visitedVector, incidenceMatrix_temp);
			}
			else{
				visitedVector[v] = 1;
				stack_vec.push_back(v);
				if (incidenceMatrix_temp[v][start] == true){
					int chaintest = 0;
					//string bridgeDonorBT;
					//vector<int> recipids;
					//bool repeatedRecip = false;
					for (typename vector<int>::iterator it = stack_vec.begin(); it != stack_vec.end(); ++it){
						//if (dataconfig.compare("APD MATCH RUN")==0){
						//recipids.push_back();
						//}
						if (subStatusVector[*it] != 0){
							chaintest++;
							//if (it == stack_vec.begin()){
							//bridgeDonorBT = ;
							//}
							//else {
							//bridgeDonorBT = ;
							//}
						}
					}

					//if (dataconfig.compare("APD MATCH RUN")==0){
					//sort(recipids.begin(),recipids.end());
					//for (int p=0; p<recipids.size()-1; p++){
					//if(recipids[p]==recipids[p+1]){
					//repeatedRecip = true;
					//}
					//}
					//}

					//if (repeatedRecip==false){
					if (chaintest == 1){
						//if (includeABbridgeDonors==true || (includeABbridgeDonors==false && bridgeDonorBT.compare("AB"))){	//Bridge donors ending in AB are not allowed
						if (chain_storage.compare("LAST") == 0){
							storedCycles.push_back(vector<int >(stack_vec.begin(), stack_vec.end()));
						}
						else {
							allFB.push_back(vector<int >(stack_vec.begin(), stack_vec.end()));
						}
						//}
					}
					else if (chaintest == 0){
						if (chain_storage.compare("FIRST") == 0){
							storedCycles.push_back(vector<int >(stack_vec.begin(), stack_vec.end()));
						}
						else {
							allFB.push_back(vector<int >(stack_vec.begin(), stack_vec.end()));
						}
					}
					//}
				}

				bool chain = false;
				for (typename vector<int>::iterator it = stack_vec.begin(); it != stack_vec.end(); ++it){
					if (subStatusVector[*it] != 0){
						chain = true;
					}
				}
				if (chain == true){
					if (stack_vec.size() >= maxChainLength)
						v = -1;
					else
						v = getChild(start, v, visitedVector, incidenceMatrix_temp);
				}
				else {
					if (stack_vec.size() >= maxLength)
						v = -1;
					else
						v = getChild(start, v, visitedVector, incidenceMatrix_temp);
				}
			}
		}
		start++;
	}

	if (storedCycles.size()>0){
		for (vector<vector<int> >::iterator it = storedCycles.begin(); it != storedCycles.end(); ++it){
			allFB.push_back(*it);
		}
	}

	//If there are multiple solutions
	if (allFB.size()>0){
		for (typename vector<vector<int> >::iterator it = allFB.begin(); it != allFB.end(); it++){
			double u = 0;
			for (typename vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end() - 1; it2++){
				u += subUtilityMatrix[*it2][*(it2 + 1)];
			}
			u = u + subUtilityMatrix[*(it->end() - 1)][*(it->begin())];
			UofAllFB.push_back(u);
		}

		getFB(nV, indexToPoolIDVector);
		return 1;
	}
	else {
		return 0;
	}
}

//Calculate max utility within a set/component
template <typename VertexType>
double Graph<VertexType>::getMaxUtilityInFB(int nV, vector<vector<bool> > & incidenceMatrix_temp, vector<vector<double> > &subUtilityMatrix){

	int start = 1;
	double utility = 0;
	vector<int> visitedVec(nV + 1, 0);
	vector<int> stack_vec;

	while (start <= nV){
		visitedVec[start] = 1;
		stack_vec.push_back(start);
		int v = getChild(start, stack_vec.back(), visitedVec, incidenceMatrix_temp);
		while (!stack_vec.empty()){
			if (v == -1){
				int top = stack_vec.back();
				stack_vec.pop_back();
				if (top == start) {
					visitedVec[top] = 0;
					break;
				}
				visitedVec[top] = 0;
				v = getChild(top, stack_vec.back(), visitedVec, incidenceMatrix_temp);
			}

			else{
				visitedVec[v] = 1;
				stack_vec.push_back(v);

				if (incidenceMatrix_temp[v][start] == true){
					double temp = 0;
					for (int i = 0; i< stack_vec.size() - 1; i++)
						temp = temp + subUtilityMatrix[stack_vec[i]][stack_vec[i + 1]];
					temp = temp + subUtilityMatrix[stack_vec.back()][start];
					if (temp>utility) {
						utility = temp;
					}
				}
				v = getChild(start, stack_vec.back(), visitedVec, incidenceMatrix_temp);
			}
		}
		start++;
	}

	return utility;
}

template <typename VertexType>
void Graph<VertexType>::outputCycles(){
	vector<vector<int> > Record_Cycles;

	for (typename vector<vector<int> >::iterator it = allEC.begin(); it != allEC.end(); ++it){
		double total_mismatches = 0.0;
		vector<int> list;
		for (typename vector<int>::iterator it2 = it->begin(); it2 != it->end() - 1; it2++){
			list.push_back(*it2);
		}
		list.push_back(*(it->end() - 1));
		Record_Cycles.push_back(list);
	}
	string cycleFileName = "output/" + outputName + "/Logfiles/CycleList_" + intToString(KPD_simuID) + "_" + KPD_strategy + ".csv";
	ofstream oFile(cycleFileName.c_str());
	stringstream ss_cycles_out;
	for (typename vector<vector<int> >::iterator it = Record_Cycles.begin(); it != Record_Cycles.end(); it++){
		/*if (dataconfig.compare("APD MATCH RUN")!=0){
		for(typename vector<int>::iterator it2 = it->begin (); it2 != it->end()-1; it2++  ){
		ss_cycles_out<<pairVector[*it2]->pairLabel <<",";
		}
		ss_cycles_out<<pairVector[*(it->end()-1)]->pairLabel << endl;
		}*/

		for (typename vector<int>::iterator it2 = it->begin(); it2 != it->end() - 1; it2++){
			ss_cycles_out << *it2 << ",";
		}
		ss_cycles_out << *(it->end() - 1) << endl;
	}
	oFile << ss_cycles_out.str();
	oFile.close();
}

//Optimize
template <typename VertexType>
void Graph<VertexType>::getOptimalSolution(string scheme){

	SelectedSolutions.clear();
	SelectedStructures.clear();
	SolutionObjectives.clear();

	int nStructures = (int)allEC.size();
	if (nStructures == 0) return;

	//vector<vector<int> > optimalSolutions;
	//vector<double> optimalObjectives;

	double objective = 0;
	int iteration = 1;
	bool continueIterating = true;

	GRBEnv *env = 0;	//Created outside try; needs to be recollected;
	GRBVar *vars = 0;	//Created outside try; needs to be recollected;
	GRBVar *myVars = new GRBVar[nStructures + 1]; //Created outside try; needs to be recollected;
	try{
		env = new GRBEnv();
		env->set(GRB_IntParam_Threads, 4); // Limit the threads

		GRBModel model = GRBModel(*env);
		model.getEnv().set(GRB_IntParam_OutputFlag, 0);// 0 means no solver output; 1 otherwise;


		//Set utilities on structures
		if (scheme.compare("MUC") == 0)
		{
			for (int i = 1; i <= nStructures; i++){
				string s = "cycle_" + intToString(i);
				myVars[i] = model.addVar(0.0, 1.0, -1 * UofAllEC[i - 1] /* Max Utility */, GRB_BINARY, s); //The default is min, hence the -1
			}
		}
		else if (scheme.compare("MEUC") == 0)
		{
			for (int i = 1; i <= nStructures; i++){
				string s = "cycle_" + intToString(i);
				myVars[i] = model.addVar(0.0, 1.0, -1 * EUofAllEC[i - 1] /* Max Utility */, GRB_BINARY, s); //The default is min, hence the -1
			}
		}
		else if (scheme.compare("MEUS") == 0)
		{
			for (int i = 1; i <= nStructures; i++){
				string s = "cycle_" + intToString(i);
				myVars[i] = model.addVar(0.0, 1.0, -1 * EUofAllES[i - 1] /* Max Utility */, GRB_BINARY, s); //The default is min, hence the -1
			}
		}
		else if (scheme.compare("SCC") == 0)
		{
			for (int i = 1; i <= nStructures; i++){
				string s = "cycle_" + intToString(i);
				myVars[i] = model.addVar(0.0, 1.0, -1 * EUofAllSCC[i - 1] /* Max Utility */, GRB_BINARY, s); //The default is min, hence the -1
			}
		}
		model.update();

		//Restriction: Each vertex can only appear at most once in solution
		for (int i = 1; i <= nVertices; i++){
			GRBLinExpr expr = 0;
			for (int j = 0; j <= nStructures - 1; j++){
				for (typename vector<int>::iterator it = allEC[j].begin(); it != allEC[j].end(); ++it){
					if (*it == i){
						expr += myVars[j + 1];
					}
				}
			}
			string s = "vertex_" + intToString(i);
			model.addConstr(expr, GRB_LESS_EQUAL, 1.0, s); // Disjoint cycles and chains
		}

		//Restriction: For match run, recipients can be in multiple vertices
		//Each recipient can appear at most once in each solution
		if (dataconfig.compare("APD MATCH RUN") == 0){
			for (int i = 1; i <= nVertices; i++){
				GRBLinExpr exprmb = 0;
				for (int j = 0; j <= nStructures - 1; j++){
					for (typename vector<int>::iterator it = allEC[j].begin(); it != allEC[j].end(); ++it){
						if (pairVector[*it]->recipID == pairVector[i]->recipID){
							exprmb += myVars[j + 1];
						}
					}
				}

				string s = "recipient_" + intToString(pairVector[i]->recipID);
				model.addConstr(exprmb, GRB_LESS_EQUAL, 1.0, s);
			}
		}
		model.optimize();
		int optimstatus = model.get(GRB_IntAttr_Status);
		if (tiebreakIterations > 1){
			simLog << iteration << "- ";
		}
		simLog << "Optimization complete / ";
		double objval = 0;
		if (optimstatus == GRB_OPTIMAL) { // GRB_OPTIMAL when the MIPGap is reached, default is 1e-4;
			objval = model.get(GRB_DoubleAttr_ObjVal);
			simLog << "Optimal objective: " << (-1)*objval << endl;
		}
		else if (optimstatus == GRB_INF_OR_UNBD) {
			simLog << "Model is infeasible or unbounded" << endl;
			return;
		}
		else if (optimstatus == GRB_INFEASIBLE) {
			simLog << "Model is infeasible" << endl;
			return;
		}
		else if (optimstatus == GRB_UNBOUNDED) {
			simLog << "Model is unbounded" << endl;
			return;
		}
		else {
			simLog << "Optimization was stopped with status = " << optimstatus << endl;
			return;
		}

		int numvars = model.get(GRB_IntAttr_NumVars);
		vars = model.getVars();

		vector<int> candidateSolution;

		for (int j = 0; j < numvars; j++) {
			GRBVar v = vars[j];
			if (v.get(GRB_DoubleAttr_X) == 1){
				candidateSolution.push_back(j);
			}
		}

		SelectedSolutions.push_back(candidateSolution);
		SolutionObjectives.push_back(objval);
		//optimalSolutions.push_back(candidateSolution);
		//objective = objval;
		//optimalObjective.push_back(objval);
		//optimalObjectives.push_back(objective);

		while (continueIterating == true && iteration<tiebreakIterations){
			iteration++;
			GRBLinExpr expr = 0;

			//Add restriction against previously found solution
			for (int j = 0; j <= nStructures - 1; j++){
				bool found = false;
				//for (typename vector<int>::iterator it = optimalSolutions[iteration - 2].begin(); it != optimalSolutions[iteration - 2].end(); ++it){
				for (typename vector<int>::iterator it = SelectedSolutions[iteration - 2].begin(); it != SelectedSolutions[iteration - 2].end(); ++it){
					if (*it == j){ found = true; }
				}
				if (found == true){
					expr += (1 - myVars[j + 1]);
				}
				else {
					expr += myVars[j + 1];
				}
			}
			string s = "alternate_" + intToString(iteration - 2);
			model.addConstr(expr, GRB_GREATER_EQUAL, 1.0, s); //Remove previous solution
			
			model.optimize();

			optimstatus = model.get(GRB_IntAttr_Status);
			simLog << iteration << ": ";
			if (optimstatus == GRB_OPTIMAL) { // GRB_OPTIMAL when the MIPGap is reached, default is 1e-4;
				objval = model.get(GRB_DoubleAttr_ObjVal);
				simLog << "Completed with optimal objective: " << (-1)*objval << endl;
			}
			else if (optimstatus == GRB_INF_OR_UNBD) {
				simLog << "Model is infeasible or unbounded" << endl;
				return;
			}
			else if (optimstatus == GRB_INFEASIBLE) {
				simLog << "Model is infeasible" << endl;
				return;
			}
			else if (optimstatus == GRB_UNBOUNDED) {
				simLog << "Model is unbounded" << endl;
				return;
			}
			else {
				simLog << "Optimization was stopped with status = " << optimstatus << endl;
				return;
			}

			numvars = model.get(GRB_IntAttr_NumVars);
			vars = model.getVars();

			vector<int> candidateSolution;

			for (int j = 0; j < numvars; j++) {
				GRBVar v = vars[j];
				if (v.get(GRB_DoubleAttr_X) == 1){
					candidateSolution.push_back(j);
				}
			}

			//if (objval == objective){
			SelectedSolutions.push_back(candidateSolution);
			SolutionObjectives.push_back(objval);
				//optimalSolutions.push_back(candidateSolution);
				//optimalObjectives.push_back(objval);
			//}
			//else {
				//simLog << " (Subobtimal - End Iterations)" << endl;
				//iteration--;
				//continueIterating = false;
			//}
		}

	}
	catch (GRBException e) {
		//simLog << "Error code = " << e.getErrorCode() << endl;
		//simLog << e.getMessage() << endl;
	}
	catch (...) {
		simLog << "Error during optimization" << endl;
	}

	delete[] myVars;
	delete[] vars;
	delete env;

	int q = 0;
	double bestScore = -1.0;
	int bestSolution = -1;

	//for (typename vector<vector<int> >::iterator it = optimalSolutions.begin(); it != optimalSolutions.end(); ++it){
	for (typename vector<vector<int> >::iterator it = SelectedSolutions.begin(); it != SelectedSolutions.end(); ++it){
		//simLog << "Solution " << q + 1 << " / Objective = " << SolutionObjectives[q];
		double score = 0;
		double transplants = 0;
		for (typename vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2){
			//simLog << *it2 << " ";
			for (typename vector<int>::iterator it3 = allEC[*it2].begin(); it3 != allEC[*it2].end() - 1; ++it3){
				score += scoreMatrix[*it3][*(it3 + 1)];
				transplants += viableTransplantMatrix[*it3][*(it3 + 1)];
			}
			score += scoreMatrix[*(allEC[*it2].end() - 1)][*(allEC[*it2].begin())];
			transplants += viableTransplantMatrix[*(allEC[*it2].end() - 1)][*(allEC[*it2].begin())];
		}
		//simLog << transplants << " (Score = " << score << ")" << endl;
		if (score>bestScore){
			bestScore = score;
			bestSolution = q;
		}
		q++;
	}
	
	//if (tiebreakIterations > 1) {
		//simLog << "Optimization Complete" << endl << "Optimal Objective: " << (-1)*objective << endl;
		//simLog << "Chosen Solution: " << bestSolution + 1 << "/" << iteration << endl;
	//}
	//simLog << "Optimization Complete with Optimal Objective: " << objective << ". Chosen Solution: " << bestSolution + 1 << "/" << iteration << endl << endl;
	
	//SelectedStructures = optimalSolutions[bestSolution];
	SelectedStructures = SelectedSolutions[bestSolution];
	//simLog << SelectedStructures.size();
}

template <typename VertexType>
vector<vector<int> > & Graph<VertexType>::returnSolutionSet(){
	return SelectedSolutions;
}

template <typename VertexType>
vector<int> & Graph<VertexType>::returnOptimalSolution(){
	return SelectedStructures;
}

template <typename VertexType>
vector<double> & Graph<VertexType>::returnSolutionObjectives(){
	return SolutionObjectives;
}

//Optimize within set/component for fallbacks
template <typename VertexType>
void Graph<VertexType>::getFB(int nV, vector<int> & indexToPoolIDVector){

	FB.clear();
	int nCycles = (int)allFB.size();
	if (nCycles == 0) return;

	GRBEnv *env = 0;						 //Created outside try; needs to be recollected;
	GRBVar *vars = 0;						 //Created outside try; needs to be recollected;
	GRBVar *myVars = new GRBVar[nCycles + 1]; //Created outside try; needs to be recollected;
	try{
		env = new GRBEnv();
		env->set(GRB_IntParam_Threads, 4); // Limit the threads

		GRBModel model = GRBModel(*env);
		model.getEnv().set(GRB_IntParam_OutputFlag, 0);// 0 means no solver output; 1 otherwise;

		for (int i = 1; i <= nCycles; i++){
			string s = "cycle_" + intToString(i);
			myVars[i] = model.addVar(0.0, 1.0, -1 * UofAllFB[i - 1] /* Utility of fallback option */, GRB_BINARY, s); //The default is min, hence the -1
		}
		model.update(); //Lazy update;

		for (int i = 1; i <= nV; i++){
			GRBLinExpr expr = 0;
			for (int j = 0; j <= nCycles - 1; j++){
				for (typename vector<int>::iterator it = allFB[j].begin(); it != allFB[j].end(); ++it){
					if (*it == i){
						expr += myVars[j + 1];
					}
				}
			}
			string s = "vertex_" + intToString(i);
			model.addConstr(expr, GRB_LESS_EQUAL, 1.0, s); /* Disjoint cycles/chains */
		}

		if (dataconfig.compare("APD MATCH RUN") == 0){
			for (int i = 1; i <= nV; i++){
				GRBLinExpr exprmb = 0;
				for (int j = 0; j <= nCycles - 1; j++){
					for (typename vector<int>::iterator it = allFB[j].begin(); it != allFB[j].end(); ++it){
						if (pairVector[indexToPoolIDVector[*it]]->recipID == pairVector[indexToPoolIDVector[i]]->recipID){
							exprmb += myVars[j + 1];
						}
					}
				}

				string s = "recipient_" + intToString(pairVector[indexToPoolIDVector[i]]->recipID);
				model.addConstr(exprmb, GRB_LESS_EQUAL, 1.0, s);
			}
		}

		model.optimize();

		int optimstatus = model.get(GRB_IntAttr_Status);
		simLog << "Optimization complete" << endl;
		double objval = 0;
		if (optimstatus == GRB_OPTIMAL) { // GRB_OPTIMAL when the MIPGap is reached, default is 1e-4;
			objval = model.get(GRB_DoubleAttr_ObjVal);
			simLog << "Optimal objective: " << objval << endl;
		}
		else if (optimstatus == GRB_INF_OR_UNBD) {
			simLog << "Model is infeasible or unbounded" << endl; return;
		}
		else if (optimstatus == GRB_INFEASIBLE) {
			simLog << "Model is infeasible" << endl; return;
		}
		else if (optimstatus == GRB_UNBOUNDED) {
			simLog << "Model is unbounded" << endl; return;
		}
		else {
			simLog << "Optimization was stopped with status = " << optimstatus << endl; return;
		}

		int numvars = model.get(GRB_IntAttr_NumVars);
		vars = model.getVars();

		for (int j = 0; j < numvars; j++) {
			GRBVar v = vars[j];
			if (v.get(GRB_DoubleAttr_X) == 1){ FB.push_back(j); }
		}

	}
	catch (GRBException e) {
		simLog << "Error code = " << e.getErrorCode() << endl;
		simLog << e.getMessage() << endl;
	}
	catch (...) {
		simLog << "Error during optimization" << endl;
	}

	delete[] myVars;
	delete[] vars;
	delete env;
}

//Prepares transplant stats for transplant between dPoolID and rPoolID
template <typename VertexType>
void Graph<VertexType>::getTransplantStats(int dPoolID, int rPoolID){
	vector<double> stat_row;
	stat_row.assign(54, 0.0);
	stat_row[0] = KPD_simuID;
	stat_row[1] = scoreMatrix[dPoolID][rPoolID];
	stat_row[2] = survival5yearMatrix[dPoolID][rPoolID];
	stat_row[3] = survival10yearMatrix[dPoolID][rPoolID];

	//Recipient Demo Information
	string rBT = pairVector[rPoolID]->recipBT;
	if ((rBT).compare("O") == 0){ stat_row[4] = 1.0; }
	else if ((rBT).compare("A") == 0){ stat_row[5] = 1.0; }
	else if ((rBT).compare("B") == 0){ stat_row[6] = 1.0; }
	else if ((rBT).compare("AB") == 0){ stat_row[7] = 1.0; }
	//stats->addRecipBT(rBT);

	double rPRA = pairVector[rPoolID]->recipPRA;
	if ((rPRA) <= 100 && (rPRA) >= 75){ stat_row[8] = 1.0; }
	else if ((rPRA)<75 && (rPRA) >= 50){ stat_row[9] = 1.0; }
	else if ((rPRA)<50 && (rPRA) >= 25){ stat_row[10] = 1.0; }
	else if ((rPRA)<25 && (rPRA) >= 0) { stat_row[11] = 1.0; }
	//stats->addRecipPRA(rPRA);

	double rAge = pairVector[rPoolID]->recipAge;
	if ((rAge) <= 35){ stat_row[12] = 1.0; }
	else if ((rAge) <= 50 && (rAge)>35){ stat_row[13] = 1.0; }
	else if ((rAge) <= 65 && (rAge)>50){ stat_row[14] = 1.0; }
	else if ((rAge)>65) { stat_row[15] = 1.0; }
	//stats->addRecipAge(rAge);

	double rBMI = pairVector[rPoolID]->recipBMI;
	if ((rBMI)<30){ stat_row[16] = 1.0; }
	else { stat_row[17] = 1.0; }
	//stats->addRecipBMI(rBMI);

	bool rDiabetes = pairVector[rPoolID]->recipDiabetes;
	if ((rDiabetes) == false){ stat_row[18] = 1.0; }
	else { stat_row[19] = 1.0; }
	//stats->addRecipDiabetes(rDiabetes);

	bool rSex = pairVector[rPoolID]->recipMale;
	if ((rSex) == true){ stat_row[20] = 1.0; }
	else { stat_row[21] = 1.0; }
	//stats->addRecipSex(rSex);

	string rRace = pairVector[rPoolID]->recipRace;
	if ((rRace).compare(0, 1, "W") == 0){ stat_row[22] = 1.0; }
	else if ((rRace).compare(0, 1, "B") == 0){ stat_row[23] = 1.0; }
	else if ((rRace).compare(0, 1, "H") == 0){ stat_row[24] = 1.0; }
	else { stat_row[25] = 1.0; }
	//stats->addRecipRace(rRace);

	bool rPrevTrans = pairVector[rPoolID]->recipPrevTrans;
	if ((rPrevTrans) == false){ stat_row[26] = 1.0; }
	else { stat_row[27] = 1.0; }
	//stats->addRecipPrevTrans(rPrevTrans);

	double rTOD = pairVector[rPoolID]->recipTOD;
	if ((rTOD) == 0){ stat_row[28] = 1.0; }
	else if ((rTOD)>0 && (rTOD) <= 0.5){ stat_row[29] = 1.0; }
	else if ((rTOD)>0.5 && (rTOD) <= 1){ stat_row[30] = 1.0; }
	else if ((rTOD)>1 && (rTOD) <= 2){ stat_row[31] = 1.0; }
	else if ((rTOD)>2 && (rTOD) <= 3){ stat_row[32] = 1.0; }
	else { stat_row[33] = 1.0; }
	//stats->addRecipTOD(rTOD);

	bool rHepC = pairVector[rPoolID]->recipHepC;
	if ((rHepC) == false){ stat_row[34] = 1.0; }
	else { stat_row[35] = 1.0; }
	//stats->addRecipHepC(rHepC);

	//Donor Demo Information
	string dBT = pairVector[dPoolID]->donorBT;
	if ((dBT).compare("O") == 0){ stat_row[36] = 1.0; }
	else if ((dBT).compare("A") == 0){ stat_row[37] = 1.0; }
	else if ((dBT).compare("B") == 0){ stat_row[38] = 1.0; }
	else if ((dBT).compare("AB") == 0){ stat_row[39] = 1.0; }
	//stats->addDonorBT(dBT);

	double dAge = pairVector[dPoolID]->donorAge;
	if ((dAge) <= 50){ stat_row[40] = 1.0; }
	else { stat_row[41] = 1.0; }
	//stats->addDonorAge(dAge);

	double dBMI = pairVector[dPoolID]->donorBMI;
	if ((dBMI)<30){ stat_row[42] = 1.0; }
	else { stat_row[43] = 1.0; }
	//stats->addDonorBMI(dBMI);

	bool dSex = pairVector[dPoolID]->donorMale;
	if ((dSex) == true){ stat_row[44] = 1.0; }
	else { stat_row[45] = 1.0; }
	//stats->addDonorSex(dSex);

	// Transplant Demo Information
	if ((dSex) == true && (rSex) == true){ /*stats->addTransplantMM();*/ stat_row[46] = 1.0; }
	else if ((dSex) == true && (rSex) == false){ /*stats->addTransplantMF();*/ stat_row[47] = 1.0; }
	else if ((dSex) == false && (rSex) == true){ /*stats->addTransplantFM();*/ stat_row[48] = 1.0; }
	else if ((dSex) == false && (rSex) == false){ /*stats->addTransplantFF();*/ stat_row[49] = 1.0; }

	double weightRatio = (pairVector[dPoolID]->donorWeight) / (pairVector[rPoolID]->recipWeight);
	if (weightRatio < 0.75){ stat_row[50] = 1.0; }
	else if (weightRatio >= 0.75 && weightRatio < 0.90){ stat_row[51] = 1.0; }
	else if (weightRatio >= 0.90 && weightRatio < 1.15){ stat_row[52] = 1.0; }
	else if (weightRatio >= 1.15){ stat_row[53] = 1.0; }
	//stats->addWeightRatio(weightRatio);

	vector<double> * stat_row_ptr = &stat_row;

	//stats->addrow(stat_row_ptr);
}

template <typename VertexType>
void Graph<VertexType>::simulation(int month){
	MR_CurrentNo++;
	simLog << "Match Run " << MR_CurrentNo << endl;

	if (outputCycleInfo == true){
		outputCycles();
	}

	if (SelectedStructures.size() == 0){
		simLog << "No cycles found" << endl;
		return;
	}

	set<int> finishedVertices;

	//Repeat for all selected cycles/chains
	for (typename vector<int>::iterator it = SelectedStructures.begin(); it != SelectedStructures.end(); ++it){

		//Queues up the AD/Bridge donor to the front of the cycle; Counts cycles and chains
		bool chain = false;
		for (int q = 0; q<allEC[*it].size(); q++){
			if (chain == false){
				int queue = *(allEC[*it].begin());
				allEC[*it].erase(allEC[*it].begin());
				allEC[*it].push_back(queue);

				if (pairVector[*(allEC[*it].begin())]->donorType != 0){
					chain = true;
					//stats->addChain();
				}
			}
		}

		if (chain == false){
			//stats->addCycle();
		}

		//Calculates expected values
		double cycleExpTransplants = calculateExpectation("TRANSPLANTS", chain, allEC[*it]);
		double cycleExpUtility = calculateExpectation(utilityScheme, chain, allEC[*it]);
		///////////////////////////////////////////////////////////////////////////

		//int i=1;
		bool failure = false;
		bool stbdReneged = false;

		int lengthOfChain = 0;
		double maxPossibleScore = 0;
		double maxPossible5yearSurvival = 0;
		double maxPossible10yearSurvival = 0;

		simLog << "Cycle #: " << *it << endl;
		for (typename vector<int >::iterator it2 = allEC[*it].begin(); it2 != allEC[*it].end() - 1; ++it2){
			maxPossibleScore += scoreMatrix[*it2][*(it2 + 1)];
			maxPossible5yearSurvival += survival5yearMatrix[*it2][*(it2 + 1)];
			maxPossible10yearSurvival += survival10yearMatrix[*it2][*(it2 + 1)];

			simLog << getPairID(*it2) << "-->" << getPairID(*(it2 + 1)) << endl;

			//Output
			/////////////////////////////////////////////////////////////////////////////////
			vector<double> edge_row;
			edge_row.push_back(MR_CurrentNo);									//Match Run
			edge_row.push_back(*it);												//Cycle #
			//if (chain==true){edge_row.push_back(1); }								//Cycle or Chain
			//else{ edge_row.push_back(0); }
			edge_row.push_back(getPairID(*it2));									//Donor #
			edge_row.push_back(getPairID(*(it2 + 1)));								//Recipient #
			edge_row.push_back(pairVector[*it2]->donorType);						//Pair=0, AD=1, Bridge Donor=2
			edge_row.push_back(pairVector[*(it2 + 1)]->donorType);
			edge_row.push_back(labCrossmatchMatrix[*it2][*(it2 + 1)]);			//Pass=1, Fail=0
			edge_row.push_back(pairVector[*it2]->pairAvailabilityVector[month]);	//Available=1, Not Available for This Match Run=0, Not Available Permanently=-1
			edge_row.push_back(pairVector[*(it2 + 1)]->pairAvailabilityVector[month]);
			edge_row.push_back(probabilityMatrix[*it2][*(it2 + 1)]);			//Prob Edge Failure
			edge_row.push_back(pairVector[*it2]->uncertainty);					//Prob Pair Unavailable
			edge_row.push_back(pairVector[*(it2 + 1)]->uncertainty);				//Prob Pair Unavailable
			edge_row.push_back(scoreMatrix[*it2][*(it2 + 1)]);					//Score
			edge_row.push_back(survival5yearMatrix[*it2][*(it2 + 1)]);			//5 Year Surv Prob
			edge_row.push_back(survival10yearMatrix[*it2][*(it2 + 1)]);		//10 Year Surv Prob		
			Record_Edge_Level.push_back(edge_row);
			/////////////////////////////////////////////////////////////////

			//Note: ALL pairs involved in a long chain are crossmatched; unnecessary to perform check for negative crossmatch, as these have been removed
			//in previous function
			if (labCrossmatchMatrix[*it2][*(it2 + 1)] == 1){
				simLog << "Positive Lab Crossmatch for " << getPairID(*it2) << "-->" << getPairID(*(it2 + 1));
				if (probabilityMatrix[*it2][*(it2 + 1)] != 1.0){
					probabilityMatrix[*it2][*(it2 + 1)] = 1.0;
					simLog << "; Probability Updated to 1";
				}
				simLog << endl;
			}

			//Remove failed vertices/edges
			if ((labCrossmatchMatrix[*it2][*(it2 + 1)] == 0) || (pairVector[*it2]->pairAvailabilityVector[month] != 1) || pairVector[*(it2 + 1)]->pairAvailabilityVector[month] != 1){
				if (pairVector[*it2]->pairAvailabilityVector[month] == 0){
					//finishedVertices.insert(getPairID(*it2));
					simLog << "Pair " << getPairID(*it2) << " Unavailable For This Match Run, ";
				}
				else if (pairVector[*it2]->pairAvailabilityVector[month] == -1){
					finishedVertices.insert(getPairID(*it2));
					simLog << "Pair " << getPairID(*it2) << " Unavailable Permanently, ";
				}

				if (pairVector[*(it2 + 1)]->pairAvailabilityVector[month] == 0){
					//finishedVertices.insert(getPairID(*(it2+1)));
					simLog << "Pair " << getPairID(*(it2 + 1)) << " Unavailable For This Match Run, ";
				}
				else if (pairVector[*(it2 + 1)]->pairAvailabilityVector[month] == -1){
					finishedVertices.insert(getPairID(*(it2 + 1)));
					simLog << "Pair " << getPairID(*(it2 + 1)) << " Unavailable Permanently, ";
				}

				if (labCrossmatchMatrix[*it2][*(it2 + 1)] == 0){
					removeEdgeByPoolID(*it2, *(it2 + 1));
				}
				simLog << "Transplant Failed" << endl;
				failure = true;
			}

			//Determines length of chain after accounting for failure, reneging
			if (chain == true && failure == false){
				lengthOfChain++;
			}

			//Short-Term Bridge Donor Calculations
			if ((allEC[*it].size() == 5 && lengthOfChain == 2) || (allEC[*it].size()>5 && lengthOfChain == 3)){
				if (chain == true && failure == false){
					//if (rng.runif() < short_renege_rate){
					if (pairVector[*(it2 + 1)]->pairSTBDRenegeVector[month] == 1){
						failure = true;
						stbdReneged = true;
						simLog << "Short-Term Bridge Donor " << getPairID(*(it2 + 1)) << " Reneged; Removed From Pool" << endl;
						finishedVertices.insert(getPairID(*(it2 + 1)));
					}
				}
			}
		}

		//Final transplant needs to evaluated for cycles only
		if (chain == false){
			maxPossibleScore += scoreMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())];
			maxPossible5yearSurvival += survival5yearMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())];
			maxPossible10yearSurvival += survival10yearMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())];

			simLog << getPairID(*(allEC[*it].end() - 1)) << "-->" << getPairID(*(allEC[*it].begin())) << endl;

			//Output
			vector<double> edge_row; edge_row.push_back(MR_CurrentNo); edge_row.push_back(*it);
			//edge_row.push_back(0);
			edge_row.push_back(getPairID(*(allEC[*it].end() - 1)));
			edge_row.push_back(getPairID(*(allEC[*it].begin())));
			edge_row.push_back(pairVector[*(allEC[*it].begin())]->donorType);
			edge_row.push_back(pairVector[*(allEC[*it].end() - 1)]->donorType);
			edge_row.push_back(labCrossmatchMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())]);
			edge_row.push_back(pairVector[*(allEC[*it].end() - 1)]->pairAvailabilityVector[month]);
			edge_row.push_back(pairVector[*(allEC[*it].begin())]->pairAvailabilityVector[month]);
			edge_row.push_back(probabilityMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())]);
			edge_row.push_back(pairVector[*(allEC[*it].end() - 1)]->uncertainty);
			edge_row.push_back(pairVector[*(allEC[*it].begin())]->uncertainty);
			edge_row.push_back(scoreMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())]);
			edge_row.push_back(survival5yearMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())]);
			edge_row.push_back(survival10yearMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())]);
			Record_Edge_Level.push_back(edge_row);
			///////////////////////////////////////////////////////////////////////////////////////////

			//Update successful final transplant
			if (labCrossmatchMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())] == 1){
				simLog << "Positive Lab Crossmatch for " << getPairID(*(allEC[*it].end() - 1)) << "-->" << getPairID(*(allEC[*it].begin())) << "; Probability Updated to 1" << endl;
				probabilityMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())] = 1.0;
			}

			//Simulate failures
			if (labCrossmatchMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())] == 0 || pairVector[*(allEC[*it].end() - 1)]->pairAvailabilityVector[month] != 1 || pairVector[*(allEC[*it].begin())]->pairAvailabilityVector[month] != 1){
				if (pairVector[*(allEC[*it].end() - 1)]->pairAvailabilityVector[month] == 0){
					//finishedVertices.insert(getPairID(*( allEC[*it].end()-1 ) ) );
					simLog << "Pair " << getPairID(*(allEC[*it].end() - 1)) << " Unavailable For This Match Run, ";
				}
				else if (pairVector[*(allEC[*it].end() - 1)]->pairAvailabilityVector[month] == -1){
					finishedVertices.insert(getPairID(*(allEC[*it].end() - 1)));
					simLog << "Pair " << getPairID(*(allEC[*it].end() - 1)) << " Unavailable Permanently, ";
				}
				if (labCrossmatchMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())] == 1){
					probabilityMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())] = 1.0;
				}
				if (labCrossmatchMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())] == 0){
					removeEdgeByPoolID(*(allEC[*it].end() - 1), *(allEC[*it].begin()));
				}
				simLog << "Transplant Failed" << endl;
				failure = true;
			}
		}

		//Calculates statistics related to claimed transplants
		double claimedscore = 0;
		double claimedsurvival5year = 0;
		double claimedsurvival10year = 0;
		int numberTransplantsChain = 0;
		int numberTransplantsCycle = 0;
		int numberTransplantsImplicit = 0;
		bool includeExchange = false;

		//Realized Chain
		if (chain == true && lengthOfChain>0){
			//Complete Chain
			if (lengthOfChain == allEC[*it].size() - 1){
				simLog << "Complete Chain";
				//stats->addCompleteChain();
			}
			//Interrupted Chain
			else {
				simLog << "Interrupted Chain";
				//stats->addFallbackChain();
			}
			simLog << " of Length " << lengthOfChain << endl;
			//stats->addChainLength(lengthOfChain);

			//Collect Info on Realized Chain
			int bridgeDonor = *(allEC[*it].begin());
			for (typename vector<int >::iterator it2 = allEC[*it].begin(); it2 != allEC[*it].end() - 1; ++it2){
				if (numberTransplantsChain<lengthOfChain){
					numberTransplantsChain++;										//Iterate through realized transplants
					claimedscore += scoreMatrix[*it2][*(it2 + 1)];
					claimedsurvival5year += survival5yearMatrix[*it2][*(it2 + 1)];
					claimedsurvival10year += survival10yearMatrix[*it2][*(it2 + 1)];
					finishedVertices.insert(getPairID(*it2));						//Remove transplanted pairs
					getTransplantStats(*it2, *(it2 + 1));
					bridgeDonor = *(it2 + 1);										//Save bridge donor for reference
				}
			}
			if (includeBridgeDonors == true){
				//Update to bridge donor
				if (stbdReneged == false){
					simLog << getPairID(bridgeDonor) << " Now A Bridge Donor" << endl;
					pairVector[bridgeDonor]->donorType = 2;
				}
			}
			else {
				//Add implicit transplant to deceased donor pool; remove pair
				finishedVertices.insert(getPairID(bridgeDonor));
				if (stbdReneged == false){
					numberTransplantsImplicit++;
				}
			}
			includeExchange = true;
		}

		//Realized Cycle
		else if (failure == false){
			if (allEC[*it].size() == 2){
				simLog << "Complete Cycle of Size 2" << endl;
				//stats->addTwoWayExchange();
			}
			else if (allEC[*it].size() == 3){
				simLog << "Complete Cycle of Size 3" << endl;
				//stats->addThreeWayExchange();
			}

			//Get information from realized cycle
			for (typename vector<int >::iterator it2 = allEC[*it].begin(); it2 != allEC[*it].end() - 1; ++it2){
				claimedscore += scoreMatrix[*it2][*(it2 + 1)];
				claimedsurvival5year += survival5yearMatrix[*it2][*(it2 + 1)];
				claimedsurvival10year += survival10yearMatrix[*it2][*(it2 + 1)];
				numberTransplantsCycle++;
				getTransplantStats(*it2, *(it2 + 1));
				finishedVertices.insert(getPairID(*it2));
			}
			claimedscore += scoreMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())];
			claimedsurvival5year += survival5yearMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())];
			claimedsurvival10year += survival10yearMatrix[*(allEC[*it].end() - 1)][*(allEC[*it].begin())];
			numberTransplantsCycle++;
			getTransplantStats(*(allEC[*it].end() - 1), *(allEC[*it].begin()));
			//stats->addCompleteCycle();
			finishedVertices.insert(getPairID(*(allEC[*it].end() - 1)));

			includeExchange = true;
		}

		else {
			includeExchange = false;
			simLog << "Failed ";
			if (chain == true){ simLog << "Chain" << endl; }
			else { simLog << "Cycle" << endl; }
		}

		//Update statistics
		int maxsize = (int)allEC[*it].size();
		//if (includeBridgeDonors==true && chain==true){
		if (chain == true){
			maxsize--;
		}

		simLog << endl;

		//stats->addNumTransplantsChain(numberTransplantsChain);
		//stats->addNumTransplantsCycle(numberTransplantsCycle);
		//stats->addNumTransplantsImplicit(numberTransplantsImplicit);

		//stats->addTotalScore(claimedscore);
		//stats->addTotal5yearSurvival(claimedsurvival5year);
		//stats->addTotal10yearSurvival(claimedsurvival10year);

		//stats->addMaxPossibleTransplants(maxsize);
		//stats->addMaxPossibleScore(maxPossibleScore);
		//stats->addMaxPossible5yearSurvival(maxPossible5yearSurvival);
		//stats->addMaxPossible10yearSurvival(maxPossible10yearSurvival);

		//stats->addExpectedTransplants(cycleExpTransplants);
		//stats->addExpectedUtility(cycleExpUtility);
		//////////////////////////////////////////////////

		//Output
		vector<double> exchange_row;
		if (includeExchange == true){
			exchange_row.push_back(MR_CurrentNo);			// Match Run
			exchange_row.push_back(*it);					// Cycle#
			if (chain == true){ exchange_row.push_back(1); }	// Cycle=0 Chain=1
			else { exchange_row.push_back(0); }
			int totalTransplants = numberTransplantsCycle + numberTransplantsChain + numberTransplantsImplicit;
			exchange_row.push_back(totalTransplants);		// Total Transplants
			exchange_row.push_back(claimedscore);			// Total Score
			exchange_row.push_back(claimedsurvival5year);	// Total 5 Year Survival
			exchange_row.push_back(claimedsurvival10year);	// Total 10 Year Survival

			//Output chain transplant IDs
			if (chain == true && numberTransplantsChain>0){
				int out = 0;
				exchange_row.push_back(getPairID(*(allEC[*it].begin())));
				for (typename vector<int>::iterator ito = allEC[*it].begin() + 1; ito != allEC[*it].end(); ++ito) {
					if (out<totalTransplants){
						out++;
						exchange_row.push_back(getPairID(*ito));
					}
				}
			}

			Record_Exchange_Level.push_back(exchange_row);
		}
	}
	simLog << endl;

	//Remove successful pairs and failed vertices
	for (typename set<int>::iterator it = finishedVertices.begin(); it != finishedVertices.end(); ++it){
		removeVertex(*it);
	}

	//Include implict donations from remaining bridge donors at the final month
	if (last_month == true){
		for (int i = 0; i<pairVector.size(); i++){
			if (pairVector[i]->donorType == 1){
				simLog << "Altruistic Donor " << getPairID(i) << " remains at final match run; Implicit Donation Recorded" << endl;
				//stats->addNumTransplantsImplicit(1);
			}
			if (pairVector[i]->donorType == 2){
				simLog << "Bridge Donor " << getPairID(i) << " remains at final match run; Implicit Donation Recorded" << endl;
				//stats->addNumTransplantsImplicit(1);
			}
		}
	}
}

template <typename VertexType>
void Graph<VertexType>::simulation_fallbacks(int month) {

	MR_CurrentNo++;
	simLog << "Match Run " << MR_CurrentNo << endl;

	if (outputCycleInfo == true){
		outputCycles();
	}

	if (SelectedStructures.size() == 0){
		simLog << "No cycles found" << endl;
		return;
	}

	set<int> finishedVertices;

	for (typename vector<int>::iterator it = SelectedStructures.begin(); it != SelectedStructures.end(); ++it){
		//Initialize SubMatrices
		int nV = (int)allEC[*it].size();
		vector<vector<bool> > subIncidenceOriginalMatrix(nV + 1, vector<bool>(nV + 1, false));
		vector<vector<double> > subViableTransplantOriginalMatrix(nV + 1, vector<double>(nV + 1, 0));
		vector<vector<double> > sub5yearSurvivalOriginalMatrix(nV + 1, vector<double>(nV + 1, 0));
		vector<vector<double> > sub10yearSurvivalOriginalMatrix(nV + 1, vector<double>(nV + 1, 0));
		vector<vector<double> > subScoreOriginalMatrix(nV + 1, vector<double>(nV + 1, 0));
		vector<vector<double> > subProbabilityOriginalMatrix(nV + 1, vector<double>(nV + 1, 0));

		vector<vector<bool> > subIncidenceMatrix(nV + 1, vector<bool>(nV + 1, false));
		vector<vector<double> > subUtilityMatrix(nV + 1, vector<double>(nV + 1, 0));
		vector<double> subProbVertexVector(nV + 1, 0.0);
		vector<int> subStatusVector(nV + 1, 0);

		vector<int> longestVec;
		vector<int> indexToPoolIDVec(nV + 1, 0);
		///////////////////////////////////////////////////////////////////////

		// Determines whether pairs proceed; Counts cycles and chains
		//bool flag=false;
		//for(typename vector<int >::iterator itTSV  = allEC[*it].begin(); itTSV != allEC[*it].end(); ++itTSV){
		//	if (pairVector[*itTSV]->donorType!=0){
		//		//stats->addChain();
		//		flag=true;
		//	}
		//}

		//if (flag==false){
		//	//stats->addCycle();
		//}
		///////////////////////////////////////////////////////////////////

		//Build Submatrices
		int i = 1, j = 1;
		set<int> failedVertices;

		for (typename vector<int>::iterator it2 = allEC[*it].begin(); it2 != allEC[*it].end(); ++it2){
			for (typename vector<int>::iterator it3 = allEC[*it].begin(); it3 != allEC[*it].end(); ++it3){
				subIncidenceOriginalMatrix[i][j] = incidenceMatrix[*it2][*it3];
				subViableTransplantOriginalMatrix[i][j] = viableTransplantMatrix[*it2][*it3];
				sub5yearSurvivalOriginalMatrix[i][j] = survival5yearMatrix[*it2][*it3];
				sub10yearSurvivalOriginalMatrix[i][j] = survival10yearMatrix[*it2][*it3];
				subScoreOriginalMatrix[i][j] = scoreMatrix[*it2][*it3];
				subProbabilityOriginalMatrix[i][j] = probabilityMatrix[*it2][*it3];

				if (incidenceMatrix[*it2][*it3] == 1) {
					//Output
					vector<double> edge_row; edge_row.push_back(MR_CurrentNo); edge_row.push_back(*it);
					edge_row.push_back(getPairID(*it2)); edge_row.push_back(getPairID(*it3));
					edge_row.push_back(pairVector[*it2]->donorType);
					edge_row.push_back(pairVector[*it3]->donorType);
					edge_row.push_back(labCrossmatchMatrix[*it2][*it3]);
					edge_row.push_back(pairVector[*it2]->pairAvailabilityVector[month]);
					edge_row.push_back(pairVector[*it3]->pairAvailabilityVector[month]);

					edge_row.push_back(probabilityMatrix[*it2][*it3]);
					edge_row.push_back(pairVector[*it2]->uncertainty);
					edge_row.push_back(pairVector[*it3]->uncertainty);

					edge_row.push_back(scoreMatrix[*it2][*it3]);
					edge_row.push_back(survival5yearMatrix[*it2][*it3]);
					edge_row.push_back(survival10yearMatrix[*it2][*it3]);
					Record_Edge_Level.push_back(edge_row);
					////////////////////////////////////////////////////////////////

					if (labCrossmatchMatrix[*it2][*it3] == 0 || pairVector[*it2]->pairAvailabilityVector[month] != 1 || pairVector[*it3]->pairAvailabilityVector[month] != 1){
						if (pairVector[*it2]->pairAvailabilityVector[month] == 0){
							//finishedVertices.insert(getPairID(*it2));
							failedVertices.insert(i);
							simLog << "Pair " << getPairID(*it2) << " Unavailable For This Match Run, ";
						}
						else if (pairVector[*it2]->pairAvailabilityVector[month] == -1){
							finishedVertices.insert(getPairID(*it2));
							failedVertices.insert(i);
							simLog << "Pair " << getPairID(*it2) << " Unavailable Permanently, ";
						}
						if (pairVector[*(it3)]->pairAvailabilityVector[month] == 0){
							//finishedVertices.insert(getPairID(*(it3)));
							failedVertices.insert(j);
							simLog << "Pair " << getPairID(*(it3)) << " Unavailable For This Match Run, ";
						}
						else if (pairVector[*(it3)]->pairAvailabilityVector[month] == -1){
							finishedVertices.insert(getPairID(*(it3)));
							failedVertices.insert(j);
							simLog << "Pair " << getPairID(*(it3)) << " Unavailable Permanently, ";
						}
						if (labCrossmatchMatrix[*it2][*it3] == 0){
							removeEdgeByPoolID(*it2, *it3);
						}
						simLog << "Transplant Failed" << endl;
					}

					if (labCrossmatchMatrix[*it2][*it3] == 1){
						probabilityMatrix[*it2][*it3] = 1.0;
					}
				}

				if (i != j){
					subIncidenceMatrix[i][j] = incidenceMatrix[*it2][*it3];
					if (utilityScheme.compare("TRANSPLANTS") == 0){
						subUtilityMatrix[i][j] = viableTransplantMatrix[*it2][*it3];
					}
					else if (utilityScheme.compare("SURVIVAL5YEAR") == 0){
						subUtilityMatrix[i][j] = survival5yearMatrix[*it2][*it3];
					}
					else if (utilityScheme.compare("SURVIVAL10YEAR") == 0){
						subUtilityMatrix[i][j] = survival10yearMatrix[*it2][*it3];
					}
					else {
						subUtilityMatrix[i][j] = scoreMatrix[*it2][*it3];
					}
				}
				j++;
			}
			j = 1;
			subIncidenceMatrix[i][i] = false;
			subUtilityMatrix[i][i] = 0.0;
			subProbVertexVector[i] = pairVector[*it2]->uncertainty;
			subStatusVector[i] = pairVector[*it2]->donorType;
			indexToPoolIDVec[i] = (*it2);
			i++;
		}

		for (set<int>::iterator itSet = failedVertices.begin(); itSet != failedVertices.end(); ++itSet){
			for (i = 1; i <= nV; i++){
				subIncidenceMatrix[i][*itSet] = false;
				subIncidenceMatrix[*itSet][i] = false;
				subUtilityMatrix[i][*itSet] = 0.0;
				subUtilityMatrix[*itSet][i] = 0.0;
			}
		}


		// Get fallback options

		//getLongestCycle(nV, longestVec,subIncidenceOriginalMatrix);

		//double cycleScore;
		//double cycle5yearSurvival;
		//double cycle10yearSurvival;

		//int maxsize = (int) longestVec.size();

		//Queue up AD in longest vector
		//bool longchain = false;
		//for (int q=0; q<longestVec.size(); q++){
		//	if (longchain==false){
		//		int queue = *(longestVec.begin() );
		//		longestVec.erase(longestVec.begin() );
		//		longestVec.push_back(queue);

		//		if (pairVector[indexToPoolIDVec[*(longestVec.begin() )]]->donorType != 0){
		//			longchain=true;
		//		}
		//	}
		//}
		///////////////////////////////////////

		//Calculate Expecations
		//double cycleExpTransplants = calculateExpectationFB(longchain, longestVec, subViableTransplantOriginalMatrix, subProbabilityOriginalMatrix, subProbVertexVector);
		//double cycleExpUtility;
		//if (utilityScheme.compare("TRANSPLANTS")==0){
		//	cycleExpUtility = cycleExpTransplants;
		//}
		//else if (utilityScheme.compare("SURVIVAL5YEAR")==0){
		//	cycleExpUtility = calculateExpectationFB(longchain, longestVec, sub5yearSurvivalOriginalMatrix, subProbabilityOriginalMatrix, subProbVertexVector);
		//}
		//else if (utilityScheme.compare("SURVIVAL10YEAR")==0){
		//cycleExpUtility = calculateExpectationFB(longchain, longestVec, sub10yearSurvivalOriginalMatrix, subProbabilityOriginalMatrix, subProbVertexVector);
		//}
		//else {
		//cycleExpUtility = calculateExpectationFB(longchain, longestVec, subScoreOriginalMatrix, subProbabilityOriginalMatrix, subProbVertexVector);
		//}		
		///////////////////////////////////////////

		//int expectationSuccess=0;
		/*if (utilityScheme.compare("TRANSPLANTS")==0){
		expectationSuccess = getIdealMEUCinFB;
		}
		else if (utilityScheme.compare("SURVIVAL5YEAR")==0){
		expectationSuccess = getIdealMEUCinFB;
		}
		else if (utilityScheme.compare("SURVIVAL10YEAR")==0){
		expectationSuccess = getIdealMEUCinFB;
		}
		else {
		expectationSuccess = =getIdealMEUCinFB;
		}

		maxPossibleTransplants=getMUCInFB(nV, subIncidenceOriginalMatrix,subViableTransplantOriginalMatrix,subStatusVector);

		//stats->addMaxPossibleTransplants(maxPossibleTransplants);
		//stats->addMaxPossibleScore(maxPossibleScore);
		//stats->addMaxPossible5yearSurvival(maxPossible5yearSurvival);
		//stats->addMaxPossible10yearSurvival(maxPossible10yearSurvival);
		//stats->addExpectedTransplants(expTransplants);
		//stats->addExpectedUtility(expUtility); */

		int optimizationSuccess = getMUCInFB(nV, subIncidenceMatrix, subUtilityMatrix, subStatusVector, indexToPoolIDVec);

		if (optimizationSuccess == 1){
			/*if (FB.size()==1){
			if (longestVec.size() == allFB[*(FB.begin() )].size()){
			if (longchain==true){
			//stats->addCompleteChain();
			}
			else {
			//stats->addCompleteCycle();
			}
			}
			else {
			if (longchain==true){
			//stats->addFallbackChain();
			}
			else {
			//stats->addFallbackCycle();
			}
			}
			}
			else {
			int fbSize = (int) FB.size();
			if (longchain==true){
			//stats->addFallbackChain();
			//stats->addFallbackCycles(fbSize-1);
			}
			else {
			//stats->addFallbackCycles(fbSize);
			}
			}*/

			for (typename vector<int>::iterator itFB = FB.begin(); itFB != FB.end(); ++itFB){
				double claimedScore = 0;
				double claimed5yearSurvival = 0;
				double claimed10yearSurvival = 0;
				int numberTransplantsChain = 0;
				int numberTransplantsCycle = 0;
				int numberTransplantsImplicit = 0;

				//Queues up the AD/Bridge donor to the front of the vector
				bool chain = false;

				for (int q = 0; q<allFB[*itFB].size(); q++){
					if (chain == false){
						int queue = *(allFB[*itFB].begin());
						allFB[*itFB].erase(allFB[*itFB].begin());
						allFB[*itFB].push_back(queue);

						if (subStatusVector[*(allFB[*itFB].begin())] != 0){
							chain = true;
						}
					}
				}
				/////////////////////////////////////////////////////////		

				vector<double> exchange_row; exchange_row.push_back(MR_CurrentNo); exchange_row.push_back(*it);

				//Chain
				if (chain == true){
					int chainlength = 0;
					exchange_row.push_back(1);
					if (allFB[*itFB].size()>0) {
						claimedScore = 0;
						claimed5yearSurvival = 0;
						claimed10yearSurvival = 0;
						bool proceed = true;
						vector<int> verticesToRemove;
						int bridgeDonor = indexToPoolIDVec[*(allFB[*itFB].begin())];
						for (typename vector<int>::iterator itbmv = allFB[*itFB].begin(); itbmv != allFB[*itFB].end() - 1; ++itbmv){
							if (proceed == true){
								claimedScore += scoreMatrix[indexToPoolIDVec[*itbmv]][indexToPoolIDVec[*(itbmv + 1)]];
								claimed5yearSurvival += survival5yearMatrix[indexToPoolIDVec[*itbmv]][indexToPoolIDVec[*(itbmv + 1)]];
								claimed10yearSurvival += survival10yearMatrix[indexToPoolIDVec[*itbmv]][indexToPoolIDVec[*(itbmv + 1)]];

								chainlength++;
								numberTransplantsChain++;
								getTransplantStats(indexToPoolIDVec[(*itbmv)], indexToPoolIDVec[*(itbmv + 1)]);
								bridgeDonor = indexToPoolIDVec[*(itbmv + 1)];
								verticesToRemove.push_back(getPairID(indexToPoolIDVec[*itbmv]));

								if ((allFB[*itFB].size() == 5 && numberTransplantsChain == 2) || (allFB[*itFB].size()>5 && numberTransplantsChain == 3)){
									//double u = rng.runif();
									if (pairVector[bridgeDonor]->pairSTBDRenegeVector[month] == 1){
										//if (u < short_renege_rate){
										proceed = false;
										//if (allEC[*it].size() == allFB[*itFB].size()){
										//	//stats->removeCompleteChain();
										//	//stats->addFallbackCycle();
										//}
										verticesToRemove.push_back(getPairID(indexToPoolIDVec[*(itbmv + 1)]));
									}
								}
							}
						}

						for (typename vector<int>::iterator itVTR = verticesToRemove.begin(); itVTR != verticesToRemove.end(); ++itVTR){
							finishedVertices.insert(*itVTR);
						}

						if (includeBridgeDonors == true) {
							pairVector[bridgeDonor]->donorType = 2;
						}
						else {
							finishedVertices.insert(getPairID(bridgeDonor));
							if (proceed == true){
								numberTransplantsImplicit++;
							}
						}
						//exchange_row.push_back(1);
					}

					//else {
					//exchange_row.push_back(0);
					//}

					//stats->addChainLength(chainlength);
				}
				else {
					exchange_row.push_back(0);
					if (allFB[*itFB].size()>0){
						for (typename vector<int>::iterator itbmv = allFB[*itFB].begin(); itbmv != allFB[*itFB].end() - 1; ++itbmv) {
							finishedVertices.insert(getPairID(indexToPoolIDVec[*itbmv]));
							numberTransplantsCycle++;
							getTransplantStats(indexToPoolIDVec[*itbmv], indexToPoolIDVec[*(itbmv + 1)]);
							claimedScore += scoreMatrix[indexToPoolIDVec[*itbmv]][indexToPoolIDVec[*(itbmv + 1)]];
							claimed5yearSurvival += survival5yearMatrix[indexToPoolIDVec[*itbmv]][indexToPoolIDVec[*(itbmv + 1)]];
							claimed10yearSurvival += survival10yearMatrix[indexToPoolIDVec[*itbmv]][indexToPoolIDVec[*(itbmv + 1)]];
						}
						numberTransplantsCycle++;
						getTransplantStats(indexToPoolIDVec[*(allFB[*itFB].end() - 1)], indexToPoolIDVec[*(allFB[*itFB].begin())]);
						finishedVertices.insert(getPairID(indexToPoolIDVec[*(allFB[*itFB].end() - 1)]));
						claimedScore += scoreMatrix[indexToPoolIDVec[*(allFB[*itFB].end() - 1)]][indexToPoolIDVec[*(allFB[*itFB].begin())]];
						claimed5yearSurvival += survival5yearMatrix[indexToPoolIDVec[*(allFB[*itFB].end() - 1)]][indexToPoolIDVec[*(allFB[*itFB].begin())]];
						claimed10yearSurvival += survival10yearMatrix[indexToPoolIDVec[*(allFB[*itFB].end() - 1)]][indexToPoolIDVec[*(allFB[*itFB].begin())]];

						//exchange_row.push_back (1);
					}

					if (allFB[*itFB].size() == 2){
						//stats->addTwoWayExchange();
					}
					else if (allFB[*itFB].size() == 3){
						//stats->addThreeWayExchange();
					}


					//else {
					//exchange_row.push_back (0);
					//}
				}

				//stats->addNumTransplantsChain(numberTransplantsChain);
				//stats->addNumTransplantsCycle(numberTransplantsCycle);
				//stats->addNumTransplantsImplicit(numberTransplantsImplicit);
				//stats->addTotalScore(claimedScore);
				//stats->addTotal5yearSurvival(claimed5yearSurvival);
				//stats->addTotal10yearSurvival(claimed10yearSurvival);

				int totalTransplants = numberTransplantsCycle + numberTransplantsChain + numberTransplantsImplicit;
				exchange_row.push_back(totalTransplants);

				exchange_row.push_back(claimedScore);
				exchange_row.push_back(claimed5yearSurvival);
				exchange_row.push_back(claimed10yearSurvival);

				for (typename vector<int>::iterator ito = allFB[*itFB].begin(); ito != allFB[*itFB].end(); ++ito) {
					exchange_row.push_back(getPairID(indexToPoolIDVec[*ito]));
				}

				Record_Exchange_Level.push_back(exchange_row);
			}
		}
		else {
			vector<double> exchange_row; exchange_row.push_back(MR_CurrentNo); exchange_row.push_back(*it);
			//for (int i=1; i<=8; i++){
			for (int i = 1; i <= 7; i++){
				exchange_row.push_back(0);
			}
		}
	}

	//Remove successful pairs;
	for (typename set<int>::iterator it = finishedVertices.begin(); it != finishedVertices.end(); ++it){
		removeVertex(*it);
	}

	if (includeBridgeDonors == true && last_month == true){
		for (int i = 0; i<pairVector.size(); i++){
			if (pairVector[i]->donorType>0){
				//stats->addNumTransplantsImplicit(1);
			}
		}
	}
}

//Remove pairs due to attrition
template <typename VertexType>
void Graph<VertexType>::attrition(int month) {
	vector<int> verticesToRemove;
	for (typename map<int, VertexType* >::iterator it = pairIDMap.begin(); it != pairIDMap.end(); ++it) {
		//double u = rng.runif();
		if (pairVector[getPoolID(it->first)]->donorType == 0){
			//if(u < att_rate){
			if (pairVector[getPoolID(it->first)]->pairAttritionVector[month] == 1){
				verticesToRemove.push_back(it->first);
				simLog << it->first << " removed from the pool due to attrition" << endl;
			}
		}
		else {//if (pairVector[getPoolID(it->first)]->donorType==2){
			//if(u < renege_rate){
			if (pairVector[getPoolID(it->first)]->pairRenegeVector[month] == 1){
				verticesToRemove.push_back(it->first);
				simLog << it->first << " reneged as bridge donor" << endl;
			}
		}
	}

	simLog << endl;

	for (typename vector<int>::iterator it = verticesToRemove.begin(); it != verticesToRemove.end(); ++it){
		removeVertex(*it);
	}
}

template <typename VertexType>
string Graph<VertexType>::intToString(int number){
	stringstream ss;	//Create a stringstream
	ss << number;		//Add number to the stream
	return ss.str();	//Return a string with the contents of the stream
}

template <typename VertexType>
string Graph<VertexType>::getSimLog(){
	return simLog.str();
}

#endif
