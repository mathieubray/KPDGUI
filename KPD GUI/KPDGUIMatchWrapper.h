#ifndef KPDGUIMATCHWRAPPER_H
#define KPDGUIMATCHWRAPPER_H

#include <QtGui>

#include "KPDGUIMatch.h"

class KPDGUIMatchWrapper : public QObject, public QTreeWidgetItem
{
	Q_OBJECT;

public:
	KPDGUIMatchWrapper(KPDGUIMatch * match);
	~KPDGUIMatchWrapper();

	KPDGUIMatch * getMatch();

public slots:
	void updateText();

	void matchWrapperDoubleClickActions(QTreeWidgetItem * item);
	
private:
	KPDGUIMatch * myMatch;

	bool operator<(const QTreeWidgetItem &other)const;

};


#endif