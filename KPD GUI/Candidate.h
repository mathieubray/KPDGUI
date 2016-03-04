#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <qstring.h>
#include <qvector.h>

#include "DialogCandidate.h"

class Candidate {

public:
	Candidate();
	Candidate(DialogCandidate * c);
	~Candidate();

	//Getters
	QString getName() const;
	int getAge() const;
	KPDBloodType getBT() const;
	int getPRA() const;

	bool getMale() const;
	double getBMI() const;
	double getWeight() const;
	KPDRace getRace() const;
	bool getDiabetes() const;	
	bool getPrevTrans() const;
	double getTOD() const;
	bool getHepC() const;

	QVector<int> getExcludedDonors() const;
	QString getExcludedDonorString();
	
	QVector<QString> getAntibodies() const;
	QString getHLAString();

	QString getComment() const;
	
	//Setters
	void setName(QString name);
	void setAge(int age);
	void setBT(KPDBloodType bt);
	void setPRA(int pra);

	void setMale(bool genderMale);
	void setBMI(double bmi);
	void setWeight(double weight);
	void setRace(KPDRace race);
	void setDiabetes(bool diabetes);	
	void setPrevTrans(bool prevTrans);
	void setTOD(double tod);
	void setHepC(bool hepC);

	void setExcludedDonors(QVector<int> donors);
	void setAntibodies(QVector<QString> antibodies);
	
	void setComment(QString comment);

private:
	//Demographics
	QString candidateName;
	int candidateAge;
	KPDBloodType candidateBT;	
	int candidatePRA;	
	
	bool candidateMale;
	double candidateBMI;
	double candidateWeight;
	KPDRace candidateRace;
	bool candidateDiabetes;	
	bool candidatePrevTrans;
	double candidateTOD;
	bool candidateHepC;

	//Compatibilities
	QVector<int> candidateExcludedDonors;
	QVector<QString> candidateAntibodies;

	QString candidateComment;
};

QDataStream &operator<<(QDataStream &out, const Candidate & candidate);

QDataStream &operator>>(QDataStream &in, Candidate & candidate);

#endif