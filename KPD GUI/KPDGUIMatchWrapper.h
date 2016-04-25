#ifndef KPDGUIMATCHWRAPPER_H
#define KPDGUIMATCHWRAPPER_H

#include <QtGui>

#include "KPDGUIMatch.h"

class KPDGUIMatchWrapper : public QTreeWidgetItem
{

public:
	KPDGUIMatchWrapper(KPDGUIMatch * match);
	~KPDGUIMatchWrapper();

	KPDGUIMatch * getMatch();
	void updateText();
	
private:
	KPDGUIMatch * myMatch;

	bool operator<(const QTreeWidgetItem &other)const;

};

#endif