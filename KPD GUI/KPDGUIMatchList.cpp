#include "KPDGUIMatchList.h"

KPDGUIMatchList::KPDGUIMatchList(QWidget *parent) : QTreeWidget(parent) {

	QStringList headers;
	headers << "Donor ID" << "Number" << "Donor Name" << "Candidate ID" << "Candidate Name" << "Crossmatch Result" << "Five-Year Survival" << "Ten-Year Survival" << "Structures" << "Solutions" << "";
	setHeaderLabels(headers);
	
	header()->setSectionResizeMode(QHeaderView::ResizeToContents);

	setSortingEnabled(true);
	setMouseTracking(true);

	sortItems(0, Qt::AscendingOrder);
	setContextMenuPolicy(Qt::CustomContextMenu);
	setSelectionMode(QAbstractItemView::NoSelection);

}

KPDGUIMatchList::~KPDGUIMatchList() {

}

void KPDGUIMatchList::updateText() {
	
	for (int i = 0; i < topLevelItemCount(); i++) {
		QTreeWidgetItem * item = topLevelItem(0);

		KPDGUIMatchWrapper * wrapper = dynamic_cast<KPDGUIMatchWrapper *>(item);
		if (wrapper) {
			wrapper->updateText();
		}
	}	

}


