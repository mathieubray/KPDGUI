#ifndef KPDGUIDASHBOARDLIST_H
#define KPDGUIDASHBOARDLIST_H

#include<QtGui>
#include<QtWidgets>

#include "KPDGUINodeWrapper.h"
#include "KPDGUIDonorWrapper.h"
#include "KPDGUICandidateWrapper.h"
#include "KPDGUIMatchWrapper.h"


class KPDGUIDashboardList : public QTreeWidget
{
	Q_OBJECT

public:
	KPDGUIDashboardList(KPDDashboardMode mode = NODE, QWidget *parent = 0);
	~KPDGUIDashboardList();

	QVector<QTreeWidgetItem *> getDashboardItems();

public slots:
	void updateText();

	void rightClickActions(QPoint pos);
	
private:
	KPDDashboardMode myMode;

};

#endif