#include "KPDGUIStructure.h"

KPDGUIStructure::KPDGUIStructure(QVector<KPDGUINode *> nodeList, KPDOptimizationScheme optScheme, double utility, int id){
	structureNodeList = nodeList;
	structureOptScheme = optScheme;
	
	structureUtility = utility;
	structureID = id;
	
	//Set altruistic donor flag
	structureHasAnAD = false;
	for (int q = 0; q < structureNodeList.size(); q++){
		if (structureHasAnAD == false){
			KPDGUINode * node = structureNodeList.first();
			structureNodeList.removeFirst();
			structureNodeList.push_back(node);

			if (structureNodeList.first()->getType() == AD){
				structureHasAnAD = true;
			}
		}
	}

	//Find corresponding arrows
	if (optScheme == KPDOptimizationScheme::MUC || optScheme == KPDOptimizationScheme::MEUC){
		for (int j = 0; j < structureNodeList.size() - 1; j++){
			KPDGUINode * firstNode = structureNodeList.at(j);
			KPDGUINode * secondNode = structureNodeList.at(j + 1);
			
			QVector<KPDGUIDonor *> donors = firstNode->getDonors();

			foreach (KPDGUIDonor * donor, donors) {
				KPDGUIMatch * match = donor->findMatchingCandidate(secondNode->getCandidate());
				if (match != NULL) {
					structureMatches << match;
				}
			}
		}

		if (!structureHasAnAD){

			QVector<KPDGUIDonor *> donors = structureNodeList.last()->getDonors();

			foreach(KPDGUIDonor * donor, donors) {
				KPDGUIMatch * match = donor->findMatchingCandidate(structureNodeList.first()->getCandidate());
				if (match != NULL) {
					structureMatches << match;
				}
			}
		}
	}
	
	else {
		for (int j = 0; j < structureNodeList.size(); j++){
			KPDGUINode * firstNode = structureNodeList.at(j);
			QVector<KPDGUIDonor *> donors = firstNode->getDonors();

			for (int k = 0; k < structureNodeList.size(); k++){
				if (j != k){
					KPDGUINode * secondNode = structureNodeList.at(k);

					foreach(KPDGUIDonor * donor, donors) {
						KPDGUIMatch * match = donor->findMatchingCandidate(secondNode->getCandidate());
						if (match != NULL) {
							structureMatches.insert(match);
						}
					}
				}
			}
		}
	}
}

KPDGUIStructure::~KPDGUIStructure(){
	
}

void KPDGUIStructure::select(){
	foreach(KPDGUINode * node, structureNodeList){
		node->setSelected(true);
	}
}

void KPDGUIStructure::highlight(){	
	foreach(KPDGUIMatch * arrow, structureMatches){
		arrow->highlightMatch(1);
	}
}

void KPDGUIStructure::undoHighlights(){
	foreach(KPDGUIMatch * arrow, structureMatches){
		arrow->endDisplayAsPartOfSolution();
	}
}

qreal KPDGUIStructure::centerX(){
	qreal avgx = 0;

	foreach(KPDGUINode * node, structureNodeList){
		avgx += node->getNodePosition().x();		
	}

	avgx = avgx / structureNodeList.size();

	return avgx;
}

qreal KPDGUIStructure::centerY(){
	qreal avgy = 0;

	foreach(KPDGUINode * node, structureNodeList){
		avgy += node->getNodePosition().y();
	}

	avgy = avgy / structureNodeList.size();

	return avgy;
}

void KPDGUIStructure::cluster(){
	qreal dist = 50 + 10*structureNodeList.size();

	qreal angle = (2 * PI) / structureNodeList.size();
	qreal nodeAngle = PI;

	qreal centerX = this->centerX();
	qreal centerY = this->centerY();

	foreach(KPDGUINode * node, structureNodeList){
		//node->setVisible(false);
		if (!(abs((node->getNodePosition().x()) - (centerX + dist*cos(nodeAngle))) < TOL && abs((node->getNodePosition().y()) - (centerY + dist*sin(nodeAngle)) < TOL))){
			node->setNodePosition(QPoint(centerX + dist*cos(nodeAngle), centerY + dist*sin(nodeAngle)));
		}		
		nodeAngle += angle;
		//node->setVisible(true);
	}
}

void KPDGUIStructure::cluster(qreal x, qreal y){

	qreal dist = 50 + 10 * structureNodeList.size();

	qreal angle = (2 * PI) / structureNodeList.size();
	qreal nodeAngle = PI;

	foreach(KPDGUINode * node, structureNodeList){
		//node->setVisible(false);
		if (!(abs((node->getNodePosition().x()) - (x + dist*cos(nodeAngle))) < TOL && abs((node->getNodePosition().y()) - (y + dist*sin(nodeAngle)) < TOL))){
			node->setNodePosition(QPoint(x + dist*cos(nodeAngle), y + dist*sin(nodeAngle)));
		}
		nodeAngle += angle;
		//node->setVisible(true);
	}
}

QString KPDGUIStructure::text(){
	QString myText;

	QString structureString = "";
	foreach(KPDGUINode * node, structureNodeList){
		structureString += QString::number(node->getID());
		structureString += ", ";
	}

	structureString.chop(2);

	structureString += " (" + QString::number(structureUtility) + ")";

	myText = structureString;
	return myText;
}

int KPDGUIStructure::size(){
	return structureNodeList.size();
}

bool KPDGUIStructure::hasAnAD(){
	return structureHasAnAD;
}

bool KPDGUIStructure::contains(KPDGUINode * node){
	foreach(KPDGUINode * pair, structureNodeList){
		if (pair == node){
			return true;
		}
	}

	return false;
}

double KPDGUIStructure::getUtility() const{
	return structureUtility;
}

int KPDGUIStructure::getID() const{
	return structureID;
}

void KPDGUIStructure::increasePopularity(bool solution){
	
	foreach(KPDGUIMatch * match, structureMatches){
		match->increasePopularity(solution);
	}
}

void KPDGUIStructure::decreasePopularity(bool solution){
	
	foreach(KPDGUIMatch * match, structureMatches) {
		match->decreasePopularity(solution);
	}
}

void KPDGUIStructure::resetPopularity(bool solution){
	foreach(KPDGUIMatch * match, structureMatches) {
		match->resetPopularity(solution);
	}
}

QString KPDGUIStructure::structureString(){
	QString structureString = "";

	if (structureOptScheme == KPDOptimizationScheme::SCC){
		structureString += "Component #" + QString::number(structureID) + " (";
	}
	else {
		if (structureHasAnAD){
			structureString += "Chain #" + QString::number(structureID) + " (";
		}
		else{
			structureString += "Cycle #" + QString::number(structureID) + " (";
		}
	}

	foreach(KPDGUINode * node, structureNodeList){
		structureString += QString::number(node->getID());
		structureString += ", ";
	}

	structureString.chop(2);
	structureString += "): ";

	if (structureOptScheme == KPDOptimizationScheme::MUC || structureOptScheme == KPDOptimizationScheme::MEUC){
		QString nodeString = "";
		for (int j = 0; j < structureNodeList.size() - 1; j++){
			KPDGUINode * firstPair = structureNodeList.at(j);
			KPDGUINode * secondPair = structureNodeList.at(j + 1);
			nodeString = nodeString + QString::number(firstPair->getID()) + "->" + QString::number(secondPair->getID()) + ", ";
		}
		if (!structureHasAnAD){
			nodeString = nodeString + QString::number(structureNodeList.last()->getID()) + "->" + QString::number(structureNodeList.first()->getID()) + ", ";
		}
		nodeString.chop(2);
		structureString += nodeString;
	}
	else {
		foreach(KPDGUIMatch * arrow, structureMatches){
			QString arrowString = QString::number(arrow->getDonor()->getID()) + " (" + QString::number(arrow->getDonor()->getDonorNumber()) + " -> " + QString::number(arrow->getCandidate()->getID());
			structureString += arrowString;
			structureString += ", ";
		}
		structureString.chop(2);
	}

	structureString += " (" + QString::number(structureUtility) + ")";

	return structureString;
}


QList<QTreeWidgetItem *> KPDGUIStructure::getItemList(){
	QList<QTreeWidgetItem *> newList;
	foreach(KPDGUINode * node, structureNodeList){
		KPDGUINodeWrapper * wrapper = new KPDGUINodeWrapper(node);
		newList.push_back(wrapper);
	}

	return newList;
}