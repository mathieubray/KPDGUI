#include "KPDGUIMatchList.h"

KPDGUIMatchList::KPDGUIMatchList(QWidget *parent) : QTreeWidget(parent) {

	QStringList headers;
	headers << "Donor" << "Candidate" << "Score";
	setHeaderLabels(headers);

	header()->resizeSection(0, 50);
	header()->resizeSection(1, 75);
	header()->resizeSection(2, 50);

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

void KPDGUIMatchList::mouseDoubleClickEvent(QMouseEvent *event)
{
	QTreeWidgetItem * item = itemAt(event->localPos().x(), event->localPos().y());

	KPDGUIMatchWrapper * match = dynamic_cast<KPDGUIMatchWrapper *>(item);
	if (match) {
		match->getMatch()->editMatch();
	}

	QTreeWidget::mouseDoubleClickEvent(event);
}

void KPDGUIMatchList::mouseMoveEvent(QMouseEvent *event)
{

	for (int i = 0; i < topLevelItemCount(); i++) {
		KPDGUIMatchWrapper * match = dynamic_cast<KPDGUIMatchWrapper *>(topLevelItem(i));
		if (match) {
			match->getMatch()->clearHighlight();
		}
	}

	QTreeWidgetItem * item = itemAt(event->localPos().x(), event->localPos().y());

	if (item != 0) {

		KPDGUIMatchWrapper * match = dynamic_cast<KPDGUIMatchWrapper *>(item);
		if (match) {
			match->getMatch()->highlightMatch(1);
		}
	}

	QTreeWidget::mouseMoveEvent(event);
}

