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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogDisplaySettings
{
public:
    QWidget *layoutWidget;
    QGridLayout *displayGridLayout;
    QVBoxLayout *displayVerticalLayout;
    QRadioButton *allPairsButton;
    QRadioButton *showStructuresRadioButton;
    QRadioButton *showSolutionsRadioButton;
    QRadioButton *pairSubsetButton;
    QGroupBox *displaySettingsBox;
    QCheckBox *showIncompatibleCheckBox;
    QWidget *layoutWidget1;
    QGridLayout *displaySettingsGridLayout;
    QCheckBox *maxPRACheckBox;
    QSlider *minPRASlider;
    QSpinBox *maxPRASpinBox;
    QSlider *minPRAHorizontalSlider;
    QSpinBox *minPRASpinBox;
    QCheckBox *minPRACheckBox;
    QCheckBox *showHoldCheckBox;
    QDialogButtonBox *buttonBox;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *DialogDisplaySettings)
    {
        if (DialogDisplaySettings->objectName().isEmpty())
            DialogDisplaySettings->setObjectName(QStringLiteral("DialogDisplaySettings"));
        DialogDisplaySettings->resize(326, 248);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogDisplaySettings->sizePolicy().hasHeightForWidth());
        DialogDisplaySettings->setSizePolicy(sizePolicy);
        DialogDisplaySettings->setSizeGripEnabled(true);
        layoutWidget = new QWidget(DialogDisplaySettings);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(12, 17, 303, 221));
        displayGridLayout = new QGridLayout(layoutWidget);
        displayGridLayout->setObjectName(QStringLiteral("displayGridLayout"));
        displayGridLayout->setContentsMargins(0, 0, 0, 0);
        displayVerticalLayout = new QVBoxLayout();
        displayVerticalLayout->setObjectName(QStringLiteral("displayVerticalLayout"));
        allPairsButton = new QRadioButton(layoutWidget);
        buttonGroup = new QButtonGroup(DialogDisplaySettings);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(allPairsButton);
        allPairsButton->setObjectName(QStringLiteral("allPairsButton"));
        allPairsButton->setChecked(true);

        displayVerticalLayout->addWidget(allPairsButton);

        showStructuresRadioButton = new QRadioButton(layoutWidget);
        buttonGroup->addButton(showStructuresRadioButton);
        showStructuresRadioButton->setObjectName(QStringLiteral("showStructuresRadioButton"));

        displayVerticalLayout->addWidget(showStructuresRadioButton);

        showSolutionsRadioButton = new QRadioButton(layoutWidget);
        buttonGroup->addButton(showSolutionsRadioButton);
        showSolutionsRadioButton->setObjectName(QStringLiteral("showSolutionsRadioButton"));

        displayVerticalLayout->addWidget(showSolutionsRadioButton);

        pairSubsetButton = new QRadioButton(layoutWidget);
        buttonGroup->addButton(pairSubsetButton);
        pairSubsetButton->setObjectName(QStringLiteral("pairSubsetButton"));

        displayVerticalLayout->addWidget(pairSubsetButton);


        displayGridLayout->addLayout(displayVerticalLayout, 0, 0, 1, 1);

        displaySettingsBox = new QGroupBox(layoutWidget);
        displaySettingsBox->setObjectName(QStringLiteral("displaySettingsBox"));
        displaySettingsBox->setEnabled(true);
        displaySettingsBox->setMinimumSize(QSize(301, 121));
        displaySettingsBox->setMaximumSize(QSize(301, 121));
        showIncompatibleCheckBox = new QCheckBox(displaySettingsBox);
        showIncompatibleCheckBox->setObjectName(QStringLiteral("showIncompatibleCheckBox"));
        showIncompatibleCheckBox->setGeometry(QRect(10, 40, 185, 17));
        showIncompatibleCheckBox->setChecked(true);
        layoutWidget1 = new QWidget(displaySettingsBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 63, 281, 48));
        displaySettingsGridLayout = new QGridLayout(layoutWidget1);
        displaySettingsGridLayout->setObjectName(QStringLiteral("displaySettingsGridLayout"));
        displaySettingsGridLayout->setContentsMargins(0, 0, 0, 0);
        maxPRACheckBox = new QCheckBox(layoutWidget1);
        maxPRACheckBox->setObjectName(QStringLiteral("maxPRACheckBox"));

        displaySettingsGridLayout->addWidget(maxPRACheckBox, 1, 0, 1, 1);

        minPRASlider = new QSlider(layoutWidget1);
        minPRASlider->setObjectName(QStringLiteral("minPRASlider"));
        minPRASlider->setEnabled(false);
        minPRASlider->setMaximum(100);
        minPRASlider->setValue(100);
        minPRASlider->setOrientation(Qt::Horizontal);

        displaySettingsGridLayout->addWidget(minPRASlider, 1, 2, 1, 1);

        maxPRASpinBox = new QSpinBox(layoutWidget1);
        maxPRASpinBox->setObjectName(QStringLiteral("maxPRASpinBox"));
        maxPRASpinBox->setEnabled(false);
        maxPRASpinBox->setMaximum(100);
        maxPRASpinBox->setValue(100);

        displaySettingsGridLayout->addWidget(maxPRASpinBox, 1, 1, 1, 1);

        minPRAHorizontalSlider = new QSlider(layoutWidget1);
        minPRAHorizontalSlider->setObjectName(QStringLiteral("minPRAHorizontalSlider"));
        minPRAHorizontalSlider->setEnabled(false);
        minPRAHorizontalSlider->setMaximum(100);
        minPRAHorizontalSlider->setOrientation(Qt::Horizontal);

        displaySettingsGridLayout->addWidget(minPRAHorizontalSlider, 0, 2, 1, 1);

        minPRASpinBox = new QSpinBox(layoutWidget1);
        minPRASpinBox->setObjectName(QStringLiteral("minPRASpinBox"));
        minPRASpinBox->setEnabled(false);
        minPRASpinBox->setMaximum(100);

        displaySettingsGridLayout->addWidget(minPRASpinBox, 0, 1, 1, 1);

        minPRACheckBox = new QCheckBox(layoutWidget1);
        minPRACheckBox->setObjectName(QStringLiteral("minPRACheckBox"));

        displaySettingsGridLayout->addWidget(minPRACheckBox, 0, 0, 1, 1);

        showHoldCheckBox = new QCheckBox(displaySettingsBox);
        showHoldCheckBox->setObjectName(QStringLiteral("showHoldCheckBox"));
        showHoldCheckBox->setGeometry(QRect(10, 17, 114, 17));
        showHoldCheckBox->setChecked(true);

        displayGridLayout->addWidget(displaySettingsBox, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        displayGridLayout->addWidget(buttonBox, 0, 1, 1, 1);


        retranslateUi(DialogDisplaySettings);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogDisplaySettings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogDisplaySettings, SLOT(reject()));
        QObject::connect(minPRASpinBox, SIGNAL(valueChanged(int)), minPRAHorizontalSlider, SLOT(setValue(int)));
        QObject::connect(minPRAHorizontalSlider, SIGNAL(sliderMoved(int)), minPRASpinBox, SLOT(setValue(int)));
        QObject::connect(maxPRASpinBox, SIGNAL(valueChanged(int)), minPRASlider, SLOT(setValue(int)));
        QObject::connect(minPRASlider, SIGNAL(sliderMoved(int)), maxPRASpinBox, SLOT(setValue(int)));
        QObject::connect(minPRACheckBox, SIGNAL(toggled(bool)), minPRASpinBox, SLOT(setEnabled(bool)));
        QObject::connect(minPRACheckBox, SIGNAL(toggled(bool)), minPRAHorizontalSlider, SLOT(setEnabled(bool)));
        QObject::connect(maxPRACheckBox, SIGNAL(toggled(bool)), maxPRASpinBox, SLOT(setEnabled(bool)));
        QObject::connect(maxPRACheckBox, SIGNAL(toggled(bool)), minPRASlider, SLOT(setEnabled(bool)));
        QObject::connect(pairSubsetButton, SIGNAL(toggled(bool)), displaySettingsBox, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(DialogDisplaySettings);
    } // setupUi

    void retranslateUi(QDialog *DialogDisplaySettings)
    {
        DialogDisplaySettings->setWindowTitle(QApplication::translate("DialogDisplaySettings", "Display Settings", 0));
        allPairsButton->setText(QApplication::translate("DialogDisplaySettings", "Display All Pairs", 0));
        showStructuresRadioButton->setText(QApplication::translate("DialogDisplaySettings", "Display Only Pairs in Structures", 0));
        showSolutionsRadioButton->setText(QApplication::translate("DialogDisplaySettings", "Display Only Pairs in Solutions", 0));
        pairSubsetButton->setText(QApplication::translate("DialogDisplaySettings", "Display Pair Subset...", 0));
        displaySettingsBox->setTitle(QApplication::translate("DialogDisplaySettings", "Pair Subset Settings", 0));
        showIncompatibleCheckBox->setText(QApplication::translate("DialogDisplaySettings", "Show Pairs with No Compatibilities", 0));
        maxPRACheckBox->setText(QApplication::translate("DialogDisplaySettings", "Maximum PRA to Display", 0));
        minPRACheckBox->setText(QApplication::translate("DialogDisplaySettings", "Minimum PRA to Display", 0));
        showHoldCheckBox->setText(QApplication::translate("DialogDisplaySettings", "Show Pairs on Hold", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogDisplaySettings: public Ui_DialogDisplaySettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDISPLAYSETTINGS_H
