#ifndef KPDGUICROSSMATCHFUNCTIONS_H
#define KPDGUICROSSMATCHFUNCTIONS_H

#include <QtGui>
#include <QtWidgets>

#include "KPDGUIDonor.h"
#include "KPDGUICandidate.h"

class KPDGUICrossmatchFunctions {

public:
	KPDGUICrossmatchFunctions();
	~KPDGUICrossmatchFunctions();

	KPDCrossmatchResult performCrossmatch(KPDGUIDonor * donor, KPDGUICandidate * candidate);
	QVector<int> countHLAMismatches(KPDGUIDonor * donor, KPDGUICandidate * candidate);
	double calculateSurvival(KPDGUIDonor * donor, KPDGUICandidate * candidate, int fiveyear);
	bool determineDifficultMatch(KPDGUIDonor * donor, KPDGUICandidate * candidate);

private:
	QMap<QString, QVector<QString> > hlaDictionary;
	QMap<QString, QVector<double> > survivalParameters;
	
	void loadDictionary();
	void loadSurvivalParameters();

};

#endif
