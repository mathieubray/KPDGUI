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
	nodeType = NDD;
	
	nodeDonors << donor;
	donor->setAltruistic(true);
}

KPDGUINode::KPDGUINode(QVector<KPDGUIDonor *> donors, KPDGUICandidate * candidate)
{
	nodeID = 0;
	nodeType = PAIR;	

	nodeCandidate = candidate;

	foreach(KPDGUIDonor * donor, donors) {
		donor->setAltruistic(false);
		nodeDonors << donor;
	}
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

KPDGUIDonor * KPDGUINode::getDonor(int k) const {
	return nodeDonors[k];
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

	
	if (nodeType == PAIR){
		if (!nodeCandidate->getStatus()) {
			return false;
		}
		else {
			foreach(KPDGUIDonor * donor, nodeDonors) {
				if (donor->getStatus()) {
					return true;
				}
			}
			return false;
		}
	}
	else {
		return nodeDonors.first()->getStatus();
	}
	
}

int KPDGUINode::getNumberOfCompatibilities() {

	int compatibilities = 0;

	if (nodeType == PAIR) {
		compatibilities += nodeCandidate->getNumberOfMatches();
	}

	foreach(KPDGUIDonor * donor, nodeDonors) {
		compatibilities += donor->getNumberOfMatches();
	}

	return compatibilities;
}

QVector<KPDCrossmatchResult> KPDGUINode::getCrossmatchResults() const {

	QVector<KPDCrossmatchResult> crossmatchResults;

	foreach(KPDGUIDonor * donor, nodeDonors) {
		crossmatchResults << donor->getCompatibilityWithPairedCandidate();
	}

	return crossmatchResults;
}

void KPDGUINode::setID(int id) {
	nodeID = id;
	
	int i = 1;
	foreach(KPDGUIDonor * donor, nodeDonors) {
		donor->setID(id);
		donor->setDonorNumber(i);
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

	donor->setParentNode(this);
	donor->setAltruistic(false);

	donor->setID(getID());
	donor->setDonorNumber(getNumberOfDonors() + 1);
	
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

/*void KPDGUINode::setCrossmatchResults(QVector<KPDCrossmatchResult> results) {

	crossmatchResults.clear();

	foreach(KPDCrossmatchResult result, results) {
		crossmatchResults << result;
	}
}*/

void KPDGUINode::clusterNode() {
	
	if (nodeType == PAIR) {
		int numberOfDonors = nodeDonors.size();

		qreal dist = 52;
		qreal donorAngle = -PI / 4;

		qreal x = nodeCandidate->getCandidatePosition().x();
		qreal y = nodeCandidate->getCandidatePosition().y();

		foreach(KPDGUIDonor * donor, nodeDonors) {
			donor->setDonorPosition(QPointF(x + dist*cos(donorAngle), y + dist*sin(donorAngle)));
			donorAngle += (2 * PI) / numberOfDonors;
		}
	}
}

QPolygonF KPDGUINode::getRect() {

	if (nodeType == PAIR) {
		return nodeCandidate->sceneBoundingRect();
	}

	else {
		return nodeDonors.at(0)->sceneBoundingRect();
	}

}

QPointF KPDGUINode::getNodePosition() {

	if (nodeType == PAIR) {
		return nodeCandidate->getCandidatePosition();
	}

	else {
		return nodeDonors.at(0)->getDonorPosition();
	}	

}

void KPDGUINode::setSelected(bool selected) {
	foreach(KPDGUIDonor * donor, nodeDonors) {
		donor->setSelected(selected);
	}

	if (nodeType == PAIR) {
		nodeCandidate->setSelected(selected);
	}
}

void KPDGUINode::setNodePosition(QPointF center) {
		
	if (nodeType == PAIR) {
		nodeCandidate->setCandidatePosition(center);
		clusterNode();
	}
	else {
		nodeDonors.first()->setDonorPosition(center);
	}	
}

void KPDGUINode::updateVisibility(KPDGUIDisplaySettings * displaySettings) {

	if (displaySettings->getNodeDisplayMode() == SEPARATE_DONOR_CANDIDATE) {
		if (nodeType == NDD) {
			nodeDonors.first()->setVisible(true);
			nodeDonors.first()->setDisplayMode(SEPARATE_DONOR_CANDIDATE);
		}
		else {
			nodeCandidate->setVisible(true);

			foreach(KPDGUIDonor * donor, nodeDonors) {
				donor->setVisible(true);
				donor->setDisplayMode(SEPARATE_DONOR_CANDIDATE);
			}
		}
	}

	if (displaySettings->getNodeDisplayMode() == COMBINE_DONOR_CANDIDATE) {
		if (nodeType == NDD) {
			nodeDonors.first()->setVisible(true);
			nodeDonors.first()->setDisplayMode(COMBINE_DONOR_CANDIDATE);
		}
		else {
			nodeCandidate->setVisible(true);

			foreach(KPDGUIDonor * donor, nodeDonors) {
				donor->setVisible(false);
				donor->setDisplayMode(COMBINE_DONOR_CANDIDATE);
			}
		}
	}

	//Only Show Nodes in Arrangements
	if (displaySettings->getShowNodesInArrangements()) {
		// If the NDD is not in the arrangement
		if (nodeType == NDD && nodeDonors.first()->getPopularityInArrangements() == 0) {
			nodeDonors.first()->setVisible(false);
			nodeDonors.first()->setSelected(false);
		}
		// If the pair is not in the arrangement
		else if (nodeType == PAIR) {
			if (nodeCandidate->getPopularityInArrangements() == 0) {
				nodeCandidate->setVisible(false);
				nodeCandidate->setSelected(false);

				foreach(KPDGUIDonor * donor, nodeDonors) {
					donor->setVisible(false);
					donor->setSelected(false);
				}
			}
		}
	}
	else if (displaySettings->getShowNodesInSolutions()) {
		// If the NDD is not in solution
		if (nodeType == NDD && nodeDonors.first()->getPopularityInSolutions() == 0) {
			nodeDonors.first()->setVisible(false);
			nodeDonors.first()->setSelected(false);
		}
		// If the pair is not in a solution
		else if (nodeType == PAIR) {
			if (nodeCandidate->getPopularityInSolutions() == 0) {
				nodeCandidate->setVisible(false);
				nodeCandidate->setSelected(false);

				foreach(KPDGUIDonor * donor, nodeDonors) {
					donor->setVisible(false);
					donor->setSelected(false);
				}
			}
		}
	}

	else if (displaySettings->getShowNodeSubset()) {

		bool display = true;

		if (nodeType == PAIR) {
			if (displaySettings->getShowCandidatesInPRARange() && (nodeCandidate->getPRA() >= displaySettings->getMaxPRA() || nodeCandidate->getPRA() <= displaySettings->getMinPRA())) {
				display = false;
			}
		}

		if (!displaySettings->getShowExcludedNodes() && !getStatus()) {
			display = false;
		}

		if (!displaySettings->getShowNodesWithNoCompatibilities() && getNumberOfCompatibilities() == 0) {
			display = false;
		}

		if (!display) {
			if (nodeType == PAIR) {
				nodeCandidate->setVisible(false);
				nodeCandidate->setSelected(false);
			}
			
			foreach(KPDGUIDonor * donor, nodeDonors) {
				donor->setVisible(false);
				donor->setSelected(false);
			}
		}
		/*else {

			if (nodeType == PAIR) {
				nodeCandidate->setVisible(true);
			}

			foreach(KPDGUIDonor * donor, nodeDonors) {
				donor->setVisible(true);
			}
		}*/
	}
	
	/*else {
		if (nodeType == PAIR) {
			nodeCandidate->setVisible(true);
		}

		foreach(KPDGUIDonor * donor, nodeDonors) {
			donor->setVisible(true);
		}
	}*/

	clusterNode();

}

void KPDGUINode::setZValue(int z) {
	foreach(KPDGUIDonor * donor, nodeDonors) {
		donor->setZValue(z + 0.5);
	}

	nodeCandidate->setZValue(z);
}

void KPDGUINode::edit() {

	if (nodeType == PAIR) {
		getCandidate()->edit();

		foreach(KPDGUIDonor * donor,getDonors()) {
			donor->edit();
		}
	}
	else {
		getFirstDonor()->edit();
	}
}

void KPDGUINode::editActions() {
	emit nodeEdited();
}

QString KPDGUINode::getNameString() {
	
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

	if (nodeType == NDD) {
		return nodeDonors.first()->getName();
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
	consoleString += ": ";
	if (nodeType == PAIR) {
		if (nodeCandidate->getStatus()) {
			consoleString += "Candidate ";
			consoleString += nodeCandidate->getName();
			consoleString += ", ";
		}
	}

	int i = 0;
	foreach(KPDGUIDonor * donor, nodeDonors) {
		i++;
		if (donor->getStatus()) {
			consoleString += "Donor ";
			consoleString += donor->getName();
			consoleString += " (";
			consoleString += QString::number(i);
			consoleString += "), ";
		}
	}
	consoleString.chop(2);

	return consoleString;
}

/*QDataStream &operator<<(QDataStream &out, const KPDGUINode & node)
{
	out << qint32(node.getID());
	out << qint32(KPDFunctions::nodeTypeToInt(node.getType()));

	qDebug() << "out << node.getID(): " << QString::number(node.getID());
	qDebug() << "out << node.getType(): " << QString::number(KPDFunctions::nodeTypeToInt(node.getType()));
	
	out << qint32(node.getNumberOfDonors());
	qDebug() << "out << node.getNumberOfDonors(): " << QString::number(node.getNumberOfDonors());

	//if (node.getType() == PAIR) {
	//	qDebug() << "out << *(node.getCandidate())";
	//	out << *(node.getCandidate());
	//}

	foreach(KPDGUIDonor * donor, node.getDonors()) {
		qDebug() << "out << *donor";
		out << *donor;
	}
	//out << node.getDonors();	
	
	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUINode & node)
{
	int id;
	int type;
		
	in >> id >> type;
	qDebug() << "in >> id >> type: " << QString::number(id) << QString::number(type);

	KPDNodeType myType = KPDFunctions::intToNodeType(type);
	
	QVector<KPDGUIDonor * > donors;
	int numberOfDonors;

	in >> numberOfDonors;
	qDebug() << "in >> numberOfDonors: " << QString::number(numberOfDonors);

	//if (myType == PAIR) {
	//	KPDGUICandidate * c = new KPDGUICandidate();

	//	qDebug() << "in >> *c:";
	//	in >> *c;

		//node.setCandidate(c);
	//}

	for (int i = 1; i <= numberOfDonors; i++) {
		
		KPDGUIDonor * d = new KPDGUIDonor();
		
		qDebug() << "in >> *d";
		in >> *d;

		donors.push_back(d);
	}

	//node.setDonors(donors);

	

	//node.setID(id);
	//node.setType(myType);

	return in;
}*/