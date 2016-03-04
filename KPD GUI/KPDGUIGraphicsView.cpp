#include "KPDGUIGraphicsView.h"

KPDGUIGraphicsView::KPDGUIGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
	setBackgroundBrush(QBrush(Qt::lightGray, Qt::Dense7Pattern));
	mode = 0;
}

KPDGUIGraphicsView::~KPDGUIGraphicsView()
{

}

void KPDGUIGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
	QGraphicsView::mouseReleaseEvent(event);

	emit mouseReleased();
}

void KPDGUIGraphicsView::wheelEvent(QWheelEvent *event){
	if (mode == 0){
		QGraphicsView::wheelEvent(event);
	}
	else {
		if (event->delta() > 0){
			emit zoomIn();
		}
		else {
			emit zoomOut();
		}
	}

}

void KPDGUIGraphicsView::changeMode(int i){
	mode = i;
}