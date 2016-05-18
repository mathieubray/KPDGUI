#include "KPDGUICandidateWrapper.h"

KPDGUICandidateWrapper::KPDGUICandidateWrapper(KPDGUICandidate * candidate) {
	myCandidate = candidate;

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

}


bool KPDGUICandidateWrapper::operator<(const QTreeWidgetItem &other)const {

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
}