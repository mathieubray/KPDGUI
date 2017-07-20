#include "KPDGUINodeList.h"

KPDGUINodeList::KPDGUINodeList(QWidget *parent) : QTreeWidget(parent){
	
	QStringList headers;
	headers << "Node" << "Type" << "Name" << "Donors" << "";
	setHeaderLabels(headers);
	
	header()->setSectionResizeMode(QHeaderView::ResizeToContents);
			
	setSortingEnabled(true);
	setMouseTracking(true);
	
	sortItems(0, Qt::AscendingOrder);
	setContextMenuPolicy(Qt::CustomContextMenu);
	setSelectionMode(QAbstractItemView::NoSelection);

}

KPDGUINodeList::~KPDGUINodeList(){

}

void KPDGUINodeList::updateText() {

	for (int i = 0; i < topLevelItemCount(); i++) {
		QTreeWidgetItem * item = topLevelItem(0);

		KPDGUINodeWrapper * wrapper = dynamic_cast<KPDGUINodeWrapper *>(item);
		if (wrapper) {
			wrapper->updateText();
		}
	}


}


