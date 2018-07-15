#ifndef KPDGUINODEWRAPPER_H
#define KPDGUINODEWRAPPER_H

#include <QtGui>

#include "KPDGUINode.h"

class KPDGUINodeWrapper : public QObject, public QTreeWidgetItem 
{
	Q_OBJECT;

public:
	KPDGUINodeWrapper(KPDGUINode * node);
	~KPDGUINodeWrapper();

	KPDGUINode * getNode();	

signals:
	void updateVisibilitySignal();

public slots:
	void updateText();

	void nodeWrapperClickActions(QTreeWidgetItem * item);
	void nodeWrapperDoubleClickActions(QTreeWidgetItem * item);

private:
	KPDGUINode * myNode;

	bool operator<(const QTreeWidgetItem &other)const;
	
};


#endif