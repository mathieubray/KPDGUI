#ifndef KPDGUISTRUCTURESET_H
#define KPDGUISTRUCTURESET_H

#include <QtGui>
#include <math.h>

#include "KPDGUISimParameters.h"
#include "KPDGUIStructure.h"
#include "KPDGUIStructureWrapper.h"

class KPDGUIStructureSet : public QTreeWidgetItem
{

public:
	KPDGUIStructureSet();
	KPDGUIStructureSet(KPDGUISimParameters * parameters, QString timeStamp, QString recordLog, QString simLog, bool solution, int solutionNumber = 0);
	~KPDGUIStructureSet();

	void construct(KPDGUISimParameters * parameters, QString timeStamp, QString recordLog, QString simLog, bool solution, int solutionNumber = 0);
		
	void push_back(KPDGUIStructure * structure);
	void removeStructure(KPDGUIStructure * structure);

	KPDGUISimParameters * getParameters() const { return myParameters;  }
	KPDOptimizationScheme getOptScheme() const { return myParameters->getOptimizationScheme(); }

	QString getTimeStamp() const { return myTimeStamp; }
	QString getRecordLog() const { return myRecordLog;  }
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
	void sort();

	QString getConsoleString();

public slots:
	void updateTree();

private:

	void setUpWidgets();

	void updateText();

	QVector<KPDGUIStructureWrapper *> myStructureWrappers;
	QVector<KPDGUIStructure *> myStructureList;
	KPDGUISimParameters * myParameters;

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
	QTreeWidgetItem * componentSizeFive;
	QTreeWidgetItem * componentSizeSix;

	QString myTimeStamp;
	QString myRecordLog;
	QString mySimLog;

	bool solutionSet;
	int mySolutionNumber;
};

QDataStream &operator<<(QDataStream &out, const KPDGUIStructureSet & structureSet);

QDataStream &operator>>(QDataStream &in, KPDGUIStructureSet & structureSet);

#endif