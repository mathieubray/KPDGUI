#ifndef KPDGUISTRUCTURE_H
#define KPDGUISTRUCTURE_H

#include <QtGui>

#include <math.h>

#include "KPDGUINode.h"
#include "KPDGUINodeWrapper.h"
#include "KPDGUIMatch.h"

class KPDGUIStructure
{
public:
	KPDGUIStructure(QVector<KPDGUINode *> nodeList, KPDOptimizationScheme optScheme, double utility, int id);
	~KPDGUIStructure();

	void select();
	void highlight();
	void undoHighlights();
	qreal centerX();
	qreal centerY();
	void cluster();
	void cluster(qreal x, qreal y);
	
	QString text();
	int size();
	bool hasAnAD();

	bool contains(KPDGUINode * node);
	bool contains(KPDGUIDonor * donor);
	bool contains(KPDGUICandidate * candidate);
	
	double getUtility() const;
	int getID() const;

	void increasePopularity(bool solution);
	void decreasePopularity(bool solution);
	void resetPopularity(bool solution);
	
	QString structureString();

	QList<QTreeWidgetItem *> getItemList();

private:
	QVector<KPDGUINode *> structureNodeList;
	QSet<KPDGUIMatch *> structureMatches;

	KPDOptimizationScheme structureOptScheme;
	
	double structureUtility;
	int structureID;		
	bool structureHasAnAD;
};

#endif