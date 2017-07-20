#include "KPDGUIArrangementWrapper.h"

KPDGUIArrangementWrapper::KPDGUIArrangementWrapper(KPDGUIArrangement * arrangement){
	myArrangement = arrangement;
	
	//addChildren(arrangement->getItemList());	
	//setExpanded(true);

	updateText();
}

KPDGUIArrangementWrapper::~KPDGUIArrangementWrapper(){

}

KPDGUIArrangement * KPDGUIArrangementWrapper::getArrangement(){
	return myArrangement;
}

void KPDGUIArrangementWrapper::updateText() {
	
	setText(0, myArrangement->arrangementLabel());
	setText(1, QString::number(myArrangement->getUtility()));
}

bool KPDGUIArrangementWrapper::operator<(const QTreeWidgetItem &other) const {
	
	int column = treeWidget()->sortColumn();

	if (column == 0) {
		return text(0).toInt() < other.text(0).toInt();
	}
	else {
		return text(1).toDouble() < other.text(1).toDouble();
	}
	
}