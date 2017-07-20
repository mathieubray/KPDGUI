#ifndef KPDGUIARRANGEMENT_H
#define KPDGUIARRANGEMENT_H

#include <QtGui>

#include <math.h>

#include "KPDGUINode.h"
#include "KPDGUINodeWrapper.h"
#include "KPDGUIMatch.h"

class KPDGUIArrangement
{
public:
	KPDGUIArrangement();
	KPDGUIArrangement(double utility, QString id);
	~KPDGUIArrangement();

	void setID(QString id);
	void setUtility(double util);

	void addNode(KPDGUINode * node);
	void addMatch(KPDGUIMatch * match);

	// Arrangement Properties
	QVector<KPDGUINode *> getNodes();
	QList<KPDGUIMatch *> getMatches();

	QString getID() const;
	double getUtility() const;
	
	int getNumberOfNodes();
	int getNumberOfMatches();
	bool hasAnNDD();

	bool containsNode(KPDGUINode * node);
	bool containsDonor(KPDGUIDonor * donor);
	bool containsCandidate(KPDGUICandidate * candidate);

	// Visual Properties
	void select();
	void highlight();
	void undoHighlights();
	qreal centerX();
	qreal centerY();
	void cluster();
	void cluster(qreal x, qreal y);
	
	// Helper Functions
	void increasePopularity(bool solution);
	void decreasePopularity(bool solution);
	void resetPopularity(bool solution);
	
	//QList<QTreeWidgetItem *> getItemList();
	
	// Strings
	QString arrangementLabel();
	QString arrangementDashboardString();


private:
	QVector<KPDGUINode *> arrangementNodes;
	QList<KPDGUIMatch *> arrangementMatches;
	
	QString arrangementID;
	double arrangementUtility;

	bool arrangementHasAnNDD;
};


#endif