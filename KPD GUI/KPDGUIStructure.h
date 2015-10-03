#ifndef KPDGUISTRUCTURE_H
#define KPDGUISTRUCTURE_H

#include <QtGui>

#include <math.h>

#include "KPDGUINode.h"
#include "KPDGUINodeWrapper.h"
#include "KPDGUIArrow.h"

class KPDGUIStructure
{
public:
	KPDGUIStructure(QVector<KPDGUINode *> pairList, KPDOptimizationScheme optScheme, double utility, int id);
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
	bool isChain();
	bool contains(KPDGUINode * node);
	double getUtility() const;
	int getID() const;

	void increasePopularityInStructures();
	void increasePopularityInSolutions();
	void decreasePopularityInStructures();
	void decreasePopularityInSolutions();
	void resetPopularityInStructures();
	void resetPopularityInSolutions();
	
	QString toString();

	QList<QTreeWidgetItem *> getItemList();

private:
	QVector<KPDGUINode *> myPairList;
	QSet<KPDGUIArrow *> myArrows;
	KPDOptimizationScheme myOptScheme;
	double myUtility;
	int myID;		
	bool chain;
};

#endif