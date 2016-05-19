#ifndef KPDGUIDONOR_H
#define KPDGUIDONOR_H

#include <qstring.h>
#include <qvector.h>

#include "DialogDonor.h"

class KPDGUIMatch;
class KPDGUICandidate;

class KPDGUIDonor : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT;

private:

	int matchingID;
	int donorNumber;

	// Major Fields
	QString donorName;
	int donorAge;
	KPDBloodType donorBT;

	bool donorIsAltruistic;
	bool donorStatus;
	double donorFailureProbability;

	QSet<KPDGUIMatch *>  donorMatches;

	// Popularity
	int popularityInStructures;
	int popularityInSolutions;

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

	// Comment
	QString donorComment;

	// Visual
	QColor donorBackgroundColor;
	qreal donorOpacity;
	QString donorLabel;
	

signals:
	void donorClicked(bool selected);
	void donorSelectionChanged(bool selected);
	void donorStatusChanged(bool status);
	void donorEdited();
	void donorEntered();
	void donorExited();


protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

	

public slots:
	void editDonor();
	void updateVisualProperties();

public:
	KPDGUIDonor();
	KPDGUIDonor(DialogDonor * d);
	~KPDGUIDonor();

	/// Getters ///
	
	int getID() const;
	int getDonorNumber() const;

	// Major Fields
	QString getName() const;
	int getAge() const;
	KPDBloodType getBT() const;
	
	bool isAltruistic() const;
	bool getStatus() const;
	double getFailureProbability() const;

	QSet<KPDGUIMatch *> getMatches() const;
	bool hasNoMatches();
	int getNumberOfMatches();

	// Popularity
	int getPopularityInStructures();
	int getPopularityInSolutions();

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

	// Comment
	QString getComment() const;


	/// Setters ///
		
	void setID(int id);
	void setDonorNumber(int id);

	// Major Fields
	void setName(QString name);
	void setAge(int age);
	void setBT(KPDBloodType bt);

	void setAltruistic(bool altruistic);
	void setStatus(bool status);
	void setFailureProbability(double prob);

	void setMatches(QSet<KPDGUIMatch *> matches);
	void addMatchingCandidate(KPDGUIMatch * match);
	void removeMatchingCandidate(KPDGUIMatch * match);
	KPDGUIMatch * findMatchingCandidate(KPDGUICandidate * candidate);

	// Popularity
	void increasePopularityInStructures();
	void increasePopularityInSolutions();
	void decreasePopularityInStructures();
	void decreasePopularityInSolutions();
	void resetPopularityInStructures();
	void resetPopularityInSolutions();

	// Characteristics
	void setMale(bool genderMale);
	void setWeight(double weight);
	void setBMI(double bmi);

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

	// Comment
	void setComment(QString comment);

	/// Visual Properties ///

	QPointF getDonorPosition();
	void setDonorPosition(QPointF point);
	QString text() const;
	void setText(const QString &text);
	void setBackgroundColor();
	QColor backgroundColor() const;
	//QRectF boundingRect() const;
	//QPainterPath shape() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	//QVariant data(int column) const;
	

	/// Strings ///
	QString donorString();
	QString compatibilitiesString();
	QString fullHLAString();
	QString additionalHLAString();

};

QDataStream &operator<<(QDataStream &out, const KPDGUIDonor & donor);

QDataStream &operator>>(QDataStream &in, KPDGUIDonor & donor);

#endif