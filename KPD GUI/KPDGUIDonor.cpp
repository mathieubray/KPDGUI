#include "KPDGUIMatch.h"
#include "KPDGUICandidate.h"

#include "KPDGUIDonor.h"

KPDGUIDonor::KPDGUIDonor(){
	
	matchingID = 0;
	donorNumber = 0;

	donorName = "Donor Name";
	donorAge = 40;
	donorBT = BT_O;

	donorIsAltruistic = false;
	donorStatus = true;
	donorFailureProbability = 0.0;

	popularityInStructures = 0;
	popularityInSolutions = 0;

	donorMale = false;
	donorWeight = 75.0;
	donorBMI = 25.0;	

	donorBW4 = false;
	donorBW6 = false;
	donorDR51 = false;
	donorDR52 = false;
	donorDR53 = false;

	donorComment = "";
}

KPDGUIDonor::KPDGUIDonor(DialogDonor * d){

	matchingID = 0;
	donorNumber = 0;

	donorName = d->donorNameLineEdit->text();
	donorAge = d->donorAgeSpinBox->value();	
	donorBT = KPDFunctions::intToBloodType(d->donorBTComboBox->currentIndex());

	//donorIsAltruistic
	donorStatus = d->donorStatusCheckBox->isChecked();
	donorFailureProbability = d->donorFailureProbabilitySpinBox->value();

	popularityInStructures = 0;
	popularityInSolutions = 0;

	QString gender = d->donorGenderComboBox->currentText();
	double height = d->donorHeightSpinBox->value();
	double weight = d->donorWeightSpinBox->value();	

	if (gender == "Male") { donorMale = true; }
	else { donorMale = false; }
	donorWeight = weight;
	donorBMI = weight / height / height;
	
	QString hlaA1 = d->donorHLAA1ComboBox->currentText();
	QString hlaA2 = d->donorHLAA2ComboBox->currentText();
	if (hlaA1 != ""){
		donorA << hlaA1;
	}
	if (hlaA2 != hlaA1 && hlaA2 != ""){
		donorA << hlaA2;
	}

	QString hlaB1 = d->donorHLAB1ComboBox->currentText();
	QString hlaB2 = d->donorHLAB2ComboBox->currentText();
	if (hlaB1 != ""){
		donorB << hlaB1;
	}
	if (hlaB2 != hlaB1 && hlaB2 != ""){
		donorB << hlaB2;
	}

	QString hlaCW1 = d->donorHLACW1ComboBox->currentText();
	QString hlaCW2 = d->donorHLACW2ComboBox->currentText();
	if (hlaCW1 != ""){
		donorCW << hlaCW1;
	}
	if (hlaCW2 != hlaCW1 && hlaCW2 != ""){
		donorCW << hlaCW2;
	}

	QString hlaDQ1 = d->donorHLADQ1ComboBox->currentText();
	QString hlaDQ2 = d->donorHLADQ2ComboBox->currentText();
	if (hlaDQ1 != ""){
		donorDQ << hlaDQ1;
	}
	if (hlaDQ2 != hlaDQ1 && hlaDQ2 != ""){
		donorDQ << hlaDQ2;
	}

	QString hlaDR1 = d->donorHLADR1ComboBox->currentText();
	QString hlaDR2 = d->donorHLADR2ComboBox->currentText();
	if (hlaDR1 != ""){
		donorDR << hlaDR1;
	}
	if (hlaDR2 != hlaDR1 && hlaDR2 != ""){
		donorDR << hlaDR2;
	}

	donorBW4 = d->donorBW4CheckBox->isChecked();
	donorBW6 = d->donorBW6CheckBox->isChecked();
	donorDR51 = d->donorDR51CheckBox->isChecked();
	donorDR52 = d->donorDR52CheckBox->isChecked();
	donorDR53 = d->donorDR53CheckBox->isChecked();

	QString additionalHLA = d->donorHLALineEdit->text();
	additionalHLA.replace(" ", "");
	QStringList additionalHLAList = additionalHLA.split(";");

	foreach(QString antibody, additionalHLAList){
		additionalDonorHLA << antibody;
	}

	donorFailureProbability = 0.1;

	donorComment = d->commentTextEdit->toPlainText();

	setVisualProperties();
		
}

KPDGUIDonor::~KPDGUIDonor(){

}

int KPDGUIDonor::getID() const {
	return matchingID;
}

int KPDGUIDonor::getDonorNumber() const {
	return donorNumber;
}

QString KPDGUIDonor::getName() const {
	return donorName;
}

int KPDGUIDonor::getAge() const {
	return donorAge;
}

KPDBloodType KPDGUIDonor::getBT() const {
	return donorBT;
}

bool KPDGUIDonor::isAltruistic() const {
	return donorIsAltruistic;
}

bool KPDGUIDonor::getStatus() const {
	return donorStatus;
}

double KPDGUIDonor::getFailureProbability() const {
	return donorFailureProbability;
}

QSet<KPDGUIMatch *> KPDGUIDonor::getMatches() const {
	return donorMatches;
}

bool KPDGUIDonor::hasNoMatches() {
	return (donorMatches.size() == 0);
}

int KPDGUIDonor::getNumberOfMatches() {
	return donorMatches.size();
}

int KPDGUIDonor::getPopularityInStructures() {
	return popularityInStructures;
}

int KPDGUIDonor::getPopularityInSolutions() {
	return popularityInSolutions;
}

bool KPDGUIDonor::getMale() const{
	return donorMale;
}

double KPDGUIDonor::getWeight() const{
	return donorWeight;
}

double KPDGUIDonor::getBMI() const {
	return donorBMI;
}

QVector<QString> KPDGUIDonor::getA() const {
	return donorA;
}

QVector<QString> KPDGUIDonor::getB() const {
	return donorB;
}

QVector<QString> KPDGUIDonor::getCW() const {
	return donorCW;
}

QVector<QString> KPDGUIDonor::getDQ() const {
	return donorDQ;
}

QVector<QString> KPDGUIDonor::getDR() const {
	return donorDR;
}

bool KPDGUIDonor::getBW4() const{
	return donorBW4;
}

bool KPDGUIDonor::getBW6() const{
	return donorBW6;
}

bool KPDGUIDonor::getDR51() const{
	return donorDR51;
}

bool KPDGUIDonor::getDR52() const{
	return donorDR52;
}

bool KPDGUIDonor::getDR53() const{
	return donorDR53;
}

QVector<QString> KPDGUIDonor::getAdditionalHLA() const{
	return additionalDonorHLA;
}

QString KPDGUIDonor::getComment() const {
	return donorComment;
}

void KPDGUIDonor::setID(int id) {
	matchingID = id;
}

void KPDGUIDonor::setDonorNumber(int number) {
	donorNumber = number;
}

void KPDGUIDonor::setName(QString name){
	donorName = name;
}

void KPDGUIDonor::setAge(int age){
	donorAge = age;
}

void KPDGUIDonor::setBT(KPDBloodType bt){
	donorBT = bt;
}

void KPDGUIDonor::setAltruistic(bool altruistic) {
	donorIsAltruistic = altruistic;

	setBackgroundColor();
}

void KPDGUIDonor::setStatus(bool status) {
	donorStatus = status;
}

void KPDGUIDonor::setFailureProbability(double prob) {
	donorFailureProbability = prob;
}

void KPDGUIDonor::setMatches(QSet<KPDGUIMatch *> matches) {
	donorMatches.clear();

	foreach(KPDGUIMatch * match, matches) {
		donorMatches << match;
	}
}

void KPDGUIDonor::addMatchingCandidate(KPDGUIMatch * match) {
	donorMatches << match;
}

void KPDGUIDonor::removeMatchingCandidate(KPDGUIMatch * match) {
	if (donorMatches.contains(match)) {
		donorMatches.remove(match);
	}
}

KPDGUIMatch * KPDGUIDonor::findMatchingCandidate(KPDGUICandidate * candidate) {
	
	foreach(KPDGUIMatch * match, donorMatches) {
		if (match->getCandidate() == candidate) {
			return match;
		}
	}

	return NULL;
}

void KPDGUIDonor::increasePopularityInStructures() {
	popularityInStructures++;
}

void KPDGUIDonor::increasePopularityInSolutions() {
	popularityInSolutions++;
}

void KPDGUIDonor::decreasePopularityInStructures() {
	popularityInStructures--;
}

void KPDGUIDonor::decreasePopularityInSolutions() {
	popularityInSolutions--;
}

void KPDGUIDonor::resetPopularityInStructures() {
	popularityInStructures = 0;
}

void KPDGUIDonor::resetPopularityInSolutions() {
	popularityInSolutions = 0;
}

void KPDGUIDonor::setMale(bool genderMale){
	donorMale = genderMale;
}

void KPDGUIDonor::setWeight(double weight){
	donorWeight = weight;
}

void KPDGUIDonor::setBMI(double bmi) {
	donorBMI = bmi;
}

void KPDGUIDonor::setA(QVector<QString> hlaA){
	donorA.clear();
	foreach(QString hla, hlaA){
		donorA << hla;
	}
}

void KPDGUIDonor::setB(QVector<QString> hlaB){
	donorB.clear();
	foreach(QString hla, hlaB){
		donorB << hla;
	}
}

void KPDGUIDonor::setCW(QVector<QString> hlaCW){
	donorCW.clear();
	foreach(QString hla, hlaCW){
		donorCW << hla;
	}
}

void KPDGUIDonor::setDQ(QVector<QString> hlaDQ){
	donorDQ.clear();
	foreach(QString hla, hlaDQ){
		donorDQ << hla;
	}
}

void KPDGUIDonor::setDR(QVector<QString> hlaDR){
	donorDR.clear();
	foreach(QString hla, hlaDR){
		donorDR << hla;
	}
}

void KPDGUIDonor::addA(QString hlaA){
	donorA << hlaA;
}

void KPDGUIDonor::addB(QString hlaB){
	donorB << hlaB;
}

void KPDGUIDonor::addCW(QString hlaCW){
	donorCW << hlaCW;
}

void KPDGUIDonor::addDQ(QString hlaDQ){
	donorDQ << hlaDQ;
}

void KPDGUIDonor::addDR(QString hlaDR){
	donorDR << hlaDR;
}

void KPDGUIDonor::removeA(QString hlaA) {
	int position = donorA.indexOf(hlaA);
	if (position >= 0) {
		donorA.remove(position);
	}
}

void KPDGUIDonor::removeB(QString hlaB) {
	int position = donorB.indexOf(hlaB);
	if (position >= 0) {
		donorB.remove(position);
	}
}

void KPDGUIDonor::removeCW(QString hlaCW) {
	int position = donorCW.indexOf(hlaCW);
	if (position >= 0) {
		donorCW.remove(position);
	}
}

void KPDGUIDonor::removeDQ(QString hlaDQ) {
	int position = donorDQ.indexOf(hlaDQ);
	if (position >= 0) {
		donorDQ.remove(position);
	}
}

void KPDGUIDonor::removeDR(QString hlaDR) {
	int position = donorDR.indexOf(hlaDR);
	if (position >= 0) {
		donorDR.remove(position);
	}
}

void KPDGUIDonor::setBW4(bool hlaBW4) {
	donorBW4 = hlaBW4;
}

void KPDGUIDonor::setBW6(bool hlaBW6) {
	donorBW6 = hlaBW6;
}

void KPDGUIDonor::setDR51(bool hlaDR51) {
	donorDR51 = hlaDR51;
}

void KPDGUIDonor::setDR52(bool hlaDR52) {
	donorDR52 = hlaDR52;
}

void KPDGUIDonor::setDR53(bool hlaDR53) {
	donorDR53 = hlaDR53;
}

void KPDGUIDonor::setAdditionalDonorHLA(QVector<QString> additionalHLA){
	additionalDonorHLA.clear();
	foreach(QString hla, additionalHLA){
		additionalDonorHLA << hla;
	}
}

void KPDGUIDonor::addAdditionalDonorHLA(QString additionalHLA){
	additionalDonorHLA << additionalHLA;
}

void KPDGUIDonor::removeAdditionalDonorHLA(QString additionalHLA) {
	int position = additionalDonorHLA.indexOf(additionalHLA);
	if (position >= 0) {
		additionalDonorHLA.remove(position);
	}
}


void KPDGUIDonor::setComment(QString comment){
	donorComment = comment;
}

QPointF KPDGUIDonor::getCenter() {

	//qreal x = myDonor->mapFromScene(myDonor->boundingRect().x());
	//qreal y = myDonor->mapFromScene(myDonor->boundingRect().y());
	QPointF point = mapToScene(boundingRect().topLeft());
	qreal x = point.x();
	qreal y = point.y();

	qreal width = boundingRect().width();
	qreal height = boundingRect().height();

	return QPointF(x + width / 2, y + height / 2);
}

QString KPDGUIDonor::text() const
{
	return donorLabel;
}

void KPDGUIDonor::setText(const QString &text)
{
	prepareGeometryChange();
	donorLabel = text;
	update();
}

void KPDGUIDonor::setBackgroundColor()
{
	if (donorStatus) {
		if (donorIsAltruistic) {
			donorBackgroundColor = QColor(0, 255, 0);
		}
		else {
			donorBackgroundColor = QColor(0, 0, 255);
		}
	}
	else {
		if (donorIsAltruistic) {
			donorBackgroundColor = QColor(100, 125, 100);
		}
		else {
			donorBackgroundColor = QColor(100, 100, 125);
		}
	}

	update();
}

QColor KPDGUIDonor::backgroundColor() const
{
	return donorBackgroundColor;
}

//QRectF KPDGUIDonor::boundingRect() const
//{
//const int Margin = 1;
//return outlineRect().adjusted(-Margin, -Margin, +Margin, +Margin);
//}

//QRectF KPDGUIDonor::outlineRect() const
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

//QPainterPath KPDGUIDonor::shape() const
//{
//QRectF rect = outlineRect();

//QPainterPath path;
//path.addEllipse(rect);
//return path;
//}

void KPDGUIDonor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
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
	painter->setBrush(QBrush(donorBackgroundColor, Qt::SolidPattern));

	QRectF donorRect = boundingRect();
	painter->drawEllipse(donorRect);

	painter->setPen(QPen(myTextColor, 16, Qt::SolidLine, Qt::RoundCap));

	QFont * font = new QFont();
	font->setBold(true);
	font->setPointSize(8);
	painter->setFont(*font);

	painter->drawText(donorRect, Qt::AlignCenter, donorLabel);

}

QString KPDGUIDonor::donorString() {

	if (donorIsAltruistic) {
		return donorName + " (" + QString::number(matchingID) + ")";
	}
	else {
		return donorName + " (" + QString::number(matchingID) + "-" + QString::number(donorNumber) + ")";
	}
}

QString KPDGUIDonor::compatibilitiesString() {
	QString compatibleDonorString = "Compatible Donors: ";

	if (donorMatches.count() > 0) {
		QVector<int> compatibilities;
		foreach(KPDGUIMatch * match, donorMatches) {
			compatibilities.push_back(match->getCandidate()->getID());
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

QString KPDGUIDonor::fullHLAString() {
	QString hlaString = "";
	foreach(QString hlaA, donorA) {
		if (!hlaA.isEmpty()) {
			hlaString += hlaA;
			hlaString += ";";
		}
	}
	foreach(QString hlaB, donorB) {
		if (!hlaB.isEmpty()) {
			hlaString += hlaB;
			hlaString += ";";
		}
	}
	if (donorBW4 == true) {
		hlaString += "BW4";
		hlaString += ";";
	}
	if (donorBW6 == true) {
		hlaString += "BW6";
		hlaString += ";";
	}
	foreach(QString hlaCW, donorCW) {
		if (!hlaCW.isEmpty()) {
			hlaString += hlaCW;
			hlaString += ";";
		}
	}

	foreach(QString hlaDQ, donorDQ) {
		if (!hlaDQ.isEmpty()) {
			hlaString += hlaDQ;
			hlaString += ";";
		}
	}
	foreach(QString hlaDR, donorDR) {
		if (!hlaDR.isEmpty()) {
			hlaString += hlaDR;
			hlaString += ";";
		}
	}
	if (donorDR51 == true) {
		hlaString += "DR51";
		hlaString += ";";
	}
	if (donorDR52 == true) {
		hlaString += "DR52";
		hlaString += ";";
	}
	if (donorDR53 == true) {
		hlaString += "DR53";
		hlaString += ";";
	}
	hlaString.chop(1);
	hlaString += "(";
	foreach(QString hla, additionalDonorHLA) {
		if (!hla.isEmpty()) {
			hlaString += hla;
			hlaString += ";";
		}
	}
	hlaString.chop(1);
	hlaString += ")";

	return hlaString;
}

QString KPDGUIDonor::additionalHLAString() {
	QString hlaString = "";
	foreach(QString hla, additionalDonorHLA) {
		hlaString += hla;
		hlaString += ";";
	}

	hlaString.chop(1);

	return hlaString;
}

QVariant KPDGUIDonor::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemPositionHasChanged) {
		foreach(KPDGUIMatch * match, donorMatches) {			
			match->updatePosition();
		}
	}

	if (change == ItemSelectedHasChanged) {
		emit donorSelectionChanged(value.toBool());
	}

	return QGraphicsItem::itemChange(change, value);
}

void KPDGUIDonor::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
	emit donorEntered();
}

void KPDGUIDonor::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
	emit donorExited();
}

void KPDGUIDonor::mousePressEvent(QGraphicsSceneMouseEvent *event) {

	setSelected(true);

	emit donorClicked(isSelected());
}

void KPDGUIDonor::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) {

	editDonor();

	//QGraphicsObject::mouseDoubleClickEvent(event);
}

void KPDGUIDonor::setVisualProperties() {

	setRect(QRectF(0, 0, 65, 55));
	
	setBackgroundColor();
	setZValue(0);
	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);
	
	if (donorIsAltruistic) {
		setToolTip("AD " + QString::number(matchingID));
	}
	else {
		setToolTip("Donor " + QString::number(matchingID) + "-" + QString::number(donorNumber));
	}

}

void KPDGUIDonor::editDonor() {

}


QDataStream &operator<<(QDataStream &out, const KPDGUIDonor & donor)
{	
	out << donor.getID();
	out << donor.getDonorNumber();

	out << donor.getName();
	out << qint32(donor.getAge());
	out << qint32(KPDFunctions::bloodTypeToInt(donor.getBT()));

	out << donor.isAltruistic();
	out << donor.getStatus();
	out << donor.getFailureProbability();

	//out << donor.getMatches();
	
	out << donor.getMale();
	out << donor.getWeight();
	out << donor.getBMI();

	out << donor.getA();
	out << donor.getB();
	out << donor.getCW();
	out << donor.getDQ();
	out << donor.getDR();
	out << donor.getBW4();
	out << donor.getBW6();
	out << donor.getDR51();
	out << donor.getDR52();
	out << donor.getDR53();
	out << donor.getAdditionalHLA();
	
	out << donor.getComment();

	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUIDonor & donor)
{
	int id;
	int donorNumber;	

	QString name;
	int age;
	int BT;

	bool ad;
	bool status;
	bool prob;

	//QSet<KPDGUIMatch *> matches;

	bool male;
	double weight;
	double BMI;	
	
	QVector<QString> donorA;
	QVector<QString> donorB;	
	QVector<QString> donorCW;
	QVector<QString> donorDQ;
	QVector<QString> donorDR;
	bool donorBW4;
	bool donorBW6;
	bool donorDR51;
	bool donorDR52;
	bool donorDR53;
	QVector<QString> additionalDonorHLA;
	
	QString comment;

	in >> id >> donorNumber;

	in >> name >> age >> BT;

	in >> ad >> status >> prob;

	//in >> matches;

	in >> male >> weight >> BMI;
	
	in >> donorA >> donorB >> donorCW >> donorDQ >> donorDR;
	in >> donorBW4 >> donorBW6 >> donorDR51 >> donorDR52 >> donorDR53;
	in >> additionalDonorHLA;

	in >> comment;

	donor.setID(id);
	donor.setDonorNumber(donorNumber);

	donor.setName(name);
	donor.setAge(age);
	donor.setBT(KPDFunctions::intToBloodType(BT));

	donor.setAltruistic(ad);
	donor.setStatus(status);
	donor.setFailureProbability(prob);

	//donor.setMatches(matches);

	donor.setMale(male);
	donor.setWeight(weight);
	donor.setBMI(BMI);	

	donor.setA(donorA);
	donor.setB(donorB);
	donor.setCW(donorCW);
	donor.setDQ(donorDQ);
	donor.setDR(donorDR);
	donor.setBW4(donorBW4);
	donor.setBW6(donorBW6);
	donor.setDR51(donorDR51);
	donor.setDR52(donorDR52);
	donor.setDR53(donorDR52);
	donor.setAdditionalDonorHLA(additionalDonorHLA);

	donor.setComment(comment);

	return in;
}