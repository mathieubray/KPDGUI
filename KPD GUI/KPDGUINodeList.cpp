#include "KPDGUINodeList.h"

KPDGUINodeList::KPDGUINodeList(QWidget *parent) : QTreeWidget(parent){
	
}

KPDGUINodeList::~KPDGUINodeList(){

}

void KPDGUINodeList::mouseReleaseEvent(QMouseEvent *event)
{
	QTreeWidget::mouseReleaseEvent(event);

	emit mouseReleased();
}

