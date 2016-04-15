#include "KPDGUIStructureSet.h"

KPDGUIStructureSet::KPDGUIStructureSet(){
	
	myParameters = new KPDGUISimParameters();

	myTimeStamp = "";
	myRecordLog = "";
	mySimLog = "";
	
	solutionSet = true;
	mySolutionNumber = -1;
	
}

KPDGUIStructureSet::KPDGUIStructureSet(KPDGUISimParameters * parameters, QString timestamp, QString recordLog, QString simLog, bool solution, int solutionNumber){
	
	construct(parameters, timestamp, recordLog, simLog, true, solutionNumber);
	
}

KPDGUIStructureSet::~KPDGUIStructureSet(){
	if (solutionSet){
		foreach(KPDGUIStructure * structure, myStructureList){
			structure->decreasePopularityInSolutions();
		}
	}
}

void KPDGUIStructureSet::construct(KPDGUISimParameters * params, QString timestamp, QString recordLog, QString simLog, bool solution, int solutionNumber){
	
	myParameters->copyParameters(params);

	myTimeStamp = timestamp;
	myRecordLog = recordLog;
	mySimLog = simLog;

	solutionSet = solution;
	mySolutionNumber = solutionNumber;

	KPDOptimizationScheme myOptScheme = myParameters->getOptimizationScheme();

	QString textOptScheme = KPDFunctions::toString(myOptScheme);

	if (solutionSet){
		setText(0, textOptScheme + "[" + QString::number(mySolutionNumber) + "] (" + myTimeStamp + ")");
	}
	else{
		setText(0, textOptScheme + " (" + myTimeStamp + ")");
	}

	setUpWidgets();

	/*if (myOptScheme != KPDOptimizationScheme::SCC){
		addChild(cycleSizeTwo);
		addChild(cycleSizeThree);

		addChild(chainSizeOne);
		addChild(chainSizeTwo);
		if (parameters->getMaxSize() >= 3){
			addChild(chainSizeThree);
		}
		if (parameters->getMaxSize() >= 4){
			addChild(chainSizeFour);
		}
		if (parameters->getMaxSize() >= 5){
			addChild(chainSizeFive);
		}
		if (parameters->getMaxSize() >= 6){
			addChild(chainSizeSix);
		}
	}

	else {
		addChild(componentSizeTwo);

		if (parameters->getMaxSize() >= 3){
			addChild(componentSizeThree);
		}
		if (parameters->getMaxSize() >= 4){
			addChild(componentSizeFour);
		}
		if (parameters->getMaxSize() >= 5){
			addChild(componentSizeFive);
		}
		if (parameters->getMaxSize() == 6){
			addChild(componentSizeSix);
		}
	}*/
	
}

void KPDGUIStructureSet::addStructure(KPDGUIStructure * structure){
	myStructureList.push_back(structure);
	KPDGUIStructureWrapper * wrapper = new KPDGUIStructureWrapper(structure);
	
	KPDOptimizationScheme myOptScheme = myParameters->getOptimizationScheme();

	int structureSize = structure->size();

	if (myOptScheme != KPDOptimizationScheme::SCC){
		
		if (structure->isChain()) {
			myChains[structureSize-1]->addChild(wrapper);
		}
		else {
			myCycles[structureSize]->addChild(wrapper);
		}
	}

	else {
		myComponents[structureSize]->addChild(wrapper);
	}

	updateText();
}

void KPDGUIStructureSet::removeStructure(KPDGUIStructure * structure){
	myStructureList.remove(myStructureList.indexOf(structure));
}

QList<KPDGUIStructure*> KPDGUIStructureSet::getStructures(){
	QList<KPDGUIStructure *> structureListCopy;

	foreach(KPDGUIStructure * structure, myStructureList){
		structureListCopy.push_back(structure);
	}

	return structureListCopy;
}

void KPDGUIStructureSet::selectStructures(){
	foreach(KPDGUIStructure * structure, myStructureList){
		structure->select();
	}
}

void KPDGUIStructureSet::highlight(){
	foreach(KPDGUIStructure * structure, myStructureList){
		structure->highlight();
	}
}

void KPDGUIStructureSet::undoHighlights(){
	foreach(KPDGUIStructure * structure, myStructureList){
		structure->undoHighlights();
	}
}

qreal KPDGUIStructureSet::centerX(){

	qreal avgx = 0;

	foreach(KPDGUIStructure * structure, myStructureList){
		avgx += structure->centerX();
	}
	avgx = avgx / myStructureList.size();

	return avgx;
}

qreal KPDGUIStructureSet::centerY(){
	
	qreal avgy = 0;

	foreach(KPDGUIStructure * structure, myStructureList){
		avgy += structure->centerY();
	}
	avgy = avgy / myStructureList.size();

	return avgy;
}

void KPDGUIStructureSet::cluster(){
	qreal dist = 100 + 10 * myStructureList.size();
	
	qreal centerX = this->centerX();
	qreal centerY = this->centerY();

	qreal angle = (2 * PI) / myStructureList.size();
	qreal nodeAngle = PI;
	
	foreach(KPDGUIStructure * structure, myStructureList){
		structure->cluster(centerX + dist*cos(nodeAngle), centerY + dist*sin(nodeAngle));
		nodeAngle += angle;
	}	
}

void KPDGUIStructureSet::deleteNode(KPDGUINode * nodeToDelete){ }

int KPDGUIStructureSet::size(){
	return myStructureList.size();
}

int KPDGUIStructureSet::numberOfElements(){
	int numberOfElements = 0;
	foreach(KPDGUIStructure * structure, myStructureList){
		numberOfElements += structure->size();
	}

	return numberOfElements;
}

double KPDGUIStructureSet::utility(){
	double utility = 0;
	foreach(KPDGUIStructure * structure, myStructureList){
		utility += structure->getUtility();
	}
	return utility;
}

bool KPDGUIStructureSet::isSolutionSet(){
	return solutionSet;
}

void KPDGUIStructureSet::updatePopularity(){
	if (solutionSet){
		foreach(KPDGUIStructure * structure, myStructureList){
			structure->increasePopularityInSolutions();
		}
	}
	else {
		foreach(KPDGUIStructure * structure, myStructureList){
			structure->increasePopularityInStructures();
		}
	}
}

void KPDGUIStructureSet::resetPopularity(){
	if (solutionSet){
		foreach(KPDGUIStructure * structure, myStructureList){
			structure->resetPopularityInSolutions();
		}
	}
	else {
		foreach(KPDGUIStructure * structure, myStructureList){
			structure->resetPopularityInStructures();
		}
	}
}

QString KPDGUIStructureSet::getConsoleString(){

	QString receipt = "";

	if (solutionSet){
		receipt = receipt + "Solution For Match Run Performed On " + myTimeStamp + "\n\n";
	}
	else {
		receipt = receipt + "Cycle List For Match Run performed On " + myTimeStamp + "\n\n";
	}

	receipt = receipt + myRecordLog + "\n";

	if (solutionSet){
		receipt = receipt + "Solution " + QString::number(mySolutionNumber) + " / Objective: " + QString::number(utility()) + "\n\n";
	}
	else {
		if (myParameters->getOptimizationScheme() != KPDOptimizationScheme::SCC){
			receipt = receipt + "List of Cycles:\n";
		}
		else{
			receipt = receipt + "List of Components:\n";
		}
	}

	int chains = 0;
	int cycles = 0;

	foreach(KPDGUIStructure * structure, myStructureList){
		receipt = receipt + structure->toString() + "\n";
		if (structure->isChain()){
			chains++;
		}
		else {
			cycles++;
		}
	}
	receipt = receipt + "\n";
	if (solutionSet){
		receipt = receipt + mySimLog + "\n";
	}

	if (myParameters->getOptimizationScheme() != KPDOptimizationScheme::SCC){
		receipt = receipt + "Cycles: " + QString::number(cycles) + ", Chains: " + QString::number(chains) + "\n";
	}
	else{
		receipt = receipt + "Components: " + QString::number(size()) + "\n";
	}

	receipt = receipt + myParameters->toString();

	return receipt;
}

void KPDGUIStructureSet::setUpWidgets(){
	/*
	cycleSizeTwo = new QTreeWidgetItem();
	cycleSizeThree = new QTreeWidgetItem();
	chainSizeOne = new QTreeWidgetItem();
	chainSizeTwo = new QTreeWidgetItem();
	chainSizeThree = new QTreeWidgetItem();
	chainSizeFour = new QTreeWidgetItem();
	chainSizeFive = new QTreeWidgetItem();
	chainSizeSix = new QTreeWidgetItem();
	componentSizeTwo = new QTreeWidgetItem();
	componentSizeThree = new QTreeWidgetItem();
	componentSizeFour = new QTreeWidgetItem();
	componentSizeFive = new QTreeWidgetItem();
	componentSizeSix = new QTreeWidgetItem();
	*/
	updateText();
}

void KPDGUIStructureSet::updateText(){

	foreach(int size, myCycles.keys()) {
		myCycles[size]->setText(0, QString::number(size) + "-Way Exchange (" + QString::number(myCycles[size]->childCount()) + ")");
	}

	foreach(int size, myChains.keys()) {
		myChains[size]->setText(0, "Chains of Length " + QString::number(size) + " (" + QString::number(myChains[size]->childCount()) + ")");
	}

	foreach(int size, myComponents.keys()) {
		myComponents[size]->setText(0, "Components of Size " + QString::number(size) + " (" + QString::number(myComponents[size]->childCount()) + ")");
	}

	/*cycleSizeTwo->setText(0, "Two-Way Exchange (" + QString::number(cycleSizeTwo->childCount()) + ")");
	cycleSizeThree->setText(0, "Three-Way Exchange (" + QString::number(cycleSizeThree->childCount()) + ")");
	chainSizeOne->setText(0, "Chains of Length 1 (" + QString::number(chainSizeOne->childCount()) + ")");
	chainSizeTwo->setText(0, "Chains of Length 2 (" + QString::number(chainSizeTwo->childCount()) + ")");
	chainSizeThree->setText(0, "Chains of Length 3 (" + QString::number(chainSizeThree->childCount()) + ")");
	chainSizeFour->setText(0, "Chains of Length 4 (" + QString::number(chainSizeFour->childCount()) + ")");
	chainSizeFive->setText(0, "Chains of Length 5 (" + QString::number(chainSizeFive->childCount()) + ")");
	chainSizeSix->setText(0, "Chains of Length 6+ (" + QString::number(chainSizeSix->childCount()) + ")");
	componentSizeTwo->setText(0, "Components of Size 2 (" + QString::number(componentSizeTwo->childCount()) + ")");
	componentSizeThree->setText(0, "Components of Size 3 (" + QString::number(componentSizeThree->childCount()) + ")");
	componentSizeFour->setText(0, "Components of Size 4 (" + QString::number(componentSizeFour->childCount()) + ")");
	componentSizeFive->setText(0, "Components of Size 5 (" + QString::number(componentSizeFive->childCount()) + ")");
	componentSizeSix->setText(0, "Components of Size 6 (" + QString::number(componentSizeSix->childCount()) + ")"); */

}

void KPDGUIStructureSet::sort(){
	
	for (int i = 0; i < childCount(); i++){
		
		QTreeWidgetItem * item = child(i);

		QList<KPDGUIStructureWrapper*> newStructureList;
		int itemCount = item->childCount();

		for (int i = 0; i < itemCount; i++){
			QTreeWidgetItem * structure = item->child(0);
			KPDGUIStructureWrapper * temp = dynamic_cast<KPDGUIStructureWrapper *>(structure);
			if (temp){
				newStructureList.push_back(temp);
				item->removeChild(structure);
			}
		}
		//qSort(newStructureList.begin(), newStructureList.end(), KPDGUIStructureGreaterThan(0));
		

		foreach(KPDGUIStructureWrapper * structure, newStructureList){
			item->addChild(structure);
		}
	}
}

QDataStream &operator<<(QDataStream &out, const KPDGUIStructureSet & structureSet)
{
	out << *structureSet.getParameters();
	out << structureSet.getTimeStamp();
	out << structureSet.getRecordLog();
	out << structureSet.getSimLog();
	out << qint32(structureSet.getSolutionNumber());

	return out;
}

//void KPDGUINode::extractFromDataStream(QDataStream& dataStream)
QDataStream &operator>>(QDataStream &in, KPDGUIStructureSet & structureSet)
{
	
	KPDGUISimParameters * paramInfo = new KPDGUISimParameters();
	QString timeStamp;
	QString recordLog;
	QString simLog;
	qint32 solutionNumber;

	in >> *paramInfo >> timeStamp >> recordLog >> simLog >> solutionNumber;
	
	structureSet.construct(paramInfo, timeStamp, recordLog, simLog, true, solutionNumber);
	
	return in;
}