#include "KPDGUIArrowWrapper.h"

KPDGUIArrowWrapper::KPDGUIArrowWrapper(KPDGUIArrow * arrow){
	myArrow = arrow;

	updateText();

	//setText(0, QString::number(arrow->startItem()->getInternalID()) + " -> " + QString::number(arrow->endItem()->getInternalID()) + " (" + QString::number(arrow->getPopularityInSolutions()) + ")");

	//connect(arrow, SIGNAL(selectArrowInMatchList(bool)), this, SLOT(changeArrowSelection(bool)));
}

KPDGUIArrowWrapper::~KPDGUIArrowWrapper(){

}

KPDGUIArrow * KPDGUIArrowWrapper::getArrow(){
	return myArrow;
}

void KPDGUIArrowWrapper::updateText(){
	
	setText(0, QString::number(myArrow->startItem()->getInternalID()));
	setText(1, QString::number(myArrow->endItem()->getInternalID()));
	setText(2, QString::number(myArrow->getPopularityInStructures()));
	setText(3, QString::number(myArrow->getPopularityInSolutions()));

}


bool KPDGUIArrowWrapper::operator<(const QTreeWidgetItem &other)const {

	int column = treeWidget()->sortColumn();

	QString fromNode = text(0).toInt();
	QString otherFromNode = other.text(0).toInt();

	QString toNode = text(1).toInt();
	QString otherToNode = other.text(1).toInt();

	if (column == 0){
		if (fromNode == otherFromNode){
			return toNode < otherToNode;
		}
		else {
			return fromNode < otherFromNode;
		}
	}
	else if (column == 1){
		if (toNode == otherToNode){
			return fromNode < otherFromNode;
		}
		else {
			return toNode < otherToNode;
		}
	}
	else {

		QString popularity = text(column).toInt();
		QString otherPopularity = other.text(column).toInt();

		if (popularity == otherPopularity){

			if (fromNode == otherFromNode){
				return toNode < otherToNode;
			}
			else {
				return fromNode < otherFromNode;
			}
		}
		else {
			return popularity < otherPopularity;
		}
	}

}