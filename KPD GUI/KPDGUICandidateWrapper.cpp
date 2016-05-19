#include "KPDGUICandidateWrapper.h"

KPDGUICandidateWrapper::KPDGUICandidateWrapper(KPDGUICandidate * Candidate) {
	myCandidate = Candidate;

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

	/*int column = treeWidget()->sortColumn();

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
	}*/

	return true;
}