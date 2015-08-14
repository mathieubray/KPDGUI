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
	//bool contains(KPDGUIStructure * structure);

private:
	KPDGUIStructure * myStructure;

};

#endif