#ifndef KPDGUIDISPLAYSETTINGS_H
#define KPDGUIDISPLAYSETTINGS_H

#include <qstring.h>
#include <qvector.h>
#include <qdatastream.h>

#include "DialogDisplaySettings.h"
#include "EnumsFunctions.h"

class KPDGUIDisplaySettings {

public:

	KPDGUIDisplaySettings();
	~KPDGUIDisplaySettings();

	bool changeDisplaySettings(DialogDisplaySettings * d);

	bool getShowAllPairs() const;
	bool getShowPairSubset() const;
	bool getShowPairsInStructures() const;
	bool getShowPairsInSolutions() const;
	bool getShowPairsOnHold() const;
	bool getShowPairsWithNoCompatibilities() const;
	bool getShowPairsOfMinPRA() const;
	bool getShowPairsOfMaxPRA() const;

	int getMinPRA() const;
	int getMaxPRA() const;

	KPDArrowDisplayMode getArrowDisplayMode() const;

	void setShowAllPairs(bool show);
	void setShowPairSubset(bool show);
	void setShowPairsInStructures(bool show);
	void setShowPairsInSolutions(bool show);
	void setShowPairsOnHold(bool show);
	void setShowPairsWithNoCompatibilities(bool show);
	void setShowPairsOfMinPRA(bool show);
	void setShowPairsOfMaxPRA(bool show);

	void setMinPRA(int pra);
	void setMaxPRA(int pra);

	void setArrowDisplayMode(KPDArrowDisplayMode mode);

private:
	bool showAllPairs;
	bool showPairSubset;
	bool showPairsInSolutions;
	bool showPairsInStructures;
	bool showPairsOnHold;
	bool showPairsWithNoCompatibilities;
	bool showPairsOfMinPRA;
	bool showPairsOfMaxPRA;

	int minPRA;
	int maxPRA;

	KPDArrowDisplayMode arrowDisplayMode;
};

QDataStream &operator<<(QDataStream &out, const KPDGUIDisplaySettings & settings);

QDataStream &operator>>(QDataStream &in, KPDGUIDisplaySettings & settings);

#endif