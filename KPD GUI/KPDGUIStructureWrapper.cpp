#include "KPDGUIStructureWrapper.h"

KPDGUIStructureWrapper::KPDGUIStructureWrapper(KPDGUIStructure * structure){
	myStructure = structure;
	
	setText(0, structure->text());
	setText(0, QString::number(structure->getUtility()));

	addChildren(structure->getItemList());	
	setExpanded(true);
}

KPDGUIStructureWrapper::~KPDGUIStructureWrapper(){

}

KPDGUIStructure * KPDGUIStructureWrapper::getStructure(){
	return myStructure;
}


bool KPDGUIStructureWrapper::operator<(const QTreeWidgetItem &other) const{
	
	return text(1).toInt() < other.text(1).toInt();
}