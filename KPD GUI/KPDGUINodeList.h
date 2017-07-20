#ifndef KPDGUINODELIST_H
#define KPDGUINODELIST_H

#include <QTreeWidget>
#include <QHeaderView>

#include "KPDGUINodeWrapper.h"


class KPDGUINodeList : public QTreeWidget
{
	Q_OBJECT

public:
	KPDGUINodeList(QWidget *parent = 0);
	~KPDGUINodeList();

public slots:
	void updateText();
	

protected:

signals:

private:

};

#endif