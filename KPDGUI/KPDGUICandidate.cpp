#include "KPDGUIMatch.h"
#include "KPDGUINode.h"

#include "KPDGUICandidate.h"

KPDGUICandidate::KPDGUICandidate(){

	matchingID = 0;

	candidateName = "Candidate Name";
	candidateAge = 40;
	candidatePRA = 0;
	candidateBT = BT_O;	
	
	candidateStatus = true;
	candidateFailureProbability = 0.0;

	popularityInArrangements = 0;
	popularityInSolutions = 0;

	candidateMale = false;
	candidateRace = RACE_WHITE;
	candidateDiabetes = false;
	candidateHeight = 1.62;
	candidateWeight = 76.0;	
	candidatePrevTrans = false;
	candidateTOD = 0.0;
	candidateHepC = false;
	candidateInsurance = PUBLIC;
	
	candidateComment = "";

	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);

	setRect(QRectF(0, 0, 75, 65));

	currentDisplayMode = DONOR_DISPLAY_MULTIPLE;
	hue = 80;
}

KPDGUICandidate::KPDGUICandidate(DialogCandidate * c){

	matchingID = 0;

	popularityInArrangements = 0;
	popularityInSolutions = 0;
	
	editCandidate(c);

	setRect(QRectF(0, 0, 75, 65));
	
	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);
	
	currentDisplayMode = DONOR_DISPLAY_MULTIPLE;
	hue = 80;
}

KPDGUICandidate::~KPDGUICandidate(){

}

bool KPDGUICandidate::checkWithinBounds(int minPRA, int maxPRA) {

	if (minPRA <= candidatePRA && maxPRA >= candidatePRA) {
		return true;
	}

	return false;
}

void KPDGUICandidate::addHLA(QString hla) {
	candidateHLA << hla;
}

void KPDGUICandidate::removeHLA(QString hla) {
	int hlaIndex = candidateHLA.indexOf(hla);
	if (hlaIndex >= 0) {
		candidateHLA.remove(hlaIndex);
	}
}

void KPDGUICandidate::addExcludedDonor(int donor) {
	candidateExcludedDonors << donor;
}

void KPDGUICandidate::removeExcludedDonor(int donor) {
	int hlaIndex = candidateExcludedDonors.indexOf(donor);
	if (hlaIndex >= 0) {
		candidateExcludedDonors.remove(hlaIndex);
	}
}

bool KPDGUICandidate::hasNoMatches() {
	return (candidateMatches.size() == 0);
}

int KPDGUICandidate::getNumberOfMatches() {
	return candidateMatches.size();
}

void KPDGUICandidate::addMatchingDonor(KPDGUIMatch * match) {
	candidateMatches << match;
}

void KPDGUICandidate::removeMatchingDonor(KPDGUIMatch * match) {
	if (candidateMatches.contains(match)) {
		candidateMatches.remove(match);
	}
}

KPDGUIMatch * KPDGUICandidate::findMatchingDonor(KPDGUIDonor * donor) {

	foreach(KPDGUIMatch * match, candidateMatches) {
		if (match->getDonor() == donor) {
			return match;
		}
	}

	return NULL;
}

void KPDGUICandidate::increasePopularityInArrangements() {
	popularityInArrangements++;
}

void KPDGUICandidate::increasePopularityInSolutions() {
	popularityInSolutions++;
}

void KPDGUICandidate::decreasePopularityInArrangements() {
	popularityInArrangements--;
}

void KPDGUICandidate::decreasePopularityInSolutions() {
	popularityInSolutions--;
}

void KPDGUICandidate::resetPopularityInArrangements() {
	popularityInArrangements = 0;
}

void KPDGUICandidate::resetPopularityInSolutions() {
	popularityInSolutions = 0;
}

KPDGUINode * KPDGUICandidate::getParentNode() const {
	return parentNode;
}

int KPDGUICandidate::getID() const {
	return matchingID;
}

QString KPDGUICandidate::getName() const {
	return candidateName;
}

int KPDGUICandidate::getAge() const {
	return candidateAge;
}

int KPDGUICandidate::getPRA() const {
	return candidatePRA;
}

KPDBloodType KPDGUICandidate::getBT() const {
	return candidateBT;
}

QVector<QString> KPDGUICandidate::getHLA() const {
	return candidateHLA;
}

bool KPDGUICandidate::getMale() const{
	return candidateMale;
}

KPDRace KPDGUICandidate::getRace() const {
	return candidateRace;
}

bool KPDGUICandidate::getDiabetes() const {
	return candidateDiabetes;
}

double KPDGUICandidate::getHeight() const {
	return candidateHeight;
}

double KPDGUICandidate::getWeight() const {
	return candidateWeight;
}

double KPDGUICandidate::getBMI() const{

	//double newHeight = (double)candidateHeight * 0.0254;
	//double newWeight = (double)candidateWeight * 0.4536;

	//return (newWeight / newHeight) / newHeight;

	return (candidateWeight / candidateHeight) / candidateHeight;
}

bool KPDGUICandidate::getPrevTrans() const{
	return candidatePrevTrans;
}

double KPDGUICandidate::getTOD() const{
	return candidateTOD;
}

bool KPDGUICandidate::getHepC() const{
	return candidateHepC;
}

KPDInsurance KPDGUICandidate::getInsurance() const {
	return candidateInsurance;
}

bool KPDGUICandidate::getStatus() const {
	return candidateStatus;
}

double KPDGUICandidate::getFailureProbability() const {
	return candidateFailureProbability;
}

QVector<int> KPDGUICandidate::getExcludedDonors() const {
	return candidateExcludedDonors;
}

QSet<KPDGUIMatch *> KPDGUICandidate::getMatches() const {
	return candidateMatches;
}

int KPDGUICandidate::getPopularityInArrangements() {
	return popularityInArrangements;
}

int KPDGUICandidate::getPopularityInSolutions() {
	return popularityInSolutions;
}

QString KPDGUICandidate::getComment() const{
	return candidateComment;
}

void KPDGUICandidate::setParentNode(KPDGUINode * node) {
	parentNode = node;
}

void KPDGUICandidate::setID(int id){
	matchingID = id;		
}

void KPDGUICandidate::setName(QString name){
	candidateName = name;	
}

void KPDGUICandidate::setAge(int age){
	candidateAge = age;	
}

void KPDGUICandidate::setPRA(int pra) {
	candidatePRA = pra;	
}

void KPDGUICandidate::setBT(KPDBloodType bt){
	candidateBT = bt;	
}

void KPDGUICandidate::setHLA(QVector<QString> antibodies) {
	candidateHLA.clear();
	foreach(QString antibody, antibodies) {
		candidateHLA << antibody;
	}
}

void KPDGUICandidate::setMale(bool genderMale){
	candidateMale = genderMale;
}

void KPDGUICandidate::setRace(KPDRace race) {
	candidateRace = race;
}

void KPDGUICandidate::setDiabetes(bool diabetes) {
	candidateDiabetes = diabetes;
}

void KPDGUICandidate::setHeight(double height) {
	candidateHeight = height;
}

void KPDGUICandidate::setWeight(double weight) {
	candidateWeight = weight;
}

void KPDGUICandidate::setPrevTrans(bool prevTrans){
	candidatePrevTrans = prevTrans;
}

void KPDGUICandidate::setTOD(double tod){
	candidateTOD = tod;
}

void KPDGUICandidate::setHepC(bool hepC){
	candidateHepC = hepC;
}

void KPDGUICandidate::setInsurance(KPDInsurance insurance) {
	candidateInsurance = insurance;
}

void KPDGUICandidate::setStatus(bool status) {
	candidateStatus = status;
}

void KPDGUICandidate::setFailureProbability(double prob) {
	candidateFailureProbability = prob;
}

void KPDGUICandidate::setExcludedDonors(QVector<int> donors) {
	candidateExcludedDonors.clear();
	foreach(int donor, donors) {
		candidateExcludedDonors << donor;
	}
}

void KPDGUICandidate::setMatches(QSet<KPDGUIMatch *> matches) {
	candidateMatches.clear();

	foreach(KPDGUIMatch * match, matches) {
		candidateMatches << match;
	}
}

void KPDGUICandidate::setComment(QString comment){
	candidateComment = comment;
}

void KPDGUICandidate::setDisplayMode(KPDDonorDisplayMode mode) {
	currentDisplayMode = mode;
}


QPointF KPDGUICandidate::getCandidatePosition() {

	QPointF point = scenePos();
	qreal x = point.x();
	qreal y = point.y();

	qreal width = boundingRect().width();
	qreal height = boundingRect().height();

	return QPointF(x + width / 2, y + height / 2);
}

void KPDGUICandidate::setCandidatePosition(QPointF point) {

	qreal width = boundingRect().width();
	qreal height = boundingRect().height();

	QPointF adjustedPosition(point.x() - width / 2, point.y() - height / 2);

	setPos(adjustedPosition);
}

void KPDGUICandidate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	QColor myBackgroundColor;

	if (candidateStatus) {
		if(currentDisplayMode == DONOR_DISPLAY_NONE && parentNode->getNumberOfDonors() > 1) {
			myBackgroundColor = QColor(255, 128, 0);
		}
		else {
			myBackgroundColor = QColor(255, hue, hue);
		}		
	}
	else {
		myBackgroundColor = QColor(100, 100, 100);
	}

	if (isSelected()) {
		setOpacity(1);
	}
	else {
		setOpacity(0.5);
	}

	setToolTip(candidateString());

	/// Node ///

	//Outline
	QPen pen(Qt::black);

	if (option->state & QStyle::State_Selected) {
		pen.setWidth(1.5);
		//pen.setStyle(Qt::DotLine);
	}

	painter->setPen(pen);
	//if (!candidateStatus) {
		painter->setBrush(QBrush(myBackgroundColor, Qt::SolidPattern));
	//}
	//else {
	//	if (parentNode->getNumberOfDonors() > 1) {
	//		painter->setBrush(QBrush(myBackgroundColor, Qt::Dense3Pattern));
	//	}
	//	else {
	//		painter->setBrush(QBrush(myBackgroundColor, Qt::SolidPattern));
	//	}
	//}
	QRectF donorRect = boundingRect();
	painter->drawEllipse(donorRect);

	//Text
	painter->setPen(QPen(Qt::white, 16, Qt::SolidLine, Qt::RoundCap));

	QFont * font = new QFont();
	font->setBold(true);
	font->setPointSize(14);
	painter->setFont(*font);

	painter->drawText(donorRect, Qt::AlignCenter, QString::number(matchingID));

}

QString KPDGUICandidate::candidateString() {
	return candidateName + " (" + QString::number(matchingID) + ")";
}

QString KPDGUICandidate::compatibilitiesString() {
	QString compatibleDonorString = "Compatible Donors: ";

	if (candidateMatches.count() > 0) {
		QVector<int> compatibilities;
		foreach(KPDGUIMatch * match, candidateMatches) {
			compatibilities.push_back(match->getDonor()->getID());
		}
		qSort(compatibilities);
		foreach(int id, compatibilities) {
			compatibleDonorString += QString::number(id);
			compatibleDonorString += ", ";
		}
		compatibleDonorString.chop(2);
	}
	else {
		compatibleDonorString += "None";
	}

	return compatibleDonorString;
}

QString KPDGUICandidate::excludedDonorString()
{
	QString excludedDonorString = "";
	foreach(int donor, candidateExcludedDonors) {
		excludedDonorString += QString::number(donor);
		excludedDonorString += ";";
	}

	excludedDonorString.chop(1);

	return excludedDonorString;
}

QString KPDGUICandidate::hlaString() {
	QString hlaString = "";
	foreach(QString antibody, candidateHLA) {
		hlaString += antibody;
		hlaString += ";";
	}

	hlaString.chop(1);

	return hlaString;
}

QVariant KPDGUICandidate::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemPositionHasChanged) {
		foreach(KPDGUIMatch * match, candidateMatches) {
			match->updatePosition();
		}
	}

	if (change == ItemSelectedHasChanged) {
		//emit candidateSelectionChanged(matchingID, value.toBool());

		parentNode->setSelected(value.toBool());

		emit candidateSelectionChanged();
	}

	return QGraphicsItem::itemChange(change, value);
}

void KPDGUICandidate::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
	
	emit candidateEntered(matchingID);
}

void KPDGUICandidate::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
		
	emit candidateExited(matchingID);
}

void KPDGUICandidate::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) {
	edit();	
}

void KPDGUICandidate::edit() {

	int r = QMessageBox::Yes;

	if (parentNode->getLoadedFromAPD()) {
		r = QMessageBox::warning(0, "Warning: APD Candidate", "This candidate was loaded from APD data. As there is no HLA information, editing the candidate may lead to undesirable changes elsewhere in the pool. Do you wish to proceed?", QMessageBox::Yes | QMessageBox::No);
	}

	if (r == QMessageBox::Yes) {
		DialogCandidate * candidateDialog = new DialogCandidate(this, false);
		
		if (candidateDialog->exec()) {

			editCandidate(candidateDialog);

			parentNode->setLoadedFromAPD(false);
		}
	}

}


void KPDGUICandidate::editCandidate(DialogCandidate * dialog) {

	candidateName = dialog->candidateNameLineEdit->text();
	candidateAge = dialog->candidateAgeSpinBox->value();
	candidatePRA = dialog->candidatePRASpinBox->value();
	candidateBT = KPDFunctions::intToBloodType(dialog->candidateBTComboBox->currentIndex());

	candidateStatus = dialog->candidateStatusCheckBox->isChecked();
	candidateFailureProbability = dialog->candidateFailureProbabilitySpinBox->value();

	QString gender = dialog->candidateGenderComboBox->currentText();
	if (gender == "Male") { candidateMale = true; }
	else { candidateMale = false; }
	candidateRace = KPDFunctions::intToRace(dialog->candidateRaceComboBox->currentIndex());
	candidateDiabetes = dialog->candidateDiabetesCheckBox->isChecked();
	candidateHeight = dialog->candidateHeightSpinBox->value();
	candidateWeight = dialog->candidateWeightSpinBox->value();
	candidatePrevTrans = dialog->candidatePrevTransCheckBox->isChecked();
	candidateTOD = dialog->candidateTODSpinBox->value();
	candidateHepC = dialog->candidateHepCCheckBox->isChecked();
	candidateInsurance = KPDFunctions::intToInsurance(dialog->candidateInsuranceComboBox->currentIndex());
	
	QString antibodies = dialog->candidateHLALineEdit->text();
	antibodies.replace(" ", "");
	QStringList antibodyList = antibodies.split(";");

	candidateHLA.clear();
	foreach(QString antibody, antibodyList) {
		candidateHLA << antibody;
	}

	candidateComment = dialog->commentTextEdit->toPlainText();

	emit candidateEdited();
	
}

void KPDGUICandidate::addAdditionalDonor() {

	emit addAdditionalDonorSignal();

}

void KPDGUICandidate::updateVisualProperties() {

	prepareGeometryChange();
	update();
}

void KPDGUICandidate::updateHue(int n, double mu, double sigma) {

	double pivot = (getNumberOfMatches() - mu) / (sigma / sqrt(n));

	if (pivot < -2) {
		pivot = -2;
	}

	if (pivot > 2) {
		pivot = 2;
	}

	//hue = 200 - 50 * (pivot + 2);

	hue = 0;

}

QDataStream &operator<<(QDataStream &out, const KPDGUICandidate & candidate)
{
	out << candidate.getID();

	// Major Fields
	out << candidate.getName();
	out << qint32(candidate.getAge());
	out << qint32(candidate.getPRA());
	out << qint32(KPDFunctions::bloodTypeToInt(candidate.getBT()));

	// HLA Information
	out << candidate.getHLA();

	// Characteristics
	out << candidate.getMale();
	out << qint32(KPDFunctions::raceToInt(candidate.getRace()));
	out << candidate.getDiabetes();
	out << qreal(candidate.getHeight());
	out << qreal(candidate.getWeight());
	out << candidate.getPrevTrans();
	out << qreal(candidate.getTOD());
	out << candidate.getHepC();
	out << qint32(KPDFunctions::insuranceToInt(candidate.getInsurance()));
	
	// Additional Parameters
	out << candidate.getStatus();
	out << qreal(candidate.getFailureProbability());
	
	out << candidate.getExcludedDonors();
	
	out << candidate.getComment();

	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUICandidate & candidate)
{
	int matchingID;
	in >> matchingID;
	candidate.setID(matchingID);

	// Major Fields
	QString name;
	int age;
	int pra;
	int BT;
	in >> name >> age >> pra >> BT;
	candidate.setName(name);
	candidate.setAge(age);
	candidate.setBT(KPDFunctions::intToBloodType(BT));
	candidate.setPRA(pra);

	// HLA Information
	QVector<QString> hla;
	in >> hla;
	candidate.setHLA(hla);
		
	// Characteristics
	bool male;
	int race;
	bool diabetes;
	double height;
	double weight;			
	bool prevTrans;
	double TOD;
	bool hepC;
	int insurance;
	in >> male >> race >> diabetes >> height >> weight >> prevTrans >> TOD >> hepC >> insurance;
	candidate.setMale(male);
	candidate.setRace(KPDFunctions::intToRace(race));
	candidate.setDiabetes(diabetes);
	candidate.setHeight(height);
	candidate.setWeight(weight);
	candidate.setPrevTrans(prevTrans);
	candidate.setTOD(TOD);
	candidate.setHepC(hepC);
	candidate.setInsurance(KPDFunctions::intToInsurance(insurance));

	// Additional Parameters
	bool status;
	double prob;
	in >> status >> prob;
	candidate.setStatus(status);
	candidate.setFailureProbability(prob);

	QVector<int> excludedDonors;
	in >> excludedDonors;
	candidate.setExcludedDonors(excludedDonors);

	QString comment;	
	in >> comment;
	candidate.setComment(comment);

	return in;

}