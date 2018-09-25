#include "KPDGUIMatch.h"
#include "KPDGUICandidate.h"

#include "KPDGUIDonor.h"

KPDGUIDonor::KPDGUIDonor(){
	
	matchingID = 0;
	donorNumber = 0;

	donorIsAltruistic = false;
	donorCompatibilityWithPairedCandidate = FAILED_CROSSMATCH_HLA;
	
	donorName = "Donor Name";
	donorAge = 40;
	donorBT = BT_O;
	
	donorBW4 = false;
	donorBW6 = false;
	donorDR51 = false;
	donorDR52 = false;
	donorDR53 = false;

	donorMale = false;
	donorRace = RACE_WHITE;
	donorHeight = 1.62;
	donorWeight = 76;
	donorCigarette = false;

	donorStatus = true;
	donorFailureProbability = 0.0;

	popularityInArrangements = 0;
	popularityInSolutions = 0;

	donorComment = "";

	hue = 80;

	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);	

	if (donorIsAltruistic) {
		setRect(QRectF(0, 0, 55, 50));
	}
	else {
		setRect(QRectF(0, 0, 45, 40));
	}

}

KPDGUIDonor::KPDGUIDonor(DialogDonor * d){

	matchingID = 0;
	donorNumber = 0;

	popularityInArrangements = 0;
	popularityInSolutions = 0;

	donorCompatibilityWithPairedCandidate = FAILED_CROSSMATCH_HLA;

	editDonor(d);

	hue = 80;

	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);

	if (donorIsAltruistic) {
		setRect(QRectF(0, 0, 55, 50));
	}
	else {
		setRect(QRectF(0, 0, 45, 40));
	}	
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

	if (HLA_LIST.split(",").contains(additionalHLA)) {

		if (additionalHLA == "BW4") {
			donorBW4 = true;
		}
		else if (additionalHLA == "BW6") {
			donorBW6 = true;
		}
		else if (additionalHLA == "DR51") {
			donorDR51 = true;
		}
		else if (additionalHLA == "DR52") {
			donorDR52 = true;
		}
		else if (additionalHLA == "DR53") {
			donorDR53 = true;
		}
		else if (additionalHLA.startsWith("A")) {
			donorA << additionalHLA;
		}
		else if (additionalHLA.startsWith("B")) {
			donorB << additionalHLA;
		}
		else if (additionalHLA.startsWith("CW")) {
			donorCW << additionalHLA;
		}
		else if (additionalHLA.startsWith("DQ")) {
			donorDQ << additionalHLA;
		}
		else if (additionalHLA.startsWith("DR")) {
			donorDR << additionalHLA;
		}
	}
	else {
		additionalDonorHLA << additionalHLA;
	}
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

KPDGUINode * KPDGUIDonor::getParentNode() const {
	return parentNode;
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

KPDCrossmatchResult KPDGUIDonor::getCompatibilityWithPairedCandidate() const{
	return donorCompatibilityWithPairedCandidate;
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

QVector<QString> KPDGUIDonor::getFullHLA() {

	QVector<QString> hlas;

	hlas << donorA;
	hlas << donorB;
	if (donorBW4) {
		hlas << "BW4";
	}
	if (donorBW6) {
		hlas << "BW6";
	}
	hlas << donorCW;
	hlas << donorDQ;
	hlas << donorDR;
	if (donorDR51) {
		hlas << "DR51";
	}
	if (donorDR52) {
		hlas << "DR52";
	}
	if (donorDR53) {
		hlas << "DR53";
	}
	hlas << additionalDonorHLA;

	return hlas;
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

	//double newHeight = (double)donorHeight * 0.0254;
	//double newWeight = (double)donorWeight * 0.4536;

	//return (newWeight / newHeight) / newHeight;

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
		setRect(QRectF(0, 0, 45, 40));
	}

	updateVisualProperties();
}

void KPDGUIDonor::setCompatibilityWithPairedCandidate(KPDCrossmatchResult result) {
	donorCompatibilityWithPairedCandidate = result;
	
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

void KPDGUIDonor::setDisplayMode(KPDDonorDisplayMode mode) {
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

	if (currentDisplayMode == DONOR_DISPLAY_ALL) {
		return getDonorPosition();
	}
	else if (currentDisplayMode == DONOR_DISPLAY_NONE) {
		return parentNode->getNodePosition();
	}
	else if (currentDisplayMode == DONOR_DISPLAY_MULTIPLE) {
		if (parentNode->getNumberOfDonors() > 1) {
			return getDonorPosition();
		}
		else {
			return parentNode->getNodePosition();
		}
	}
	else {
		return getDonorPosition();
	}
}

QPolygonF KPDGUIDonor::getRect() {

	if (currentDisplayMode == DONOR_DISPLAY_ALL) {
		return sceneBoundingRect();
	}
	else if (currentDisplayMode == DONOR_DISPLAY_NONE) {
		return parentNode->getRect();
	}
	else if (currentDisplayMode == DONOR_DISPLAY_MULTIPLE) {
		if (parentNode->getNumberOfDonors() > 1) {
			return sceneBoundingRect();
		}
		else {
			return parentNode->getRect();
		}
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

			if (donorCompatibilityWithPairedCandidate == SUCCESSFUL_CROSSMATCH) {

				myBackgroundColor = Qt::darkGreen;
			}
			else if (donorCompatibilityWithPairedCandidate == O_DONOR_TO_NON_O_CANDIDATE ||
				donorCompatibilityWithPairedCandidate == FAILED_CROSSMATCH_ADDITIONAL_HLA ||
				donorCompatibilityWithPairedCandidate == FAILED_CROSSMATCH_ADDITIONAL_HLA_AND_O_TO_NON_O) {

				myBackgroundColor = Qt::darkYellow;

			}
			else {
				myBackgroundColor = QColor(hue, hue, 255);
			}
		}
	}
	else {
		if (donorIsAltruistic) {
			myBackgroundColor = QColor(100,100,100);
		}
		else {
			myBackgroundColor = QColor(100,100,100);
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
		//pen.setStyle(Qt::DotLine);
		pen.setWidth(1.5);
	}

	painter->setPen(pen);
	painter->setBrush(QBrush(myBackgroundColor, Qt::SolidPattern));

	QRectF donorRect = boundingRect();
	painter->drawEllipse(donorRect);

	painter->setPen(QPen(Qt::white, 16, Qt::SolidLine, Qt::RoundCap));

	QFont * font = new QFont();
	font->setBold(true);
	font->setPointSize(11);
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
	QString compatibleDonorString = "Compatible Candidates: ";

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
		//emit donorSelectionChanged(matchingID, donorNumber, value.toBool());
		
		parentNode->setSelected(value.toBool());

		emit donorSelectionChanged();
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

	edit();
}

void KPDGUIDonor::edit() {	

	int r = QMessageBox::Yes;

	if (parentNode->getLoadedFromAPD()) {
		r = QMessageBox::warning(0, "Warning: APD Donor", "This donor was loaded from APD data. As there is no HLA information, editing the donor may lead to undesirable changes elsewhere in the pool. Do you wish to proceed?", QMessageBox::Yes | QMessageBox::No);
	}

	if (r == QMessageBox::Yes) {
		DialogDonor * donorDialog = new DialogDonor(this, false);

		if (donorDialog->exec()) {

			qDebug() << "This shouldn't display if hitting cancel";

			editDonor(donorDialog);

			parentNode->setLoadedFromAPD(false);
		}
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

	donorA.clear();
	QString hlaA1 = dialog->donorHLAA1ComboBox->currentText();
	QString hlaA2 = dialog->donorHLAA2ComboBox->currentText();
	if (hlaA1 != "") {
		donorA << hlaA1;
	}
	if (hlaA2 != hlaA1 && hlaA2 != "") {
		donorA << hlaA2;
	}

	donorB.clear();
	QString hlaB1 = dialog->donorHLAB1ComboBox->currentText();
	QString hlaB2 = dialog->donorHLAB2ComboBox->currentText();
	if (hlaB1 != "") {
		donorB << hlaB1;
	}
	if (hlaB2 != hlaB1 && hlaB2 != "") {
		donorB << hlaB2;
	}

	donorCW.clear();
	QString hlaCW1 = dialog->donorHLACW1ComboBox->currentText();
	QString hlaCW2 = dialog->donorHLACW2ComboBox->currentText();
	if (hlaCW1 != "") {
		donorCW << hlaCW1;
	}
	if (hlaCW2 != hlaCW1 && hlaCW2 != "") {
		donorCW << hlaCW2;
	}

	donorDQ.clear();
	QString hlaDQ1 = dialog->donorHLADQ1ComboBox->currentText();
	QString hlaDQ2 = dialog->donorHLADQ2ComboBox->currentText();
	if (hlaDQ1 != "") {
		donorDQ << hlaDQ1;
	}
	if (hlaDQ2 != hlaDQ1 && hlaDQ2 != "") {
		donorDQ << hlaDQ2;
	}

	donorDR.clear();
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

	additionalDonorHLA.clear();
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

void KPDGUIDonor::updateHue(int n, double mu, double sigma) {

	double pivot = (getNumberOfMatches() - mu) / (sigma / sqrt(n));

	if (pivot < -1.5) {
		pivot = -1.5;
	}

	if (pivot > 1.5) {
		pivot = 1.5;
	}

	//hue = 225 - 75 * (pivot + 1.5);

	hue = 0;

}

QDataStream &operator<<(QDataStream &out, const KPDGUIDonor & donor)
{	
	out << qint32(donor.getID());
	out << qint32(donor.getDonorNumber());
	out << donor.isAltruistic();
	out << qint32(KPDFunctions::crossmatchResultToInt(donor.getCompatibilityWithPairedCandidate()));
	
	//qDebug() << "out << qint32(donor.getID()): " << QString::number(donor.getID());
	//qDebug() << "out << qint32(donor.getDonorNumber()): " << QString::number(donor.getDonorNumber());
	//qDebug() << "out << donor.isAltruistic(): " << donor.isAltruistic();

	// Major Fields
	out << donor.getName();
	out << qint32(donor.getAge());
	out << qint32(KPDFunctions::bloodTypeToInt(donor.getBT()));

	//qDebug() << "out << donor.getName(): " << donor.getName();
	//qDebug() << "out << qint32(donor.getAge()): " << QString::number(donor.getAge());
	//qDebug() << "out << qint32(KPDFunctions::bloodTypeToInt(donor.getBT())): " << QString::number(KPDFunctions::bloodTypeToInt(donor.getBT()));

	// HLA Information
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

	// Characteristics
	out << donor.getMale();
	out << qint32(KPDFunctions::raceToInt(donor.getRace()));
	out << qreal(donor.getHeight());
	out << qreal(donor.getWeight());
	out << donor.getCigarette();

	//qDebug() << "out << donor.getMale(): " << donor.getMale();
	//qDebug() << "out << qint32(KPDFunctions::raceToInt(donor.getRace())): " << QString::number(KPDFunctions::raceToInt(donor.getRace()));
	//qDebug() << "out << qreal(donor.getHeight()): " << QString::number(donor.getHeight());
	//qDebug() << "out << qreal(donor.getWeight()): " << QString::number(donor.getWeight());
	//qDebug() << "out << donor.getCigarette(): " << QString::number(donor.getCigarette());

	// Additional Parameters
	out << donor.getStatus();
	out << qreal(donor.getFailureProbability());
		
	//qDebug() << "out << donor.getStatus(): " << donor.getStatus();
	//qDebug() << "out << qreal(donor.getFailureProbability()): " << QString::number(donor.getFailureProbability());

	out << donor.getComment();
	
	//qDebug() << "out << donor.getComment(): " << donor.getComment();

	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUIDonor & donor)
{
	int id;
	int donorNumber;
	bool ad;
	int crossmatch;
	in >> id >> donorNumber >> ad >> crossmatch;
	donor.setID(id);
	donor.setDonorNumber(donorNumber);
	donor.setAltruistic(ad);
	donor.setCompatibilityWithPairedCandidate(KPDFunctions::intToCrossmatchResult(crossmatch));	
	
	//qDebug() << "in >> id >> nDonors: " << QString::number(id) << QString::number(nDonors);

	// Major Fields
	QString name;
	int age;
	int BT;
	in >> name >> age >> BT;	
	donor.setName(name);
	donor.setAge(age);
	donor.setBT(KPDFunctions::intToBloodType(BT));

	//qDebug() << "in >> name >> age >> BT: " << name << QString::number(age) << QString::number(BT);

	// HLA Information
	QVector<QString> dA;
	QVector<QString> dB;
	QVector<QString> dCW;
	QVector<QString> dDQ;
	QVector<QString> dDR;
	bool dBW4;
	bool dBW6;
	bool dDR51;
	bool dDR52;
	bool dDR53;
	QVector<QString> dAdditionalHLA;
	in >> dA >> dB >> dCW >> dDQ >> dDR >> dBW4 >> dBW6 >> dDR51 >> dDR52 >> dDR53 >> dAdditionalHLA;
	donor.setA(dA);
	donor.setB(dB);
	donor.setCW(dCW);
	donor.setDQ(dDQ);
	donor.setDR(dDR);
	donor.setBW4(dBW4);
	donor.setBW6(dBW6);
	donor.setDR51(dDR51);
	donor.setDR52(dDR52);
	donor.setDR53(dDR52);
	donor.setAdditionalDonorHLA(dAdditionalHLA);

	// Characteristics
	bool male;
	int race;
	double height;
	double weight;
	bool cigarette;
	in >> male >> race >> height >> weight >> cigarette;
	donor.setMale(male);
	donor.setRace(KPDFunctions::intToRace(race));
	donor.setHeight(height);
	donor.setWeight(weight);
	donor.setCigarette(cigarette);
		
	//qDebug() << "in >> male >> race >> height >> weight >> cigarette: " << male << QString::number(race) << QString::number(height) << QString::number(weight) << cigarette;
	
	// Additional Parameters
	bool status;
	double prob;
	in >> status >> prob;
	donor.setStatus(status);
	donor.setFailureProbability(prob);

	//qDebug() << "in >> status >> prob: " << ad << status << QString::number(prob);
		
	QString comment;
	in >> comment;
	donor.setComment(comment);

	//qDebug() << "in >> comment: " << comment;
	
	return in;
}