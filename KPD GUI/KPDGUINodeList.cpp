#include "KPDGUINodeList.h"

KPDGUINodeList::KPDGUINodeList(QWidget *parent) : QTreeWidget(parent){
	
	QStringList headers;
	headers << "Node" << "Type" << "Name" << "Donors";
	setHeaderLabels(headers);
	
	header()->resizeSection(0, 50);
	header()->resizeSection(1, 50);
	header()->resizeSection(2, 120);
	header()->resizeSection(3, 50);
	
	setSortingEnabled(true);
	setMouseTracking(true);
	
	sortItems(0, Qt::AscendingOrder);
	setContextMenuPolicy(Qt::CustomContextMenu);

}

KPDGUINodeList::~KPDGUINodeList(){

}

void KPDGUINodeList::mouseReleaseEvent(QMouseEvent *event)
{
	QTreeWidget::mouseReleaseEvent(event);

	emit mouseReleased();
}

void KPDGUINodeList::mouseMoveEvent(QMouseEvent *event)
{

	for (int i = 0; i < topLevelItemCount(); i++) {
		KPDGUINodeWrapper * node = dynamic_cast<KPDGUINodeWrapper *>(topLevelItem(i));
		if (node) {
			node->getNode()->clearHighlight();
		}
	}

	QTreeWidgetItem * item = itemAt(event->localPos().x(), event->localPos().y());

	if (item != 0) {
		
		KPDGUINodeWrapper * node = dynamic_cast<KPDGUINodeWrapper *>(item);
		if (node) {
			node->getNode()->highlightNode();
		}
	}

	QTreeWidget::mouseMoveEvent(event);
}


