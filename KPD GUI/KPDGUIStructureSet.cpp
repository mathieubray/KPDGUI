#include "KPDGUIStructureSet.h"

const qreal Pi = 3.14159265;

KPDGUIStructureSet::KPDGUIStructureSet(){
	myParameters.optScheme = KPDOptimizationScheme::MUC;
	myParameters.utilityScheme = KPDUtilityScheme::TRANSPLANTS;
	myParameters.maxChainLength = 2;
	
	myParameters.pairFailureRate = 0;
	myParameters.adFailureRate = 0;
	myParameters.exogenousFailureRate = 0;

	myParameters.addAdvantageToHighPRACandidates = false;
	myParameters.praAdvantageCutoff = 100;
	myParameters.praAdvantageValue = 0;

	myParameters.numberOfSolutions = 1;
	
	myParameters.chainStorage = "NONE";
	myParameters.reserveODonorsForOCandidates = false;
	myParameters.checkDP = false;
	myParameters.includeCompatiblePairs = false;
	myParameters.excludeABDonorsFromSimulation = false;
	myParameters.allowABBridgeDonors = false;

	myTimeStamp = "";
	mySimLog = "";
	
	solutionSet = true;
	mySolutionNumber = -1;
	
}

KPDGUIStructureSet::KPDGUIStructureSet(ParamInfoStruct parameters, QString timestamp, QString simLog, bool solution, int solutionNumber){
	/*myParameters.optScheme = parameters.optScheme;
	myParameters.utilityScheme = parameters.utilityScheme;
	myParameters.maxChainLength = parameters.maxChainLength;

	myParameters.pairFailureRate = parameters.pairFailureRate;
	myParameters.adFailureRate = parameters.adFailureRate;
	myParameters.exogenousFailureRate = parameters.exogenousFailureRate;

	myParameters.addAdvantageToHighPRACandidates = parameters.addAdvantageToHighPRACandidates;
	myParameters.praAdvantageCutoff = parameters.praAdvantageCutoff;
	myParameters.praAdvantageValue = parameters.praAdvantageValue;

	myParameters.numberOfSolutions = parameters.numberOfSolutions;

	myParameters.chainStorage = parameters.chainStorage;
	myParameters.reserveODonorsForOCandidates = parameters.reserveODonorsForOCandidates;
	myParameters.checkDP = parameters.checkDP;
	myParameters.includeCompatiblePairs = parameters.includeCompatiblePairs;
	myParameters.excludeABDonorsFromSimulation = parameters.excludeABDonorsFromSimulation;
	myParameters.allowABBridgeDonors = parameters.allowABBridgeDonors;

	myTimeStamp = timestamp;
	mySimLog = simLog;

	solutionSet = solution;
	mySolutionNumber = solutionNumber;

	KPDOptimizationScheme myOptScheme = myParameters.optScheme;

	QString textOptScheme = KPDFunctions::toString(myOptScheme);

	if (solutionSet){
		setText(0, textOptScheme + "[" + QString::number(mySolutionNumber) + "] (" + myTimeStamp + ")");
	}
	else{
		setText(0, textOptScheme + " (" + myTimeStamp + ")");
	}
	
	setUpWidgets();

	if (myOptScheme != KPDOptimizationScheme::SCC){
		addChild(cycleSizeTwo);
		addChild(cycleSizeThree);

		addChild(chainSizeOne);
		addChild(chainSizeTwo);
		if (parameters.maxChainLength >= 3){
			addChild(chainSizeThree);
		}
		if (parameters.maxChainLength >= 4){
			addChild(chainSizeFour);
		}
		if (parameters.maxChainLength >= 5){
			addChild(chainSizeFive);
		}
		if (parameters.maxChainLength >= 6){
			addChild(chainSizeSix);
		}
	}

	else {
		addChild(componentSizeTwo);
		addChild(componentSizeThree);
		if (parameters.maxChainLength >= 3){
			addChild(componentSizeFour);
		}
	}*/

	construct(parameters, timestamp, simLog, solution, solutionNumber);
}

KPDGUIStructureSet::~KPDGUIStructureSet(){
	if (solutionSet){
		foreach(KPDGUIStructure * structure, myStructureList){
			structure->decreasePopularityInSolutions();
		}
	}
}

void KPDGUIStructureSet::construct(ParamInfoStruct parameters, QString timestamp, QString simLog, bool solution, int solutionNumber){
	
	myParameters.optScheme = parameters.optScheme;
	myParameters.utilityScheme = parameters.utilityScheme;
	myParameters.maxChainLength = parameters.maxChainLength;

	myParameters.pairFailureRate = parameters.pairFailureRate;
	myParameters.adFailureRate = parameters.adFailureRate;
	myParameters.exogenousFailureRate = parameters.exogenousFailureRate;

	myParameters.addAdvantageToHighPRACandidates = parameters.addAdvantageToHighPRACandidates;
	myParameters.praAdvantageCutoff = parameters.praAdvantageCutoff;
	myParameters.praAdvantageValue = parameters.praAdvantageValue;

	myParameters.numberOfSolutions = parameters.numberOfSolutions;

	myParameters.chainStorage = parameters.chainStorage;
	myParameters.reserveODonorsForOCandidates = parameters.reserveODonorsForOCandidates;
	myParameters.checkDP = parameters.checkDP;
	myParameters.includeCompatiblePairs = parameters.includeCompatiblePairs;
	myParameters.excludeABDonorsFromSimulation = parameters.excludeABDonorsFromSimulation;
	myParameters.allowABBridgeDonors = parameters.allowABBridgeDonors;

	myTimeStamp = timestamp;
	mySimLog = simLog;	

	solutionSet = solution;
	mySolutionNumber = solutionNumber;

	KPDOptimizationScheme myOptScheme = myParameters.optScheme;

	QString textOptScheme = KPDFunctions::toString(myOptScheme);

	if (solutionSet){
		setText(0, textOptScheme + "[" + QString::number(mySolutionNumber) + "] (" + myTimeStamp + ")");
	}
	else{
		setText(0, textOptScheme + " (" + myTimeStamp + ")");
	}

	setUpWidgets();

	if (myOptScheme != KPDOptimizationScheme::SCC){
		addChild(cycleSizeTwo);
		addChild(cycleSizeThree);

		addChild(chainSizeOne);
		addChild(chainSizeTwo);
		if (parameters.maxChainLength >= 3){
			addChild(chainSizeThree);
		}
		if (parameters.maxChainLength >= 4){
			addChild(chainSizeFour);
		}
		if (parameters.maxChainLength >= 5){
			addChild(chainSizeFive);
		}
		if (parameters.maxChainLength >= 6){
			addChild(chainSizeSix);
		}
	}

	else {
		addChild(componentSizeTwo);
		addChild(componentSizeThree);
		if (parameters.maxChainLength >= 3){
			addChild(componentSizeFour);
		}
	}
}

void KPDGUIStructureSet::push_back(KPDGUIStructure * structure){
	myStructureList.push_back(structure);
	KPDGUIStructureWrapper * wrapper = new KPDGUIStructureWrapper(structure);
	
	KPDOptimizationScheme myOptScheme = myParameters.optScheme;

	if (myOptScheme != KPDOptimizationScheme::SCC){
		if (structure->size() == 2){
			if (structure->isChain()){
				chainSizeOne->addChild(wrapper);
			}
			else {
				cycleSizeTwo->addChild(wrapper);
			}
		}
		else if (structure->size() == 3){
			if (structure->isChain()) {
				chainSizeTwo->addChild(wrapper);
			}
			else {
				cycleSizeThree->addChild(wrapper);
			}
		}
		else if (structure->size() == 4){
			chainSizeThree->addChild(wrapper);
		}
		else if (structure->size() == 5){
			chainSizeFour->addChild(wrapper);
		}
		else if (structure->size() == 6){
			chainSizeFive->addChild(wrapper);
		}
		else if (structure->size() >= 7){
			chainSizeSix->addChild(wrapper);
		}
	}
	else {
		if (structure->size() == 2){
			componentSizeTwo->addChild(wrapper);
		}
		else if (structure->size() == 3){
			componentSizeThree->addChild(wrapper);
		}
		else if (structure->size() >= 4){
			componentSizeFour->addChild(wrapper);
		}
	}
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

	qreal angle = (2 * Pi) / myStructureList.size();
	qreal nodeAngle = Pi;
	
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

	if (solutionSet){
		receipt = receipt + "Solution " + QString::number(mySolutionNumber) + " / Objective: " + QString::number(utility()) + "\n\n";
	}
	else {
		if (myParameters.optScheme != KPDOptimizationScheme::SCC){
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

	if (myParameters.optScheme != KPDOptimizationScheme::SCC){
		receipt = receipt + "Cycles: " + QString::number(cycles) + ", Chains: " + QString::number(chains) + "\n";
	}
	else{
		receipt = receipt + "Components: " + QString::number(size()) + "\n";
	}
	receipt = receipt + "Optimization Scheme: " + KPDFunctions::toString(myParameters.optScheme) + "\n";
	receipt = receipt + "Utility Scheme: " + KPDFunctions::toString(myParameters.utilityScheme) + "\n";
	receipt = receipt + "Maximum Chain Length: " + QString::number(myParameters.maxChainLength) + "\n\n";

	receipt = receipt + "Pair Failure Rate: " + QString::number(myParameters.pairFailureRate) + "\n";
	receipt = receipt + "AD Failure Rate: " + QString::number(myParameters.adFailureRate) + "\n";
	receipt = receipt + "Exogenous Failure Rate: " + QString::number(myParameters.exogenousFailureRate) + "\n";
	
	if (myParameters.addAdvantageToHighPRACandidates){
		receipt = receipt + "Add " + QString::number(myParameters.praAdvantageValue) + " to Candidates with PRA Over " + QString::number(myParameters.praAdvantageCutoff) + "\n";
	}
	else {
		receipt = receipt + "Do Not Add Additional Advantage to High PRA Candidates\n";
	}
	receipt = receipt + "\n";	

	receipt = receipt + "Number of Solutions Produced: " + QString::number(myParameters.numberOfSolutions) + "\n\n";

	if (myParameters.chainStorage == "FIRST"){
		receipt = receipt + "Chains Are Stored First During Optimization";
	}
	else if (myParameters.chainStorage == "LAST"){
		receipt = receipt + "Chains Are Stored Last During Optimization";
	}
	else {
		receipt = receipt + "Chains Are Stored As They Are Found During Optimization";
	}
	receipt = receipt + "\n";

	if (!myParameters.reserveODonorsForOCandidates){
		receipt = receipt + "Do Not ";
	}
	receipt = receipt + "Reserve O Donors for O Recipients\n";
	if (!myParameters.checkDP){
		receipt = receipt + "Do Not ";
	}
	receipt = receipt + "Check Additional DP Mismatches\n";
	if (!myParameters.includeCompatiblePairs){
		receipt = receipt + "Do Not ";
	}
	receipt = receipt + "Include Compatible Pairs\n";

	if (myParameters.excludeABDonorsFromSimulation){
		receipt = receipt + "AB Donors are Excluded From Simulation\n";
	}
	else {
		if (!myParameters.allowABBridgeDonors){
			receipt = receipt + "Do Not ";
		}
		receipt = receipt + "Allow AB Bridge Donors\n";
	}		

	return receipt;
}

void KPDGUIStructureSet::setUpWidgets(){
	cycleSizeTwo = new QTreeWidgetItem();
	cycleSizeTwo->setText(0, "Two-Way Exchange");

	cycleSizeThree = new QTreeWidgetItem();
	cycleSizeThree->setText(0, "Three-Way Exchange");

	chainSizeOne = new QTreeWidgetItem();
	chainSizeOne->setText(0, "Chains of Length 1");

	chainSizeTwo = new QTreeWidgetItem();
	chainSizeTwo->setText(0, "Chains of Length 2");

	chainSizeThree = new QTreeWidgetItem();
	chainSizeThree->setText(0, "Chains of Length 3");

	chainSizeFour = new QTreeWidgetItem();
	chainSizeFour->setText(0, "Chains of Length 4");

	chainSizeFive = new QTreeWidgetItem();
	chainSizeFive->setText(0, "Chains of Length 5");

	chainSizeSix = new QTreeWidgetItem();
	chainSizeSix->setText(0, "Chains of Length 6+");

	componentSizeTwo = new QTreeWidgetItem();
	componentSizeTwo->setText(0, "Component of Size 2");

	componentSizeThree = new QTreeWidgetItem();
	componentSizeThree->setText(0, "Component of Size 3");

	componentSizeFour = new QTreeWidgetItem();
	componentSizeFour->setText(0, "Component of Size 4");
}

QDataStream &operator<<(QDataStream &out, const KPDGUIStructureSet & structureSet)
{
	ParamInfoStruct paramInfo = structureSet.getParameters();
	
	//qDebug() << "--Saved Solution--";
	//qDebug() << KPDFunctions::toString(paramInfo.optScheme);
	//qDebug() << KPDFunctions::toString(paramInfo.utilityScheme);
	//qDebug() << qint32(paramInfo.maxChainLength);

	//qDebug() << qreal(paramInfo.pairFailureRate);
	//qDebug() << qreal(paramInfo.adFailureRate);
	//qDebug() << qreal(paramInfo.exogenousFailureRate);

	//qDebug() << paramInfo.addAdvantageToHighPRACandidates;
	//qDebug() << qint32(paramInfo.praAdvantageCutoff);
	//qDebug() << qreal(paramInfo.praAdvantageValue);

	//qDebug() << qint32(paramInfo.numberOfSolutions);

	//qDebug() << paramInfo.chainStorage;
	//qDebug() << paramInfo.reserveODonorsForOCandidates;
	//qDebug() << paramInfo.checkDP;
	//qDebug() << paramInfo.includeCompatiblePairs;
	//qDebug() << paramInfo.excludeABDonorsFromSimulation;
	//qDebug() << paramInfo.allowABBridgeDonors;

	//qDebug() << structureSet.getTimeStamp();
	//qDebug() << structureSet.getSimLog();
	//qDebug() << qint32(structureSet.getSolutionNumber());
	//qDebug() << "-------";

	out << KPDFunctions::toString(paramInfo.optScheme);
	out << KPDFunctions::toString(paramInfo.utilityScheme);
	out << qint32(paramInfo.maxChainLength);
	
	out << qreal(paramInfo.pairFailureRate);
	out << qreal(paramInfo.adFailureRate);
	out << qreal(paramInfo.exogenousFailureRate);

	out << paramInfo.addAdvantageToHighPRACandidates;
	out << qint32(paramInfo.praAdvantageCutoff);
	out << qreal(paramInfo.praAdvantageValue);

	out << qint32(paramInfo.numberOfSolutions);

	out << paramInfo.chainStorage;
	out << paramInfo.reserveODonorsForOCandidates;
	out << paramInfo.checkDP;
	out << paramInfo.includeCompatiblePairs;
	out << paramInfo.excludeABDonorsFromSimulation;
	out << paramInfo.allowABBridgeDonors;	
	
	out << structureSet.getTimeStamp();
	out << structureSet.getSimLog();
	out << qint32(structureSet.getSolutionNumber());

	return out;
}

//void KPDGUINode::extractFromDataStream(QDataStream& dataStream)
QDataStream &operator>>(QDataStream &in, KPDGUIStructureSet & structureSet)
{
	ParamInfoStruct paramInfo;
	
	QString opt;
	in >> opt;
	paramInfo.optScheme = KPDFunctions::dialogToOptScheme(opt);

	QString util;
	in >> util;
	paramInfo.utilityScheme = KPDFunctions::dialogToUtilityScheme(util);
	
	in >> paramInfo.maxChainLength;

	in >> paramInfo.pairFailureRate;
	in >> paramInfo.adFailureRate;
	in >> paramInfo.exogenousFailureRate;

	in >> paramInfo.numberOfSolutions;

	in >> paramInfo.addAdvantageToHighPRACandidates;
	in >> paramInfo.praAdvantageCutoff;
	in >> paramInfo.praAdvantageValue;

	in >> paramInfo.chainStorage;
	in >> paramInfo.reserveODonorsForOCandidates;
	in >> paramInfo.checkDP;
	in >> paramInfo.includeCompatiblePairs;
	in >> paramInfo.excludeABDonorsFromSimulation;
	in >> paramInfo.allowABBridgeDonors;

	//qDebug() << "---Loaded Solution---";
	//qDebug() << opt;
	//qDebug()<< util;

	//qDebug()<< paramInfo.maxChainLength;

	//qDebug()<< paramInfo.pairFailureRate;
	//qDebug()<< paramInfo.adFailureRate;
	//qDebug()<< paramInfo.exogenousFailureRate;

	//qDebug()<< paramInfo.numberOfSolutions;

	//qDebug()<< paramInfo.chainStorage;
	//qDebug()<< paramInfo.reserveODonorsForOCandidates;
	//qDebug()<< paramInfo.checkDP;
	//qDebug()<< paramInfo.includeCompatiblePairs;
	//qDebug()<< paramInfo.excludeABDonorsFromSimulation;
	//qDebug()<< paramInfo.allowABBridgeDonors;
	
	QString timeStamp;
	QString simLog;
	qint32 solutionNumber;

	in >> timeStamp >> simLog >> solutionNumber;
	//qDebug() << timeStamp;
	//qDebug() << simLog;
	//qDebug() << solutionNumber;
	//qDebug() << "-------";
	structureSet.construct(paramInfo, timeStamp, simLog, true, solutionNumber);
	
	return in;
}