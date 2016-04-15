#ifndef KPDGUICANDIDATEINFO_H
#define KPDGUICANDIDATEINFO_H

#include <qstring.h>
#include <qvector.h>

#include "DialogCandidate.h"

class KPDGUICandidateInfo {

private:

	int candidateUniqueID;

	// Major Fields
	QString candidateName;
	int candidateAge;
	int candidatePRA;
	KPDBloodType candidateBT;
	
	// Characteristics
	bool candidateMale;
	KPDRace candidateRace;
	bool candidateDiabetes;
	double candidateWeight;
	double candidateBMI;	
	bool candidatePrevTrans;
	double candidateTOD;
	bool candidateHepC;

	// Compatibilities
	QVector<int> candidateExcludedDonors;
	QVector<QString> candidateHLA;

	double candidateFailureProbability;

	// Comment
	QString candidateComment;

public:
	KPDGUICandidateInfo();
	KPDGUICandidateInfo(DialogCandidate * c);
	~KPDGUICandidateInfo();

	/// Getters ///

	int getUniqueID() const;

	// Major Fields
	QString getName() const;
	int getAge() const;	
	int getPRA() const;
	KPDBloodType getBT() const;	

	// Characteristics
	bool getMale() const;
	KPDRace getRace() const;
	bool getDiabetes() const;
	double getWeight() const;
	double getBMI() const;	
	bool getPrevTrans() const;
	double getTOD() const;
	bool getHepC() const;

	// Compatibilities
	QVector<int> getExcludedDonors() const;
	QVector<QString> getHLA() const;

	double getFailureProbability() const;

	// Comment
	QString getComment() const;
		
	
	/// Setters ///

	void setUniqueID(int id);
	
	// Major Fields
	void setName(QString name);
	void setAge(int age);
	void setPRA(int pra);
	void setBT(KPDBloodType bt);
	
	// Characteristics
	void setMale(bool genderMale);
	void setRace(KPDRace race);
	void setDiabetes(bool diabetes);	
	void setWeight(double weight);
	void setBMI(double bmi);
	void setPrevTrans(bool prevTrans);
	void setTOD(double tod);
	void setHepC(bool hepC);

	// Compatibilities
	void setExcludedDonors(QVector<int> donors);
	void addExcludedDonor(int donor);
	void removeExcludedDonor(int donor);

	void setHLA(QVector<QString> hla);
	void addHLA(QString hla);
	void removeHLA(QString hla);
	
	void setFailureProbability(double prob);


	// Comment
	void setComment(QString comment);

	/// Strings ///

	QString getExcludedDonorString();
	QString getHLAString();
};

QDataStream &operator<<(QDataStream &out, const KPDGUICandidateInfo & candidate);

QDataStream &operator>>(QDataStream &in, KPDGUICandidateInfo & candidate);

#endif