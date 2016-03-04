#ifndef KPDGUIGRAPHICSVIEW_H
#define KPDGUIGRAPHICSVIEW_H

#include <QWheelEvent>
#include <QGraphicsView>

class KPDGUIGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	KPDGUIGraphicsView(QWidget *parent = 0);
	~KPDGUIGraphicsView();

	void changeMode(int i);

protected:
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

signals:
	void mouseReleased();
	void zoomIn();
	void zoomOut();
	
private:

	int mode;
};

#endif
