/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

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
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QListView *listView;
    QGraphicsView *graphicsView;
    QTextBrowser *textBrowser;
    QTableView *tableView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;
    QMenu *menuMatch_Run;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(679, 504);
        MainWindow->setMinimumSize(QSize(679, 504));
        MainWindow->setMaximumSize(QSize(679, 504));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/newPrefix/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/newPrefix/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
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
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionParameters = new QAction(MainWindow);
        actionParameters->setObjectName(QStringLiteral("actionParameters"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/newPrefix/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 671, 461));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        listView = new QListView(layoutWidget);
        listView->setObjectName(QStringLiteral("listView"));

        gridLayout->addWidget(listView, 0, 0, 1, 1);

        graphicsView = new QGraphicsView(layoutWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 1, 2, 1);

        textBrowser = new QTextBrowser(layoutWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 2, 2, 1);

        tableView = new QTableView(layoutWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 679, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuMatch_Run = new QMenu(menubar);
        menuMatch_Run->setObjectName(QStringLiteral("menuMatch_Run"));
        MainWindow->setMenuBar(menubar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuMatch_Run->menuAction());
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
        menuTools->addAction(actionSettings);
        menuHelp->addAction(actionAbout);
        menuMatch_Run->addAction(actionRun);
        menuMatch_Run->addAction(actionParameters);

        retranslateUi(MainWindow);
        QObject::connect(actionNew, SIGNAL(triggered()), MainWindow, SLOT(newFile()));
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindow, SLOT(open()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
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
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuMatch_Run->setTitle(QApplication::translate("MainWindow", "Match Run", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
