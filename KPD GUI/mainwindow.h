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

protected:
	void closeEvent(QCloseEvent *event);

public slots:
	//Window Actions
    void newFile();
    void open();
	bool save();
    bool saveAs();
	void exitProgram();
	void about();
	
	//Simulation Actions
	void run();

	//Pair Actions
	void addNewPair();
	void addNewAD();
	void loadPairs();
	void deleteNode(int);
	
	//Update Actions
	void clickActions(int,bool);
	void newPairListSelectionActions(QTreeWidgetItem *);
	void newMatchListSelectionActions(QTreeWidgetItem *);
	void newTreeSelectionActions(QTreeWidgetItem *);
		
	void checkSelections();
	void updateStatusBar();	
	void updateTable(int);
	void updateVisibility();

	//Visual Actions
	void clusterStructure();
	void clusterSolution();
	void removeSolution();
	void clearSolutions();

	void zoomIn();
	void zoomOut();
	void zoom(int);
	void sort();

	void changeFocus(int);

	//Display Modes
	void setDisplaySettings(DisplaySettingsStruct * newDisplaySettings);

	//Sort Modes
	void resort();
	void setPairSortMode(int mode, bool decreasing);
	void setMatchSortMode(int mode, bool decreasing);

	//Parameters
	bool setSimParameters();	
	void changeArrowViewMode(int);
	void changePairViewMode(int);

	//Custom Menus
	void cycleTreeCustomMenu(QPoint);
	void solutionTreeCustomMenu(QPoint);

signals:
	void visibilityChanged(DisplaySettingsStruct * displaySettings);

private:
    Ui::MainWindow *ui;

	//Read and Write (Necessary)
    void readSettings();
    void writeSettings();

	//Helper Functions
    bool okToContinue();
	void clearTable();
	void runSimulation();
	void clearScreen();

	void addNode(KPDGUINode * newNode, bool fromSavedFile);
	void addArrow(KPDGUINode * fromNode, KPDGUINode * toNode);
	void readPairsFromFile(QString fileName);

	void bringToFront();
	int maxZ;

	//File Properties
	QString curFile;
    void setCurrentFile(const QString &fileName);
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
	
	//Visual and Storage Properties
	int seqNumber;
	int prevSliderPos;

	KPDGUIGraphicsScene * scene;
	KPDGUIRecord * kpdguiRecord;
	KPDGUISimulParam * simulParam;

	QTreeWidget * listWidget;
	QTreeWidget * matchWidget;
	QTreeWidget * structureTreeWidget;
	QTreeWidget * solutionTreeWidget;
	
	int mostRecentNodeID;
	KPDGUIStructure * rightClickStructure;
	KPDGUIStructureSet * rightClickStructureSet;
	QVector<KPDGUIStructure *> selectedStructures;
			
	//Actions
	void createAdditionalActions();
	QAction * clusterStructureAction;
	QAction * clusterSolutionAction;
	QAction * removeSolutionAction;

	//Display Modes
	DisplaySettingsStruct displaySettings;

	//Sort Modes
	int pairSortMode;
	bool pairSortDecreasing;
	int matchSortMode;
	bool matchSortDecreasing;

	static const int MagicNumber = 40930942;
};

#endif // MAINWINDOW_H

