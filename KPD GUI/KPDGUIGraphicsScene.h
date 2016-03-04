#ifndef KPDGUIGRAPHICSSCENE_H
#define KPDGUIGRAPHICSSCENE_H

#include <QtGui>
#include <QGraphicsScene>
#include <QMenu>
#include <QGraphicsSceneEvent>
#include <QMessageBox>

#include "KPDGUINode.h"

//#include "DialogPair.h"
#include "DialogDonor.h"

class KPDGUIGraphicsScene : public QGraphicsScene 
{
	Q_OBJECT

public:
	KPDGUIGraphicsScene();
	~KPDGUIGraphicsScene();	

	//void changeMode(int i);
	//void setHLAList(QStringList hla);

protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	//void wheelEvent(QGraphicsSceneWheelEvent *event);

signals:
	void addAssociatedDonor(int i);
	void highlightRelevantStructures(int i);
	void highlightRelevantSolutions(int i);
	void selectAllVisibleNodes();
	void clearAllHighlights();
	void deleteNode(int i);
	void editNode(int i);
	void screenChanged();
	
	//void zoomIn();
	//void zoomOut();
	void mouseReleased();

private slots:
	void addAssociatedDonor();
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
	void clearHighlights();

private:

	//int mode;

	void createNodeActions();
	
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
