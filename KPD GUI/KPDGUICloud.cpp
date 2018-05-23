#include "KPDGUICloud.h"


//const qreal PI = 3.14159265;

KPDGUICloud::KPDGUICloud(int id, int donors)
{
	myID = id;

	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);

	QGraphicsRectItem *candidate = new QGraphicsRectItem();
	//candidate->setBrush(QBrush(QColor(255, 110, 110)));
	candidate->setRect(QRectF(0, 0, 50, 50));

	myRecip = candidate;
	addToGroup(candidate);


	qreal dist = 55;

	qreal angle = (2 * PI) / donors;
	qreal donorAngle = -PI/2;
	
	for (int i = 0; i < donors; i++){
		QGraphicsEllipseItem *donor = new QGraphicsEllipseItem();
		//donor->setBrush(QBrush(QColor(255, 110, 110)));
		donor->setRect(QRectF(dist*cos(donorAngle),dist*sin(donorAngle), 50, 50));
		donorAngle -= angle;

		myDonors.push_back(donor);
		addToGroup(donor);
	}

	//QGraphicsLineItem *line = new QGraphicsLineItem(25, 25, 25, 60);
	//line->setPen(QPen(QBrush(QColor(255, 0, 0)), 50));
	//line->setOpacity(0.3);
	

	//candidate->setZValue(1);
	//donor->setZValue(1);
	//line->setZValue(-100);
	
	//addToGroup(line);
	
	
	
	myTextColor = Qt::white;
	myOutlineColor = Qt::black;

	setBackgroundColor();
}

KPDGUICloud::~KPDGUICloud()
{

}

void KPDGUICloud::setBackgroundColor(){

	myBackgroundColor = QColor(255, 0, 0);

	update();
}

void KPDGUICloud::addDonor()
{
	
}

void KPDGUICloud::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget *widget)
{

	QPen pen(myOutlineColor);

	if (option->state & QStyle::State_Selected) {
		pen.setStyle(Qt::DotLine);
		pen.setWidth(2);		
	}

	painter->setPen(pen);
	painter->setBrush(QBrush(myBackgroundColor, Qt::SolidPattern));

	foreach(QGraphicsEllipseItem * donor, myDonors){
		QRectF rect = donor->boundingRect();
		//rect.adjust(-1, -1, 1, 1);
		painter->drawEllipse(rect);		
	}

	QRectF rect = myRecip->boundingRect();
	painter->drawRect(rect);

	painter->setPen(QPen(myTextColor, 16, Qt::SolidLine, Qt::RoundCap));
	QFont * font = new QFont();
	font->setBold(true);
	font->setPointSize(8);
	painter->setFont(*font);

	painter->drawText(rect, Qt::AlignCenter, QString::number(myID));

	int i = 1;
	foreach(QGraphicsEllipseItem * donor, myDonors){
		QRectF rect = donor->boundingRect();
		painter->drawText(rect, Qt::AlignCenter, QString::number(myID) + "-" + QString::number(i));
		i++;
	}
	
	//foreach(KPDGUINode * node, myItems){
		//node->paint(painter, option, widget);
	//}

	/*qreal minx = 200000;
	qreal miny = 200000;
	qreal maxx = -200000;
	qreal maxy = -200000;

	foreach(KPDGUINode * node, myItems){
		qreal height = node->boundingRect().height();
		qreal width = node->boundingRect().width();

		qDebug() << height << " " << width;

		qreal x = node->pos().x();
		qreal y = node->pos().y();

		if (x-width/2 < minx){
			minx = x-width/2;
		}
		if (x+width/2 > maxx){
			maxx = x+width/2;
		}
		if (y-height/2 < miny){
			miny = y-height/2;
		}
		if (y+height/2 > maxy){
			maxy = y+height/2;
		}
	}

	QRectF newBounds(QPointF(minx, miny), QPointF(maxx, maxy));

	setRect(newBounds);

	painter->setBrush(QBrush(QColor(255, 150, 150), Qt::SolidPattern));
	painter->setPen(Qt::NoPen);
	painter->setOpacity(0.3);
	painter->drawRoundedRect(rect(),50.0,50.0);*/

	//QGraphicsItemGroup::paint(painter, option, widget);

}
