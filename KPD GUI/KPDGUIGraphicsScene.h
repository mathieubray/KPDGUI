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

	
protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);


private slots:

	void edit();
	void changeStatus();

	void cluster();

	void selectAll();


private:

	int zValue;
	int nodePlacementSequenceNumber;

	void createActions();
	
	QAction * editAction;
	QAction * changeStatusAction;

	QAction * clusterAction;

	QAction * selectAllAction;

};

#endif
