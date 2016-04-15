#include "KPDGUIMatch.h"

KPDGUIMatch::KPDGUIMatch(KPDGUINode *fromNode, KPDGUINode *toNode, int donor)
{
	//Add Arrow to Nodes
    myFromNode = fromNode;
    myToNode = toNode;
	myFromNode->addCandidateMatch(this, donor);
	myToNode->addDonorMatch(this);

	associatedDonor = donor;

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
    myFromNode->removeCandidateMatch(this, associatedDonor);
    myToNode->removeDonorMatch(this);
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

   QLineF line(myFromNode->getDonorCenter(associatedDonor), myToNode->getCandidateCenter());
	setLine(line);
}

void KPDGUIMatch::highlightMatch(int level){

	if (level == 1) {
		if (!displayAsPartOfSolution) {
			qreal z = myFromNode->zValue();

			setArrowProperties(Qt::black, 2, 1, z - 1);
		}
	}
	else if (level == 2) {
		qreal z = myFromNode->zValue();
		
		setVisible(false);
		setArrowProperties(Qt::magenta, 4, 1, z - 1);
		setVisible(true);

		displayAsPartOfSolution = true;
	}
}

void KPDGUIMatch::clearHighlight() {

	if (!displayAsPartOfSolution) {
		setArrowProperties(Qt::black, 1, 0.25, -1);
	}
}

void KPDGUIMatch::increasePopularityInStructures(){
	myPopularityInStructures++;
}

void KPDGUIMatch::increasePopularityInSolutions(){
	myPopularityInSolutions++;
}

void KPDGUIMatch::decreasePopularityInStructures(){
	myPopularityInStructures--;
}

void KPDGUIMatch::decreasePopularityInSolutions(){
	myPopularityInSolutions--;
}

void KPDGUIMatch::resetPopularityInStructures(){
	myPopularityInStructures = 0;
}

void KPDGUIMatch::resetPopularityInSolutions(){
	myPopularityInSolutions = 0;
}

void KPDGUIMatch::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

	if (myFromNode->getDonorItem(associatedDonor)->collidesWithItem(myToNode->getCandidateItem())){
		return;
	}

	QPen myPen = pen();
	myPen.setColor(myColor);
	myPen.setWidth(myWidth);
	qreal arrowSize = 6;
	painter->setPen(myPen);
	painter->setBrush(myColor);
	
	QPointF startPoint = myFromNode->getDonorCenter(associatedDonor);
	QPointF endPoint = myToNode->getCandidateCenter();
	
	QLineF centerLine(startPoint, endPoint);
	QPolygonF endPolygon = myToNode->getCandidateItem()->sceneBoundingRect();
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
	
	if (displaySettings->getShowNodeSubset()){
		if (!displaySettings->getShowNodesOnHold() && (myFromNode->getNodeStatus() || myToNode->getNodeStatus())){
			return false;
		}

		int fromPRA = myFromNode->getCandidate()->getPRA();
		int toPRA = myToNode->getCandidate()->getPRA();

		if (displaySettings->getShowCandidatesInPRARange() && (toPRA < displaySettings->getMinPRA() || fromPRA < displaySettings->getMinPRA() || toPRA > displaySettings->getMaxPRA() ||fromPRA > displaySettings->getMaxPRA())){
			return false;
		}
	}

	else if (displaySettings->getShowNodesInStructures()) {
		if (myToNode->getPopularityInStructures() == 0 || myFromNode->getPopularityInStructures() == 0) {
			return false;
		}
	}
	
	else if (displaySettings->getShowNodesInSolutions()){
		if (myToNode->getPopularityInSolutions() == 0 || myFromNode->getPopularityInSolutions() == 0){
			return false;
		}
	}

	return true;
}

void KPDGUIMatch::setArrowProperties(QColor color, int width, qreal opacity, int zValue) {
	setArrowColor(color);
	setArrowWidth(width);
	setArrowZValue(opacity);
	setArrowOpacity(zValue);

	setPen(QPen(myColor, myWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	setZValue(myZValue);
	setOpacity(myOpacity);

}

void KPDGUIMatch::updateSelection(int id, bool selected){	
	if ((myFromNode->isSelected() && myToNode->getNodeID()==id) || (myToNode->isSelected() && myFromNode->getNodeID()==id)){		
		emit selectArrowInMatchList(selected);
	}
}

void KPDGUIMatch::updateVisibility(KPDGUIDisplaySettings * displaySettings){

	if (!displayAsPartOfSolution){
		setVisible(false);
		clearHighlight();

		if (myFromNode->isSelected() && myToNode->isSelected()){
			highlightMatch(1);
		}

		if (displaySettings->getMatchDisplayMode() == ALL_COMPATIBILITIES){
			setVisible(checkVisibility(displaySettings));
		}
		else if (displaySettings->getMatchDisplayMode() == SELECTED_COMPATIBILITIES){
			if (myFromNode->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
			else if (myToNode->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
		else if (displaySettings->getMatchDisplayMode() == COMPATIBLE_DONORS){
			if (myToNode->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
		else if (displaySettings->getMatchDisplayMode() == COMPATIBLE_RECIPIENTS){
			if (myFromNode->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
		else if (displaySettings->getMatchDisplayMode() == WITHIN_SELECTION){
			if (myFromNode->isSelected() && myToNode->isSelected()){
				setVisible(checkVisibility(displaySettings));
			}
		}
	}	
}

void KPDGUIMatch::endDisplayAsPartOfSolution(){
	displayAsPartOfSolution = false;
}



