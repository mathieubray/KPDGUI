#ifndef KPDGUICANDIDATEWRAPPER_H
#define KPDGUICANDIDATEWRAPPER_H

#include <QtGui>

#include "KPDGUICandidate.h"

class KPDGUICandidateWrapper : public QObject, public QTreeWidgetItem
{
	Q_OBJECT;

public:
	KPDGUICandidateWrapper(KPDGUICandidate * Candidate);
	~KPDGUICandidateWrapper();

	KPDGUICandidate * getCandidate();

signals:
	void updateVisibilitySignal();
	
public slots:		
	void updateText();

	void candidateWrapperClickActions(QTreeWidgetItem * item);
	void candidateWrapperDoubleClickActions(QTreeWidgetItem * item);

private:
	KPDGUICandidate * myCandidate;

	bool operator<(const QTreeWidgetItem &other)const;

};


#endif