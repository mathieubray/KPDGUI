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

	popularityInArrangements = 0;
	popularityInSolutions = 0;

	donorMale = false;
	donorRace = RACE_WHITE;
	donorHeight = 1.5;
	donorWeight = 60.0;
	donorCigarette = false;

	donorBW4 = false;
	donorBW6 = false;
	donorDR51 = false;
	donorDR52 = false;
	donorDR53 = false;

	donorComment = "";

	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);	

	if (donorIsAltruistic) {
		setRect(QRectF(0, 0, 55, 50));
	}
	else {
		setRect(QRectF(0, 0, 35, 30));
	}
}

KPDGUIDonor::KPDGUIDonor(DialogDonor * d){

	matchingID = 0;
	donorNumber = 0;

	popularityInArrangements = 0;
	popularityInSolutions = 0;

	editDonor(d);

	if (donorIsAltruistic) {
		setRect(QRectF(0, 0, 45, 40));
	}
	else {
		setRect(QRectF(0, 0, 35, 30));
	}

	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);
		
}

KPDGUIDonor::~KPDGUIDonor(){

}

void KPDGUIDonor::addA(QString hlaA) {
	donorA << hlaA;
}

void KPDGUIDonor::addB(QString hlaB) {
	donorB << hlaB;
}

void KPDGUIDonor::addCW(QString hlaCW) {
	donorCW << hlaCW;
}

void KPDGUIDonor::addDQ(QString hlaDQ) {
	donorDQ << hlaDQ;
}

void KPDGUIDonor::addDR(QString hlaDR) {
	donorDR << hlaDR;
}

void KPDGUIDonor::addAdditionalDonorHLA(QString additionalHLA) {
	additionalDonorHLA << additionalHLA;
}

void KPDGUIDonor::removeA(QString hlaA) {
	int hlaIndex = donorA.indexOf(hlaA);
	if (hlaIndex >= 0) {
		donorA.remove(hlaIndex);
	}
}

void KPDGUIDonor::removeB(QString hlaB) {
	int hlaIndex = donorB.indexOf(hlaB);
	if (hlaIndex >= 0) {
		donorB.remove(hlaIndex);
	}
}

void KPDGUIDonor::removeCW(QString hlaCW) {
	int hlaIndex = donorCW.indexOf(hlaCW);
	if (hlaIndex >= 0) {
		donorCW.remove(hlaIndex);
	}
}

void KPDGUIDonor::removeDQ(QString hlaDQ) {
	int hlaIndex = donorDQ.indexOf(hlaDQ);
	if (hlaIndex >= 0) {
		donorDQ.remove(hlaIndex);
	}
}

void KPDGUIDonor::removeDR(QString hlaDR) {
	int hlaIndex = donorDR.indexOf(hlaDR);
	if (hlaIndex >= 0) {
		donorDR.remove(hlaIndex);
	}
}

void KPDGUIDonor::removeAdditionalDonorHLA(QString additionalHLA) {
	int hlaIndex = additionalDonorHLA.indexOf(additionalHLA);
	if (hlaIndex >= 0) {
		additionalDonorHLA.remove(hlaIndex);
	}
}

bool KPDGUIDonor::hasNoMatches() {
	return (donorMatches.size() == 0);
}

int KPDGUIDonor::getNumberOfMatches() {
	return donorMatches.size();
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

void KPDGUIDonor::increasePopularityInArrangements() {
	popularityInArrangements++;
}

void KPDGUIDonor::increasePopularityInSolutions() {
	popularityInSolutions++;
}

void KPDGUIDonor::decreasePopularityInArrangements() {
	popularityInArrangements--;
}

void KPDGUIDonor::decreasePopularityInSolutions() {
	popularityInSolutions--;
}

void KPDGUIDonor::resetPopularityInArrangements() {
	popularityInArrangements = 0;
}

void KPDGUIDonor::resetPopularityInSolutions() {
	popularityInSolutions = 0;
}

int KPDGUIDonor::getID() const {
	return matchingID;
}

int KPDGUIDonor::getDonorNumber() const {
	return donorNumber;
}

bool KPDGUIDonor::isAltruistic() const {
	return donorIsAltruistic;
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

bool KPDGUIDonor::getBW4() const {
	return donorBW4;
}

bool KPDGUIDonor::getBW6() const {
	return donorBW6;
}

bool KPDGUIDonor::getDR51() const {
	return donorDR51;
}

bool KPDGUIDonor::getDR52() const {
	return donorDR52;
}

bool KPDGUIDonor::getDR53() const {
	return donorDR53;
}

QVector<QString> KPDGUIDonor::getAdditionalHLA() const {
	return additionalDonorHLA;
}

bool KPDGUIDonor::getMale() const {
	return donorMale;
}

KPDRace KPDGUIDonor::getRace() const {
	return donorRace;
}

double KPDGUIDonor::getHeight() const {
	return donorHeight;
}

double KPDGUIDonor::getWeight() const {
	return donorWeight;
}

double KPDGUIDonor::getBMI() const {
	return (donorWeight / donorHeight) / donorHeight;
}

bool KPDGUIDonor::getCigarette() const {
	return donorCigarette;
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

int KPDGUIDonor::getPopularityInArrangements() {
	return popularityInArrangements;
}

int KPDGUIDonor::getPopularityInSolutions() {
	return popularityInSolutions;
}

QString KPDGUIDonor::getComment() const {
	return donorComment;
}

void KPDGUIDonor::setParentNode(KPDGUINode * node) {
	parentNode = node;
}

void KPDGUIDonor::setID(int id) {
	matchingID = id;

	updateVisualProperties();
}

void KPDGUIDonor::setDonorNumber(int number) {
	donorNumber = number;

	updateVisualProperties();
}

void KPDGUIDonor::setAltruistic(bool altruistic) {
	donorIsAltruistic = altruistic;

	if (donorIsAltruistic) {
		setRect(QRectF(0, 0, 55, 50));
	}
	else {
		setRect(QRectF(0, 0, 35, 30));
	}

	updateVisualProperties();
}

void KPDGUIDonor::setName(QString name) {
	donorName = name;

	updateVisualProperties();
}

void KPDGUIDonor::setAge(int age) {
	donorAge = age;

	updateVisualProperties();
}

void KPDGUIDonor::setBT(KPDBloodType bt) {
	donorBT = bt;

	updateVisualProperties();
}

void KPDGUIDonor::setA(QVector<QString> hlaA) {
	donorA.clear();
	foreach(QString hla, hlaA) {
		donorA << hla;
	}
}

void KPDGUIDonor::setB(QVector<QString> hlaB) {
	donorB.clear();
	foreach(QString hla, hlaB) {
		donorB << hla;
	}
}

void KPDGUIDonor::setCW(QVector<QString> hlaCW) {
	donorCW.clear();
	foreach(QString hla, hlaCW) {
		donorCW << hla;
	}
}

void KPDGUIDonor::setDQ(QVector<QString> hlaDQ) {
	donorDQ.clear();
	foreach(QString hla, hlaDQ) {
		donorDQ << hla;
	}
}

void KPDGUIDonor::setDR(QVector<QString> hlaDR) {
	donorDR.clear();
	foreach(QString hla, hlaDR) {
		donorDR << hla;
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

void KPDGUIDonor::setAdditionalDonorHLA(QVector<QString> additionalHLA) {
	additionalDonorHLA.clear();
	foreach(QString hla, additionalHLA) {
		additionalDonorHLA << hla;
	}
}

void KPDGUIDonor::setMale(bool genderMale) {
	donorMale = genderMale;

	updateVisualProperties();
}

void KPDGUIDonor::setRace(KPDRace race) {
	donorRace = race;

	updateVisualProperties();
}

void KPDGUIDonor::setHeight(double height) {
	donorHeight = height;

	updateVisualProperties();
}

void KPDGUIDonor::setWeight(double weight) {
	donorWeight = weight;

	updateVisualProperties();
}

void KPDGUIDonor::setCigarette(bool cigarette) {
	donorCigarette = cigarette;

	updateVisualProperties();
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

void KPDGUIDonor::setComment(QString comment){
	donorComment = comment;
}

void KPDGUIDonor::setDisplayMode(KPDNodeDisplayMode mode) {
	currentDisplayMode = mode;
}

QPointF KPDGUIDonor::getDonorPosition() {

	QPointF point = scenePos();
	qreal x = point.x();
	qreal y = point.y();

	qreal width = boundingRect().width();
	qreal height = boundingRect().height();

	return QPointF(x + width / 2, y + height / 2);
}

void KPDGUIDonor::setDonorPosition(QPointF point) {

	qreal width = boundingRect().width();
	qreal height = boundingRect().height();

	QPointF adjustedPosition(point.x() - width / 2, point.y() - height / 2);

	setPos(adjustedPosition);
}

QPointF KPDGUIDonor::getPosition() {

	if (currentDisplayMode == SEPARATE_DONOR_CANDIDATE) {
		return getDonorPosition();
	}
	else if (currentDisplayMode == COMBINE_DONOR_CANDIDATE) {
		return parentNode->getNodePosition();
	}
	else {
		return getDonorPosition();
	}
}

QPolygonF KPDGUIDonor::getRect() {

	if (currentDisplayMode == SEPARATE_DONOR_CANDIDATE) {
		return sceneBoundingRect();
	}
	else if (currentDisplayMode == COMBINE_DONOR_CANDIDATE) {
		return parentNode->getRect();
	}
	else {
		return sceneBoundingRect();
	}

}

void KPDGUIDonor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	QColor myBackgroundColor;
	if (donorStatus) {
		if (donorIsAltruistic) {
			myBackgroundColor = QColor(200, 0, 200);
		}
		else {
			myBackgroundColor = QColor(0, 0, 255);
		}
	}
	else {
		if (donorIsAltruistic) {
			myBackgroundColor = QColor(75, 0, 75);
		}
		else {
			myBackgroundColor = QColor(0, 0, 100);
		}
	}

	//if (donorIsAltruistic){
		if (isSelected()) {
			setOpacity(1);
		}
		else {
			setOpacity(0.5);
		}
	//}

	setToolTip(donorString());

	/// Node ///

	//Outline
	QPen pen(Qt::black);

	if (isSelected()) {
		pen.setStyle(Qt::DotLine);
		pen.setWidth(2);
	}

	painter->setPen(pen);
	painter->setBrush(QBrush(myBackgroundColor, Qt::SolidPattern));

	QRectF donorRect = boundingRect();
	painter->drawEllipse(donorRect);

	painter->setPen(QPen(Qt::white, 16, Qt::SolidLine, Qt::RoundCap));

	QFont * font = new QFont();
	font->setBold(true);
	font->setPointSize(8);
	painter->setFont(*font);

	if (donorIsAltruistic) {
		painter->drawText(donorRect, Qt::AlignCenter, QString::number(matchingID));
	}
	else {
		painter->drawText(donorRect, Qt::AlignCenter, QString::number(matchingID) + "-" + QString::number(donorNumber));
	}
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
		emit donorSelectionChanged(matchingID, donorNumber, value.toBool());
		update();
	}

	return QGraphicsItem::itemChange(change, value);
}

void KPDGUIDonor::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
	
	emit donorEntered(matchingID, donorNumber);
}

void KPDGUIDonor::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
	
	emit donorExited(matchingID, donorNumber);
}

void KPDGUIDonor::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) {

	DialogDonor * donorDialog = new DialogDonor(this, false);
	if (donorDialog->exec()) {
		editDonor(donorDialog);
	}

}

void KPDGUIDonor::editDonor(DialogDonor * dialog) {
	
	donorName = dialog->donorNameLineEdit->text();
	donorAge = dialog->donorAgeSpinBox->value();
	donorBT = KPDFunctions::intToBloodType(dialog->donorBTComboBox->currentIndex());

	donorStatus = dialog->donorStatusCheckBox->isChecked();
	donorFailureProbability = dialog->donorFailureProbabilitySpinBox->value();

	QString gender = dialog->donorGenderComboBox->currentText();
	if (gender == "Male") { donorMale = true; }
	else { donorMale = false; }
	donorRace = KPDFunctions::intToRace(dialog->donorRaceComboBox->currentIndex());
	donorHeight = dialog->donorHeightSpinBox->value();
	donorWeight = dialog->donorWeightSpinBox->value();
	donorCigarette = dialog->donorCigaretteCheckBox->isChecked();

	QString hlaA1 = dialog->donorHLAA1ComboBox->currentText();
	QString hlaA2 = dialog->donorHLAA2ComboBox->currentText();
	if (hlaA1 != "") {
		donorA << hlaA1;
	}
	if (hlaA2 != hlaA1 && hlaA2 != "") {
		donorA << hlaA2;
	}

	QString hlaB1 = dialog->donorHLAB1ComboBox->currentText();
	QString hlaB2 = dialog->donorHLAB2ComboBox->currentText();
	if (hlaB1 != "") {
		donorB << hlaB1;
	}
	if (hlaB2 != hlaB1 && hlaB2 != "") {
		donorB << hlaB2;
	}

	QString hlaCW1 = dialog->donorHLACW1ComboBox->currentText();
	QString hlaCW2 = dialog->donorHLACW2ComboBox->currentText();
	if (hlaCW1 != "") {
		donorCW << hlaCW1;
	}
	if (hlaCW2 != hlaCW1 && hlaCW2 != "") {
		donorCW << hlaCW2;
	}

	QString hlaDQ1 = dialog->donorHLADQ1ComboBox->currentText();
	QString hlaDQ2 = dialog->donorHLADQ2ComboBox->currentText();
	if (hlaDQ1 != "") {
		donorDQ << hlaDQ1;
	}
	if (hlaDQ2 != hlaDQ1 && hlaDQ2 != "") {
		donorDQ << hlaDQ2;
	}

	QString hlaDR1 = dialog->donorHLADR1ComboBox->currentText();
	QString hlaDR2 = dialog->donorHLADR2ComboBox->currentText();
	if (hlaDR1 != "") {
		donorDR << hlaDR1;
	}
	if (hlaDR2 != hlaDR1 && hlaDR2 != "") {
		donorDR << hlaDR2;
	}

	donorBW4 = dialog->donorBW4CheckBox->isChecked();
	donorBW6 = dialog->donorBW6CheckBox->isChecked();
	donorDR51 = dialog->donorDR51CheckBox->isChecked();
	donorDR52 = dialog->donorDR52CheckBox->isChecked();
	donorDR53 = dialog->donorDR53CheckBox->isChecked();

	QString additionalHLA = dialog->donorHLALineEdit->text();
	additionalHLA.replace(" ", "");
	QStringList additionalHLAList = additionalHLA.split(";");

	foreach(QString antibody, additionalHLAList) {
		additionalDonorHLA << antibody;
	}

	donorFailureProbability = dialog->donorFailureProbabilitySpinBox->value();

	donorComment = dialog->commentTextEdit->toPlainText();

	emit donorEdited();

}

void KPDGUIDonor::updateVisualProperties() {

	prepareGeometryChange();
	update();
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
	out << qint32(KPDFunctions::raceToInt(donor.getRace()));
	out << donor.getHeight();
	out << donor.getWeight();
	out << donor.getCigarette();

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
	int race;
	double height;
	double weight;
	bool cigarette;
	
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

	in >> male >> race >> height >> weight >> cigarette;
	
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
	donor.setRace(KPDFunctions::intToRace(race));
	donor.setHeight(height);
	donor.setWeight(weight);
	donor.setCigarette(cigarette);

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