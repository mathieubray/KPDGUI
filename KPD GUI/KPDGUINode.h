#ifndef KPDGUINODE_H
#define KPDGUINODE_H

#include <QtGui>
#include <QtWidgets>

#include "Structs.h"

class KPDGUIArrow;
class PairDialog;
class ADDialog;

class KPDGUINode : public QGraphicsObject
{
	Q_OBJECT

public:
	KPDGUINode();
	KPDGUINode(Donor d, Candidate c, QString commentString, bool hold = false);
	~KPDGUINode();

	//Visual Node Properties
    void setText(const QString &text);
    QString text() const;
    void setTextColor(const QColor &color);
    QColor textColor() const;
    void setOutlineColor(const QColor &color);
    QColor outlineColor() const;
    void setBackgroundColor();
    QColor backgroundColor() const;
	QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	//Arrow Properties
	void addInArrow(KPDGUIArrow *link);
	void removeInArrow(KPDGUIArrow *link);
	void addOutArrow(KPDGUIArrow *link);
	void removeOutArrow(KPDGUIArrow *link);
	KPDGUIArrow * findOutArrow(KPDGUINode * toNode);
	void setEnhancedHighlight(int secondID);
	    
	//Compatibilities
	bool hasNoCompatibilities();
	bool hasNoAvailableCompatibilities();
	int getNumberOfCompatibilities();
	int getNumberOfCompatibleDonors();
	int getNumberOfCompatibleRecipients();

	//Popularity
	int getPopularityInStructures();
	int getPopularityInSolutions();	
	void increasePopularityInStructures();
	void increasePopularityInSolutions();
	void decreasePopularityInStructures();
	void decreasePopularityInSolutions();
	void resetPopularityInStructures();
	void resetPopularityInSolutions();

	//Hold Status
	bool getHoldStatus() const;
	void setHoldStatus(bool hold);
	bool isOnHold();

	//Node Properties
	int getInternalID() const;
	void setInternalID(int id);
	void setDonor(Donor d);
	void setCandidate(Candidate c);
	KPDPairType getType() const;
	
	QString getDonorName() const;
	QString getRecipName() const;
	int getDonorAge() const;
	int getRecipAge() const;
	QString getDonorBT() const;
	QString getRecipBT() const;
	int getRecipPRA() const;

	double getRecipBMI() const;
	bool getRecipDiabetes() const;
	bool getRecipGenderMale() const;
	double getRecipWeight() const;
	QString getRecipRace() const;
	bool getRecipPrevTrans() const;
	double getRecipTOD() const;
	bool getRecipHepC() const;
		
	double getDonorBMI() const;
	bool getDonorGenderMale() const;
	double getDonorWeight() const;

	void setDonorName(QString name);
	void setRecipName(QString name);
	void setDonorAge(int age);
	void setRecipAge(int age);
	void setDonorBT(QString bt);
	void setRecipBT(QString bt);
	void setRecipPRA(int age);

	void setRecipBMI(double bmi);
	void setRecipDiabetes(bool diabetes);
	void setRecipGenderMale(bool genderMale);
	void setRecipWeight(double weight);
	void setRecipRace(QString race);
	void setRecipPrevTrans(bool prevTrans);
	void setRecipTOD(double tod);
	void setRecipHepC(bool hepC);
	
	void setDonorBMI(double bmi);
	void setDonorGenderMale(bool genderMale);
	void setDonorWeight(double weight );

	QVector<QString> getDonorAVector() const;
	QVector<QString> getDonorBVector() const;
	QVector<QString> getDonorCWVector() const;
	QVector<QString> getDonorDPVector() const;
	QVector<QString> getDonorDQVector() const;
	QVector<QString> getDonorDRVector() const;
	bool getDonorBW4() const;
	bool getDonorBW6() const;
	bool getDonorDR51() const;
	bool getDonorDR52() const;
	bool getDonorDR53() const;

	QVector<QString> getRecipAntibodies() const;

	QString getDonorHLAString();
	QString getRecipHLAString();
		
	Candidate * getCandidatePtr();
	Donor * getDonorPtr();

	QString getComment() const;
	void setComment(QString commentString);

	//Console Text
	QString getCompatibleDonorString();
	QString getCompatibleRecipientsString();
	QString getConsoleString();

signals:
	void nodeWasClicked(int i, bool selected);
	void nodeSelectionChanged(int i, bool selected);
	void nodeHoldStatusChanged(int i, bool held);
	void nodeEdited(int i);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

private:
	//Helper Functions
    QRectF outlineRect() const;
	bool checkWithinBounds(bool pairsWithMinPRA, int minPRA, bool pairsWithMaxPRA, int maxPRA);

	//Node Visual Properties
    QString myText;
    QColor myTextColor;
	QColor myOutlineColor;
    QColor myBackgroundColor;
	
	//Arrows
	QSet<KPDGUIArrow *> myOutArrows;
	QSet<KPDGUIArrow *> myInArrows;

	//Properties
	int popularityInStructures;
	int popularityInSolutions;

	//Hold Status
	bool holdStatus;

	//Node Properties
	int internalID;	
	Donor donor;
	Candidate candidate;
	QString comment;
	

public slots:
	void updateVisibility(DisplaySettingsStruct * displaySettings);

};

QDataStream &operator<<(QDataStream &out, const KPDGUINode & node);

QDataStream &operator>>(QDataStream &in, KPDGUINode & node);

#endif
