#include "donor.h"

Donor::Donor(){
	donorName = "Donor Name";
	donorAge = 40;
	donorBT = BT_O;

	donorBMI = 25.0;
	donorMale = false;
	donorWeight = 75.0;

	donorA.push_back("");
	donorB.push_back("");
	donorCW.push_back("");
	donorDQ.push_back("");
	donorDR.push_back("");
	donorBW4 = false;
	donorBW6 = false;
	donorDR51 = false;
	donorDR52 = false;
	donorDR53 = false;
	additionalDonorHLA.push_back("");

	donorComment = "";
}

Donor::Donor(DialogDonor * d){

	donorName = d->donorNameLineEdit->text();
	donorAge = d->donorAgeSpinBox->value();
	
	int btIndex = d->donorBTComboBox->currentIndex();
	donorBT = KPDFunctions::intToBloodType(btIndex);

	double height = d->donorHeightSpinBox->value();
	double weight = d->donorWeightSpinBox->value();
	QString gender = d->donorGenderComboBox->currentText();

	donorBMI = weight / height / height;
	if (gender == "Male"){ donorMale = true; }
	else { donorMale = false; }
	donorWeight = weight;

	QString hlaA1 = d->donorHLAA1ComboBox->currentText();
	QString hlaA2 = d->donorHLAA2ComboBox->currentText();
	if (hlaA1 != ""){
		donorA.push_back(hlaA1);
	}
	if (hlaA2 != hlaA1 && hlaA2 != ""){
		donorA.push_back(hlaA2);
	}

	QString hlaB1 = d->donorHLAB1ComboBox->currentText();
	QString hlaB2 = d->donorHLAB2ComboBox->currentText();
	if (hlaB1 != ""){
		donorB.push_back(hlaB1);
	}
	if (hlaB2 != hlaB1 && hlaB2 != ""){
		donorB.push_back(hlaB2);
	}

	QString hlaCW1 = d->donorHLACW1ComboBox->currentText();
	QString hlaCW2 = d->donorHLACW2ComboBox->currentText();
	if (hlaCW1 != ""){
		donorCW.push_back(hlaCW1);
	}
	if (hlaCW2 != hlaCW1 && hlaCW2 != ""){
		donorCW.push_back(hlaCW2);
	}

	QString hlaDQ1 = d->donorHLADQ1ComboBox->currentText();
	QString hlaDQ2 = d->donorHLADQ2ComboBox->currentText();
	if (hlaDQ1 != ""){
		donorDQ.push_back(hlaDQ1);
	}
	if (hlaDQ2 != hlaDQ1 && hlaDQ2 != ""){
		donorDQ.push_back(hlaDQ2);
	}

	QString hlaDR1 = d->donorHLADR1ComboBox->currentText();
	QString hlaDR2 = d->donorHLADR2ComboBox->currentText();
	if (hlaDR1 != ""){
		donorDR.push_back(hlaDR1);
	}
	if (hlaDR2 != hlaDR1 && hlaDR2 != ""){
		donorDR.push_back(hlaDR2);
	}

	donorBW4 = d->donorBW4CheckBox->isChecked();
	donorBW6 = d->donorBW6CheckBox->isChecked();
	donorDR51 = d->donorDR51CheckBox->isChecked();
	donorDR52 = d->donorDR52CheckBox->isChecked();
	donorDR53 = d->donorDR53CheckBox->isChecked();

	QString additionalDonorHLA = d->donorHLALineEdit->text();
	additionalDonorHLA.replace(" ", "");
	QStringList additionalDonorHLAList = additionalDonorHLA.split(";");

	foreach(QString antibody, additionalDonorHLAList){
		additionalDonorHLA.push_back(antibody);
	}

	donorComment = d->commentTextEdit->toPlainText();

}

Donor::~Donor(){

}

QString Donor::getName() const {
	return donorName;
}

int Donor::getAge() const {
	return donorAge;
}

KPDBloodType Donor::getBT() const {
	return donorBT;
}

double Donor::getBMI() const{
	return donorBMI;
}

bool Donor::getMale() const{
	return donorMale;
}

double Donor::getWeight() const{
	return donorWeight;
}

QVector<QString> Donor::getA() const {
	return donorA;
}

QVector<QString> Donor::getB() const {
	return donorB;
}

QVector<QString> Donor::getCW() const {
	return donorCW;
}

QVector<QString> Donor::getDQ() const {
	return donorDQ;
}

QVector<QString> Donor::getDR() const {
	return donorDR;
}

bool Donor::getBW4() const{
	return donorBW4;
}

bool Donor::getBW6() const{
	return donorBW6;
}

bool Donor::getDR51() const{
	return donorDR51;
}

bool Donor::getDR52() const{
	return donorDR52;
}

bool Donor::getDR53() const{
	return donorDR53;
}

QVector<QString> Donor::getAdditionalHLA() const{
	return additionalDonorHLA;
}

QString Donor::getFullHLAString(){
	QString hlaString = "";
	foreach(QString hlaA, donorA){
		if (!hlaA.isEmpty()){
			hlaString += hlaA;
			hlaString += ";";
		}
	}
	foreach(QString hlaB, donorB){
		if (!hlaB.isEmpty()){
			hlaString += hlaB;
			hlaString += ";";
		}
	}
	if (donorBW4 == true){
		hlaString += "BW4";
		hlaString += ";";
	}
	if (donorBW6 == true){
		hlaString += "BW6";
		hlaString += ";";
	}
	foreach(QString hlaCW, donorCW){
		if (!hlaCW.isEmpty()){
			hlaString += hlaCW;
			hlaString += ";";
		}
	}
	
	foreach(QString hlaDQ, donorDQ){
		if (!hlaDQ.isEmpty()){
			hlaString += hlaDQ;
			hlaString += ";";
		}
	}
	foreach(QString hlaDR, donorDR){
		if (!hlaDR.isEmpty()){
			hlaString += hlaDR;
			hlaString += ";";
		}
	}
	if (donorDR51 == true){
		hlaString += "DR51";
		hlaString += ";";
	}
	if (donorDR52 == true){
		hlaString += "DR52";
		hlaString += ";";
	}
	if (donorDR53 == true){
		hlaString += "DR53";
		hlaString += ";";
	}
	hlaString.chop(1);
	hlaString += "(";
	foreach(QString hla, additionalDonorHLA){
		if (!hla.isEmpty()){
			hlaString += hla;
			hlaString += ";";
		}
	}
	hlaString.chop(1);
	hlaString += ")";

	return hlaString;
}

QString Donor::getAdditionalHLAString(){
	QString hlaString = "";
	foreach(QString hla, additionalDonorHLA){
		hlaString += hla;
		hlaString += ";";
	}

	hlaString.chop(1);

	return hlaString;
}

QString Donor::getComment() const {
	return donorComment;
}

void Donor::setName(QString name){
	donorName = name;
}

void Donor::setAge(int age){
	donorAge = age;
}

void Donor::setBT(KPDBloodType bt){
	donorBT = bt;
}

void Donor::setBMI(double bmi){
	donorBMI = bmi;
}

void Donor::setMale(bool genderMale){
	donorMale = genderMale;
}

void Donor::setWeight(double weight){
	donorWeight = weight;
}

void Donor::setA(QVector<QString> hlaA){
	donorA.clear();
	foreach(QString hla, hlaA){
		donorA << hla;
	}
}

void Donor::setB(QVector<QString> hlaB){
	donorB.clear();
	foreach(QString hla, hlaB){
		donorB << hla;
	}
}

void Donor::setCW(QVector<QString> hlaCW){
	donorCW.clear();
	foreach(QString hla, hlaCW){
		donorCW << hla;
	}
}

void Donor::setDQ(QVector<QString> hlaDQ){
	donorDQ.clear();
	foreach(QString hla, hlaDQ){
		donorDQ << hla;
	}
}

void Donor::setDR(QVector<QString> hlaDR){
	donorDR.clear();
	foreach(QString hla, hlaDR){
		donorDR << hla;
	}
}

void Donor::setBW4(bool hlaBW4){
	donorBW4 = hlaBW4;
}

void Donor::setBW6(bool hlaBW6){
	donorBW6 = hlaBW6;
}

void Donor::setDR51(bool hlaDR51){
	donorDR51 = hlaDR51;
}

void Donor::setDR52(bool hlaDR52){
	donorDR52 = hlaDR52;
}

void Donor::setDR53(bool hlaDR53){
	donorDR53 = hlaDR53;
}

void Donor::setAdditionalDonorHLA(QVector<QString> additionalHLA){
	additionalDonorHLA.clear();
	foreach(QString hla, additionalHLA){
		additionalDonorHLA << hla;
	}
}

void Donor::setComment(QString comment){
	donorComment = comment;
}


QDataStream &operator<<(QDataStream &out, const Donor & donor)
{
	out << donor.getName();
	out << qint32(donor.getAge());
	out << qint32(KPDFunctions::bloodTypeToInt(donor.getBT()));

	out << donor.getBMI();
	out << donor.getMale();
	out << donor.getWeight();

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

	out << donor.getComment();

	return out;
}

QDataStream &operator>>(QDataStream &in, Donor & donor)
{
	QString name;
	int age;
	int BT;

	double BMI;
	bool male;
	double weight;
	
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

	QString comment;

	in >> name;
	in >> age;
	in >> BT;

	in >> BMI;
	in >> male;
	in >> weight;

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

	in >> comment;

	donor.setName(name);
	donor.setAge(age);
	donor.setBT(KPDFunctions::intToBloodType(BT));

	donor.setBMI(BMI);
	donor.setMale(male);
	donor.setWeight(weight);

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
