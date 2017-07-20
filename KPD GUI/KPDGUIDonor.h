#ifndef KPDGUIDONOR_H
#define KPDGUIDONOR_H

#include <qstring.h>
#include <qvector.h>

#include "DialogDonor.h"

class KPDGUINode;
class KPDGUIMatch;
class KPDGUICandidate;

class KPDGUIDonor : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT;

private:

	int matchingID;
	int donorNumber;

	bool donorIsAltruistic;

	KPDGUINode * parentNode;

	// Major Fields
	QString donorName;
	int donorAge;
	KPDBloodType donorBT;
	
	// HLA Information
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

	// Characteristics
	bool donorMale;
	KPDRace donorRace;
	double donorHeight;
	double donorWeight;
	bool donorCigarette;
	
	// Additional Parameters
	bool donorStatus;
	double donorFailureProbability;

	QSet<KPDGUIMatch *>  donorMatches;
	
	int popularityInArrangements;
	int popularityInSolutions;

	KPDNodeDisplayMode currentDisplayMode;
	
	// Comment
	QString donorComment;		

signals:

	void donorSelectionChanged(int matchingID, int donorID, bool selected);
	void donorEntered(int matchingID, int donorID);
	void donorExited(int matchingID, int donorID);
	void donorEdited();

protected:

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);	

public slots:

	void editDonor(DialogDonor * dialog);
	void updateVisualProperties();

public:

	KPDGUIDonor();
	KPDGUIDonor(DialogDonor * d);
	~KPDGUIDonor();
		
	void addA(QString hlaA);
	void addB(QString hlaB);
	void addCW(QString hlaCW);
	void addDQ(QString hlaDQ);
	void addDR(QString hlaDR);
	void addAdditionalDonorHLA(QString additionalHLA);

	void removeA(QString hlaA);
	void removeB(QString hlaB);
	void removeCW(QString hlaCW);
	void removeDQ(QString hlaDQ);
	void removeDR(QString hlaDR);
	void removeAdditionalDonorHLA(QString additionalHLA);
	
	bool hasNoMatches();
	int getNumberOfMatches();
	void addMatchingCandidate(KPDGUIMatch * match);
	void removeMatchingCandidate(KPDGUIMatch * match);
	KPDGUIMatch * findMatchingCandidate(KPDGUICandidate * candidate);

	void increasePopularityInArrangements();
	void increasePopularityInSolutions();
	void decreasePopularityInArrangements();
	void decreasePopularityInSolutions();
	void resetPopularityInArrangements();
	void resetPopularityInSolutions();


	/// Getters ///
	
	int getID() const;
	int getDonorNumber() const;

	bool isAltruistic() const;

	// Major Fields
	QString getName() const;
	int getAge() const;
	KPDBloodType getBT() const;

	// HLA Information
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

	// Characteristics
	bool getMale() const;
	KPDRace getRace() const;
	double getHeight() const;
	double getWeight() const;
	double getBMI() const;
	bool getCigarette() const;

	// Additional Parameters
	bool getStatus() const;
	double getFailureProbability() const;

	QSet<KPDGUIMatch *> getMatches() const;

	int getPopularityInArrangements();
	int getPopularityInSolutions();

	// Comment
	QString getComment() const;


	/// Setters ///

	void setParentNode(KPDGUINode * node);
		
	void setID(int id);
	void setDonorNumber(int id);

	void setAltruistic(bool altruistic);

	// Major Fields
	void setName(QString name);
	void setAge(int age);
	void setBT(KPDBloodType bt);

	// HLA Information
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

	// Characteristics
	void setMale(bool genderMale);
	void setRace(KPDRace race);
	void setHeight(double height);
	void setWeight(double weight);
	void setCigarette(bool cigarette);

	// Additional Parameters
	void setStatus(bool status);
	void setFailureProbability(double prob);

	void setMatches(QSet<KPDGUIMatch *> matches);

	// Comment
	void setComment(QString comment);


	/// Visual Properties ///

	void setDisplayMode(KPDNodeDisplayMode mode);

	QPointF getDonorPosition();
	void setDonorPosition(QPointF point);

	QPointF getPosition();
	QPolygonF getRect();

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	

	/// Strings ///

	QString donorString();
	QString compatibilitiesString();
	QString fullHLAString();
	QString additionalHLAString();

};

QDataStream &operator<<(QDataStream &out, const KPDGUIDonor & donor);

QDataStream &operator>>(QDataStream &in, KPDGUIDonor & donor);

#endif