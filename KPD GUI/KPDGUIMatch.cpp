#include "KPDGUIMatch.h"

KPDGUIMatch::KPDGUIMatch() 
{
	matchResult = FAILED_CROSSMATCH_HLA;

	matchFailureProbability = 0.1;

	matchFiveYearSurvival = 0;
	matchTenYearSurvival = 0;
	matchTransplantScore = 0;
	matchAssignedUtility = 0;

	includeMatch = false;

	myColor = determineArrowColor();
	myWidth = 3;
	myPenStyle = determineArrowPenStyle();
	myOpacity = 0.35;
	myZValue = -1;

	//Arrow Defaults
	setArrowProperties(myColor, myWidth, myPenStyle, myOpacity, myZValue);

	//Reset Popularity
	myPopularityInArrangements = 0;
	myPopularityInSolutions = 0;

	displayAsPartOfSolution = false;
}

KPDGUIMatch::KPDGUIMatch(KPDGUIDonor * donor, KPDGUICandidate * candidate, KPDCrossmatchResult result, double fiveYearSurvival, double tenYearSurvival, bool difficultToMatch)
{
	myDonor = donor;
    myCandidate = candidate;
	myDonor->addMatchingCandidate(this);
	myCandidate->addMatchingDonor(this);

	matchResult = result;

	matchFailureProbability = 0.1;

	matchFiveYearSurvival = fiveYearSurvival;
	matchTenYearSurvival = tenYearSurvival;
	matchTransplantScore = 0.00001;
	if (difficultToMatch) {
		matchTransplantScore = 1;
	}
	matchAssignedUtility = 1;

	includeMatch = true;
	
	myColor = determineArrowColor();
	myWidth = 3;
	myPenStyle = determineArrowPenStyle();
	myOpacity = 0.35;
	myZValue = -1;	

	//Arrow Defaults
	setArrowProperties(myColor, myWidth, myPenStyle, myOpacity, myZValue);
	
	//Reset Popularity
	myPopularityInArrangements = 0;
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
	
	////qDebug() << "Update Position: " << myDonor->getCenter() << " " << myCandidate->getCenter();
	//QLineF line(mapFromItem(myDonor, 0, 0), mapFromItem(myCandidate, 0, 0));
	QLineF line(myDonor->getDonorPosition(), myCandidate->getCandidatePosition());
	setLine(line);
}

QColor KPDGUIMatch::determineArrowColor() {

	QColor color;

	if (!includeMatch || matchResult == FAILED_CROSSMATCH_BT || matchResult == FAILED_CROSSMATCH_HLA) {
		color = Qt::red;
	}
	else if (matchResult == O_DONOR_TO_NON_O_CANDIDATE || matchResult == FAILED_CROSSMATCH_ADDITIONAL_HLA || matchResult == FAILED_CROSSMATCH_ADDITIONAL_HLA_AND_O_TO_NON_O) {
		color = QColor(255,165,0);
	}
	else {
		color = Qt::black;
	}

	return color;
}

Qt::PenStyle KPDGUIMatch::determineArrowPenStyle() {

	Qt::PenStyle style = Qt::SolidLine;

	if (!includeMatch || matchResult == FAILED_CROSSMATCH_BT || matchResult == FAILED_CROSSMATCH_HLA) {
		style = Qt::DashLine;
	}

	return style;
}

void KPDGUIMatch::highlightMatch(int level){
	
	if (level == 1) {
		//if (!displayAsPartOfSolution) {
			setArrowProperties(determineArrowColor(), 3, determineArrowPenStyle(), 1, myDonor->zValue() - 0.1);
		//}
	}
	else if (level == 2) {
		setVisible(false);
		setArrowProperties(Qt::green, 5, determineArrowPenStyle(), 1, myDonor->zValue() - 0.1);
		setVisible(true);

	//	displayAsPartOfSolution = true;
	}
	
}

void KPDGUIMatch::clearHighlight() {
	
	//if (!displayAsPartOfSolution) {
		setArrowProperties(determineArrowColor(), 3, determineArrowPenStyle(), 0.35, -1);
	//}
	
}

void KPDGUIMatch::setDonorAndCandidate(KPDGUIDonor * donor, KPDGUICandidate * candidate) {

	myDonor = donor;
	myCandidate = candidate;
	myDonor->addMatchingCandidate(this);
	myCandidate->addMatchingDonor(this);

}


void KPDGUIMatch::setInclude(bool include) {
	includeMatch = include;
}

void KPDGUIMatch::setCrossmatchResult(KPDCrossmatchResult result) {
	matchResult = result;
}

void KPDGUIMatch::increasePopularity(bool solution){
	if (solution) {
		myPopularityInSolutions++;

		myDonor->increasePopularityInSolutions();
		myCandidate->increasePopularityInSolutions();	

		//qDebug() << myDonor->getID() << "->" << myCandidate->getID() << " (Solution)";
	}
	else {
		myPopularityInArrangements++;

		myDonor->increasePopularityInArrangements();
		myCandidate->increasePopularityInArrangements();

		//qDebug() << myDonor->getID() << "->" << myCandidate->getID() << " (Arrangement)";
	}
}

void KPDGUIMatch::decreasePopularity(bool solution){
	if (solution) {
		myPopularityInSolutions--;

		myDonor->decreasePopularityInSolutions();
		myCandidate->decreasePopularityInSolutions();
	}
	else {
		myPopularityInArrangements--;

		myDonor->decreasePopularityInArrangements();
		myCandidate->decreasePopularityInArrangements();
	}
}

void KPDGUIMatch::resetPopularity(bool solution){
	if (solution) {
		myPopularityInSolutions = 0;

		myDonor->resetPopularityInSolutions();
		myCandidate->resetPopularityInSolutions();
	}
	else {
		myPopularityInArrangements = 0;

		myDonor->resetPopularityInArrangements();
		myCandidate->resetPopularityInArrangements();
	}
}

void KPDGUIMatch::setFailureProbability(double probability) {
	matchFailureProbability = probability;
}

void KPDGUIMatch::setFiveYearSurvival(double fiveYearSurvival) {
	matchFiveYearSurvival = fiveYearSurvival;
}

void KPDGUIMatch::setTenYearSurvival(double tenYearSurvival) {
	matchTenYearSurvival = tenYearSurvival;
}

void KPDGUIMatch::setTransplantScore(double transplantScore) {
	matchTransplantScore = transplantScore;
}

void KPDGUIMatch::setAssignedUtility(double assignedUtility) {
	matchAssignedUtility = assignedUtility;
}

void KPDGUIMatch::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

	
	if (myDonor->collidesWithItem(myCandidate)) {
		return;
	}

	QPen myPen = pen();
	myPen.setColor(myColor);
	myPen.setWidth(myWidth);
	myPen.setStyle(myPenStyle);
	qreal arrowSize = 10;
	painter->setPen(myPen);
	painter->setBrush(myColor);
	
	QPointF startPoint = myDonor->getPosition();
	QPointF endPoint = myCandidate->getCandidatePosition();		

	QLineF centerLine(startPoint, endPoint);
	QPolygonF endPolygon = myCandidate->sceneBoundingRect();
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

	QPolygonF startPolygon = myDonor->getRect();
	QPointF q1 = startPolygon.first();
	QPointF q2;
	QPointF intersectPoint2;
	QLineF polyLine2;
	for (int i = 1; i < startPolygon.count(); ++i) {
		q2 = startPolygon.at(i);
		polyLine2 = QLineF(q1, q2);
		QLineF::IntersectType intersectType2 = polyLine2.intersect(centerLine, &intersectPoint2);
		if (intersectType2 == QLineF::BoundedIntersection)
			break;
		q1 = q2;
	}

	setLine(QLineF(intersectPoint, intersectPoint2));

	double angle = ::acos(line().dx() / line().length());
	if (line().dy() >= 0)
		angle = (PI * 2) - angle;

	QPointF arrowP1 = line().p1() + QPointF(sin(angle + PI / 3) * arrowSize, cos(angle + PI / 3) * arrowSize);
	QPointF arrowP2 = line().p1() + QPointF(sin(angle + PI - PI / 3) * arrowSize, cos(angle + PI - PI / 3) * arrowSize);

	arrowHead.clear();
	arrowHead << line().p1() << arrowP1 << arrowP2;

	painter->drawLine(line());
	painter->drawPolygon(arrowHead);
	
	//if (isSelected()) {
	//	painter->setPen(QPen(myColor, myWidth, Qt::DashLine));
	//	QLineF myLine = line();
	//	myLine.translate(0, 4.0);
	//	painter->drawLine(myLine);
	//	myLine.translate(0, -8.0);
	//	painter->drawLine(myLine);
	//}

}

bool KPDGUIMatch::checkVisibility(KPDGUIDisplaySettings * displaySettings){
	
	if (displaySettings->getShowNodeSubset()){
		if (!displaySettings->getShowExcludedNodes() && (!myDonor->getStatus() || !myCandidate->getParentNode()->getStatus())){
			return false;
		}

		int toPRA = myCandidate->getPRA();

		if (displaySettings->getShowCandidatesInPRARange() && (toPRA < displaySettings->getMinPRA() || toPRA > displaySettings->getMaxPRA())){
			return false;
		}
	}

	else if (displaySettings->getShowNodesInArrangements()) {
		if (myCandidate->getPopularityInArrangements() == 0 || myDonor->getPopularityInArrangements() == 0) {
			return false;
		}
	}
	
	else if (displaySettings->getShowNodesInSolutions()){
		if (myCandidate->getPopularityInSolutions() == 0 || myDonor->getPopularityInSolutions() == 0){
			return false;
		}
	}

	return true;
}

void KPDGUIMatch::setArrowProperties(QColor color, int width, Qt::PenStyle penStyle, qreal opacity, int zValue) {
	setArrowColor(color);
	setArrowWidth(width);
	setArrowPenStyle(penStyle);
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

		bool filterOut = false;
		
		if (!displaySettings->getFilterSuccessfulMatches() && matchResult == SUCCESSFUL_CROSSMATCH) {
			filterOut = true;
		}
		if (!displaySettings->getFilterOtoNonOMatches() && (matchResult == O_DONOR_TO_NON_O_CANDIDATE || matchResult == FAILED_CROSSMATCH_ADDITIONAL_HLA_AND_O_TO_NON_O)) {
			filterOut = true;
		}
		if (!displaySettings->getFilterFailedMatchesAdditionalHLA() && (matchResult == FAILED_CROSSMATCH_ADDITIONAL_HLA || matchResult == FAILED_CROSSMATCH_ADDITIONAL_HLA_AND_O_TO_NON_O)) {
			filterOut = true;
		}
		if (!displaySettings->getFilterFailedMatchesCrossmatch() && (matchResult == FAILED_CROSSMATCH_BT || matchResult == FAILED_CROSSMATCH_HLA)) {
			filterOut = true;
		}

		if (!filterOut) {
			
			KPDNodeDisplayMode nodeDisplayMode = displaySettings->getNodeDisplayMode();

			if (nodeDisplayMode == SEPARATE_DONOR_CANDIDATE) {
				if (myDonor->isSelected() && myCandidate->isSelected()) {
					highlightMatch(1);
				}
			}
			else {

				if (myDonor->isAltruistic()) {
					if (myDonor->isSelected() && myCandidate->isSelected()) {
						highlightMatch(1);
					}
				}

				else if (myDonor->getParentNode()->getCandidate()->isSelected() && myCandidate->isSelected()) {
					highlightMatch(1);
				}
			}

			if (displaySettings->getMatchDisplayMode() == ALL_COMPATIBILITIES) {
				setVisible(checkVisibility(displaySettings));
			}
			else if (displaySettings->getMatchDisplayMode() == SELECTED_COMPATIBILITIES) {
				if (nodeDisplayMode == SEPARATE_DONOR_CANDIDATE) {
					if (myDonor->isSelected()) {
						setVisible(checkVisibility(displaySettings));
					}
					else if (myCandidate->isSelected()) {
						setVisible(checkVisibility(displaySettings));
					}
				}
				else {
					if (myDonor->isAltruistic()) {
						if (myDonor->isSelected()) {
							setVisible(checkVisibility(displaySettings));
						}
						else if (myCandidate->isSelected()) {
							setVisible(checkVisibility(displaySettings));
						}
					}
					else {
						if (myDonor->getParentNode()->getCandidate()->isSelected()) {
							setVisible(checkVisibility(displaySettings));
						}
						else if (myCandidate->isSelected()) {
							setVisible(checkVisibility(displaySettings));
						}
					}
				}
			}
			else if (displaySettings->getMatchDisplayMode() == WITHIN_SELECTION) {
				if (nodeDisplayMode == SEPARATE_DONOR_CANDIDATE) {
					if (myDonor->isSelected() && myCandidate->isSelected()) {
						setVisible(checkVisibility(displaySettings));
					}
				}
				else {
					if (myDonor->isAltruistic()) {
						if (myDonor->isSelected() && myCandidate->isSelected()) {
							setVisible(checkVisibility(displaySettings));
						}
					}
					else {
						if (myDonor->getParentNode()->getCandidate()->isSelected() && myCandidate->isSelected()) {
							setVisible(checkVisibility(displaySettings));
						}
					}
				}
			}
		}
	}
		
}

void KPDGUIMatch::endDisplayAsPartOfSolution(){
	displayAsPartOfSolution = false;
}

void KPDGUIMatch::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) {

	edit();
}

void KPDGUIMatch::edit() {

	DialogMatch * matchDialog = new DialogMatch(this);
	if (matchDialog->exec()) {
		editMatch(matchDialog);
		
		if (matchDialog->getAdditionalInformation()) {
			emit showAdditionalMatchInformation(this);
		}
	}

}

void KPDGUIMatch::editMatch(DialogMatch * dialog) {
	
	includeMatch = dialog->includeCheckBox->isChecked();

	matchFailureProbability = dialog->probabilitySpinBox->value();
	matchAssignedUtility = dialog->scoreSpinBox->value();

	myPenStyle = determineArrowPenStyle();
	myColor = determineArrowColor();

	setArrowProperties(myColor, myWidth, myPenStyle, myOpacity, myZValue);
	
}

void KPDGUIMatch::updateCrossmatchResults(KPDCrossmatchResult result, double fiveYear, double tenYear, bool difficultToMatch) {

	matchResult = result;
	matchFiveYearSurvival = fiveYear;
	matchTenYearSurvival = tenYear;

	if (difficultToMatch) {
		matchTransplantScore = 1;
	}
	else {
		matchTransplantScore = 0.00001;
	}

	myPenStyle = determineArrowPenStyle();
	myColor = determineArrowColor();

	setArrowProperties(myColor, myWidth, myPenStyle, myOpacity, myZValue);
}

QDataStream &operator<<(QDataStream &out, const KPDGUIMatch & match)
{
	out << match.getInclude();
	out << qint32(KPDFunctions::crossmatchResultToInt(match.getCrossmatchResult()));

	out << qreal(match.getFailureProbability());

	out << qreal(match.getFiveYearSurvival());
	out << qreal(match.getTenYearSurvival());
	out << qreal(match.getTransplantScore());
	out << qreal(match.getAssignedUtility());

	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUIMatch & match)
{
	bool include;
	int crossmatch;
	in >> include >> crossmatch;
	match.setInclude(include);
	match.setCrossmatchResult(KPDFunctions::intToCrossmatchResult(crossmatch));

	double prob;
	in >> prob;
	match.setFailureProbability(prob);

	double fiveYear;
	double tenYear;
	double score;
	double utility;
	in >> fiveYear >> tenYear >> score >> utility;
	match.setFiveYearSurvival(fiveYear);
	match.setTenYearSurvival(tenYear);
	match.setTransplantScore(score);
	match.setAssignedUtility(utility);
	
	return in;
}


