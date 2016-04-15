#include "KPDGUINode.h"
#include "KPDGUIMatch.h"

#include "DialogDonor.h"

KPDGUINode::KPDGUINode()
{
	myType = PAIR;


}

KPDGUINode::KPDGUINode(KPDGUIDonorInfo * donor)
{
	myType = KPDNodeType::AD;
	
	myDonors << donor;	
	myDonorStatuses << false;

	QGraphicsEllipseItem * newDonorItem = new QGraphicsEllipseItem();
	newDonorItem->setRect(QRectF(0, 0, 75, 65));
	addToGroup(newDonorItem);
	myDonorItems << newDonorItem;
		
	setAdditionalProperties();	
}

KPDGUINode::KPDGUINode(QVector<KPDGUIDonorInfo *> donors, KPDGUICandidateInfo * candidate)
{
	myType = KPDNodeType::PAIR;
	
	int numberOfDonors = donors.size();

	qreal dist = 45;
	qreal donorAngle = -PI / 4;

	foreach(KPDGUIDonorInfo * donor, donors) {
		myDonors << donor;
		myDonorStatuses << false;

		QGraphicsEllipseItem * associatedDonorItem = new QGraphicsEllipseItem();
		associatedDonorItem->setRect(QRectF(dist*cos(donorAngle), dist*sin(donorAngle), 75, 65));
		addToGroup(associatedDonorItem);
		myDonorItems << associatedDonorItem;
		
		donorAngle += (2 * PI) / numberOfDonors;
	}

	myCandidate = candidate;

	myCandidateItem = new QGraphicsEllipseItem();
	myCandidateItem->setRect(QRectF(0, 0, 65, 55));
	addToGroup(myCandidateItem);

	myCandidateStatus = false;

	setAdditionalProperties();	
}

KPDGUINode::~KPDGUINode()
{
	foreach(KPDGUIMatch * match, myCompatibleDonorMatches)
		delete match;
	foreach(QSet<KPDGUIMatch * > candidateMatchesByDonor, myCompatibleCandidateMatches){
		foreach(KPDGUIMatch * match, candidateMatchesByDonor) {
			delete match;
		}
	}
}

int KPDGUINode::getNodeID() const {
	return nodeID;
}

KPDNodeType KPDGUINode::getNodeType() const {
	return myType;
}

KPDGUIDonorInfo * KPDGUINode::getDonor(int i) const {
	return myDonors[i];
}

QVector<KPDGUIDonorInfo *> KPDGUINode::getDonors() const {
	return myDonors;
}

int KPDGUINode::getNumberOfDonors() const {
	return myDonors.size();
}

KPDGUICandidateInfo * KPDGUINode::getCandidate() const {
	return myCandidate;
}

bool KPDGUINode::getDonorStatus(int i) const {
	return myDonorStatuses[i];
}

bool KPDGUINode::getCandidateStatus() const {
	return myCandidateStatus;
}

bool KPDGUINode::getNodeStatus() {

	if (getCandidateStatus()) {
		return true;
	}
	else {
		foreach(bool donorStatus, myDonorStatuses) {
			if (!donorStatus) {
				return false;
			}
		}

		return true;
	}
}

QVector<QString> KPDGUINode::getPrograms() const {
	return myPrograms;
}

int KPDGUINode::getNumberOfPrograms() const {
	return myPrograms.size();
}

void KPDGUINode::setCandidate(KPDGUICandidateInfo * c) {

	myCandidate = c;
}

void KPDGUINode::setNodeID(int id) {
	nodeID = id;

	if (myType == PAIR) {
		setToolTip("Pair " + QString::number(id));
	}
	else {
		setToolTip("AD " + QString::number(id));
	}
}

void KPDGUINode::setNodeType(KPDNodeType type) {
	myType = type;
}

void KPDGUINode::setDonors(QVector<KPDGUIDonorInfo *> donors) {
	myDonors = donors;

	//FIX
}

void KPDGUINode::addDonor(KPDGUIDonorInfo * d) {

	myDonors << d;

	int numberOfDonors = myDonors.size();

	qreal dist = 45;
	qreal donorAngle = -PI / 4;

	foreach(QGraphicsEllipseItem * donorItem, myDonorItems) {
		donorItem->setRect(QRectF(dist*cos(donorAngle), dist*sin(donorAngle), 75, 65));
		donorAngle += (2 * PI) / numberOfDonors;
	}

	QGraphicsEllipseItem * donorItem = new QGraphicsEllipseItem();
	donorItem->setRect(QRectF(dist*cos(donorAngle), dist*sin(donorAngle), 75, 65));
	addToGroup(donorItem);
	myDonorItems << donorItem;

	myDonorStatuses << false;

}

void KPDGUINode::removeDonor(int i) {
	myDonors.remove(i);
	myDonorItems.remove(i);
	myDonorStatuses.remove(i);

	int numberOfDonors = myDonors.size();

	qreal dist = 45;
	qreal donorAngle = -PI / 4;

	foreach(QGraphicsEllipseItem * donorItem, myDonorItems) {
		donorItem->setRect(QRectF(dist*cos(donorAngle), dist*sin(donorAngle), 75, 65));
		donorAngle += (2 * PI) / numberOfDonors;
	}
}

void KPDGUINode::setDonorStatus(int i, bool status) {
	myDonorStatuses[i] = status;
	setBackgroundColors();

	emit nodeHoldStatusChanged(nodeID, status);
}

void KPDGUINode::setCandidateStatus(bool status) {

}

void KPDGUINode::setPrograms(QVector<QString> programs) {

}

void KPDGUINode::addProgram(QString program) {

}

void KPDGUINode::removeProgram(QString program) {

}

QGraphicsEllipseItem * KPDGUINode::getDonorItem(int i) {
	return myDonorItems[i];
}

QGraphicsEllipseItem * KPDGUINode::getCandidateItem() {
	return myCandidateItem;
}

QPointF KPDGUINode::getDonorCenter(int i) {

	//qreal x = myDonor->mapFromScene(myDonor->boundingRect().x());
	//qreal y = myDonor->mapFromScene(myDonor->boundingRect().y());
	QPointF point = mapToScene(myDonorItems[i]->boundingRect().topLeft());
	qreal x = point.x();
	qreal y = point.y();

	qreal width = myDonorItems[i]->boundingRect().width();
	qreal height = myDonorItems[i]->boundingRect().height();

	return QPointF(x + width / 2, y + height / 2);
}

QPointF KPDGUINode::getCandidateCenter() {

	QPointF point = mapToScene(myCandidateItem->boundingRect().topLeft());
	qreal x = point.x();
	qreal y = point.y();
	qreal width = myCandidateItem->boundingRect().width();
	qreal height = myCandidateItem->boundingRect().height();

	return QPointF(x + width / 2, y + height / 2);

}

QString KPDGUINode::text() const
{
	return myText;
}

void KPDGUINode::setText(const QString &text)
{
	prepareGeometryChange();
	myText = text;
	update();
}

void KPDGUINode::setBackgroundColors()
{
	if (myType == PAIR) {
		if (myCandidateStatus) {
			myCandidateBackgroundColor = QColor(100, 100, 100);
		}
		else {
			int pra = myCandidate->getPRA();
			myCandidateBackgroundColor = QColor(255, pra * 1.5, pra * 1.5);
		}
	}

	for (int i = 1; i <= getNumberOfDonors(); i++) {
		if (myDonorStatuses[i - 1]) {
			myDonorBackgroundColors[i - 1] = QColor(100, 100, 125);
		}
		else {
			myDonorBackgroundColors[i - 1] = QColor(0, 0, 255);
		}
	}

	update();
}

QColor KPDGUINode::donorBackgroundColor(int i) const
{
	return myDonorBackgroundColors[i];
}

QColor KPDGUINode::candidateBackgroundColor() const
{
	return myCandidateBackgroundColor;
}

//QRectF KPDGUINode::boundingRect() const
//{
//const int Margin = 1;
//return outlineRect().adjusted(-Margin, -Margin, +Margin, +Margin);
//}

//QRectF KPDGUINode::outlineRect() const
//{
/*qreal x1; qreal x2; qreal y1; qreal y2;

int Padding = 12;
QFont * font = new QFont();
font->setBold(true);
font->setPointSize(8);
QFontMetricsF * metrics = new QFontMetricsF(*font);
QRectF rect = metrics->boundingRect(myText);
rect.getCoords(&x1, &y1, &x2, &y2);
rect.adjust(-(2.5*Padding - x1), -(Padding - y1), (2.5*Padding - x2), (Padding - y2));
rect.translate(-rect.center());
return rect; */
//}

//QPainterPath KPDGUINode::shape() const
//{
//QRectF rect = outlineRect();

//QPainterPath path;
//path.addEllipse(rect);
//return path;
//}

void KPDGUINode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	QColor myOutlineColor = Qt::black;
	QColor myTextColor = Qt::white;

	//Outline
	QPen pen(myOutlineColor);

	if (option->state & QStyle::State_Selected) {
		pen.setStyle(Qt::DotLine);
		pen.setWidth(2);
	}

	painter->setPen(pen);
	painter->setBrush(QBrush(myDonorBackgroundColors[0], Qt::SolidPattern));

	QRectF donorRect = myDonorItems[0]->boundingRect();
	painter->drawEllipse(donorRect);

	painter->setPen(QPen(myTextColor, 16, Qt::SolidLine, Qt::RoundCap));

	QFont * font = new QFont();
	font->setBold(true);
	font->setPointSize(8);
	painter->setFont(*font);

	painter->drawText(donorRect, Qt::AlignCenter, QString::number(nodeID));

	if (myType == PAIR) {
		painter->setPen(pen);
		painter->setBrush(QBrush(myCandidateBackgroundColor, Qt::SolidPattern));

		QRectF recipRect = myCandidateItem->boundingRect();
		painter->drawEllipse(recipRect);

		painter->setPen(QPen(myTextColor, 16, Qt::SolidLine, Qt::RoundCap));

		QFont * font = new QFont();
		font->setBold(true);
		font->setPointSize(8);
		painter->setFont(*font);

		//painter->drawText(recipRect, Qt::AlignCenter, QString::number(internalID));
	}

}

//QVariant KPDGUINode::data(int column) const {
//}


void KPDGUINode::addDonorMatch(KPDGUIMatch * match)
{
	myCompatibleDonorMatches.insert(match);
}

void KPDGUINode::removeDonorMatch(KPDGUIMatch * match)
{
	myCompatibleDonorMatches.remove(match);
}

void KPDGUINode::addCandidateMatch(KPDGUIMatch * match, int i)
{
	myCompatibleCandidateMatches[i].insert(match);
}

void KPDGUINode::removeCandidateMatch(KPDGUIMatch * match, int i)
{
	myCompatibleCandidateMatches[i].remove(match);
}

KPDGUIMatch * KPDGUINode::findDonorMatch(KPDGUINode * toNode) {
	foreach(KPDGUIMatch * match, myCompatibleDonorMatches) {
		if (match->getToNode() == toNode) {
			return match;
		}
	}

	return NULL;
}

KPDGUIMatch * KPDGUINode::findCandidateMatch(KPDGUINode * fromNode, int i) {
	foreach(KPDGUIMatch * match, myCompatibleCandidateMatches[i]) {
		if (match->getFromNode() == fromNode) {
			return match;
		}
	}

	return NULL;
}

bool KPDGUINode::hasNoCompatibilities() {
	return (getNumberOfCompatibleDonors() == 0);
}

int KPDGUINode::getNumberOfCompatibilities() {
	return myCompatibleDonorMatches.count() + myCompatibleCandidateMatches.count();
}

int KPDGUINode::getNumberOfCompatibleDonors() {
	return myCompatibleDonorMatches.count();
}

int KPDGUINode::getNumberOfCompatibleCandidates() {
	return myCompatibleCandidateMatches.count();
}


int KPDGUINode::getPopularityInStructures() {
	return popularityInStructures;
}

int KPDGUINode::getPopularityInSolutions() {
	return popularityInSolutions;
}

void KPDGUINode::increasePopularityInStructures() {
	popularityInStructures++;
}

void KPDGUINode::increasePopularityInSolutions() {
	popularityInSolutions++;
}

void KPDGUINode::decreasePopularityInStructures() {
	popularityInStructures--;
}

void KPDGUINode::decreasePopularityInSolutions() {
	popularityInSolutions--;
}

void KPDGUINode::resetPopularityInStructures() {
	popularityInStructures = 0;
}

void KPDGUINode::resetPopularityInSolutions() {
	popularityInSolutions = 0;
}

QString KPDGUINode::getNameString() {

	// Should be drawn from Candidate and Donor files

	if (myType == AD) {
		return "AD: " + myDonors.first()->getName();
	}
	else {
		QString nameString = myCandidate->getName() + "/";
		foreach(KPDGUIDonorInfo * donor, myDonors) {
			nameString += donor->getName() + ",";
		}
		nameString.chop(1);

		return nameString;
	}

}

QString KPDGUINode::getCompatibleDonorString() {
	QString compatibleDonorString = "Compatible Donors: ";

	if (myCompatibleDonorMatches.count() > 0) {
		QVector<int> compatibleDonors;
		foreach(KPDGUIMatch * match, myCompatibleDonorMatches) {
			compatibleDonors.push_back(match->getFromNode()->getNodeID());
		}
		qSort(compatibleDonors);
		foreach(int id, compatibleDonors) {
			compatibleDonorString += QString::number(id);
			compatibleDonorString += ", ";
		}
		compatibleDonorString.chop(2);
	}
	else {
		compatibleDonorString += "None";
	}

	return compatibleDonorString;
}

QString KPDGUINode::getCompatibleCandidatesString() {
	QString compatibleCandidateString = "Compatible Candidates: ";

	foreach(QSet<KPDGUIMatch *> compatibleMatchesByDonor, myCompatibleCandidateMatches) {
		if (compatibleMatchesByDonor.size() > 0) {
			QVector<int> compatibleCandidates;
			foreach(KPDGUIMatch * match, compatibleMatchesByDonor) {
				compatibleCandidates.push_back(match->getToNode()->getNodeID());
			}
			qSort(compatibleCandidates);
			foreach(int id, compatibleCandidates) {
				compatibleCandidateString += QString::number(id);
				compatibleCandidateString += ", ";
			}
			compatibleCandidateString.chop(2);
		}
		else {
			compatibleCandidateString += "None";
		}
	}

	return compatibleCandidateString;
}

QString KPDGUINode::getDashboardString() {
	QString consoleString = "";

	if (myType == PAIR) {
		consoleString += "Pair ";
	}
	else {
		consoleString += "AD ";
	}
	consoleString += QString::number(nodeID);
	consoleString += " (";
	if (myCandidateStatus) {
		consoleString += "KPDGUICandidateInfo on hold, ";
	}

	int i = 0;
	foreach(bool status, myDonorStatuses) {
		i++;
		if (status) {
			consoleString += "KPDGUIDonorInfo ";
			consoleString += i;
			consoleString += " on hold, ";
		}
	}
	consoleString.chop(2);

	//MOVE
	/*
	consoleString += "\nDonor: ";
	consoleString += getDonorName();
	consoleString += " (";
	consoleString += getDonorBT();
	consoleString += ")";
	if (myDonors[i]->type == PAIR){
	consoleString += ", Candidate: ";
	consoleString += getCandidateName();
	consoleString += " (";
	consoleString += getCandidateBT();
	consoleString += ")";
	}
	consoleString += "\n\nKPDGUIDonorInfo HLA : ";

	QString donorHLAString = getFullDonorHLAString();
	donorHLAString.replace(";", " ");
	if (donorHLAString.size() > 0){
	consoleString += donorHLAString;
	}
	else {
	consoleString += "None";
	}

	if (myDonors[i]->type == PAIR){
	consoleString += "\nKPDGUICandidateInfo HLA: ";

	QString recipHLAString = getCandidateHLAString();
	recipHLAString.replace(";", " ");
	if (recipHLAString.size() > 0){
	consoleString += recipHLAString;
	}
	else {
	consoleString += "None";
	}
	}

	consoleString += "\n";
	if (myDonors[i]->type == PAIR){
	consoleString += "\n";
	consoleString += getCompatibleDonorString();
	consoleString += "\n";
	}
	consoleString += getCompatibleCandidatesString();
	consoleString += "\n";

	if (comment.size() > 0){
	consoleString += "\n";
	consoleString += "Additional Comments: ";
	consoleString += comment;
	}
	*/
	//MOVE
	return consoleString;
}

QVariant KPDGUINode::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemPositionHasChanged) {
		foreach(KPDGUIMatch * match, myCompatibleDonorMatches)
			match->updatePosition();
		foreach(QSet<KPDGUIMatch *> compatibleCandidatesByDonor, myCompatibleCandidateMatches) {
			foreach(KPDGUIMatch * match, compatibleCandidatesByDonor)
				match->updatePosition();

		}
	}

	if (change == ItemSelectedHasChanged) {
		emit nodeSelectionChanged(nodeID, value.toBool());
	}

	return QGraphicsItem::itemChange(change, value);
}

void KPDGUINode::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {

	qDebug() << "Entered!";
	emit nodeEntered(nodeID);
}

void KPDGUINode::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
	qDebug() << "Left";
	emit nodeLeft(nodeID);
}

void KPDGUINode::mousePressEvent(QGraphicsSceneMouseEvent *event) {

	setSelected(true);

	emit nodeWasClicked(nodeID, isSelected());
}

void KPDGUINode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) {

	editNode();

	//QGraphicsObject::mouseDoubleClickEvent(event);
}


void KPDGUINode::editNode() {

}


void KPDGUINode::setAdditionalProperties() {
	setBackgroundColors();
	setZValue(0);
	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);

	popularityInStructures = 0;
	popularityInSolutions = 0;
}





bool KPDGUINode::checkWithinBounds(int minPRA, int maxPRA) {

	int pra = myCandidate->getPRA();

	if (myType == AD || (minPRA < pra && maxPRA > pra)) {
		return true;
	}

	return false;
}

void KPDGUINode::updateVisibility(KPDGUIDisplaySettings * displaySettings) {

	qDebug() << "Update Visibility of Node " << nodeID;

	if (displaySettings->getShowNodesInStructures()) {
		if (getPopularityInStructures() == 0) {
			setVisible(false);
			setSelected(false);
		}
	}
	else if (displaySettings->getShowNodesInSolutions()) {
		if (getPopularityInSolutions() == 0) {
			setVisible(false);
			setSelected(false);
		}
	}

	else if (displaySettings->getShowNodeSubset()) {

		bool withinBounds = true;
		if (displaySettings->getShowCandidatesInPRARange()) {
			bool withinBounds = checkWithinBounds(displaySettings->getMinPRA(), displaySettings->getMaxPRA());
		}

		if (!withinBounds) {
			setVisible(false);
			setSelected(false);
		}
		else if (!displaySettings->getShowNodesWithNoCompatibilities() && hasNoCompatibilities()) {
			setVisible(false);
			setSelected(false);
		}
		else if (!displaySettings->getShowNodesOnHold() && getNodeStatus()) {
			setVisible(false);
			setSelected(false);
		}
		else {
			setVisible(true);
		}
	}
	else {
		setVisible(true);
	}
}


void KPDGUINode::selectIfVisible() {
	if (isVisible()) {
		setSelected(true);
	}
}



QDataStream &operator<<(QDataStream &out, const KPDGUINode & node)
{
	out << qint32(node.getNodeID());
	out << qint32(KPDFunctions::nodeTypeToInt(node.getNodeType()));
	
	if (node.getNodeType() == PAIR){
		out << node.getCandidate();
		out << node.getCandidateStatus();
	}

	out << qint32(node.getNumberOfDonors());

	for (int i = 0; i < node.getNumberOfDonors(); i++) {
		out << node.getDonor(i);
	}

	for (int i = 0; i < node.getNumberOfDonors(); i++) {
		out << node.getDonorStatus(i);
	}

	out << node.getPrograms();
	
	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUINode & node)
{
	int internalID;
	int type;
	int numberOfDonors;
		
	in >> internalID >> type;
	KPDNodeType myType = KPDFunctions::intToNodeType(type);

	node.setNodeID(internalID);
	node.setNodeType(myType);

	if (myType == PAIR) {
		KPDGUICandidateInfo c;
		bool cStatus;

		in >> c >> cStatus;

		node.setCandidate(&c);
		node.setCandidateStatus(cStatus);
	}

	in >> numberOfDonors;

	for (int i = 0; i < numberOfDonors; i++) {
		KPDGUIDonorInfo d;
		
		in >> d;

		node.addDonor(&d);		
	}

	for (int i = 0; i < numberOfDonors; i++) {
		bool dStatus;

		in >> dStatus;

		node.setDonorStatus(dStatus,i);
	}

	QVector<QString> programs;

	in >> programs;

	node.setPrograms(programs);

	return in;
}