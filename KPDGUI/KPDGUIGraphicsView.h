#ifndef KPDGUIGRAPHICSVIEW_H
#define KPDGUIGRAPHICSVIEW_H

#include <QWheelEvent>
#include <QGraphicsView>
#include <QDebug>

class KPDGUIGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	KPDGUIGraphicsView(QWidget *parent = 0);
	~KPDGUIGraphicsView();

	void changeMode(int i);

protected:
	void wheelEvent(QWheelEvent *event);

public slots:
	void centerView(int x, int y);

signals:
	void zoomIn();
	void zoomOut();
	
private:
	int mode;
};

#endif
