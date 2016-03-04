#ifndef KPDGUIARROWWRAPPER_H
#define KPDGUIARROWWRAPPER_H

#include <QtGui>

#include "KPDGUIArrow.h"

class KPDGUIArrowWrapper : public QTreeWidgetItem
{
	//Q_OBJECT;

public:
	KPDGUIArrowWrapper(KPDGUIArrow * arrow);
	~KPDGUIArrowWrapper();

	KPDGUIArrow * getArrow();
	void updateText();
	
private:
	KPDGUIArrow * myArrow;

	bool operator<(const QTreeWidgetItem &other)const;

};


#endif