#ifndef KPDGUINODELIST_H
#define KPDGUINODELIST_H

#include <QTreeWidget>


class KPDGUINodeList : public QTreeWidget
{
	Q_OBJECT

public:
	KPDGUINodeList(QWidget *parent = 0);
	~KPDGUINodeList();

protected:
	void mouseReleaseEvent(QMouseEvent * event);
	void mouseHoverEvent(QMouseEvent * event);

signals:
	void mouseReleased();

private:

};

#endif