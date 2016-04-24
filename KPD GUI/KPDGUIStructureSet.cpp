#include "KPDGUIStructureSet.h"

KPDGUIStructureSet::KPDGUIStructureSet(){
	
	structureSetParameters = new KPDGUISimParameters();

	structureSetTimeStamp = "";
	structureSetRecordLog = "";
	structureSetSimLog = "";
	
	isSolutionSet = true;
	solutionNumber = -1;
	
}

KPDGUIStructureSet::KPDGUIStructureSet(KPDGUISimParameters * parameters, QString timestamp, QString recordLog, QString simLog, bool solution, int solutionNumber){
	
	construct(parameters, timestamp, recordLog, simLog, true, solutionNumber);
	
}

KPDGUIStructureSet::~KPDGUIStructureSet(){
	if (isSolutionSet){
		foreach(KPDGUIStructure * structure, structureSetList){
			structure->decreasePopularity(true);
		}
	}
}

void KPDGUIStructureSet::construct(KPDGUISimParameters * params, QString timestamp, QString recordLog, QString simLog, bool solution, int solutionNumber){
	
	structureSetParameters->copyParameters(params);

	structureSetTimeStamp = timestamp;
	structureSetRecordLog = recordLog;
	structureSetSimLog = simLog;

	isSolutionSet = solution;
	solutionNumber = solutionNumber;

	KPDOptimizationScheme myOptScheme = structureSetParameters->getOptimizationScheme();

	QString textOptScheme = KPDFunctions::toString(myOptScheme);

	if (isSolutionSet){
		setText(0, textOptScheme + "[" + QString::number(solutionNumber) + "] (" + structureSetTimeStamp + ")");
	}
	else{
		setText(0, textOptScheme + " (" + structureSetTimeStamp + ")");
	}

	setUpWidgets();	
}

void KPDGUIStructureSet::addStructure(KPDGUIStructure * structure){
	structureSetList.push_back(structure);
	KPDGUIStructureWrapper * wrapper = new KPDGUIStructureWrapper(structure);
	
	int structureSize = structure->size();

	if (structureSetParameters->getOptimizationScheme() != KPDOptimizationScheme::SCC){
		
		if (structure->hasAnAD()) {
			structureSetChains[structureSize-1]->addChild(wrapper);
		}
		else {
			structureSetCycles[structureSize]->addChild(wrapper);
		}
	}

	else {
		structureSetComponents[structureSize]->addChild(wrapper);
	}

	updateText();
}

void KPDGUIStructureSet::removeStructure(KPDGUIStructure * structure){
	structureSetList.remove(structureSetList.indexOf(structure));
}

QList<KPDGUIStructure*> KPDGUIStructureSet::getStructures(){
	QList<KPDGUIStructure *> structureListCopy;

	foreach(KPDGUIStructure * structure, structureSetList){
		structureListCopy.push_back(structure);
	}

	return structureListCopy;
}

void KPDGUIStructureSet::selectStructures(){
	foreach(KPDGUIStructure * structure, structureSetList){
		structure->select();
	}
}

void KPDGUIStructureSet::highlight(){
	foreach(KPDGUIStructure * structure, structureSetList){
		structure->highlight();
	}
}

void KPDGUIStructureSet::undoHighlights(){
	foreach(KPDGUIStructure * structure, structureSetList){
		structure->undoHighlights();
	}
}

qreal KPDGUIStructureSet::centerX(){

	qreal avgx = 0;

	foreach(KPDGUIStructure * structure, structureSetList){
		avgx += structure->centerX();
	}
	avgx = avgx / structureSetList.size();

	return avgx;
}

qreal KPDGUIStructureSet::centerY(){
	
	qreal avgy = 0;

	foreach(KPDGUIStructure * structure, structureSetList){
		avgy += structure->centerY();
	}
	avgy = avgy / structureSetList.size();

	return avgy;
}

void KPDGUIStructureSet::cluster(){
	qreal dist = 100 + 10 * structureSetList.size();
	
	qreal centerX = this->centerX();
	qreal centerY = this->centerY();

	qreal angle = (2 * PI) / structureSetList.size();
	qreal nodeAngle = PI;
	
	foreach(KPDGUIStructure * structure, structureSetList){
		structure->cluster(centerX + dist*cos(nodeAngle), centerY + dist*sin(nodeAngle));
		nodeAngle += angle;
	}	
}

void KPDGUIStructureSet::deleteNode(KPDGUINode * nodeToDelete){ 

}

int KPDGUIStructureSet::size(){
	return structureSetList.size();
}

int KPDGUIStructureSet::getNumberOfNodes(){
	int numberOfNodes = 0;
	foreach(KPDGUIStructure * structure, structureSetList){
		numberOfNodes += structure->size();
	}

	return numberOfNodes;
}

double KPDGUIStructureSet::utility(){
	double utility = 0;
	foreach(KPDGUIStructure * structure, structureSetList){
		utility += structure->getUtility();
	}
	return utility;
}

bool KPDGUIStructureSet::structureSetisSolutionSet() {
	return isSolutionSet;
}

void KPDGUIStructureSet::updatePopularity(){
	foreach(KPDGUIStructure * structure, structureSetList){
		structure->increasePopularity(isSolutionSet);
	}
	
}

void KPDGUIStructureSet::resetPopularity(){
	foreach(KPDGUIStructure * structure, structureSetList){
		structure->resetPopularity(isSolutionSet);
	}	
}

QString KPDGUIStructureSet::getDashboardString(){

	QString receipt = "";

	if (isSolutionSet){
		receipt = receipt + "Solution For Match Run Performed On " + structureSetTimeStamp + "\n\n";
	}
	else {
		receipt = receipt + "Cycle List For Match Run performed On " + structureSetTimeStamp + "\n\n";
	}

	receipt = receipt + structureSetRecordLog + "\n";

	if (isSolutionSet){
		receipt = receipt + "Solution " + QString::number(solutionNumber) + " / Objective: " + QString::number(utility()) + "\n\n";
	}
	else {
		if (structureSetParameters->getOptimizationScheme() != KPDOptimizationScheme::SCC){
			receipt = receipt + "List of Cycles:\n";
		}
		else{
			receipt = receipt + "List of Components:\n";
		}
	}

	int chains = 0;
	int cycles = 0;

	foreach(KPDGUIStructure * structure, structureSetList){
		receipt = receipt + structure->structureString() + "\n";
		if (structure->hasAnAD()){
			chains++;
		}
		else {
			cycles++;
		}
	}
	receipt = receipt + "\n";
	if (isSolutionSet){
		receipt = receipt + structureSetSimLog + "\n";
	}

	if (structureSetParameters->getOptimizationScheme() != KPDOptimizationScheme::SCC){
		receipt = receipt + "Cycles: " + QString::number(cycles) + ", Chains: " + QString::number(chains) + "\n";
	}
	else{
		receipt = receipt + "Components: " + QString::number(size()) + "\n";
	}

	receipt = receipt + structureSetParameters->toString();

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

	foreach(int size, structureSetCycles.keys()) {
		structureSetCycles[size]->setText(0, QString::number(size) + "-Way Exchange (" + QString::number(structureSetCycles[size]->childCount()) + ")");
	}

	foreach(int size, structureSetChains.keys()) {
		structureSetChains[size]->setText(0, "Chains of Length " + QString::number(size) + " (" + QString::number(structureSetChains[size]->childCount()) + ")");
	}

	foreach(int size, structureSetComponents.keys()) {
		structureSetComponents[size]->setText(0, "Components of Size " + QString::number(size) + " (" + QString::number(structureSetComponents[size]->childCount()) + ")");
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