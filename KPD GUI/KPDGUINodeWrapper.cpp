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
	//setSelected(myNode->isSelected());
}

void KPDGUINodeWrapper::updateText(){
	
	setText(0, QString::number(myNode->getID()));
	setText(1, KPDFunctions::toString(myNode->getType()));
	setText(2, myNode->getNodeListString());
	setText(3, QString::number(myNode->getNumberOfDonors()));
	
	QColor textColor;
	if (myNode->getStatus()) {
		textColor = QColor(0, 0, 0);
	}
	else {
		textColor = QColor(175, 175, 175);
	}

	for (int i = 0; i < columnCount(); i++){
		setTextColor(i, textColor);
		if (i == 0 || i == 3) {
			setTextAlignment(i, Qt::AlignHCenter | Qt::AlignVCenter);
		}
		else {
			setTextAlignment(i, Qt::AlignLeft | Qt::AlignVCenter);
		}
	}

}

bool KPDGUINodeWrapper::operator<(const QTreeWidgetItem &other)const {
	
	int column = treeWidget()->sortColumn();

	int thisID = text(0).toInt();
	int otherID = other.text(0).toInt();

	if (column == 0){
		return thisID < otherID;
	}
	else if (column == 1) {
		
		QString thisType = text(column).toLower();
		QString otherType = other.text(column).toLower();

		if (thisType == otherType) {
			return thisID < otherID;
		}
		else {
			return thisType < otherType;
		}
	}
	else if (column == 2) {

		QString thisName = text(column).toLower();
		QString otherName = other.text(column).toLower();

		if (thisName == otherName) {
			return thisID < otherID;
		}
		else {
			return thisName < otherName;
		}
	}

	else {

		QString thisMatches = text(column).toInt();
		QString otherMatches = other.text(column).toInt();

		if (thisMatches == otherMatches) {
			return thisID < otherID;
		}
		else {
			return thisMatches < otherMatches;
		}
	}
}
