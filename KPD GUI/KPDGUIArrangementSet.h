#ifndef KPDGUIARRANGEMENTSET_H
#define KPDGUIARRANGEMENTSET_H

#include <QtGui>
#include <math.h>

#include "KPDGUIParameters.h"
#include "KPDGUIArrangement.h"
#include "KPDGUIArrangementWrapper.h"

#include "DialogMessage.h"

class KPDGUIArrangementSet : public QObject, public QTreeWidgetItem
{
	Q_OBJECT;

public:
	KPDGUIArrangementSet();
	KPDGUIArrangementSet(KPDGUIParameters * params, QString timestamp, QString nodeList, QString matchList, bool solution, bool complete, int trueSetNum, int number = 0);
	~KPDGUIArrangementSet();

	void construct(KPDGUIParameters * params, QString timestamp, QString nodeList, QString matchList, bool solution, bool complete, int trueSetNum, int number = 0);
		
	void addArrangement(KPDGUIArrangement * arrangement);
	
	// Arrangement Set Properties
	QList<KPDGUIArrangement *> getArrangements();
	
	KPDGUIParameters * getParameters() const;
	QString getName() const;
	QString getTimestamp() const;
	QString getNodeList() const;
	QString getMatchList() const;
	bool isSolutionSet() const;
	bool isCompleteSet() const;
	int getTrueSetSize() const;
	int getSetNumber() const;

	int getNumberOfArrangements();
	int getNumberOfNodes();
	double getUtility();
	void sort();
	
	bool containsNode(KPDGUINode * node);
	bool containsDonor(KPDGUIDonor * donor);
	bool containsCandidate(KPDGUICandidate * candidate);
	

	QString toString();
	QString toCondensedString();

	void setUpWidgets();

signals:

	void arrangementClustered(int x, int y);

public slots:

	// Visual Properties
	void select();
	void highlight();
	void undoHighlights();
	qreal centerX();
	qreal centerY();
	void cluster();


	// Helper Functions
	void increasePopularity();
	void decreasePopularity();
	void resetPopularity();

	void displayInformation();

private:

	void updateText();

	KPDGUIParameters * arrangementSetParameters;

	QString arrangementSetName;
	QString arrangementSetTimestamp;
	QString arrangementSetNodeList;
	QString arrangementSetMatchList;
	bool isSolution;
	bool isComplete;
	int trueSetSize;
	int setNumber;

	QVector<KPDGUIArrangement *> arrangements;
	QVector<KPDGUIArrangementWrapper *> arrangementWrappers;
	
	QMap<int, QTreeWidgetItem *> arrangementSetCycles;
	QMap<int, QTreeWidgetItem *> arrangementSetChains;
	QMap<int, QTreeWidgetItem *> arrangementSetLRSs;

	
};

QDataStream &operator<<(QDataStream &out, const KPDGUIArrangementSet & arrangementSet);

QDataStream &operator>>(QDataStream &in, KPDGUIArrangementSet & arrangementSet);

#endif