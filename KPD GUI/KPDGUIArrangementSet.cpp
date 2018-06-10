#include "KPDGUIArrangementSet.h"

KPDGUIArrangementSet::KPDGUIArrangementSet(){
	
	arrangementSetParameters = new KPDGUIParameters();

	arrangementSetName = "";
	arrangementSetTimestamp = "";
	arrangementSetNodeList = "";
	arrangementSetMatchList = "";
	isSolution = true;
	isComplete = true;
	setNumber = -1;
	
}

KPDGUIArrangementSet::KPDGUIArrangementSet(KPDGUIParameters * parameters, QString timestamp, QString nodeList, QString matchList, bool solution, bool complete, int trueSetNum, int number){
	
	arrangementSetParameters = new KPDGUIParameters();

	construct(parameters, timestamp, nodeList, matchList, solution, complete, trueSetNum, number);
	
}

KPDGUIArrangementSet::~KPDGUIArrangementSet(){

}

void KPDGUIArrangementSet::construct(KPDGUIParameters * params, QString timestamp, QString nodeList, QString matchList, bool solution, bool complete, int trueSetNum, int number){
	
	arrangementSetParameters->copyParameters(params);
	
	arrangementSetName = KPDFunctions::toString(arrangementSetParameters->getOptimizationScheme());
	arrangementSetTimestamp = timestamp;
	arrangementSetNodeList = nodeList;
	arrangementSetMatchList = matchList;
	isSolution = solution;
	isComplete = complete;
	trueSetSize = trueSetNum;
	setNumber = number;
	
	if (isSolution){
		setText(0, arrangementSetName + " [" + QString::number(setNumber) + "]\n" + arrangementSetTimestamp);
	}
	else{
		setText(0, arrangementSetName + "\n" + arrangementSetTimestamp);
	}

	setUpWidgets();	
}

void KPDGUIArrangementSet::addArrangement(KPDGUIArrangement * arrangement){	

	arrangements.push_back(arrangement);
		
	setUpWidgets();
}


QList<KPDGUIArrangement*> KPDGUIArrangementSet::getArrangements(){
	
	QList<KPDGUIArrangement *> arrangementListCopy;

	foreach(KPDGUIArrangement * arrangement, arrangements){
		arrangementListCopy.push_back(arrangement);
	}

	return arrangementListCopy;
}

KPDGUIParameters * KPDGUIArrangementSet::getParameters() const {
	return arrangementSetParameters;
}

QString KPDGUIArrangementSet::getName() const {
	return arrangementSetName;
}

QString KPDGUIArrangementSet::getTimestamp() const {
	return arrangementSetTimestamp;
}

QString KPDGUIArrangementSet::getNodeList() const {
	return arrangementSetNodeList;
}

QString KPDGUIArrangementSet::getMatchList() const {
	return arrangementSetMatchList;
}

bool KPDGUIArrangementSet::isSolutionSet() const {
	return isSolution;
}

bool KPDGUIArrangementSet::isCompleteSet() const {
	return isComplete;
}

int KPDGUIArrangementSet::getTrueSetSize() const {
	return trueSetSize;
}

int KPDGUIArrangementSet::getSetNumber() const {
	return setNumber;
}


int KPDGUIArrangementSet::getNumberOfArrangements() {
	return arrangements.size();
}

int KPDGUIArrangementSet::getNumberOfNodes() {

	int numberOfNodes = 0;

	foreach(KPDGUIArrangement * arrangement, arrangements) {
		numberOfNodes += arrangement->getNumberOfNodes();
	}

	return numberOfNodes;
}

double KPDGUIArrangementSet::getUtility() {

	double utility = 0;

	foreach(KPDGUIArrangement * arrangement, arrangements) {
		utility += arrangement->getUtility();
	}

	return utility;
}


void KPDGUIArrangementSet::sort() {

	for (int i = 0; i < childCount(); i++) {

		QTreeWidgetItem * item = child(i);

		QList<KPDGUIArrangementWrapper*> newArrangementList;
		int itemCount = item->childCount();

		for (int i = 0; i < itemCount; i++) {
			QTreeWidgetItem * arrangement = item->child(0);
			KPDGUIArrangementWrapper * temp = dynamic_cast<KPDGUIArrangementWrapper *>(arrangement);
			if (temp) {
				newArrangementList.push_back(temp);
				item->removeChild(arrangement);
			}
		}

		foreach(KPDGUIArrangementWrapper * arrangement, newArrangementList) {
			item->addChild(arrangement);
		}
	}
}

bool KPDGUIArrangementSet::containsNode(KPDGUINode * node) {

	foreach(KPDGUIArrangement * arrangement, arrangements) {
		if (arrangement->containsNode(node)) {
			return true;
		}
	}

	return false;
}

bool KPDGUIArrangementSet::containsDonor(KPDGUIDonor * donor) {

	foreach(KPDGUIArrangement * arrangement, arrangements) {
		if (arrangement->containsDonor(donor)) {
			return true;
		}
	}

	return false;
}

bool KPDGUIArrangementSet::containsCandidate(KPDGUICandidate * candidate) {

	foreach(KPDGUIArrangement * arrangement, arrangements) {
		if (arrangement->containsCandidate(candidate)) {
			return true;
		}
	}

	return false;
}

void KPDGUIArrangementSet::select(){

	foreach(KPDGUIArrangement * arrangement, arrangements){
		arrangement->select();
	}

}

void KPDGUIArrangementSet::highlight(){

	foreach(KPDGUIArrangement * arrangement, arrangements){
		arrangement->highlight();
	}

}

void KPDGUIArrangementSet::undoHighlights(){

	foreach(KPDGUIArrangement * arrangement, arrangements){
		arrangement->undoHighlights();
	}

}

qreal KPDGUIArrangementSet::centerX(){

	qreal avgx = 0;

	foreach(KPDGUIArrangement * arrangement, arrangements){
		avgx += arrangement->centerX();
	}
	avgx = avgx / arrangements.size();

	return avgx;
}

qreal KPDGUIArrangementSet::centerY(){
	
	qreal avgy = 0;

	foreach(KPDGUIArrangement * arrangement, arrangements){
		avgy += arrangement->centerY();
	}
	avgy = avgy / arrangements.size();

	return avgy;
}

void KPDGUIArrangementSet::cluster(){
	qreal dist = 125 + 50 * arrangements.size();
	
	qreal centerX = this->centerX();
	qreal centerY = this->centerY();

	qreal angle = (2 * PI) / arrangements.size();
	qreal nodeAngle = PI;
	
	foreach(KPDGUIArrangement * arrangement, arrangements){
		arrangement->cluster(centerX + dist*cos(nodeAngle), centerY + dist*sin(nodeAngle));
		nodeAngle += angle;
	}	

	emit arrangementClustered(centerX, centerY);
}

void KPDGUIArrangementSet::isolate() {

	qreal minX = 9999;
	qreal maxX = -9999;
	qreal minY = 9999;
	qreal maxY = -9999;

	foreach(KPDGUIArrangement * arrangement, arrangements) {
		qreal newMinX = arrangement->minX();
		qreal newMaxX = arrangement->maxX();
		qreal newMinY = arrangement->minY();
		qreal newMaxY = arrangement->maxY();

		if (newMinX < minX) {
			minX = newMinX;
		}
		if (newMaxX > maxX) {
			maxX = newMaxX;
		}
		if (newMinY < minY) {
			minY = newMinY;
		}
		if (newMaxY > maxY) {
			maxY = newMaxY;
		}
	}

	//foreach(KPDGUIArrangement * arrangement, arrangements) {
		//arrangement->isolate(minX,maxX,minY,maxY);
	//}

	emit arrangementIsolated(minX, maxX, minY, maxY);

}

void KPDGUIArrangementSet::increasePopularity(){

	foreach(KPDGUIArrangement * arrangement, arrangements){
		arrangement->increasePopularity(isSolution);
	}
	
}

void KPDGUIArrangementSet::decreasePopularity() {

	foreach(KPDGUIArrangement * arrangement, arrangements) {
		arrangement->decreasePopularity(isSolution);
	}

}

void KPDGUIArrangementSet::resetPopularity(){

	foreach(KPDGUIArrangement * arrangement, arrangements){
		arrangement->resetPopularity(isSolution);
	}

}

QString KPDGUIArrangementSet::toString(){

	QString receipt = "";

	if (isSolution){
		receipt = receipt + "Solution " + QString::number(setNumber) + " For Match Run " + arrangementSetName + "\n";
		receipt = receipt + "Performed On " + arrangementSetTimestamp + "\n";
		receipt = receipt + "\n";

		if (floor(getUtility()) == getUtility()) {
			receipt = receipt + "Objective: " + QString::number(getUtility()) + "\n\n";
		}
		else {
			receipt = receipt + "Objective: " + QString::number(floor(getUtility() * 1000 + 0.5) / 1000) + "\n\n";
		}

	}
	else {
		if (arrangementSetParameters->getOptimizationScheme() != KPDOptimizationScheme::LOCALLY_RELEVANT_SUBGRAPHS){
			receipt = receipt + "Match Run " + arrangementSetName + "\n";
			receipt = receipt + "Performed On " + arrangementSetTimestamp + "\n\n";
		}
		else{
			receipt = receipt + "Match Run " + arrangementSetName + "\n";
			receipt = receipt + "Performed On " + arrangementSetTimestamp + "\n\n";
		}
	}

	if (!isSolution && !isComplete) {
		receipt = receipt + "NOTE: THE COLLECTION BELOW IS NOT COMPLETE\n";
		if (arrangementSetParameters->getCollectArrangements()) {			
			receipt = receipt + "The true number of possible arrangements (" + QString::number(trueSetSize) + ") was higher than the specified cutoff of " + QString::number(arrangementSetParameters->getCollectArrangementsCutoff()) + "\n\n";		
		}
		else {
			receipt = receipt + "User specified not to collect all possible arrangements, of which there were " + QString::number(trueSetSize) + "\n\n";
		}
	}

	int chains = 0;
	int cycles = 0;

	if (isSolution) {
		if (arrangementSetParameters->getOptimizationScheme() != KPDOptimizationScheme::LOCALLY_RELEVANT_SUBGRAPHS) {
			receipt = receipt + "------------------------------\n";
			receipt = receipt + "Solution Cycle/Chain List\n";
			receipt = receipt + "------------------------------\n\n";
		}
		else {
			receipt = receipt + "----------------------\n";
			receipt = receipt + "Solution LRS List\n";
			receipt = receipt + "----------------------\n\n";
		}
	}
	else {
		if (arrangementSetParameters->getOptimizationScheme() != KPDOptimizationScheme::LOCALLY_RELEVANT_SUBGRAPHS) {
			receipt = receipt + "----------------------\n";
			receipt = receipt + "Match Run Cycle/Chain List\n";
			receipt = receipt + "----------------------\n\n";
		}
		else {
			receipt = receipt + "----------------------\n";
			receipt = receipt + "Match Run LRS List\n";
			receipt = receipt + "----------------------\n\n";
		}
	}

	foreach(KPDGUIArrangement * arrangement, arrangements) {
		receipt = receipt + arrangement->arrangementDashboardString() + "\n";
		if (arrangement->hasAnNDD()) {
			chains++;
		}
		else {
			cycles++;
		}
	}
	receipt = receipt + "\n";


	if (arrangementSetParameters->getOptimizationScheme() != KPDOptimizationScheme::LOCALLY_RELEVANT_SUBGRAPHS) {
		receipt = receipt + "Cycles: " + QString::number(cycles) + ", Chains: " + QString::number(chains) + "\n";
	}
	else {
		receipt = receipt + "Locally Relevant Subgraphs: " + QString::number(getNumberOfArrangements()) + "\n";
	}

	receipt = receipt + "\n";

	receipt = receipt + "---------------------\n";
	receipt = receipt + "Pairing/NDD List\n";
	receipt = receipt + "---------------------\n\n";

	receipt = receipt + arrangementSetNodeList;

	receipt = receipt + "\n";

	receipt = receipt + "---------------\n";
	receipt = receipt + "Match List\n";
	receipt = receipt + "---------------\n\n";

	receipt = receipt + arrangementSetMatchList;

	receipt = receipt + "\n";

	receipt = receipt + "------------------------\n";
	receipt = receipt + "Match Run Specifications\n";
	receipt = receipt + "------------------------\n\n";

	receipt = receipt + arrangementSetParameters->toString();

	receipt = receipt + "\n";

	return receipt;
}


QString KPDGUIArrangementSet::toCondensedString() {

	QString receipt = "";

	if (isSolution) {
		receipt = receipt + "Solution " + QString::number(setNumber) + " For Match Run " + arrangementSetName + "\n";
		receipt = receipt + "Performed On " + arrangementSetTimestamp + "\n\nObjective: " + QString::number(getUtility()) + "\n\n";
	}

	int chains = 0;
	int cycles = 0;

	foreach(KPDGUIArrangement * arrangement, arrangements) {
		if (arrangement->hasAnNDD()) {
			chains++;
		}
		else {
			cycles++;
		}
	}

	if (arrangementSetParameters->getOptimizationScheme() != KPDOptimizationScheme::LOCALLY_RELEVANT_SUBGRAPHS) {
		receipt = receipt + "Cycles: " + QString::number(cycles) + ", Chains: " + QString::number(chains) + "\n";
	}
	else {
		receipt = receipt + "Locally Relevant Subgraphs: " + QString::number(getNumberOfArrangements()) + "\n";
	}

	return receipt;
}

void KPDGUIArrangementSet::setUpWidgets(){

	takeChildren();

	arrangementSetCycles.clear();
	arrangementSetChains.clear();
	arrangementSetLRSs.clear();
	
	foreach(KPDGUIArrangement * arrangement, arrangements) {
		
		int size = arrangement->getNumberOfNodes();

		if (arrangementSetParameters->getOptimizationScheme() == LOCALLY_RELEVANT_SUBGRAPHS) {
			
			QTreeWidgetItem * newItem = new QTreeWidgetItem();
			arrangementSetLRSs[size] = newItem;
			
		}

		else {

			if (arrangement->hasAnNDD()) {
				QTreeWidgetItem * newItem = new QTreeWidgetItem();
				arrangementSetChains[size-1] = newItem;

			}
			else {
				QTreeWidgetItem * newItem = new QTreeWidgetItem();
				arrangementSetCycles[size] = newItem;
			}

		}
	}

	foreach(KPDGUIArrangement * arrangement, arrangements) {

		KPDGUIArrangementWrapper * wrapper = new KPDGUIArrangementWrapper(arrangement);

		int arrangementSize = arrangement->getNumberOfNodes();

		if (arrangementSetParameters->getOptimizationScheme() != KPDOptimizationScheme::LOCALLY_RELEVANT_SUBGRAPHS) {

			if (arrangement->hasAnNDD()) {
				arrangementSetChains[arrangementSize - 1]->addChild(wrapper);
			}
			else {
				arrangementSetCycles[arrangementSize]->addChild(wrapper);
			}
		}

		else {
			arrangementSetLRSs[arrangementSize]->addChild(wrapper);
		}
	}
	

	foreach(int size, arrangementSetCycles.keys()) {
		addChild(arrangementSetCycles[size]);
	}

	foreach(int size, arrangementSetChains.keys()) {
		addChild(arrangementSetChains[size]);
	}

	foreach(int size, arrangementSetLRSs.keys()) {
		addChild(arrangementSetLRSs[size]);
	}

	updateText();

	setExpanded(true);
}

void KPDGUIArrangementSet::displayInformation() {
	
	DialogMessage * dialog = new DialogMessage(toString());

	if (!isSolution) {
		dialog->setWindowTitle("Possible Exchanges");
	}

	if (dialog->exec()) {
		
	}

}

void KPDGUIArrangementSet::updateText(){

	foreach(int size, arrangementSetCycles.keys()) {
		arrangementSetCycles[size]->setText(0, QString::number(size) + "-Way Exchanges (" + QString::number(arrangementSetCycles[size]->childCount()) + ")");
	}

	foreach(int size, arrangementSetChains.keys()) {
		arrangementSetChains[size]->setText(0, "Chains of Length " + QString::number(size) + " (" + QString::number(arrangementSetChains[size]->childCount()) + ")");
	}

	foreach(int size, arrangementSetLRSs.keys()) {
		arrangementSetLRSs[size]->setText(0, "Locally Relevant Subgraphs of Size " + QString::number(size) + " (" + QString::number(arrangementSetLRSs[size]->childCount()) + ")");
	}
}


QDataStream &operator<<(QDataStream &out, const KPDGUIArrangementSet & arrangementSet)
{
	out << *arrangementSet.getParameters();
	out << arrangementSet.getTimestamp();
	out << arrangementSet.getNodeList();
	out << arrangementSet.getMatchList();
	out << arrangementSet.isSolutionSet();
	out << arrangementSet.isCompleteSet();
	out << qint32(arrangementSet.getTrueSetSize());
	out << qint32(arrangementSet.getSetNumber());

	return out;
}

//void KPDGUINode::extractFromDataStream(QDataStream& dataStream)
QDataStream &operator>>(QDataStream &in, KPDGUIArrangementSet & arrangementSet)
{	
	KPDGUIParameters * params = new KPDGUIParameters();
	QString timeStamp;
	QString nodeList;
	QString matchList;
	bool isSolution;
	bool isComplete;
	int trueSetNum;
	int id;

	in >> *params >> timeStamp >> nodeList >> matchList >> isSolution >> isComplete >> trueSetNum >> id;
	
	arrangementSet.construct(params, timeStamp, nodeList, matchList, isSolution, isComplete, trueSetNum, id);
	
	return in;
}