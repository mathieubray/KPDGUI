/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "KPDGUIConsole.h"
#include "kpdguigraphicsview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
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
    QAction *actionSort;
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
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    KPDGUIGraphicsView *graphicsView;
    QTabWidget *tabWidget;
    KPDGUIConsole *consoleWidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;
    QMenu *menuMatch_Run;
    QMenu *menuDisplay;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1146, 777);
        MainWindow->setMinimumSize(QSize(829, 560));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/images/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionAdd_Pair = new QAction(MainWindow);
        actionAdd_Pair->setObjectName(QStringLiteral("actionAdd_Pair"));
        actionAdd_AD = new QAction(MainWindow);
        actionAdd_AD->setObjectName(QStringLiteral("actionAdd_AD"));
        actionLoad_Pairs_from_File = new QAction(MainWindow);
        actionLoad_Pairs_from_File->setObjectName(QStringLiteral("actionLoad_Pairs_from_File"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/images/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon3);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionParameters = new QAction(MainWindow);
        actionParameters->setObjectName(QStringLiteral("actionParameters"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon4);
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionView_PairInfo = new QAction(MainWindow);
        actionView_PairInfo->setObjectName(QStringLiteral("actionView_PairInfo"));
        actionView_PairInfo->setCheckable(true);
        actionView_PairInfo->setChecked(true);
        actionShow_All_Arrows = new QAction(MainWindow);
        actionShow_All_Arrows->setObjectName(QStringLiteral("actionShow_All_Arrows"));
        actionShow_All_Arrows->setCheckable(true);
        actionShow_All_Arrows->setChecked(true);
        actionShow_Compatible_Donors = new QAction(MainWindow);
        actionShow_Compatible_Donors->setObjectName(QStringLiteral("actionShow_Compatible_Donors"));
        actionShow_Compatilbe_Recipients_Only = new QAction(MainWindow);
        actionShow_Compatilbe_Recipients_Only->setObjectName(QStringLiteral("actionShow_Compatilbe_Recipients_Only"));
        actionShow_All_Compatibilities = new QAction(MainWindow);
        actionShow_All_Compatibilities->setObjectName(QStringLiteral("actionShow_All_Compatibilities"));
        actionShow_All_Compatibilities->setCheckable(true);
        actionShow_All_Compatibilities->setChecked(true);
        actionSort = new QAction(MainWindow);
        actionSort->setObjectName(QStringLiteral("actionSort"));
        actionClear_Solutions = new QAction(MainWindow);
        actionClear_Solutions->setObjectName(QStringLiteral("actionClear_Solutions"));
        actionZoom_Out = new QAction(MainWindow);
        actionZoom_Out->setObjectName(QStringLiteral("actionZoom_Out"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/images/zoomout.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_Out->setIcon(icon5);
        actionZoom_In = new QAction(MainWindow);
        actionZoom_In->setObjectName(QStringLiteral("actionZoom_In"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/images/zoomin.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom_In->setIcon(icon6);
        actionHand_Tool = new QAction(MainWindow);
        actionHand_Tool->setObjectName(QStringLiteral("actionHand_Tool"));
        actionHand_Tool->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/images/handtool.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHand_Tool->setIcon(icon7);
        actionMouse_Tool = new QAction(MainWindow);
        actionMouse_Tool->setObjectName(QStringLiteral("actionMouse_Tool"));
        actionMouse_Tool->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/images/cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMouse_Tool->setIcon(icon8);
        actionPair_AD_Settings = new QAction(MainWindow);
        actionPair_AD_Settings->setObjectName(QStringLiteral("actionPair_AD_Settings"));
        actionDisplay_No_Compatibilities = new QAction(MainWindow);
        actionDisplay_No_Compatibilities->setObjectName(QStringLiteral("actionDisplay_No_Compatibilities"));
        actionDisplay_No_Compatibilities->setCheckable(true);
        actionDisplay_All_Compatibilities = new QAction(MainWindow);
        actionDisplay_All_Compatibilities->setObjectName(QStringLiteral("actionDisplay_All_Compatibilities"));
        actionDisplay_All_Compatibilities->setCheckable(true);
        actionDisplay_Selected_Compatible_Recipients = new QAction(MainWindow);
        actionDisplay_Selected_Compatible_Recipients->setObjectName(QStringLiteral("actionDisplay_Selected_Compatible_Recipients"));
        actionDisplay_Selected_Compatible_Recipients->setCheckable(true);
        actionDisplay_Selected_Compatible_Donors = new QAction(MainWindow);
        actionDisplay_Selected_Compatible_Donors->setObjectName(QStringLiteral("actionDisplay_Selected_Compatible_Donors"));
        actionDisplay_Selected_Compatible_Donors->setCheckable(true);
        actionDisplay_Selected_Compatibilities = new QAction(MainWindow);
        actionDisplay_Selected_Compatibilities->setObjectName(QStringLiteral("actionDisplay_Selected_Compatibilities"));
        actionDisplay_Selected_Compatibilities->setCheckable(true);
        actionDisplay_Compatibilities_Within_Selection = new QAction(MainWindow);
        actionDisplay_Compatibilities_Within_Selection->setObjectName(QStringLiteral("actionDisplay_Compatibilities_Within_Selection"));
        actionDisplay_Compatibilities_Within_Selection->setCheckable(true);
        actionDisplay_Compatibilities_Within_Selection->setChecked(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget->rowCount() < 8)
            tableWidget->setRowCount(8);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(8);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font);
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font);
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font);
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font);
        tableWidget->setItem(0, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font);
        tableWidget->setItem(1, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font);
        tableWidget->setItem(2, 0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setFont(font);
        tableWidget->setItem(3, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setFont(font);
        tableWidget->setItem(4, 0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFont(font);
        tableWidget->setItem(5, 0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setFont(font);
        tableWidget->setItem(6, 0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setFont(font);
        tableWidget->setItem(7, 0, __qtablewidgetitem16);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMinimumSize(QSize(250, 263));
        tableWidget->setMaximumSize(QSize(250, 263));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setShowGrid(false);
        tableWidget->setCornerButtonEnabled(true);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(150);
        tableWidget->horizontalHeader()->setMinimumSectionSize(27);
        tableWidget->verticalHeader()->setDefaultSectionSize(30);
        tableWidget->verticalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(20);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        graphicsView = new KPDGUIGraphicsView(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMinimumSize(QSize(480, 300));
        graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
        graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

        gridLayout->addWidget(graphicsView, 0, 1, 2, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(250, 0));
        tabWidget->setMaximumSize(QSize(250, 16777215));
        tabWidget->setTabPosition(QTabWidget::West);
        tabWidget->setTabShape(QTabWidget::Triangular);

        gridLayout->addWidget(tabWidget, 1, 0, 2, 1);

        consoleWidget = new KPDGUIConsole(centralwidget);
        consoleWidget->setObjectName(QStringLiteral("consoleWidget"));
        consoleWidget->setMinimumSize(QSize(480, 150));
        consoleWidget->setMaximumSize(QSize(16777215, 150));
        consoleWidget->setTabPosition(QTabWidget::South);
        consoleWidget->setTabShape(QTabWidget::Rounded);
        consoleWidget->setElideMode(Qt::ElideNone);

        gridLayout->addWidget(consoleWidget, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1146, 31));
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
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMinimumSize(QSize(0, 30));
        toolBar->setMaximumSize(QSize(16777215, 30));
        toolBar->setMovable(false);
        toolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

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
        menuTools->addAction(actionSort);
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

        retranslateUi(MainWindow);
        QObject::connect(actionNew, SIGNAL(triggered()), MainWindow, SLOT(newFile()));
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindow, SLOT(open()));
        QObject::connect(actionClose, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(exitProgram()));
        QObject::connect(actionAbout, SIGNAL(triggered()), MainWindow, SLOT(about()));
        QObject::connect(actionSave, SIGNAL(triggered()), MainWindow, SLOT(save()));
        QObject::connect(actionSave_As, SIGNAL(triggered()), MainWindow, SLOT(saveAs()));
        QObject::connect(actionAdd_Pair, SIGNAL(triggered()), MainWindow, SLOT(addNewPair()));
        QObject::connect(actionParameters, SIGNAL(triggered()), MainWindow, SLOT(setSimParameters()));
        QObject::connect(actionLoad_Pairs_from_File, SIGNAL(triggered()), MainWindow, SLOT(loadPairs()));
        QObject::connect(actionAdd_AD, SIGNAL(triggered()), MainWindow, SLOT(addNewAD()));
        QObject::connect(actionRun, SIGNAL(triggered()), MainWindow, SLOT(run()));
        QObject::connect(actionPair_AD_Settings, SIGNAL(triggered()), MainWindow, SLOT(changePairViewMode()));
        QObject::connect(actionSort, SIGNAL(triggered()), MainWindow, SLOT(sortLists()));
        QObject::connect(actionClear_Solutions, SIGNAL(triggered()), MainWindow, SLOT(clearSolutions()));
        QObject::connect(actionView_PairInfo, SIGNAL(toggled(bool)), tableWidget, SLOT(setVisible(bool)));
        QObject::connect(actionZoom_In, SIGNAL(triggered()), MainWindow, SLOT(zoomIn()));
        QObject::connect(actionZoom_Out, SIGNAL(triggered()), MainWindow, SLOT(zoomOut()));
        QObject::connect(actionHand_Tool, SIGNAL(triggered()), MainWindow, SLOT(changeToHandMode()));
        QObject::connect(actionMouse_Tool, SIGNAL(triggered()), MainWindow, SLOT(changeToMouseMode()));
        QObject::connect(actionDisplay_All_Compatibilities, SIGNAL(triggered()), MainWindow, SLOT(changeArrowViewMode_All()));
        QObject::connect(actionDisplay_Compatibilities_Within_Selection, SIGNAL(triggered()), MainWindow, SLOT(changeArrowViewMode_Within()));
        QObject::connect(actionDisplay_No_Compatibilities, SIGNAL(triggered()), MainWindow, SLOT(changeArrowViewMode_None()));
        QObject::connect(actionDisplay_Selected_Compatibilities, SIGNAL(triggered()), MainWindow, SLOT(changeArrowViewMode_SelectedComps()));
        QObject::connect(actionDisplay_Selected_Compatible_Donors, SIGNAL(triggered()), MainWindow, SLOT(changeArrowViewMode_Donors()));
        QObject::connect(actionDisplay_Selected_Compatible_Recipients, SIGNAL(triggered()), MainWindow, SLOT(changeArrowViewMode_Recips()));

        tabWidget->setCurrentIndex(-1);
        consoleWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "KPD", 0));
        actionNew->setText(QApplication::translate("MainWindow", "&New", 0));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "&Open", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionClose->setText(QApplication::translate("MainWindow", "&Close", 0));
        actionClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionAdd_Pair->setText(QApplication::translate("MainWindow", "Add &Pair", 0));
        actionAdd_Pair->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0));
        actionAdd_AD->setText(QApplication::translate("MainWindow", "Add &AD", 0));
        actionAdd_AD->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+P", 0));
        actionLoad_Pairs_from_File->setText(QApplication::translate("MainWindow", "&Load Pairs from File", 0));
        actionLoad_Pairs_from_File->setShortcut(QApplication::translate("MainWindow", "Ctrl+L", 0));
        actionExit->setText(QApplication::translate("MainWindow", "&Exit", 0));
        actionRun->setText(QApplication::translate("MainWindow", "&Run", 0));
        actionRun->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionParameters->setText(QApplication::translate("MainWindow", "Parameters", 0));
        actionSave->setText(QApplication::translate("MainWindow", "&Save", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionSave_As->setText(QApplication::translate("MainWindow", "&Save As", 0));
        actionSave_As->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0));
        actionView_PairInfo->setText(QApplication::translate("MainWindow", "View Pair Info", 0));
        actionShow_All_Arrows->setText(QApplication::translate("MainWindow", "Show All Arrows", 0));
        actionShow_Compatible_Donors->setText(QApplication::translate("MainWindow", "Show Compatible Donors Only", 0));
        actionShow_Compatilbe_Recipients_Only->setText(QApplication::translate("MainWindow", "Show Compatilbe Recipients Only", 0));
        actionShow_All_Compatibilities->setText(QApplication::translate("MainWindow", "Show All Compatibilities", 0));
        actionSort->setText(QApplication::translate("MainWindow", "Sort...", 0));
        actionClear_Solutions->setText(QApplication::translate("MainWindow", "Clear Solutions", 0));
        actionZoom_Out->setText(QApplication::translate("MainWindow", "Zoom Out", 0));
        actionZoom_Out->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", 0));
        actionZoom_In->setText(QApplication::translate("MainWindow", "Zoom In", 0));
        actionZoom_In->setShortcut(QApplication::translate("MainWindow", "Ctrl+=", 0));
        actionHand_Tool->setText(QApplication::translate("MainWindow", "Hand Tool", 0));
        actionHand_Tool->setShortcut(QApplication::translate("MainWindow", "Ctrl+H", 0));
        actionMouse_Tool->setText(QApplication::translate("MainWindow", "Mouse Tool", 0));
        actionMouse_Tool->setShortcut(QApplication::translate("MainWindow", "Ctrl+M", 0));
        actionPair_AD_Settings->setText(QApplication::translate("MainWindow", "Pair/AD Display Settings...", 0));
        actionPair_AD_Settings->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0));
        actionDisplay_No_Compatibilities->setText(QApplication::translate("MainWindow", "Display No Compatibilities", 0));
        actionDisplay_All_Compatibilities->setText(QApplication::translate("MainWindow", "Display All Compatibilities", 0));
        actionDisplay_Selected_Compatible_Recipients->setText(QApplication::translate("MainWindow", "Display Selected Compatible Recipients", 0));
        actionDisplay_Selected_Compatible_Donors->setText(QApplication::translate("MainWindow", "Display Selected Compatible Donors", 0));
        actionDisplay_Selected_Compatibilities->setText(QApplication::translate("MainWindow", "Display Selected Compatibilities", 0));
        actionDisplay_Compatibilities_Within_Selection->setText(QApplication::translate("MainWindow", "Display Compatibilities Within Selection", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Item", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "ID", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Donor Name", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Donor Age", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Donor BT", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Candidate Name", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "Candidate Age", 0));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "Candidate BT", 0));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "Candidate PRA", 0));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "About", 0));
        menuMatch_Run->setTitle(QApplication::translate("MainWindow", "Match Run", 0));
        menuDisplay->setTitle(QApplication::translate("MainWindow", "Display", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
