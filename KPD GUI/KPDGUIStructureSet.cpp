#include "KPDGUIStructureSet.h"

const qreal Pi = 3.14159265;

KPDGUIStructureSet::KPDGUIStructureSet(){
	myParameters.maxChainLength = 0;
	myParameters.utilScheme = "NULL";
	myParameters.optScheme = "NULL";
	myParameters.praAdvantage = false;
	myParameters.reserveOtoO = false;
	myParameters.checkDP = false;
	myParameters.includeCompatiblePairs = false;
	myParameters.includeABBridgeDonors = false;
	myParameters.numberOfSolutions = 0;

	myTimeStamp = "";
	myOptScheme = "";
	myPairList = "";
	mySimLog = "";
	solutionSet = true;
	mySolutionNumber = -1;
}

KPDGUIStructureSet::KPDGUIStructureSet(ParamInfoStruct parameters, QString timestamp, QString optScheme, QString includedPairList, QString simLog, bool solution, int solutionNumber){
	myTimeStamp = timestamp;
	myOptScheme = optScheme;
	myParameters = parameters;
	myPairList = includedPairList;
	mySimLog = simLog;
	solutionSet = solution;
	mySolutionNumber = solutionNumber;

	if (solutionSet){
		setText(0, myOptScheme + "[" + QString::number(mySolutionNumber) + "] (" + myTimeStamp + ")");
	}
	else{
		setText(0, myOptScheme + " (" + myTimeStamp + ")");
	}
	
	setUpWidgets();

	if (myOptScheme != "SCC"){
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

KPDGUIStructureSet::~KPDGUIStructureSet(){
	if (solutionSet){
		foreach(KPDGUIStructure * structure, myStructureList){
			structure->decreasePopularityInSolutions();
		}
	}
}

void KPDGUIStructureSet::construct(ParamInfoStruct parameters, QString timestamp, QString optScheme, QString includedPairList, QString simLog, bool solution, int solutionNumber){
	////qDebug() << myParameters.maxChainLength;
	
	myTimeStamp = timestamp;
	myOptScheme = optScheme;
	myParameters.maxChainLength = parameters.maxChainLength;
	myParameters.utilScheme = parameters.utilScheme;
	myParameters.optScheme = parameters.optScheme;
	myParameters.praAdvantage = parameters.praAdvantage;
	myParameters.reserveOtoO = parameters.reserveOtoO;
	myParameters.checkDP = parameters.checkDP;
	myParameters.includeCompatiblePairs = parameters.includeCompatiblePairs;
	myParameters.includeABBridgeDonors = parameters.includeABBridgeDonors;
	myParameters.numberOfSolutions = parameters.numberOfSolutions;
	myPairList = includedPairList;
	mySimLog = simLog;
	solutionSet = solution;
	mySolutionNumber = solutionNumber;

	if (solutionSet){
		setText(0, myOptScheme + "[" + QString::number(mySolutionNumber) + "] (" + myTimeStamp + ")");
	}
	else{
		setText(0, myOptScheme + " (" + myTimeStamp + ")");
	}

	setUpWidgets();

	if (myOptScheme != "SCC"){
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
	
	if (myOptScheme != "SCC"){
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
		////qDebug() << "A";
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

	/*QString filename = "";
	if (solutionSet){
		filename += "C:\\Users\\Mathieu Bray\\Desktop\\Solution_";
	}
	else {
		filename += "C:\\Users\\Mathieu Bray\\Desktop\\StructureList_";
	}
	filename += myTimeStamp + ".txt";*/

	//QFile file(filename);
	//if (file.open(QIODevice::ReadWrite))
	//{
		//QTextStream receipt;//(&file);
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
			if (myOptScheme != "SCC"){
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

		if (myOptScheme != "SCC"){
			receipt = receipt + "Cycles: " + QString::number(cycles) + ", Chains: " + QString::number(chains) + "\n";
		}
		else{
			receipt = receipt + "Components: "  + QString::number(size())  + "\n";
		}
		receipt = receipt + "Optimization Scheme: " + myOptScheme + "\n";
		receipt = receipt + "Maximum Chain Length: " + QString::number(myParameters.maxChainLength) + "\n";
		receipt = receipt + "Utility Scheme: " + myParameters.utilScheme + "\n";
		if (!myParameters.praAdvantage){
			receipt = receipt + "Do Not ";
		}
		receipt = receipt + "Add Additional Advantage to High PRA Candidates\n";
		if (!myParameters.reserveOtoO){
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
		if (!myParameters.includeABBridgeDonors){
			receipt = receipt + "Do Not ";
		}
		receipt = receipt + "Allow AB Bridge Donors\n";
		receipt = receipt + "Number of Solutions Produced: " + QString::number(myParameters.numberOfSolutions) + "\n";
		//receipt = receipt + "Included Pairs: " + myPairList + "\n\n";
	//}
		

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
	////qDebug() << "Entered <<";
	ParamInfoStruct paramInfo = structureSet.getParameters();
	out << qint32(paramInfo.maxChainLength);
	////qDebug() << "Max Chain Length: " << paramInfo.maxChainLength;
	out << paramInfo.utilScheme;
	////qDebug() << "Util Scheme: " << paramInfo.utilScheme;
	out << paramInfo.optScheme;
	////qDebug() << "Opt Scheme: " << paramInfo.optScheme;
	out << paramInfo.praAdvantage;
	////qDebug() << "PRA: " << paramInfo.praAdvantage;
	out << paramInfo.reserveOtoO;
	////qDebug() << "Reserve O to O: " << paramInfo.reserveOtoO;
	out << paramInfo.checkDP;
	////qDebug() << "Check DP: " << paramInfo.checkDP;
	out << paramInfo.includeCompatiblePairs;
	////qDebug() << "Include Compat: " << paramInfo.includeCompatiblePairs;
	out << paramInfo.includeABBridgeDonors;
	////qDebug() << "Include AB: " << paramInfo.includeABBridgeDonors;
	out << qint32(paramInfo.numberOfSolutions);
	////qDebug() << "Number of Solutions: " << paramInfo.numberOfSolutions;

	out << structureSet.getTimeStamp();
	////qDebug() << "Time Stamp: " << structureSet.getTimeStamp();
	out << structureSet.getOptScheme();
	////qDebug() << "Opt Scheme: " << structureSet.getOptScheme();
	out << structureSet.getIncludedPairList();
	out << structureSet.getSimLog();
	out << qint32(structureSet.getSolutionNumber());
	////qDebug() << "Solution Number: " << structureSet.getSolutionNumber();

	return out;
}

//void KPDGUINode::extractFromDataStream(QDataStream& dataStream)
QDataStream &operator>>(QDataStream &in, KPDGUIStructureSet & structureSet)
{
	ParamInfoStruct paramInfo;
	
	in >> paramInfo.maxChainLength;
	in >> paramInfo.utilScheme;
	in >> paramInfo.optScheme;
	in >> paramInfo.praAdvantage;
	in >> paramInfo.reserveOtoO;
	in >> paramInfo.checkDP;
	in >> paramInfo.includeCompatiblePairs;
	in >> paramInfo.includeABBridgeDonors;
	in >> paramInfo.numberOfSolutions;

	////qDebug() << paramInfo.maxChainLength;
	////qDebug() << paramInfo.utilScheme;
	////qDebug() << paramInfo.optScheme;
	////qDebug() << paramInfo.praAdvantage;
	////qDebug() << paramInfo.reserveOtoO;
	////qDebug() << paramInfo.checkDP;
	////qDebug() << paramInfo.includeCompatiblePairs;
	////qDebug() << paramInfo.includeABBridgeDonors;
	////qDebug() << paramInfo.numberOfSolutions;

	QString timeStamp;
	QString optScheme;
	QString includedPairList;
	QString simLog;
	qint32 solutionNumber;

	in >> timeStamp >> optScheme >> includedPairList >> simLog >> solutionNumber;

	////qDebug() << structureSet.getTimeStamp();
	////qDebug() << structureSet.getOptScheme();
	////qDebug() << structureSet.getSolutionNumber();

	structureSet.construct(paramInfo, timeStamp, optScheme, includedPairList, simLog, true, solutionNumber);
	
	return in;
}