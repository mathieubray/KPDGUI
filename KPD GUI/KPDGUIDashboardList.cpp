#include "KPDGUIDashboardList.h"

KPDGUIDashboardList::KPDGUIDashboardList(KPDDashboardMode mode, QWidget *parent) : QTreeWidget(parent) {

	myMode = mode;

	QStringList headers;

	if (myMode == DONOR) {
		headers << "Donor ID" << "Type" << "Name" << "Matches" << "";
	}
	else if (myMode == CANDIDATE) {
		headers << "Candidate ID" << "Name" << "Matches" << "";
	}
	else if (myMode == MATCH) {
		headers << "Donor ID" << "#" << "Donor Name" << "Candidate ID" << "Candidate Name" << "Crossmatch Result" << "Five-Year Survival" << "Ten-Year Survival" << "Arrangements" << "Solutions" << "";
	}
	else {
		headers << "Node ID" << "Type" << "Name" << "Donors" << "";
	}
	
	setHeaderLabels(headers);

	header()->setSectionResizeMode(QHeaderView::ResizeToContents);

	setSortingEnabled(true);
	setMouseTracking(true);

	sortItems(0, Qt::AscendingOrder);
	setContextMenuPolicy(Qt::CustomContextMenu);
	setSelectionMode(QAbstractItemView::NoSelection);

}

KPDGUIDashboardList::~KPDGUIDashboardList() {

}

QVector<QTreeWidgetItem *> KPDGUIDashboardList::getDashboardItems() {

	QVector<QTreeWidgetItem *> items;

	for (int i = 0; i < topLevelItemCount(); i++) {
		items << topLevelItem(i);
	}

	return(items);

}

void KPDGUIDashboardList::updateText() {

	for (int i = 0; i < topLevelItemCount(); i++) {
		QTreeWidgetItem * item = topLevelItem(0);		

		if (myMode == DONOR) {
			KPDGUIDonorWrapper * wrapper = dynamic_cast<KPDGUIDonorWrapper *>(item);
			if (wrapper) {
				wrapper->updateText();
			}
		}
		else if (myMode == CANDIDATE) {
			KPDGUICandidateWrapper * wrapper = dynamic_cast<KPDGUICandidateWrapper *>(item);
			if (wrapper) {
				wrapper->updateText();
			}
		}
		else if (myMode == MATCH) {
			KPDGUIMatchWrapper * wrapper = dynamic_cast<KPDGUIMatchWrapper *>(item);
			if (wrapper) {
				wrapper->updateText();
			}
		}
		else {
			KPDGUINodeWrapper * wrapper = dynamic_cast<KPDGUINodeWrapper *>(item);
			if (wrapper) {
				wrapper->updateText();
			}
		}		
	}
}


