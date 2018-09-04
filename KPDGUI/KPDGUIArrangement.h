#ifndef KPDGUIARRANGEMENT_H
#define KPDGUIARRANGEMENT_H

#include <QtGui>

#include <math.h>

#include "KPDGUINode.h"
#include "KPDGUINodeWrapper.h"
#include "KPDGUIMatch.h"

class KPDGUIArrangement : public QObject
{

	Q_OBJECT;

public:
	KPDGUIArrangement();
	KPDGUIArrangement(int id, double utility);
	~KPDGUIArrangement();

	void setID(int id);
	void setUtility(double util);

	void addNode(KPDGUINode * node);
	void addMatch(KPDGUIMatch * match);

	// Arrangement Properties
	QVector<KPDGUINode *> getNodes();
	QList<KPDGUIMatch *> getMatches();

	int getID() const;
	double getUtility() const;
	
	int getNumberOfNodes();
	int getNumberOfMatches();
	bool hasAnNDD();

	bool containsNode(KPDGUINode * node);
	bool containsDonor(KPDGUIDonor * donor);
	bool containsCandidate(KPDGUICandidate * candidate);

signals:
	void arrangementIsolated(int minX, int maxX, int minY, int maxY);
	void arrangementClustered(int x, int y);

public slots:
	// Visual Properties
	void select();
	void highlight();
	void undoHighlights();
	qreal centerX();
	qreal centerY();
	qreal minX();
	qreal maxX();
	qreal minY();
	qreal maxY();
	void cluster();
	void cluster(qreal x, qreal y);
	void isolate();
	void isolate(qreal minX, qreal maxX, qreal minY, qreal maxY);
	
	// Helper Functions
	void increasePopularity(bool solution);
	void decreasePopularity(bool solution);
	void resetPopularity(bool solution);
	
	//QList<QTreeWidgetItem *> getItemList();
	
	// Strings
	QString arrangementLabel();
	QString arrangementDashboardString();
	QString arrangementSolutionString();


private:
	QVector<KPDGUINode *> arrangementNodes;
	QList<KPDGUIMatch *> arrangementMatches;
	
	int arrangementID;
	double arrangementUtility;

	bool arrangementHasAnNDD;
};


#endif