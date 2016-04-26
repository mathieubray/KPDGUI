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
	

public slots:
	//void selectionActions(int, bool);
	void editActions();

	void highlightNode(QTreeWidgetItem *);

	void updateSelections();
	void updateText();

private:
	KPDGUINode * myNode;

	bool operator<(const QTreeWidgetItem &other)const;
	
};

#endif