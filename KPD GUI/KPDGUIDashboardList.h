#ifndef KPDGUIDASHBOARDLIST_H
#define KPDGUIDASHBOARDLIST_H

#include<QtGui>
#include<QtWidgets>

#include "KPDGUINodeWrapper.h"
#include "KPDGUIDonorWrapper.h"
#include "KPDGUICandidateWrapper.h"
#include "KPDGUIMatchWrapper.h"

#include "KPDGUIGraphicsView.h"


class KPDGUIDashboardList : public QTreeWidget
{
	Q_OBJECT

public:
	KPDGUIDashboardList(KPDDashboardMode mode = NODE, QWidget *parent = 0);
	~KPDGUIDashboardList();

	QVector<QTreeWidgetItem *> getDashboardItems();

signals:
	void recenterView(int x, int y);

public slots:
	void updateText();

	void clickActions(QTreeWidgetItem * item);
	void rightClickActions(QPoint pos);
	
private:
	KPDDashboardMode myMode;

};

#endif