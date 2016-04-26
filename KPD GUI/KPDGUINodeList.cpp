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

