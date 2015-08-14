#ifndef KPDGUIARROWWRAPPER_H
#define KPDGUIARROWWRAPPER_H

#include <QtGui>

#include "KPDGUIArrow.h"

class KPDGUIArrowWrapper : public QObject, public QTreeWidgetItem
{
	Q_OBJECT

public:
	KPDGUIArrowWrapper(KPDGUIArrow * arrow);
	~KPDGUIArrowWrapper();

	KPDGUIArrow * getArrow();

	void updateText(int mode);

public slots:
	void changeArrowSelection(bool);

private:
	KPDGUIArrow * myArrow;
};

//Sorting Classes

class KPDGUIArrowLessThan
{
public:
	KPDGUIArrowLessThan(int mode);
	bool operator()(KPDGUIArrowWrapper *left, KPDGUIArrowWrapper *right) const;
	
private:
	int myMode;
};

class KPDGUIArrowGreaterThan
{
public:
	KPDGUIArrowGreaterThan(int mode);
	bool operator()(KPDGUIArrowWrapper *left, KPDGUIArrowWrapper *right) const;

private:
	int myMode;
};

#endif