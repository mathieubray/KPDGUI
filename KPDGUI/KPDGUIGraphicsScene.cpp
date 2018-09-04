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
					//qDebug() << "Before: Not Selected:";
				}
				
				candidate->setSelected(true);
				
				if (candidate->isSelected()) {
					//qDebug() << "After: Selected";
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
		
		KPDGUINode * node = nodes.at(0);

		//bool altruistic = false;

		/*QVector<KPDGUICandidate *> candidates;
		QVector<KPDGUIDonor *> donors;

		foreach(QGraphicsItem * item, items) {
			KPDGUICandidate *candidate = dynamic_cast<KPDGUICandidate *>(item);
			if (candidate) {
				candidates << candidate;
			}
			else {
				KPDGUIDonor *donor = dynamic_cast<KPDGUIDonor *>(item);
				if (donor) {
					donors << donor;
				}
			}			
		}*/


		/*if (node->getNumberOfDonors() > 1) {

			int n = donors.size();
			bool continueSorting = true;

			while (continueSorting) {
				continueSorting = false;

				for (int i = 1; i < n; i++) {
					if (donors[i - 1]->getDonorNumber() > donors[i]->getDonorNumber()) {
						KPDGUIDonor * tempDonor = donors.takeAt(i);
						donors.insert(i-1, tempDonor);

						continueSorting = true;
					}
				}
			}			
		}*/

		//if (candidates.size() > 0) {

			//KPDGUICandidate * candidate = candidates.at(0);

		if (node->getType() != NDD) {

			KPDGUICandidate * candidate = node->getCandidate();

			QAction * editAction = new QAction("Edit Candidate " + candidate->candidateString(), this);
			connect(editAction, SIGNAL(triggered()), candidate, SLOT(edit()));

			menu.addAction(editAction);
			menu.addSeparator();
		}

		foreach(KPDGUIDonor * donor, node->getDonors()){
			
			/*if (donor->isAltruistic()) {
				altruistic = true;
			}*/

			QAction * editAction = new QAction("Edit Donor " + donor->donorString(), this);
			connect(editAction, SIGNAL(triggered()), donor, SLOT(edit()));

			menu.addAction(editAction);						
		}

		if (node->getType() != NDD) {
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

void KPDGUIGraphicsScene::isolate(int minX, int maxX, int minY, int maxY) {

	qreal padding = 500;

	RNG * rng = new RNG();
	rng->setSeed(900707);
	
	QObject * object = sender();
	
	QList<QGraphicsItem *> itemsToMove = items(QRectF(QPointF(minX - padding, minY - padding), QPointF(maxX + padding, maxY + padding)));

	QSet<KPDGUINode *> nodesToMove;

	foreach(QGraphicsItem * item, itemsToMove) {

		KPDGUICandidate * candidate = dynamic_cast<KPDGUICandidate *>(item);
		if (candidate) {
			nodesToMove.insert(candidate->getParentNode());
		}
		else {
			KPDGUIDonor * donor = dynamic_cast<KPDGUIDonor *>(item);
			if (donor) {
				nodesToMove.insert(donor->getParentNode());
			}
		}
	}


	int counter = 1;

	KPDGUIArrangement * arrangement = dynamic_cast<KPDGUIArrangement *>(object);
	

	if (arrangement) {

		foreach(KPDGUINode * node, nodesToMove) {

			if (!arrangement->containsNode(node)) {

				qreal newX = node->getNodePosition().x();
				qreal newY = node->getNodePosition().y();

				if (counter % 4 == 0) {
					newX = minX - padding * (1 + rng->runif());
				}
				else if (counter % 4 == 1) {
					newX = maxX + padding * (1 + rng->runif());
				}
				else if (counter % 4 == 2) {
					newY = minY - padding * (1 + rng->runif());
				}
				else {
					newY = maxY + padding * (1 + rng->runif());
				}

				node->setNodePosition(QPointF(newX, newY));

				counter++;
			}			
		}
	}

	else {
			
		KPDGUIArrangementSet * arrangementSet = dynamic_cast<KPDGUIArrangementSet *>(object);

		if (arrangementSet) {

			foreach(KPDGUINode * node, nodesToMove){

				if (!arrangementSet->containsNode(node)) {

					qreal newX = node->getNodePosition().x();
					qreal newY = node->getNodePosition().y();

					if (counter % 4 == 0) {
						newX = minX - padding * (1 + rng->runif());
					}
					else if (counter % 4 == 1) {
						newX = maxX + padding * (1 + rng->runif());
					}
					else if (counter % 4 == 2) {
						newY = minY - padding * (1 + rng->runif());
					}
					else {
						newY = maxY + padding * (1 + rng->runif());
					}

					node->setNodePosition(QPointF(newX, newY));

					counter++;
				}
			}
		}
	}

	delete rng;
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