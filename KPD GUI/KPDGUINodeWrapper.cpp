#include "KPDGUINodeWrapper.h"

KPDGUINodeWrapper::KPDGUINodeWrapper(KPDGUINode * node){
	myNode = node;
	prevMode = 0;

	if (node->getType() == PAIR){
		setText(0, QString::number(node->getInternalID()) + ": (" + node->getDonorName() + ", " + node->getRecipName() + ")");
	}
	else {
		setText(0, QString::number(node->getInternalID()) + ": (" + node->getDonorName() + ")");
	}

	connect(node, SIGNAL(nodeSelectionChanged(int, bool)), this, SLOT(selectionActions(int, bool)));
	connect(node, SIGNAL(nodeEdited(int)), this, SLOT(editActions(int)));
}

KPDGUINodeWrapper::~KPDGUINodeWrapper(){

}

KPDGUINode * KPDGUINodeWrapper::getNode(){
	return myNode;
}

void KPDGUINodeWrapper::updateText(int mode){
	if (myNode->getType() == PAIR){
		//Sorted by ID
		if (mode == 0){
			setText(0, QString::number(myNode->getInternalID()) + ": (" + myNode->getDonorName() + ", " + myNode->getRecipName() + ")");
		}
		//By Popularity in Solutions
		else if (mode == 1){
			setText(0, QString::number(myNode->getInternalID()) + " [Popularity: " + QString::number(myNode->getPopularityInSolutions() ) + "]");
		}
		//By Popularity in Structures
		else if (mode == 2){
			setText(0, QString::number(myNode->getInternalID()) + " [Popularity: " + QString::number(myNode->getPopularityInStructures() ) + "]");
		}
		//By Compatibilities
		else if (mode == 3){
			setText(0, QString::number(myNode->getInternalID()) + " [Compatibilities: " + QString::number(myNode->getNumberOfCompatibilities() ) + "]");
		}
		//By Compatible Donors
		else if (mode == 4){
			setText(0, QString::number(myNode->getInternalID()) + " [Compatible Donors: " + QString::number(myNode->getNumberOfCompatibleDonors() ) + "]");
		}
		//By Compatible Recipients
		else if (mode == 5){
			setText(0, QString::number(myNode->getInternalID()) + " [Compatible Recipients: " + QString::number(myNode->getNumberOfCompatibleRecipients() ) + "]");
		}
		//By PRA
		else{
			setText(0, QString::number(myNode->getInternalID()) + " [PRA: " + QString::number(myNode->getRecipPRA() ) + "]");
		}
	}
	else {
		if (mode == 0){
			setText(0, QString::number(myNode->getInternalID()) + ": (" + myNode->getDonorName() + ")");
		}
		else if (mode == 1){
			setText(0, QString::number(myNode->getInternalID()) + " [Popularity: " + QString::number(myNode->getPopularityInSolutions() ) + "]");
		}
		else if (mode == 2){
			setText(0, QString::number(myNode->getInternalID()) + " [Popularity: " + QString::number(myNode->getPopularityInStructures() ) + "]");
		}
		else if (mode == 3){
			setText(0, QString::number(myNode->getInternalID()) + " [Compatibilities: " + QString::number(myNode->getNumberOfCompatibilities() ) + "]");
		}
		else if (mode == 4){
			setText(0, QString::number(myNode->getInternalID()) + " [Compatible Donors: " + QString::number(myNode->getNumberOfCompatibleDonors() ) + "]");
		}
		else if (mode == 5){
			setText(0, QString::number(myNode->getInternalID()) + " [Compatible Recipients: " + QString::number(myNode->getNumberOfCompatibleRecipients() ) + "]");
		}
		else{
			setText(0, QString::number(myNode->getInternalID()) + " [PRA: 0 (AD)]");
		}
	}
	prevMode = mode;
}

void KPDGUINodeWrapper::selectionActions(int id, bool selected){
	setSelected(selected);
}

void KPDGUINodeWrapper::editActions(int id){
	updateText(prevMode);
}


KPDGUINodeLessThan::KPDGUINodeLessThan(int mode) :myMode(mode){}

bool KPDGUINodeLessThan::operator()(KPDGUINodeWrapper * left, KPDGUINodeWrapper * right) const
{
	bool toReturn;
	if (myMode == 0){
		toReturn = (left->getNode()->getInternalID() < right->getNode()->getInternalID());
	}

	else if (myMode == 1){
		int leftPop = left->getNode()->getPopularityInSolutions();
		int rightPop = right->getNode()->getPopularityInSolutions();
		if (leftPop <= rightPop){
			if (leftPop == rightPop){
				toReturn = (left->getNode()->getInternalID() < right->getNode()->getInternalID());
			}
			else {
				toReturn = true;
			}

		}
		else {
			toReturn = false;
		}
	}

	else if (myMode == 2){
		int leftPop = left->getNode()->getPopularityInStructures();
		int rightPop = right->getNode()->getPopularityInStructures();
		if (leftPop <= rightPop){
			if (leftPop == rightPop){
				toReturn = (left->getNode()->getInternalID() < right->getNode()->getInternalID());
			}
			else {
				toReturn = true;
			}

		}
		else {
			toReturn = false;
		}
	}

	else if (myMode == 3){
		int leftComp = left->getNode()->getNumberOfCompatibilities();
		int rightComp = right->getNode()->getNumberOfCompatibilities();
		if (leftComp <= rightComp){
			if (leftComp == rightComp){
				toReturn = (left->getNode()->getInternalID() < right->getNode()->getInternalID());
			}
			else {
				toReturn = true;
			}
			
		}
		else {
			toReturn = false;
		}		
	}

	else if (myMode == 4){
		int leftComp = left->getNode()->getNumberOfCompatibleDonors();
		int rightComp = right->getNode()->getNumberOfCompatibleDonors();
		if (leftComp <= rightComp){
			if (leftComp == rightComp){
				toReturn = (left->getNode()->getInternalID() < right->getNode()->getInternalID());
			}
			else {
				toReturn = true;
			}

		}
		else {
			toReturn = false;
		}
	}

	else if (myMode == 5){
		int leftComp = left->getNode()->getNumberOfCompatibleRecipients();
		int rightComp = right->getNode()->getNumberOfCompatibleRecipients();
		if (leftComp <= rightComp){
			if (leftComp == rightComp){
				toReturn = (left->getNode()->getInternalID() < right->getNode()->getInternalID());
			}
			else {
				toReturn = true;
			}

		}
		else {
			toReturn = false;
		}
	}

	else {
		int leftType = left->getNode()->getType();
		int rightType = right->getNode()->getType();
		if (leftType != AD && rightType != AD){
			toReturn = (left->getNode()->getRecipPRA() < right->getNode()->getRecipPRA());
		}
		else if (leftType == AD && rightType == AD){
			toReturn = (left->getNode()->getInternalID() < right->getNode()->getInternalID());
		}
		else if (leftType == AD){
			toReturn = true;
		}
		else {
			toReturn = false;
		}
	}

	return toReturn;
}

KPDGUINodeGreaterThan::KPDGUINodeGreaterThan(int mode) :myMode(mode){}

bool KPDGUINodeGreaterThan::operator()(KPDGUINodeWrapper * left, KPDGUINodeWrapper * right) const
{

	bool toReturn;
	if (myMode == 0){
		toReturn = (left->getNode()->getInternalID() > right->getNode()->getInternalID());
	}

	else if (myMode == 1){
		int leftPop = left->getNode()->getPopularityInSolutions();
		int rightPop = right->getNode()->getPopularityInSolutions();
		if (leftPop >= rightPop){
			if (leftPop == rightPop){
				toReturn = (left->getNode()->getInternalID() > right->getNode()->getInternalID());
			}
			else {
				toReturn = true;
			}

		}
		else {
			toReturn = false;
		}
	}

	else if (myMode == 2){
		int leftPop = left->getNode()->getPopularityInStructures();
		int rightPop = right->getNode()->getPopularityInStructures();
		if (leftPop >= rightPop){
			if (leftPop == rightPop){
				toReturn = (left->getNode()->getInternalID() > right->getNode()->getInternalID());
			}
			else {
				toReturn = true;
			}

		}
		else {
			toReturn = false;
		}
	}

	else if (myMode == 3){
		int leftComp = left->getNode()->getNumberOfCompatibilities();
		int rightComp = right->getNode()->getNumberOfCompatibilities();
		if (leftComp >= rightComp){
			if (leftComp == rightComp){
				toReturn = (left->getNode()->getInternalID() > right->getNode()->getInternalID());
			}
			else {
				toReturn = true;
			}

		}
		else {
			toReturn = false;
		}
	}

	else if (myMode == 4){
		int leftComp = left->getNode()->getNumberOfCompatibleDonors();
		int rightComp = right->getNode()->getNumberOfCompatibleDonors();
		if (leftComp >= rightComp){
			if (leftComp == rightComp){
				toReturn = (left->getNode()->getInternalID() > right->getNode()->getInternalID());
			}
			else {
				toReturn = true;
			}

		}
		else {
			toReturn = false;
		}
	}

	else if (myMode == 5){
		int leftComp = left->getNode()->getNumberOfCompatibleRecipients();
		int rightComp = right->getNode()->getNumberOfCompatibleRecipients();
		if (leftComp >= rightComp){
			if (leftComp == rightComp){
				toReturn = (left->getNode()->getInternalID() > right->getNode()->getInternalID());
			}
			else {
				toReturn = true;
			}

		}
		else {
			toReturn = false;
		}
	}

	else {
		int leftType = left->getNode()->getType();
		int rightType = right->getNode()->getType();
		if (leftType != AD && rightType != AD){
			toReturn = (left->getNode()->getRecipPRA() > right->getNode()->getRecipPRA());
		}
		else if (leftType == AD && rightType == AD){
			toReturn = (left->getNode()->getInternalID() > right->getNode()->getInternalID());
		}
		else if (leftType == AD){
			toReturn = false;
		}
		else {
			toReturn = true;
		}
	}

	return toReturn;
}