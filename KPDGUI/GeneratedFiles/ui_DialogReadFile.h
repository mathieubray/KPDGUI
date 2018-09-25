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

QT_BEGIN_NAMESPACE

class Ui_DialogReadFile
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *loadLabel;
    QLineEdit *loadLineEdit;
    QToolButton *loadToolButton;
    QLabel *layoutLabel;
    QComboBox *layoutComboBox;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogReadFile)
    {
        if (DialogReadFile->objectName().isEmpty())
            DialogReadFile->setObjectName(QStringLiteral("DialogReadFile"));
        DialogReadFile->resize(415, 86);
        DialogReadFile->setMinimumSize(QSize(415, 86));
        DialogReadFile->setMaximumSize(QSize(415, 86));
        gridLayout_2 = new QGridLayout(DialogReadFile);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        loadLabel = new QLabel(DialogReadFile);
        loadLabel->setObjectName(QStringLiteral("loadLabel"));

        gridLayout->addWidget(loadLabel, 0, 0, 1, 1);

        loadLineEdit = new QLineEdit(DialogReadFile);
        loadLineEdit->setObjectName(QStringLiteral("loadLineEdit"));

        gridLayout->addWidget(loadLineEdit, 0, 1, 1, 3);

        loadToolButton = new QToolButton(DialogReadFile);
        loadToolButton->setObjectName(QStringLiteral("loadToolButton"));

        gridLayout->addWidget(loadToolButton, 0, 4, 1, 1);

        layoutLabel = new QLabel(DialogReadFile);
        layoutLabel->setObjectName(QStringLiteral("layoutLabel"));

        gridLayout->addWidget(layoutLabel, 1, 0, 1, 1);

        layoutComboBox = new QComboBox(DialogReadFile);
        layoutComboBox->setObjectName(QStringLiteral("layoutComboBox"));

        gridLayout->addWidget(layoutComboBox, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(28, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        buttonBox = new QDialogButtonBox(DialogReadFile);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 3, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(DialogReadFile);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogReadFile, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogReadFile, SLOT(reject()));
        QObject::connect(loadToolButton, SIGNAL(clicked()), DialogReadFile, SLOT(browse()));
        QObject::connect(loadLineEdit, SIGNAL(textChanged(QString)), DialogReadFile, SLOT(checkValid(QString)));

        QMetaObject::connectSlotsByName(DialogReadFile);
    } // setupUi

    void retranslateUi(QDialog *DialogReadFile)
    {
        DialogReadFile->setWindowTitle(QApplication::translate("DialogReadFile", "Load Pairings and ADs From File", 0));
        loadLabel->setText(QApplication::translate("DialogReadFile", "File", 0));
        loadToolButton->setText(QApplication::translate("DialogReadFile", "Browse...", 0));
        layoutLabel->setText(QApplication::translate("DialogReadFile", "Layout", 0));
        layoutComboBox->clear();
        layoutComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogReadFile", "Grid", 0)
         << QApplication::translate("DialogReadFile", "Circle", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class DialogReadFile: public Ui_DialogReadFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGREADFILE_H
