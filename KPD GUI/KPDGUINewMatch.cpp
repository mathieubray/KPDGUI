#include "KPDGUINewMatch.h"

KPDGUINewMatch::KPDGUINewMatch(KPDGUIDonor * donor, KPDGUICandidate * candidate)
{

	myDonor = donor;
	myCandidate = candidate;

	setArrowProperties(Qt::black, 10, 0.25, -1);
}


KPDGUINewMatch::~KPDGUINewMatch()
{
}


void KPDGUINewMatch::setArrowProperties(QColor color, int width, qreal opacity, int zValue) {
	
	prepareGeometryChange();
	
	setArrowColor(color);
	setArrowWidth(width);
	setArrowOpacity(opacity);
	setArrowZValue(zValue);

	setPen(QPen(myColor, myWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	setZValue(myZValue);
	setOpacity(myOpacity);

	update();

}

QRectF KPDGUINewMatch::boundingRect() const
{
	qreal extra = (pen().width() + 20) / 2.0;

	return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y())).normalized().adjusted(-extra, -extra, extra, extra);
}

QPainterPath KPDGUINewMatch::shape() const {

	QPainterPath path = QGraphicsLineItem::shape();
	path.addPolygon(arrowHead);

	return path;
}

void KPDGUINewMatch::updatePosition() {


	//qDebug() << myDonor->getCenter() << " " << myCandidate->getCenter();

	//QLineF newline(mapFromItem(myDonor, 0, 0), mapFromItem(myCandidate, 0, 0));
	
	//QLineF newline(90, 76, -87, -13);

	//QLineF line(myDonor->getCenter(), myCandidate->getCenter());
	//setLine(newline);

	QLineF newline(myDonor->pos(), myCandidate->pos());

	//QLineF line(myDonor->getCenter(), myCandidate->getCenter());
	setLine(newline);

	//qDebug() << line().p1() << " " << line().p2();

	qDebug() << "UPDATE POSITION: " << isVisible() << " " << line().p1() << " " << line().p2();
}


void KPDGUINewMatch::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

	qDebug() << "Painted!";

	QPen myPen = pen();
	myPen.setColor(myColor);
	myPen.setWidth(myWidth);
	qreal arrowSize = 6;
	painter->setPen(myPen);
	painter->setBrush(myColor);

	QPointF startPoint = myDonor->getCenter();
	QPointF endPoint = myCandidate->getCenter();	

	QLineF centerLine(startPoint, endPoint);
	//QLineF centerLine(myDonor->pos(), myCandidate->pos());
	
	
	
	/*//QPolygonF endPolygon = myCandidate->sceneBoundingRect();
	QPolygonF endPolygon = myCandidate->boundingRect();
	//QPointF p1 = endPolygon.first();
	QPointF p1 = endPolygon.first() + myCandidate->pos();
	QPointF p2;
	QPointF intersectPoint;
	QLineF polyLine;
	for (int i = 1; i < endPolygon.count(); ++i) {
		p2 = endPolygon.at(i);
		polyLine = QLineF(p1, p2);
		QLineF::IntersectType intersectType = polyLine.intersect(centerLine, &intersectPoint);
		if (intersectType == QLineF::BoundedIntersection)
			break;
		p1 = p2;
	}*/

	setLine(QLineF(endPoint, startPoint));
	//setLine(QLineF(intersectPoint, startPoint));
	//setLine(QLineF(intersectPoint, myDonor->pos()));


	double angle = ::acos(line().dx() / line().length());
	if (line().dy() >= 0)
		angle = (PI * 2) - angle;

	QPointF arrowP1 = line().p1() + QPointF(sin(angle + PI / 3) * arrowSize, cos(angle + PI / 3) * arrowSize);
	QPointF arrowP2 = line().p1() + QPointF(sin(angle + PI - PI / 3) * arrowSize, cos(angle + PI - PI / 3) * arrowSize);

	arrowHead.clear();
	arrowHead << line().p1() << arrowP1 << arrowP2;

	painter->drawLine(line());
	painter->drawPolygon(arrowHead);

	/*if (isSelected()) {
		painter->setPen(QPen(myColor, myWidth, Qt::DashLine));
		QLineF myLine = line();
		myLine.translate(0, 4.0);
		painter->drawLine(myLine);
		myLine.translate(0, -8.0);
		painter->drawLine(myLine);
	}*/

	qDebug() << "PAINT: " << line().p1() << " " << line().p2();

}
