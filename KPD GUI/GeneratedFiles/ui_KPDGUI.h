/********************************************************************************
** Form generated from reading UI file 'KPDGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "KPDGUIDashboard.h"
#include "KPDGUIPairList.h"
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
    QAction *actionSettings;
    QAction *actionAbout;
    QAction *actionParameters;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionView_PairInfo;
    QAction *actionShow_All_Arrows;
    QAction *actionShow_Compatible_Donors;
    QAction *actionShow_Compatilbe_Recipients_Only;
    QAction *actionShow_All_Compatibilities;
    QAction *actionClear_Solutions;
    QAction *actionZoom_Out;
    QAction *actionZoom_In;
    QAction *actionHand_Tool;
    QAction *actionMouse_Tool;
    QAction *actionPair_AD_Settings;
    QAction *actionDisplay_No_Compatibilities;
    QAction *actionDisplay_All_Compatibilities;
    QAction *actionDisplay_Selected_Compatible_Recipients;
    QAction *actionDisplay_Selected_Compatible_Donors;
    QAction *actionDisplay_Selected_Compatibilities;
    QAction *actionDisplay_Compatibilities_Within_Selection;
    QAction *actionView_Structures_Solutions;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *rightPanelLayout;
    QTreeWidget *structureWidget;
    QTreeWidget *solutionWidget;
    QVBoxLayout *centralPanelLayout;
    KPDGUIGraphicsView *graphicsView;
    KPDGUIDashboard *dashboard;
    QVBoxLayout *leftPanelLayout;
    QTableWidget *tableWidget;
    KPDGUIPairList *pairWidget;
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
        KPDGUI->resize(1060, 590);
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
        actionSettings = new QAction(KPDGUI);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
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
        actionShow_All_Arrows = new QAction(KPDGUI);
        actionShow_All_Arrows->setObjectName(QStringLiteral("actionShow_All_Arrows"));
        actionShow_All_Arrows->setCheckable(true);
        actionShow_All_Arrows->setChecked(true);
        actionShow_Compatible_Donors = new QAction(KPDGUI);
        actionShow_Compatible_Donors->setObjectName(QStringLiteral("actionShow_Compatible_Donors"));
        actionShow_Compatilbe_Recipients_Only = new QAction(KPDGUI);
        actionShow_Compatilbe_Recipients_Only->setObjectName(QStringLiteral("actionShow_Compatilbe_Recipients_Only"));
        actionShow_All_Compatibilities = new QAction(KPDGUI);
        actionShow_All_Compatibilities->setObjectName(QStringLiteral("actionShow_All_Compatibilities"));
        actionShow_All_Compatibilities->setCheckable(true);
        actionShow_All_Compatibilities->setChecked(true);
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
        actionDisplay_Selected_Compatible_Recipients = new QAction(KPDGUI);
        actionDisplay_Selected_Compatible_Recipients->setObjectName(QStringLiteral("actionDisplay_Selected_Compatible_Recipients"));
        actionDisplay_Selected_Compatible_Recipients->setCheckable(true);
        actionDisplay_Selected_Compatible_Donors = new QAction(KPDGUI);
        actionDisplay_Selected_Compatible_Donors->setObjectName(QStringLiteral("actionDisplay_Selected_Compatible_Donors"));
        actionDisplay_Selected_Compatible_Donors->setCheckable(true);
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

        gridLayout->addWidget(rightPanelLayout, 0, 2, 1, 1);

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


        gridLayout->addLayout(centralPanelLayout, 0, 1, 1, 1);

        leftPanelLayout = new QVBoxLayout();
        leftPanelLayout->setObjectName(QStringLiteral("leftPanelLayout"));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QFont font;
        font.setPointSize(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 9)
            tableWidget->setRowCount(9);
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font1);
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font1);
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font1);
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font1);
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font1);
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font1);
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font1);
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font1);
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem9);
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font2);
        tableWidget->setItem(0, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font2);
        tableWidget->setItem(1, 0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setFont(font2);
        tableWidget->setItem(2, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setFont(font2);
        tableWidget->setItem(3, 0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFont(font2);
        tableWidget->setItem(4, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setFont(font2);
        tableWidget->setItem(5, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setFont(font2);
        tableWidget->setItem(6, 0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setFont(font2);
        tableWidget->setItem(7, 0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        __qtablewidgetitem18->setFont(font2);
        tableWidget->setItem(8, 0, __qtablewidgetitem18);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(300, 200));
        tableWidget->setMaximumSize(QSize(300, 200));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setShowGrid(false);
        tableWidget->setCornerButtonEnabled(true);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(197);
        tableWidget->horizontalHeader()->setMinimumSectionSize(197);
        tableWidget->verticalHeader()->setDefaultSectionSize(22);
        tableWidget->verticalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(22);

        leftPanelLayout->addWidget(tableWidget);

        pairWidget = new KPDGUIPairList(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(6, Qt::AlignLeft|Qt::AlignVCenter);
        __qtreewidgetitem->setTextAlignment(5, Qt::AlignLeft|Qt::AlignVCenter);
        __qtreewidgetitem->setTextAlignment(4, Qt::AlignLeft|Qt::AlignVCenter);
        __qtreewidgetitem->setTextAlignment(3, Qt::AlignLeft|Qt::AlignVCenter);
        __qtreewidgetitem->setTextAlignment(2, Qt::AlignLeft|Qt::AlignVCenter);
        pairWidget->setHeaderItem(__qtreewidgetitem);
        pairWidget->setObjectName(QStringLiteral("pairWidget"));
        pairWidget->setMinimumSize(QSize(300, 0));
        pairWidget->setMaximumSize(QSize(300, 16777215));
        pairWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        pairWidget->setAlternatingRowColors(true);
        pairWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        pairWidget->setSortingEnabled(true);

        leftPanelLayout->addWidget(pairWidget);


        gridLayout->addLayout(leftPanelLayout, 0, 0, 1, 1);

        KPDGUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(KPDGUI);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1060, 21));
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
        menuTools->addAction(actionView_PairInfo);
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
        menuDisplay->addAction(actionDisplay_Selected_Compatible_Donors);
        menuDisplay->addAction(actionDisplay_Selected_Compatible_Recipients);
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
        QObject::connect(actionNew, SIGNAL(triggered()), KPDGUI, SLOT(newFile()));
        QObject::connect(actionOpen, SIGNAL(triggered()), KPDGUI, SLOT(open()));
        QObject::connect(actionClose, SIGNAL(triggered()), KPDGUI, SLOT(close()));
        QObject::connect(actionExit, SIGNAL(triggered()), KPDGUI, SLOT(exitProgram()));
        QObject::connect(actionAbout, SIGNAL(triggered()), KPDGUI, SLOT(about()));
        QObject::connect(actionSave, SIGNAL(triggered()), KPDGUI, SLOT(save()));
        QObject::connect(actionSave_As, SIGNAL(triggered()), KPDGUI, SLOT(saveAs()));
        QObject::connect(actionAdd_Pair, SIGNAL(triggered()), KPDGUI, SLOT(addNewPair()));
        QObject::connect(actionParameters, SIGNAL(triggered()), KPDGUI, SLOT(setSimParameters()));
        QObject::connect(actionLoad_Pairs_from_File, SIGNAL(triggered()), KPDGUI, SLOT(loadPairs()));
        QObject::connect(actionAdd_AD, SIGNAL(triggered()), KPDGUI, SLOT(addNewAD()));
        QObject::connect(actionRun, SIGNAL(triggered()), KPDGUI, SLOT(run()));
        QObject::connect(actionPair_AD_Settings, SIGNAL(triggered()), KPDGUI, SLOT(changePairViewMode()));
        QObject::connect(actionClear_Solutions, SIGNAL(triggered()), KPDGUI, SLOT(clearSolutions()));
        QObject::connect(actionView_PairInfo, SIGNAL(toggled(bool)), tableWidget, SLOT(setVisible(bool)));
        QObject::connect(actionZoom_In, SIGNAL(triggered()), KPDGUI, SLOT(zoomIn()));
        QObject::connect(actionZoom_Out, SIGNAL(triggered()), KPDGUI, SLOT(zoomOut()));
        QObject::connect(actionHand_Tool, SIGNAL(triggered()), KPDGUI, SLOT(changeToHandMode()));
        QObject::connect(actionMouse_Tool, SIGNAL(triggered()), KPDGUI, SLOT(changeToMouseMode()));
        QObject::connect(actionDisplay_All_Compatibilities, SIGNAL(triggered()), KPDGUI, SLOT(changeArrowViewMode_All()));
        QObject::connect(actionDisplay_Compatibilities_Within_Selection, SIGNAL(triggered()), KPDGUI, SLOT(changeArrowViewMode_Within()));
        QObject::connect(actionDisplay_No_Compatibilities, SIGNAL(triggered()), KPDGUI, SLOT(changeArrowViewMode_None()));
        QObject::connect(actionDisplay_Selected_Compatibilities, SIGNAL(triggered()), KPDGUI, SLOT(changeArrowViewMode_SelectedComps()));
        QObject::connect(actionDisplay_Selected_Compatible_Donors, SIGNAL(triggered()), KPDGUI, SLOT(changeArrowViewMode_Donors()));
        QObject::connect(actionDisplay_Selected_Compatible_Recipients, SIGNAL(triggered()), KPDGUI, SLOT(changeArrowViewMode_Recips()));
        QObject::connect(actionView_Structures_Solutions, SIGNAL(toggled(bool)), structureWidget, SLOT(setVisible(bool)));
        QObject::connect(actionView_Structures_Solutions, SIGNAL(toggled(bool)), solutionWidget, SLOT(setVisible(bool)));
        QObject::connect(graphicsView, SIGNAL(customContextMenuRequested(QPoint)), KPDGUI, SLOT(screenCustomMenu(QPoint)));
        QObject::connect(graphicsView, SIGNAL(zoomIn()), KPDGUI, SLOT(zoomIn()));
        QObject::connect(graphicsView, SIGNAL(zoomOut()), KPDGUI, SLOT(zoomOut()));
        QObject::connect(graphicsView, SIGNAL(mouseReleased()), KPDGUI, SLOT(updateVisibility()));

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
        actionAdd_Pair->setText(QApplication::translate("KPDGUI", "Add &Pair", 0));
        actionAdd_Pair->setShortcut(QApplication::translate("KPDGUI", "Ctrl+P", 0));
        actionAdd_AD->setText(QApplication::translate("KPDGUI", "Add &AD", 0));
        actionAdd_AD->setShortcut(QApplication::translate("KPDGUI", "Ctrl+Shift+P", 0));
        actionLoad_Pairs_from_File->setText(QApplication::translate("KPDGUI", "&Load Pairs from File", 0));
        actionLoad_Pairs_from_File->setShortcut(QApplication::translate("KPDGUI", "Ctrl+L", 0));
        actionExit->setText(QApplication::translate("KPDGUI", "&Exit", 0));
        actionRun->setText(QApplication::translate("KPDGUI", "&Run", 0));
        actionRun->setShortcut(QApplication::translate("KPDGUI", "Ctrl+R", 0));
        actionSettings->setText(QApplication::translate("KPDGUI", "Settings", 0));
        actionAbout->setText(QApplication::translate("KPDGUI", "About", 0));
        actionParameters->setText(QApplication::translate("KPDGUI", "Parameters", 0));
        actionSave->setText(QApplication::translate("KPDGUI", "&Save", 0));
        actionSave->setShortcut(QApplication::translate("KPDGUI", "Ctrl+S", 0));
        actionSave_As->setText(QApplication::translate("KPDGUI", "&Save As", 0));
        actionSave_As->setShortcut(QApplication::translate("KPDGUI", "Ctrl+Shift+S", 0));
        actionView_PairInfo->setText(QApplication::translate("KPDGUI", "View Pair Info", 0));
        actionShow_All_Arrows->setText(QApplication::translate("KPDGUI", "Show All Arrows", 0));
        actionShow_Compatible_Donors->setText(QApplication::translate("KPDGUI", "Show Compatible Donors Only", 0));
        actionShow_Compatilbe_Recipients_Only->setText(QApplication::translate("KPDGUI", "Show Compatilbe Recipients Only", 0));
        actionShow_All_Compatibilities->setText(QApplication::translate("KPDGUI", "Show All Compatibilities", 0));
        actionClear_Solutions->setText(QApplication::translate("KPDGUI", "Clear Solutions", 0));
        actionZoom_Out->setText(QApplication::translate("KPDGUI", "Zoom Out", 0));
        actionZoom_Out->setShortcut(QApplication::translate("KPDGUI", "Ctrl+-", 0));
        actionZoom_In->setText(QApplication::translate("KPDGUI", "Zoom In", 0));
        actionZoom_In->setShortcut(QApplication::translate("KPDGUI", "Ctrl+=", 0));
        actionHand_Tool->setText(QApplication::translate("KPDGUI", "Hand Tool", 0));
        actionHand_Tool->setShortcut(QApplication::translate("KPDGUI", "Ctrl+H", 0));
        actionMouse_Tool->setText(QApplication::translate("KPDGUI", "Mouse Tool", 0));
        actionMouse_Tool->setShortcut(QApplication::translate("KPDGUI", "Ctrl+M", 0));
        actionPair_AD_Settings->setText(QApplication::translate("KPDGUI", "Pair/AD Display Settings...", 0));
        actionPair_AD_Settings->setShortcut(QApplication::translate("KPDGUI", "Ctrl+D", 0));
        actionDisplay_No_Compatibilities->setText(QApplication::translate("KPDGUI", "Display No Compatibilities", 0));
        actionDisplay_All_Compatibilities->setText(QApplication::translate("KPDGUI", "Display All Compatibilities", 0));
        actionDisplay_Selected_Compatible_Recipients->setText(QApplication::translate("KPDGUI", "Display Selected Compatible Recipients", 0));
        actionDisplay_Selected_Compatible_Donors->setText(QApplication::translate("KPDGUI", "Display Selected Compatible Donors", 0));
        actionDisplay_Selected_Compatibilities->setText(QApplication::translate("KPDGUI", "Display Selected Compatibilities", 0));
        actionDisplay_Compatibilities_Within_Selection->setText(QApplication::translate("KPDGUI", "Display Compatibilities Within Selection", 0));
        actionView_Structures_Solutions->setText(QApplication::translate("KPDGUI", "View Structures/Solutions", 0));
        QTreeWidgetItem *___qtreewidgetitem = structureWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("KPDGUI", "Structures", 0));
        QTreeWidgetItem *___qtreewidgetitem1 = solutionWidget->headerItem();
        ___qtreewidgetitem1->setText(0, QApplication::translate("KPDGUI", "Solutions", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("KPDGUI", "Item", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("KPDGUI", "ID", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("KPDGUI", "Donor Name", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("KPDGUI", "Donor Age", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("KPDGUI", "Donor BT", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("KPDGUI", "Candidate Name", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QApplication::translate("KPDGUI", "Candidate Age", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem7->setText(QApplication::translate("KPDGUI", "Candidate BT", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem8->setText(QApplication::translate("KPDGUI", "Candidate PRA", 0));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem9->setText(QApplication::translate("KPDGUI", "Other Donors", 0));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        QTreeWidgetItem *___qtreewidgetitem2 = pairWidget->headerItem();
        ___qtreewidgetitem2->setText(6, QApplication::translate("KPDGUI", "Comp. Recipients", 0));
        ___qtreewidgetitem2->setText(5, QApplication::translate("KPDGUI", "Comp. Donors", 0));
        ___qtreewidgetitem2->setText(4, QApplication::translate("KPDGUI", "Solutions", 0));
        ___qtreewidgetitem2->setText(3, QApplication::translate("KPDGUI", "Structures", 0));
        ___qtreewidgetitem2->setText(2, QApplication::translate("KPDGUI", "Donors", 0));
        ___qtreewidgetitem2->setText(1, QApplication::translate("KPDGUI", "Name", 0));
        ___qtreewidgetitem2->setText(0, QApplication::translate("KPDGUI", "Pair/AD", 0));
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
