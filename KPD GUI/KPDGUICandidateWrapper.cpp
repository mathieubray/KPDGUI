#include "KPDGUICandidateWrapper.h"

KPDGUICandidateWrapper::KPDGUICandidateWrapper(KPDGUICandidate * candidate) {
	myCandidate = candidate;

	QObject::connect(candidate, SIGNAL(candidateEdited()), this, SLOT(updateText()));

	updateText();
}

KPDGUICandidateWrapper::~KPDGUICandidateWrapper() {

}

KPDGUICandidate * KPDGUICandidateWrapper::getCandidate() {
	return myCandidate;
}

void KPDGUICandidateWrapper::updateText() {

	setText(0, QString::number(myCandidate->getID()));
	setText(1, myCandidate->getName());
	setText(2, QString::number(myCandidate->getNumberOfMatches()));

	QColor textColor;
	if (myCandidate->getStatus()) {
		textColor = QColor(0, 0, 0);
	}
	else {
		textColor = QColor(175, 175, 175);
	}

	for (int i = 0; i < columnCount(); i++) {
		setTextColor(i, textColor);
		if (i == 0 || i == 2) {
			setTextAlignment(i, Qt::AlignRight | Qt::AlignVCenter);
		}
		else {
			setTextAlignment(i, Qt::AlignLeft | Qt::AlignVCenter);
		}
	}
}

void KPDGUICandidateWrapper::candidateWrapperClickActions(QTreeWidgetItem * item) {

	if (item == this) {

		bool isSelected = myCandidate->isSelected();

		myCandidate->setSelected(!isSelected);

		emit updateVisibilitySignal();
	}
}

void KPDGUICandidateWrapper::candidateWrapperDoubleClickActions(QTreeWidgetItem * item) {

	if (item == this) {

		//DialogCandidate * dialogCandidate = new DialogCandidate(myCandidate);

		//if (dialogCandidate->exec()) {
			//myCandidate->editCandidate(dialogCandidate);
		//}

		myCandidate->edit();
	}

}


bool KPDGUICandidateWrapper::operator<(const QTreeWidgetItem &other) const {

	int column = treeWidget()->sortColumn();

	QString thisID = text(0).toInt();
	QString otherID = other.text(0).toInt();


	if (column == 0) {
		return thisID < otherID;
	}
	else if (column == 1) {

		QString thisName = text(1);
		QString otherName = other.text(1);

		if (thisName == otherName) {
			return thisID < otherID;
		}
		else {
			return thisName < otherName;
		}
	}
	else {

		QString thisMatches = text(2).toInt();
		QString otherMatches = other.text(2).toInt();

		if (thisMatches == otherMatches) {
			return thisID < otherID;
		}
		else {
			return thisMatches < otherMatches;
		}
	}

	return true;
}