#include "KPDGUINode.h"
#include "KPDGUIMatch.h"

#include "DialogDonor.h"

KPDGUINode::KPDGUINode()
{
	nodeID = 0;
	nodeType = PAIR;

}

KPDGUINode::KPDGUINode(KPDGUIDonor * donor)
{
	nodeID = 0;
	nodeType = AD;
	
	nodeDonors << donor;
	donor->setAltruistic(true);
}

KPDGUINode::KPDGUINode(QVector<KPDGUIDonor *> donors, KPDGUICandidate * candidate)
{
	nodeID = 0;
	nodeType = PAIR;
	
	foreach(KPDGUIDonor * donor, donors) {
		donor->setAltruistic(false);
		nodeDonors << donor;
	}

	nodeCandidate = candidate;
}

KPDGUINode::~KPDGUINode()
{
	foreach(KPDGUIDonor * donor, nodeDonors) {
		delete donor;
	}

	delete nodeCandidate;
}

int KPDGUINode::getID() const {
	return nodeID;
}

KPDNodeType KPDGUINode::getType() const {
	return nodeType;
}

QVector<KPDGUIDonor *> KPDGUINode::getDonors() const {
	return nodeDonors;
}

KPDGUIDonor * KPDGUINode::getFirstDonor() const {
	return nodeDonors.first();
}

int KPDGUINode::getNumberOfDonors() const {
	return nodeDonors.size();
}

KPDGUICandidate * KPDGUINode::getCandidate() const {
	return nodeCandidate;
}

bool KPDGUINode::getStatus() {

	if (nodeCandidate->getStatus()) {
		return true;
	}
	else {
		foreach(KPDGUIDonor * donor, nodeDonors) {
			if (!(donor->getStatus())) {
				return false;
			}
		}

		return true;
	}
}

QVector<QString> KPDGUINode::getPrograms() const {
	return nodePrograms;
}

int KPDGUINode::getNumberOfPrograms() const {
	return nodePrograms.size();
}

void KPDGUINode::setID(int id) {
	nodeID = id;

	qDebug() << "Setting ID";

	int i = 1;
	foreach(KPDGUIDonor * donor, nodeDonors) {
		
		qDebug() << "Setting ID for Donor " << i;

		donor->setID(id);
		donor->setDonorNumber(i);

		qDebug() << "Donor ID" << donor->getID() << " " << donor->getDonorNumber();
		i++;
	}

	if (nodeType == PAIR) {
		nodeCandidate->setID(id);
	}
}

void KPDGUINode::setType(KPDNodeType type) {
	nodeType = type;
}

void KPDGUINode::setDonors(QVector<KPDGUIDonor *> donors) {

	nodeDonors.clear();

	foreach(KPDGUIDonor * donor, donors) {
		nodeDonors << donor;
	}

	clusterNode();
}

void KPDGUINode::addDonor(KPDGUIDonor * donor) {

	nodeDonors << donor;

	clusterNode();

}

void KPDGUINode::removeDonor(KPDGUIDonor * donor) {

	int position = nodeDonors.indexOf(donor);

	if (position > -1) {
		nodeDonors.remove(position);
	}

	clusterNode();
}

void KPDGUINode::setCandidate(KPDGUICandidate * c) {
	nodeCandidate = c;
}

void KPDGUINode::setPrograms(QVector<QString> programs) {

	nodePrograms.clear();

	foreach(QString program, programs) {
		nodePrograms << program;
	}
}

void KPDGUINode::addProgram(QString program) {
	nodePrograms << program;
}

void KPDGUINode::removeProgram(QString program) {
	int position = nodePrograms.indexOf(program);

	if (position > -1) {
		nodePrograms.remove(position);
	}
}

void KPDGUINode::clusterNode() {
	
	if (nodeType == PAIR) {
		int numberOfDonors = nodeDonors.size();

		qreal dist = 45;
		qreal donorAngle = -PI / 4;

		qreal x = nodeCandidate->x();
		qreal y = nodeCandidate->y();

		foreach(KPDGUIDonor * donor, nodeDonors) {
			donor->setX(x + dist*cos(donorAngle));
			donor->setY(y + dist*sin(donorAngle));
			donorAngle += (2 * PI) / numberOfDonors;
		}
	}
}

QPointF KPDGUINode::getNodePosition() {

	if (nodeType == PAIR) {
		return nodeCandidate->getCenter();
	}

	else {
		return nodeDonors.at(0)->getCenter();
	}	

}

void KPDGUINode::setSelected(bool selected) {
	foreach(KPDGUIDonor * donor, nodeDonors) {
		donor->setSelected(selected);
	}

	nodeCandidate->setSelected(selected);
}

void KPDGUINode::setNodePosition(QPointF center) {
		
	if (nodeType == PAIR) {
		nodeCandidate->setPos(center);
	}
	else {
		nodeDonors.at(0)->setPos(center);
	}

	clusterNode();
}

void KPDGUINode::updateNodeVisibility(KPDGUIDisplaySettings * displaySettings) {

	/*if (displaySettings->getShowNodesInStructures()) {
		if (nodeType == AD && nodeDonors.first()->getPopularityInStructures() == 0) {
			nodeCandidate->setVisible(false);
			nodeCandidate->setSelected(false);
		}
		else if (nodeType == PAIR) {
			if (nodeCandidate->getPopularityInStructures() == 0) {
				setVisible(false);
				setSelected(false);
			}
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
	}*/
}

void KPDGUINode::setZValue(int z) {
	foreach(KPDGUIDonor * donor, nodeDonors) {
		donor->setZValue(z + 0.5);
	}

	nodeCandidate->setZValue(z);
}

void KPDGUINode::updateVisibility(KPDGUIDisplaySettings * displaySettings) {

}

QString KPDGUINode::getNameString() {
	
	qDebug() << "Donor ID: " << nodeDonors.first()->getID();

	QString nameString = "";
	
	if (nodeType == PAIR) {
		nameString += nodeCandidate->getName() + " (" + QString::number(nodeCandidate->getID()) + "), ";

		if (nodeDonors.size() == 1) {
			nameString += nodeDonors.first()->getName() + " (" + QString::number(nodeDonors.first()->getDonorNumber()) + ")";
		}
		else {
			nameString += "{";
			foreach(KPDGUIDonor * donor, nodeDonors) {
				nameString += donor->getName() + " (" + QString::number(donor->getDonorNumber()) + "), ";
			}
			nameString.chop(2);
			nameString += "}";			
		}
	}
	else {
		nameString += nodeDonors.first()->donorString();
	}


	return nameString;
}

QString KPDGUINode::getNodeListString() {

	// Should be drawn from Candidate and Donor files

	if (nodeType == AD) {
		return "AD: " + nodeDonors.first()->getName();
	}
	else {
		QString nameString = nodeCandidate->getName() + "/";
		foreach(KPDGUIDonor * donor, nodeDonors) {
			nameString += donor->getName() + ",";
		}
		nameString.chop(1);

		return nameString;
	}

}


QString KPDGUINode::getDashboardString() {
	QString consoleString = "";

	if (nodeType == PAIR) {
		consoleString += "Pair ";
	}
	else {
		consoleString += "AD ";
	}
	consoleString += QString::number(nodeID);
	consoleString += " (";
	if (nodeCandidate->getStatus()) {
		consoleString += "Candidate on hold, ";
	}

	int i = 0;
	foreach(KPDGUIDonor * donor, nodeDonors) {
		i++;
		if (donor->getStatus()) {
			consoleString += "Donor ";
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
	if (nodeDonors[i]->type == PAIR){
	consoleString += ", Candidate: ";
	consoleString += getCandidateName();
	consoleString += " (";
	consoleString += getCandidateBT();
	consoleString += ")";
	}
	consoleString += "\n\nKPDGUIDonor HLA : ";

	QString donorHLAString = getFullDonorHLAString();
	donorHLAString.replace(";", " ");
	if (donorHLAString.size() > 0){
	consoleString += donorHLAString;
	}
	else {
	consoleString += "None";
	}

	if (nodeDonors[i]->type == PAIR){
	consoleString += "\nKPDGUICandidate HLA: ";

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
	if (nodeDonors[i]->type == PAIR){
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

QDataStream &operator<<(QDataStream &out, const KPDGUINode & node)
{
	out << qint32(node.getID());
	out << qint32(KPDFunctions::nodeTypeToInt(node.getType()));
	
	//out << node.getDonors();

	if (node.getType() == PAIR){
		//out << node.getCandidate();
	}
	
	out << node.getPrograms();
	
	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUINode & node)
{
	int id;
	int type;
		
	in >> id >> type;

	KPDNodeType myType = KPDFunctions::intToNodeType(type);

	node.setID(id);
	node.setType(myType);

	//QVector<KPDGUIDonor * > donors;

	//in >> donors;

	//node.setDonors(donors);

	if (myType == PAIR) {
		//KPDGUICandidate c;
		
		//in >> c;
		
		//node.setCandidate(&c);
	}	

	QVector<QString> programs;

	in >> programs;

	node.setPrograms(programs);

	return in;
}