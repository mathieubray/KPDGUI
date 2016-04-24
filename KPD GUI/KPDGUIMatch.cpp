#include "KPDGUIMatch.h"

KPDGUIMatch::KPDGUIMatch(KPDGUIDonor * donor, KPDGUICandidate * candidate)
{
	myDonor = donor;
    myCandidate = candidate;
	myDonor->addMatchingCandidate(this);
	myCandidate->addMatchingDonor(this);

	//connect(myStartItem, SIGNAL(nodeSelectionChanged(int, bool)), this, SLOT(changeArrowSelection(int, bool)));
	//connect(myEndItem, SIGNAL(nodeSelectionChanged(int, bool)), this, SLOT(changeArrowSelection(int, bool)));
	
	//Arrow Defaults
	setArrowProperties(Qt::black, 1, 0.25, -1);
	
	//Reset Popularity
	myPopularityInStructures = 0;
	myPopularityInSolutions = 0;

	displayAsPartOfSolution = false;
}

KPDGUIMatch::~KPDGUIMatch()
{
    //myDonor->removeCandidateMatch(this, associatedDonor);
    //myCandidate->removeDonorMatch(this);
}

QRectF KPDGUIMatch::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(), line().p2().y() - line().p1().y())).normalized().adjusted(-extra, -extra, extra, extra);
}

QPainterPath KPDGUIMatch::shape() const {

    QPainterPath path = QGraphicsLineItem::shape();
	path.addPolygon(arrowHead);

    return path;
}

void KPDGUIMatch::updatePosition() {
	
	//qDebug() << "Update Position: " << myDonor->getCenter() << " " << myCandidate->getCenter();
	//QLineF line(mapFromItem(myDonor, 0, 0), mapFromItem(myCandidate, 0, 0));
	QLineF line(myDonor->getCenter(), myCandidate->getCenter());
	setLine(line);
}

void KPDGUIMatch::highlightMatch(int level){

	if (level == 1) {
		if (!displayAsPartOfSolution) {
			setArrowProperties(Qt::black, 2, 1, myDonor->zValue() - 0.1);
		}
	}
	else if (level == 2) {
		//setVisible(false);
		setArrowProperties(Qt::magenta, 4, 1, myDonor->zValue() - 0.1);
		//setVisible(true);

		displayAsPartOfSolution = true;
	}
}

void KPDGUIMatch::clearHighlight() {

	if (!displayAsPartOfSolution) {
		setArrowProperties(Qt::black, 1, 0.25, -1);
	}
}

void KPDGUIMatch::increasePopularity(bool solution){
	if (solution) {
		myPopularityInSolutions++;

		myDonor->increasePopularityInSolutions();
		myCandidate->increasePopularityInSolutions();		
	}
	else {
		myPopularityInStructures++;

		myDonor->increasePopularityInStructures();
		myCandidate->increasePopularityInStructures();
	}
}

void KPDGUIMatch::decreasePopularity(bool solution){
	if (solution) {
		myPopularityInSolutions--;

		myDonor->decreasePopularityInSolutions();
		myCandidate->decreasePopularityInSolutions();
	}
	else {
		myPopularityInStructures--;

		myDonor->decreasePopularityInStructures();
		myCandidate->decreasePopularityInStructures();
	}
}

void KPDGUIMatch::resetPopularity(bool solution){
	if (solution) {
		myPopularityInSolutions = 0;

		myDonor->resetPopularityInSolutions();
		myCandidate->resetPopularityInSolutions();
	}
	else {
		myPopularityInStructures = 0;

		myDonor->resetPopularityInStructures();
		myCandidate->resetPopularityInStructures();
	}
}

void KPDGUIMatch::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

	
	if (myDonor->collidesWithItem(myCandidate)) {
		return;
	}

	QPen myPen = pen();
	myPen.setColor(myColor);
	myPen.setWidth(myWidth);
	qreal arrowSize = 6;
	painter->setPen(myPen);
	painter->setBrush(myColor);
	
	QPointF startPoint = myDonor->getCenter();
	QPointF endPoint = myCandidate->getCenter();	
	
	qDebug() << "Painting: " << startPoint << " " << endPoint;

	QLineF centerLine(startPoint, endPoint);
	//QLineF centerLine(myDonor->pos(), myCandidate->pos());
	QPolygonF endPolygon = myCandidate->sceneBoundingRect();
	//QPolygonF endPolygon = myCandidate->boundingRect();
	QPointF p1 = endPolygon.first();
	//QPointF p1 = endPolygon.first() + myCandidate->pos();
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
	//setLine(QLineF(intersectPoint, myDonor->pos()));

	//setLine(QLineF(endPoint, startPoint));

	double angle = ::acos(line().dx() / line().length());
	if (line().dy() >= 0)
		angle = (PI * 2) - angle;

	QPointF arrowP1 = line().p1() + QPointF(sin(angle + PI / 3) * arrowSize, cos(angle + PI / 3) * arrowSize);
	QPointF arrowP2 = line().p1() + QPointF(sin(angle + PI - PI / 3) * arrowSize, cos(angle + PI - PI / 3) * arrowSize);

	arrowHead.clear();
	arrowHead << line().p1() << arrowP1 << arrowP2;

	painter->drawLine(line());
	painter->drawPolygon(arrowHead);
	
	if (isSelected()) {
		painter->setPen(QPen(myColor, myWidth, Qt::DashLine));
		QLineF myLine = line();
		myLine.translate(0, 4.0);
		painter->drawLine(myLine);
		myLine.translate(0, -8.0);
		painter->drawLine(myLine);
	}

}

bool KPDGUIMatch::checkVisibility(KPDGUIDisplaySettings * displaySettings){
	
	/*if (displaySettings->getShowNodeSubset()){
		if (!displaySettings->getShowNodesOnHold() && (myDonor->getStatus() || myCandidate->getStatus())){
			return false;
		}

		int toPRA = myCandidate->getPRA();

		if (displaySettings->getShowCandidatesInPRARange() && (toPRA < displaySettings->getMinPRA() || toPRA > displaySettings->getMaxPRA())){
			return false;
		}
	}

	else if (displaySettings->getShowNodesInStructures()) {
		if (myCandidate->getPopularityInStructures() == 0 || myDonor->getPopularityInStructures() == 0) {
			return false;
		}
	}
	
	else if (displaySettings->getShowNodesInSolutions()){
		if (myCandidate->getPopularityInSolutions() == 0 || myDonor->getPopularityInSolutions() == 0){
			return false;
		}
	}*/

	return true;
}

void KPDGUIMatch::setArrowProperties(QColor color, int width, qreal opacity, int zValue) {
	setArrowColor(color);
	setArrowWidth(width);
	setArrowOpacity(opacity);
	setArrowZValue(zValue);

	setPen(QPen(myColor, myWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	setOpacity(myOpacity);
	setZValue(myZValue);

}

void KPDGUIMatch::updateSelection(int id, bool selected){	
	//if ((myDonor->isSelected() && myCandidate->getNodeID()==id) || (myCandidate->isSelected() && myDonor->getNodeID()==id)){		
		//emit selectMatchInList(selected);
	//}
}

void KPDGUIMatch::updateVisibility(KPDGUIDisplaySettings * displaySettings){

	if (!displayAsPartOfSolution){
		setVisible(false);
		clearHighlight();

		if (myDonor->isSelected() && myCandidate->isSelected()){
			highlightMatch(1);
		}

		if (displaySettings->getMatchDisplayMode() == ALL_COMPATIBILITIES){
			setVisible(checkVisibility(displaySettings));
		}
		else if (displaySettings->getMatchDisplayMode() == SELECTED_COMPATIBILITIES){
			if (myDonor->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
			else if (myCandidate->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
		else if (displaySettings->getMatchDisplayMode() == WITHIN_SELECTION){
			if (myDonor->isSelected() && myCandidate->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
	}
		
}

void KPDGUIMatch::endDisplayAsPartOfSolution(){
	displayAsPartOfSolution = false;
}



