#ifndef KPDGUICLOUD_H
#define KPDGUICLOUD_H

#include <QtGui>
#include <QtWidgets>

#include "KPDGUINode.h"

class KPDGUICloud : public QObject, public QGraphicsItemGroup
{
	Q_OBJECT

public:
	KPDGUICloud(int id, int donors);
	~KPDGUICloud();

	void addDonor();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget *widget);
	
private:
	QGraphicsRectItem* myRecip;
	QVector<QGraphicsEllipseItem *> myDonors;

	void setBackgroundColor();

	int myID;

	QColor myBackgroundColor;
	QColor myTextColor;
	QColor myOutlineColor;
};

#endif

