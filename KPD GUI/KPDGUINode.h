#ifndef KPDGUINODE_H
#define KPDGUINODE_H

#include <QtGui>
#include <QtWidgets>

#include "KPDGUIDisplaySettings.h"
#include "KPDGUIPairModelItem.h"

#include "EnumsFunctions.h"
#include "Donor.h"
#include "Candidate.h"

class KPDGUIArrow;
class DialogDonor;
class DialogCandidate;

class KPDGUINode : public QObject, public QGraphicsItemGroup
{
	Q_OBJECT

public:
	KPDGUINode();
	KPDGUINode(Donor d, bool hold = false);
	KPDGUINode(Donor d, Candidate c, bool hold = false);
	~KPDGUINode();

	//Visual Node Properties
    void setText(const QString &text);
    QString text() const;
    void setBackgroundColors();
    QColor donorBackgroundColor() const;
	QColor recipBackgroundColor() const;
	//QRectF boundingRect() const;
    //QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	//QVariant data(int column) const;

	//Arrow Properties
	void addInArrow(KPDGUIArrow *link);
	void removeInArrow(KPDGUIArrow *link);
	void addOutArrow(KPDGUIArrow *link);
	void removeOutArrow(KPDGUIArrow *link);
	KPDGUIArrow * findOutArrow(KPDGUINode * toNode);
	    
	//Compatibilities
	bool hasNoCompatibilities();
	int getNumberOfCompatibilities();
	int getNumberOfCompatibleDonors();
	int getNumberOfCompatibleRecipients();
	int getNumberOfAssociatedDonors();

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

	//Node Properties	

	int getInternalID() const;
	Donor getDonor() const;
	Candidate getCandidate() const;
	KPDPairType getType() const;

	QString getDonorName() const;
	int	getDonorAge() const;
	KPDBloodType getDonorBT() const;
	QString	getCandidateName() const;
	int	getCandidateAge() const;
	KPDBloodType getCandidateBT() const;
	int	getCandidatePRA() const;		

	void setInternalID(int id);
	void setDonor(Donor d);
	void setCandidate(Candidate c);
	void setType(KPDPairType type);
	
	void editNode();

	QGraphicsEllipseItem * getDonorItem();
	QGraphicsEllipseItem * getRecipItem();

	QPointF getDonorCenter();
	QPointF getRecipCenter();

	//Text
	QString getNameString();
	QString getCompatibleDonorString();
	QString getCompatibleRecipientsString();
	QString getConsoleString();

signals:
	void nodeWasClicked(int i, bool selected);
	void nodeSelectionChanged(int i, bool selected);
	void nodeHoldStatusChanged(int i, bool held);
	void nodeEdited(int i);
	void nodeEntered(int i);
	void nodeLeft(int i);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
	void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event);

private:
	void setAdditionalProperties();

	//Helper Functions
   // QRectF outlineRect() const;
	bool checkWithinBounds(bool pairsWithMinPRA, int minPRA, bool pairsWithMaxPRA, int maxPRA);

	//Node Visual Properties
    QString myText;
    QColor myDonorBackgroundColor;
	QColor myRecipBackgroundColor;
	
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
	KPDPairType pairType;

	QGraphicsEllipseItem * myRecip;
	QGraphicsEllipseItem * myDonor;
	

public slots:
	void updateVisibility(KPDGUIDisplaySettings * displaySettings);
	void selectIfVisible();

};

QDataStream &operator<<(QDataStream &out, const KPDGUINode & node);

QDataStream &operator>>(QDataStream &in, KPDGUINode & node);

#endif
