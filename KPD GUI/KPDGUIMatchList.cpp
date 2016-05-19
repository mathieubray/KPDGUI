#include "KPDGUIMatchList.h"

KPDGUIMatchList::KPDGUIMatchList(QWidget *parent) : QTreeWidget(parent) {

	QStringList headers;
	headers << "Match" << "Type" << "Name" << "Donors";
	setHeaderLabels(headers);

	header()->resizeSection(0, 50);
	header()->resizeSection(1, 50);
	header()->resizeSection(2, 120);

	setSortingEnabled(true);
	setMouseTracking(true);

	sortItems(0, Qt::AscendingOrder);
	setContextMenuPolicy(Qt::CustomContextMenu);

}

KPDGUIMatchList::~KPDGUIMatchList() {

}

void KPDGUIMatchList::mouseReleaseEvent(QMouseEvent *event)
{
	QTreeWidget::mouseReleaseEvent(event);

	emit mouseReleased();
}

void KPDGUIMatchList::mouseMoveEvent(QMouseEvent *event)
{

	/*for (int i = 0; i < topLevelItemCount(); i++) {
		KPDGUIMatchWrapper * Match = dynamic_cast<KPDGUIMatchWrapper *>(topLevelItem(i));
		if (Match) {
			Match->getMatch()->clearHighlight();
		}
	}

	QTreeWidgetItem * item = itemAt(event->localPos().x(), event->localPos().y());

	if (item != 0) {

		KPDGUIMatchWrapper * Match = dynamic_cast<KPDGUIMatchWrapper *>(item);
		if (Match) {
			Match->getMatch()->highlightMatch();
		}
	}*/

	QTreeWidget::mouseMoveEvent(event);
}


