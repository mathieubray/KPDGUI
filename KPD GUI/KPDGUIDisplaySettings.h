#ifndef KPDGUIDISPLAYSETTINGS_H
#define KPDGUIDISPLAYSETTINGS_H

#include <qstring.h>
#include <qvector.h>
#include <qdatastream.h>

#include "DialogDisplaySettings.h"
#include "EnumsFunctions.h"

class KPDGUIDisplaySettings {
	
private:
	bool showAllNodes;
	bool showNodeSubset;
	bool showNodesInSolutions;
	bool showNodesInStructures;
	bool showNodesOnHold;
	bool showNodesWithNoCompatibilities;
	bool showCandidatesInPRARange;

	int minPRA;
	int maxPRA;

	KPDMatchDisplayMode matchDisplayMode;

public:

	KPDGUIDisplaySettings();
	~KPDGUIDisplaySettings();

	bool changeDisplaySettings(DialogDisplaySettings * d);

	bool getShowAllNodes() const;
	bool getShowNodeSubset() const;
	bool getShowNodesInStructures() const;
	bool getShowNodesInSolutions() const;
	bool getShowNodesOnHold() const;
	bool getShowNodesWithNoCompatibilities() const;
	bool getShowCandidatesInPRARange() const;

	int getMinPRA() const;
	int getMaxPRA() const;

	KPDMatchDisplayMode getMatchDisplayMode() const;

	void setShowAllNodes(bool show);
	void setShowNodeSubset(bool show);
	void setShowNodesInStructures(bool show);
	void setShowNodesInSolutions(bool show);
	void setShowNodesOnHold(bool show);
	void setShowNodesWithNoCompatibilities(bool show);
	void setShowCandidatesInPRARange(bool show);

	void setMinPRA(int pra);
	void setMaxPRA(int pra);

	void setMatchDisplayMode(KPDMatchDisplayMode mode);

};

QDataStream &operator<<(QDataStream &out, const KPDGUIDisplaySettings & settings);

QDataStream &operator>>(QDataStream &in, KPDGUIDisplaySettings & settings);

#endif