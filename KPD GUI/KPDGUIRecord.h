#ifndef KPDGUIRECORD_H
#define KPDGUIRECORD_H

#include <QtGui>
#include <QtWidgets>
#include <QtDebug>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "KPDGUINode.h"
#include "KPDGUINodeWrapper.h"
#include "KPDGUIArrow.h"
#include "KPDGUIArrowWrapper.h"
#include "KPDGUIGraphicsScene.h"

#include "Structs.h"

class KPDGUIRecord : public QObject
{
	Q_OBJECT;

public:
	KPDGUIRecord();
	~KPDGUIRecord();
	
	//Pairs
	//int loadPairs(QString file);
	//void addPair(KPDGUINode * node, bool fromSavedFile=false);
	void insert(KPDGUINode * node, bool fromSavedFile = false);
	void insertArrow(KPDGUIArrow * arrow);
			
	KPDGUINode * getNode(int id);
	KPDGUINode * getNodeFromIndex(int i);
	//KPDGUINode * connectNodePtr(int i);
	int getIDfromIndex(int index);
	int size();
	void clear();

	bool isMatch(Donor * donor, Candidate * candidate, bool reserveOtoO, bool checkDP);
	bool isMatch(KPDGUINode * donor, KPDGUINode * candidate, bool reserveOtoO, bool checkDP);
	
	QList<KPDGUINode *> getPairs();

	//Matrices
	void generateMatrices(bool reserveOtoO, bool checkDP, bool includeCompatiblePairs);
	std::vector<std::vector<int> > viableTransplantMatrix;
	std::vector<std::vector<double > > scoreMatrix;
	std::vector<std::vector<double > > survival5yearMatrix;
	std::vector<std::vector<double > > survival10yearMatrix;
	std::vector<std::vector<double > > probabilityMatrix;
	std::vector<std::vector<int> > labCrossmatchMatrix;
	std::vector<std::vector<bool> > incidenceMatrix;
	std::vector<Pair> pairVector;
	std::vector<int> inTimes;

	//Other Settings
	int getBaselineIDCode();
	void setBaselineIDCode(int code);
	
signals:
	
	//void removeStructureHighlights();
	void takeAdditionalDeleteNodeActions(KPDGUINode * node);

public slots:
	//void updateVisibility();
	//void undoHighlights();
	void deleteNodeFromRecord(int id);

protected:
	void loadDictionary();	
	void clearMatrices();
	
	double survival(KPDGUINode * d, KPDGUINode * c, int fiveyear);

private:
	//Input Vectors 
	QMap<QString, QVector<QString> > hla_dictionary;

	//Stored Items
	QMap<int, KPDGUINode*> pairs;
	QSet<KPDGUIArrow *> arrows;
	QVector<int> orderedPairs;
	QMap<int, int> intToExt;


	//Parameters
	//QString dataconfig;
	int id_code;
	

	
	
};

#endif
