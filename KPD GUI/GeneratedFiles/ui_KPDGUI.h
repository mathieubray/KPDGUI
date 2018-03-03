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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "kpdguigraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_KPDGUI
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionAddPairing;
    QAction *actionAddNDD;
    QAction *actionLoadPairings;
    QAction *actionExit;
    QAction *actionPerformMatchRun;
    QAction *actionAbout;
    QAction *actionSetParameters;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionClearSolutions;
    QAction *actionZoomOut;
    QAction *actionZoomIn;
    QAction *actionHandTool;
    QAction *actionMouseTool;
    QAction *actionNodeDisplaySettings;
    QAction *actionDisplayNoCompatibilities;
    QAction *actionDisplayAllCompatibilities;
    QAction *actionDisplaySelectedCompatibilities;
    QAction *actionDisplayCompatibilitiesWithinSelection;
    QAction *actionRefresh;
    QAction *actionSurvival_Calculator;
    QAction *actionClearArrangements;
    QAction *actionFilter_Successful_Matches;
    QAction *actionFilter_O_Donor_to_Non_O_Candidate_Matches;
    QAction *actionFilter_Failed_Matches_on_Addtional_HLA;
    QAction *actionFilter_Failed_Matches_on_Crossmatch;
    QAction *actionLoad_APD_Pool;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    KPDGUIGraphicsView *kpdGraphicsView;
    QTabWidget *kpdListView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;
    QMenu *menuMatch_Run;
    QMenu *menuDisplay;
    QMenu *menuFilter_Matches;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *KPDGUI)
    {
        if (KPDGUI->objectName().isEmpty())
            KPDGUI->setObjectName(QStringLiteral("KPDGUI"));
        KPDGUI->resize(1060, 751);
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
        actionAddPairing = new QAction(KPDGUI);
        actionAddPairing->setObjectName(QStringLiteral("actionAddPairing"));
        actionAddNDD = new QAction(KPDGUI);
        actionAddNDD->setObjectName(QStringLiteral("actionAddNDD"));
        actionLoadPairings = new QAction(KPDGUI);
        actionLoadPairings->setObjectName(QStringLiteral("actionLoadPairings"));
        actionExit = new QAction(KPDGUI);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionPerformMatchRun = new QAction(KPDGUI);
        actionPerformMatchRun->setObjectName(QStringLiteral("actionPerformMatchRun"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/images/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPerformMatchRun->setIcon(icon3);
        actionAbout = new QAction(KPDGUI);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionSetParameters = new QAction(KPDGUI);
        actionSetParameters->setObjectName(QStringLiteral("actionSetParameters"));
        actionSave = new QAction(KPDGUI);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon4);
        actionSaveAs = new QAction(KPDGUI);
        actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
        actionClearSolutions = new QAction(KPDGUI);
        actionClearSolutions->setObjectName(QStringLiteral("actionClearSolutions"));
        actionZoomOut = new QAction(KPDGUI);
        actionZoomOut->setObjectName(QStringLiteral("actionZoomOut"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/images/zoomout.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomOut->setIcon(icon5);
        actionZoomIn = new QAction(KPDGUI);
        actionZoomIn->setObjectName(QStringLiteral("actionZoomIn"));
        actionZoomIn->setCheckable(false);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/images/zoomin.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomIn->setIcon(icon6);
        actionHandTool = new QAction(KPDGUI);
        actionHandTool->setObjectName(QStringLiteral("actionHandTool"));
        actionHandTool->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/images/handtool.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHandTool->setIcon(icon7);
        actionMouseTool = new QAction(KPDGUI);
        actionMouseTool->setObjectName(QStringLiteral("actionMouseTool"));
        actionMouseTool->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/images/cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMouseTool->setIcon(icon8);
        actionNodeDisplaySettings = new QAction(KPDGUI);
        actionNodeDisplaySettings->setObjectName(QStringLiteral("actionNodeDisplaySettings"));
        actionDisplayNoCompatibilities = new QAction(KPDGUI);
        actionDisplayNoCompatibilities->setObjectName(QStringLiteral("actionDisplayNoCompatibilities"));
        actionDisplayNoCompatibilities->setCheckable(true);
        actionDisplayAllCompatibilities = new QAction(KPDGUI);
        actionDisplayAllCompatibilities->setObjectName(QStringLiteral("actionDisplayAllCompatibilities"));
        actionDisplayAllCompatibilities->setCheckable(true);
        actionDisplaySelectedCompatibilities = new QAction(KPDGUI);
        actionDisplaySelectedCompatibilities->setObjectName(QStringLiteral("actionDisplaySelectedCompatibilities"));
        actionDisplaySelectedCompatibilities->setCheckable(true);
        actionDisplayCompatibilitiesWithinSelection = new QAction(KPDGUI);
        actionDisplayCompatibilitiesWithinSelection->setObjectName(QStringLiteral("actionDisplayCompatibilitiesWithinSelection"));
        actionDisplayCompatibilitiesWithinSelection->setCheckable(true);
        actionDisplayCompatibilitiesWithinSelection->setChecked(true);
        actionRefresh = new QAction(KPDGUI);
        actionRefresh->setObjectName(QStringLiteral("actionRefresh"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/images/refresh.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        actionRefresh->setIcon(icon9);
        actionSurvival_Calculator = new QAction(KPDGUI);
        actionSurvival_Calculator->setObjectName(QStringLiteral("actionSurvival_Calculator"));
        actionClearArrangements = new QAction(KPDGUI);
        actionClearArrangements->setObjectName(QStringLiteral("actionClearArrangements"));
        actionFilter_Successful_Matches = new QAction(KPDGUI);
        actionFilter_Successful_Matches->setObjectName(QStringLiteral("actionFilter_Successful_Matches"));
        actionFilter_Successful_Matches->setCheckable(true);
        actionFilter_Successful_Matches->setChecked(true);
        actionFilter_O_Donor_to_Non_O_Candidate_Matches = new QAction(KPDGUI);
        actionFilter_O_Donor_to_Non_O_Candidate_Matches->setObjectName(QStringLiteral("actionFilter_O_Donor_to_Non_O_Candidate_Matches"));
        actionFilter_O_Donor_to_Non_O_Candidate_Matches->setCheckable(true);
        actionFilter_O_Donor_to_Non_O_Candidate_Matches->setChecked(true);
        actionFilter_Failed_Matches_on_Addtional_HLA = new QAction(KPDGUI);
        actionFilter_Failed_Matches_on_Addtional_HLA->setObjectName(QStringLiteral("actionFilter_Failed_Matches_on_Addtional_HLA"));
        actionFilter_Failed_Matches_on_Addtional_HLA->setCheckable(true);
        actionFilter_Failed_Matches_on_Addtional_HLA->setChecked(true);
        actionFilter_Failed_Matches_on_Crossmatch = new QAction(KPDGUI);
        actionFilter_Failed_Matches_on_Crossmatch->setObjectName(QStringLiteral("actionFilter_Failed_Matches_on_Crossmatch"));
        actionFilter_Failed_Matches_on_Crossmatch->setCheckable(true);
        actionFilter_Failed_Matches_on_Crossmatch->setChecked(true);
        actionLoad_APD_Pool = new QAction(KPDGUI);
        actionLoad_APD_Pool->setObjectName(QStringLiteral("actionLoad_APD_Pool"));
        centralwidget = new QWidget(KPDGUI);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setChildrenCollapsible(false);
        kpdGraphicsView = new KPDGUIGraphicsView(splitter);
        kpdGraphicsView->setObjectName(QStringLiteral("kpdGraphicsView"));
        kpdGraphicsView->setMinimumSize(QSize(500, 300));
        kpdGraphicsView->setDragMode(QGraphicsView::RubberBandDrag);
        kpdGraphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
        splitter->addWidget(kpdGraphicsView);
        kpdListView = new QTabWidget(splitter);
        kpdListView->setObjectName(QStringLiteral("kpdListView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(kpdListView->sizePolicy().hasHeightForWidth());
        kpdListView->setSizePolicy(sizePolicy);
        kpdListView->setMinimumSize(QSize(400, 0));
        kpdListView->setMaximumSize(QSize(16777215, 16777215));
        kpdListView->setBaseSize(QSize(200, 0));
        kpdListView->setTabPosition(QTabWidget::South);
        splitter->addWidget(kpdListView);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

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
        menuFilter_Matches = new QMenu(menuDisplay);
        menuFilter_Matches->setObjectName(QStringLiteral("menuFilter_Matches"));
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
        menuFile->addAction(actionSaveAs);
        menuFile->addAction(actionClose);
        menuFile->addSeparator();
        menuFile->addAction(actionAddPairing);
        menuFile->addAction(actionAddNDD);
        menuFile->addSeparator();
        menuFile->addAction(actionLoadPairings);
        menuFile->addAction(actionLoad_APD_Pool);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTools->addAction(actionSurvival_Calculator);
        menuTools->addSeparator();
        menuTools->addAction(actionZoomIn);
        menuTools->addAction(actionZoomOut);
        menuTools->addSeparator();
        menuTools->addAction(actionMouseTool);
        menuTools->addAction(actionHandTool);
        menuHelp->addAction(actionAbout);
        menuMatch_Run->addAction(actionPerformMatchRun);
        menuMatch_Run->addAction(actionSetParameters);
        menuMatch_Run->addSeparator();
        menuMatch_Run->addAction(actionClearArrangements);
        menuMatch_Run->addAction(actionClearSolutions);
        menuDisplay->addAction(actionNodeDisplaySettings);
        menuDisplay->addSeparator();
        menuDisplay->addAction(actionDisplayAllCompatibilities);
        menuDisplay->addAction(actionDisplaySelectedCompatibilities);
        menuDisplay->addAction(actionDisplayCompatibilitiesWithinSelection);
        menuDisplay->addAction(actionDisplayNoCompatibilities);
        menuDisplay->addSeparator();
        menuDisplay->addAction(menuFilter_Matches->menuAction());
        menuFilter_Matches->addAction(actionFilter_Successful_Matches);
        menuFilter_Matches->addAction(actionFilter_O_Donor_to_Non_O_Candidate_Matches);
        menuFilter_Matches->addAction(actionFilter_Failed_Matches_on_Addtional_HLA);
        menuFilter_Matches->addAction(actionFilter_Failed_Matches_on_Crossmatch);
        toolBar->addAction(actionNew);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionSave);
        toolBar->addSeparator();
        toolBar->addAction(actionPerformMatchRun);
        toolBar->addSeparator();
        toolBar->addAction(actionZoomOut);
        toolBar->addAction(actionZoomIn);
        toolBar->addAction(actionMouseTool);
        toolBar->addAction(actionHandTool);

        retranslateUi(KPDGUI);
        QObject::connect(actionOpen, SIGNAL(triggered()), KPDGUI, SLOT(openKPD()));
        QObject::connect(actionClose, SIGNAL(triggered()), KPDGUI, SLOT(close()));
        QObject::connect(actionExit, SIGNAL(triggered()), KPDGUI, SLOT(exitProgram()));
        QObject::connect(actionAbout, SIGNAL(triggered()), KPDGUI, SLOT(aboutKPD()));
        QObject::connect(actionSave, SIGNAL(triggered()), KPDGUI, SLOT(saveKPD()));
        QObject::connect(actionSaveAs, SIGNAL(triggered()), KPDGUI, SLOT(saveKPDAs()));
        QObject::connect(actionAddPairing, SIGNAL(triggered()), KPDGUI, SLOT(addNewNode()));
        QObject::connect(actionSetParameters, SIGNAL(triggered()), KPDGUI, SLOT(setSimParameters()));
        QObject::connect(actionLoadPairings, SIGNAL(triggered()), KPDGUI, SLOT(loadNodes()));
        QObject::connect(actionAddNDD, SIGNAL(triggered()), KPDGUI, SLOT(addNewNDD()));
        QObject::connect(actionPerformMatchRun, SIGNAL(triggered()), KPDGUI, SLOT(performMatchRun()));
        QObject::connect(actionClearSolutions, SIGNAL(triggered()), KPDGUI, SLOT(clearSolutions()));
        QObject::connect(actionZoomIn, SIGNAL(triggered()), KPDGUI, SLOT(zoomIn()));
        QObject::connect(actionZoomOut, SIGNAL(triggered()), KPDGUI, SLOT(zoomOut()));
        QObject::connect(actionHandTool, SIGNAL(triggered()), KPDGUI, SLOT(changeToHandMode()));
        QObject::connect(actionMouseTool, SIGNAL(triggered()), KPDGUI, SLOT(changeToMouseMode()));
        QObject::connect(actionDisplayAllCompatibilities, SIGNAL(triggered()), KPDGUI, SLOT(changeMatchViewMode_All()));
        QObject::connect(actionDisplayCompatibilitiesWithinSelection, SIGNAL(triggered()), KPDGUI, SLOT(changeMatchViewMode_Within()));
        QObject::connect(actionDisplayNoCompatibilities, SIGNAL(triggered()), KPDGUI, SLOT(changeMatchViewMode_None()));
        QObject::connect(actionDisplaySelectedCompatibilities, SIGNAL(triggered()), KPDGUI, SLOT(changeMatchViewMode_SelectedCompatibilities()));
        QObject::connect(actionNew, SIGNAL(triggered()), KPDGUI, SLOT(newKPD()));
        QObject::connect(actionNodeDisplaySettings, SIGNAL(triggered()), KPDGUI, SLOT(changeNodeViewMode()));
        QObject::connect(kpdGraphicsView, SIGNAL(zoomIn()), KPDGUI, SLOT(zoomIn()));
        QObject::connect(kpdGraphicsView, SIGNAL(zoomOut()), KPDGUI, SLOT(zoomOut()));
        QObject::connect(actionSurvival_Calculator, SIGNAL(triggered()), KPDGUI, SLOT(runSurvivalCalculator()));
        QObject::connect(actionClearArrangements, SIGNAL(triggered()), KPDGUI, SLOT(clearArrangements()));
        QObject::connect(actionFilter_Successful_Matches, SIGNAL(toggled(bool)), KPDGUI, SLOT(filterMatchesSuccessful(bool)));
        QObject::connect(actionFilter_O_Donor_to_Non_O_Candidate_Matches, SIGNAL(toggled(bool)), KPDGUI, SLOT(filterMatchesOtoNonO(bool)));
        QObject::connect(actionFilter_Failed_Matches_on_Addtional_HLA, SIGNAL(toggled(bool)), KPDGUI, SLOT(filterMatchesFailedAdditionalHLA(bool)));
        QObject::connect(actionFilter_Failed_Matches_on_Crossmatch, SIGNAL(toggled(bool)), KPDGUI, SLOT(filterMatchesFailedCrossmatch(bool)));
        QObject::connect(actionLoad_APD_Pool, SIGNAL(triggered()), KPDGUI, SLOT(loadAPD()));

        kpdListView->setCurrentIndex(-1);


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
        actionAddPairing->setText(QApplication::translate("KPDGUI", "Add &Donor-Candidate Pairing", 0));
        actionAddPairing->setShortcut(QApplication::translate("KPDGUI", "Ctrl+P", 0));
        actionAddNDD->setText(QApplication::translate("KPDGUI", "Add Non-Directed (Altruistic) Donor", 0));
#ifndef QT_NO_TOOLTIP
        actionAddNDD->setToolTip(QApplication::translate("KPDGUI", "Add NDD", 0));
#endif // QT_NO_TOOLTIP
        actionAddNDD->setShortcut(QApplication::translate("KPDGUI", "Ctrl+Shift+P", 0));
        actionLoadPairings->setText(QApplication::translate("KPDGUI", "&Load Pairings from File", 0));
#ifndef QT_NO_TOOLTIP
        actionLoadPairings->setToolTip(QApplication::translate("KPDGUI", "Load Pairings", 0));
#endif // QT_NO_TOOLTIP
        actionLoadPairings->setShortcut(QApplication::translate("KPDGUI", "Ctrl+L", 0));
        actionExit->setText(QApplication::translate("KPDGUI", "&Exit", 0));
        actionPerformMatchRun->setText(QApplication::translate("KPDGUI", "Perform Match Run", 0));
#ifndef QT_NO_TOOLTIP
        actionPerformMatchRun->setToolTip(QApplication::translate("KPDGUI", "Perform Match Run", 0));
#endif // QT_NO_TOOLTIP
        actionPerformMatchRun->setShortcut(QApplication::translate("KPDGUI", "Ctrl+R", 0));
        actionAbout->setText(QApplication::translate("KPDGUI", "&About", 0));
        actionSetParameters->setText(QApplication::translate("KPDGUI", "Set Parameters", 0));
        actionSave->setText(QApplication::translate("KPDGUI", "&Save", 0));
        actionSave->setShortcut(QApplication::translate("KPDGUI", "Ctrl+S", 0));
        actionSaveAs->setText(QApplication::translate("KPDGUI", "&Save As", 0));
        actionSaveAs->setShortcut(QApplication::translate("KPDGUI", "Ctrl+Shift+S", 0));
        actionClearSolutions->setText(QApplication::translate("KPDGUI", "Clear Solutions", 0));
        actionZoomOut->setText(QApplication::translate("KPDGUI", "Zoom Out", 0));
        actionZoomOut->setShortcut(QApplication::translate("KPDGUI", "Ctrl+-", 0));
        actionZoomIn->setText(QApplication::translate("KPDGUI", "Zoom In", 0));
        actionZoomIn->setShortcut(QApplication::translate("KPDGUI", "Ctrl+=", 0));
        actionHandTool->setText(QApplication::translate("KPDGUI", "Hand Tool", 0));
        actionHandTool->setShortcut(QApplication::translate("KPDGUI", "Ctrl+H", 0));
        actionMouseTool->setText(QApplication::translate("KPDGUI", "Mouse Tool", 0));
        actionMouseTool->setShortcut(QApplication::translate("KPDGUI", "Ctrl+M", 0));
        actionNodeDisplaySettings->setText(QApplication::translate("KPDGUI", "Node Display Settings...", 0));
        actionNodeDisplaySettings->setShortcut(QApplication::translate("KPDGUI", "Ctrl+D", 0));
        actionDisplayNoCompatibilities->setText(QApplication::translate("KPDGUI", "Display No Matches", 0));
        actionDisplayAllCompatibilities->setText(QApplication::translate("KPDGUI", "Display All Matches", 0));
        actionDisplaySelectedCompatibilities->setText(QApplication::translate("KPDGUI", "Display Selected Matches", 0));
        actionDisplayCompatibilitiesWithinSelection->setText(QApplication::translate("KPDGUI", "Display Matches Within Selection", 0));
        actionRefresh->setText(QApplication::translate("KPDGUI", "Refresh", 0));
        actionSurvival_Calculator->setText(QApplication::translate("KPDGUI", "Survival Calculator", 0));
        actionClearArrangements->setText(QApplication::translate("KPDGUI", "Clear Arrangements", 0));
        actionFilter_Successful_Matches->setText(QApplication::translate("KPDGUI", "Successful Matches", 0));
        actionFilter_O_Donor_to_Non_O_Candidate_Matches->setText(QApplication::translate("KPDGUI", "O Donor to Non-O Candidate Matches", 0));
        actionFilter_Failed_Matches_on_Addtional_HLA->setText(QApplication::translate("KPDGUI", "Failed Matches on Addtional HLA", 0));
        actionFilter_Failed_Matches_on_Crossmatch->setText(QApplication::translate("KPDGUI", "Failed Matches on Crossmatch", 0));
        actionLoad_APD_Pool->setText(QApplication::translate("KPDGUI", "Load APD Pool", 0));
        menuFile->setTitle(QApplication::translate("KPDGUI", "&File", 0));
        menuTools->setTitle(QApplication::translate("KPDGUI", "Tools", 0));
        menuHelp->setTitle(QApplication::translate("KPDGUI", "About", 0));
        menuMatch_Run->setTitle(QApplication::translate("KPDGUI", "Match Run", 0));
        menuDisplay->setTitle(QApplication::translate("KPDGUI", "Display", 0));
        menuFilter_Matches->setTitle(QApplication::translate("KPDGUI", "Show Matches", 0));
        toolBar->setWindowTitle(QApplication::translate("KPDGUI", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class KPDGUI: public Ui_KPDGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KPDGUI_H
