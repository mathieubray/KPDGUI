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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogDisplaySettings
{
public:
    QGroupBox *displaySettingsBox;
    QCheckBox *showIncompatibleCheckBox;
    QWidget *layoutWidget;
    QGridLayout *displaySettingsGridLayout;
    QCheckBox *praCheckBox;
    QSpinBox *praSpinBoxRight;
    QSpinBox *praSpinBoxLeft;
    QCheckBox *showExcludedCheckBox;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *nodeDisplayModeLabel;
    QComboBox *nodeDisplayModeComboBox;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;
    QVBoxLayout *displayVerticalLayout;
    QRadioButton *allNodesButton;
    QRadioButton *showArrangementsRadioButton;
    QRadioButton *showSolutionsRadioButton;
    QRadioButton *nodeSubsetButton;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *DialogDisplaySettings)
    {
        if (DialogDisplaySettings->objectName().isEmpty())
            DialogDisplaySettings->setObjectName(QStringLiteral("DialogDisplaySettings"));
        DialogDisplaySettings->resize(425, 323);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogDisplaySettings->sizePolicy().hasHeightForWidth());
        DialogDisplaySettings->setSizePolicy(sizePolicy);
        DialogDisplaySettings->setMinimumSize(QSize(425, 323));
        DialogDisplaySettings->setMaximumSize(QSize(425, 323));
        DialogDisplaySettings->setSizeGripEnabled(true);
        displaySettingsBox = new QGroupBox(DialogDisplaySettings);
        displaySettingsBox->setObjectName(QStringLiteral("displaySettingsBox"));
        displaySettingsBox->setEnabled(true);
        displaySettingsBox->setGeometry(QRect(10, 200, 401, 111));
        showIncompatibleCheckBox = new QCheckBox(displaySettingsBox);
        showIncompatibleCheckBox->setObjectName(QStringLiteral("showIncompatibleCheckBox"));
        showIncompatibleCheckBox->setGeometry(QRect(10, 53, 311, 17));
        showIncompatibleCheckBox->setChecked(true);
        layoutWidget = new QWidget(displaySettingsBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 73, 385, 24));
        displaySettingsGridLayout = new QGridLayout(layoutWidget);
        displaySettingsGridLayout->setObjectName(QStringLiteral("displaySettingsGridLayout"));
        displaySettingsGridLayout->setContentsMargins(0, 0, 0, 0);
        praCheckBox = new QCheckBox(layoutWidget);
        praCheckBox->setObjectName(QStringLiteral("praCheckBox"));

        displaySettingsGridLayout->addWidget(praCheckBox, 0, 0, 1, 1);

        praSpinBoxRight = new QSpinBox(layoutWidget);
        praSpinBoxRight->setObjectName(QStringLiteral("praSpinBoxRight"));
        praSpinBoxRight->setEnabled(false);
        praSpinBoxRight->setMaximum(100);
        praSpinBoxRight->setValue(100);

        displaySettingsGridLayout->addWidget(praSpinBoxRight, 0, 2, 1, 1);

        praSpinBoxLeft = new QSpinBox(layoutWidget);
        praSpinBoxLeft->setObjectName(QStringLiteral("praSpinBoxLeft"));
        praSpinBoxLeft->setEnabled(false);
        praSpinBoxLeft->setMaximum(100);

        displaySettingsGridLayout->addWidget(praSpinBoxLeft, 0, 1, 1, 1);

        showExcludedCheckBox = new QCheckBox(displaySettingsBox);
        showExcludedCheckBox->setObjectName(QStringLiteral("showExcludedCheckBox"));
        showExcludedCheckBox->setGeometry(QRect(10, 30, 291, 17));
        showExcludedCheckBox->setChecked(true);
        layoutWidget1 = new QWidget(DialogDisplaySettings);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 404, 178));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        nodeDisplayModeLabel = new QLabel(layoutWidget1);
        nodeDisplayModeLabel->setObjectName(QStringLiteral("nodeDisplayModeLabel"));

        verticalLayout->addWidget(nodeDisplayModeLabel);

        nodeDisplayModeComboBox = new QComboBox(layoutWidget1);
        nodeDisplayModeComboBox->setObjectName(QStringLiteral("nodeDisplayModeComboBox"));

        verticalLayout->addWidget(nodeDisplayModeComboBox);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(layoutWidget1);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 0, 1, 1, 1);

        displayVerticalLayout = new QVBoxLayout();
        displayVerticalLayout->setObjectName(QStringLiteral("displayVerticalLayout"));
        allNodesButton = new QRadioButton(layoutWidget1);
        buttonGroup = new QButtonGroup(DialogDisplaySettings);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(allNodesButton);
        allNodesButton->setObjectName(QStringLiteral("allNodesButton"));
        allNodesButton->setChecked(true);

        displayVerticalLayout->addWidget(allNodesButton);

        showArrangementsRadioButton = new QRadioButton(layoutWidget1);
        buttonGroup->addButton(showArrangementsRadioButton);
        showArrangementsRadioButton->setObjectName(QStringLiteral("showArrangementsRadioButton"));

        displayVerticalLayout->addWidget(showArrangementsRadioButton);

        showSolutionsRadioButton = new QRadioButton(layoutWidget1);
        buttonGroup->addButton(showSolutionsRadioButton);
        showSolutionsRadioButton->setObjectName(QStringLiteral("showSolutionsRadioButton"));

        displayVerticalLayout->addWidget(showSolutionsRadioButton);

        nodeSubsetButton = new QRadioButton(layoutWidget1);
        buttonGroup->addButton(nodeSubsetButton);
        nodeSubsetButton->setObjectName(QStringLiteral("nodeSubsetButton"));

        displayVerticalLayout->addWidget(nodeSubsetButton);


        gridLayout->addLayout(displayVerticalLayout, 1, 0, 1, 2);


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
        displaySettingsBox->setTitle(QApplication::translate("DialogDisplaySettings", "Node Subset Settings", 0));
        showIncompatibleCheckBox->setText(QApplication::translate("DialogDisplaySettings", "Show Pairs/ADs with No Compatibilities", 0));
        praCheckBox->setText(QApplication::translate("DialogDisplaySettings", "Display Pairs with Candidates in PRA Range", 0));
        showExcludedCheckBox->setText(QApplication::translate("DialogDisplaySettings", "Show Pairs/ADs Excluded From Match Runs", 0));
        nodeDisplayModeLabel->setText(QApplication::translate("DialogDisplaySettings", "Network Display Mode:", 0));
        nodeDisplayModeComboBox->clear();
        nodeDisplayModeComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogDisplaySettings", "Display Donors and Candidate Separately", 0)
         << QApplication::translate("DialogDisplaySettings", "Display Donors and Candidate as a Single Node", 0)
        );
        allNodesButton->setText(QApplication::translate("DialogDisplaySettings", "Display All Pairs/ADs", 0));
        showArrangementsRadioButton->setText(QApplication::translate("DialogDisplaySettings", "Display Only Pairs/ADs Involved in Transplant Arrangements", 0));
        showSolutionsRadioButton->setText(QApplication::translate("DialogDisplaySettings", "Display Only Pairs/ADs Involved in Solutions", 0));
        nodeSubsetButton->setText(QApplication::translate("DialogDisplaySettings", "Display Pair/ADs Subset...", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogDisplaySettings: public Ui_DialogDisplaySettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDISPLAYSETTINGS_H
