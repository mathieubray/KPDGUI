#include "KPDGUIStructure.h"

const qreal Pi = 3.14159265;
const qreal Tol = 3;

KPDGUIStructure::KPDGUIStructure(QVector<KPDGUINode *> pairList, QString optScheme, double utility, int id){
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

			if (myPairList.first()->getType() != 0){
				chain = true;
			}
		}
	}

	//Find corresponding arrows
	if (optScheme == "MUC" || optScheme == "MEUC"){
		for (int j = 0; j < myPairList.size() - 1; j++){
			KPDGUINode * firstPair = myPairList.at(j);
			KPDGUINode * secondPair = myPairList.at(j + 1);
			KPDGUIArrow * arrow = firstPair->findOutArrow(secondPair);
			myArrows.insert(arrow);
		}

		if (!chain){
			KPDGUIArrow * arrow = myPairList.last()->findOutArrow(myPairList.first());
			if (arrow != NULL){
				myArrows.insert(arrow);
			}			
		}
	}
	
	else {
		for (int j = 0; j < myPairList.size(); j++){
			for (int k = 0; k < myPairList.size(); k++){
				if (j != k){
					KPDGUIArrow * arrow = myPairList.at(j)->findOutArrow(myPairList.at(k));
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
	foreach(KPDGUIArrow * arrow, myArrows){
		arrow->highlightCycle();
	}
}

void KPDGUIStructure::undoHighlights(){
	foreach(KPDGUIArrow * arrow, myArrows){
		arrow->endDisplayAsPartOfSolution();
	}
}

qreal KPDGUIStructure::centerX(){
	qreal avgx = 0;

	foreach(KPDGUINode * node, myPairList){
		////qDebug() << "x: " << node->x();
		avgx += node->x();		
	}

	avgx = avgx / myPairList.size();

	////qDebug() << "AVG X: " << avgx;
	return avgx;
}

qreal KPDGUIStructure::centerY(){
	qreal avgy = 0;

	foreach(KPDGUINode * node, myPairList){
		////qDebug() << "y: " << node->y();
		avgy += node->y();
	}

	avgy = avgy / myPairList.size();

	////qDebug() << "AVG Y: " << avgy;
	return avgy;
}

void KPDGUIStructure::cluster(){
	qreal dist = 50 + 10*myPairList.size();

	qreal angle = (2 * Pi) / myPairList.size();
	qreal nodeAngle = Pi;

	qreal centerX = this->centerX();
	qreal centerY = this->centerY();

	foreach(KPDGUINode * node, myPairList){
		node->setVisible(false);
		////qDebug() << "Center X:" << centerX << ", Center Y:" << centerY;
		////qDebug() << "Angle X:" << cos(nodeAngle) << ", Angle Y:" << sin(nodeAngle);
		////qDebug() << "Scale X:" << dist*cos(nodeAngle) << ", Scale Y:" << dist*sin(nodeAngle);
		////qDebug() << "(" << centerX + dist*cos(nodeAngle) << "," << centerY + dist*sin(nodeAngle) << ")";
		if (!(abs((node->x()) - (centerX + dist*cos(nodeAngle))) < Tol && abs((node->y()) - (centerY + dist*sin(nodeAngle)) < Tol))){
			node->setPos(QPoint(centerX + dist*cos(nodeAngle), centerY + dist*sin(nodeAngle)));
		}		
		nodeAngle += angle;
		node->setVisible(true);
	}
}

void KPDGUIStructure::cluster(qreal x, qreal y){

	qreal dist = 50 + 10 * myPairList.size();

	qreal angle = (2 * Pi) / myPairList.size();
	qreal nodeAngle = Pi;

	foreach(KPDGUINode * node, myPairList){
		node->setVisible(false);
		////qDebug() << "(" << x + dist*cos(nodeAngle) << "," << y + dist*sin(nodeAngle) << ")";
		if (!(abs((node->x()) - (x + dist*cos(nodeAngle))) < Tol && abs((node->y()) - (y + dist*sin(nodeAngle)) < Tol))){
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
		structureString += QString::number(node->getInternalID());
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
	foreach(KPDGUIArrow * arrow, myArrows){
		arrow->increasePopularityInStructures();
	}
}

void KPDGUIStructure::increasePopularityInSolutions(){
	foreach(KPDGUINode * node, myPairList){
		node->increasePopularityInSolutions();
	}
	foreach(KPDGUIArrow * arrow, myArrows){
		arrow->increasePopularityInSolutions();
	}
}

void KPDGUIStructure::decreasePopularityInStructures(){
	foreach(KPDGUINode * node, myPairList){
		node->decreasePopularityInStructures();
	}
	foreach(KPDGUIArrow * arrow, myArrows){
		arrow->decreasePopularityInStructures();
	}
}

void KPDGUIStructure::decreasePopularityInSolutions(){
	foreach(KPDGUINode * node, myPairList){
		node->decreasePopularityInSolutions();
	}
	foreach(KPDGUIArrow * arrow, myArrows){
		arrow->decreasePopularityInSolutions();
	}
}

void KPDGUIStructure::resetPopularityInStructures(){
	foreach(KPDGUINode * node, myPairList){
		node->resetPopularityInStructures();
	}
	foreach(KPDGUIArrow * arrow, myArrows){
		arrow->resetPopularityInStructures();
	}
}

void KPDGUIStructure::resetPopularityInSolutions(){
	foreach(KPDGUINode * node, myPairList){
		node->resetPopularityInSolutions();
	}
	foreach(KPDGUIArrow * arrow, myArrows){
		arrow->resetPopularityInSolutions();
	}
}

QString KPDGUIStructure::toString(){
	QString structureString = "";

	if (myOptScheme == "SCC"){
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
		structureString += QString::number(node->getInternalID());
		structureString += ", ";
	}

	structureString.chop(2);
	structureString += "): ";

	if (myOptScheme == "MUC" || myOptScheme == "MEUC"){
		QString nodeString = "";
		for (int j = 0; j < myPairList.size() - 1; j++){
			KPDGUINode * firstPair = myPairList.at(j);
			KPDGUINode * secondPair = myPairList.at(j + 1);
			nodeString = nodeString + QString::number(firstPair->getInternalID()) + "->" + QString::number(secondPair->getInternalID()) + ", ";
		}
		if (!chain){
			nodeString = nodeString + QString::number(myPairList.last()->getInternalID()) + "->" + QString::number(myPairList.first()->getInternalID()) + ", ";
		}
		nodeString.chop(2);
		structureString += nodeString;
	}
	else {
		foreach(KPDGUIArrow * arrow, myArrows){
			QString arrowString = QString::number(arrow->startItem()->getInternalID()) + "->" + QString::number(arrow->endItem()->getInternalID());
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