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
#include "KPDGUISimParameters.h"


class KPDGUIRecord : public QObject
{
	Q_OBJECT;

public:
	KPDGUIRecord();
	~KPDGUIRecord();
	
	//Pairs
	void insertNode(KPDGUINode * node, bool fromSavedFile = false);
	void insertArrow(KPDGUIArrow * arrow);
			
	KPDGUINode * getNode(int id);
	KPDGUINode * getNodeFromIndex(int i);
	
	int size();
	void clear();

	bool isMatch(Donor donor, Candidate candidate, bool reserveOtoO, bool checkAdditionalHLA);
	bool isMatch(KPDGUINode * donor, KPDGUINode * candidate, bool reserveOtoO, bool checkAdditionalHLA);
	
	QList<KPDGUINode *> getNodes();

	//Matrices
	void generateMatrices(KPDGUISimParameters * params, QProgressDialog * progress);
	
	std::vector<std::vector<int> > viableTransplantMatrix;
	std::vector<std::vector<double > > scoreMatrix;
	std::vector<std::vector<double > > survival5yearMatrix;
	std::vector<std::vector<double > > survival10yearMatrix;
	std::vector<std::vector<double > > probabilityMatrix;
	std::vector<std::vector<int> > labCrossmatchMatrix;
	std::vector<std::vector<bool> > incidenceMatrix;
	std::vector<AdditionalPairInfo> pairInfoVector;
	
	//Other Settings
	int getBaselineIDCode();
	void setBaselineIDCode(int code);

	int getNumberOfNodes();

	QString getRecordLog();
	
signals:
	
	void takeAdditionalDeleteNodeActions(KPDGUINode * node);

public slots:
	void deleteNodeFromRecord(int id);

protected:
	void loadDictionary();	
	void clearMatrices();
	
	double survival(Donor d, Candidate c, int fiveyear);
	double survival(KPDGUINode * d, KPDGUINode * c, int fiveyear);
	

private:
	//Input Vectors 
	QMap<QString, QVector<QString> > hla_dictionary;

	//Stored Items
	QMap<int, KPDGUINode*> pairs;
	QSet<KPDGUIArrow *> arrows;
	
	//Parameters
	int id_code;

	QString recordLog;
	
};

#endif
