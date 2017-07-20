#ifndef KPDGUIMATCHLIST_H
#define KPDGUIMATCHLIST_H

#include <QTreeWidget>
#include <QHeaderView>

#include "KPDGUIMatchWrapper.h"


class KPDGUIMatchList : public QTreeWidget
{
	Q_OBJECT

public:
	KPDGUIMatchList(QWidget *parent = 0);
	~KPDGUIMatchList();

public slots:
	void updateText();

protected:

signals:

private:

};

#endif