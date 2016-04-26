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
	
protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private slots:
	/*void addAssociatedDonor();
	void highlightRelevantStructures();
	void highlightRelevantSolutions();
	void editNode();
	void holdNode();
	void unholdNode();
	void deleteNode();

	void holdMultipleNodes();
	void unholdMultipleNodes();
	void clusterMultipleNodes();
	void deleteMultipleNodes();

	void selectAll();
	void clearHighlights();*/

private:

	//int mode;

	//void createNodeActions();
	
	/*QAction * addAssociatedDonorAction;
	QAction * highlightStructuresAction;
	QAction * highlightSolutionsAction;
	QAction * editNodeAction;
	QAction * holdNodeAction;
	QAction * unholdNodeAction;
	QAction * deleteNodeAction;

	QAction * holdMultipleNodesAction;
	QAction * unholdMultipleNodesAction;
	QAction * clusterMultipleNodesAction;
	QAction * deleteMultipleNodesAction;

	QAction * selectAllAction;
	QAction * clearHighlightsAction;*/

	//QStringList hlaList;

};

#endif
