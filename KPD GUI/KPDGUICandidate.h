#ifndef KPDGUICANDIDATE_H
#define KPDGUICANDIDATE_H

#include <qstring.h>
#include <qvector.h>

#include "DialogCandidate.h"

class KPDGUIMatch;
class KPDGUIDonor;

class KPDGUICandidate : public QObject, public QGraphicsEllipseItem 
{
	Q_OBJECT;

private:

	int matchingID;

	// Major Fields
	QString candidateName;
	int candidateAge;
	int candidatePRA;
	KPDBloodType candidateBT;

	bool candidateStatus;
	double candidateFailureProbability;

	QSet<KPDGUIMatch *> candidateMatches;

	// Popularity
	int popularityInStructures;
	int popularityInSolutions;
	
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

	// Comment
	QString candidateComment;

	// Visual
	QColor candidateBackgroundColor;
	qreal candidateOpacity;
	QString candidateLabel;
	

signals:
	void candidateClicked(bool selected);
	void candidateSelectionChanged(bool selected);
	void candidatetatusChanged(bool status);
	void candidateEdited();
	void candidateEntered();
	void candidateExited();


protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

	


public slots:

	void editCandidate();
	void updateVisualProperties();


public:
	KPDGUICandidate();
	KPDGUICandidate(DialogCandidate * c);
	~KPDGUICandidate();

	/// Getters ///

	int getID() const;

	// Major Fields
	QString getName() const;
	int getAge() const;	
	int getPRA() const;
	KPDBloodType getBT() const;

	bool checkWithinBounds(int minPRA, int maxPRA);

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

	// Comment
	QString getComment() const;
		
	
	/// Setters ///

	void setID(int id);
	
	// Major Fields
	void setName(QString name);
	void setAge(int age);
	void setPRA(int pra);
	void setBT(KPDBloodType bt);

	void setStatus(bool status);
	void setFailureProbability(double prob);

	void setMatches(QSet<KPDGUIMatch *> matches);
	void addMatchingDonor(KPDGUIMatch * match);
	void removeMatchingDonor(KPDGUIMatch * match);
	KPDGUIMatch * findMatchingDonor(KPDGUIDonor * donor);
	
	// Popularity
	void increasePopularityInStructures();
	void increasePopularityInSolutions();
	void decreasePopularityInStructures();
	void decreasePopularityInSolutions();
	void resetPopularityInStructures();
	void resetPopularityInSolutions();

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

	// Comment
	void setComment(QString comment);


	/// Visual Properties ///

	QPointF getCenter();
	QString text() const;
	void setText(const QString &text);
	void setBackgroundColor();
	QColor backgroundColor() const;
	//QRectF boundingRect() const;
	//QPainterPath shape() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	//QVariant data(int column) const;
	

	/// Strings ///
	QString candidateString();
	QString compatibilitiesString();
	QString excludedDonorString();
	QString hlaString();

};

QDataStream &operator<<(QDataStream &out, const KPDGUICandidate & candidate);

QDataStream &operator>>(QDataStream &in, KPDGUICandidate & candidate);

#endif