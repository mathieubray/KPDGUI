#ifndef STRUCTS_H
#define STRUCTS_H

#include <qstring.h>
#include <qvector.h>

struct Candidate{
	//Administrative
	int id;
	int recipid;
	int regid;

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

	bool sensitized;
	QVector<int> excludedDonors;
};

struct Donor{
	//Administrative
	int id;
	int donorid;
	int regid;
	int type;

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
};

struct Pair{
	int pairLabel;

	int pairID;
	int poolID;

	int donorID;
	std::string donorBT;
	//int donorBTCode;
	int donorAge;
	bool donorMale;
	double donorWeight;
	double donorBMI;

	int recipID;
	std::string recipBT;
	//int recipBTCode;
	int recipAge;
	bool recipMale;
	std::string recipRace;
	bool recipDiabetes;
	double recipWeight;
	double recipBMI;
	double recipPRA;
	bool recipPrevTrans;
	double recipTOD;
	bool recipHepC;

	bool recipSensitized;

	double uncertainty;
	std::vector<int> pairAvailabilityVector;
	std::vector<int> pairAttritionVector;
	std::vector<int> pairRenegeVector;
	std::vector<int> pairSTBDRenegeVector;
	int donorType;
};

struct ParamInfoStruct{
	int maxChainLength;
	QString utilScheme;
	QString optScheme;
	bool praAdvantage;
	bool reserveOtoO;
	bool checkDP;
	bool includeCompatiblePairs;
	bool includeABBridgeDonors;
	int numberOfSolutions;
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

	int arrowDisplayMode;
};

#endif