/********************************************************************************
** Form generated from reading UI file 'DisplayDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DisplayDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QRadioButton *allPairsButton;
    QRadioButton *showStructuresRadioButton;
    QRadioButton *showSolutionsRadioButton;
    QRadioButton *pairSubsetButton;
    QDialogButtonBox *buttonBox;
    QGroupBox *displaySettingsBox;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *showHoldCheckBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *showIncompatibleCheckBox;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QCheckBox *maxPRACheckBox;
    QSlider *horizontalSlider_2;
    QSpinBox *maxPRASpinBox;
    QSlider *horizontalSlider;
    QSpinBox *minPRASpinBox;
    QCheckBox *minPRACheckBox;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *DisplayDialog)
    {
        if (DisplayDialog->objectName().isEmpty())
            DisplayDialog->setObjectName(QStringLiteral("DisplayDialog"));
        DisplayDialog->resize(426, 343);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DisplayDialog->sizePolicy().hasHeightForWidth());
        DisplayDialog->setSizePolicy(sizePolicy);
        DisplayDialog->setMinimumSize(QSize(426, 343));
        DisplayDialog->setMaximumSize(QSize(426, 343));
        DisplayDialog->setSizeGripEnabled(true);
        widget = new QWidget(DisplayDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(13, 18, 271, 121));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        allPairsButton = new QRadioButton(widget);
        buttonGroup = new QButtonGroup(DisplayDialog);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(allPairsButton);
        allPairsButton->setObjectName(QStringLiteral("allPairsButton"));
        allPairsButton->setChecked(true);

        verticalLayout->addWidget(allPairsButton);

        showStructuresRadioButton = new QRadioButton(widget);
        buttonGroup->addButton(showStructuresRadioButton);
        showStructuresRadioButton->setObjectName(QStringLiteral("showStructuresRadioButton"));

        verticalLayout->addWidget(showStructuresRadioButton);

        showSolutionsRadioButton = new QRadioButton(widget);
        buttonGroup->addButton(showSolutionsRadioButton);
        showSolutionsRadioButton->setObjectName(QStringLiteral("showSolutionsRadioButton"));

        verticalLayout->addWidget(showSolutionsRadioButton);

        pairSubsetButton = new QRadioButton(widget);
        buttonGroup->addButton(pairSubsetButton);
        pairSubsetButton->setObjectName(QStringLiteral("pairSubsetButton"));

        verticalLayout->addWidget(pairSubsetButton);

        buttonBox = new QDialogButtonBox(DisplayDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(300, 20, 112, 77));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        displaySettingsBox = new QGroupBox(DisplayDialog);
        displaySettingsBox->setObjectName(QStringLiteral("displaySettingsBox"));
        displaySettingsBox->setEnabled(true);
        displaySettingsBox->setGeometry(QRect(10, 160, 401, 171));
        displaySettingsBox->setMinimumSize(QSize(301, 0));
        displaySettingsBox->setMaximumSize(QSize(16777215, 9898798));
        widget1 = new QWidget(displaySettingsBox);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(10, 30, 381, 131));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        showHoldCheckBox = new QCheckBox(widget1);
        showHoldCheckBox->setObjectName(QStringLiteral("showHoldCheckBox"));
        showHoldCheckBox->setChecked(true);

        horizontalLayout->addWidget(showHoldCheckBox);

        horizontalSpacer = new QSpacerItem(298, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        showIncompatibleCheckBox = new QCheckBox(widget1);
        showIncompatibleCheckBox->setObjectName(QStringLiteral("showIncompatibleCheckBox"));
        showIncompatibleCheckBox->setChecked(true);

        horizontalLayout_2->addWidget(showIncompatibleCheckBox);

        horizontalSpacer_2 = new QSpacerItem(218, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        maxPRACheckBox = new QCheckBox(widget1);
        maxPRACheckBox->setObjectName(QStringLiteral("maxPRACheckBox"));

        gridLayout->addWidget(maxPRACheckBox, 1, 0, 1, 1);

        horizontalSlider_2 = new QSlider(widget1);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setEnabled(false);
        horizontalSlider_2->setMaximum(100);
        horizontalSlider_2->setValue(100);
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_2, 1, 2, 1, 1);

        maxPRASpinBox = new QSpinBox(widget1);
        maxPRASpinBox->setObjectName(QStringLiteral("maxPRASpinBox"));
        maxPRASpinBox->setEnabled(false);
        maxPRASpinBox->setMaximum(100);
        maxPRASpinBox->setValue(100);

        gridLayout->addWidget(maxPRASpinBox, 1, 1, 1, 1);

        horizontalSlider = new QSlider(widget1);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setEnabled(false);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 0, 2, 1, 1);

        minPRASpinBox = new QSpinBox(widget1);
        minPRASpinBox->setObjectName(QStringLiteral("minPRASpinBox"));
        minPRASpinBox->setEnabled(false);
        minPRASpinBox->setMaximum(100);

        gridLayout->addWidget(minPRASpinBox, 0, 1, 1, 1);

        minPRACheckBox = new QCheckBox(widget1);
        minPRACheckBox->setObjectName(QStringLiteral("minPRACheckBox"));

        gridLayout->addWidget(minPRACheckBox, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


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
        showHoldCheckBox->setText(QApplication::translate("DisplayDialog", "Show Pairs on Hold", 0));
        showIncompatibleCheckBox->setText(QApplication::translate("DisplayDialog", "Show Pairs with No Compatibilities", 0));
        maxPRACheckBox->setText(QApplication::translate("DisplayDialog", "Maximum PRA to Display", 0));
        minPRACheckBox->setText(QApplication::translate("DisplayDialog", "Minimum PRA to Display", 0));
    } // retranslateUi

};

namespace Ui {
    class DisplayDialog: public Ui_DisplayDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYDIALOG_H
