#include "KPDGUIStructureWrapper.h"

KPDGUIStructureWrapper::KPDGUIStructureWrapper(KPDGUIStructure * structure){
	myStructure = structure;
	
	setText(0, structure->text());

	addChildren(structure->getItemList());	
	setExpanded(true);
}

KPDGUIStructureWrapper::~KPDGUIStructureWrapper(){

}

KPDGUIStructure * KPDGUIStructureWrapper::getStructure(){
	return myStructure;
}