/********************************************************************************
** Form generated from reading UI file 'DialogReadFile.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGREADFILE_H
#define UI_DIALOGREADFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogReadFile
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *readFileVerticalLayout;
    QGridLayout *readFileGridLayout;
    QLabel *pairFileLabel;
    QLineEdit *pairFileLineEdit;
    QToolButton *pairFileToolButton;
    QSpacerItem *layoutHorizontalSpacer;
    QLabel *layoutLabel;
    QComboBox *layoutComboBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogReadFile)
    {
        if (DialogReadFile->objectName().isEmpty())
            DialogReadFile->setObjectName(QStringLiteral("DialogReadFile"));
        DialogReadFile->resize(270, 100);
        DialogReadFile->setMinimumSize(QSize(270, 100));
        DialogReadFile->setMaximumSize(QSize(270, 100));
        layoutWidget = new QWidget(DialogReadFile);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 246, 90));
        readFileVerticalLayout = new QVBoxLayout(layoutWidget);
        readFileVerticalLayout->setObjectName(QStringLiteral("readFileVerticalLayout"));
        readFileVerticalLayout->setContentsMargins(0, 0, 0, 0);
        readFileGridLayout = new QGridLayout();
        readFileGridLayout->setObjectName(QStringLiteral("readFileGridLayout"));
        pairFileLabel = new QLabel(layoutWidget);
        pairFileLabel->setObjectName(QStringLiteral("pairFileLabel"));

        readFileGridLayout->addWidget(pairFileLabel, 0, 0, 1, 1);

        pairFileLineEdit = new QLineEdit(layoutWidget);
        pairFileLineEdit->setObjectName(QStringLiteral("pairFileLineEdit"));

        readFileGridLayout->addWidget(pairFileLineEdit, 0, 1, 1, 2);

        pairFileToolButton = new QToolButton(layoutWidget);
        pairFileToolButton->setObjectName(QStringLiteral("pairFileToolButton"));

        readFileGridLayout->addWidget(pairFileToolButton, 0, 3, 1, 1);

        layoutHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        readFileGridLayout->addItem(layoutHorizontalSpacer, 1, 3, 1, 1);

        layoutLabel = new QLabel(layoutWidget);
        layoutLabel->setObjectName(QStringLiteral("layoutLabel"));

        readFileGridLayout->addWidget(layoutLabel, 1, 0, 1, 1);

        layoutComboBox = new QComboBox(layoutWidget);
        layoutComboBox->setObjectName(QStringLiteral("layoutComboBox"));

        readFileGridLayout->addWidget(layoutComboBox, 1, 1, 1, 2);


        readFileVerticalLayout->addLayout(readFileGridLayout);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        readFileVerticalLayout->addWidget(buttonBox);


        retranslateUi(DialogReadFile);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogReadFile, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogReadFile, SLOT(reject()));
        QObject::connect(pairFileToolButton, SIGNAL(clicked()), DialogReadFile, SLOT(browse()));
        QObject::connect(pairFileLineEdit, SIGNAL(textChanged(QString)), DialogReadFile, SLOT(checkValidFile(QString)));

        QMetaObject::connectSlotsByName(DialogReadFile);
    } // setupUi

    void retranslateUi(QDialog *DialogReadFile)
    {
        DialogReadFile->setWindowTitle(QApplication::translate("DialogReadFile", "Load Pairs From File", 0));
        pairFileLabel->setText(QApplication::translate("DialogReadFile", "Pair File", 0));
        pairFileToolButton->setText(QApplication::translate("DialogReadFile", "Browse...", 0));
        layoutLabel->setText(QApplication::translate("DialogReadFile", "Layout", 0));
        layoutComboBox->clear();
        layoutComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogReadFile", "Circle", 0)
         << QApplication::translate("DialogReadFile", "Grid", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class DialogReadFile: public Ui_DialogReadFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGREADFILE_H
