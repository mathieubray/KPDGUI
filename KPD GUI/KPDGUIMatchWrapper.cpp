#include "KPDGUIMatchWrapper.h"

KPDGUIMatchWrapper::KPDGUIMatchWrapper(KPDGUIMatch * match) {
	myMatch = match;

	updateText();

	//connect(match, SIGNAL(selectArrowInMatchList(bool)), this, SLOT(changeArrowSelection(bool)));

	connect(match, SIGNAL(matchEdited()), this, SLOT(editActions()));
}

KPDGUIMatchWrapper::~KPDGUIMatchWrapper() {

}

KPDGUIMatch * KPDGUIMatchWrapper::getMatch() {
	return myMatch;
}

void KPDGUIMatchWrapper::updateText() {

	setText(0, QString::number(myMatch->getDonor()->getID()));
	setText(1, QString::number(myMatch->getCandidate()->getID()));
	setText(2, QString::number(myMatch->getMatchScore()));

}

void KPDGUIMatchWrapper::editActions(){
	updateText();
}

bool KPDGUIMatchWrapper::operator<(const QTreeWidgetItem &other)const {

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