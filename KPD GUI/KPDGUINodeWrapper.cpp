#include "KPDGUINodeWrapper.h"

KPDGUINodeWrapper::KPDGUINodeWrapper(KPDGUINode * node){
	myNode = node;

	updateText();

	//connect(node, SIGNAL(nodeSelectionChanged(int, bool)), this, SLOT(selectionActions(int, bool)));
	//connect(node, SIGNAL(nodeEdited(int)), this, SLOT(editActions(int)));
}

KPDGUINodeWrapper::~KPDGUINodeWrapper(){

}

KPDGUINode * KPDGUINodeWrapper::getNode(){
	return myNode;
}

/*void KPDGUINodeWrapper::selectionActions(int id, bool selected){
	setSelected(selected);
}

void KPDGUINodeWrapper::editActions(int id){
	//updateText(prevMode);
}*/

void KPDGUINodeWrapper::updateSelections(){
	//qDebug() << "Update Selections";
	setSelected(myNode->isSelected());
}

void KPDGUINodeWrapper::updateText(){
	
	setText(0, QString::number(myNode->getInternalID()));
	setText(1, myNode->getNameString());
	setText(2, QString::number(myNode->getNumberOfAssociatedDonors()));
	setText(3, QString::number(myNode->getPopularityInStructures()));
	setText(4, QString::number(myNode->getPopularityInSolutions()));
	setText(5, QString::number(myNode->getNumberOfCompatibleDonors()));
	setText(6, QString::number(myNode->getNumberOfCompatibleRecipients()));

	for (int i = 0; i < columnCount(); i++){
		setTextAlignment(i, Qt::AlignHCenter | Qt::AlignVCenter);
	}

}

bool KPDGUINodeWrapper::operator<(const QTreeWidgetItem &other)const {
	
	int column = treeWidget()->sortColumn();

	int id = text(0).toInt();
	int otherID = other.text(0).toInt();

	if (column == 0){
		return id < otherID;
	}
	else {
		QString thisText = text(column).toLower();
		QString otherText = other.text(column).toLower();

		if (column == 1){
			if (thisText == otherText){
				return id < otherID;
			}
			else {
				return thisText < otherText;
			}
		}
		else {
			int value = thisText.toInt();
			int otherValue = otherText.toInt();

			if (value == otherValue){
				return id < otherID;
			}
			else {
				return value < otherValue;
			}
		}
	}
}
