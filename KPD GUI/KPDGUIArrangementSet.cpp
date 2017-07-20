#include "KPDGUIArrangementSet.h"

KPDGUIArrangementSet::KPDGUIArrangementSet(){
	
	arrangementSetParameters = new KPDGUIParameters();

	arrangementSetTimestamp = "";
	arrangementSetMatchRunText = "";
	
	isSolution = true;
	setNumber = -1;
	
}

KPDGUIArrangementSet::KPDGUIArrangementSet(KPDGUIParameters * parameters, QString timestamp, QString text, bool solution, int number){
	
	construct(parameters, timestamp, text, solution, number);
	
}

KPDGUIArrangementSet::~KPDGUIArrangementSet(){

}

void KPDGUIArrangementSet::construct(KPDGUIParameters * params, QString timestamp, QString text, bool solution, int number){
	
	arrangementSetParameters = new KPDGUIParameters();
	
	arrangementSetParameters->copyParameters(params);

	arrangementSetTimestamp = timestamp;
	arrangementSetMatchRunText = text;

	isSolution = solution;
	setNumber = number;
	

	QString textOptScheme = KPDFunctions::toString(arrangementSetParameters->getOptimizationScheme());

	if (isSolution){
		setText(0, textOptScheme + "[" + QString::number(setNumber) + "] (" + arrangementSetTimestamp + ")");
	}
	else{
		setText(0, textOptScheme + " (" + arrangementSetTimestamp + ")");
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
	return NULL;
}

QString KPDGUIArrangementSet::getTimestamp() const {
	return arrangementSetTimestamp;
}

QString KPDGUIArrangementSet::getMatchRunText() const {
	return arrangementSetMatchRunText;
}

bool KPDGUIArrangementSet::isSolutionSet() const {
	return isSolution;
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
		//qSort(newArrangementList.begin(), newArrangementList.end(), KPDGUIArrangementGreaterThan(0));


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
	qreal dist = 100 + 10 * arrangements.size();
	
	qreal centerX = this->centerX();
	qreal centerY = this->centerY();

	qreal angle = (2 * PI) / arrangements.size();
	qreal nodeAngle = PI;
	
	foreach(KPDGUIArrangement * arrangement, arrangements){
		arrangement->cluster(centerX + dist*cos(nodeAngle), centerY + dist*sin(nodeAngle));
		nodeAngle += angle;
	}	
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

QString KPDGUIArrangementSet::getDashboardString(){

	QString receipt = "";

	if (isSolution){
		receipt = receipt + "Solution " + QString::number(setNumber) + " For Match Run Performed On " + arrangementSetTimestamp + "\nObjective: " + QString::number(getUtility()) + "\n\n";
	}
	else {
		if (arrangementSetParameters->getOptimizationScheme() != KPDOptimizationScheme::LOCALLY_RELEVANT_SUBSETS){
			receipt = receipt + "Cycle/Chain List For Match Run Performed On " + arrangementSetTimestamp + "\n\n";
		}
		else{
			receipt = receipt + "LRS List For Match Run Performed On " + arrangementSetTimestamp + "\n\n";
		}
	}

	int chains = 0;
	int cycles = 0;

	foreach(KPDGUIArrangement * arrangement, arrangements){
		receipt = receipt + arrangement->arrangementDashboardString() + "\n";
		if (arrangement->hasAnNDD()){
			chains++;
		}
		else {
			cycles++;
		}
	}
	receipt = receipt + "\n" + arrangementSetMatchRunText + "\n";

	if (arrangementSetParameters->getOptimizationScheme() != KPDOptimizationScheme::LOCALLY_RELEVANT_SUBSETS){
		receipt = receipt + "Cycles: " + QString::number(cycles) + ", Chains: " + QString::number(chains) + "\n";
	}
	else{
		receipt = receipt + "Locally Relevant Subsets: " + QString::number(getNumberOfArrangements()) + "\n";
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

		if (arrangementSetParameters->getOptimizationScheme() == LOCALLY_RELEVANT_SUBSETS) {
			
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

		if (arrangementSetParameters->getOptimizationScheme() != KPDOptimizationScheme::LOCALLY_RELEVANT_SUBSETS) {

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

	qDebug() << "DOUBLE-CLICKED!";
	
	DialogMessage * dialog = new DialogMessage(getDashboardString());

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
		arrangementSetLRSs[size]->setText(0, "Locally Relevant Subsets of Size " + QString::number(size) + " (" + QString::number(arrangementSetLRSs[size]->childCount()) + ")");
	}
}


QDataStream &operator<<(QDataStream &out, const KPDGUIArrangementSet & arrangementSet)
{
	out << *arrangementSet.getParameters();
	out << arrangementSet.getTimestamp();
	out << arrangementSet.getMatchRunText();
	out << qint32(arrangementSet.getSetNumber());

	return out;
}

//void KPDGUINode::extractFromDataStream(QDataStream& dataStream)
QDataStream &operator>>(QDataStream &in, KPDGUIArrangementSet & arrangementSet)
{
	
	KPDGUIParameters * params= new KPDGUIParameters();
	QString timeStamp;
	QString text;
	bool isSolution;
	qint32 id;

	in >> *params >> timeStamp >> text >> isSolution >> id;
	
	arrangementSet.construct(params, timeStamp, text, isSolution, id);
	
	return in;
}