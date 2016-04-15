#ifndef KPDGUIDONORINFO_H
#define KPDGUIDONORINFO_H

#include <qstring.h>
#include <qvector.h>

#include "DialogDonor.h"

class KPDGUIDonorInfo {

private:

	int donorUniqueID;

	// Major Fields
	QString donorName;
	int donorAge;
	KPDBloodType donorBT;

	// Characteristics
	bool donorMale;
	double donorWeight;
	double donorBMI;	

	// Compatibilities
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

	double donorFailureProbability;

	// Comment
	QString donorComment;

public:
	KPDGUIDonorInfo();
	KPDGUIDonorInfo(DialogDonor * d);
	~KPDGUIDonorInfo();

	/// Getters ///
	
	int getUniqueID() const;

	// Major Fields
	QString getName() const;
	int getAge() const;
	KPDBloodType getBT() const;
	
	// Characteristics
	bool getMale() const;
	double getWeight() const;
	double getBMI() const;	
	
	// Compatibilities
	QVector<QString> getA() const;
	QVector<QString> getB() const;
	QVector<QString> getCW() const;
	QVector<QString> getDQ() const;
	QVector<QString> getDR() const;
	bool getBW4() const;
	bool getBW6() const;
	bool getDR51() const;
	bool getDR52() const;
	bool getDR53() const;
	QVector<QString> getAdditionalHLA() const;

	double getFailureProbability() const;

	// Comment
	QString getComment() const;


	/// Setters ///

	void setUniqueID(int id);
	
	// Major Fields
	void setName(QString name);
	void setAge(int age);
	void setBT(KPDBloodType bt);

	// Characteristics
	void setBMI(double bmi);
	void setMale(bool genderMale);
	void setWeight(double weight);

	// Compatibilities
	void setA(QVector<QString> hlaA);
	void setB(QVector<QString> hlaB);
	void setCW(QVector<QString> hlaCW);
	void setDQ(QVector<QString> hlaDQ);
	void setDR(QVector<QString> hlaDR);

	void addA(QString hlaA);
	void addB(QString hlaB);
	void addCW(QString hlaCW);
	void addDQ(QString hlaDQ);
	void addDR(QString hlaDR);

	void removeA(QString hlaA);
	void removeB(QString hlaB);
	void removeCW(QString hlaCW);
	void removeDQ(QString hlaDQ);
	void removeDR(QString hlaDR);

	void setBW4(bool hlaBW4);
	void setBW6(bool hlaBW6);
	void setDR51(bool hlaDR51);
	void setDR52(bool hlaDR52);
	void setDR53(bool hlaDR52);

	void setAdditionalDonorHLA(QVector<QString> additionalHLA);
	void addAdditionalDonorHLA(QString additionalHLA);
	void removeAdditionalDonorHLA(QString additionalHLA);

	void setFailureProbability(double prob);

	// Comment
	void setComment(QString comment);


	/// Strings ///

	QString fullHLAString();
	QString additionalHLAString();


};

QDataStream &operator<<(QDataStream &out, const KPDGUIDonorInfo & donor);

QDataStream &operator>>(QDataStream &in, KPDGUIDonorInfo & donor);

#endif