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

	popularityInStructures = 0;
	popularityInSolutions = 0;

	candidateMale = false;
	candidateRace = RACE_WHITE;
	candidateDiabetes = false;
	candidateWeight = 75.0;
	candidateBMI = 25.0;		
	candidatePrevTrans = false;
	candidateTOD = 0.0;
	candidateHepC = false;
	
	candidateComment = "";
}

KPDGUICandidate::KPDGUICandidate(DialogCandidate * c){

	matchingID = 0;
	
	candidateName = c->candidateNameLineEdit->text();
	candidateAge = c->candidateAgeSpinBox->value();
	candidatePRA = c->candidatePRASpinBox->value();
	candidateBT = KPDFunctions::intToBloodType(c->candidateBTComboBox->currentIndex());
	
	candidateStatus = c->candidateStatusCheckBox->isChecked();
	candidateFailureProbability = c->candidateFailureProbabilitySpinBox->value();

	popularityInStructures = 0;
	popularityInSolutions = 0;

	QString gender = c->candidateGenderComboBox->currentText();
	double height = c->candidateHeightSpinBox->value();
	double weight = c->candidateWeightSpinBox->value();	

	if (gender == "Male"){ candidateMale = true; }
	else { candidateMale = false; }
	candidateRace = KPDFunctions::intToRace(c->candidateRaceComboBox->currentIndex());
	candidateDiabetes = c->candidateDiabetesCheckBox->isChecked();
	candidateWeight = weight;
	candidateBMI = weight / height / height;
	candidatePrevTrans = c->candidatePrevTransCheckBox->isChecked();
	candidateTOD = c->candidateTODSpinBox->value();
	candidateHepC = c->candidateHepCCheckBox->isChecked();

	/*QString excludedDonors = c->excludedDonorLineEdit->text();
	excludedDonors.replace(" ", "");
	QStringList excludedDonorList = excludedDonors.split(";");

	foreach(QString donor, excludedDonorList){
		candidateExcludedDonors << donor.toInt();
	}*/

	QString antibodies = c->candidateHLALineEdit->text();
	antibodies.replace(" ", "");
	QStringList antibodyList = antibodies.split(";");

	foreach(QString antibody, antibodyList){
		candidateHLA << antibody;
	}

	candidateComment = c->commentTextEdit->toPlainText();

	setVisualProperties();

}

KPDGUICandidate::~KPDGUICandidate(){

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

bool KPDGUICandidate::checkWithinBounds(int minPRA, int maxPRA) {

	if (minPRA <= candidatePRA && maxPRA >= candidatePRA) {
		return true;
	}

	return false;
}

KPDBloodType KPDGUICandidate::getBT() const {
	return candidateBT;
}

bool KPDGUICandidate::getStatus() const {
	return candidateStatus;
}

double KPDGUICandidate::getFailureProbability() const {
	return candidateFailureProbability;
}

QSet<KPDGUIMatch *> KPDGUICandidate::getMatches() const {
	return candidateMatches;
}

bool KPDGUICandidate::hasNoMatches() {
	return (candidateMatches.size() == 0);
}

int KPDGUICandidate::getNumberOfMatches() {
	return candidateMatches.size();
}

int KPDGUICandidate::getPopularityInStructures() {
	return popularityInStructures;
}

int KPDGUICandidate::getPopularityInSolutions() {
	return popularityInSolutions;
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

double KPDGUICandidate::getWeight() const {
	return candidateWeight;
}

double KPDGUICandidate::getBMI() const{
	return candidateBMI;
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

QVector<int> KPDGUICandidate::getExcludedDonors() const{
	return candidateExcludedDonors;
}

QVector<QString> KPDGUICandidate::getHLA() const {
	return candidateHLA;
}

QString KPDGUICandidate::getComment() const{
	return candidateComment;
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

void KPDGUICandidate::setStatus(bool status) {
	candidateStatus = status;
}

void KPDGUICandidate::setFailureProbability(double prob) {
	candidateFailureProbability = prob;
}

void KPDGUICandidate::setMatches(QSet<KPDGUIMatch *> matches) {
	candidateMatches.clear();

	foreach(KPDGUIMatch * match, matches) {
		candidateMatches << match;
	}
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

void KPDGUICandidate::increasePopularityInStructures() {
	popularityInStructures++;
}

void KPDGUICandidate::increasePopularityInSolutions() {
	popularityInSolutions++;
}

void KPDGUICandidate::decreasePopularityInStructures() {
	popularityInStructures--;
}

void KPDGUICandidate::decreasePopularityInSolutions() {
	popularityInSolutions--;
}

void KPDGUICandidate::resetPopularityInStructures() {
	popularityInStructures = 0;
}

void KPDGUICandidate::resetPopularityInSolutions() {
	popularityInSolutions = 0;
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

void KPDGUICandidate::setWeight(double weight) {
	candidateWeight = weight;
}

void KPDGUICandidate::setBMI(double bmi){
	candidateBMI = bmi;
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

void KPDGUICandidate::setExcludedDonors(QVector<int> donors){
	candidateExcludedDonors.clear();
	foreach(int donor, donors){
		candidateExcludedDonors << donor;
	}
}

void KPDGUICandidate::addExcludedDonor(int donor){
	candidateExcludedDonors << donor;
}

void KPDGUICandidate::removeExcludedDonor(int donor) {
	int position = candidateExcludedDonors.indexOf(donor);
	if (position >= 0) {
		candidateExcludedDonors.remove(position);
	}
}

void KPDGUICandidate::setHLA(QVector<QString> antibodies){
	candidateHLA.clear();
	foreach(QString antibody, antibodies){
		candidateHLA << antibody;
	}
}

void KPDGUICandidate::addHLA(QString hla){
	candidateHLA << hla;
}

void KPDGUICandidate::removeHLA(QString hla) {
	int position = candidateHLA.indexOf(hla);
	if (position >= 0) {
		candidateHLA.remove(position);
	}
}

void KPDGUICandidate::setComment(QString comment){
	candidateComment = comment;
}

QPointF KPDGUICandidate::getCenter() {

	//qreal x = myDonor->mapFromScene(myDonor->boundingRect().x());
	//qreal y = myDonor->mapFromScene(myDonor->boundingRect().y());
	QPointF point = mapFromScene(boundingRect().topLeft());
	qreal x = point.x();
	qreal y = point.y();

	qreal width = boundingRect().width();
	qreal height = boundingRect().height();

	return QPointF(x + width / 2, y + height / 2);
}

QString KPDGUICandidate::text() const
{
	return candidateLabel;
}

void KPDGUICandidate::setText(const QString &text)
{
	prepareGeometryChange();
	candidateLabel = text;
	update();
}

void KPDGUICandidate::setBackgroundColor() {

	if (candidateStatus) {
		candidateBackgroundColor = QColor(255, candidatePRA * 1.5, candidatePRA * 1.5);		
	}
	else {
		candidateBackgroundColor = QColor(100, 100, 100);
	}

	update();
}

QColor KPDGUICandidate::backgroundColor() const
{
	return candidateBackgroundColor;
}

//QRectF KPDGUICandidate::boundingRect() const
//{
//const int Margin = 1;
//return outlineRect().adjusted(-Margin, -Margin, +Margin, +Margin);
//}

//QRectF KPDGUICandidate::outlineRect() const
//{
/*qreal x1; qreal x2; qreal y1; qreal y2;

int Padding = 12;
QFont * font = new QFont();
font->setBold(true);
font->setPointSize(8);
QFontMetricsF * metrics = new QFontMetricsF(*font);
QRectF rect = metrics->boundingRect(myText);
rect.getCoords(&x1, &y1, &x2, &y2);
rect.adjust(-(2.5*Padding - x1), -(Padding - y1), (2.5*Padding - x2), (Padding - y2));
rect.translate(-rect.center());
return rect; */
//}

//QPainterPath KPDGUICandidate::shape() const
//{
//QRectF rect = outlineRect();

//QPainterPath path;
//path.addEllipse(rect);
//return path;
//}

void KPDGUICandidate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	QColor myOutlineColor = Qt::black;
	QColor myTextColor = Qt::white;

	//Outline
	QPen pen(myOutlineColor);

	if (option->state & QStyle::State_Selected) {
		pen.setStyle(Qt::DotLine);
		pen.setWidth(2);
	}

	painter->setPen(pen);
	painter->setBrush(QBrush(candidateBackgroundColor, Qt::SolidPattern));

	QRectF donorRect = boundingRect();
	painter->drawEllipse(donorRect);

	painter->setPen(QPen(myTextColor, 16, Qt::SolidLine, Qt::RoundCap));

	QFont * font = new QFont();
	font->setBold(true);
	font->setPointSize(8);
	painter->setFont(*font);

	painter->drawText(donorRect, Qt::AlignCenter, candidateLabel);

}

QString KPDGUICandidate::candidateString() {
	return "";
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
		emit candidateSelectionChanged(value.toBool());
	}

	return QGraphicsItem::itemChange(change, value);
}

void KPDGUICandidate::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
	emit candidateEntered();
}

void KPDGUICandidate::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
	emit candidateExited();
}

void KPDGUICandidate::mousePressEvent(QGraphicsSceneMouseEvent *event) {

	setSelected(true);

	emit candidateClicked(isSelected());
}

void KPDGUICandidate::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) {

	editCandidate();

	//QGraphicsObject::mouseDoubleClickEvent(event);
}

void KPDGUICandidate::setVisualProperties() {

	setRect(QRectF(0, 0, 75, 65));

	setBackgroundColor();
	setZValue(0);
	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);

	setToolTip("Candidate " + QString::number(matchingID));

}

void KPDGUICandidate::editCandidate() {

}

QDataStream &operator<<(QDataStream &out, const KPDGUICandidate & candidate)
{
	out << candidate.getID();

	out << candidate.getName();
	out << qint32(candidate.getAge());
	out << qint32(candidate.getPRA());
	out << qint32(KPDFunctions::bloodTypeToInt(candidate.getBT()));

	out << candidate.getStatus();
	out << candidate.getFailureProbability();
	
	//out << candidate.getMatches();

	out << candidate.getMale();
	out << qint32(KPDFunctions::raceToInt(candidate.getRace()));
	out << candidate.getDiabetes();
	out << candidate.getWeight();
	out << candidate.getBMI();	
	out << candidate.getPrevTrans();
	out << candidate.getTOD();
	out << candidate.getHepC();

	out << candidate.getExcludedDonors();
	out << candidate.getHLA();
	
	out << candidate.getComment();

	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUICandidate & candidate)
{
	int uniqueID;

	QString name;
	int age;
	int pra;
	int BT;

	bool status;
	double prob;

	//QSet<KPDGUIMatch *> matches;
	
	bool male;
	int race;
	bool diabetes;
	double weight;
	double BMI;			
	bool prevTrans;
	double TOD;
	bool hepC;

	QVector<int> excludedDonors;
	QVector<QString> hla;

	QString comment;

	in >> uniqueID;

	in >> name >> age >> pra >> BT;	

	in >> status >> prob;

	//in >> matches;

	in >> male >> race >> diabetes >> weight;
	in >> BMI >> prevTrans >> TOD >> hepC;
	
	in >> excludedDonors >> hla;
	
	in >> comment;

	candidate.setID(uniqueID);

	candidate.setName(name);
	candidate.setAge(age);
	candidate.setBT(KPDFunctions::intToBloodType(BT));
	candidate.setPRA(pra);

	candidate.setStatus(status);
	candidate.setFailureProbability(prob);

	//candidate.setMatches(matches);

	candidate.setMale(male);
	candidate.setRace(KPDFunctions::intToRace(race));
	candidate.setDiabetes(diabetes);
	candidate.setWeight(weight);
	candidate.setBMI(BMI);	
	candidate.setPrevTrans(prevTrans);
	candidate.setTOD(TOD);
	candidate.setHepC(hepC);

	candidate.setExcludedDonors(excludedDonors);
	candidate.setHLA(hla);

	candidate.setComment(comment);

	return in;

}