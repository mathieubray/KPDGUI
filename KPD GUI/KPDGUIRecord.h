#ifndef KPDGUIRECORD_H
#define KPDGUIRECORD_H

#include <QtGui>
#include <QtWidgets>
#include <QtDebug>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "KPDGUINode.h"
#include "KPDGUINodeWrapper.h"
#include "KPDGUIMatch.h"
#include "KPDGUIMatchWrapper.h"
#include "KPDGUIGraphicsScene.h"
#include "KPDGUISimParameters.h"


class KPDGUIRecord : public QObject
{
	Q_OBJECT;

public:
	KPDGUIRecord();
	~KPDGUIRecord();

	int getBaselineIDCode();
	void setBaselineIDCode(int code);
	
	void insertNode(KPDGUINode * node, bool fromSavedFile = false);
	void insertMatch(KPDGUIMatch * match);
			
	KPDGUINode * getNode(int nodeID);
	KPDGUINode * getNodeFromIndex(int i);
	QList<KPDGUINode *> getNodes();
	
	int getNumberOfNodes();
	int getNumberOfAvailableNodes();	
	
	//Matrices
	void generateMatrices(KPDGUISimParameters * params, QProgressDialog * progress);

	std::vector<std::vector<bool> > getIncidenceMatrix();
	std::vector<std::vector<std::vector<int> > > getAssociatedDonorMatrix();
	std::vector<std::vector<std::vector<double> > > getAssociatedScoresMatrix();
	std::vector<std::vector<std::vector<double> > > getAssociated5YearSurvivalMatrix();
	std::vector<std::vector<std::vector<double> > > getAssociated10YearSurvivalMatrix();
	std::vector<std::vector<std::vector<double> > > getAssociatedProbabilitiesMatrix();
	std::vector<AdditionalNodeInfo> getNodeInfoVector();

	bool isMatch(KPDGUIDonorInfo * donor, KPDGUICandidateInfo * candidate, bool reserveOtoO, bool checkAdditionalHLA);
	bool isMatch(KPDGUINode * donorNode, KPDGUINode * candidateNode, int donor, bool reserveOtoO, bool checkAdditionalHLA);

	double calculateSurvival(KPDGUIDonorInfo * donor, KPDGUICandidateInfo * candidate, int fiveyear);
	double calculateSurvival(KPDGUINode * donorNode, KPDGUINode * candidateNode, int donor, int fiveyear);

	void clearRecord();

	QString getRecordLog();
	
signals:
	//void takeAdditionalDeleteNodeActions(KPDGUINode * node);

public slots:
	//void deleteNodeFromRecord(int id);

protected:
	void loadDictionary();
	void loadSurvivalParameters();
	void clearMatrices();

	
	


private:

	int baselineID;

	//Data Vectors 
	QMap<QString, QVector<QString> > hlaDictionary;
	QMap<QString, QVector<double> > survivalParameters;

	//Stored Items
	QMap<int, KPDGUINode*> nodes;
	QMap<int, KPDGUIMatch*> fromMatches;
	QMap<int, KPDGUIMatch*> toMatches;

	std::vector<KPDGUINode *> availableNodes;
	std::vector<std::vector<bool> > incidenceMatrix;
	std::vector<std::vector<std::vector<int> > > associatedDonorMatrix;
	std::vector<std::vector<std::vector<double> > > associatedScoresMatrix;
	std::vector<std::vector<std::vector<double> > > associated5YearSurvivalMatrix;
	std::vector<std::vector<std::vector<double> > > associated10YearSurvivalMatrix;
	std::vector<std::vector<std::vector<double> > > associatedProbabilitiesMatrix;
	std::vector<AdditionalNodeInfo> nodeInfoVector;

	QString recordLog;	
};

#endif
