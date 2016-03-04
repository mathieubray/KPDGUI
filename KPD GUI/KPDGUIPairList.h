#ifndef KPDGUIPAIRLIST_H
#define KPDGUIPAIRLIST_H

#include <QTreeWidget>


class KPDGUIPairList : public QTreeWidget
{
	Q_OBJECT

public:
	KPDGUIPairList(QWidget *parent = 0);
	~KPDGUIPairList();

protected:
	void mouseReleaseEvent(QMouseEvent * event);

signals:
	void mouseReleased();

private:

};

#endif