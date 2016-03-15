#ifndef KPDGUISTRUCTURESET_H
#define KPDGUISTRUCTURESET_H

#include <QtGui>
#include <math.h>

#include "KPDGUISimulParam.h"
#include "KPDGUIStructure.h"
#include "KPDGUIStructureWrapper.h"

class KPDGUIStructureSet : public QTreeWidgetItem
{

public:
	KPDGUIStructureSet();
	KPDGUIStructureSet(ParamInfoStruct parameters, QString timeStamp, QString simLog, bool solution, int solutionNumber = 0);
	~KPDGUIStructureSet();

	void construct(ParamInfoStruct parameters, QString timeStamp, QString simLog, bool solution, int solutionNumber = 0);
		
	void push_back(KPDGUIStructure * structure);
	void removeStructure(KPDGUIStructure * structure);

	ParamInfoStruct getParameters() const { return myParameters;  }
	KPDOptimizationScheme getOptScheme() const { return myParameters.optScheme; }

	QString getTimeStamp() const { return myTimeStamp; }
	QString getSimLog() const { return mySimLog;  }
	int getSolutionNumber() const { return mySolutionNumber;  }
	QList<KPDGUIStructure *> getStructures();
	
	void selectStructures();
	void highlight();
	void undoHighlights();
	qreal centerX();
	qreal centerY();
	void cluster();
	void deleteNode(KPDGUINode * node);
	
	int size();
	int numberOfElements();
	double utility();
	bool isSolutionSet();
	void updatePopularity();
	void resetPopularity();

	QString getConsoleString();

public slots:
	void updateTree();

private:

	void setUpWidgets();

	QVector<KPDGUIStructureWrapper *> myStructureWrappers;
	QVector<KPDGUIStructure *> myStructureList;
	ParamInfoStruct myParameters;

	QTreeWidgetItem * cycleSizeTwo;
	QTreeWidgetItem * cycleSizeThree;
	QTreeWidgetItem * chainSizeOne;
	QTreeWidgetItem * chainSizeTwo;
	QTreeWidgetItem * chainSizeThree;
	QTreeWidgetItem * chainSizeFour;
	QTreeWidgetItem * chainSizeFive;
	QTreeWidgetItem * chainSizeSix;
	QTreeWidgetItem * componentSizeTwo;
	QTreeWidgetItem * componentSizeThree;
	QTreeWidgetItem * componentSizeFour;

	QString myTimeStamp;
	QString mySimLog;

	bool solutionSet;
	int mySolutionNumber;
};

QDataStream &operator<<(QDataStream &out, const KPDGUIStructureSet & node);

QDataStream &operator>>(QDataStream &in, KPDGUIStructureSet & node);

#endif