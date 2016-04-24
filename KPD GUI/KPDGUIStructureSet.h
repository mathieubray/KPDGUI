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
	KPDGUIStructureSet(KPDGUISimParameters * params, QString timeStamp, QString recordLog, QString simLog, bool solution, int solutionNumber = 0);
	~KPDGUIStructureSet();

	void construct(KPDGUISimParameters * params, QString timeStamp, QString recordLog, QString simLog, bool solution, int solutionNumber = 0);
		
	void addStructure(KPDGUIStructure * structure);
	void removeStructure(KPDGUIStructure * structure);

	KPDGUISimParameters * getParameters() const { return structureSetParameters;  }
	KPDOptimizationScheme getOptScheme() const { return structureSetParameters->getOptimizationScheme(); }

	QString getTimeStamp() const { return structureSetTimeStamp; }
	QString getRecordLog() const { return structureSetRecordLog;  }
	QString getSimLog() const { return structureSetSimLog;  }
	int getSolutionNumber() const { return solutionNumber;  }
	
	QList<KPDGUIStructure *> getStructures();
	
	void selectStructures();
	void highlight();
	void undoHighlights();
	qreal centerX();
	qreal centerY();
	void cluster();
	void deleteNode(KPDGUINode * node);
	
	int size();
	int getNumberOfNodes();
	double utility();
	bool structureSetisSolutionSet();
	void updatePopularity();
	void resetPopularity();
	void sort();

	QString getDashboardString();

public slots:
	void updateTree();

private:

	void setUpWidgets();
	void updateText();

	QVector<KPDGUIStructureWrapper *> structureSetWrappers;
	QVector<KPDGUIStructure *> structureSetList;
	KPDGUISimParameters * structureSetParameters;

	QMap<int, QTreeWidgetItem *> structureSetCycles;
	QMap<int, QTreeWidgetItem *> structureSetChains;
	QMap<int, QTreeWidgetItem *> structureSetComponents;

	QString structureSetTimeStamp;
	QString structureSetRecordLog;
	QString structureSetSimLog;

	bool isSolutionSet;
	int solutionNumber;
};

QDataStream &operator<<(QDataStream &out, const KPDGUIStructureSet & structureSet);

QDataStream &operator>>(QDataStream &in, KPDGUIStructureSet & structureSet);

#endif