#ifndef DONOR_H
#define DONOR_H

#include <qstring.h>
#include <qvector.h>

#include "DialogDonor.h"

class Donor {

public:
	Donor();
	Donor(DialogDonor * d);
	~Donor();

	//Getters
	QString getName() const;
	int getAge() const;
	KPDBloodType getBT() const;
	
	double getBMI() const;
	bool getMale() const;
	double getWeight() const;
	
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

	QString getFullHLAString();
	QString getAdditionalHLAString();

	QString getComment() const;

	//Setters
	void setName(QString name);
	void setAge(int age);
	void setBT(KPDBloodType bt);

	void setBMI(double bmi);
	void setMale(bool genderMale);
	void setWeight(double weight);

	void setA(QVector<QString> hlaA);
	void setB(QVector<QString> hlaB);
	void setCW(QVector<QString> hlaCW);
	void setDQ(QVector<QString> hlaDQ);
	void setDR(QVector<QString> hlaDR);
	void setBW4(bool hlaBW4);
	void setBW6(bool hlaBW6);
	void setDR51(bool hlaDR51);
	void setDR52(bool hlaDR52);
	void setDR53(bool hlaDR52);
	void setAdditionalDonorHLA(QVector<QString> additionalHLA);

	void setComment(QString comment);

private:
	//Demographics
	QString donorName;
	int donorAge;
	KPDBloodType donorBT;

	double donorBMI;
	bool donorMale;
	double donorWeight;	

	//Compatibilities
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

	QString donorComment;

};

QDataStream &operator<<(QDataStream &out, const Donor & donor);

QDataStream &operator>>(QDataStream &in, Donor & donor);

#endif