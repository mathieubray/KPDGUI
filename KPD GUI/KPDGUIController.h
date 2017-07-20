#ifndef KPDGUICONTROLLER_H
#define KPDGUICONTROLLER_H

#include "KPDGUIGraphicsScene.h"
#include "KPDGUINodeList.h"
#include "KPDGUIMatchList.h"

class KPDGUIController : public QObject
{

	Q_OBJECT;

private:
		
	int maxZ;

	KPDGUIGraphicsScene * kpdguiScene;

	KPDGUINodeList * kpdguiNodeList;
	KPDGUIMatchList * kpdguiMatchList;

		
public slots:

	void candidateSelectionActions(int id, bool selected);
		
public:
	KPDGUIController(KPDGUIGraphicsScene * scene, KPDGUINodeList * nodeList, KPDGUIMatchList * matchList);
	~KPDGUIController();

	void addNodeToScene(KPDGUINode * node, QString layout);
	void addNodeWrapperToList(KPDGUINodeWrapper * wrapper);
	void addMatchToScene(KPDGUIMatch * match);
	void addMatchWrapperToList(KPDGUIMatchWrapper * wrapper);

};

#endif

