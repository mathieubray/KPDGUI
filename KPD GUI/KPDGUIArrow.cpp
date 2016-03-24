#include "KPDGUIArrow.h"

KPDGUIArrow::KPDGUIArrow(KPDGUINode *startItem, KPDGUINode *endItem, bool arrow)
{
	//Add Arrow to Nodes
    myStartItem = startItem;
    myEndItem = endItem;
	myStartItem->addOutArrow(this);
	myEndItem->addInArrow(this);

	//connect(myStartItem, SIGNAL(nodeSelectionChanged(int, bool)), this, SLOT(changeArrowSelection(int, bool)));
	//connect(myEndItem, SIGNAL(nodeSelectionChanged(int, bool)), this, SLOT(changeArrowSelection(int, bool)));
	
	//Arrow Defaults
	setZValue(-1);
	isArrow = arrow;

	if (!arrow){
		myColor = QColor(255, 100, 100);
		myWidth = 50;
		setOpacity(0.5);
	}
	else {
		myColor = Qt::black;
		myWidth = 1;
	}
    setPen(QPen(myColor, myWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	
	//Reset Popularity
	myPopularityInStructures = 0;
	myPopularityInSolutions = 0;

	displayAsPartOfSolution = false;
}

KPDGUIArrow::~KPDGUIArrow()
{
    myStartItem->removeOutArrow(this);
    myEndItem->removeInArrow(this);
}

QRectF KPDGUIArrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath KPDGUIArrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
	if (isArrow){
		path.addPolygon(arrowHead);
	}
    return path;
}

void KPDGUIArrow::updatePosition()
{
    //QLineF line(mapFromItem(myStartItem->getDonorItem(), 0, 0), mapFromItem(myEndItem->getRecipItem(), 0, 0));
	QLineF line(myStartItem->getDonorCenter(), myEndItem->getRecipCenter());
	setLine(line);
}

void KPDGUIArrow::clearHighlight(){
	if (!displayAsPartOfSolution){
		setColor(Qt::black);
		setWidth(1);
		setOpacity(0.25);
		setZValue(-1);
	}
}

void KPDGUIArrow::highlightConnection(){
	if (!displayAsPartOfSolution){
		qreal z = myStartItem->zValue();
		setColor(Qt::black);
		setWidth(2);
		setOpacity(1);
		setZValue(z - 1);
	}
}

void KPDGUIArrow::highlightCycle(){
	qreal z = myStartItem->zValue();
	setVisible(false);
	setColor(Qt::magenta);
	setWidth(4);
	setOpacity(1);
	setZValue(z-1);
	setVisible(true);

	displayAsPartOfSolution = true;
}

void KPDGUIArrow::increasePopularityInStructures(){
	myPopularityInStructures++;
}

void KPDGUIArrow::increasePopularityInSolutions(){
	myPopularityInSolutions++;
}

void KPDGUIArrow::decreasePopularityInStructures(){
	myPopularityInStructures--;
}

void KPDGUIArrow::decreasePopularityInSolutions(){
	myPopularityInSolutions--;
}

void KPDGUIArrow::resetPopularityInStructures(){
	myPopularityInStructures = 0;
}

void KPDGUIArrow::resetPopularityInSolutions(){
	myPopularityInSolutions = 0;
}

void KPDGUIArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	if (myStartItem->getDonorItem()->collidesWithItem(myEndItem->getRecipItem())){
		return;
	}

	QPen myPen = pen();
	myPen.setColor(myColor);
	myPen.setWidth(myWidth);
	qreal arrowSize = 6;
	painter->setPen(myPen);
	painter->setBrush(myColor);
	
	QPointF startPoint = myStartItem->getDonorCenter();
	QPointF endPoint = myEndItem->getRecipCenter();
	
	if (isArrow){
		QLineF centerLine(startPoint, endPoint);
		QPolygonF endPolygon = myEndItem->getRecipItem()->sceneBoundingRect();
		QPointF p1 = endPolygon.first();
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
		}

		setLine(QLineF(intersectPoint, startPoint));
	}
	else {
		setLine(QLineF(endPoint,startPoint));
	}

	double angle = ::acos(line().dx() / line().length());
	if (line().dy() >= 0)
		angle = (PI * 2) - angle;

	QPointF arrowP1 = line().p1() + QPointF(sin(angle + PI / 3) * arrowSize, cos(angle + PI / 3) * arrowSize);
	QPointF arrowP2 = line().p1() + QPointF(sin(angle + PI - PI / 3) * arrowSize, cos(angle + PI - PI / 3) * arrowSize);

	arrowHead.clear();
	arrowHead << line().p1() << arrowP1 << arrowP2;

	painter->drawLine(line());
	if (isArrow){
		painter->drawPolygon(arrowHead);
	}
	if (isSelected()) {
		painter->setPen(QPen(myColor, myWidth, Qt::DashLine));
		QLineF myLine = line();
		myLine.translate(0, 4.0);
		painter->drawLine(myLine);
		myLine.translate(0, -8.0);
		painter->drawLine(myLine);
	}
}

bool KPDGUIArrow::checkVisibility(KPDGUIDisplaySettings * displaySettings){
	
	if (displaySettings->getShowPairSubset()){
		if (!displaySettings->getShowPairsOnHold() && (myStartItem->getHoldStatus() || myEndItem->getHoldStatus())){
			return false;
		}
		if (displaySettings->getShowPairsOfMinPRA() && (myEndItem->getCandidatePRA() < displaySettings->getMinPRA() || myStartItem->getCandidatePRA() < displaySettings->getMinPRA())){
			return false;
		}
		if (displaySettings->getShowPairsOfMaxPRA() && (myEndItem->getCandidatePRA() > displaySettings->getMaxPRA() || myStartItem->getCandidatePRA() > displaySettings->getMaxPRA())){
			return false;
		}
	}
	
	else if (displaySettings->getShowPairsInSolutions()){
		if (myEndItem->getPopularityInSolutions() == 0 || myStartItem->getPopularityInSolutions() == 0){
			return false;
		}
	}

	else if (displaySettings->getShowPairsInStructures()){
		if (myEndItem->getPopularityInStructures() == 0 || myStartItem->getPopularityInSolutions() == 0){
			return false;
		}
	}

	return true;
}

void KPDGUIArrow::changeArrowSelection(int id, bool selected){	
	if ((startItem()->isSelected() && endItem()->getInternalID()==id) || (endItem()->isSelected() && startItem()->getInternalID()==id)){		
		emit selectArrowInMatchList(selected);
	}
}

void KPDGUIArrow::updateVisibility(KPDGUIDisplaySettings * displaySettings){

	if (!displayAsPartOfSolution){
		setVisible(false);
		clearHighlight();

		if (myStartItem->isSelected() && myEndItem->isSelected()){
			highlightConnection();
		}

		if (displaySettings->getArrowDisplayMode() == ALL_COMPATIBILITIES){
			setVisible(checkVisibility(displaySettings));
		}
		else if (displaySettings->getArrowDisplayMode() == SELECTED_COMPATIBILITIES){
			if (myStartItem->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
			else if (myEndItem->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
		else if (displaySettings->getArrowDisplayMode() == COMPATIBLE_DONORS){
			if (myEndItem->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
		else if (displaySettings->getArrowDisplayMode() == COMPATIBLE_RECIPIENTS){
			if (myStartItem->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
		else if (displaySettings->getArrowDisplayMode() == WITHIN_SELECTION){
			if (myStartItem->isSelected() && myEndItem->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
	}	
}

void KPDGUIArrow::endDisplayAsPartOfSolution(){
	displayAsPartOfSolution = false;
}

