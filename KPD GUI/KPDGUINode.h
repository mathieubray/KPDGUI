#ifndef KPDGUINODE_H
#define KPDGUINODE_H

#include <QtGui>
#include <QtWidgets>

#include "KPDGUIDonor.h"
#include "KPDGUICandidate.h"

#include "KPDGUIDisplaySettings.h"
#include "KPDGUIPairModelItem.h"

#include "EnumsFunctions.h"

class KPDGUIMatch;
class DialogDonor;
class DialogCandidate;

class KPDGUINode : public QObject
{
	Q_OBJECT;

private:
	
	int nodeID;
	KPDNodeType nodeType;

	QVector<KPDGUIDonor *> nodeDonors;
	KPDGUICandidate * nodeCandidate;
	
	QVector<QString> nodePrograms;
	

public slots:

	void updateVisibility(KPDGUIDisplaySettings * displaySettings);
	void clusterNode();
	void highlightNode();
	void clearHighlight();

public:
	
	KPDGUINode();
	KPDGUINode(KPDGUIDonor* donor);
	KPDGUINode(QVector<KPDGUIDonor*> donors, KPDGUICandidate * candidate);
	~KPDGUINode();
		
	//Getters
	int getID() const;
	KPDNodeType getType() const;

	QVector<KPDGUIDonor *> getDonors() const;
	KPDGUIDonor * getFirstDonor() const;
	int getNumberOfDonors() const;
	
	KPDGUICandidate * getCandidate() const;
	
	bool getStatus();

	QVector<QString> getPrograms() const;
	int getNumberOfPrograms() const;


	//Setters
	void setID(int id);
	void setType(KPDNodeType type);

	void setDonors(QVector<KPDGUIDonor*> donors);
	void addDonor(KPDGUIDonor * donor);
	void removeDonor(KPDGUIDonor * donor);
	
	void setCandidate(KPDGUICandidate * candidate);
	
	void setPrograms(QVector<QString> programs);
	void addProgram(QString program);
	void removeProgram(QString program);
		


	// Visual Properties

	
	QPointF getNodePosition();
	void setNodePosition(QPointF center);
	void setSelected(bool selected);
	void updateNodeVisibility(KPDGUIDisplaySettings * displaySettings);

	void setZValue(int z);


	//Text
	QString getNameString();
	QString getNodeListString();
	QString getDashboardString();	


};

QDataStream &operator<<(QDataStream &out, const KPDGUINode & node);

QDataStream &operator>>(QDataStream &in, KPDGUINode & node);

#endif
