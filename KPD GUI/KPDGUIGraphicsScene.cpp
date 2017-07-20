#include "KPDGUIGraphicsScene.h"


KPDGUIGraphicsScene::KPDGUIGraphicsScene() : QGraphicsScene()
{
	setBackgroundBrush(QBrush(Qt::lightGray, Qt::Dense4Pattern));
	nodePlacementSequenceNumber = 0;
	zValue = 1;
		
	createActions();
}

KPDGUIGraphicsScene::~KPDGUIGraphicsScene()
{
	nodePlacementSequenceNumber = 1;
}

void KPDGUIGraphicsScene::addNode(KPDGUINode * node) {

	QPointF position(0, 0);

	int h_offset = rand() % 50 - 25;
	int v_offset = rand() % 50 - 25;
	position.setX(100 + 150 * (nodePlacementSequenceNumber % 10) + h_offset);
	position.setY(100 + 150 * ((nodePlacementSequenceNumber / 10) % 10) + v_offset);
	nodePlacementSequenceNumber++;

	node->setNodePosition(position);

	if (node->getType() == PAIR) {
		addItem(node->getCandidate());

		foreach(KPDGUIDonor * donor, node->getDonors()) {
			addItem(donor);
		}
	}

	else {
		addItem(node->getFirstDonor());
	}
}

void KPDGUIGraphicsScene::addNodes(QVector<KPDGUINode *> nodes, QString layout) {

	int nodesAdded = (int)nodes.size();

	qreal dist = 100 + 10 * nodesAdded;
	qreal angle = (2 * PI) / nodesAdded;
	qreal nodeAngle = PI;
	
	foreach(KPDGUINode * node, nodes) {

		QPointF position(0, 0);

		if (layout == "Circle") {
			position.setX(dist*cos(nodeAngle));
			position.setY(dist*sin(nodeAngle));
			nodeAngle += angle;
		}
		else {
			int h_offset = rand() % 50 - 25;
			int v_offset = rand() % 50 - 25;
			position.setX(150 + 150 * (nodePlacementSequenceNumber % 10) + h_offset);
			position.setY(150 + 1500 * ((nodePlacementSequenceNumber / 10) % 10) + v_offset);
			nodePlacementSequenceNumber++;

			qDebug() << nodePlacementSequenceNumber << " " << position.x() << " " << position.y();

		}

		node->setNodePosition(position);

		if (node->getType() == PAIR) {
			addItem(node->getCandidate());

			foreach(KPDGUIDonor * donor, node->getDonors()) {
				addItem(donor);
			}
		}

		else {
			addItem(node->getFirstDonor());
		}
	}
}

void KPDGUIGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	QMenu menu(event->widget());
	QList<QGraphicsItem*> items = selectedItems();

	if (selectedItems().size() >= 2){
		menu.addAction(clusterAction);
	}

	else if (selectedItems().size() == 1){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		if (node){
			menu.addAction(editAction);
			menu.addAction(changeStatusAction);
		}
	}

	else {
		menu.addAction(selectAllAction);
	}

	menu.exec(event->screenPos());
}

void KPDGUIGraphicsScene::edit(){
	QList<QGraphicsItem*> items = selectedItems();
	if (items.size() == 1){
		//KPDGUINode *node = dynamic_cast<KPDGUINode *>(items.first());
		//if (node){
			//node->editNode();			
		//}
		qDebug() << "EDIT 1 THING!";
	}
}


void KPDGUIGraphicsScene::cluster() {

	qreal avgx = 0;
	qreal avgy = 0;
	qreal dist = 50+10*selectedItems().size();

	QList<QGraphicsItem*> items = selectedItems();
	foreach(QGraphicsItem * item, items){
		KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		if (node){
			avgx += node->getNodePosition().x();
			avgy += node->getNodePosition().y();
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
			//node->setVisible(false);
			if (!(abs((node->getNodePosition().x()) - (x + dist*cos(nodeAngle))) < TOL && abs((node->getNodePosition().y()) - (y + dist*sin(nodeAngle)) < TOL))){
				node->setNodePosition(QPoint(x + dist*cos(nodeAngle), y + dist*sin(nodeAngle)));
			}
			nodeAngle += angle;
			//node->setVisible(true);
			
			node->setSelected(true);
		}
	}

	QApplication::restoreOverrideCursor();
	QApplication::processEvents();
}

void KPDGUIGraphicsScene::changeStatus() {
	
	KPDGUIDonor * d = dynamic_cast<KPDGUIDonor *>(selectedItems().first());
	if (d) {

		bool currentStatus = d->getStatus();

		d->setStatus(!currentStatus);
	}
	else {
		KPDGUICandidate * c = dynamic_cast<KPDGUICandidate *>(selectedItems().first());

		if (c) {

			bool currentStatus = c->getStatus();

			c->setStatus(!currentStatus);
		}
	}
}

void KPDGUIGraphicsScene::selectAll() {
	qDebug() << "SELECT ALL!";
}

void KPDGUIGraphicsScene::createActions(){
	
	editAction = new QAction(tr("&Edit"), this);
	connect(editAction, SIGNAL(triggered()), this, SLOT(edit()));

	changeStatusAction = new QAction(tr("&Change Status"), this);
	connect(changeStatusAction, SIGNAL(triggered()), this, SLOT(changeStatus()));
	
	clusterAction = new QAction(tr("&Cluster Selection"), this);
	connect(clusterAction, SIGNAL(triggered()), this, SLOT(cluster()));

	selectAllAction = new QAction(tr("&Select All"), this);
	connect(selectAllAction, SIGNAL(triggered()), this, SLOT(selectAll()));
}

void KPDGUIGraphicsScene::raiseZValue() {
	zValue++;

	foreach(QGraphicsItem * item, selectedItems()) {
		item->setZValue(zValue);
	}
}