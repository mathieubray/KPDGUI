#ifndef KPDGUISTRUCTUREWRAPPER_H
#define KPDGUISTRUCTUREWRAPPER_H

#include <QtGui>

#include "KPDGUIStructure.h"

class KPDGUIStructureWrapper : public QTreeWidgetItem
{	

public:
	KPDGUIStructureWrapper(KPDGUIStructure * structure);
	~KPDGUIStructureWrapper();

	KPDGUIStructure * getStructure();
	void updateText();

private:
	KPDGUIStructure * myStructure;

	bool operator<(const QTreeWidgetItem &other)const;

};

#endif