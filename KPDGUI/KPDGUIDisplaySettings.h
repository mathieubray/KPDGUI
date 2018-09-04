#ifndef KPDGUIDISPLAYSETTINGS_H
#define KPDGUIDISPLAYSETTINGS_H

#include <QtGui>
#include <QtWidgets>

#include "DialogDisplaySettings.h"

#include "KPDGUIEnumsFunctions.h"

class KPDGUIDisplaySettings {
	
private:

	KPDDonorDisplayMode nodeDisplayMode;

	bool showAllNodes;
	bool showNodeSubset;
	bool showNodesInArrangements;
	bool showNodesInSolutions;
	bool showExcludedNodes;
	bool showNodesWithNoCompatibilities;
	bool showCandidatesInPRARange;

	int minPRA;
	int maxPRA;

	KPDMatchDisplayMode matchDisplayMode;

	bool filterSuccessfulMatches;
	bool filterOtoNonOMatches;
	bool filterFailedMatchesAdditionalHLA;
	bool filterFailedMatchesCrossmatch;

	bool highlightMatchesToAvoid;

public:

	KPDGUIDisplaySettings();
	~KPDGUIDisplaySettings();

	bool changeDisplaySettings(DialogDisplaySettings * d);
	bool changeDisplaySettings(KPDGUIDisplaySettings * d);

	// Getters
	KPDDonorDisplayMode getNodeDisplayMode() const;

	bool getShowAllNodes() const;
	bool getShowNodeSubset() const;
	bool getShowNodesInArrangements() const;
	bool getShowNodesInSolutions() const;
	bool getShowExcludedNodes() const;
	bool getShowNodesWithNoCompatibilities() const;
	bool getShowCandidatesInPRARange() const;

	int getMinPRA() const;
	int getMaxPRA() const;

	KPDMatchDisplayMode getMatchDisplayMode() const;

	bool getFilterSuccessfulMatches() const;
	bool getFilterOtoNonOMatches() const;
	bool getFilterFailedMatchesAdditionalHLA() const;
	bool getFilterFailedMatchesCrossmatch() const;

	bool getHighlightMatchesToAvoid() const;

	// Setters
	void setNodeDisplayMode(KPDDonorDisplayMode mode);	

	void setShowAllNodes(bool show);
	void setShowNodeSubset(bool show);
	void setShowNodesInArrangements(bool show);
	void setShowNodesInSolutions(bool show);
	void setShowExcludedNodes(bool show);
	void setShowNodesWithNoCompatibilities(bool show);
	void setShowCandidatesInPRARange(bool show);

	void setMinPRA(int pra);
	void setMaxPRA(int pra);

	void setMatchDisplayMode(KPDMatchDisplayMode mode);

	void setFilterSuccessfulMatches(bool show);
	void setFilterOtoNonOMatches(bool show);
	void setFilterFailedMatchesAdditionalHLA(bool show);
	void setFilterFailedMatchesCrossmatch(bool show);

	void setHightlightMatchesToAvoid(bool flag);

};

QDataStream &operator<<(QDataStream &out, const KPDGUIDisplaySettings &settings);

QDataStream &operator>>(QDataStream &in, KPDGUIDisplaySettings &settings);

#endif