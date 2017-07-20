#ifndef KPDGUI_H
#define KPDGUI_H

#include <QtGui>
#include <QMainWindow>
#include <QtWidgets>

#include "DialogDonor.h"
#include "DialogCandidate.h"
#include "DialogMatch.h"
#include "DialogDisplaySettings.h"
#include "DialogReadFile.h"
#include "DialogSimParameters.h"
#include "DialogSurvivalCalculator.h"

#include "KPDGUINode.h"
#include "KPDGUIMatch.h"
#include "KPDGUIParameters.h"
#include "KPDGUIMatchRun.h"
#include "KPDGUIArrangement.h"
#include "KPDGUIArrangementSet.h"
#include "KPDGUIDisplaySettings.h"

#include "KPDGUICrossmatchFunctions.h"

#include "KPDGUIGraphicsView.h"
#include "KPDGUIGraphicsScene.h"

#include "KPDGUICommandHistory.h"
#include "KPDGUIDashboardList.h"

#include "KPDGUINodeWrapper.h"
#include "KPDGUIMatchWrapper.h"
#include "KPDGUIArrangementWrapper.h"

#include "KPDGUIEnumsFunctions.h"

namespace Ui {
	class KPDGUI;
}

class KPDGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit KPDGUI(QWidget *parent = 0);
    ~KPDGUI();

	KPDGUINode * getNode(int nodeID);
	QList<KPDGUINode *> getNodes();
	QVector<KPDGUIMatch *> getMatches(int id);

	void insertNode(KPDGUINode * node);
	void insertMatch(KPDGUIMatch * match);

public slots:
	
	//Window -> File
    void newKPD();
    void openKPD();
	bool saveKPD();
    bool saveKPDAs();

	void addNewNode();
	void addNewNDD();
	void loadNodes();
	
	void exitProgram();
		
	//Window -> Match Run
	void performMatchRun();
	bool setSimParameters();
	void clearArrangements();
	void clearSolutions();

	//Window -> Display
	bool changeNodeViewMode();
	void changeMatchViewMode_Within();
	void changeMatchViewMode_SelectedCompatibilities();
	void changeMatchViewMode_All();
	void changeMatchViewMode_None();
	
	//Window -> Tools
	void runSurvivalCalculator();

	void zoomIn();
	void zoomOut();
	void zoom(int);

	void changeToMouseMode();
	void changeToHandMode();

	//Window -> About
	void aboutKPD();

	//void updateStatusBar();

	/////// Actions ///////

	void donorSelectionActions(int nodeID, int donorID, bool seleted);
	void candidateSelectionActions(int id, bool selected);

	//void nodeWrapperClickActions();
	void arrangementListClickActions(QTreeWidgetItem * item);
	void arrangementListDoubleClickActions(QTreeWidgetItem * item);

	void solutionListClickActions(QTreeWidgetItem * item);
	void solutionListDoubleClickActions(QTreeWidgetItem * item);

	
signals:
	void displaySettingsChanged(KPDGUIDisplaySettings *);

	void nodesAdded();

	void matchRunCompleted();

	void clearHighlights();

protected:
	void closeEvent(QCloseEvent *event);

private:
    Ui::KPDGUI *ui;
		
	KPDGUIGraphicsScene * kpdguiScene;

	KPDGUICommandHistory * kpdguiCommandHistory;
	KPDGUIDashboardList * kpdguiNodeList;
	KPDGUIDashboardList * kpdguiDonorList;
	KPDGUIDashboardList * kpdguiCandidateList;
	KPDGUIDashboardList * kpdguiMatchList;
	QTreeWidget * kpdguiArrangementList;
	QTreeWidget * kpdguiSolutionList;

	KPDGUIDisplaySettings * kpdguiDisplaySettings;
	KPDGUICrossmatchFunctions * kpdguiCrossmatchFunctions;
	KPDGUIParameters * kpdguiParameters;

	// Data
	QMap<int, KPDGUINode *> nodes;
	QMap<int, QVector<KPDGUIMatch *> > candidateMatches;
	QMap<int, QVector<KPDGUIMatch *> > donorMatches;
	QMap<KPDGUINode *, KPDGUINodeWrapper *> nodeWrapperMap;
	QMap<KPDGUIMatch *, KPDGUIMatchWrapper *> matchWrapperMap;

	void updateStatus(QString message);
	
	//Saving and Loading
	bool loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);

	//Read and Write (Needed for some reason)
	//void readSettings();
	//void writeSettings();
	
	//Parameters
	QString currentFile;
	int previousSliderPosition;	
	int baselineID;
		
	//Menu and Toolbar Objects
	QActionGroup * displayMatchesActionGroup;
	QSlider * zoomSlider;

	//Recent Arrangements
	KPDGUIArrangement * rightClickArrangement;
	KPDGUIArrangementSet * rightClickArrangementSet;
	QVector<KPDGUIArrangement *> selectedArrangements;

	static const int MagicNumber = 40930942;
};

#endif // MAINWINDOW_H

