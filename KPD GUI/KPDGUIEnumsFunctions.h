#ifndef ENUMSFUNCTIONS_H
#define ENUMSFUNCTIONS_H

#include <qstring.h>
#include <qvector.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qdebug.h>

#include <string>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>

// Numerical Constants
const qreal PI = 3.14159265;
const qreal TOL = 3;
const qreal STATUS_TIME = 3000;

const int MINIMUM_SLIDER_POSITION = -6;
const int MAXIMUM_SLIDER_POSITION = 6;

const double DEFAULT_OPACITY = 0.15;
const QColor DEFAULT_CAUTION_COLOR = QColor(255, 165, 0);
//const QColor DEFAULT_CAUTION_COLOR = Qt::black;
const double DEFAULT_CLUSTER_SPREAD = 25;

// String Constants
const QString HLA_LIST = "A1,A2,A3,A9,A10,A11,A19,A23,A24,A25,A26,A28,A29,A30,A31,A32,A33,A34,A36,A43,A66,A68,A69,A74,A80,A203,A210,A2403,A6601,A6602,B5,B7,B8,B12,B13,B14,B15,B16,B17,B18,B21,B22,B27,B35,B37,B38,B39,B40,B41,B42,B44,B45,B46,B47,B48,B49,B50,B51,B52,B53,B54,B55,B56,B57,B58,B59,B60,B61,B62,B63,B64,B65,B67,B70,B71,B72,B73,B75,B76,B77,B78,B81,B82,B703,B804,B1304,B2708,B3901,B3902,B3905,B4005,B5102,B5103,B8201,BW4,BW6,CW1,CW2,CW3,CW4,CW5,CW6,CW7,CW8,CW9,CW10,CW12,CW13,CW14,CW15,CW16,CW17,CW18,DQ1,DQ2,DQ3,DQ4,DQ5,DQ6,DQ7,DQ8,DQ9,DQB1,DQB2,DQB3,DQB4,DQB5,DQB6,DQB7,DQB8,DQB9,DR1,DR2,DR3,DR4,DR5,DR6,DR7,DR8,DR9,DR10,DR11,DR12,DR13,DR14,DR15,DR16,DR17,DR18,DR103,DR1403,DR1404,DR51,DR52,DR53";

// Random Number Generators
const int RAND_A = 16807;
const int RAND_M = 2147483647;
const int RAND_Q = 127773;
const int RAND_R = 2836;
const double RAND_SCALE = (1.0 / RAND_M);

// Simulation Specifications
enum KPDOptimizationScheme { CYCLES_AND_CHAINS, CYCLES_AND_CHAINS_WITH_FALLBACKS, LOCALLY_RELEVANT_SUBSETS };
enum KPDUtilityScheme { TRANSPLANTS, FIVE_YEAR_SURVIVAL, TEN_YEAR_SURVIVAL, HARD_TO_TRANSPLANT, ASSIGNED_SCORE };

// Characteristics
enum KPDBloodType { BT_O, BT_A, BT_B, BT_AB };
enum KPDRace { RACE_WHITE, RACE_BLACK, RACE_HISPANIC, RACE_OTHER };
enum KPDInsurance { PUBLIC, PRIVATE, OTHER_INSURANCE };

// Node Properties
enum KPDNodeType { PAIR, NDD };

// Match Properties
enum KPDCrossmatchResult { SUCCESSFUL_CROSSMATCH, O_DONOR_TO_NON_O_CANDIDATE, FAILED_CROSSMATCH_ADDITIONAL_HLA, FAILED_CROSSMATCH_ADDITIONAL_HLA_AND_O_TO_NON_O, FAILED_CROSSMATCH_HLA, FAILED_CROSSMATCH_BT };

// GUI Display
enum KPDDashboardMode { NODE, MATCH, DONOR, CANDIDATE};
enum KPDNodeDisplayMode { SEPARATE_DONOR_CANDIDATE, COMBINE_DONOR_CANDIDATE };
enum KPDMatchDisplayMode { WITHIN_SELECTION, SELECTED_COMPATIBILITIES, ALL_COMPATIBILITIES, NO_COMPATIBILITIES };
enum KPDNodeSortMode { NODESORT_ID, NODESORT_POPULARITY_SOLUTIONS, NODESORT_POPULARITY_ARRANGEMENTS, NODESORT_COMPATIBILITIES, NODESORT_COMPATIBLE_DONORS, NODESORT_COMPATIBLE_RECIPIENTS, NODESORT_PRA };
enum KPDMatchSortMode { MATCHSORT_POPULARITY_SOLUTIONS, MATCHSORT_POPULARITY_ARRANGEMENTS, MATCHSORT_DONORID, MATCHSORT_RECIPID };

namespace KPDFunctions {

	//Optimization Scheme
	inline KPDOptimizationScheme intToOptScheme(int i){

		KPDOptimizationScheme scheme = CYCLES_AND_CHAINS;

		if (i == 1){ scheme = CYCLES_AND_CHAINS_WITH_FALLBACKS;	}
		else if (i == 2){ scheme = LOCALLY_RELEVANT_SUBSETS; }

		return scheme;
	}

	inline int optSchemeToInt(KPDOptimizationScheme scheme){
		
		int i = 0;
		
		if (scheme == CYCLES_AND_CHAINS_WITH_FALLBACKS){ i = 1; }
		else if (scheme == LOCALLY_RELEVANT_SUBSETS){ i = 2; }

		return i;
	}

	inline QString toString(KPDOptimizationScheme scheme){
		if (scheme == CYCLES_AND_CHAINS){ return "Maximum Utility Cycles and Chains"; }
		else if (scheme == CYCLES_AND_CHAINS_WITH_FALLBACKS){ return "Maximum Expected Utility Cycles and Chains (with Fallbacks)"; }
		else if (scheme == LOCALLY_RELEVANT_SUBSETS){ return "Maximum Expected Utility Locally Relevant Subsets"; }
		else { return ""; }
	}

	//Utility Scheme
	inline KPDUtilityScheme intToUtilScheme(int i){

		KPDUtilityScheme scheme = TRANSPLANTS;

		if (i == 1) { scheme = FIVE_YEAR_SURVIVAL; }
		else if (i == 2) { scheme = TEN_YEAR_SURVIVAL; }
		else if (i == 3) { scheme = HARD_TO_TRANSPLANT; }
		else if (i == 4) { scheme = ASSIGNED_SCORE; }

		return scheme;
	}

	inline int utilSchemeToInt(KPDUtilityScheme scheme){
		
		int i = 0;

		if (scheme == FIVE_YEAR_SURVIVAL) { i = 1; }
		else if (scheme == TEN_YEAR_SURVIVAL) { i = 2; }
		else if (scheme == HARD_TO_TRANSPLANT) { i = 3; }
		else if (scheme == ASSIGNED_SCORE) { i = 4; }

		return i;
	}

	inline QString toString(KPDUtilityScheme scheme){
		if (scheme == TRANSPLANTS){ return "Transplants"; }
		else if (scheme == FIVE_YEAR_SURVIVAL){ return "5 Year Survival"; }
		else if (scheme == TEN_YEAR_SURVIVAL){ return "10 Year Survival"; }
		else if (scheme == HARD_TO_TRANSPLANT){ return "Hard-To-Transplant Candidates"; }
		else if (scheme == ASSIGNED_SCORE) { return "User-Assigned Score"; }
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

	inline KPDBloodType stringToBloodType(QString bt) {
		KPDBloodType bloodtype = BT_O;
		if (bt == "A") { bloodtype = BT_A; }
		else if (bt == "B") { bloodtype = BT_B; }
		else if (bt == "AB") { bloodtype = BT_AB; }

		return bloodtype;
	}

	inline int bloodTypeToInt(KPDBloodType type){

		int i = 0;

		if (type == BT_A){ i = 1; }
		else if (type == BT_B){ i = 2; }
		else if (type == BT_AB){ i = 3;	}

		return i;
	}

	inline QString toString(KPDBloodType type){
		if (type == BT_O){ return "O"; }
		else if (type == BT_A){ return "A"; }
		else if (type == BT_B){ return "B"; }
		else if (type == BT_AB){ return "AB"; }
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

	//Insurance
	inline KPDInsurance intToInsurance(int i) {

		KPDInsurance insurance = PUBLIC;

		if (i == 1) { insurance = PRIVATE; }
		else if (i == 2) { insurance = OTHER_INSURANCE; }

		return insurance;
	}

	inline int insuranceToInt(KPDInsurance insurance) {

		int i = 0;

		if (insurance == PRIVATE) { i = 1; }
		else if (insurance == OTHER_INSURANCE) { i = 2; }

		return i;
	}

	inline QString toString(KPDInsurance insurance) {
		if (insurance == PUBLIC) { return "Public Primary Payer"; }
		else if (insurance == PRIVATE) { return "Private Primary Payer"; }
		else if (insurance == OTHER_INSURANCE) { return "Other Payer"; }
		else { return ""; }
	}

	//Node Type
	inline KPDNodeType intToNodeType(int i) {

		KPDNodeType type = PAIR;

		if (i == 1) { type = NDD; }

		return type;
	}

	inline int nodeTypeToInt(KPDNodeType type) {

		int i = 0;

		if (type == NDD) { i = 1; }

		return i;
	}

	inline QString toString(KPDNodeType type) {
		if (type == PAIR) { return "Pair"; }
		else if (type == NDD) { return "NDD"; }
		else { return ""; }
	}

	//Crossmatch Result
	inline KPDCrossmatchResult intToCrossmatchResult(int i) {

		KPDCrossmatchResult result = SUCCESSFUL_CROSSMATCH;

		if (i == 1) { result = O_DONOR_TO_NON_O_CANDIDATE; }
		else if (i == 2) { result = FAILED_CROSSMATCH_ADDITIONAL_HLA; }
		else if (i == 3) { result = FAILED_CROSSMATCH_HLA; }
		else if (i == 4) { result = FAILED_CROSSMATCH_BT; }

		return result;
	}

	inline int crossmatchResultToInt(KPDCrossmatchResult result) {

		int i = 0;

		if (result == O_DONOR_TO_NON_O_CANDIDATE) { i = 1; }
		else if (result == FAILED_CROSSMATCH_ADDITIONAL_HLA) { i = 2; }
		else if (result == FAILED_CROSSMATCH_HLA) { i = 3; }
		else if (result == FAILED_CROSSMATCH_BT) { i = 4; }

		return i;
	}

	inline QString toString(KPDCrossmatchResult result) {
		if (result == SUCCESSFUL_CROSSMATCH) { return "Successful Crossmatch"; }
		else if (result == O_DONOR_TO_NON_O_CANDIDATE) { return "O Donor to Non-O Candidate"; }
		else if (result == FAILED_CROSSMATCH_ADDITIONAL_HLA) { return "Failed Crossmatch (Based on Additional HLA)"; }
		else if (result == FAILED_CROSSMATCH_HLA) { return "Failed Crossmatch (Based on HLA)"; }
		else if (result == FAILED_CROSSMATCH_BT) { return "Failed Crossmatch (Based on BT)"; }
		else { return ""; }
	}


	//Entity
	inline KPDDashboardMode intToEntity(int i) {

		KPDDashboardMode entity = NODE;

		if (i == 1) { entity = MATCH; }
		else if (i == 2) { entity = DONOR; }
		else if (i == 3) { entity = CANDIDATE; }

		return entity;
	}

	inline int entityToInt(KPDDashboardMode entity) {

		int i = 0;

		if (entity == MATCH) { i = 1; }
		else if (entity == DONOR) { i = 2; }
		else if (entity == CANDIDATE) { i = 3; }

		return i;
	}

	inline QString toString(KPDDashboardMode entity) {
		if (entity == NODE) { return "Node"; }
		else if (entity == MATCH) { return "Match"; }
		else if (entity == DONOR) { return "Donor"; }
		else if (entity == CANDIDATE) { return "Candidate"; }
		else { return ""; }
	}


	//Node Display Mode
	inline KPDNodeDisplayMode intToNodeDisplayMode(int i) {

		KPDNodeDisplayMode mode = SEPARATE_DONOR_CANDIDATE;

		if (i == 1) { mode = COMBINE_DONOR_CANDIDATE; }

		return mode;
	}

	inline int nodeDisplayModeToInt(KPDNodeDisplayMode mode) {

		int i = 0;

		if (mode == COMBINE_DONOR_CANDIDATE) { i = 1; }

		return i;
	}

	inline QString toString(KPDNodeDisplayMode mode) {
		if (mode == SEPARATE_DONOR_CANDIDATE) { return "Display Donors and Candidates Separately"; }
		else if (mode == COMBINE_DONOR_CANDIDATE) { return "Display Donors and Candidates as a Single Node"; }
		else { return ""; }
	}

	//Match Display Mode
	inline KPDMatchDisplayMode intToMatchDisplayMode(int i) {

		KPDMatchDisplayMode mode = WITHIN_SELECTION;

		if (i == 1) { mode = SELECTED_COMPATIBILITIES; }
		else if (i == 2) { mode = ALL_COMPATIBILITIES; }
		else if (i == 3) { mode = NO_COMPATIBILITIES; }

		return mode;
	}

	inline int matchDisplayModeToInt(KPDMatchDisplayMode mode) {

		int i = 0;

		if (mode == SELECTED_COMPATIBILITIES) { i = 1; }
		else if (mode == ALL_COMPATIBILITIES) { i = 2; }
		else if (mode == NO_COMPATIBILITIES) { i = 3; }

		return i;
	}

	inline QString toString(KPDMatchDisplayMode mode) {
		if (mode == WITHIN_SELECTION) { return "Within Selection"; }
		else if (mode == SELECTED_COMPATIBILITIES) { return "Selected Compatibilities"; }
		else if (mode == ALL_COMPATIBILITIES) { return "All Compatibilities"; }
		else if (mode == NO_COMPATIBILITIES) { return "No Compatibilities"; }
		else { return ""; }
	}

	//Node Sort Mode
	inline KPDNodeSortMode intToNodeSortMode(int i){

		KPDNodeSortMode mode = NODESORT_ID;

		if (i == 1){ mode = NODESORT_POPULARITY_SOLUTIONS; }
		else if (i == 2){ mode = NODESORT_POPULARITY_ARRANGEMENTS; }
		else if (i == 3){ mode = NODESORT_COMPATIBILITIES; }
		else if (i == 4){ mode = NODESORT_COMPATIBLE_DONORS; }
		else if (i == 5){ mode = NODESORT_COMPATIBLE_RECIPIENTS; }
		else if (i == 6){ mode = NODESORT_PRA; }

		return mode;
	}

	inline int nodeSortModeToInt(KPDNodeSortMode mode){

		int i = 0;

		if (mode == NODESORT_POPULARITY_SOLUTIONS){ i = 1; }
		else if (mode == NODESORT_POPULARITY_ARRANGEMENTS){ i = 2; }
		else if (mode == NODESORT_COMPATIBILITIES){ i = 3; }
		else if (mode == NODESORT_COMPATIBLE_DONORS){ i = 4; }
		else if (mode == NODESORT_COMPATIBLE_RECIPIENTS){ i = 5; }
		else if (mode == NODESORT_PRA){ i = 6; }

		return i;
	}

	inline QString toString(KPDNodeSortMode mode){
		if (mode == NODESORT_ID){ return "ID"; }
		else if (mode == NODESORT_POPULARITY_SOLUTIONS){ return "Popularity in Solutions"; }
		else if (mode == NODESORT_POPULARITY_ARRANGEMENTS){ return "Popularity in Arrangements"; }
		else if (mode == NODESORT_COMPATIBILITIES){ return "Number of Compatibilities"; }
		else if (mode == NODESORT_COMPATIBLE_DONORS){ return "Number of Compatible Donors"; }
		else if (mode == NODESORT_COMPATIBLE_RECIPIENTS){ return "Number of Compatible Recipients"; }
		else if (mode == NODESORT_PRA){ return "Candidate PRA"; }
		else { return ""; }
	}

	//Match Sort Mode
	inline KPDMatchSortMode intToMatchSortMode(int i) {

		KPDMatchSortMode mode = MATCHSORT_POPULARITY_SOLUTIONS;

		if (i == 1) { mode = MATCHSORT_POPULARITY_ARRANGEMENTS; }
		else if (i == 2) { mode = MATCHSORT_DONORID; }
		else if (i == 3) { mode = MATCHSORT_RECIPID; }

		return mode;
	}

	inline int matchSortModeToInt(KPDMatchSortMode mode) {

		int i = 0;

		if (mode == MATCHSORT_POPULARITY_ARRANGEMENTS) { i = 1; }
		else if (mode == MATCHSORT_DONORID) { i = 2; }
		else if (mode == MATCHSORT_RECIPID) { i = 3; }

		return i;
	}

	inline QString toString(KPDMatchSortMode mode) {
		if (mode == MATCHSORT_POPULARITY_SOLUTIONS) { return "Popularity in Solutions"; }
		else if (mode == MATCHSORT_POPULARITY_ARRANGEMENTS) { return "Popularity in Arrangements"; }
		else if (mode == MATCHSORT_DONORID) { return "Donor ID"; }
		else if (mode == MATCHSORT_RECIPID) { return "Candidate ID"; }
		else { return ""; }
	}
	
	// Additional Functions

	inline std::string intToString(int number) {
		std::stringstream ss;	//Create a stringstream
		ss << number;		//Add number to the stream
		return ss.str();	//Return a string with the contents of the stream
	}

	inline QString nodeStatusToString(bool status) {
		if (status) { return "Participating"; }
		else { return "Not Participating";  }
	}

	inline QString donorTypeToString(bool altruistic) {
		if (altruistic) { return "NDD"; }
		else { return "Pair"; }
	}

	inline double getRandomValue(double seed) {

		if (seed == 0) { //Cannot allow seed to be 0;
			seed = 1;
		}

		int k = seed / RAND_Q;
		seed = RAND_A * (seed - k* RAND_Q) - k * RAND_R;
		if (seed < 0) {
			seed += RAND_M;
		}

		return seed * (double)RAND_SCALE;
	}

	inline int setFlags(int value, std::vector<int> &flagVector) {

		//Starts at index 1
		int position = 1;
		int numberOfFlags = 0;
		while (value != 0) {
			int flag = value % 2;
			if (flag == 1) {
				numberOfFlags++;
				flagVector[position] = 1;
			}
			value = value / 2;
			position++;
		}

		return numberOfFlags;
	}

	inline QVector<QVector<QVector<QString> > > loadData(QString fileName, bool fullName) {

		//qDebug() << "Entered";

		QVector<QVector<QVector<QString> > > parsedData;

		QString file;

		if (fullName) {
			file = fileName;
		}
		else {
			file = "data/" + fileName;
		}


		QFile iFile(file);
		if (!iFile.open(QIODevice::ReadOnly)) {
			qDebug() << "Cannot Open File For Reading: " << qPrintable(iFile.errorString());
		}
		QTextStream fileStream(&iFile);

		int i = 0;
		while (!fileStream.atEnd()) {
			QString row = fileStream.readLine();
			QStringList tokens = row.split(',');

			if (i > 0) {
				QVector<QVector<QString> > dataRow;

				foreach(QString token, tokens) {
					QVector<QString> dataField;

					QStringList subTokens = token.split(';');

					foreach(QString subToken, subTokens) {
						dataField.push_back(subToken);
					}

					dataRow.push_back(dataField);
				}
				parsedData.push_back(dataRow);
			}
			i++;
		}

		return parsedData;
	}

}

#endif