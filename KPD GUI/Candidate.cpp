
#include "Candidate.h"

Candidate::Candidate(){
	candidateName = "Candidate Name";
	candidateAge = 40;
	candidateBT = BT_O;
	candidatePRA = 0;
	
	candidateMale = false;
	candidateBMI = 25.0;
	candidateWeight = 75.0;
	candidateRace = RACE_WHITE;
	candidateDiabetes = false;	
	candidatePrevTrans = false;
	candidateTOD = 0.0;
	candidateHepC = false;

	candidateComment = "";
}

Candidate::Candidate(DialogCandidate * c){

	qDebug() << "ENTERED Candidate::Candidate(DialogCandidate)";
	qDebug() << "From Dialog: " << c->recipNameLineEdit->text();

	candidateName = c->recipNameLineEdit->text();
	candidateAge = c->recipAgeSpinBox->value();
	candidateBT = KPDFunctions::intToBloodType(c->recipBTComboBox->currentIndex());
	candidatePRA = c->recipPRASpinBox->value();

	double height = c->recipHeightSpinBox->value();
	double weight = c->recipWeightSpinBox->value();
	QString gender = c->recipGenderComboBox->currentText();

	if (gender == "Male"){ candidateMale = true; }
	else { candidateMale = false; }
	candidateBMI = weight / height / height;
	candidateWeight = weight;
	candidateRace = KPDFunctions::intToRace(c->recipRaceComboBox->currentIndex());
	candidateDiabetes = c->recipDiabetesCheckBox->isChecked();
	candidatePrevTrans = c->recipPrevTransCheckBox->isChecked();
	candidateTOD = c->recipTODSpinBox->value();
	candidateHepC = c->recipHepCCheckBox->isChecked();

	/*QString excludedDonors = c->excludedDonorLineEdit->text();
	excludedDonors.replace(" ", "");
	QStringList excludedDonorList = excludedDonors.split(";");

	foreach(QString donor, excludedDonorList){
		int excludedDonorID = donor.toInt();
		if (kpdguiRecord->getNode(excludedDonorID) != NULL){
			candidateexcludedDonors.push_back(donor.toInt());
		}
	}*/

	QString antibodies = c->recipHLALineEdit->text();
	antibodies.replace(" ", "");
	QStringList antibodyList = antibodies.split(";");

	foreach(QString antibody, antibodyList){
		candidateAntibodies.push_back(antibody);
	}

	candidateComment = c->commentTextEdit->toPlainText();

}

Candidate::~Candidate(){

}

QString Candidate::getName() const {
	return candidateName;
}

int Candidate::getAge() const {
	return candidateAge;
}

KPDBloodType Candidate::getBT() const {
	return candidateBT;
}

int Candidate::getPRA() const {
	return candidatePRA;
}

bool Candidate::getMale() const{
	return candidateMale;
}

double Candidate::getBMI() const{
	return candidateBMI;
}

double Candidate::getWeight() const{
	return candidateWeight;
}

KPDRace Candidate::getRace() const{
	return candidateRace;
}

bool Candidate::getDiabetes() const{
	return candidateDiabetes;
}

bool Candidate::getPrevTrans() const{
	return candidatePrevTrans;
}

double Candidate::getTOD() const{
	return candidateTOD;
}

bool Candidate::getHepC() const{
	return candidateHepC;
}

QVector<int> Candidate::getExcludedDonors() const{
	return candidateExcludedDonors;
}

QString Candidate::getExcludedDonorString(){
	QString excludedDonorString = "";
	foreach(int donor, candidateExcludedDonors){
		excludedDonorString += QString::number(donor);
		excludedDonorString += ";";
	}

	excludedDonorString.chop(1);

	return excludedDonorString;
}

QVector<QString> Candidate::getAntibodies() const{
	return candidateAntibodies;
}

QString Candidate::getHLAString(){
	QString hlaString = "";
	foreach(QString antibody, candidateAntibodies){
		hlaString += antibody;
		hlaString += ";";
	}

	hlaString.chop(1);

	return hlaString;
}

QString Candidate::getComment() const{
	return candidateComment;
}

void Candidate::setName(QString name){
	candidateName = name;
}

void Candidate::setAge(int age){
	candidateAge = age;
}

void Candidate::setBT(KPDBloodType bt){
	candidateBT = bt;
}

void Candidate::setPRA(int pra){
	candidatePRA = pra;
}

void Candidate::setMale(bool genderMale){
	candidateMale = genderMale;
}

void Candidate::setBMI(double bmi){
	candidateBMI = bmi;
}

void Candidate::setWeight(double weight){
	candidateWeight = weight;
}

void Candidate::setRace(KPDRace race){
	candidateRace = race;
}

void Candidate::setDiabetes(bool diabetes){
	candidateDiabetes = diabetes;
}

void Candidate::setPrevTrans(bool prevTrans){
	candidatePrevTrans = prevTrans;
}

void Candidate::setTOD(double tod){
	candidateTOD = tod;
}

void Candidate::setHepC(bool hepC){
	candidateHepC = hepC;
}

void Candidate::setExcludedDonors(QVector<int> donors){
	candidateExcludedDonors.clear();
	foreach(int donor, donors){
		candidateExcludedDonors << donor;
	}
}

void Candidate::setAntibodies(QVector<QString> antibodies){
	candidateAntibodies.clear();
	foreach(QString antibody, antibodies){
		candidateAntibodies << antibody;
	}
}

void Candidate::setComment(QString comment){
	candidateComment = comment;
}


QDataStream &operator<<(QDataStream &out, const Candidate & candidate)
{
	out << candidate.getName();
	out << qint32(candidate.getAge());
	out << qint32(KPDFunctions::bloodTypeToInt(candidate.getBT()));
	out << qint32(candidate.getPRA());
	
	out << candidate.getMale();
	out << candidate.getBMI();
	out << candidate.getWeight();
	out << qint32(KPDFunctions::raceToInt(candidate.getRace()));
	out << candidate.getDiabetes();
	out << candidate.getPrevTrans();
	out << candidate.getTOD();
	out << candidate.getHepC();

	out << candidate.getExcludedDonors();
	out << candidate.getAntibodies();

	out << candidate.getComment();

	return out;
}

QDataStream &operator>>(QDataStream &in, Candidate & candidate)
{
	QString name;
	int age;
	int BT;
	int pra;
	
	bool male;
	double BMI;
	double weight;	
	int race;
	bool diabetes;	
	bool prevTrans;
	double TOD;
	bool hepC;

	QVector<int> excludedDonors;
	QVector<QString> antibodies;

	QString comment;

	in >> name;
	in >> age;
	in >> BT;
	in >> pra;

	in >> BMI;
	in >> diabetes;
	in >> male;
	in >> weight;
	in >> race;
	in >> prevTrans;
	in >> TOD;
	in >> hepC;

	in >> excludedDonors;
	in >> antibodies;

	in >> comment;

	candidate.setName(name);
	candidate.setAge(age);
	candidate.setBT(KPDFunctions::intToBloodType(BT));
	candidate.setPRA(pra);

	candidate.setMale(male);
	candidate.setBMI(BMI);
	candidate.setWeight(weight);
	candidate.setRace(KPDFunctions::intToRace(race));
	candidate.setDiabetes(diabetes);	
	candidate.setPrevTrans(prevTrans);
	candidate.setTOD(TOD);
	candidate.setHepC(hepC);

	candidate.setExcludedDonors(excludedDonors);
	candidate.setAntibodies(antibodies);

	candidate.setComment(comment);

	return in;

}