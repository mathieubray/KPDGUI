#ifndef KPDGUIGRAPHICSSCENE_H
#define KPDGUIGRAPHICSSCENE_H

#include <QtGui>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneEvent>
#include <QMessageBox>

#include "KPDGUINode.h"
#include "DialogPair.h"
#include "DialogAD.h"

class KPDGUIGraphicsScene : public QGraphicsScene 
{
	Q_OBJECT

public:
	KPDGUIGraphicsScene();
	~KPDGUIGraphicsScene();	

	//void changeMode(int i);

protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	//void wheelEvent(QGraphicsSceneWheelEvent *event);

signals:
	void deleteNode(int i);
	void editNode(int i);
	void screenChanged();
	
	//void zoomIn();
	//void zoomOut();
	void mouseReleased();

private slots:
	void editNode();
	void holdNode();
	void unholdNode();
	void deleteNode();

	void holdMultipleNodes();
	void unholdMultipleNodes();
	void clusterMultipleNodes();
	void deleteMultipleNodes();

private:

	//int mode;

	void createNodeActions();
	

	QAction * editNodeAction;
	QAction * holdNodeAction;
	QAction * unholdNodeAction;
	QAction * deleteNodeAction;

	QAction * holdMultipleNodesAction;
	QAction * unholdMultipleNodesAction;
	QAction * clusterMultipleNodesAction;
	QAction * deleteMultipleNodesAction;

};

#endif
