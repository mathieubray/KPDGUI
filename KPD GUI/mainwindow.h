#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

#include "DialogPair.h"
#include "DialogAD.h"
#include "DialogSimParam.h"
#include "DialogReadFile.h"
#include "DialogSort.h"
#include "DialogDisplay.h"

#include "KPDGUINode.h"
#include "KPDGUINodeWrapper.h"
#include "KPDGUIArrow.h"
#include "KPDGUIArrowWrapper.h"
#include "KPDGUIRecord.h"
#include "KPDGUIGraphicsScene.h"
#include "KPDGUISimulParam.h"
#include "KPDGUIGraph.h"
#include "KPDGUIStructure.h"
#include "KPDGUIStructureSet.h"
#include "KPDGUIStructureWrapper.h"
#include "KPDGUIConsole.h"

#include "Structs.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
	void sortLists();

	//Window-->About
	void about();

	//Selection Actions
	void newPairListSelectionActions(QTreeWidgetItem *);
	void newMatchListSelectionActions(QTreeWidgetItem *);
	void newTreeSelectionActions(QTreeWidgetItem *);

	//Custom Menus
	void structureTreeCustomMenu(QPoint);
	void solutionTreeCustomMenu(QPoint);

	//Additional Actions
	void deleteNode(int);
	void clickActions(int, bool);

	void clusterStructure();
	void clusterSolution();
	void removeSolution();
	
	//Updates
	void checkSelections();
	void updateTable(int);
	void updateVisibility();	
	void updateStatusBar();

signals:
	void visibilityChanged(DisplaySettingsStruct * displaySettings);

protected:
	void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
	void initializeParameters();
	void setUpGraphicsScene();
	void setUpLists();
	void setUpKPDObjects();
	void setUpActions();
	void setUpMenu();
	void setUpToolbar();

	//Saving and Loading
	bool loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);

	//Adding Pairs/ADs
	void addNode(KPDGUINode * newNode, bool fromSavedFile);
	void addArrow(KPDGUINode * fromNode, KPDGUINode * toNode);
	void readPairsFromFile(QString fileName);

	//Display Modes
	void setDisplaySettings(DisplaySettingsStruct * newDisplaySettings);
	void setPairSortMode(int mode, bool decreasing);
	void setMatchSortMode(int mode, bool decreasing);

	//Helper Functions
    bool okToContinue();
	void clearTable();
	void changeFocus(int);
	void sort();

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
	int mostRecentNodeID;

	//Display Modes
	DisplaySettingsStruct displaySettings;

	//Sort Modes
	int pairSortMode;
	bool pairSortDecreasing;
	int matchSortMode;
	bool matchSortDecreasing;

	//KPDGUI Objects
	KPDGUIGraphicsScene * kpdguiScene;
	KPDGUISimulParam * kpdguiParameters;
	KPDGUIRecord * kpdguiRecord;
	
	//Tab Widget Lists
	QTreeWidget * pairListWidget;
	QTreeWidget * matchListWidget;
	QTreeWidget * structureTreeWidget;
	QTreeWidget * solutionTreeWidget;
		
	//Actions
	QAction * clusterStructureAction;
	QAction * clusterSolutionAction;
	QAction * removeSolutionAction;

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

