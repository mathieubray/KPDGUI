#ifndef ENUMSFUNCTIONS_H
#define ENUMSFUNCTIONS_H

#include <qstring.h>
#include <qvector.h>

const qreal PI = 3.14159265;
const qreal TOL = 3;
const qreal STATUS_TIME = 3000;

const int MINIMUM_SLIDER_POSITION = -4;
const int MAXIMUM_SLIDER_POSITION = 3;

enum KPDOptimizationScheme { MUC, MEUC, MEUS, SCC };
enum KPDUtilityScheme { TRANSPLANTS, SURVIVAL5YEAR, SURVIVAL10YEAR, SCORE };

enum KPDBloodType { BT_O, BT_A, BT_B, BT_AB };
enum KPDRace { RACE_WHITE, RACE_BLACK, RACE_HISPANIC, RACE_OTHER };

enum KPDMatchDisplayMode { WITHIN_SELECTION, SELECTED_COMPATIBILITIES, COMPATIBLE_DONORS, COMPATIBLE_RECIPIENTS, ALL_COMPATIBILITIES, NO_COMPATIBILITIES };
enum KPDNodeSortMode { NODESORT_ID, NODESORT_POPULARITY_SOLUTIONS, NODESORT_POPULARITY_STRUCTURES, NODESORT_COMPATIBILITIES, NODESORT_COMPATIBLE_DONORS, NODESORT_COMPATIBLE_RECIPIENTS, NODESORT_PRA };
enum KPDMatchSortMode { MATCHSORT_POPULARITY_SOLUTIONS, MATCHSORT_POPULARITY_STRUCTURES, MATCHSORT_DONORID, MATCHSORT_RECIPID };

enum KPDChainStorage { AS_FOUND, CHAINS_FIRST, CHAINS_LAST };

enum KPDNodeType { PAIR, AD };

struct AdditionalNodeInfo{
	
	int nodeID;
	KPDNodeType nodeType;

	int numberOfDonors;

	QVector<KPDBloodType> donorBTs;
	QVector<double> donorUncertainty;

	KPDBloodType candidateBT;
	int candidatePRA;	
	double candidateUncertainty;
};


namespace KPDFunctions {

	//Optimization Scheme
	inline KPDOptimizationScheme intToOptScheme(int i){

		KPDOptimizationScheme scheme = MUC;

		if (i == 1){ scheme = MEUC;	}
		else if (i == 2){ scheme = MEUS; }
		else if (i == 3){ scheme = SCC;	}

		return scheme;
	}

	inline int optSchemeToInt(KPDOptimizationScheme scheme){
		
		int i = 0;
		
		if (scheme == MEUC){ i = 1; }
		else if (scheme == MEUS){ i = 2; }
		else if (scheme == SCC){ i = 3;	}

		return i;
	}

	inline QString toString(KPDOptimizationScheme scheme){
		if (scheme == MUC){ return "Utility"; }
		else if (scheme == MEUC){ return "Expected Utility"; }
		else if (scheme == MEUS){ return "Fallbacks"; }
		else if (scheme == SCC){ return "Extended Fallbacks"; }
		else { return ""; }
	}

	//Utility Scheme
	inline KPDUtilityScheme intToUtilScheme(int i){

		KPDUtilityScheme scheme = TRANSPLANTS;

		if (i == 1){ scheme = SURVIVAL5YEAR; }
		else if (i == 2){ scheme = SURVIVAL10YEAR; }
		else if (i == 3){ scheme = SCORE; }

		return scheme;
	}

	inline int utilSchemeToInt(KPDUtilityScheme scheme){
		
		int i = 0;

		if (scheme == SURVIVAL5YEAR){ i = 1; }
		else if (scheme == SURVIVAL10YEAR){ i = 2; }
		else if (scheme == SCORE){ i = 3; }

		return i;
	}

	inline QString toString(KPDUtilityScheme scheme){
		if (scheme == TRANSPLANTS){ return "Transplants"; }
		else if (scheme == SURVIVAL5YEAR){ return "5 Year Survival"; }
		else if (scheme == SURVIVAL10YEAR){ return "10 Year Survival"; }
		else if (scheme == SCORE){ return "Score"; }
		else { return ""; }
	}

	//Blood Type
	inline KPDBloodType intToBloodType(int i){

		KPDBloodType type = BT_O;

		if (i == 1){ type = BT_A; }
		else if (i == 2){ type = BT_B; }
		else if (i == 3){ type = BT_AB;	}

		return type;
	}

	inline int bloodTypeToInt(KPDBloodType type){

		int i = 0;

		if (type == BT_A){ i = 1; }
		else if (type == BT_B){ i = 2; }
		else if (type == BT_AB){ i = 3;	}

		return i;
	}

	inline QString toString(KPDBloodType type){
		if (type == WITHIN_SELECTION){ return "O"; }
		else if (type == SELECTED_COMPATIBILITIES){ return "A"; }
		else if (type == COMPATIBLE_DONORS){ return "B"; }
		else if (type == COMPATIBLE_RECIPIENTS){ return "AB"; }
		else { return ""; }
	}

	//Race
	inline KPDRace intToRace(int i){

		KPDRace race = RACE_WHITE;

		if (i == 1){ race = RACE_BLACK; }
		else if (i == 2){ race = RACE_HISPANIC; }
		else if (i == 3){ race = RACE_OTHER; }

		return race;
	}

	inline int raceToInt(KPDRace race){

		int i = 0;

		if (race == RACE_BLACK){ i = 1; }
		else if (race == RACE_HISPANIC){ i = 2; }
		else if (race == RACE_OTHER){ i = 3; }

		return i;
	}

	inline QString toString(KPDRace race){
		if (race == RACE_WHITE){ return "White"; }
		else if (race == RACE_BLACK){ return "Black"; }
		else if (race == RACE_HISPANIC){ return "Hispanic"; }
		else if (race == RACE_OTHER){ return "Other"; }
		else { return ""; }
	}

	//Match Display Mode
	inline KPDMatchDisplayMode intToMatchDisplayMode(int i) {

		KPDMatchDisplayMode mode = WITHIN_SELECTION;

		if (i == 1) { mode = SELECTED_COMPATIBILITIES; }
		else if (i == 2) { mode = COMPATIBLE_DONORS; }
		else if (i == 3) { mode = COMPATIBLE_RECIPIENTS; }
		else if (i == 4) { mode = ALL_COMPATIBILITIES; }
		else if (i == 5) { mode = NO_COMPATIBILITIES; }

		return mode;
	}

	inline int matchDisplayModeToInt(KPDMatchDisplayMode mode) {

		int i = 0;

		if (mode == SELECTED_COMPATIBILITIES) { i = 1; }
		else if (mode == COMPATIBLE_DONORS) { i = 2; }
		else if (mode == COMPATIBLE_RECIPIENTS) { i = 3; }
		else if (mode == ALL_COMPATIBILITIES) { i = 4; }
		else if (mode == NO_COMPATIBILITIES) { i = 5; }

		return i;
	}

	inline QString toString(KPDMatchDisplayMode mode) {
		if (mode == WITHIN_SELECTION) { return "Within Selection"; }
		else if (mode == SELECTED_COMPATIBILITIES) { return "Selected Compatibilities"; }
		else if (mode == COMPATIBLE_DONORS) { return "Compatible Donors"; }
		else if (mode == COMPATIBLE_RECIPIENTS) { return "Compatible Recipients"; }
		else if (mode == ALL_COMPATIBILITIES) { return "All Compatibilities"; }
		else if (mode == NO_COMPATIBILITIES) { return "No Compatibilities"; }
		else { return ""; }
	}

	//Node Sort Mode
	inline KPDNodeSortMode intToNodeSortMode(int i){

		KPDNodeSortMode mode = NODESORT_ID;

		if (i == 1){ mode = NODESORT_POPULARITY_SOLUTIONS; }
		else if (i == 2){ mode = NODESORT_POPULARITY_STRUCTURES; }
		else if (i == 3){ mode = NODESORT_COMPATIBILITIES; }
		else if (i == 4){ mode = NODESORT_COMPATIBLE_DONORS; }
		else if (i == 5){ mode = NODESORT_COMPATIBLE_RECIPIENTS; }
		else if (i == 6){ mode = NODESORT_PRA; }

		return mode;
	}

	inline int nodeSortModeToInt(KPDNodeSortMode mode){

		int i = 0;

		if (mode == NODESORT_POPULARITY_SOLUTIONS){ i = 1; }
		else if (mode == NODESORT_POPULARITY_STRUCTURES){ i = 2; }
		else if (mode == NODESORT_COMPATIBILITIES){ i = 3; }
		else if (mode == NODESORT_COMPATIBLE_DONORS){ i = 4; }
		else if (mode == NODESORT_COMPATIBLE_RECIPIENTS){ i = 5; }
		else if (mode == NODESORT_PRA){ i = 6; }

		return i;
	}

	inline QString toString(KPDNodeSortMode mode){
		if (mode == NODESORT_ID){ return "ID"; }
		else if (mode == NODESORT_POPULARITY_SOLUTIONS){ return "Popularity in Solutions"; }
		else if (mode == NODESORT_POPULARITY_STRUCTURES){ return "Popularity in Structures"; }
		else if (mode == NODESORT_COMPATIBILITIES){ return "Number of Compatibilities"; }
		else if (mode == NODESORT_COMPATIBLE_DONORS){ return "Number of Compatible Donors"; }
		else if (mode == NODESORT_COMPATIBLE_RECIPIENTS){ return "Number of Compatible Recipients"; }
		else if (mode == NODESORT_PRA){ return "Candidate PRA"; }
		else { return ""; }
	}

	//Match Sort Mode
	inline KPDMatchSortMode intToMatchSortMode(int i) {

		KPDMatchSortMode mode = MATCHSORT_POPULARITY_SOLUTIONS;

		if (i == 1) { mode = MATCHSORT_POPULARITY_STRUCTURES; }
		else if (i == 2) { mode = MATCHSORT_DONORID; }
		else if (i == 3) { mode = MATCHSORT_RECIPID; }

		return mode;
	}

	inline int matchSortModeToInt(KPDMatchSortMode mode) {

		int i = 0;

		if (mode == MATCHSORT_POPULARITY_STRUCTURES) { i = 1; }
		else if (mode == MATCHSORT_DONORID) { i = 2; }
		else if (mode == MATCHSORT_RECIPID) { i = 3; }

		return i;
	}

	inline QString toString(KPDMatchSortMode mode) {
		if (mode == MATCHSORT_POPULARITY_SOLUTIONS) { return "Popularity in Solutions"; }
		else if (mode == MATCHSORT_POPULARITY_STRUCTURES) { return "Popularity in Structures"; }
		else if (mode == MATCHSORT_DONORID) { return "Donor ID"; }
		else if (mode == MATCHSORT_RECIPID) { return "Candidate ID"; }
		else { return ""; }
	}

	//Chain Storage
	inline KPDChainStorage intToChainStorage(int i){

		KPDChainStorage mode = AS_FOUND;

		if (i == 1){ mode = CHAINS_FIRST; }
		else if (i == 2){ mode = CHAINS_LAST; }

		return mode;
	}

	inline int chainStorageToInt(KPDChainStorage mode){

		int i = 0;

		if (mode == CHAINS_FIRST){ i = 1; }
		else if (mode == CHAINS_LAST){ i = 2; }

		return i;
	}

	inline QString toString(KPDChainStorage mode){
		if (mode == AS_FOUND){ return "As They Are Found"; }
		else if (mode == CHAINS_FIRST){ return "First"; }
		else if (mode == CHAINS_LAST){ return "Last"; }
		else { return ""; }
	}

	//Node Type
	inline KPDNodeType intToNodeType(int i) {

		KPDNodeType type = PAIR;

		if (i == 1) { type = AD; }

		return type;
	}

	inline int nodeTypeToInt(KPDNodeType type) {

		int i = 0;

		if (type == AD) { i = 1; }

		return i;
	}

	inline QString toString(KPDNodeType type) {
		if (type == PAIR) { return "Pair"; }
		else if (type == AD) { return "AD"; }
		else { return ""; }
	}

}

#endif