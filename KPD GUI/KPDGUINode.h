#ifndef KPDGUINODE_H
#define KPDGUINODE_H

#include <QtGui>
#include <QtWidgets>

#include "KPDGUIDonorInfo.h"
#include "KPDGUICandidateInfo.h"

#include "KPDGUIDisplaySettings.h"
#include "KPDGUIPairModelItem.h"

#include "EnumsFunctions.h"

class KPDGUIMatch;
class DialogDonor;
class DialogCandidate;

class KPDGUINode : public QObject, public QGraphicsItemGroup
{
	Q_OBJECT

private:
	
	//Node Properties
	int nodeID;
	KPDNodeType myType;

	QVector<KPDGUIDonorInfo *> myDonors;
	KPDGUICandidateInfo * myCandidate;

	QVector<bool> myDonorStatuses;
	bool myCandidateStatus;
	
	QVector<QString> myPrograms;
	
	//Visual Properties
	QVector<QGraphicsEllipseItem *> myDonorItems;
	QGraphicsEllipseItem * myCandidateItem;

	QString myText;
	QVector<QColor> myDonorBackgroundColors;
	QColor myCandidateBackgroundColor;

	//Matches
	QSet<KPDGUIMatch *> myCompatibleDonorMatches;
	QVector<QSet<KPDGUIMatch *>  > myCompatibleCandidateMatches;

	//Popularity
	int popularityInStructures;
	int popularityInSolutions;	

	//Helper Functions
	// QRectF outlineRect() const;


public:
	
	KPDGUINode();
	KPDGUINode(KPDGUIDonorInfo* donor);
	KPDGUINode(QVector<KPDGUIDonorInfo*> donors, KPDGUICandidateInfo * candidate);
	~KPDGUINode();

	////Node Properties
	
	//Getters
	int getNodeID() const;
	KPDNodeType getNodeType() const;

	KPDGUIDonorInfo* getDonor(int i) const;
	QVector<KPDGUIDonorInfo*> getDonors() const;
	int getNumberOfDonors() const;
	
	KPDGUICandidateInfo * getCandidate() const;
	
	bool getDonorStatus(int i) const;
	bool getCandidateStatus() const;
	bool getNodeStatus();

	QVector<QString> getPrograms() const;
	int getNumberOfPrograms() const;

	//Setters
	void setNodeID(int id);
	void setNodeType(KPDNodeType type);

	void setDonors(QVector<KPDGUIDonorInfo*> donors);
	void addDonor(KPDGUIDonorInfo* d);
	void removeDonor(int i);
	
	void setCandidate(KPDGUICandidateInfo * c);

	void setDonorStatus(int i, bool status);
	void setCandidateStatus(bool status);
	
	void setPrograms(QVector<QString> programs);
	void addProgram(QString program);
	void removeProgram(QString program);
	
	//// Visual Properties
	QGraphicsEllipseItem * getDonorItem(int i);
	QGraphicsEllipseItem * getCandidateItem();

	QPointF getDonorCenter(int i);
	QPointF getCandidateCenter();

	QString text() const;
	void setText(const QString &text);
    void setBackgroundColors();
    QColor donorBackgroundColor(int i) const;
	QColor candidateBackgroundColor() const;
	//QRectF boundingRect() const;
    //QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	//QVariant data(int column) const;

	//// Matches
	void addDonorMatch(KPDGUIMatch * match);
	void removeDonorMatch(KPDGUIMatch * match);
	void addCandidateMatch(KPDGUIMatch * match, int i);
	void removeCandidateMatch(KPDGUIMatch * match, int i);	
	KPDGUIMatch * findDonorMatch(KPDGUINode * fromNode);
	KPDGUIMatch * findCandidateMatch(KPDGUINode * toNode, int i);
	    
	bool hasNoCompatibilities();
	int getNumberOfCompatibilities();
	int getNumberOfCompatibleDonors();
	int getNumberOfCompatibleCandidates();

	//// Popularity
	int getPopularityInStructures();
	int getPopularityInSolutions();	
	void increasePopularityInStructures();
	void increasePopularityInSolutions();
	void decreasePopularityInStructures();
	void decreasePopularityInSolutions();
	void resetPopularityInStructures();
	void resetPopularityInSolutions();

	//Text
	QString getNameString();
	QString getCompatibleDonorString();
	QString getCompatibleCandidatesString();
	QString getDashboardString();	

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


	void setAdditionalProperties();
	bool checkWithinBounds(int minPRA, int maxPRA);

public slots:
	void updateVisibility(KPDGUIDisplaySettings * displaySettings);
	void selectIfVisible();

	void editNode();

};

QDataStream &operator<<(QDataStream &out, const KPDGUINode & node);

QDataStream &operator>>(QDataStream &in, KPDGUINode & node);

#endif
