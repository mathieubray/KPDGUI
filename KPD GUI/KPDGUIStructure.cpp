#include "KPDGUIStructure.h"

//const qreal PI = 3.14159265;
//const qreal TOL = 3;

KPDGUIStructure::KPDGUIStructure(QVector<KPDGUINode *> pairList, KPDOptimizationScheme optScheme, double utility, int id){
	myPairList = pairList;
	myOptScheme = optScheme;
	myUtility = utility;
	myID = id;
	
	//Set chain flag
	chain = false;
	for (int q = 0; q < myPairList.size(); q++){
		if (chain == false){
			KPDGUINode * node = myPairList.first();
			myPairList.removeFirst();
			myPairList.push_back(node);

			if (myPairList.first()->getNodeType() != PAIR){
				chain = true;
			}
		}
	}

	//Find corresponding arrows
	if (optScheme == KPDOptimizationScheme::MUC || optScheme == KPDOptimizationScheme::MEUC){
		for (int j = 0; j < myPairList.size() - 1; j++){
			KPDGUINode * firstPair = myPairList.at(j);
			KPDGUINode * secondPair = myPairList.at(j + 1);
			
			//FIX

			KPDGUIMatch * arrow = firstPair->findCandidateMatch(secondPair,0);
			myArrows.insert(arrow);
		}

		if (!chain){

			// FIX

			KPDGUIMatch * arrow = myPairList.last()->findCandidateMatch(myPairList.first(),0);
			if (arrow != NULL){
				myArrows.insert(arrow);
			}			
		}
	}
	
	else {
		for (int j = 0; j < myPairList.size(); j++){
			for (int k = 0; k < myPairList.size(); k++){
				if (j != k){

					// FIX

					KPDGUIMatch * arrow = myPairList.at(j)->findCandidateMatch(myPairList.at(k), 0);
					if (arrow != NULL){
						myArrows.insert(arrow);
					}
				}
			}
		}
	}
}

KPDGUIStructure::~KPDGUIStructure(){
	
}

void KPDGUIStructure::select(){
	foreach(KPDGUINode * node, myPairList){
		node->setSelected(true);
	}
}

void KPDGUIStructure::highlight(){	
	foreach(KPDGUIMatch * arrow, myArrows){
		arrow->highlightMatch(1);
	}
}

void KPDGUIStructure::undoHighlights(){
	foreach(KPDGUIMatch * arrow, myArrows){
		arrow->endDisplayAsPartOfSolution();
	}
}

qreal KPDGUIStructure::centerX(){
	qreal avgx = 0;

	foreach(KPDGUINode * node, myPairList){
		avgx += node->x();		
	}

	avgx = avgx / myPairList.size();

	return avgx;
}

qreal KPDGUIStructure::centerY(){
	qreal avgy = 0;

	foreach(KPDGUINode * node, myPairList){
		avgy += node->y();
	}

	avgy = avgy / myPairList.size();

	return avgy;
}

void KPDGUIStructure::cluster(){
	qreal dist = 50 + 10*myPairList.size();

	qreal angle = (2 * PI) / myPairList.size();
	qreal nodeAngle = PI;

	qreal centerX = this->centerX();
	qreal centerY = this->centerY();

	foreach(KPDGUINode * node, myPairList){
		node->setVisible(false);
		if (!(abs((node->x()) - (centerX + dist*cos(nodeAngle))) < TOL && abs((node->y()) - (centerY + dist*sin(nodeAngle)) < TOL))){
			node->setPos(QPoint(centerX + dist*cos(nodeAngle), centerY + dist*sin(nodeAngle)));
		}		
		nodeAngle += angle;
		node->setVisible(true);
	}
}

void KPDGUIStructure::cluster(qreal x, qreal y){

	qreal dist = 50 + 10 * myPairList.size();

	qreal angle = (2 * PI) / myPairList.size();
	qreal nodeAngle = PI;

	foreach(KPDGUINode * node, myPairList){
		node->setVisible(false);
		if (!(abs((node->x()) - (x + dist*cos(nodeAngle))) < TOL && abs((node->y()) - (y + dist*sin(nodeAngle)) < TOL))){
			node->setPos(QPoint(x + dist*cos(nodeAngle), y + dist*sin(nodeAngle)));
		}
		nodeAngle += angle;
		node->setVisible(true);
	}
}

QString KPDGUIStructure::text(){
	QString myText;

	QString structureString = "";
	foreach(KPDGUINode * node, myPairList){
		structureString += QString::number(node->getNodeID());
		structureString += ", ";
	}

	structureString.chop(2);

	structureString += " (" + QString::number(myUtility) + ")";

	myText = structureString;
	return myText;
}

int KPDGUIStructure::size(){
	return myPairList.size();
}

bool KPDGUIStructure::isChain(){
	return chain;
}

bool KPDGUIStructure::contains(KPDGUINode * node){
	foreach(KPDGUINode * pair, myPairList){
		if (pair == node){
			return true;
		}
	}

	return false;
}

double KPDGUIStructure::getUtility() const{
	return myUtility;
}

int KPDGUIStructure::getID() const{
	return myID;
}

void KPDGUIStructure::increasePopularityInStructures(){
	foreach(KPDGUINode * node, myPairList){
		node->increasePopularityInStructures();
	}
	foreach(KPDGUIMatch * arrow, myArrows){
		arrow->increasePopularityInStructures();
	}
}

void KPDGUIStructure::increasePopularityInSolutions(){
	foreach(KPDGUINode * node, myPairList){
		node->increasePopularityInSolutions();
	}
	foreach(KPDGUIMatch * arrow, myArrows){
		arrow->increasePopularityInSolutions();
	}
}

void KPDGUIStructure::decreasePopularityInStructures(){
	foreach(KPDGUINode * node, myPairList){
		node->decreasePopularityInStructures();
	}
	foreach(KPDGUIMatch * arrow, myArrows){
		arrow->decreasePopularityInStructures();
	}
}

void KPDGUIStructure::decreasePopularityInSolutions(){
	foreach(KPDGUINode * node, myPairList){
		node->decreasePopularityInSolutions();
	}
	foreach(KPDGUIMatch * arrow, myArrows){
		arrow->decreasePopularityInSolutions();
	}
}

void KPDGUIStructure::resetPopularityInStructures(){
	foreach(KPDGUINode * node, myPairList){
		node->resetPopularityInStructures();
	}
	foreach(KPDGUIMatch * arrow, myArrows){
		arrow->resetPopularityInStructures();
	}
}

void KPDGUIStructure::resetPopularityInSolutions(){
	foreach(KPDGUINode * node, myPairList){
		node->resetPopularityInSolutions();
	}
	foreach(KPDGUIMatch * arrow, myArrows){
		arrow->resetPopularityInSolutions();
	}
}

QString KPDGUIStructure::toString(){
	QString structureString = "";

	if (myOptScheme == KPDOptimizationScheme::SCC){
		structureString += "Component #" + QString::number(myID) + " (";
	}
	else {
		if (chain){
			structureString += "Chain #" + QString::number(myID) + " (";
		}
		else{
			structureString += "Cycle #" + QString::number(myID) + " (";
		}
	}

	foreach(KPDGUINode * node, myPairList){
		structureString += QString::number(node->getNodeID());
		structureString += ", ";
	}

	structureString.chop(2);
	structureString += "): ";

	if (myOptScheme == KPDOptimizationScheme::MUC || myOptScheme == KPDOptimizationScheme::MEUC){
		QString nodeString = "";
		for (int j = 0; j < myPairList.size() - 1; j++){
			KPDGUINode * firstPair = myPairList.at(j);
			KPDGUINode * secondPair = myPairList.at(j + 1);
			nodeString = nodeString + QString::number(firstPair->getNodeID()) + "->" + QString::number(secondPair->getNodeID()) + ", ";
		}
		if (!chain){
			nodeString = nodeString + QString::number(myPairList.last()->getNodeID()) + "->" + QString::number(myPairList.first()->getNodeID()) + ", ";
		}
		nodeString.chop(2);
		structureString += nodeString;
	}
	else {
		foreach(KPDGUIMatch * arrow, myArrows){
			QString arrowString = QString::number(arrow->getFromNode()->getNodeID()) + "->" + QString::number(arrow->getToNode()->getNodeID());
			structureString += arrowString;
			structureString += ", ";
		}
		structureString.chop(2);
	}

	structureString += " (" + QString::number(myUtility) + ")";

	return structureString;
}


QList<QTreeWidgetItem *> KPDGUIStructure::getItemList(){
	QList<QTreeWidgetItem *> newList;
	foreach(KPDGUINode * node, myPairList){
		KPDGUINodeWrapper * wrapper = new KPDGUINodeWrapper(node);
		newList.push_back(wrapper);
	}

	return newList;
}