/********************************************************************************
** Form generated from reading UI file 'DialogDisplaySettings.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDISPLAYSETTINGS_H
#define UI_DIALOGDISPLAYSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogDisplaySettings
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *displayVerticalLayout;
    QRadioButton *allNodesButton;
    QRadioButton *showStructuresRadioButton;
    QRadioButton *showSolutionsRadioButton;
    QRadioButton *nodeSubsetButton;
    QVBoxLayout *buttonBoxVerticalLayout;
    QDialogButtonBox *buttonBox;
    QSpacerItem *verticalSpacer;
    QGroupBox *displaySettingsBox;
    QCheckBox *showIncompatibleCheckBox;
    QWidget *layoutWidget1;
    QGridLayout *displaySettingsGridLayout;
    QCheckBox *praCheckBox;
    QSpinBox *praSpinBoxRight;
    QSpinBox *praSpinBoxLeft;
    QCheckBox *showHoldCheckBox;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *DialogDisplaySettings)
    {
        if (DialogDisplaySettings->objectName().isEmpty())
            DialogDisplaySettings->setObjectName(QStringLiteral("DialogDisplaySettings"));
        DialogDisplaySettings->resize(334, 236);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogDisplaySettings->sizePolicy().hasHeightForWidth());
        DialogDisplaySettings->setSizePolicy(sizePolicy);
        DialogDisplaySettings->setMinimumSize(QSize(334, 236));
        DialogDisplaySettings->setMaximumSize(QSize(334, 236));
        DialogDisplaySettings->setSizeGripEnabled(true);
        layoutWidget = new QWidget(DialogDisplaySettings);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(13, 18, 318, 105));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        displayVerticalLayout = new QVBoxLayout();
        displayVerticalLayout->setObjectName(QStringLiteral("displayVerticalLayout"));
        allNodesButton = new QRadioButton(layoutWidget);
        buttonGroup = new QButtonGroup(DialogDisplaySettings);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(allNodesButton);
        allNodesButton->setObjectName(QStringLiteral("allNodesButton"));
        allNodesButton->setChecked(true);

        displayVerticalLayout->addWidget(allNodesButton);

        showStructuresRadioButton = new QRadioButton(layoutWidget);
        buttonGroup->addButton(showStructuresRadioButton);
        showStructuresRadioButton->setObjectName(QStringLiteral("showStructuresRadioButton"));

        displayVerticalLayout->addWidget(showStructuresRadioButton);

        showSolutionsRadioButton = new QRadioButton(layoutWidget);
        buttonGroup->addButton(showSolutionsRadioButton);
        showSolutionsRadioButton->setObjectName(QStringLiteral("showSolutionsRadioButton"));

        displayVerticalLayout->addWidget(showSolutionsRadioButton);

        nodeSubsetButton = new QRadioButton(layoutWidget);
        buttonGroup->addButton(nodeSubsetButton);
        nodeSubsetButton->setObjectName(QStringLiteral("nodeSubsetButton"));

        displayVerticalLayout->addWidget(nodeSubsetButton);


        horizontalLayout->addLayout(displayVerticalLayout);

        buttonBoxVerticalLayout = new QVBoxLayout();
        buttonBoxVerticalLayout->setObjectName(QStringLiteral("buttonBoxVerticalLayout"));
        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        buttonBoxVerticalLayout->addWidget(buttonBox);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        buttonBoxVerticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(buttonBoxVerticalLayout);

        displaySettingsBox = new QGroupBox(DialogDisplaySettings);
        displaySettingsBox->setObjectName(QStringLiteral("displaySettingsBox"));
        displaySettingsBox->setEnabled(true);
        displaySettingsBox->setGeometry(QRect(13, 128, 311, 101));
        showIncompatibleCheckBox = new QCheckBox(displaySettingsBox);
        showIncompatibleCheckBox->setObjectName(QStringLiteral("showIncompatibleCheckBox"));
        showIncompatibleCheckBox->setGeometry(QRect(10, 40, 185, 17));
        showIncompatibleCheckBox->setChecked(true);
        layoutWidget1 = new QWidget(displaySettingsBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 63, 325, 24));
        displaySettingsGridLayout = new QGridLayout(layoutWidget1);
        displaySettingsGridLayout->setObjectName(QStringLiteral("displaySettingsGridLayout"));
        displaySettingsGridLayout->setContentsMargins(0, 0, 0, 0);
        praCheckBox = new QCheckBox(layoutWidget1);
        praCheckBox->setObjectName(QStringLiteral("praCheckBox"));

        displaySettingsGridLayout->addWidget(praCheckBox, 0, 0, 1, 1);

        praSpinBoxRight = new QSpinBox(layoutWidget1);
        praSpinBoxRight->setObjectName(QStringLiteral("praSpinBoxRight"));
        praSpinBoxRight->setEnabled(false);
        praSpinBoxRight->setMaximum(100);
        praSpinBoxRight->setValue(100);

        displaySettingsGridLayout->addWidget(praSpinBoxRight, 0, 2, 1, 1);

        praSpinBoxLeft = new QSpinBox(layoutWidget1);
        praSpinBoxLeft->setObjectName(QStringLiteral("praSpinBoxLeft"));
        praSpinBoxLeft->setEnabled(false);
        praSpinBoxLeft->setMaximum(100);

        displaySettingsGridLayout->addWidget(praSpinBoxLeft, 0, 1, 1, 1);

        showHoldCheckBox = new QCheckBox(displaySettingsBox);
        showHoldCheckBox->setObjectName(QStringLiteral("showHoldCheckBox"));
        showHoldCheckBox->setGeometry(QRect(10, 17, 141, 17));
        showHoldCheckBox->setChecked(true);

        retranslateUi(DialogDisplaySettings);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogDisplaySettings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogDisplaySettings, SLOT(reject()));
        QObject::connect(nodeSubsetButton, SIGNAL(toggled(bool)), displaySettingsBox, SLOT(setEnabled(bool)));
        QObject::connect(praCheckBox, SIGNAL(toggled(bool)), praSpinBoxLeft, SLOT(setEnabled(bool)));
        QObject::connect(praCheckBox, SIGNAL(toggled(bool)), praSpinBoxRight, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(DialogDisplaySettings);
    } // setupUi

    void retranslateUi(QDialog *DialogDisplaySettings)
    {
        DialogDisplaySettings->setWindowTitle(QApplication::translate("DialogDisplaySettings", "Display Settings", 0));
        allNodesButton->setText(QApplication::translate("DialogDisplaySettings", "Display All Nodes", 0));
        showStructuresRadioButton->setText(QApplication::translate("DialogDisplaySettings", "Display Only Nodes in Structures", 0));
        showSolutionsRadioButton->setText(QApplication::translate("DialogDisplaySettings", "Display Only Nodes in Solutions", 0));
        nodeSubsetButton->setText(QApplication::translate("DialogDisplaySettings", "Display Nodes Subset...", 0));
        displaySettingsBox->setTitle(QApplication::translate("DialogDisplaySettings", "Node Subset Settings", 0));
        showIncompatibleCheckBox->setText(QApplication::translate("DialogDisplaySettings", "Show Nodes with No Compatibilities", 0));
        praCheckBox->setText(QApplication::translate("DialogDisplaySettings", "Display Candidates in PRA Range", 0));
        showHoldCheckBox->setText(QApplication::translate("DialogDisplaySettings", "Show Nodes on Hold", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogDisplaySettings: public Ui_DialogDisplaySettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDISPLAYSETTINGS_H
