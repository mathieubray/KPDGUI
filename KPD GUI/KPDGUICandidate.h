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

	// HLA Information
	QVector<QString> candidateHLA;
	
	// Characteristics
	bool candidateMale;
	KPDRace candidateRace;
	bool candidateDiabetes;
	double candidateHeight;
	double candidateWeight;
	bool candidatePrevTrans;
	double candidateTOD;
	bool candidateHepC;
	KPDInsurance candidateInsurance;

	// Additional Parameters
	bool candidateStatus;
	double candidateFailureProbability;

	QVector<int> candidateExcludedDonors;

	QSet<KPDGUIMatch *> candidateMatches;
	
	int popularityInArrangements;
	int popularityInSolutions;

	// Comment
	QString candidateComment;	

signals:

	void candidateSelectionChanged(int id, bool selected);
	void candidateEntered(int id);
	void candidateExited(int id);
	void candidateEdited();

protected:

	QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);
	
public slots:

	void editCandidate(DialogCandidate * dialog);
	void updateVisualProperties();

public:

	KPDGUICandidate();
	KPDGUICandidate(DialogCandidate * c);
	~KPDGUICandidate();
	
	bool checkWithinBounds(int minPRA, int maxPRA);
	
	void addHLA(QString hla);
	void removeHLA(QString hla);

	void addExcludedDonor(int donor);
	void removeExcludedDonor(int donor);

	bool hasNoMatches();
	int getNumberOfMatches();
	void addMatchingDonor(KPDGUIMatch * match);
	void removeMatchingDonor(KPDGUIMatch * match);
	KPDGUIMatch * findMatchingDonor(KPDGUIDonor * donor);

	void increasePopularityInArrangements();
	void increasePopularityInSolutions();
	void decreasePopularityInArrangements();
	void decreasePopularityInSolutions();
	void resetPopularityInArrangements();
	void resetPopularityInSolutions();
	

	/// Getters ///

	int getID() const;

	// Major Fields
	QString getName() const;
	int getAge() const;	
	int getPRA() const;
	KPDBloodType getBT() const;

	// HLA Information
	QVector<QString> getHLA() const;
	
	// Characteristics
	bool getMale() const;
	KPDRace getRace() const;
	bool getDiabetes() const;
	double getHeight() const;
	double getWeight() const;
	double getBMI() const;	
	bool getPrevTrans() const;
	double getTOD() const;
	bool getHepC() const;
	KPDInsurance getInsurance() const;

	// Additional Parameters
	bool getStatus() const;
	double getFailureProbability() const;

	QVector<int> getExcludedDonors() const;

	QSet<KPDGUIMatch *> getMatches() const;

	int getPopularityInArrangements();
	int getPopularityInSolutions();
	
	// Comment
	QString getComment() const;
		
	
	/// Setters ///

	void setID(int id);
	
	// Major Fields
	void setName(QString name);
	void setAge(int age);
	void setPRA(int pra);
	void setBT(KPDBloodType bt);

	// HLA Information
	void setHLA(QVector<QString> hla);
	
	// Characteristics
	void setMale(bool genderMale);
	void setRace(KPDRace race);
	void setDiabetes(bool diabetes);
	void setHeight(double height);
	void setWeight(double weight);
	void setPrevTrans(bool prevTrans);
	void setTOD(double tod);
	void setHepC(bool hepC);
	void setInsurance(KPDInsurance insurance);

	// Compatibilities
	void setStatus(bool status);
	void setFailureProbability(double prob);

	void setExcludedDonors(QVector<int> donors);

	void setMatches(QSet<KPDGUIMatch *> matches);

	// Comment
	void setComment(QString comment);


	/// Visual Properties ///

	QPointF getCandidatePosition();
	void setCandidatePosition(QPointF point);
	
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	

	/// Strings ///

	QString candidateString();
	QString compatibilitiesString();
	QString excludedDonorString();
	QString hlaString();

};

QDataStream &operator<<(QDataStream &out, const KPDGUICandidate & candidate);

QDataStream &operator>>(QDataStream &in, KPDGUICandidate & candidate);

#endif