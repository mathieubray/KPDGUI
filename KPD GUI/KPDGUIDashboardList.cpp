#include "KPDGUIDashboardList.h"

KPDGUIDashboardList::KPDGUIDashboardList(KPDDashboardMode mode, QWidget *parent) : QTreeWidget(parent) {

	myMode = mode;

	QStringList headers;

	if (myMode == DONOR) {
		headers << "Donor ID" << "Type" << "Name" << "Matches" << "Compatibility with Paired Candidate" << "";
	}
	else if (myMode == CANDIDATE) {
		headers << "Candidate ID" << "Name" << "Matches" << "";
	}
	else if (myMode == MATCH) {
		headers << "Donor ID" << "#" << "Donor Name" << "Candidate ID" << "Candidate Name" << "Crossmatch Result" << "Five-Year Survival" << "Ten-Year Survival" << "Difficult Match" << "Arrangements" << "Solutions" << "";
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

	connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(rightClickActions(QPoint)));

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

void KPDGUIDashboardList::rightClickActions(QPoint pos) {

	QTreeWidgetItem * item = itemAt(pos);

	QMenu *menu = new QMenu(this);
	QAction * editAction = new QAction("Edit", this);
	QAction * addAdditionalDonorAction = new QAction("Add Additional Donor", this);

	if (myMode == DONOR) {
		KPDGUIDonorWrapper * wrapper = dynamic_cast<KPDGUIDonorWrapper *>(item);
		if (wrapper) {

			connect(editAction, SIGNAL(triggered()), wrapper->getDonor(), SLOT(edit()));
			menu->addAction(editAction);
		}
	}
	else if (myMode == CANDIDATE) {
		KPDGUICandidateWrapper * wrapper = dynamic_cast<KPDGUICandidateWrapper *>(item);
		if (wrapper) {

			connect(editAction, SIGNAL(triggered()), wrapper->getCandidate(), SLOT(edit()));
			connect(addAdditionalDonorAction, SIGNAL(triggered()), wrapper->getCandidate(), SLOT(addAdditionalDonor()));

			menu->addAction(editAction);
			menu->addAction(addAdditionalDonorAction);
		}
	}
	else if (myMode == MATCH) {
		KPDGUIMatchWrapper * wrapper = dynamic_cast<KPDGUIMatchWrapper *>(item);
		if (wrapper) {

			connect(editAction, SIGNAL(triggered()), wrapper->getMatch(), SLOT(edit()));

			menu->addAction(editAction);
		}
	}
	else {
		KPDGUINodeWrapper * wrapper = dynamic_cast<KPDGUINodeWrapper *>(item);
		if (wrapper) {

			connect(editAction, SIGNAL(triggered()), wrapper->getNode(), SLOT(edit()));
			menu->addAction(editAction);
		
			if (!wrapper->getNode()->getFirstDonor()->isAltruistic()) {
				connect(addAdditionalDonorAction, SIGNAL(triggered()), wrapper->getNode()->getCandidate(), SLOT(addAdditionalDonor()));
				menu->addAction(addAdditionalDonorAction);
			}

		}
	}

	if (menu->actions().size() > 0) {
		menu->popup(viewport()->mapToGlobal(pos));
	}
}


