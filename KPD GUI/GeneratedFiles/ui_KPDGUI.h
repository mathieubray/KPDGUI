/********************************************************************************
** Form generated from reading UI file 'KPDGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KPDGUI_H
#define UI_KPDGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "KPDGUIDashboard.h"
#include "kpdguigraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_KPDGUI
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionAdd_Pair;
    QAction *actionAdd_AD;
    QAction *actionLoad_Pairs_from_File;
    QAction *actionExit;
    QAction *actionRun;
    QAction *actionAbout;
    QAction *actionParameters;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionView_PairInfo;
    QAction *actionClear_Solutions;
    QAction *actionZoom_Out;
    QAction *actionZoom_In;
    QAction *actionHand_Tool;
    QAction *actionMouse_Tool;
    QAction *actionPair_AD_Settings;
    QAction *actionDisplay_No_Compatibilities;
    QAction *actionDisplay_All_Compatibilities;
    QAction *actionDisplay_Selected_Compatibilities;
    QAction *actionDisplay_Compatibilities_Within_Selection;
    QAction *actionView_Structures_Solutions;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTabWidget *nodeAndMatchWidget;
    QVBoxLayout *centralPanelLayout;
    KPDGUIGraphicsView *graphicsView;
    KPDGUIDashboard *dashboard;
    QSplitter *rightPanelLayout;
    QTreeWidget *structureWidget;
    QTreeWidget *solutionWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;
    QMenu *menuMatch_Run;
    QMenu *menuDisplay;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *KPDGUI)
    {
        if (KPDGUI->objectName().isEmpty())
            KPDGUI->setObjectName(QStringLiteral("KPDGUI"));
        KPDGUI->resize(1060, 760);
        KPDGUI->setMinimumSize(QSize(1060, 590));
        KPDGUI->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        KPDGUI->setWindowIcon(icon);
        actionNew = new QAction(KPDGUI);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionOpen = new QAction(KPDGUI);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionClose = new QAction(KPDGUI);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionAdd_Pair = new QAction(KPDGUI);
        actionAdd_Pair->setObjectName(QStringLiteral("actionAdd_Pair"));
        actionAdd_AD = new QAction(KPDGUI);
        actionAdd_AD->setObjectName(QStringLiteral("actionAdd_AD"));
        actionLoad_Pairs_from_File = new QAction(KPDGUI);
        actionLoad_Pairs_from_File->setObjectName(QStringLiteral("actionLoad_Pairs_from_File"));
        actionExit = new QAction(KPDGUI);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionRun = new QAction(KPDGUI);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/images/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon3);
        actionAbout = new QAction(KPDGUI);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionParameters = new QAction(KPDGUI);
        actionParameters->setObjectName(QStringLiteral("actionParameters"));
        actionSave = new QAction(KPDGUI);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon4);
        actionSave_As = new QAction(KPDGUI);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionView_PairInfo = new QAction(KPDGUI);
        actionView_PairInfo->setObjectName(QStringLiteral("actionView_PairInfo"));
        actionView_PairInfo->setCheckable(true);
        actionView_PairInfo->setChecked(true);
        actionClear_Solutions = new QAction(KPDGUI);
        actionClear_Solutions->setObjectName(QStringLiteral("actionClear_Solutions"));
        actionZoom_Out = new QAction(KPDGUI);
        actionZoom_Out->setObjectName(QStringLiteral("actionZoom_Out"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/images/zoomout.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_Out->setIcon(icon5);
        actionZoom_In = new QAction(KPDGUI);
        actionZoom_In->setObjectName(QStringLiteral("actionZoom_In"));
        actionZoom_In->setCheckable(false);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/images/zoomin.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_In->setIcon(icon6);
        actionHand_Tool = new QAction(KPDGUI);
        actionHand_Tool->setObjectName(QStringLiteral("actionHand_Tool"));
        actionHand_Tool->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/images/handtool.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHand_Tool->setIcon(icon7);
        actionMouse_Tool = new QAction(KPDGUI);
        actionMouse_Tool->setObjectName(QStringLiteral("actionMouse_Tool"));
        actionMouse_Tool->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/images/cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMouse_Tool->setIcon(icon8);
        actionPair_AD_Settings = new QAction(KPDGUI);
        actionPair_AD_Settings->setObjectName(QStringLiteral("actionPair_AD_Settings"));
        actionDisplay_No_Compatibilities = new QAction(KPDGUI);
        actionDisplay_No_Compatibilities->setObjectName(QStringLiteral("actionDisplay_No_Compatibilities"));
        actionDisplay_No_Compatibilities->setCheckable(true);
        actionDisplay_All_Compatibilities = new QAction(KPDGUI);
        actionDisplay_All_Compatibilities->setObjectName(QStringLiteral("actionDisplay_All_Compatibilities"));
        actionDisplay_All_Compatibilities->setCheckable(true);
        actionDisplay_Selected_Compatibilities = new QAction(KPDGUI);
        actionDisplay_Selected_Compatibilities->setObjectName(QStringLiteral("actionDisplay_Selected_Compatibilities"));
        actionDisplay_Selected_Compatibilities->setCheckable(true);
        actionDisplay_Compatibilities_Within_Selection = new QAction(KPDGUI);
        actionDisplay_Compatibilities_Within_Selection->setObjectName(QStringLiteral("actionDisplay_Compatibilities_Within_Selection"));
        actionDisplay_Compatibilities_Within_Selection->setCheckable(true);
        actionDisplay_Compatibilities_Within_Selection->setChecked(true);
        actionView_Structures_Solutions = new QAction(KPDGUI);
        actionView_Structures_Solutions->setObjectName(QStringLiteral("actionView_Structures_Solutions"));
        actionView_Structures_Solutions->setCheckable(true);
        actionView_Structures_Solutions->setEnabled(true);
        centralwidget = new QWidget(KPDGUI);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setChildrenCollapsible(false);
        nodeAndMatchWidget = new QTabWidget(splitter);
        nodeAndMatchWidget->setObjectName(QStringLiteral("nodeAndMatchWidget"));
        nodeAndMatchWidget->setMinimumSize(QSize(300, 0));
        nodeAndMatchWidget->setMaximumSize(QSize(300, 16777215));
        nodeAndMatchWidget->setTabPosition(QTabWidget::South);
        splitter->addWidget(nodeAndMatchWidget);

        horizontalLayout->addWidget(splitter);

        centralPanelLayout = new QVBoxLayout();
        centralPanelLayout->setObjectName(QStringLiteral("centralPanelLayout"));
        graphicsView = new KPDGUIGraphicsView(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMinimumSize(QSize(300, 300));
        graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
        graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

        centralPanelLayout->addWidget(graphicsView);

        dashboard = new KPDGUIDashboard(centralwidget);
        dashboard->setObjectName(QStringLiteral("dashboard"));
        dashboard->setMinimumSize(QSize(300, 125));
        dashboard->setMaximumSize(QSize(16777215, 125));
        dashboard->setTabPosition(QTabWidget::South);
        dashboard->setTabShape(QTabWidget::Rounded);
        dashboard->setElideMode(Qt::ElideNone);

        centralPanelLayout->addWidget(dashboard);


        horizontalLayout->addLayout(centralPanelLayout);

        rightPanelLayout = new QSplitter(centralwidget);
        rightPanelLayout->setObjectName(QStringLiteral("rightPanelLayout"));
        rightPanelLayout->setOrientation(Qt::Vertical);
        rightPanelLayout->setChildrenCollapsible(false);
        structureWidget = new QTreeWidget(rightPanelLayout);
        structureWidget->setObjectName(QStringLiteral("structureWidget"));
        structureWidget->setMinimumSize(QSize(250, 100));
        structureWidget->setMaximumSize(QSize(250, 16777215));
        structureWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        structureWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        rightPanelLayout->addWidget(structureWidget);
        solutionWidget = new QTreeWidget(rightPanelLayout);
        solutionWidget->setObjectName(QStringLiteral("solutionWidget"));
        solutionWidget->setMinimumSize(QSize(250, 100));
        solutionWidget->setMaximumSize(QSize(250, 16777215));
        solutionWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        solutionWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        rightPanelLayout->addWidget(solutionWidget);

        horizontalLayout->addWidget(rightPanelLayout);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        KPDGUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(KPDGUI);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1060, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuMatch_Run = new QMenu(menubar);
        menuMatch_Run->setObjectName(QStringLiteral("menuMatch_Run"));
        menuDisplay = new QMenu(menubar);
        menuDisplay->setObjectName(QStringLiteral("menuDisplay"));
        KPDGUI->setMenuBar(menubar);
        statusBar = new QStatusBar(KPDGUI);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        KPDGUI->setStatusBar(statusBar);
        toolBar = new QToolBar(KPDGUI);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMinimumSize(QSize(0, 30));
        toolBar->setMaximumSize(QSize(16777215, 30));
        toolBar->setMovable(false);
        toolBar->setFloatable(false);
        KPDGUI->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuMatch_Run->menuAction());
        menubar->addAction(menuDisplay->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addAction(actionAdd_Pair);
        menuFile->addAction(actionAdd_AD);
        menuFile->addAction(actionLoad_Pairs_from_File);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTools->addAction(actionZoom_In);
        menuTools->addAction(actionZoom_Out);
        menuTools->addSeparator();
        menuTools->addAction(actionMouse_Tool);
        menuTools->addAction(actionHand_Tool);
        menuTools->addSeparator();
        menuTools->addAction(actionView_Structures_Solutions);
        menuHelp->addAction(actionAbout);
        menuMatch_Run->addAction(actionRun);
        menuMatch_Run->addAction(actionParameters);
        menuMatch_Run->addSeparator();
        menuMatch_Run->addAction(actionClear_Solutions);
        menuDisplay->addAction(actionPair_AD_Settings);
        menuDisplay->addSeparator();
        menuDisplay->addAction(actionDisplay_Compatibilities_Within_Selection);
        menuDisplay->addAction(actionDisplay_Selected_Compatibilities);
        menuDisplay->addAction(actionDisplay_All_Compatibilities);
        menuDisplay->addAction(actionDisplay_No_Compatibilities);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionRun);
        toolBar->addSeparator();
        toolBar->addAction(actionZoom_Out);
        toolBar->addAction(actionZoom_In);
        toolBar->addSeparator();
        toolBar->addAction(actionMouse_Tool);
        toolBar->addAction(actionHand_Tool);

        retranslateUi(KPDGUI);
        QObject::connect(actionOpen, SIGNAL(triggered()), KPDGUI, SLOT(openKPD()));
        QObject::connect(actionClose, SIGNAL(triggered()), KPDGUI, SLOT(close()));
        QObject::connect(actionExit, SIGNAL(triggered()), KPDGUI, SLOT(exitProgram()));
        QObject::connect(actionAbout, SIGNAL(triggered()), KPDGUI, SLOT(aboutKPD()));
        QObject::connect(actionSave, SIGNAL(triggered()), KPDGUI, SLOT(saveKPD()));
        QObject::connect(actionSave_As, SIGNAL(triggered()), KPDGUI, SLOT(saveKPDAs()));
        QObject::connect(actionAdd_Pair, SIGNAL(triggered()), KPDGUI, SLOT(addNewNode()));
        QObject::connect(actionParameters, SIGNAL(triggered()), KPDGUI, SLOT(setSimParameters()));
        QObject::connect(actionLoad_Pairs_from_File, SIGNAL(triggered()), KPDGUI, SLOT(loadNodes()));
        QObject::connect(actionAdd_AD, SIGNAL(triggered()), KPDGUI, SLOT(addNewAD()));
        QObject::connect(actionRun, SIGNAL(triggered()), KPDGUI, SLOT(performMatchRun()));
        QObject::connect(actionClear_Solutions, SIGNAL(triggered()), KPDGUI, SLOT(clearSolutions()));
        QObject::connect(actionZoom_In, SIGNAL(triggered()), KPDGUI, SLOT(zoomIn()));
        QObject::connect(actionZoom_Out, SIGNAL(triggered()), KPDGUI, SLOT(zoomOut()));
        QObject::connect(actionHand_Tool, SIGNAL(triggered()), KPDGUI, SLOT(changeToHandMode()));
        QObject::connect(actionMouse_Tool, SIGNAL(triggered()), KPDGUI, SLOT(changeToMouseMode()));
        QObject::connect(actionDisplay_All_Compatibilities, SIGNAL(triggered()), KPDGUI, SLOT(changeMatchViewMode_All()));
        QObject::connect(actionDisplay_Compatibilities_Within_Selection, SIGNAL(triggered()), KPDGUI, SLOT(changeMatchViewMode_Within()));
        QObject::connect(actionDisplay_No_Compatibilities, SIGNAL(triggered()), KPDGUI, SLOT(changeMatchViewMode_None()));
        QObject::connect(actionDisplay_Selected_Compatibilities, SIGNAL(triggered()), KPDGUI, SLOT(changeMatchViewMode_SelectedCompatibilities()));
        QObject::connect(actionView_Structures_Solutions, SIGNAL(toggled(bool)), structureWidget, SLOT(setVisible(bool)));
        QObject::connect(actionView_Structures_Solutions, SIGNAL(toggled(bool)), solutionWidget, SLOT(setVisible(bool)));
        QObject::connect(graphicsView, SIGNAL(zoomIn()), KPDGUI, SLOT(zoomIn()));
        QObject::connect(graphicsView, SIGNAL(zoomOut()), KPDGUI, SLOT(zoomOut()));
        QObject::connect(graphicsView, SIGNAL(mouseReleased()), KPDGUI, SLOT(updateVisibility()));
        QObject::connect(actionNew, SIGNAL(triggered()), KPDGUI, SLOT(newKPD()));
        QObject::connect(actionPair_AD_Settings, SIGNAL(triggered()), KPDGUI, SLOT(changeNodeViewMode()));

        nodeAndMatchWidget->setCurrentIndex(-1);
        dashboard->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(KPDGUI);
    } // setupUi

    void retranslateUi(QMainWindow *KPDGUI)
    {
        KPDGUI->setWindowTitle(QApplication::translate("KPDGUI", "KPD", 0));
        actionNew->setText(QApplication::translate("KPDGUI", "&New", 0));
        actionNew->setShortcut(QApplication::translate("KPDGUI", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("KPDGUI", "&Open", 0));
        actionOpen->setShortcut(QApplication::translate("KPDGUI", "Ctrl+O", 0));
        actionClose->setText(QApplication::translate("KPDGUI", "&Close", 0));
        actionClose->setShortcut(QApplication::translate("KPDGUI", "Ctrl+Q", 0));
        actionAdd_Pair->setText(QApplication::translate("KPDGUI", "Add &Donor-Candidate Pairing", 0));
        actionAdd_Pair->setShortcut(QApplication::translate("KPDGUI", "Ctrl+P", 0));
        actionAdd_AD->setText(QApplication::translate("KPDGUI", "Add Altruistic Donor", 0));
        actionAdd_AD->setShortcut(QApplication::translate("KPDGUI", "Ctrl+Shift+P", 0));
        actionLoad_Pairs_from_File->setText(QApplication::translate("KPDGUI", "&Load Pairings from File", 0));
        actionLoad_Pairs_from_File->setShortcut(QApplication::translate("KPDGUI", "Ctrl+L", 0));
        actionExit->setText(QApplication::translate("KPDGUI", "&Exit", 0));
        actionRun->setText(QApplication::translate("KPDGUI", "Perform Match Run", 0));
        actionRun->setShortcut(QApplication::translate("KPDGUI", "Ctrl+R", 0));
        actionAbout->setText(QApplication::translate("KPDGUI", "About", 0));
        actionParameters->setText(QApplication::translate("KPDGUI", "Set Parameters", 0));
        actionSave->setText(QApplication::translate("KPDGUI", "&Save", 0));
        actionSave->setShortcut(QApplication::translate("KPDGUI", "Ctrl+S", 0));
        actionSave_As->setText(QApplication::translate("KPDGUI", "&Save As", 0));
        actionSave_As->setShortcut(QApplication::translate("KPDGUI", "Ctrl+Shift+S", 0));
        actionView_PairInfo->setText(QApplication::translate("KPDGUI", "View Node Info", 0));
        actionClear_Solutions->setText(QApplication::translate("KPDGUI", "Clear Solutions", 0));
        actionZoom_Out->setText(QApplication::translate("KPDGUI", "Zoom Out", 0));
        actionZoom_Out->setShortcut(QApplication::translate("KPDGUI", "Ctrl+-", 0));
        actionZoom_In->setText(QApplication::translate("KPDGUI", "Zoom In", 0));
        actionZoom_In->setShortcut(QApplication::translate("KPDGUI", "Ctrl+=", 0));
        actionHand_Tool->setText(QApplication::translate("KPDGUI", "Hand Tool", 0));
        actionHand_Tool->setShortcut(QApplication::translate("KPDGUI", "Ctrl+H", 0));
        actionMouse_Tool->setText(QApplication::translate("KPDGUI", "Mouse Tool", 0));
        actionMouse_Tool->setShortcut(QApplication::translate("KPDGUI", "Ctrl+M", 0));
        actionPair_AD_Settings->setText(QApplication::translate("KPDGUI", "Node Display Settings...", 0));
        actionPair_AD_Settings->setShortcut(QApplication::translate("KPDGUI", "Ctrl+D", 0));
        actionDisplay_No_Compatibilities->setText(QApplication::translate("KPDGUI", "Display No Compatibilities", 0));
        actionDisplay_All_Compatibilities->setText(QApplication::translate("KPDGUI", "Display All Compatibilities", 0));
        actionDisplay_Selected_Compatibilities->setText(QApplication::translate("KPDGUI", "Display Selected Compatibilities", 0));
        actionDisplay_Compatibilities_Within_Selection->setText(QApplication::translate("KPDGUI", "Display Compatibilities Within Selection", 0));
        actionView_Structures_Solutions->setText(QApplication::translate("KPDGUI", "View Structures/Solutions", 0));
        QTreeWidgetItem *___qtreewidgetitem = structureWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("KPDGUI", "Structures", 0));
        QTreeWidgetItem *___qtreewidgetitem1 = solutionWidget->headerItem();
        ___qtreewidgetitem1->setText(0, QApplication::translate("KPDGUI", "Solutions", 0));
        menuFile->setTitle(QApplication::translate("KPDGUI", "&File", 0));
        menuTools->setTitle(QApplication::translate("KPDGUI", "Tools", 0));
        menuHelp->setTitle(QApplication::translate("KPDGUI", "About", 0));
        menuMatch_Run->setTitle(QApplication::translate("KPDGUI", "Match Run", 0));
        menuDisplay->setTitle(QApplication::translate("KPDGUI", "Display", 0));
        toolBar->setWindowTitle(QApplication::translate("KPDGUI", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class KPDGUI: public Ui_KPDGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KPDGUI_H
