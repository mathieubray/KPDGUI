#ifndef KPDGUIARRANGEMENTSET_H
#define KPDGUIARRANGEMENTSET_H

#include <QtGui>
#include <math.h>

#include "KPDGUIParameters.h"
#include "KPDGUIArrangement.h"
#include "KPDGUIArrangementWrapper.h"

#include "DialogMessage.h"

class KPDGUIArrangementSet : public QTreeWidgetItem
{

public:
	KPDGUIArrangementSet();
	KPDGUIArrangementSet(KPDGUIParameters * params, QString timestamp, QString text, bool solution, int number = 0);
	~KPDGUIArrangementSet();

	void construct(KPDGUIParameters * params, QString timestamp, QString text, bool solution, int number = 0);
		
	void addArrangement(KPDGUIArrangement * arrangement);
	
	// Arrangement Set Properties
	QList<KPDGUIArrangement *> getArrangements();
	
	KPDGUIParameters * getParameters() const;
	QString getTimestamp() const;
	QString getMatchRunText() const;
	bool isSolutionSet() const;
	int getSetNumber() const;

	int getNumberOfArrangements();
	int getNumberOfNodes();
	double getUtility();
	void sort();
	
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

	
	// Helper Functions
	void increasePopularity();
	void decreasePopularity();
	void resetPopularity();

	QString getDashboardString();

	void setUpWidgets();

public slots:

	void displayInformation();

private:

	void updateText();

	KPDGUIParameters * arrangementSetParameters;

	QString arrangementSetTimestamp;
	QString arrangementSetMatchRunText;

	bool isSolution;
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