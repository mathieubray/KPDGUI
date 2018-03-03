#include "KPDGUINodeWrapper.h"

KPDGUINodeWrapper::KPDGUINodeWrapper(KPDGUINode * node) {
	myNode = node;

	if (node->getType() == PAIR){
		QObject::connect(node->getCandidate(), SIGNAL(candidateEdited()), this, SLOT(updateText()));
	}

	foreach(KPDGUIDonor * donor, node->getDonors()) {
		QObject::connect(donor, SIGNAL(donorEdited()), this, SLOT(updateText()));
	}

	updateText();
}

KPDGUINodeWrapper::~KPDGUINodeWrapper(){

}

KPDGUINode * KPDGUINodeWrapper::getNode(){
	return myNode;
}

void KPDGUINodeWrapper::updateText(){
	
	setText(0, QString::number(myNode->getID()));
	setText(1, KPDFunctions::toString(myNode->getType()));
	setText(2, myNode->getNodeListString());
	setText(3, QString::number(myNode->getNumberOfDonors()));
	setText(4, "");
	
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
			setTextAlignment(i, Qt::AlignRight | Qt::AlignVCenter);
		}
		else {
			setTextAlignment(i, Qt::AlignLeft | Qt::AlignVCenter);
		}
	}

}

void KPDGUINodeWrapper::nodeWrapperClickActions(QTreeWidgetItem * item) {

	if (item == this) {

		bool isSelected = myNode->getFirstDonor()->isSelected();

		myNode->setSelected(!isSelected);

		emit updateVisibilitySignal();
	}
}

void KPDGUINodeWrapper::nodeWrapperDoubleClickActions(QTreeWidgetItem * item) {

	if (item == this) {
		/*if (myNode->getType() == PAIR) {
			DialogCandidate * dialogCandidate = new DialogCandidate(myNode->getCandidate());
			if (dialogCandidate->exec()) {
				myNode->getCandidate()->editCandidate(dialogCandidate);
			}

			foreach(KPDGUIDonor * donor, myNode->getDonors()) {
				DialogDonor * dialogDonor = new DialogDonor(donor);
				if (dialogDonor->exec()) {
					donor->editDonor(dialogDonor);
				}
			}
		}
		else {
			DialogDonor * dialogDonor = new DialogDonor(myNode->getFirstDonor());
			if (dialogDonor->exec()) {
				myNode->getFirstDonor()->editDonor(dialogDonor);
			}
		}*/

		myNode->edit();
	}

}

bool KPDGUINodeWrapper::operator<(const QTreeWidgetItem &other) const {
	
	int column = treeWidget()->sortColumn();

	int thisID = text(0).toInt();
	int otherID = other.text(0).toInt();

	if (column == 1) {
		
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

	else if (column == 3) {

		QString thisMatches = text(column).toInt();
		QString otherMatches = other.text(column).toInt();

		if (thisMatches == otherMatches) {
			return thisID < otherID;
		}
		else {
			return thisMatches < otherMatches;
		}
	}

	else {
		return thisID < otherID;
	}
}
