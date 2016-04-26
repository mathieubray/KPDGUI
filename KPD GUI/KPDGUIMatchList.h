#ifndef KPDGUIMATCHLIST_H
#define KPDGUIMATCHLIST_H

#include <QTreeWidget>
#include <QHeaderView>

#include "KPDGUIMatch.h"
#include "KPDGUIMatchWrapper.h"


class KPDGUIMatchList : public QTreeWidget
{
	Q_OBJECT

public:
	KPDGUIMatchList(QWidget *parent = 0);
	~KPDGUIMatchList();

protected:
	void mouseReleaseEvent(QMouseEvent * event);
	void mouseDoubleClickEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent * event);

signals:
	void mouseReleased();

private:

};

#endif