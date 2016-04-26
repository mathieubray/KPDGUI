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
#include "KPDGUIMatch.h"
#include "KPDGUIRecord.h"
#include "KPDGUISimParameters.h"
#include "KPDGUISimulation.h"
#include "KPDGUIStructure.h"
#include "KPDGUIStructureSet.h"
#include "KPDGUIDashboard.h"
#include "KPDGUIDisplaySettings.h"
#include "KPDGUIGraphicsView.h"
#include "KPDGUINodeList.h"

#include "KPDGUINodeWrapper.h"
#include "KPDGUIMatchWrapper.h"
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
    void newKPD();
    void openKPD();
	bool saveKPD();
    bool saveKPDAs();

	void addNewNode();
	void addNewAD();
	void loadNodes();
	
	void exitProgram();
		
	//Window-->Match Run
	void performMatchRun();
	bool setSimParameters();
	void clearSolutions();

	//Window-->Display
	void changeNodeViewMode();
	void changeMatchViewMode_Within();
	void changeMatchViewMode_SelectedCompatibilities();
	void changeMatchViewMode_All();
	void changeMatchViewMode_None();

	//Window-->Tools
	void zoomIn();
	void zoomOut();
	void zoom(int);

	void changeToMouseMode();
	void changeToHandMode();

	//Window-->About
	void aboutKPD();

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
	void setUpMenu();
	void setUpToolbar();

	//Saving and Loading
	bool loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);

	//Adding Pairs/ADs
	void addNode(KPDGUINode * newNode, bool fromSavedFile);
	void addMatch(KPDGUIDonor * fromNode, KPDGUICandidate * toNode);
	void readPairsFromFile(QString fileName, QString layout);

	void checkNodeMatches(KPDGUINode * node);

	//Display Modes
	void setDisplaySettings(KPDGUIDisplaySettings * newDisplaySettings);

	//Helper Functions
	bool okToContinue();
	void changeFocus(KPDGUINode * node);
	void updateStatus(QString message);

	//Simulation
	void runSimulation();

	//Read and Write (Necessary)
	void readSettings();
	void writeSettings();
	
	//Parameters
	QString currentFile;
	int maxZ;
	int nodePlacementSequenceNumber;
	int previousSliderPosition;

	//List Objects
	KPDGUINodeList * nodeList;

	//KPDGUI Objects
	QGraphicsScene * kpdguiScene;
	KPDGUISimParameters * kpdguiParameters;
	KPDGUIRecord * kpdguiRecord;
	KPDGUIDisplaySettings * kpdguiDisplaySettings;
		
	//Menu Objects
	QActionGroup * displayArrowsActionGroup;
	
	//Toolbar Objects
	QSlider * zoomSlider;	

	static const int MagicNumber = 40930942;
};

#endif // MAINWINDOW_H

