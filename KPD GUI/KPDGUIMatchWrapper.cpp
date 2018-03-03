#include "KPDGUIMatchWrapper.h"

KPDGUIMatchWrapper::KPDGUIMatchWrapper(KPDGUIMatch * match){
	myMatch = match;

	QObject::connect(match->getCandidate(), SIGNAL(candidateEdited()), this, SLOT(updateText()));
	QObject::connect(match->getDonor(), SIGNAL(donorEdited()), this, SLOT(updateText()));

	updateText();
}

KPDGUIMatchWrapper::~KPDGUIMatchWrapper(){

}

KPDGUIMatch * KPDGUIMatchWrapper::getMatch(){
	return myMatch;
}

void KPDGUIMatchWrapper::updateText(){

	QString difficultyString = "No";

	if (myMatch->getTransplantScore() == 1) {
		difficultyString = "Yes";
	}

	
	setText(0, QString::number(myMatch->getDonor()->getID()));
	setText(1, QString::number(myMatch->getDonor()->getDonorNumber()));
	setText(2, myMatch->getDonor()->getName());
	setText(3, QString::number(myMatch->getCandidate()->getID()));
	setText(4, myMatch->getCandidate()->getName());
	setText(5, KPDFunctions::toString(myMatch->getCrossmatchResult()));
	setText(6, QString::number(floor(myMatch->getFiveYearSurvival() * 1000 + 0.5) / 1000));
	setText(7, QString::number(floor(myMatch->getTenYearSurvival() * 1000 + 0.5) / 1000));
	setText(8, difficultyString);
	setText(9, QString::number(myMatch->getPopularityInArrangements()));
	setText(10, QString::number(myMatch->getPopularityInSolutions()));
	setText(11, "");

	QColor textColor;
	if (myMatch->getInclude()) {
		textColor = QColor(0, 0, 0);
	}
	else {
		textColor = QColor(175, 175, 175);
	}

	for (int i = 0; i < columnCount(); i++) {
		setTextColor(i, textColor);
		if (i == 6 || i == 7 || i == 8 || i ==9 || i == 10) {
			setTextAlignment(i, Qt::AlignRight | Qt::AlignVCenter);
		}
		else {
			setTextAlignment(i, Qt::AlignLeft | Qt::AlignVCenter);
		}
	}

}

void KPDGUIMatchWrapper::matchWrapperClickActions(QTreeWidgetItem * item) {

	if (item == this) {

		bool donorIsSelected = false;

		if (myMatch->getDonor()->isAltruistic()) {
			donorIsSelected = myMatch->getDonor()->isSelected() || myMatch->getDonor()->isSelected();
		}
		else {
			donorIsSelected = myMatch->getDonor()->isSelected() || myMatch->getDonor()->getParentNode()->getCandidate()->isSelected();
		}

		bool candidateIsSelected = myMatch->getCandidate()->isSelected();

		if (donorIsSelected && candidateIsSelected) {
			/*myMatch->getDonor()->setSelected(false);
			if (!myMatch->getDonor()->isAltruistic()) {
				myMatch->getDonor()->getParentNode()->getCandidate()->setSelected(false);
			}*/

			myMatch->getDonor()->getParentNode()->setSelected(false);

			myMatch->getCandidate()->setSelected(false);
		}
		else {
			//if (!donorIsSelected) {
				/*myMatch->getDonor()->setSelected(true);
				if (!myMatch->getDonor()->isAltruistic()) {
					myMatch->getDonor()->getParentNode()->getCandidate()->setSelected(true);
				}*/
				myMatch->getDonor()->getParentNode()->setSelected(true);
			//}

			//if (!candidateIsSelected) {
				myMatch->getCandidate()->setSelected(true);
			//}
		}

		emit updateVisibilitySignal();
	}
}

void KPDGUIMatchWrapper::matchWrapperDoubleClickActions(QTreeWidgetItem * item) {

	if (item == this) {

		myMatch->edit();

		//DialogMatch * dialogMatch = new DialogMatch(myMatch);

		//if (dialogMatch->exec()) {
			//myMatch->editMatch(dialogMatch);
		//}
	}

}

bool KPDGUIMatchWrapper::operator<(const QTreeWidgetItem &other) const {

	int column = treeWidget()->sortColumn();

	int donorNodeID = text(0).toInt();
	int otherDonorNodeID = other.text(0).toInt();

	int donorNumber = text(1).toInt();
	int otherDonorNumber = other.text(1).toInt();

	QString donorName = text(2);
	QString otherDonorName = other.text(2);

	int candidateNodeID = text(3).toInt();
	int otherCandidateNodeID = other.text(3).toInt();

	QString candidateName = text(4);
	QString otherCandidateName = other.text(4);

	if (column == 0 && column == 1) {

		if (donorNodeID == otherDonorNodeID) {
			if (donorNumber == otherDonorNumber) {
				return candidateNodeID < otherCandidateNodeID;
			}
			else {
				return donorNumber < otherDonorNumber;
			}
		}
		else {
			return donorNodeID < otherDonorNodeID;
		}

	}

	else if (column == 2) {
		if (donorName == otherDonorName) {
			return candidateName < otherCandidateName;
		}
		else {
			return donorName < otherDonorName;
		}
	}

	else if (column == 3) {

		if (candidateNodeID == otherCandidateNodeID) {
			if (donorNodeID == otherDonorNodeID) {
				return donorNumber < otherDonorNumber;
			}
			else {
				return donorNodeID < otherDonorNodeID;
			}
		}
		else {
			return candidateNodeID < otherCandidateNodeID;
		}

	}

	else if (column == 4) {
		if (candidateName == otherCandidateName) {
			return donorName < otherDonorName;
		}
		else {
			return candidateName < otherCandidateName;
		}
	}

	else if (column == 6 || column == 7 || column == 9 || column == 10) {

		double fromValue = text(column).toDouble();
		double otherValue = other.text(column).toDouble();

		if (fromValue == otherValue) {
			if (donorNodeID == otherDonorNodeID) {
				if (donorNumber == otherDonorNumber) {
					return candidateNodeID < otherCandidateNodeID;
				}
				else {
					return donorNumber < otherDonorNumber;
				}
			}
			else {
				return donorNodeID < otherDonorNodeID;
			}
		}
		else {
			return fromValue < otherValue;
		}
	}

	else {

		QString fromValue = text(column);
		QString otherValue = other.text(column);

		if (fromValue == otherValue) {
			if (donorNodeID == otherDonorNodeID) {
				if (donorNumber == otherDonorNumber) {
					return candidateNodeID < otherCandidateNodeID;
				}
				else {
					return donorNumber < otherDonorNumber;
				}
			}
			else {
				return donorNodeID < otherDonorNodeID;
			}
		}
		else {
			return fromValue < otherValue;
		}

	}
	

}