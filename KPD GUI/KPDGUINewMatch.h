#ifndef KPDGUINEWMATCH_H
#define KPDGUINEWMATCH_H

#include<QGraphicsLineItem>
#include<QPen>
#include<QDebug>
#include<QPainter>

#include "EnumsFunctions.h"
#include "KPDGUINode.h"

class KPDGUINewMatch : public QObject, public QGraphicsLineItem
{

	Q_OBJECT;


private:

	KPDGUIDonor * myDonor;
	KPDGUICandidate * myCandidate;

	QColor myColor;
	int myWidth;
	qreal myOpacity;
	int myZValue;

	QPolygonF arrowHead;


protected:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

public:
	enum { Type = UserType + 4 };

	KPDGUINewMatch(KPDGUIDonor * donor, KPDGUICandidate * candidate);
	~KPDGUINewMatch();

	KPDGUIDonor * getDonor() const { return myDonor; }
	KPDGUICandidate *getCandidate() const { return myCandidate; }

	void setArrowColor(const QColor &color) { myColor = color; }
	void setArrowWidth(int width) { myWidth = width; }
	void setArrowOpacity(qreal opacity) { myOpacity = opacity; }
	void setArrowZValue(int zValue) { myZValue = zValue; }

	void setArrowProperties(QColor color, int width, qreal opacity, int zValue);


	//Visual Arrow Properties
	QRectF boundingRect() const;
	QPainterPath shape() const;
	void updatePosition();
	int type() const { return Type; }

};

#endif

