#ifndef KPDGUICANDIDATEWRAPPER_H
#define KPDGUICANDIDATEWRAPPER_H

#include <QtGui>

#include "KPDGUICandidate.h"

class KPDGUICandidateWrapper : public QTreeWidgetItem
{
	//Q_OBJECT;

public:
	KPDGUICandidateWrapper(KPDGUICandidate * Candidate);
	~KPDGUICandidateWrapper();

	KPDGUICandidate * getCandidate();
	void updateText();

private:
	KPDGUICandidate * myCandidate;

	bool operator<(const QTreeWidgetItem &other)const;

};


#endif