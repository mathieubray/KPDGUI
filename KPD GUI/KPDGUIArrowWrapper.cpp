#include "KPDGUIArrowWrapper.h"

KPDGUIArrowWrapper::KPDGUIArrowWrapper(KPDGUIArrow * arrow){
	myArrow = arrow;

	setText(0, QString::number(arrow->startItem()->getInternalID()) + " -> " + QString::number(arrow->endItem()->getInternalID()) + " (" + QString::number(arrow->getPopularityInSolutions()) + ")");

	connect(arrow, SIGNAL(selectArrowInMatchList(bool)), this, SLOT(changeArrowSelection(bool)));
}

KPDGUIArrowWrapper::~KPDGUIArrowWrapper(){

}

KPDGUIArrow * KPDGUIArrowWrapper::getArrow(){
	return myArrow;
}

void KPDGUIArrowWrapper::updateText(int mode){
	if (mode == 0){
		setText(0, QString::number(myArrow->startItem()->getInternalID()) + " -> " + QString::number(myArrow->endItem()->getInternalID()) + " (" + QString::number(myArrow->getPopularityInSolutions()) + ")");
	}
	else if (mode == 1){
		setText(0, QString::number(myArrow->startItem()->getInternalID()) + " -> " + QString::number(myArrow->endItem()->getInternalID()) + " (" + QString::number(myArrow->getPopularityInStructures()) + ")");
	}
	else {
		setText(0, QString::number(myArrow->startItem()->getInternalID()) + " -> " + QString::number(myArrow->endItem()->getInternalID()));
	}
}

KPDGUIArrowLessThan::KPDGUIArrowLessThan(int mode) :myMode(mode){}

bool KPDGUIArrowLessThan::operator()(KPDGUIArrowWrapper * left, KPDGUIArrowWrapper * right) const
{
	bool toReturn;
	if (myMode == 0){
		toReturn = (left->getArrow()->getPopularityInSolutions() < right->getArrow()->getPopularityInSolutions());
	}

	else if (myMode == 1){
		toReturn = (left->getArrow()->getPopularityInStructures() < right->getArrow()->getPopularityInStructures());
	}

	else if (myMode == 2){
		int leftStartID = left->getArrow()->startItem()->getInternalID();
		int rightStartID = right->getArrow()->startItem()->getInternalID(); 
		int leftEndID = left->getArrow()->endItem()->getInternalID();
		int rightEndID = right->getArrow()->endItem()->getInternalID();

		if (leftStartID < rightStartID){
			toReturn = true;
		}
		else if (leftStartID == rightStartID){			
			if (leftEndID < rightEndID){
				toReturn = true;
			}
			else {
				toReturn = false;
			}
		}
		else {
			toReturn = false;
		}
	}

	else {		
		int leftEndID = left->getArrow()->endItem()->getInternalID();
		int rightEndID = right->getArrow()->endItem()->getInternalID();
		int leftStartID = left->getArrow()->startItem()->getInternalID();
		int rightStartID = right->getArrow()->startItem()->getInternalID();
		
		if (leftEndID < rightEndID){
			toReturn = true;
		}
		else if (leftEndID == rightEndID){			
			if (leftStartID < rightStartID){
				toReturn = true;
			}
			else {
				toReturn = false;
			}
		}
		else {
			toReturn = false;
		}
	}

	return toReturn;
}

void KPDGUIArrowWrapper::changeArrowSelection(bool selected){
	setSelected(selected);
}

KPDGUIArrowGreaterThan::KPDGUIArrowGreaterThan(int mode) :myMode(mode){}

bool KPDGUIArrowGreaterThan::operator()(KPDGUIArrowWrapper * left, KPDGUIArrowWrapper * right) const
{
	bool toReturn;
	if (myMode == 0){
		toReturn = (left->getArrow()->getPopularityInSolutions() > right->getArrow()->getPopularityInSolutions());
	}

	else if (myMode == 1){
		toReturn = (left->getArrow()->getPopularityInStructures() > right->getArrow()->getPopularityInStructures());
	}

	else if (myMode == 2){
		int leftStartID = left->getArrow()->startItem()->getInternalID();
		int rightStartID = right->getArrow()->startItem()->getInternalID();
		int leftEndID = left->getArrow()->endItem()->getInternalID();
		int rightEndID = right->getArrow()->endItem()->getInternalID();

		if (leftStartID > rightStartID){
			toReturn = true;
		}
		else if (leftStartID == rightStartID){			
			if (leftEndID > rightEndID){
				toReturn = true;
			}
			else {
				toReturn = false;
			}
		}
		else {
			toReturn = false;
		}
	}

	else {
		int leftEndID = left->getArrow()->endItem()->getInternalID();
		int rightEndID = right->getArrow()->endItem()->getInternalID();
		int leftStartID = left->getArrow()->startItem()->getInternalID();
		int rightStartID = right->getArrow()->startItem()->getInternalID();

		if (leftEndID > rightEndID){
			toReturn = true;
		}
		else if (leftEndID == rightEndID){			
			if (leftStartID > rightStartID){
				toReturn = true;
			}
			else {
				toReturn = false;
			}
		}
		else {
			toReturn = false;
		}
	}

	return toReturn;
}





