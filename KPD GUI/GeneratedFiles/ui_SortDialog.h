/********************************************************************************
** Form generated from reading UI file 'SortDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SORTDIALOG_H
#define UI_SORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SortDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *pairsComboBox;
    QCheckBox *pairsDecreasingCheckBox;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QComboBox *matchesComboBox;
    QCheckBox *matchesDecreasingCheckBox;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SortDialog)
    {
        if (SortDialog->objectName().isEmpty())
            SortDialog->setObjectName(QStringLiteral("SortDialog"));
        SortDialog->resize(177, 221);
        layoutWidget = new QWidget(SortDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 158, 201));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        pairsComboBox = new QComboBox(layoutWidget);
        pairsComboBox->setObjectName(QStringLiteral("pairsComboBox"));

        verticalLayout->addWidget(pairsComboBox);

        pairsDecreasingCheckBox = new QCheckBox(layoutWidget);
        pairsDecreasingCheckBox->setObjectName(QStringLiteral("pairsDecreasingCheckBox"));

        verticalLayout->addWidget(pairsDecreasingCheckBox);

        verticalSpacer = new QSpacerItem(13, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        matchesComboBox = new QComboBox(layoutWidget);
        matchesComboBox->setObjectName(QStringLiteral("matchesComboBox"));

        verticalLayout->addWidget(matchesComboBox);

        matchesDecreasingCheckBox = new QCheckBox(layoutWidget);
        matchesDecreasingCheckBox->setObjectName(QStringLiteral("matchesDecreasingCheckBox"));

        verticalLayout->addWidget(matchesDecreasingCheckBox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SortDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SortDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SortDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SortDialog);
    } // setupUi

    void retranslateUi(QDialog *SortDialog)
    {
        SortDialog->setWindowTitle(QApplication::translate("SortDialog", "Sort...", 0));
        label->setText(QApplication::translate("SortDialog", "Sort Pairs By", 0));
        pairsComboBox->clear();
        pairsComboBox->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "ID Number", 0)
         << QApplication::translate("SortDialog", "Popularity (Solutions)", 0)
         << QApplication::translate("SortDialog", "Popularity (Structures)", 0)
         << QApplication::translate("SortDialog", "Compatibilities", 0)
         << QApplication::translate("SortDialog", "Compatible Donors", 0)
         << QApplication::translate("SortDialog", "Compatible Recipients", 0)
         << QApplication::translate("SortDialog", "PRA", 0)
        );
        pairsDecreasingCheckBox->setText(QApplication::translate("SortDialog", "Decreasing", 0));
        label_2->setText(QApplication::translate("SortDialog", "Sort Matches By", 0));
        matchesComboBox->clear();
        matchesComboBox->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "Popularity (Solutions)", 0)
         << QApplication::translate("SortDialog", "Popularity (Structures)", 0)
         << QApplication::translate("SortDialog", "Donor ID Number", 0)
         << QApplication::translate("SortDialog", "Candidate ID Number", 0)
        );
        matchesDecreasingCheckBox->setText(QApplication::translate("SortDialog", "Decreasing", 0));
    } // retranslateUi

};

namespace Ui {
    class SortDialog: public Ui_SortDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SORTDIALOG_H
