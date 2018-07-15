#ifndef KPDGUIARRANGEMENTWRAPPER_H
#define KPDGUIARRANGEMENTWRAPPER_H

#include <QtGui>

#include "KPDGUIArrangement.h"

class KPDGUIArrangementWrapper : public QObject, public QTreeWidgetItem
{	
	Q_OBJECT;

public:
	KPDGUIArrangementWrapper(KPDGUIArrangement * arrangement);
	~KPDGUIArrangementWrapper();

	KPDGUIArrangement * getArrangement();
	
public slots:		
	void updateText();

private:
	KPDGUIArrangement * myArrangement;

	bool operator<(const QTreeWidgetItem &other)const;

};


#endif