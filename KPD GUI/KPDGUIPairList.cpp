#include "KPDGUIPairList.h"

KPDGUIPairList::KPDGUIPairList(QWidget *parent) : QTreeWidget(parent){
	
}

KPDGUIPairList::~KPDGUIPairList(){

}

void KPDGUIPairList::mouseReleaseEvent(QMouseEvent *event)
{
	QTreeWidget::mouseReleaseEvent(event);

	emit mouseReleased();
}

