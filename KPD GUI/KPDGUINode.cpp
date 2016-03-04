#include "KPDGUINode.h"
#include "KPDGUIArrow.h"

#include "DialogDonor.h"

KPDGUINode::KPDGUINode() {
	pairType = KPDPairType::PAIR;
	holdStatus = false;

	setAdditionalProperties();	
}

KPDGUINode::KPDGUINode(Donor d, bool hold) : donor(d)
{
	pairType = KPDPairType::AD;
	holdStatus = hold;

	myDonor = new QGraphicsEllipseItem();
	myDonor->setRect(QRectF(0, 0, 75, 65));
	
	addToGroup(myDonor);

	setAdditionalProperties();
	
}

KPDGUINode::KPDGUINode(Donor d, Candidate c, bool hold) : donor(d), candidate(c)
{
	pairType = KPDPairType::PAIR;
	holdStatus = hold;

	qreal dist = 45;
	qreal donorAngle = -PI / 4;

	myRecip = new QGraphicsEllipseItem();
	myRecip->setRect(QRectF(0, 0, 65, 55));
	myRecip->setZValue(1);

	addToGroup(myRecip);

	myDonor = new QGraphicsEllipseItem();
	myDonor->setRect(QRectF(dist*cos(donorAngle), dist*sin(donorAngle), 45, 35));
	myDonor->setZValue(40000);

	addToGroup(myDonor);


	setAdditionalProperties();	
}

KPDGUINode::~KPDGUINode()
{
	foreach(KPDGUIArrow *link, myInArrows)
		delete link;
	foreach(KPDGUIArrow *link, myOutArrows)
		delete link;
}

void KPDGUINode::setAdditionalProperties(){
	setBackgroundColors();
	setZValue(0);
	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);

	popularityInStructures = 0;
	popularityInSolutions = 0;
}

void KPDGUINode::setText(const QString &text)
{
    prepareGeometryChange();
    myText = text;
    update();
}

QString KPDGUINode::text() const
{
    return myText;
}

void KPDGUINode::setBackgroundColors()
{
	if (holdStatus){
		if (pairType == PAIR){
			myRecipBackgroundColor = QColor(100, 100, 100);
			myDonorBackgroundColor = QColor(100, 100, 125);
		}
		else {
			myDonorBackgroundColor = QColor(100, 100, 125);
		}
	}
	else {
		if (pairType == PAIR){
			myRecipBackgroundColor = QColor(255, candidate.getPRA() * 1.5, candidate.getPRA() * 1.5);
			myDonorBackgroundColor = QColor(0, 0, 255);
		}
		else {
			myDonorBackgroundColor = QColor(0, 0, 255);
		}
	}

    update();
}

QColor KPDGUINode::donorBackgroundColor() const
{
    return myDonorBackgroundColor;
}

QColor KPDGUINode::recipBackgroundColor() const
{
	return myRecipBackgroundColor;
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
	painter->setBrush(QBrush(myDonorBackgroundColor, Qt::SolidPattern));

	QRectF donorRect = myDonor->boundingRect();
	painter->drawEllipse(donorRect);
	
	painter->setPen(QPen(myTextColor, 16, Qt::SolidLine, Qt::RoundCap));

	QFont * font = new QFont();
	font->setBold(true);
	font->setPointSize(8);
	painter->setFont(*font);

	painter->drawText(donorRect, Qt::AlignCenter, QString::number(internalID));

	if (pairType == PAIR){
		painter->setPen(pen);
		painter->setBrush(QBrush(myRecipBackgroundColor, Qt::SolidPattern));

		QRectF recipRect = myRecip->boundingRect();
		painter->drawEllipse(recipRect);

		painter->setPen(QPen(myTextColor, 16, Qt::SolidLine, Qt::RoundCap));

		QFont * font = new QFont();
		font->setBold(true);
		font->setPointSize(8);
		painter->setFont(*font);

		//painter->drawText(recipRect, Qt::AlignCenter, QString::number(internalID));
	}
	
}

void KPDGUINode::addInArrow(KPDGUIArrow *link)
{
	myInArrows.insert(link);
}

void KPDGUINode::removeInArrow(KPDGUIArrow *link)
{
	myInArrows.remove(link);
}

void KPDGUINode::addOutArrow(KPDGUIArrow *link)
{
	myOutArrows.insert(link);
}

void KPDGUINode::removeOutArrow(KPDGUIArrow *link)
{
	myOutArrows.remove(link);
}

KPDGUIArrow * KPDGUINode::findOutArrow(KPDGUINode * toNode){
	foreach(KPDGUIArrow * arrow, myOutArrows){
		if (arrow->endItem() == toNode){
			return arrow;
		}
	}

	return NULL;
}

bool KPDGUINode::hasNoCompatibilities(){
	if (myInArrows.count() + myOutArrows.count() == 0){
		return true;
	}
	return false;
}

int KPDGUINode::getNumberOfCompatibilities(){
	return myInArrows.count() + myOutArrows.count();
}

int KPDGUINode::getNumberOfCompatibleDonors(){
	return myInArrows.count();
}

int KPDGUINode::getNumberOfCompatibleRecipients(){
	return myOutArrows.count();
}

int KPDGUINode::getNumberOfAssociatedDonors(){
	return 1;
}

int KPDGUINode::getPopularityInStructures(){
	return popularityInStructures;
}

int KPDGUINode::getPopularityInSolutions(){
	return popularityInSolutions;
}

void KPDGUINode::increasePopularityInStructures(){
	popularityInStructures++;
}

void KPDGUINode::increasePopularityInSolutions(){
	popularityInSolutions++;
}

void KPDGUINode::decreasePopularityInStructures(){
	popularityInStructures--;
}

void KPDGUINode::decreasePopularityInSolutions(){
	popularityInSolutions--;
}

void KPDGUINode::resetPopularityInStructures(){
	popularityInStructures = 0;
}

void KPDGUINode::resetPopularityInSolutions(){
	popularityInSolutions = 0;
}

bool KPDGUINode::getHoldStatus() const{
	return holdStatus;
}

void KPDGUINode::setHoldStatus(bool hold){
	holdStatus = hold;
	setBackgroundColors();

	emit nodeHoldStatusChanged(internalID, holdStatus);
}

void KPDGUINode::editNode(){
	
}

QGraphicsEllipseItem * KPDGUINode::getDonorItem(){
	return myDonor;
}

QGraphicsEllipseItem * KPDGUINode::getRecipItem(){
	return myRecip;
}

QPointF KPDGUINode::getDonorCenter(){

	//qreal x = myDonor->mapFromScene(myDonor->boundingRect().x());
	//qreal y = myDonor->mapFromScene(myDonor->boundingRect().y());
	QPointF point = mapToScene(myDonor->boundingRect().topLeft());
	qreal x = point.x();
	qreal y = point.y();
	
	qreal width = myDonor->boundingRect().width();
	qreal height = myDonor->boundingRect().height();

	qDebug() << internalID << " DONOR CENTER " << x << " " << y << " " << width << " " << height;

	return QPointF(x + width / 2, y + height / 2);
}

QPointF KPDGUINode::getRecipCenter(){

	QPointF point = mapToScene(myRecip->boundingRect().topLeft());
	qreal x = point.x();
	qreal y = point.y();
	qreal width = myRecip->boundingRect().width();
	qreal height = myRecip->boundingRect().height();

	qDebug() << internalID << " RECIP CENTER " << x << " " << y << " " << width << " " << height;

	return QPointF(x + width / 2, y + height / 2);
	//return QPointF(x + 55*cos((-1)*PI/4)+width / 2, y + 55*sin((-1)*PI/4) + height / 2);
}

int KPDGUINode::getInternalID() const{
	return internalID;
}

void KPDGUINode::setInternalID(int id){
	internalID = id;

	if (pairType == PAIR){
		setToolTip("Pair " + QString::number(id));
	}
	else {
		setToolTip("AD " + QString::number(id));
	}
}

void KPDGUINode::setDonor(Donor d){
	
	donor = d;
}

void KPDGUINode::setCandidate(Candidate c){
	
	candidate = c;	
}

KPDPairType KPDGUINode::getType() const{
	return pairType;
}

void KPDGUINode::setType(KPDPairType type){
	pairType = type;
}

Candidate KPDGUINode::getCandidate() const{
	return candidate;
}

Donor KPDGUINode::getDonor() const{
	return donor;
}

QString KPDGUINode::getDonorName() const {
	return donor.getName();
}

int	KPDGUINode::getDonorAge() const {
	return donor.getAge();
}

KPDBloodType KPDGUINode::getDonorBT() const {
	return donor.getBT();
}

QString	KPDGUINode::getCandidateName() const {
	return candidate.getName();
}

int	KPDGUINode::getCandidateAge() const {
	return candidate.getAge();
}

KPDBloodType KPDGUINode::getCandidateBT() const{
	return candidate.getBT();
}

int	KPDGUINode::getCandidatePRA() const {
	return candidate.getPRA();
}

QString KPDGUINode::getNameString(){

	if (pairType == AD){
		return "AD: " + donor.getName();
	}
	else {
		return candidate.getName() + "/" + donor.getName();
	}

}

QString KPDGUINode::getCompatibleDonorString(){
	QString compatibleDonorString = "Compatible Donors: ";

	if (myInArrows.count() > 0){
		QVector<int> compatibleDonors;
		foreach(KPDGUIArrow * arrow, myInArrows){
			compatibleDonors.push_back(arrow->startItem()->getInternalID());
		}
		qSort(compatibleDonors);
		foreach(int id, compatibleDonors){
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

QString KPDGUINode::getCompatibleRecipientsString(){
	QString compatibleRecipientString = "Compatible Recipients: ";

	if (myOutArrows.count() > 0){
		QVector<int> compatibleRecipients;
		foreach(KPDGUIArrow * arrow, myOutArrows){
			compatibleRecipients.push_back(arrow->endItem()->getInternalID());
		}
		qSort(compatibleRecipients);
		foreach(int id, compatibleRecipients){
			compatibleRecipientString += QString::number(id);
			compatibleRecipientString += ", ";
		}
		compatibleRecipientString.chop(2);
	}
	else {
		compatibleRecipientString += "None";
	}

	return compatibleRecipientString;
}

QString KPDGUINode::getConsoleString(){
	QString consoleString = "";
	
	if (pairType == PAIR){
		consoleString += "Pair ";
	}
	else {
		consoleString += "AD ";
	}
	consoleString += QString::number(getInternalID());
	
	if (getHoldStatus()){
		consoleString += "(ON HOLD)";
	}
	//MOVE
	/*
	consoleString += "\nDonor: ";
	consoleString += getDonorName();
	consoleString += " (";
	consoleString += getDonorBT();
	consoleString += ")";
	if (donor.type == PAIR){
		consoleString += ", Candidate: ";
		consoleString += getRecipName();
		consoleString += " (";
		consoleString += getRecipBT();
		consoleString += ")";
	}
	consoleString += "\n\nDonor HLA : ";

	QString donorHLAString = getFullDonorHLAString();
	donorHLAString.replace(";", " ");
	if (donorHLAString.size() > 0){
		consoleString += donorHLAString;
	}
	else {
		consoleString += "None";
	}

	if (donor.type == PAIR){
		consoleString += "\nCandidate HLA: ";

		QString recipHLAString = getRecipHLAString();
		recipHLAString.replace(";", " ");
		if (recipHLAString.size() > 0){
			consoleString += recipHLAString;
		}
		else {
			consoleString += "None";
		}
	}

	consoleString += "\n";
	if (donor.type == PAIR){
		consoleString += "\n";
		consoleString += getCompatibleDonorString();
		consoleString += "\n";
	}
	consoleString += getCompatibleRecipientsString();
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
		foreach(KPDGUIArrow *link, myInArrows)
			link->updatePosition();
		foreach(KPDGUIArrow *link, myOutArrows)
			link->updatePosition();
	}

	if (change == ItemSelectedHasChanged) {
		emit nodeSelectionChanged(internalID, value.toBool());
	}

	return QGraphicsItem::itemChange(change, value);
}

void KPDGUINode::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
		
	qDebug() << "Entered!";
	emit nodeEntered(internalID);
}

void KPDGUINode::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
	qDebug() << "Left";
	emit nodeLeft(internalID);
}

void KPDGUINode::mousePressEvent(QGraphicsSceneMouseEvent *event){

	setSelected(true);
	
	emit nodeWasClicked(internalID,isSelected());
}

void KPDGUINode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event){
	
	editNode();
	
	//QGraphicsObject::mouseDoubleClickEvent(event);
}


bool KPDGUINode::checkWithinBounds(bool pairsOfMinPRA, int minPRA, bool pairsOfMaxPRA, int maxPRA){
	if (pairType == AD){
		return true;
	}
	else {
		if (pairsOfMinPRA){
			if (minPRA > candidate.getPRA()){
				return false;
			}
		}

		if (pairsOfMaxPRA){
			if (maxPRA < candidate.getPRA()){
				return false;
			}
		}

		return true;
	}
}

void KPDGUINode::updateVisibility(KPDGUIDisplaySettings * displaySettings){

	qDebug() << "Update Visibility of Node " << getInternalID();

	if (displaySettings->getShowPairsInStructures()){
		if (getPopularityInStructures() == 0){
			setVisible(false);
			setSelected(false);
		}
	}
	else if (displaySettings->getShowPairsInSolutions()){
		if (getPopularityInSolutions() == 0){
			setVisible(false);
			setSelected(false);
		}
	}

	else if (displaySettings->getShowPairSubset()){

		bool withinBounds = checkWithinBounds(displaySettings->getShowPairsOfMinPRA(), displaySettings->getMinPRA(), displaySettings->getShowPairsOfMaxPRA(), displaySettings->getMaxPRA());
		
		if (!withinBounds){
			setVisible(false);
			setSelected(false);
		}
		else if (!displaySettings->getShowPairsWithNoCompatibilities() && hasNoCompatibilities()){
			setVisible(false);
			setSelected(false);
		}
		else if (!displaySettings->getShowPairsOnHold() && getHoldStatus()){
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

void KPDGUINode::selectIfVisible(){
	if (isVisible()){
		setSelected(true);
	}
}

QDataStream &operator<<(QDataStream &out, const KPDGUINode & node)
{
	out << qint32(node.getInternalID());
	out << qint32(KPDFunctions::pairTypeToInt(node.getType()));
	out << node.getDonor();
	
	if (node.getType() == PAIR){
		out << node.getCandidate();
	}

	out << node.getHoldStatus();
	
	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUINode & node)
{
	int internalID;
	int type;
	Donor d;
	Candidate c;
	bool hold;
	
	in >> internalID;
	in >> type;
	KPDPairType pairType = KPDFunctions::intToPairType(type);
	in >> d;
	if (pairType == PAIR){
		in >> c;
	}	
	in >> hold;
	
	node.setInternalID(internalID);
	node.setType(pairType);
	node.setDonor(d);
	if (pairType == PAIR){
		node.setCandidate(c);
	}
	node.setHoldStatus(hold);

	return in;
}