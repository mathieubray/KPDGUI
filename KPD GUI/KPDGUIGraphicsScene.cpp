#include "KPDGUIGraphicsScene.h"


KPDGUIGraphicsScene::KPDGUIGraphicsScene() : QGraphicsScene()
{
	nodePlacementSequenceNumber = 0;
	zValue = 1;
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
			position.setX(150 + 150 * (nodePlacementSequenceNumber % 16) + h_offset);
			position.setY(150 + 150 * ((nodePlacementSequenceNumber / 16) % 16) + v_offset);
			nodePlacementSequenceNumber++;

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

void KPDGUIGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {

	if (event->button() == Qt::RightButton) {
		
		QGraphicsItem * item = itemAt(event->scenePos(), QTransform());
		if (item) {
			KPDGUIDonor * donor = dynamic_cast<KPDGUIDonor *>(item);
			if (donor) {

				donor->setSelected(true);

				emit updateVisibilitySignal();
			}

			KPDGUICandidate * candidate = dynamic_cast<KPDGUICandidate *>(item);
			if (candidate) {
				
				if (!candidate->isSelected()) {
					qDebug() << "Before: Not Selected:";
				}
				
				candidate->setSelected(true);
				
				if (candidate->isSelected()) {
					qDebug() << "After: Selected";
				}

				emit updateVisibilitySignal();
			}
		}


		QGraphicsScene::mousePressEvent(event);
	}

	else {

		QGraphicsScene::mousePressEvent(event);

		emit updateVisibilitySignal();
	}
}

void KPDGUIGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * event) {

	emit updateVisibilitySignal();

	QGraphicsScene::mouseReleaseEvent(event);

}

void KPDGUIGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{

	QMenu menu(event->widget());
	QList<QGraphicsItem*> items = selectedItems();

	//int nCandidates = 0;

	//foreach(QGraphicsItem * item, items) {

	//	KPDGUICandidate * candidate = dynamic_cast<KPDGUICandidate *>(item);
	//	if (candidate) {
	//		nCandidates++;
	//	}
	//}

	QList<KPDGUINode *> nodes;

	foreach(QGraphicsItem * item, items) {
		KPDGUICandidate * candidate = dynamic_cast<KPDGUICandidate *>(item);
		if (candidate) {
			nodes << candidate->getParentNode();
		}

		KPDGUIDonor * donor = dynamic_cast<KPDGUIDonor *>(item);
		if (donor) {
			if (donor->isAltruistic()) {
				nodes << donor->getParentNode();
			}
		}
	}

	if (nodes.size() >= 2){

		QAction * clusterAction = new QAction(tr("&Cluster Selection"), this);
		connect(clusterAction, SIGNAL(triggered()), this, SLOT(cluster()));

		menu.addAction(clusterAction);
	}

	else if (nodes.size() == 1){

		bool altruistic = false;

		foreach(QGraphicsItem * item, items) {
			KPDGUICandidate *candidate = dynamic_cast<KPDGUICandidate *>(item);
			if (candidate) {

				QAction * editAction = new QAction("Edit Candidate " + candidate->candidateString(), this);
				connect(editAction, SIGNAL(triggered()), candidate, SLOT(edit()));


				menu.addAction(editAction);
				//menu.addAction(changeStatusAction);
			}
			else {
				KPDGUIDonor *donor = dynamic_cast<KPDGUIDonor *>(item);
				if (donor) {

					if (donor->isAltruistic()) {
						altruistic = true;
					}

					QAction * editAction = new QAction("Edit Donor " + donor->donorString(), this);
					connect(editAction, SIGNAL(triggered()), donor, SLOT(edit()));

					menu.addAction(editAction);
					//menu.addAction(changeStatusAction);
				}
			}			
		}	

		if (!altruistic) {
			QAction * addAdditionalDonorAction = new QAction("Add Additional Donor", this);
			connect(addAdditionalDonorAction, SIGNAL(triggered()), this, SLOT(addAdditionalDonor()));

			menu.addSeparator();
			menu.addAction(addAdditionalDonorAction);
		}
	}

	else {

		QAction * selectAllAction = new QAction(tr("&Select All"), this);
		connect(selectAllAction, SIGNAL(triggered()), this, SLOT(selectAll()));

		menu.addAction(selectAllAction);
	}

	menu.exec(event->screenPos());
}

void KPDGUIGraphicsScene::addAdditionalDonor() {

	QList<QGraphicsItem*> items = selectedItems();
	
	foreach(QGraphicsItem * item, items) {
		KPDGUICandidate * candidate = dynamic_cast<KPDGUICandidate *>(item);
		if (candidate) {

			candidate->addAdditionalDonor();
			//emit addNewDonorSignal(candidate);

			break;
		}
	}


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
	qreal dist = 50+DEFAULT_CLUSTER_SPREAD*selectedItems().size();

	QList<QGraphicsItem*> items = selectedItems();

	QList<KPDGUINode*> nodes;

	foreach(QGraphicsItem * item, items) {
		KPDGUICandidate * candidate = dynamic_cast<KPDGUICandidate *>(item);
		if (candidate) {
			nodes << candidate->getParentNode();
		}

		KPDGUIDonor * donor = dynamic_cast<KPDGUIDonor *>(item);
		if (donor) {
			if (donor->isAltruistic()) {
				nodes << donor->getParentNode();
			}
		}
	}

	foreach(KPDGUINode * node, nodes){
		//KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		//if (node){
			avgx += node->getNodePosition().x();
			avgy += node->getNodePosition().y();
		//}
	}

	qreal x = avgx / nodes.size();
	qreal y = avgy / nodes.size();
	
	qreal angle = (2 * PI) / nodes.size();
	qreal nodeAngle = PI;

	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents();

	foreach(KPDGUINode * node, nodes){
		//KPDGUINode *node = dynamic_cast<KPDGUINode *>(item);
		//if (node){
			//node->setVisible(false);
			if (!(abs((node->getNodePosition().x()) - (x + dist*cos(nodeAngle))) < TOL && abs((node->getNodePosition().y()) - (y + dist*sin(nodeAngle)) < TOL))){
				node->setNodePosition(QPoint(x + dist*cos(nodeAngle), y + dist*sin(nodeAngle)));
			}
			nodeAngle += angle;
			//node->setVisible(true);
			
			node->setSelected(true);
		//}
	}

	emit selectionClustered(x, y);

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
	
	QList<QGraphicsItem*> sceneItems = items();
	
	foreach(QGraphicsItem * item, sceneItems) {
		KPDGUICandidate * candidate = dynamic_cast<KPDGUICandidate *>(item);
		if (candidate) {
			candidate->setSelected(true);
		}

		KPDGUIDonor * donor = dynamic_cast<KPDGUIDonor *>(item);
		if (donor) {
			if (donor->isAltruistic()) {
				donor->setSelected(true);
			}
		}
	}

}

void KPDGUIGraphicsScene::raiseZValue() {
	zValue++;

	foreach(QGraphicsItem * item, selectedItems()) {
		item->setZValue(zValue);
	}
}