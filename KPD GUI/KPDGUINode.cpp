#include "KPDGUINode.h"
#include "KPDGUIArrow.h"
#include "DialogPair.h"
#include "DialogAD.h"

KPDGUINode::KPDGUINode(){
	Donor d;
	d.type = KPDPairType::PAIR;
	
	d.name = "";
	d.age = -1;
	d.BT = "";

	d.BMI = 0.0;
	d.genderMale = false;
	d.weight = 0.0;

	d.donorA.push_back("");
	d.donorB.push_back("");
	d.donorCW.push_back("");
	d.donorDP.push_back("");
	d.donorDQ.push_back("");
	d.donorDR.push_back("");
	
	d.donorBW4 = false;
	d.donorBW6 = false;
	d.donorDR51 = false;
	d.donorDR52 = false;
	d.donorDR53 = false;
	
	Candidate c;
	c.name = "";
	c.age = -1;
	c.BT = "";
	c.pra = -1;

	c.BMI = 0.0;
	c.diabetes = false;
	c.genderMale = false;
	c.weight = 0.0;
	c.race = "";
	c.prevTrans = false;
	c.TOD = 0.0;
	c.hepC = false;
		
	c.antibodies.push_back("");

	donor = d;
	candidate = c;
	holdStatus = false;

	myTextColor = Qt::white;
	myOutlineColor = Qt::black;

	setZValue(0);
	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);

	popularityInStructures = 0;
	popularityInSolutions = 0;
}

KPDGUINode::KPDGUINode(Donor d, Candidate c, QString commentString, bool hold)
{
	//Set Node Properties
	donor = d;
	candidate = c;
	comment = commentString;
	holdStatus = hold;

	//Set Visual Properties
    myTextColor = Qt::white;
    myOutlineColor = Qt::black;	
	
	setBackgroundColor();
	setZValue(0);
	setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);

	//Reset Popularity
	popularityInStructures = 0;
	popularityInSolutions = 0;
}

KPDGUINode::~KPDGUINode()
{
	foreach(KPDGUIArrow *link, myInArrows)
		delete link;
	foreach(KPDGUIArrow *link, myOutArrows)
		delete link;
}

void KPDGUINode::setText(const QString &text)
{
    prepareGeometryChange();
    myText = text;
    update();
}

QString KPDGUINode::text() const
{
    return myText;
}

void KPDGUINode::setTextColor(const QColor &color)
{
    myTextColor = color;
    update();
}

QColor KPDGUINode::textColor() const
{
    return myTextColor;
}

void KPDGUINode::setOutlineColor(const QColor &color)
{
    myOutlineColor = color;
    update();
}

QColor KPDGUINode::outlineColor() const
{
    return myOutlineColor;
}

void KPDGUINode::setBackgroundColor()
{
	if (holdStatus){
		if (donor.type == PAIR){
			myBackgroundColor = QColor(100, 100, 100);
		}
		else {
			myBackgroundColor = QColor(100, 100, 125);
		}
	}
	else {
		if (donor.type == PAIR){
			myBackgroundColor = QColor(255, candidate.pra * 1.5, candidate.pra * 1.5);
		}
		else {
			myBackgroundColor = QColor(0, 0, 255);
		}
	}

    update();
}

QColor KPDGUINode::backgroundColor() const
{
    return myBackgroundColor;
}

QRectF KPDGUINode::boundingRect() const
{
	const int Margin = 1;
	return outlineRect().adjusted(-Margin, -Margin, +Margin, +Margin);
}

QPainterPath KPDGUINode::shape() const
{
	QRectF rect = outlineRect();

	QPainterPath path;
	path.addEllipse(rect);
	return path;
}

void KPDGUINode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */)
{
	QPen pen(myOutlineColor);
	if (option->state & QStyle::State_Selected) {
		pen.setStyle(Qt::DotLine);
		pen.setWidth(2);
	}
	painter->setPen(pen);
	painter->setBrush(QBrush(myBackgroundColor, Qt::SolidPattern));

	QRectF rect = outlineRect();
	painter->drawEllipse(rect);
	painter->setPen(QPen(myTextColor, 16, Qt::SolidLine, Qt::RoundCap));

	QFont * font = new QFont();
	font->setBold(true);
	font->setPointSize(8);
	painter->setFont(*font);

	painter->drawText(rect, Qt::AlignCenter, myText);
}

void KPDGUINode::addInArrow(KPDGUIArrow *link)
{
	myInArrows.insert(link);
}

void KPDGUINode::removeInArrow(KPDGUIArrow *link)
{
	myInArrows.remove(link);
}

void KPDGUINode::addOutArrow(KPDGUIArrow *link)
{
	myOutArrows.insert(link);
}

void KPDGUINode::removeOutArrow(KPDGUIArrow *link)
{
	myOutArrows.remove(link);
}

KPDGUIArrow * KPDGUINode::findOutArrow(KPDGUINode * toNode){
	foreach(KPDGUIArrow * arrow, myOutArrows){
		if (arrow->endItem() == toNode){
			return arrow;
		}
	}

	return NULL;
}

void KPDGUINode::setEnhancedHighlight(int secondID){
	foreach(KPDGUIArrow * arrow, myOutArrows){
		if (arrow->endItem()->getInternalID() == secondID){
			arrow->setVisible(true);
			arrow->highlightConnection();
		}
	}
}

bool KPDGUINode::hasNoCompatibilities(){
	if (myInArrows.count() + myOutArrows.count() == 0){
		return true;
	}
	return false;
}

bool KPDGUINode::hasNoAvailableCompatibilities(){
	foreach(KPDGUIArrow * arrow, myInArrows){
		if (!arrow->startItem()->isOnHold()){
			return false;
		}
	}
	foreach(KPDGUIArrow * arrow, myOutArrows){
		if (!arrow->endItem()->isOnHold()){
			return false;
		}
	}

	return true;
}

int KPDGUINode::getNumberOfCompatibilities(){
	return myInArrows.count() + myOutArrows.count();
}

int KPDGUINode::getNumberOfCompatibleDonors(){
	return myInArrows.count();
}

int KPDGUINode::getNumberOfCompatibleRecipients(){
	return myOutArrows.count();
}

int KPDGUINode::getPopularityInStructures(){
	return popularityInStructures;
}

int KPDGUINode::getPopularityInSolutions(){
	return popularityInSolutions;
}

void KPDGUINode::increasePopularityInStructures(){
	popularityInStructures++;
}

void KPDGUINode::increasePopularityInSolutions(){
	popularityInSolutions++;
}

void KPDGUINode::decreasePopularityInStructures(){
	popularityInStructures--;
}

void KPDGUINode::decreasePopularityInSolutions(){
	popularityInSolutions--;
}

void KPDGUINode::resetPopularityInStructures(){
	popularityInStructures = 0;
}

void KPDGUINode::resetPopularityInSolutions(){
	popularityInSolutions = 0;
}

bool KPDGUINode::getHoldStatus() const{
	return holdStatus;
}

void KPDGUINode::setHoldStatus(bool hold){
	holdStatus = hold;
	setBackgroundColor();

	emit nodeHoldStatusChanged(internalID, holdStatus);
}

bool KPDGUINode::isOnHold(){
	return holdStatus;
}

int KPDGUINode::getInternalID() const{
	return internalID;
}

void KPDGUINode::setInternalID(int id){
	internalID = id;
}

void KPDGUINode::setDonor(Donor d){
	
	donor.type = d.type;

	donor.name = d.name;
	donor.age = d.age;
	donor.BT = d.BT;

	donor.BMI = d.BMI;
	donor.genderMale = d.genderMale;
	donor.weight = d.weight;

	donor.donorA.clear();
	foreach(QString a, d.donorA){
		donor.donorA.push_back(a);
	}
	donor.donorB.clear();
	foreach(QString b, d.donorB){
		donor.donorB.push_back(b);
	}
	donor.donorCW.clear();
	foreach(QString cw, d.donorCW){
		donor.donorCW.push_back(cw);
	}
	donor.donorDP.clear();
	foreach(QString dp, d.donorDP){
		donor.donorDP.push_back(dp);
	}
	donor.donorDQ.clear();
	foreach(QString dq, d.donorDQ){
		donor.donorDQ.push_back(dq);
	}
	donor.donorDR.clear();
	foreach(QString dr, d.donorDR){
		donor.donorDR.push_back(dr);
	}
	donor.donorBW4 = d.donorBW4;
	donor.donorBW6 = d.donorBW6;
	donor.donorDR51 = d.donorDR51;
	donor.donorDR52 = d.donorDR52;
	donor.donorDR53 = d.donorDR53;

}

void KPDGUINode::setCandidate(Candidate c){
	candidate = c;

	candidate.name = c.name;
	candidate.age = c.age;
	candidate.BT = c.BT;
	candidate.pra = c.pra;
	
	candidate.BMI = c.BMI;
	candidate.diabetes = c.diabetes;
	candidate.genderMale = c.genderMale;
	candidate.weight = c.weight;
	candidate.race = c.race;
	candidate.prevTrans = c.prevTrans;
	candidate.TOD = c.TOD;
	candidate.hepC = c.hepC;
	
	candidate.antibodies.clear();
	foreach(QString antibody, c.antibodies){
		candidate.antibodies.push_back(antibody);
	}
}

KPDPairType KPDGUINode::getType() const{
	return donor.type;
}

QString KPDGUINode::getDonorName() const {
	return donor.name;
}

QString KPDGUINode::getRecipName() const {
	return candidate.name;
}

int KPDGUINode::getDonorAge() const {
	return donor.age;
}

int KPDGUINode::getRecipAge() const {
	return candidate.age;
}

QString KPDGUINode::getDonorBT() const {
	return donor.BT;
}

QString KPDGUINode::getRecipBT() const {
	return candidate.BT;
}

int KPDGUINode::getRecipPRA() const {
	return candidate.pra;
}

double KPDGUINode::getRecipBMI() const{
	return candidate.BMI;
}

bool KPDGUINode::getRecipDiabetes() const{
	return candidate.diabetes; 
}

bool KPDGUINode::getRecipGenderMale() const{
	return candidate.genderMale; 
}

double KPDGUINode::getRecipWeight() const{
	return candidate.weight;
}

QString KPDGUINode::getRecipRace() const{
	return candidate.race;
}

bool KPDGUINode::getRecipPrevTrans() const{
	return candidate.prevTrans;
}

double KPDGUINode::getRecipTOD() const{
	return candidate.TOD;
}

bool KPDGUINode::getRecipHepC() const{
	return candidate.hepC;
}

double KPDGUINode::getDonorBMI() const{
	return donor.BMI;
}

bool KPDGUINode::getDonorGenderMale() const{
	return donor.genderMale;
}

double KPDGUINode::getDonorWeight() const{
	return donor.weight;
}

void KPDGUINode::setDonorName(QString name){
	donor.name = name;
	emit nodeEdited(internalID);
}

void KPDGUINode::setRecipName(QString name){
	candidate.name = name;
	emit nodeEdited(internalID);
}

void KPDGUINode::setDonorAge(int age){
	donor.age = age;
	emit nodeEdited(internalID);
}

void KPDGUINode::setRecipAge(int age){
	candidate.age = age;
	emit nodeEdited(internalID);
}

void KPDGUINode::setDonorBT(QString bt){
	donor.BT = bt;
	emit nodeEdited(internalID);
}

void KPDGUINode::setRecipBT(QString bt){
	candidate.BT = bt;
	emit nodeEdited(internalID);
}

void KPDGUINode::setRecipPRA(int age){
	candidate.age = age;
	emit nodeEdited(internalID);
}

void KPDGUINode::setRecipBMI(double bmi){
	candidate.BMI = bmi;
	emit nodeEdited(internalID);
}

void KPDGUINode::setRecipDiabetes(bool diabetes){
	candidate.diabetes = diabetes;
	emit nodeEdited(internalID);
}

void KPDGUINode::setRecipGenderMale(bool genderMale){
	candidate.genderMale = genderMale;
	emit nodeEdited(internalID);
}

void KPDGUINode::setRecipWeight(double weight){ 
	candidate.weight = weight;
	emit nodeEdited(internalID);
}

void KPDGUINode::setRecipRace(QString race){ 
	candidate.race = race;
	emit nodeEdited(internalID);
}

void KPDGUINode::setRecipPrevTrans(bool prevTrans){ 
	candidate.prevTrans = prevTrans;
	emit nodeEdited(internalID);
}

void KPDGUINode::setRecipTOD(double tod){ 
	candidate.TOD = tod;
	emit nodeEdited(internalID);
}

void KPDGUINode::setRecipHepC(bool hepC){ 
	candidate.hepC = hepC;
	emit nodeEdited(internalID);
}

void KPDGUINode::setDonorBMI(double bmi){ 
	donor.BMI = bmi;
	emit nodeEdited(internalID);
}

void KPDGUINode::setDonorGenderMale(bool genderMale){ 
	donor.genderMale = genderMale;
	emit nodeEdited(internalID);
}

void KPDGUINode::setDonorWeight(double weight){ 
	donor.weight = weight;
	emit nodeEdited(internalID);
}

QVector<QString> KPDGUINode::getDonorAVector() const {
	return donor.donorA;
}

QVector<QString> KPDGUINode::getDonorBVector() const {
	return donor.donorB;
}

QVector<QString> KPDGUINode::getDonorCWVector() const {
	return donor.donorCW;
}

QVector<QString> KPDGUINode::getDonorDPVector() const {
	return donor.donorDP;
}

QVector<QString> KPDGUINode::getDonorDQVector() const {
	return donor.donorDQ;
}

QVector<QString> KPDGUINode::getDonorDRVector() const {
	return donor.donorDR;
}

bool KPDGUINode::getDonorBW4() const{
	return donor.donorBW4;
}

bool KPDGUINode::getDonorBW6() const{
	return donor.donorBW6;
}

bool KPDGUINode::getDonorDR51() const{
	return donor.donorDR51;
}

bool KPDGUINode::getDonorDR52() const{
	return donor.donorDR52;
}

bool KPDGUINode::getDonorDR53() const{
	return donor.donorDR53;
}

QVector<QString> KPDGUINode::getRecipAntibodies() const{
	return candidate.antibodies;
}

QString KPDGUINode::getDonorHLAString(){
	QString hlaString = "";
	foreach(QString donorA, donor.donorA){
		if (!donorA.isEmpty()){
			hlaString += donorA;
			hlaString += ";";
		}
	}
	foreach(QString donorB, donor.donorB){
		if (!donorB.isEmpty()){
			hlaString += donorB;
			hlaString += ";";
		}
	}
	if (donor.donorBW4 == true){
		hlaString += "BW4";
		hlaString += ";";
	}
	if (donor.donorBW6 == true){
		hlaString += "BW6";
		hlaString += ";";
	}
	foreach(QString donorCW, donor.donorCW){
		if (!donorCW.isEmpty()){
			hlaString += donorCW;
			hlaString += ";";
		}
	}
	foreach(QString donorDP, donor.donorDP){
		if (!donorDP.isEmpty()){
			hlaString += donorDP;
			hlaString += ";";
		}
	}
	foreach(QString donorDQ, donor.donorDQ){
		if (!donorDQ.isEmpty()){
			hlaString += donorDQ;
			hlaString += ";";
		}
	}
	foreach(QString donorDR, donor.donorDR){
		if (!donorDR.isEmpty()){
			hlaString += donorDR;
			hlaString += ";";
		}
	}
	if (donor.donorDR51 == true){
		hlaString += "DR51";
		hlaString += ";";
	}
	if (donor.donorDR52 == true){
		hlaString += "DR52";
		hlaString += ";";
	}
	if (donor.donorDR53 == true){
		hlaString += "DR53";
		hlaString += ";";
	}
	
	hlaString.chop(1);

	return hlaString;
}

QString KPDGUINode::getRecipHLAString(){
	QString hlaString = "";
	foreach(QString antibody, candidate.antibodies){
		hlaString += antibody;
		hlaString += ";";
	}

	hlaString.chop(1);

	return hlaString;
}

Candidate * KPDGUINode::getCandidatePtr(){
	return &candidate;
}

Donor * KPDGUINode::getDonorPtr(){
	return &donor;
}

QString KPDGUINode::getComment() const{
	return comment;
}

void KPDGUINode::setComment(QString commentString){
	comment = commentString;
}

QString KPDGUINode::getCompatibleDonorString(){
	QString compatibleDonorString = "Compatible Donors: ";

	if (myInArrows.count() > 0){
		QVector<int> compatibleDonors;
		foreach(KPDGUIArrow * arrow, myInArrows){
			compatibleDonors.push_back(arrow->startItem()->getInternalID());
		}
		qSort(compatibleDonors);
		foreach(int id, compatibleDonors){
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

QString KPDGUINode::getCompatibleRecipientsString(){
	QString compatibleRecipientString = "Compatible Recipients: ";

	if (myOutArrows.count() > 0){
		QVector<int> compatibleRecipients;
		foreach(KPDGUIArrow * arrow, myOutArrows){
			compatibleRecipients.push_back(arrow->endItem()->getInternalID());
		}
		qSort(compatibleRecipients);
		foreach(int id, compatibleRecipients){
			compatibleRecipientString += QString::number(id);
			compatibleRecipientString += ", ";
		}
		compatibleRecipientString.chop(2);
	}
	else {
		compatibleRecipientString += "None";
	}

	return compatibleRecipientString;
}

QString KPDGUINode::getConsoleString(){
	QString consoleString = "";
	
	if (donor.type == PAIR){
		consoleString += "Pair ";
	}
	else {
		consoleString += "AD ";
	}
	consoleString += QString::number(getInternalID());
	
	if (isOnHold()){
		consoleString += "(ON HOLD)";
	}

	consoleString += "\nDonor: ";
	consoleString += getDonorName();
	consoleString += " (";
	consoleString += getDonorBT();
	consoleString += ")";
	if (donor.type == PAIR){
		consoleString += ", Candidate: ";
		consoleString += getRecipName();
		consoleString += " (";
		consoleString += getRecipBT();
		consoleString += ")";
	}
	consoleString += "\n\nDonor HLA : ";

	QString donorHLAString = getDonorHLAString();
	donorHLAString.replace(";", " ");
	if (donorHLAString.size() > 0){
		consoleString += donorHLAString;
	}
	else {
		consoleString += "None";
	}

	if (donor.type == PAIR){
		consoleString += "\nCandidate HLA: ";

		QString recipHLAString = getRecipHLAString();
		recipHLAString.replace(";", " ");
		if (recipHLAString.size() > 0){
			consoleString += recipHLAString;
		}
		else {
			consoleString += "None";
		}
	}

	consoleString += "\n";
	if (donor.type == PAIR){
		consoleString += "\n";
		consoleString += getCompatibleDonorString();
		consoleString += "\n";
	}
	consoleString += getCompatibleRecipientsString();
	consoleString += "\n";
		
	if (comment.size() > 0){
		consoleString += "\n";
		consoleString += "Additional Comments: ";
		consoleString += comment;
	}

	return consoleString;
}

QVariant KPDGUINode::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == ItemPositionHasChanged) {
		foreach(KPDGUIArrow *link, myInArrows)
			link->updatePosition();
		foreach(KPDGUIArrow *link, myOutArrows)
			link->updatePosition();
	}

	if (change == ItemSelectedHasChanged) {
		emit nodeSelectionChanged(internalID, value.toBool());
	}

	return QGraphicsItem::itemChange(change, value);
}

void KPDGUINode::mousePressEvent(QGraphicsSceneMouseEvent *event){

	setSelected(true);
	
	emit nodeWasClicked(internalID,isSelected());
}

void KPDGUINode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event){
	if (donor.type == AD){
		AltruisticDonorDialog adDialog(getInternalID(), getDonorPtr(), getComment(), true, 0);
		if (adDialog.exec()){
			bool majorChange = false;
			if (donor.BT != adDialog.donorBTComboBox->currentText()){
				majorChange = true;
			}
			if (donor.donorA.size() > 0){
				if (donor.donorA[0] != adDialog.donorA1LineEdit->text()){  
					majorChange = true; 
				}
				if (donor.donorA.size() > 1){
					if (donor.donorA[1] != adDialog.donorA2LineEdit->text()){ 
						majorChange = true; 
					}
				}
			}

			if (donor.donorB.size() > 0){
				if (donor.donorB[0] != adDialog.donorB1lineEdit->text()){ 
					majorChange = true; 
				}
				if (donor.donorB.size() > 1){
					if (donor.donorB[1] != adDialog.donorB2LineEdit->text()){
						majorChange = true; 
					}
				}
			}

			if (donor.donorCW.size() > 0){
				if (donor.donorCW[0] != adDialog.donorCW1LineEdit->text()){
					majorChange = true; 
				}
				if (donor.donorCW.size() > 1){
					if (donor.donorCW[1] != adDialog.donorCW2LineEdit->text()){ 
						majorChange = true; 
					}
				}
			}

			if (donor.donorDP.size() > 0){
				if (donor.donorDP[0] != adDialog.donorDP1LineEdit->text()){ 
					majorChange = true; 
				}
				if (donor.donorDP.size() > 1){
					if (donor.donorDP[1] != adDialog.donorDP2LineEdit->text()){ 
						majorChange = true; 
					}
				}
			}

			if (donor.donorDQ.size() > 0){
				if (donor.donorDQ[0] != adDialog.donorDQ1LineEdit->text()){ 
					majorChange = true; 
				}
				if (donor.donorDQ.size() > 1){
					if (donor.donorDQ[1] != adDialog.donorDQ2LineEdit->text()){ 
						majorChange = true; 
					}
				}
			}

			if (donor.donorDR.size() > 0){
				if (donor.donorDR[0] != adDialog.donorDR1LineEdit->text()){ 
					majorChange = true; 
				}
				if (donor.donorDR.size() > 1){
					if (donor.donorDR[1] != adDialog.donorDR2LineEdit->text()){ 
						majorChange = true; 
					}
				}
			}

			if (donor.donorBW4 != adDialog.donorBW4CheckBox->isChecked()){
				majorChange = true;				
			}
			if (donor.donorBW6 != adDialog.donorBW6CheckBox->isChecked()){
				majorChange = true;
			}
			if (donor.donorDR51 != adDialog.donorDR51CheckBox->isChecked()){
				majorChange = true;
			}
			if (donor.donorDR52 != adDialog.donorDR52CheckBox->isChecked()){
				majorChange = true;
			}
			if (donor.donorDR53 != adDialog.donorDR53CheckBox->isChecked()){
				majorChange = true;
			}

			if (majorChange){
				int r = QMessageBox::warning(0, tr("KPD"),
					tr("Major changes to nodes will result in their removal from previous solutions. Are you sure you want to submit these changes?"),
					QMessageBox::Yes | QMessageBox::No);
				if (r == QMessageBox::Yes) {
					Donor d;

					d.name = adDialog.donorNameLineEdit->text();
					d.age = adDialog.donorAgeSpinBox->value();
					d.BT = adDialog.donorBTComboBox->currentText();

					double donorHeight = adDialog.donorHeightSpinBox->value();
					double donorWeight = adDialog.donorWeightSpinBox->value();
					d.BMI =  donorWeight / donorHeight / donorHeight;
					d.weight = donorWeight;
					QString donorGender = adDialog.donorGenderComboBox->currentText();
					if (donorGender == "Male"){ d.genderMale = true; }
					else { d.genderMale = false; }
					
					d.donorA.push_back(adDialog.donorA1LineEdit->text());
					d.donorA.push_back(adDialog.donorA2LineEdit->text());
					d.donorB.push_back(adDialog.donorB1lineEdit->text());
					d.donorB.push_back(adDialog.donorB2LineEdit->text());
					d.donorCW.push_back(adDialog.donorCW1LineEdit->text());
					d.donorCW.push_back(adDialog.donorCW2LineEdit->text());
					d.donorDP.push_back(adDialog.donorDP1LineEdit->text());
					d.donorDP.push_back(adDialog.donorDP2LineEdit->text());
					d.donorDQ.push_back(adDialog.donorDQ1LineEdit->text());
					d.donorDQ.push_back(adDialog.donorDQ2LineEdit->text());
					d.donorDR.push_back(adDialog.donorDR1LineEdit->text());
					d.donorDR.push_back(adDialog.donorDR2LineEdit->text());
					d.donorBW4 = adDialog.donorBW4CheckBox->isChecked();
					d.donorBW6 = adDialog.donorBW6CheckBox->isChecked();
					d.donorDR51 = adDialog.donorDR51CheckBox->isChecked();
					d.donorDR52 = adDialog.donorDR52CheckBox->isChecked();
					d.donorDR53 = adDialog.donorDR53CheckBox->isChecked();
					
					d.type = KPDPairType::AD;

					QString comment = adDialog.commentTextEdit->toPlainText();
				}
			}
			else {
				setDonorName(adDialog.donorNameLineEdit->text());
				setDonorAge(adDialog.donorAgeSpinBox->value());
				double donorHeight = adDialog.donorHeightSpinBox->value();
				double donorWeight = adDialog.donorWeightSpinBox->value();
				setDonorBMI( donorWeight / donorHeight / donorHeight);
				setDonorWeight(donorWeight);
				QString donorGender = adDialog.donorGenderComboBox->currentText();
				if (getDonorGenderMale() == true && donorGender != "Male"){
					setDonorGenderMale(false);
				}
				else if (getDonorGenderMale() == false && donorGender != "Female"){
					setDonorGenderMale(true);
				}

				setComment(adDialog.commentTextEdit->toPlainText());
			}
		}
	}
	else {
		PairDialog pairDialog(getInternalID(), getDonorPtr(), getCandidatePtr(), getComment(), true, 0);
		if (pairDialog.exec()){
			bool majorChange = false;

			if (donor.BT != pairDialog.donorBTComboBox->currentText()){
				majorChange = true;
			}
			if (candidate.BT != pairDialog.recipBTComboBox->currentText()){
				majorChange = true;
			}
			if (candidate.pra != pairDialog.recipPRASpinBox->value()){
				majorChange = true;
			}
			QString antibodies = pairDialog.recipHLALineEdit->text();
			if (getRecipHLAString() != antibodies){
				majorChange = true;
			}

			if (donor.donorA.size() > 0){
				if (donor.donorA[0] != pairDialog.donorA1LineEdit->text()){ 
					majorChange = true; 
				}
				if (donor.donorA.size() > 1){
					if (donor.donorA[1] != pairDialog.donorA2LineEdit->text()){ 
						majorChange = true; 
					}
				}
			}

			if (donor.donorB.size() > 0){
				if (donor.donorB[0] != pairDialog.donorB1lineEdit->text()){ 
					majorChange = true; 
				}
				if (donor.donorB.size() > 1){
					if (donor.donorB[1] != pairDialog.donorB2LineEdit->text()){ 
						majorChange = true; 
					}
				}
			}

			if (donor.donorCW.size() > 0){
				if (donor.donorCW[0] != pairDialog.donorCW1LineEdit->text()){  
					majorChange = true; 
				}
				if (donor.donorCW.size() > 1){
					if (donor.donorCW[1] != pairDialog.donorCW2LineEdit->text()){ 
						majorChange = true; 
					}
				}
			}

			if (donor.donorDP.size() > 0){
				if (donor.donorDP[0] != pairDialog.donorDP1LineEdit->text()){  
					majorChange = true; 
				}
				if (donor.donorDP.size() > 1){
					if (donor.donorDP[1] != pairDialog.donorDP2LineEdit->text()){  
						majorChange = true; 
					}
				}
			}

			if (donor.donorDQ.size() > 0){
				if (donor.donorDQ[0] != pairDialog.donorDQ1LineEdit->text()){  
					majorChange = true; 
				}
				if (donor.donorDQ.size() > 1){
					if (donor.donorDQ[1] != pairDialog.donorDQ2LineEdit->text()){ 
						majorChange = true; 
					}
				}
			}

			if (donor.donorDR.size() > 0){
				if (donor.donorDR[0] != pairDialog.donorDR1LineEdit->text()){  
					majorChange = true; 
				}
				if (donor.donorDR.size() > 1){
					if (donor.donorDR[1] != pairDialog.donorDR2LineEdit->text()){ 
						majorChange = true; 
					}
				}
			}

			if (donor.donorBW4 != pairDialog.donorBW4CheckBox->isChecked()){
				majorChange = true;
			}
			if (donor.donorBW6 != pairDialog.donorBW6CheckBox->isChecked()){
				majorChange = true;
			}
			if (donor.donorDR51 != pairDialog.donorDR51CheckBox->isChecked()){
				majorChange = true;
			}
			if (donor.donorDR52 != pairDialog.donorDR52CheckBox->isChecked()){
				majorChange = true;
			}
			if (donor.donorDR53 != pairDialog.donorDR53CheckBox->isChecked()){
				majorChange = true;
			}

			if (majorChange){
				int r = QMessageBox::warning(0, tr("KPD"),
					tr("Major changes to pairs will result in their removal from previous solutions. Are you sure you want to submit these changes?"),
					QMessageBox::Yes | QMessageBox::No);
				if (r == QMessageBox::Yes) {
					Donor d;
					Candidate c;

					d.name = pairDialog.donorNameLineEdit->text();
					c.name = pairDialog.recipNameLineEdit->text();
					d.age = pairDialog.donorAgeSpinBox->value();
					c.age = pairDialog.recipAgeSpinBox->value();
					d.BT = pairDialog.donorBTComboBox->currentText();
					c.BT = pairDialog.recipBTComboBox->currentText();
					c.pra = pairDialog.recipPRASpinBox->value();

					double recipHeight = pairDialog.recipHeightSpinBox->value();
					double recipWeight = pairDialog.recipWeightSpinBox->value();
					c.BMI = recipWeight / recipHeight / recipHeight;
					c.weight = recipWeight;
					c.diabetes = pairDialog.recipDiabetesCheckBox->isChecked();
					QString recipGender = pairDialog.recipGenderComboBox->currentText();
					if (recipGender == "Male"){ c.genderMale = true; }
					else { c.genderMale = false; }
					c.race = pairDialog.recipRaceComboBox->currentText();
					c.prevTrans = pairDialog.recipPrevTransCheckBox->isChecked();
					c.TOD = pairDialog.recipTODSpinBox->value();
					c.hepC = pairDialog.recipHepCCheckBox->isChecked();

					double donorHeight = pairDialog.donorHeightSpinBox->value();
					double donorWeight = pairDialog.donorWeightSpinBox->value();
					d.BMI =  donorWeight / donorHeight / donorHeight;
					d.weight = donorWeight;
					QString donorGender = pairDialog.donorGenderComboBox->currentText();
					if (donorGender == "Male"){ d.genderMale = true; }
					else { d.genderMale = false; }


					QString antibodies = pairDialog.recipHLALineEdit->text();
					QStringList antibodyList = antibodies.split(";");

					foreach(QString antibody, antibodyList){
						c.antibodies.push_back(antibody);
					}

					d.donorA.push_back(pairDialog.donorA1LineEdit->text());
					d.donorA.push_back(pairDialog.donorA2LineEdit->text());
					d.donorB.push_back(pairDialog.donorB1lineEdit->text());
					d.donorB.push_back(pairDialog.donorB2LineEdit->text());
					d.donorCW.push_back(pairDialog.donorCW1LineEdit->text());
					d.donorCW.push_back(pairDialog.donorCW2LineEdit->text());
					d.donorDP.push_back(pairDialog.donorDP1LineEdit->text());
					d.donorDP.push_back(pairDialog.donorDP2LineEdit->text());
					d.donorDQ.push_back(pairDialog.donorDQ1LineEdit->text());
					d.donorDQ.push_back(pairDialog.donorDQ2LineEdit->text());
					d.donorDR.push_back(pairDialog.donorDR1LineEdit->text());
					d.donorDR.push_back(pairDialog.donorDR2LineEdit->text());
					d.donorBW4 = pairDialog.donorBW4CheckBox->isChecked();
					d.donorBW6 = pairDialog.donorBW6CheckBox->isChecked();
					d.donorDR51 = pairDialog.donorDR51CheckBox->isChecked();
					d.donorDR52 = pairDialog.donorDR52CheckBox->isChecked();
					d.donorDR53 = pairDialog.donorDR53CheckBox->isChecked();
					
					d.type = KPDPairType::PAIR;

					QString comment = pairDialog.commentTextEdit->toPlainText();
				}
			}
			else {
				setDonorName(pairDialog.donorNameLineEdit->text());
				setRecipName(pairDialog.recipNameLineEdit->text());
				setDonorAge(pairDialog.donorAgeSpinBox->value());
				setRecipAge(pairDialog.recipAgeSpinBox->value());
				double recipHeight = pairDialog.recipHeightSpinBox->value();
				double recipWeight = pairDialog.recipWeightSpinBox->value();
				setRecipBMI( recipWeight / recipHeight / recipHeight);
				setRecipWeight(recipWeight);
				setRecipDiabetes(pairDialog.recipDiabetesCheckBox->isChecked());
				QString recipGender(pairDialog.recipGenderComboBox->currentText());
				if (getRecipGenderMale() == true && recipGender != "Male"){
					setRecipGenderMale(false);
				}
				else if (getRecipGenderMale() == false && recipGender != "Female"){
					setRecipGenderMale(true);
				}
				setRecipRace(pairDialog.recipRaceComboBox->currentText());
				setRecipPrevTrans(pairDialog.recipPrevTransCheckBox->isChecked());
				setRecipTOD(pairDialog.recipTODSpinBox->value());
				setRecipHepC(pairDialog.recipHepCCheckBox->isChecked());
				double donorHeight = pairDialog.donorHeightSpinBox->value();
				double donorWeight = pairDialog.donorWeightSpinBox->value();
				setDonorBMI( donorWeight / donorHeight / donorHeight);
				setDonorWeight(donorWeight);
				QString donorGender = pairDialog.donorGenderComboBox->currentText();
				if (getDonorGenderMale() == true && donorGender != "Male"){
					setDonorGenderMale(false);
				}
				else if (getDonorGenderMale() == false && donorGender != "Female"){
					setDonorGenderMale(true);
				}

				setComment(pairDialog.commentTextEdit->toPlainText());
			}
		}
	}

	QGraphicsObject::mouseDoubleClickEvent(event);
}

QRectF KPDGUINode::outlineRect() const
{
	qreal x1; qreal x2; qreal y1; qreal y2;

	int Padding = 12;
	QFont * font = new QFont();
	font->setBold(true);
	font->setPointSize(8);
	QFontMetricsF * metrics = new QFontMetricsF(*font);
	QRectF rect = metrics->boundingRect(myText);
	rect.getCoords(&x1, &y1, &x2, &y2);
	rect.adjust(-(2.5*Padding - x1), -(Padding - y1), (2.5*Padding - x2), (Padding - y2));
	rect.translate(-rect.center());
	return rect;
}

bool KPDGUINode::checkWithinBounds(bool pairsOfMinPRA, int minPRA, bool pairsOfMaxPRA, int maxPRA){
	if (donor.type == AD){
		return true;
	}
	else {
		if (pairsOfMinPRA){
			if (minPRA > candidate.pra){
				return false;
			}
		}

		if (pairsOfMaxPRA){
			if (maxPRA < candidate.pra){
				return false;
			}
		}

		return true;
	}
}

void KPDGUINode::updateVisibility(DisplaySettingsStruct * displaySettings){
	if (displaySettings->showPairsInStructures){
		if (getPopularityInStructures() == 0){
			setVisible(false);
			setSelected(false);
		}
	}
	else if (displaySettings->showPairsInSolutions){
		if (getPopularityInSolutions() == 0){
			setVisible(false);
			setSelected(false);
		}
	}

	else if (displaySettings->showPairSubset){

		bool withinBounds = checkWithinBounds(displaySettings->showPairsOfMinPRA, displaySettings->minPRA, displaySettings->showPairsOfMaxPRA, displaySettings->maxPRA);
		
		if (!withinBounds){
			setVisible(false);
			setSelected(false);
		}
		else if (!displaySettings->showPairsWithNoCompatibilities && hasNoCompatibilities()){
			setVisible(false);
			setSelected(false);
		}
		else if (!displaySettings->showPairsOnHold && isOnHold()){
			setVisible(false);
			setSelected(false);
		}
		else {
			setVisible(true);
		}
	}
	else {
		setVisible(true);
	}
}

QDataStream &operator<<(QDataStream &out, const KPDGUINode & node)
{
	out << qint32(node.getInternalID());
	out << KPDFunctions::toString(node.getType());

	out << node.getDonorName();
	out << qint32(node.getDonorAge());
	out << node.getDonorBT();

	//qDebug() << qreal(node.getDonorBMI());
	//qDebug() << node.getDonorGenderMale();
	//qDebug() << qreal(node.getDonorWeight());

	out << node.getDonorBMI();
	out << node.getDonorGenderMale();
	out << node.getDonorWeight();


	out << node.getDonorAVector();
	out << node.getDonorBVector();
	out << node.getDonorCWVector();
	out << node.getDonorDPVector();
	out << node.getDonorDQVector();
	out << node.getDonorDRVector();
	out << node.getDonorBW4();
	out << node.getDonorBW6();
	out << node.getDonorDR51();
	out << node.getDonorDR52();
	out << node.getDonorDR53();

	if (node.getType() == PAIR){
		out << node.getRecipName();
		out << qint32(node.getRecipAge());
		out << node.getRecipBT();
		out << qint32(node.getRecipPRA());
		
		out << node.getRecipBMI();
		out << node.getRecipDiabetes();
		out << node.getRecipGenderMale();
		out << node.getRecipWeight();
		out << node.getRecipRace();
		out << node.getRecipPrevTrans();
		out << node.getRecipTOD();
		out << node.getRecipHepC();
		
		out << node.getRecipAntibodies();
	}

	out << node.getHoldStatus();
	out << node.getComment();
	
	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUINode & node)
{
	int internalID;
	in >> internalID;

	Donor d;
	QString type;
	in >> type;
	KPDPairType pairType = KPDFunctions::stringToPairType(type);
	d.type = pairType;
	
	in >> d.name;
	in >> d.age;
	in >> d.BT;

	in >> d.BMI;
	in >> d.genderMale;
	in >> d.weight;

	//qDebug() << d.BMI;
	//qDebug() << d.genderMale;
	//qDebug() << d.weight;

	in >> d.donorA;
	in >> d.donorB;
	in >> d.donorCW;
	in >> d.donorDP;
	in >> d.donorDQ;
	in >> d.donorDR;
	in >> d.donorBW4;
	in >> d.donorBW6;
	in >> d.donorDR51;
	in >> d.donorDR52;
	in >> d.donorDR53;
	
	Candidate c;
	
	if (pairType == PAIR){
		
		in >> c.name;
		in >> c.age;
		in >> c.BT;
		in >> c.pra;
		
		in >> c.BMI;
		in >> c.diabetes;
		in >> c.genderMale;
		in >> c.weight;
		in >> c.race;
		in >> c.prevTrans;
		in >> c.TOD;
		in >> c.hepC;

		//in >> c.sensitized;
		in >> c.antibodies;
	}

	bool hold;
	in >> hold;
	
	QString comment;
	in >> comment;
	node.setInternalID(internalID);
	node.setDonor(d);
	if (pairType == PAIR){
		node.setCandidate(c);
	}
	node.setComment(comment);
	node.setHoldStatus(hold);

	return in;
}