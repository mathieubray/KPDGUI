#ifndef STRUCTS_H
#define STRUCTS_H

#include <qstring.h>
#include <qvector.h>

enum KPDOptimizationScheme { MUC, MEUC, MEUS, SCC };
enum KPDUtilityScheme { TRANSPLANTS, SURVIVAL5YEAR, SURVIVAL10YEAR, SCORE };
enum KPDPairType { PAIR, AD };

enum KPDArrowDisplayMode { WITHIN_SELECTION, SELECTED_COMPATIBILITIES, COMPATIBLE_DONORS, COMPATIBLE_RECIPIENTS, ALL_COMPATIBILITIES, NO_COMPATIBILITIES };

struct Candidate{
	
	//Compatibilities
	QString BT;
	QVector<QString> antibodies;
	int pra;

	//Demographics
	QString name;
	int age;
	bool genderMale;
	QString race;
	bool diabetes;
	double weight;
	double BMI;
	bool prevTrans;
	double TOD;
	bool hepC;
};

struct Donor{
	
	//Compatibilities
	QString BT;
	QVector<QString> donorA;
	QVector<QString> donorB;
	bool donorBW4;
	bool donorBW6;
	QVector<QString> donorCW;
	QVector<QString> donorDP;
	QVector<QString> donorDQ;
	QVector<QString> donorDR;
	bool donorDR51;
	bool donorDR52;
	bool donorDR53;

	//Demographics
	QString name;
	int age;
	bool genderMale;
	double weight;
	double BMI;

	KPDPairType type;
};

struct AdditionalPairInfo{
	int pairID;

	KPDPairType pairType;

	QString donorBT;
	QString recipBT;

	int recipPRA;

	double uncertainty;	
};

struct ParamInfoStruct{
	
	//Simulation Settings
	KPDOptimizationScheme optScheme; //MUC, MEUC, MEUS, SCC
	KPDUtilityScheme utilityScheme; // TRANSPLANTS, SURVIVAL5YEAR, SURVIVAL10YEAR, SCORE
	int maxChainLength;

	//Numerical Parameters
	double pairFailureRate;
	double adFailureRate;
	double exogenousFailureRate;

	bool addAdvantageToHighPRACandidates;
	int praAdvantageCutoff;
	double praAdvantageValue;

	int numberOfSolutions;

	//Additional Options
	QString chainStorage; // FIRST, LAST, NONE
	bool reserveODonorsForOCandidates;
	bool checkDP;
	bool includeCompatiblePairs;
	bool excludeABDonorsFromSimulation;
	bool allowABBridgeDonors;
	
};

struct DisplaySettingsStruct{
	
	bool showAllPairs;
	bool showPairSubset;
	bool showPairsInSolutions;
	bool showPairsInStructures;
	bool showPairsOnHold;
	bool showPairsWithNoCompatibilities;
	bool showPairsOfMinPRA;
	bool showPairsOfMaxPRA;

	int minPRA;
	int maxPRA;

	KPDArrowDisplayMode arrowDisplayMode;
};

namespace KPDFunctions {

	inline KPDArrowDisplayMode intToArrowDisplayMode(int i){
		
		KPDArrowDisplayMode mode = WITHIN_SELECTION;

		if (i == 1){
			
		}
		else if (i == 2){

		}
		else if (i == 3){

		}
		else if (i == 4){

		}
		else if (i == 5){

		}
		
		return mode;

	}

	inline int arrowDisplayModeToInt(KPDArrowDisplayMode mode){
		
		int i = 0;

		if (mode == SELECTED_COMPATIBILITIES){
			
		}
		else if (mode == COMPATIBLE_DONORS){

		}
		else if (mode == COMPATIBLE_RECIPIENTS){

		}
		else if (mode == ALL_COMPATIBILITIES){

		}
		else if (mode == NO_COMPATIBILITIES){

		}

		return i;
	}

	inline KPDOptimizationScheme stringToOptScheme(QString optScheme){
		KPDOptimizationScheme scheme = MUC;
		if (optScheme == "MEUC"){ scheme = MEUC; }
		else if (optScheme == "MEUS"){ scheme = MEUS; }
		else if (optScheme == "SCC"){ scheme = SCC; }

		return scheme;
	}

	inline KPDOptimizationScheme dialogToOptScheme(QString optScheme){
		KPDOptimizationScheme scheme = MUC;
		if (optScheme == "Expected Utility"){ scheme = MEUC; }
		else if (optScheme == "Fallbacks"){ scheme = MEUS; }
		else if (optScheme == "Extended Fallbacks"){ scheme = SCC; }

		return scheme;
	}

	inline KPDUtilityScheme stringToUtilityScheme(QString utilScheme){
		KPDUtilityScheme scheme = TRANSPLANTS;
		if (utilScheme == "SURVIVAL5YEAR"){ scheme = SURVIVAL5YEAR;  }
		else if (utilScheme == "SURVIVAL10YEAR"){ scheme = SURVIVAL10YEAR; }
		else if (utilScheme == "SCORE"){ scheme = SCORE; }

		return scheme;
	}

	inline KPDUtilityScheme dialogToUtilityScheme(QString utilScheme){
		KPDUtilityScheme scheme = TRANSPLANTS;
		if (utilScheme == "5 Year Survival"){ scheme = SURVIVAL5YEAR; }
		else if (utilScheme == "10 Year Survival"){ scheme = SURVIVAL10YEAR; }
		else if (utilScheme == "Score"){ scheme = SCORE; }

		return scheme;
	}

	inline KPDPairType stringToPairType(QString pairType){
		KPDPairType type = PAIR;
		if (pairType == "AD"){ type = AD; }

		return type;
	}

	inline QString toString(KPDOptimizationScheme scheme){
		if (scheme == MUC){ return "Utility"; }
		else if (scheme == MEUC){ return "Expected Utility"; }
		else if (scheme == MEUS){ return "Fallbacks"; }
		else if (scheme == SCC){ return "Extended Fallbacks"; }
		else { return ""; }
	}

	inline QString toString(KPDUtilityScheme scheme){
		if (scheme == TRANSPLANTS){ return "Transplants"; }
		else if (scheme == SURVIVAL5YEAR){ return "5 Year Survival"; }
		else if (scheme == SURVIVAL10YEAR){ return "10 Year Survival"; }
		else if (scheme == SCORE){ return "Score"; }
		else { return ""; }
	}

	inline QString toString(KPDPairType type){
		if (type == PAIR){ return "Pair"; }
		else if (type == AD){ return "AD"; }
		else { return ""; }
	}

}

#endif