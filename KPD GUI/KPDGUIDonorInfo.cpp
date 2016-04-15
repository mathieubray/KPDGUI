#include "KPDGUIDonorInfo.h"

KPDGUIDonorInfo::KPDGUIDonorInfo(){
	donorUniqueID = 0;

	donorName = "Donor Name";
	donorAge = 40;
	donorBT = BT_O;

	donorMale = false;
	donorWeight = 75.0;
	donorBMI = 25.0;	

	donorBW4 = false;
	donorBW6 = false;
	donorDR51 = false;
	donorDR52 = false;
	donorDR53 = false;

	donorFailureProbability = 0.1;

	donorComment = "";
}

KPDGUIDonorInfo::KPDGUIDonorInfo(DialogDonor * d){

	donorUniqueID = 0;

	donorName = d->donorNameLineEdit->text();
	donorAge = d->donorAgeSpinBox->value();	
	donorBT = KPDFunctions::intToBloodType(d->donorBTComboBox->currentIndex());

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
}

KPDGUIDonorInfo::~KPDGUIDonorInfo(){

}

int KPDGUIDonorInfo::getUniqueID() const {
	return donorUniqueID;
}

QString KPDGUIDonorInfo::getName() const {
	return donorName;
}

int KPDGUIDonorInfo::getAge() const {
	return donorAge;
}

KPDBloodType KPDGUIDonorInfo::getBT() const {
	return donorBT;
}

double KPDGUIDonorInfo::getBMI() const{
	return donorBMI;
}

bool KPDGUIDonorInfo::getMale() const{
	return donorMale;
}

double KPDGUIDonorInfo::getWeight() const{
	return donorWeight;
}

QVector<QString> KPDGUIDonorInfo::getA() const {
	return donorA;
}

QVector<QString> KPDGUIDonorInfo::getB() const {
	return donorB;
}

QVector<QString> KPDGUIDonorInfo::getCW() const {
	return donorCW;
}

QVector<QString> KPDGUIDonorInfo::getDQ() const {
	return donorDQ;
}

QVector<QString> KPDGUIDonorInfo::getDR() const {
	return donorDR;
}

bool KPDGUIDonorInfo::getBW4() const{
	return donorBW4;
}

bool KPDGUIDonorInfo::getBW6() const{
	return donorBW6;
}

bool KPDGUIDonorInfo::getDR51() const{
	return donorDR51;
}

bool KPDGUIDonorInfo::getDR52() const{
	return donorDR52;
}

bool KPDGUIDonorInfo::getDR53() const{
	return donorDR53;
}

QVector<QString> KPDGUIDonorInfo::getAdditionalHLA() const{
	return additionalDonorHLA;
}

double KPDGUIDonorInfo::getFailureProbability() const {
	return donorFailureProbability;
}

QString KPDGUIDonorInfo::getComment() const {
	return donorComment;
}

void KPDGUIDonorInfo::setUniqueID(int id) {
	donorUniqueID = id;
}

void KPDGUIDonorInfo::setName(QString name){
	donorName = name;
}

void KPDGUIDonorInfo::setAge(int age){
	donorAge = age;
}

void KPDGUIDonorInfo::setBT(KPDBloodType bt){
	donorBT = bt;
}

void KPDGUIDonorInfo::setBMI(double bmi){
	donorBMI = bmi;
}

void KPDGUIDonorInfo::setMale(bool genderMale){
	donorMale = genderMale;
}

void KPDGUIDonorInfo::setWeight(double weight){
	donorWeight = weight;
}

void KPDGUIDonorInfo::setA(QVector<QString> hlaA){
	donorA.clear();
	foreach(QString hla, hlaA){
		donorA << hla;
	}
}

void KPDGUIDonorInfo::setB(QVector<QString> hlaB){
	donorB.clear();
	foreach(QString hla, hlaB){
		donorB << hla;
	}
}

void KPDGUIDonorInfo::setCW(QVector<QString> hlaCW){
	donorCW.clear();
	foreach(QString hla, hlaCW){
		donorCW << hla;
	}
}

void KPDGUIDonorInfo::setDQ(QVector<QString> hlaDQ){
	donorDQ.clear();
	foreach(QString hla, hlaDQ){
		donorDQ << hla;
	}
}

void KPDGUIDonorInfo::setDR(QVector<QString> hlaDR){
	donorDR.clear();
	foreach(QString hla, hlaDR){
		donorDR << hla;
	}
}

void KPDGUIDonorInfo::addA(QString hlaA){
	donorA << hlaA;
}

void KPDGUIDonorInfo::addB(QString hlaB){
	donorB << hlaB;
}

void KPDGUIDonorInfo::addCW(QString hlaCW){
	donorCW << hlaCW;
}

void KPDGUIDonorInfo::addDQ(QString hlaDQ){
	donorDQ << hlaDQ;
}

void KPDGUIDonorInfo::addDR(QString hlaDR){
	donorDR << hlaDR;
}

void KPDGUIDonorInfo::removeA(QString hlaA) {
	int position = donorA.indexOf(hlaA);
	if (position >= 0) {
		donorA.remove(position);
	}
}

void KPDGUIDonorInfo::removeB(QString hlaB) {
	int position = donorB.indexOf(hlaB);
	if (position >= 0) {
		donorB.remove(position);
	}
}

void KPDGUIDonorInfo::removeCW(QString hlaCW) {
	int position = donorCW.indexOf(hlaCW);
	if (position >= 0) {
		donorCW.remove(position);
	}
}

void KPDGUIDonorInfo::removeDQ(QString hlaDQ) {
	int position = donorDQ.indexOf(hlaDQ);
	if (position >= 0) {
		donorDQ.remove(position);
	}
}

void KPDGUIDonorInfo::removeDR(QString hlaDR) {
	int position = donorDR.indexOf(hlaDR);
	if (position >= 0) {
		donorDR.remove(position);
	}
}

void KPDGUIDonorInfo::setBW4(bool hlaBW4) {
	donorBW4 = hlaBW4;
}

void KPDGUIDonorInfo::setBW6(bool hlaBW6) {
	donorBW6 = hlaBW6;
}

void KPDGUIDonorInfo::setDR51(bool hlaDR51) {
	donorDR51 = hlaDR51;
}

void KPDGUIDonorInfo::setDR52(bool hlaDR52) {
	donorDR52 = hlaDR52;
}

void KPDGUIDonorInfo::setDR53(bool hlaDR53) {
	donorDR53 = hlaDR53;
}

void KPDGUIDonorInfo::setAdditionalDonorHLA(QVector<QString> additionalHLA){
	additionalDonorHLA.clear();
	foreach(QString hla, additionalHLA){
		additionalDonorHLA << hla;
	}
}

void KPDGUIDonorInfo::addAdditionalDonorHLA(QString additionalHLA){
	additionalDonorHLA << additionalHLA;
}

void KPDGUIDonorInfo::removeAdditionalDonorHLA(QString additionalHLA) {
	int position = additionalDonorHLA.indexOf(additionalHLA);
	if (position >= 0) {
		additionalDonorHLA.remove(position);
	}
}

void KPDGUIDonorInfo::setFailureProbability(double prob) {
	donorFailureProbability = prob;
}

void KPDGUIDonorInfo::setComment(QString comment){
	donorComment = comment;
}

QString KPDGUIDonorInfo::fullHLAString() {
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

QString KPDGUIDonorInfo::additionalHLAString() {
	QString hlaString = "";
	foreach(QString hla, additionalDonorHLA) {
		hlaString += hla;
		hlaString += ";";
	}

	hlaString.chop(1);

	return hlaString;
}


QDataStream &operator<<(QDataStream &out, const KPDGUIDonorInfo & donor)
{
	out << donor.getUniqueID();

	out << donor.getName();
	out << qint32(donor.getAge());
	out << qint32(KPDFunctions::bloodTypeToInt(donor.getBT()));
	
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

	out << donor.getFailureProbability();

	out << donor.getComment();

	return out;
}

QDataStream &operator>>(QDataStream &in, KPDGUIDonorInfo & donor)
{
	int uniqueID;

	QString name;
	int age;
	int BT;

	bool male;
	double weight;
	double BMI;	
	
	QVector<QString> donorA;
	QVector<QString> donorB;
	bool donorBW4;
	bool donorBW6;
	QVector<QString> donorCW;
	QVector<QString> donorDQ;
	QVector<QString> donorDR;
	bool donorDR51;
	bool donorDR52;
	bool donorDR53;
	QVector<QString> additionalDonorHLA;

	double failureProb;

	QString comment;

	in >> uniqueID;

	in >> name;
	in >> age;	
	in >> BT;

	in >> male;
	in >> weight;
	in >> BMI;
	
	in >> donorA;
	in >> donorB;	
	in >> donorCW;
	in >> donorDQ;
	in >> donorDR;
	in >> donorBW4;
	in >> donorBW6;
	in >> donorDR51;
	in >> donorDR52;
	in >> donorDR53;
	in >> additionalDonorHLA;

	in >> failureProb;

	in >> comment;

	donor.setUniqueID(uniqueID);

	donor.setName(name);
	donor.setAge(age);
	donor.setBT(KPDFunctions::intToBloodType(BT));

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

	donor.setFailureProbability(failureProb);

	donor.setComment(comment);

	return in;
}