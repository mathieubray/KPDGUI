#ifndef KPDGUINODELIST_H
#define KPDGUINODELIST_H

#include <QTreeWidget>
#include <QHeaderView>

#include "KPDGUINode.h"
#include "KPDGUINodeWrapper.h"

class KPDGUINodeList : public QTreeWidget
{
	Q_OBJECT

public:
	KPDGUINodeList(QWidget *parent = 0);
	~KPDGUINodeList();

protected:
	void mouseReleaseEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent * event);

signals:
	void mouseReleased();

public slots:

private:

};

#endif