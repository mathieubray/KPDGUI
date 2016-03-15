/********************************************************************************
** Form generated from reading UI file 'DisplayDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYDIALOG_H
#define UI_DISPLAYDIALOG_H

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

class Ui_DisplayDialog
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *allPairsButton;
    QRadioButton *showStructuresRadioButton;
    QRadioButton *showSolutionsRadioButton;
    QRadioButton *pairSubsetButton;
    QGroupBox *displaySettingsBox;
    QCheckBox *showIncompatibleCheckBox;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QCheckBox *maxPRACheckBox;
    QSlider *horizontalSlider_2;
    QSpinBox *maxPRASpinBox;
    QSlider *horizontalSlider;
    QSpinBox *minPRASpinBox;
    QCheckBox *minPRACheckBox;
    QCheckBox *showHoldCheckBox;
    QDialogButtonBox *buttonBox;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *DisplayDialog)
    {
        if (DisplayDialog->objectName().isEmpty())
            DisplayDialog->setObjectName(QStringLiteral("DisplayDialog"));
        DisplayDialog->resize(326, 248);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DisplayDialog->sizePolicy().hasHeightForWidth());
        DisplayDialog->setSizePolicy(sizePolicy);
        DisplayDialog->setSizeGripEnabled(true);
        layoutWidget = new QWidget(DisplayDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(12, 17, 303, 221));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        allPairsButton = new QRadioButton(layoutWidget);
        buttonGroup = new QButtonGroup(DisplayDialog);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(allPairsButton);
        allPairsButton->setObjectName(QStringLiteral("allPairsButton"));
        allPairsButton->setChecked(true);

        verticalLayout->addWidget(allPairsButton);

        showStructuresRadioButton = new QRadioButton(layoutWidget);
        buttonGroup->addButton(showStructuresRadioButton);
        showStructuresRadioButton->setObjectName(QStringLiteral("showStructuresRadioButton"));

        verticalLayout->addWidget(showStructuresRadioButton);

        showSolutionsRadioButton = new QRadioButton(layoutWidget);
        buttonGroup->addButton(showSolutionsRadioButton);
        showSolutionsRadioButton->setObjectName(QStringLiteral("showSolutionsRadioButton"));

        verticalLayout->addWidget(showSolutionsRadioButton);

        pairSubsetButton = new QRadioButton(layoutWidget);
        buttonGroup->addButton(pairSubsetButton);
        pairSubsetButton->setObjectName(QStringLiteral("pairSubsetButton"));

        verticalLayout->addWidget(pairSubsetButton);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

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
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        maxPRACheckBox = new QCheckBox(layoutWidget1);
        maxPRACheckBox->setObjectName(QStringLiteral("maxPRACheckBox"));

        gridLayout->addWidget(maxPRACheckBox, 1, 0, 1, 1);

        horizontalSlider_2 = new QSlider(layoutWidget1);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setEnabled(false);
        horizontalSlider_2->setMaximum(100);
        horizontalSlider_2->setValue(100);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_2, 1, 2, 1, 1);

        maxPRASpinBox = new QSpinBox(layoutWidget1);
        maxPRASpinBox->setObjectName(QStringLiteral("maxPRASpinBox"));
        maxPRASpinBox->setEnabled(false);
        maxPRASpinBox->setMaximum(100);
        maxPRASpinBox->setValue(100);

        gridLayout->addWidget(maxPRASpinBox, 1, 1, 1, 1);

        horizontalSlider = new QSlider(layoutWidget1);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setEnabled(false);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 0, 2, 1, 1);

        minPRASpinBox = new QSpinBox(layoutWidget1);
        minPRASpinBox->setObjectName(QStringLiteral("minPRASpinBox"));
        minPRASpinBox->setEnabled(false);
        minPRASpinBox->setMaximum(100);

        gridLayout->addWidget(minPRASpinBox, 0, 1, 1, 1);

        minPRACheckBox = new QCheckBox(layoutWidget1);
        minPRACheckBox->setObjectName(QStringLiteral("minPRACheckBox"));

        gridLayout->addWidget(minPRACheckBox, 0, 0, 1, 1);

        showHoldCheckBox = new QCheckBox(displaySettingsBox);
        showHoldCheckBox->setObjectName(QStringLiteral("showHoldCheckBox"));
        showHoldCheckBox->setGeometry(QRect(10, 17, 114, 17));
        showHoldCheckBox->setChecked(true);

        gridLayout_2->addWidget(displaySettingsBox, 1, 0, 1, 2);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 0, 1, 1, 1);


        retranslateUi(DisplayDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), DisplayDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DisplayDialog, SLOT(reject()));
        QObject::connect(minPRASpinBox, SIGNAL(valueChanged(int)), horizontalSlider, SLOT(setValue(int)));
        QObject::connect(horizontalSlider, SIGNAL(sliderMoved(int)), minPRASpinBox, SLOT(setValue(int)));
        QObject::connect(maxPRASpinBox, SIGNAL(valueChanged(int)), horizontalSlider_2, SLOT(setValue(int)));
        QObject::connect(horizontalSlider_2, SIGNAL(sliderMoved(int)), maxPRASpinBox, SLOT(setValue(int)));
        QObject::connect(minPRACheckBox, SIGNAL(toggled(bool)), minPRASpinBox, SLOT(setEnabled(bool)));
        QObject::connect(minPRACheckBox, SIGNAL(toggled(bool)), horizontalSlider, SLOT(setEnabled(bool)));
        QObject::connect(maxPRACheckBox, SIGNAL(toggled(bool)), maxPRASpinBox, SLOT(setEnabled(bool)));
        QObject::connect(maxPRACheckBox, SIGNAL(toggled(bool)), horizontalSlider_2, SLOT(setEnabled(bool)));
        QObject::connect(pairSubsetButton, SIGNAL(toggled(bool)), displaySettingsBox, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(DisplayDialog);
    } // setupUi

    void retranslateUi(QDialog *DisplayDialog)
    {
        DisplayDialog->setWindowTitle(QApplication::translate("DisplayDialog", "Display Settings", 0));
        allPairsButton->setText(QApplication::translate("DisplayDialog", "Display All Pairs", 0));
        showStructuresRadioButton->setText(QApplication::translate("DisplayDialog", "Display Only Pairs in Structures", 0));
        showSolutionsRadioButton->setText(QApplication::translate("DisplayDialog", "Display Only Pairs in Solutions", 0));
        pairSubsetButton->setText(QApplication::translate("DisplayDialog", "Display Pair Subset...", 0));
        displaySettingsBox->setTitle(QApplication::translate("DisplayDialog", "Pair Subset Settings", 0));
        showIncompatibleCheckBox->setText(QApplication::translate("DisplayDialog", "Show Pairs with No Compatibilities", 0));
        maxPRACheckBox->setText(QApplication::translate("DisplayDialog", "Maximum PRA to Display", 0));
        minPRACheckBox->setText(QApplication::translate("DisplayDialog", "Minimum PRA to Display", 0));
        showHoldCheckBox->setText(QApplication::translate("DisplayDialog", "Show Pairs on Hold", 0));
    } // retranslateUi

};

namespace Ui {
    class DisplayDialog: public Ui_DisplayDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYDIALOG_H
