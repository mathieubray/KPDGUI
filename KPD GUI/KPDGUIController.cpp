#include "KPDGUIController.h"


KPDGUIController::KPDGUIController(KPDGUIGraphicsScene * scene, KPDGUINodeList * nodeList, KPDGUIMatchList * matchList) {
	kpdguiScene = scene;
	kpdguiNodeList = nodeList;
	kpdguiMatchList = matchList;
}

KPDGUIController::~KPDGUIController() {

}

void KPDGUIController::addNodeWrapperToList(KPDGUINodeWrapper * wrapper) {
	kpdguiNodeList->addTopLevelItem(wrapper);
}

void KPDGUIController::addMatchToScene(KPDGUIMatch * match) {
	kpdguiScene->addItem(match);
}

void KPDGUIController::addMatchWrapperToList(KPDGUIMatchWrapper * wrapper) {
	kpdguiMatchList->addTopLevelItem(wrapper);
}

void KPDGUIController::candidateSelectionActions(int id, bool selected) {
	QVector<KPDGUIDonor *> donors = nodes[id].
}


//void KPDGUIController::changeFocus(KPDGUINode * node) {
	//ui->graphicsView->centerOn(node->getNodePosition());
//}


//NODES

//connect(this, SIGNAL(poolChanged()), wrapper, SLOT(updateText()));
//connect(this, SIGNAL(visibilityChanged(KPDGUIDisplaySettings *)), newNode, SLOT(updateVisibility(KPDGUIDisplaySettings *)));
//connect(this, SIGNAL(selectAll()), newNode, SLOT(selectIfVisible()));

//MATCH

//connect(this, SIGNAL(visibilityChanged(KPDGUIDisplaySettings *)), match, SLOT(updateVisibility(KPDGUIDisplaySettings *)));



