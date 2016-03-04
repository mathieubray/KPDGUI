#include "KPDGUIGraphicsScene.h"

//const qreal PI = 3.14159265;
//const qreal TOL = 3;

KPDGUIGraphicsScene::KPDGUIGraphicsScene() : QGraphicsScene()
{
	//setBackgroundBrush(QBrush(Qt::lightGray, Qt::Dense7Pattern));
		
	createNodeActions();
}

KPDGUIGraphicsScene::~KPDGUIGraphicsScene()
{

}

/*void KPDGUIGraphicsScene::setHLAList(QStringList list)
{
	foreach(QString hla, list){
		hlaList.push_back(hla);
	}
}*/

/*void KPDGUIGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseReleaseEvent(event);

	emit mouseReleased();
}*/

void KPDGUIGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	/*QMenu menu(event->widget());
	QList<QGraphicsItem*> items = selectedItems();

	if (selectedItems().size() >= 2){
		bool allHeld = true;
		foreach(QGraphicsItem * item, items){
			KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
			if (!node->getHoldStatus()){
				allHeld = false;
			}
		}
		menu.addAction(clusterMultipleNodesAction);
		menu.addSeparator();
		if (allHeld){
			menu.addAction(unholdMultipleNodesAction);
		}
		else {
			menu.addAction(holdMultipleNodesAction);
		}
		
		menu.addAction(deleteMultipleNodesAction);
	}

	else if (selectedItems().size() == 1){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){
			menu.addAction(addAssociatedDonorAction);
			menu.addAction(highlightStructuresAction);
			menu.addAction(highlightSolutionsAction);
			menu.addAction(editNodeAction);
			menu.addSeparator();
			if (node->getHoldStatus()){
				menu.addAction(unholdNodeAction);
			}
			else {
				menu.addAction(holdNodeAction);
			}
			menu.addAction(deleteNodeAction);
		}
	}

	else {
		menu.addAction(selectAllAction);
		menu.addAction(clearHighlightsAction);
	}

	menu.exec(event->screenPos());*/
}
/*
void KPDGUIGraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *event){
	if (mode == 0){
		QGraphicsScene::wheelEvent(event);
	}
	else {
		if (event->delta() > 0){
			emit zoomIn();
		}
		else {
			emit zoomOut();
		}
	}

}
*/
void KPDGUIGraphicsScene::addAssociatedDonor(){
	QList<QGraphicsItem*> items = selectedItems();
	if (items.size() == 1){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){
			emit addAssociatedDonor(node->getInternalID());
			//qDebug() << "Triggered";
		}
	}
}

void KPDGUIGraphicsScene::highlightRelevantStructures(){
	QList<QGraphicsItem *> items = selectedItems();
	if (items.size() == 1){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){
			emit highlightRelevantStructures(node->getInternalID());
		}
	}
}

void KPDGUIGraphicsScene::highlightRelevantSolutions(){
	QList<QGraphicsItem *> items = selectedItems();
	if (items.size() == 1){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){
			emit highlightRelevantSolutions(node->getInternalID());
		}
	}
}

void KPDGUIGraphicsScene::selectAll(){
	emit selectAllVisibleNodes();
}

void KPDGUIGraphicsScene::clearHighlights(){
	emit clearAllHighlights();
}

void KPDGUIGraphicsScene::editNode(){
	QList<QGraphicsItem*> items = selectedItems();
	if (items.size() == 1){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){
			node->editNode();
			
		}
	}
}

void KPDGUIGraphicsScene::holdNode(){
	QList<QGraphicsItem*> items = selectedItems();
	KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
	if (node){
		node->setHoldStatus(true);
		emit screenChanged();
	}	
}

void KPDGUIGraphicsScene::unholdNode(){
	QList<QGraphicsItem*> items = selectedItems();
	KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
	if (node){
		node->setHoldStatus(false);
		emit screenChanged();
	}	
}

void KPDGUIGraphicsScene::deleteNode(){
	
	int r = QMessageBox::warning(0,"KPD","Clicking 'Yes' will remove selected pair from pool and all previously found solutions permanently.\nAre you sure you want to delete selected pair?",
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {
		QList<QGraphicsItem*> items = selectedItems();
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){
			emit deleteNode(node->getInternalID());
		}
	}
}

void KPDGUIGraphicsScene::holdMultipleNodes(){
	QList<QGraphicsItem*> items = selectedItems();
	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			node->setHoldStatus(true);
			emit screenChanged();
		}
	}	
}

void KPDGUIGraphicsScene::unholdMultipleNodes(){
	QList<QGraphicsItem*> items = selectedItems();
	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			node->setHoldStatus(false);
			emit screenChanged();
		}
	}
}

void KPDGUIGraphicsScene::clusterMultipleNodes(){
	qreal avgx = 0;
	qreal avgy = 0;
	qreal dist = 50+10*selectedItems().size();

	QList<QGraphicsItem*> items = selectedItems();
	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			avgx += node->x();
			avgy += node->y();
		}
	}

	qreal x = avgx / selectedItems().size();
	qreal y = avgy / selectedItems().size();
	
	qreal angle = (2 * PI) / selectedItems().size();
	qreal nodeAngle = PI;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			node->setVisible(false);
			if (!(abs((node->x()) - (x + dist*cos(nodeAngle))) < TOL && abs((node->y()) - (y + dist*sin(nodeAngle)) < TOL))){
				node->setPos(QPoint(x + dist*cos(nodeAngle), y + dist*sin(nodeAngle)));
			}
			nodeAngle += angle;
			node->setVisible(true);
			node->setSelected(true);
		}
	}

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();
}

void KPDGUIGraphicsScene::deleteMultipleNodes(){

	int r = QMessageBox::warning(0, "KPD", "Clicking \"Yes\" will remove selected pairs from pool and all previously found solutions permanently.\nAre you sure you want to delete selected pairs?",
		QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	if (r == QMessageBox::Yes) {
		QApplication::setOverrideCursor(Qt::WaitCursor);
		QApplication::processEvents();
		QList<QGraphicsItem*> items = selectedItems();
		foreach(QGraphicsItem * item, items){
			KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
			if (node){
				node->setSelected(false);
			}
		}
		foreach(QGraphicsItem * item, items){
			KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
			if (node){
				emit deleteNode(node->getInternalID());
			}
		}
		QApplication::restoreOverrideCursor();
		QApplication::processEvents();
	}	
}

void KPDGUIGraphicsScene::createNodeActions(){
	
	/*addAssociatedDonorAction = new QAction(tr("&Add Additional Donor"), this);
	//connect(addAssociatedDonorAction, SIGNAL(triggered()), this, SLOT(addAssociatedDonor()));

	highlightStructuresAction = new QAction(tr("&Highlight Structures"), this);
	//connect(highlightStructuresAction, SIGNAL(triggered()), this, SLOT(highlightRelevantStructures()));

	highlightSolutionsAction = new QAction(tr("&Highlight Solutions"), this);
	//connect(highlightSolutionsAction, SIGNAL(triggered()), this, SLOT(highlightRelevantSolutions()));

	selectAllAction = new QAction(tr("&Select All"), this);
	//connect(selectAllAction, SIGNAL(triggered()), this, SLOT(selectAll()));

	clearHighlightsAction = new QAction(tr("&Clear Highlights"), this);
	//connect(clearHighlightsAction, SIGNAL(triggered()), this, SLOT(clearHighlights()));

	editNodeAction = new QAction(tr("&Edit"), this);
	//connect(editNodeAction, SIGNAL(triggered()), this, SLOT(editNode()));

	holdNodeAction = new QAction(tr("&Hold"), this);
	//connect(holdNodeAction, SIGNAL(triggered()), this, SLOT(holdNode()));

	unholdNodeAction = new QAction(tr("&Unhold"), this);
	//connect(unholdNodeAction, SIGNAL(triggered()), this, SLOT(unholdNode()));

	deleteNodeAction = new QAction(tr("&Delete"), this);
	//connect(deleteNodeAction, SIGNAL(triggered()), this, SLOT(deleteNode()));

	holdMultipleNodesAction = new QAction(tr("&Hold Selected Pairs"), this);
	//connect(holdMultipleNodesAction, SIGNAL(triggered()), this, SLOT(holdMultipleNodes()));

	unholdMultipleNodesAction = new QAction(tr("&Unhold Selected Pairs"), this);
	//connect(unholdMultipleNodesAction, SIGNAL(triggered()), this, SLOT(unholdMultipleNodes()));

	clusterMultipleNodesAction = new QAction(tr("&Cluster Selected Pairs"), this);
	//connect(clusterMultipleNodesAction, SIGNAL(triggered()), this, SLOT(clusterMultipleNodes()));

	deleteMultipleNodesAction = new QAction(tr("&Delete Selected Pairs"), this);
	//connect(deleteMultipleNodesAction, SIGNAL(triggered()), this, SLOT(deleteMultipleNodes()));*/
}
/*
void KPDGUIGraphicsScene::changeMode(int i){
	mode = i;
}
*/