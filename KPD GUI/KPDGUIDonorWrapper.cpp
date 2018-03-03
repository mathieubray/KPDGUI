#include "KPDGUIDonorWrapper.h"

KPDGUIDonorWrapper::KPDGUIDonorWrapper(KPDGUIDonor * donor) {
	myDonor = donor;

	QObject::connect(donor, SIGNAL(donorEdited()), this, SLOT(updateText()));

	updateText();
}

KPDGUIDonorWrapper::~KPDGUIDonorWrapper() {

}

KPDGUIDonor * KPDGUIDonorWrapper::getDonor() {
	return myDonor;
}

void KPDGUIDonorWrapper::updateText() {

	setText(0, QString::number(myDonor->getID()));
	setText(1, KPDFunctions::donorTypeToString(myDonor->isAltruistic()));
	setText(2, myDonor->getName());
	setText(3, QString::number(myDonor->getNumberOfMatches()));
	setText(4, KPDFunctions::toString(myDonor->getCompatibilityWithPairedCandidate()));

	QColor textColor;
	if (myDonor->getStatus()) {
		textColor = QColor(0, 0, 0);
	}
	else {
		textColor = QColor(175, 175, 175);
	}

	for (int i = 0; i < columnCount(); i++) {
		setTextColor(i, textColor);
		if (i == 0 || i == 3) {
			setTextAlignment(i, Qt::AlignRight | Qt::AlignVCenter);
		}
		else {
			setTextAlignment(i, Qt::AlignLeft | Qt::AlignVCenter);
		}
	}
}

void KPDGUIDonorWrapper::donorWrapperClickActions(QTreeWidgetItem * item) {

	if (item == this) {

		bool isSelected = false;

		if (myDonor->isAltruistic()) {
			isSelected = myDonor->isSelected();
		}
		else {
			isSelected = myDonor->getParentNode()->getCandidate()->isSelected();
		}

		myDonor->setSelected(!isSelected);
		
		if (!myDonor->isAltruistic()) {
			myDonor->getParentNode()->setSelected(!isSelected);
		}
		
		emit updateVisibilitySignal();
	}
}

void KPDGUIDonorWrapper::donorWrapperDoubleClickActions(QTreeWidgetItem * item) {

	if (item == this) {

		//DialogDonor * dialogDonor = new DialogDonor(myDonor);

		//if (dialogDonor->exec()) {
			//myDonor->editDonor(dialogDonor);
		//}

		myDonor->edit();
	}

}


bool KPDGUIDonorWrapper::operator<(const QTreeWidgetItem &other) const {

	int column = treeWidget()->sortColumn();

	QString thisID = text(0).toInt();
	QString otherID = other.text(0).toInt();


	if (column == 0) {
		return thisID < otherID;
	}
	else if (column == 1) {

		QString thisType = text(1);
		QString otherType = other.text(1);

		if (thisType == otherType) {
			return thisID < otherID;
		}
		else {
			return thisType < otherType;
		}
	}
	else if (column == 2) {

		QString thisName = text(2);
		QString otherName = other.text(2);

		if (thisName == otherName) {
			return thisID < otherID;
		}
		else {
			return thisName < otherName;
		}
	}
	else {

		QString thisMatches = text(3).toInt();
		QString otherMatches = other.text(3).toInt();

		if (thisMatches == otherMatches) {
			return thisID < otherID;
		}
		else {
			return thisMatches < otherMatches;
		}		
	}
}