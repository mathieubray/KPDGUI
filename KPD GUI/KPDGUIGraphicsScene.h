#ifndef KPDGUIGRAPHICSSCENE_H
#define KPDGUIGRAPHICSSCENE_H

#include <QtGui>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneEvent>
#include <QMessageBox>

#include "KPDGUINode.h"

class KPDGUIGraphicsScene : public QGraphicsScene 
{
	Q_OBJECT

public:
	KPDGUIGraphicsScene();
	~KPDGUIGraphicsScene();	

	void addNode(KPDGUINode * node);
	void addNodes(QVector<KPDGUINode *> nodes, QString layout);
	
	void raiseZValue();

signals:
	void updateVisibilitySignal();

	void addNewDonorSignal(KPDGUICandidate * candidate);

	void selectionClustered(int x, int y);
	
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);


private slots:

	void edit();
	void addAdditionalDonor();
	void changeStatus();

	void cluster();

	void selectAll();


private:

	int zValue;
	int nodePlacementSequenceNumber;

};

#endif
