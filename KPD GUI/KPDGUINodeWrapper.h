#ifndef KPDGUINODEWRAPPER_H
#define KPDGUINODEWRAPPER_H

#include <QtGui>

#include "KPDGUINode.h"

class KPDGUINodeWrapper : public QObject, public QTreeWidgetItem 
{
	Q_OBJECT

public:
	KPDGUINodeWrapper(KPDGUINode * node);
	~KPDGUINodeWrapper();

	KPDGUINode * getNode();

	void updateText(int mode);

public slots:
	void selectionActions(int,bool);
	void editActions(int);
	//void silentSelectionActions(int, bool);

private:
	KPDGUINode * myNode;
	int prevMode;
	
};

//Sorting Classes

class KPDGUINodeLessThan
{
public:
	KPDGUINodeLessThan(int mode);
	bool operator()(KPDGUINodeWrapper *left, KPDGUINodeWrapper *right) const;

private:
	int myMode;
};

class KPDGUINodeGreaterThan
{
public:
	KPDGUINodeGreaterThan(int mode);
	bool operator()(KPDGUINodeWrapper *left, KPDGUINodeWrapper *right) const;

private:
	int myMode;
};

#endif