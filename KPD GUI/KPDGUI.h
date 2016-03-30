#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QtWidgets>

#include "DialogDonor.h"
#include "DialogCandidate.h"
#include "DialogDisplaySettings.h"
#include "DialogReadFile.h"
#include "DialogSimParameters.h"

#include "KPDGUINode.h"
#include "KPDGUIArrow.h"
#include "KPDGUIRecord.h"
#include "KPDGUISimParameters.h"
#include "KPDGUISimulation.h"
#include "KPDGUIStructure.h"
#include "KPDGUIStructureSet.h"
#include "KPDGUIDashboard.h"
#include "KPDGUICloud.h"
#include "KPDGUIDisplaySettings.h"
#include "KPDGUIGraphicsView.h"
#include "KPDGUIPairList.h"

#include "KPDGUINodeWrapper.h"
#include "KPDGUIArrowWrapper.h"
#include "KPDGUIStructureWrapper.h"

#include "EnumsFunctions.h"


namespace Ui {
	class KPDGUI;
}

class KPDGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit KPDGUI(QWidget *parent = 0);
    ~KPDGUI();

public slots:
	
	//Window-->File
    void newFile();
    void open();
	bool save();
    bool saveAs();
	void addNewPair();
	void addNewAD();
	void loadPairs();
	void exitProgram();
		
	//Window-->Match Run
	void run();
	bool setSimParameters();
	void clearSolutions();

	//Window-->Display
	void changePairViewMode();
	void changeArrowViewMode_Within();
	void changeArrowViewMode_SelectedComps();
	void changeArrowViewMode_Donors();
	void changeArrowViewMode_Recips();
	void changeArrowViewMode_All();
	void changeArrowViewMode_None();

	//Window-->Tools
	void zoomIn();
	void zoomOut();
	void zoom(int);

	void changeToMouseMode();
	void changeToHandMode();

	//Window-->About
	void about();

	//Custom Menus
	void screenCustomMenu(QPoint);
	void pairListCustomMenu(QPoint);
	void structureTreeCustomMenu(QPoint);
	void solutionTreeCustomMenu(QPoint);

	//Pair List Actions
	//void newPairListSelectionActions(QTreeWidgetItem *);
	void newPairListSelectionActions();
	void newPairListDoubleClickActions(QTreeWidgetItem *);

	void clusterStructure();
	void clusterSolution();
	void removeSolution();
	
	//Structure List Actions
	void structureTreeSelectionActions(QTreeWidgetItem *);
	
	//Solution List Actions
	void solutionTreeSelectionActions(QTreeWidgetItem *);
	 
	//Graphics View Actions 
	void editDonor();
	void editCandidate();
	void holdNode();
	void unholdNode();
	void deleteNode();

	void holdMultipleNodes();
	void unholdMultipleNodes();
	void clusterMultipleNodes();
	void deleteMultipleNodes();

	void deleteNode(int);
	void clickActions(QTreeWidgetItem *);
	

	//void addAssociatedDonor();
	//void highlightRelevantStructures();
	//void highlightRelevantSolutions();
	//void selectAllVisibleNodes();
	//void clearAllHighlights();	
	
	//Updates
	void checkSelections();
	void updateTable(int);
	void clearTable();
	void updateVisibility();	
	void updateStatusBar();

signals:
	void visibilityChanged(KPDGUIDisplaySettings * displaySettings);
	void poolChanged();

protected:
	void closeEvent(QCloseEvent *event);

private:
    Ui::KPDGUI *ui;
	void initializeParameters();
	void setUpGraphicsScene();
	void setUpLists();
	void setUpKPDObjects();
	void setUpActions();
	void setUpMenu();
	void setUpToolbar();

	void testNewNodes();

	//Saving and Loading
	bool loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);

	//Adding Pairs/ADs
	void addNode(KPDGUINode * newNode, bool fromSavedFile);
	void addArrow(KPDGUINode * fromNode, KPDGUINode * toNode);
	void readPairsFromFile(QString fileName, QString layout);

	//Display Modes
	void setDisplaySettings(KPDGUIDisplaySettings * newDisplaySettings);

	//Helper Functions
	bool okToContinue();
	void changeFocus(KPDGUINode * node);
	void sort();
	void highlightStructures(QTreeWidgetItem * item);
	void updateStatus(QString message);

	//Simulation
	void runSimulation();

	//Read and Write (Necessary)
	void readSettings();
	void writeSettings();
	
	//Parameters
	QString curFile;
	int maxZ;
	int seqNumber;
	int prevSliderPos;

	//KPDGUI Objects
	QGraphicsScene * kpdguiScene;
	KPDGUISimParameters * kpdguiParameters;
	KPDGUIRecord * kpdguiRecord;
	KPDGUIDisplaySettings * kpdguiDisplaySettings;
		
	//Actions
	QAction * clusterStructureAction;
	QAction * clusterSolutionAction;
	QAction * removeSolutionAction;

	QAction * editDonorAction;
	QAction * editCandidateAction;
	QAction * holdNodeAction;
	QAction * unholdNodeAction;
	QAction * deleteNodeAction;

	QAction * holdMultipleNodesAction;
	QAction * unholdMultipleNodesAction;
	QAction * clusterMultipleNodesAction;
	QAction * deleteMultipleNodesAction;

	//QAction * addAssociatedDonorAction;
	//QAction * highlightStructuresAction;
	//QAction * highlightSolutionsAction;
	//QAction * selectAllAction;
	//QAction * clearHighlightsAction;

	//Menu Objects
	QActionGroup * displayArrowsActionGroup;
	
	//Toolbar Objects
	QSlider * zoomSlider;	

	//Recent Structures
	KPDGUIStructure * rightClickStructure;
	KPDGUIStructureSet * rightClickStructureSet;
	QVector<KPDGUIStructure *> selectedStructures;

	static const int MagicNumber = 40930942;
};

#endif // MAINWINDOW_H

