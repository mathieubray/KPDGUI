#include "KPDGUIArrangement.h"


KPDGUIArrangement::KPDGUIArrangement() {

	arrangementID = -1;
	arrangementUtility = 0.0;

	arrangementHasAnNDD = false;
}

KPDGUIArrangement::KPDGUIArrangement(int id, double utility){

	arrangementID = id;
	arrangementUtility = utility;

	arrangementHasAnNDD = false;	
}

KPDGUIArrangement::~KPDGUIArrangement(){
	
}

void KPDGUIArrangement::setID(int id) {
	arrangementID = id;
}

void KPDGUIArrangement::setUtility(double util) {
	arrangementUtility = util;
}

void KPDGUIArrangement::addNode(KPDGUINode * node) {

	arrangementNodes.push_back(node);

	if (node->getType() == NDD) {
		arrangementHasAnNDD = true;
	}

}

void KPDGUIArrangement::addMatch(KPDGUIMatch * match) {

	if (containsDonor(match->getDonor()) && containsCandidate(match->getCandidate())){
		arrangementMatches.push_back(match);
	}

}

QVector<KPDGUINode *> KPDGUIArrangement::getNodes() {

	QVector<KPDGUINode *> arrangementNodesCopy;

	foreach(KPDGUINode * node, arrangementNodes) {
		arrangementNodesCopy.push_back(node);
	}

	return arrangementNodesCopy;

}

QList<KPDGUIMatch *> KPDGUIArrangement::getMatches() {
	
	QList<KPDGUIMatch *> arrangementMatchesCopy;

	foreach(KPDGUIMatch * match, arrangementMatches) {
		arrangementMatchesCopy.push_back(match);
	}

	return arrangementMatchesCopy;
}

int KPDGUIArrangement::getID() const {
	return arrangementID;
}

double KPDGUIArrangement::getUtility() const {
	return arrangementUtility;
}


int KPDGUIArrangement::getNumberOfNodes() {
	return arrangementNodes.size();
}

int KPDGUIArrangement::getNumberOfMatches() {
	return arrangementMatches.size();
}

bool KPDGUIArrangement::hasAnNDD() {
	return arrangementHasAnNDD;
}

bool KPDGUIArrangement::containsNode(KPDGUINode * node) {

	foreach(KPDGUINode * pair, arrangementNodes) {
		if (pair == node) {
			return true;
		}
	}

	return false;
}

bool KPDGUIArrangement::containsDonor(KPDGUIDonor * donor) {
	
	foreach(KPDGUINode * node, arrangementNodes) {

		foreach(KPDGUIDonor * d, node->getDonors()) {
			if (d == donor) {
				return true;
			}
		}
	}

	return false;
}

bool KPDGUIArrangement::containsCandidate(KPDGUICandidate * candidate) {
	
	foreach(KPDGUINode * node, arrangementNodes) {

		if (node->getType() == PAIR) {
			if (node->getCandidate() == candidate) {
				return true;
			}
		}
	}

	return false;
}

void KPDGUIArrangement::select(){
	foreach(KPDGUINode * node, arrangementNodes){
		node->setSelected(true);
	}
}

void KPDGUIArrangement::highlight(){	

	foreach(KPDGUINode * node, arrangementNodes) {
		node->setSelected(true);
	}

	foreach(KPDGUIMatch * arrow, arrangementMatches){
		arrow->highlightMatch(2);
	}
}

void KPDGUIArrangement::undoHighlights(){

	foreach(KPDGUINode * node, arrangementNodes) {
		node->setSelected(false);
	}

	foreach(KPDGUIMatch * arrow, arrangementMatches){
		arrow->endDisplayAsPartOfSolution();
	}
}

qreal KPDGUIArrangement::centerX(){
	qreal avgx = 0;

	foreach(KPDGUINode * node, arrangementNodes){
		avgx += node->getNodePosition().x();		
	}

	avgx = avgx / arrangementNodes.size();

	return avgx;
}

qreal KPDGUIArrangement::centerY(){
	qreal avgy = 0;

	foreach(KPDGUINode * node, arrangementNodes){
		avgy += node->getNodePosition().y();
	}

	avgy = avgy / arrangementNodes.size();

	return avgy;
}

void KPDGUIArrangement::cluster(){
	cluster(this->centerX(), this->centerY());
}

void KPDGUIArrangement::isolate() {
	isolate(this->minX(), this->maxX(), this->minY(), this->maxY());
}

qreal KPDGUIArrangement::minX() {
	qreal minX = 9999;

	foreach(KPDGUINode * node, arrangementNodes) {
		if (node->getNodePosition().x() < minX) {
			minX = node->getNodePosition().x();
		}
	}

	return minX;

}

qreal KPDGUIArrangement::maxX() {
	qreal maxX = -9999;

	foreach(KPDGUINode * node, arrangementNodes) {
		if (node->getNodePosition().x() > maxX) {
			maxX = node->getNodePosition().x();
		}
	}

	return maxX;
}

qreal KPDGUIArrangement::minY() {
	qreal minY = 9999;

	foreach(KPDGUINode * node, arrangementNodes) {
		if (node->getNodePosition().y() < minY) {
			minY = node->getNodePosition().y();
		}
	}

	return minY;
}

qreal KPDGUIArrangement::maxY() {
	qreal maxY = -9999;

	foreach(KPDGUINode * node, arrangementNodes) {
		if (node->getNodePosition().y() > maxY) {
			maxY = node->getNodePosition().y();
		}
	}

	return maxY;
}

void KPDGUIArrangement::cluster(qreal x, qreal y){

	qreal dist = 50 + 10 * arrangementNodes.size();

	qreal angle = (2 * PI) / arrangementNodes.size();
	qreal nodeAngle = PI;

	foreach(KPDGUINode * node, arrangementNodes){
		//node->setVisible(false);
		if (!(abs((node->getNodePosition().x()) - (x + dist*cos(nodeAngle))) < TOL && abs((node->getNodePosition().y()) - (y + dist*sin(nodeAngle)) < TOL))){
			node->setNodePosition(QPoint(x + dist*cos(nodeAngle), y + dist*sin(nodeAngle)));
		}
		nodeAngle += angle;
		//node->setVisible(true);
	}

	emit arrangementClustered(x, y);

}

void KPDGUIArrangement::isolate(qreal minX, qreal maxX, qreal minY, qreal maxY) {

	/*QList<QGraphicsItem *> collidingItems;

	foreach(KPDGUINode * node, arrangementNodes) {

		if (node->getType() == PAIR) {
			collidingItems.append(node->getCandidate()->collidingItems());
		}
		else {
			collidingItems.append(node->getFirstDonor()->collidingItems());
		}
	}
	
	int counter = 1;
	int bump = 50;

	foreach(QGraphicsItem * item, collidingItems) {

		if (counter % 2 == 0) {
			item->setPos(QPointF(minX, minY));
		}
		else {
			item->setPos(QPointF(maxX, maxY));
		}
		counter++;
	}

	emit arrangementClustered(this->centerX(), this->centerY());*/

	emit arrangementIsolated(minX, maxX, minY, maxY);
}

void KPDGUIArrangement::increasePopularity(bool solution) {

	foreach(KPDGUIMatch * match, arrangementMatches) {
		match->increasePopularity(solution);
	}
}

void KPDGUIArrangement::decreasePopularity(bool solution) {

	foreach(KPDGUIMatch * match, arrangementMatches) {
		match->decreasePopularity(solution);
	}
}

void KPDGUIArrangement::resetPopularity(bool solution) {
	foreach(KPDGUIMatch * match, arrangementMatches) {
		match->resetPopularity(solution);
	}
}

QString KPDGUIArrangement::arrangementLabel(){
	
	QString label = "";
	foreach(KPDGUINode * node, arrangementNodes) {
		label += QString::number(node->getID());
		label += ", ";
	}

	label.chop(2);

	if (arrangementUtility == floor(arrangementUtility)) {
		label += " (" + QString::number(arrangementUtility) + ")";
	}
	else {
		label += " (" + QString::number(floor(arrangementUtility * 1000 + 0.5) / 1000) + ")";
	}	

	return label;
}

QString KPDGUIArrangement::arrangementDashboardString(){
	
	QString arrangementString = QString::number(arrangementID) + ": <";
	
	foreach(KPDGUINode * node, arrangementNodes){
		arrangementString += QString::number(node->getID());
		arrangementString += ", ";
	}

	arrangementString.chop(2);
	arrangementString += ">, {";

	foreach(KPDGUIMatch * arrow, arrangementMatches) {
		QString arrowString = QString::number(arrow->getDonor()->getID()) + "(" + QString::number(arrow->getDonor()->getDonorNumber()) + ") -> " + QString::number(arrow->getCandidate()->getID());
		arrangementString += arrowString;
		arrangementString += ", ";
	}
	arrangementString.chop(2);
	
	if (floor(arrangementUtility) == arrangementUtility) {
		arrangementString += "}, [" + QString::number(arrangementUtility) + "]";
	}
	else {
		arrangementString += "}, [" + QString::number(floor(arrangementUtility * 1000 + 0.5) / 1000) + "]";
	}

	return arrangementString;
}

