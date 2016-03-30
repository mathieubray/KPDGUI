/********************************************************************************
** Form generated from reading UI file 'SimParamDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPARAMDIALOG_H
#define UI_SIMPARAMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimParamDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *optLabel;
    QComboBox *optComboBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *utilLabel;
    QComboBox *utilComboBox;
    QHBoxLayout *horizontalLayout;
    QLabel *chainLengthLabel;
    QSpinBox *chainLengthSpinBox;
    QSlider *chainLengthSlider;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *pairFailureRateLabel;
    QDoubleSpinBox *pairFailureRateSpinBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *adFailureRateLabel;
    QDoubleSpinBox *adFailureRateSpinBox;
    QHBoxLayout *horizontalLayout_9;
    QLabel *exogenousFailureRateLabel;
    QDoubleSpinBox *exogenousFailureRateSpinBox;
    QSpacerItem *verticalSpacer;
    QCheckBox *praBox;
    QHBoxLayout *horizontalLayout_10;
    QSpinBox *praCutoffSpinBox;
    QLabel *praCutoffLabel;
    QDoubleSpinBox *praAdvantageSpinBox;
    QLabel *praAdvantageLabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *solutionsSpinBox;
    QLabel *solutionsLabel;
    QSlider *solutionsSlider;
    QWidget *tab_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_3;
    QComboBox *chainStorageComboBox;
    QCheckBox *reserveOtoOBox;
    QCheckBox *checkDPBox;
    QCheckBox *compatibleBox;
    QCheckBox *excludeABDonorsBox;
    QCheckBox *allowABBridgeBox;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SimParamDialog)
    {
        if (SimParamDialog->objectName().isEmpty())
            SimParamDialog->setObjectName(QStringLiteral("SimParamDialog"));
        SimParamDialog->resize(278, 386);
        SimParamDialog->setMinimumSize(QSize(0, 0));
        SimParamDialog->setMaximumSize(QSize(10000000, 10000000));
        layoutWidget = new QWidget(SimParamDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 261, 371));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        optLabel = new QLabel(layoutWidget);
        optLabel->setObjectName(QStringLiteral("optLabel"));

        horizontalLayout_3->addWidget(optLabel);

        optComboBox = new QComboBox(layoutWidget);
        optComboBox->setObjectName(QStringLiteral("optComboBox"));

        horizontalLayout_3->addWidget(optComboBox);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        utilLabel = new QLabel(layoutWidget);
        utilLabel->setObjectName(QStringLiteral("utilLabel"));

        horizontalLayout_2->addWidget(utilLabel);

        utilComboBox = new QComboBox(layoutWidget);
        utilComboBox->setObjectName(QStringLiteral("utilComboBox"));

        horizontalLayout_2->addWidget(utilComboBox);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        chainLengthLabel = new QLabel(layoutWidget);
        chainLengthLabel->setObjectName(QStringLiteral("chainLengthLabel"));

        horizontalLayout->addWidget(chainLengthLabel);

        chainLengthSpinBox = new QSpinBox(layoutWidget);
        chainLengthSpinBox->setObjectName(QStringLiteral("chainLengthSpinBox"));
        chainLengthSpinBox->setMinimum(2);
        chainLengthSpinBox->setMaximum(6);

        horizontalLayout->addWidget(chainLengthSpinBox);

        chainLengthSlider = new QSlider(layoutWidget);
        chainLengthSlider->setObjectName(QStringLiteral("chainLengthSlider"));
        chainLengthSlider->setMinimum(2);
        chainLengthSlider->setMaximum(6);
        chainLengthSlider->setPageStep(2);
        chainLengthSlider->setOrientation(Qt::Horizontal);
        chainLengthSlider->setTickPosition(QSlider::TicksBelow);
        chainLengthSlider->setTickInterval(1);

        horizontalLayout->addWidget(chainLengthSlider);


        verticalLayout_3->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(layoutWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        layoutWidget1 = new QWidget(tab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 233, 207));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        pairFailureRateLabel = new QLabel(layoutWidget1);
        pairFailureRateLabel->setObjectName(QStringLiteral("pairFailureRateLabel"));

        horizontalLayout_6->addWidget(pairFailureRateLabel);

        pairFailureRateSpinBox = new QDoubleSpinBox(layoutWidget1);
        pairFailureRateSpinBox->setObjectName(QStringLiteral("pairFailureRateSpinBox"));
        pairFailureRateSpinBox->setDecimals(2);
        pairFailureRateSpinBox->setMaximum(1);
        pairFailureRateSpinBox->setSingleStep(0.1);

        horizontalLayout_6->addWidget(pairFailureRateSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        adFailureRateLabel = new QLabel(layoutWidget1);
        adFailureRateLabel->setObjectName(QStringLiteral("adFailureRateLabel"));

        horizontalLayout_8->addWidget(adFailureRateLabel);

        adFailureRateSpinBox = new QDoubleSpinBox(layoutWidget1);
        adFailureRateSpinBox->setObjectName(QStringLiteral("adFailureRateSpinBox"));
        adFailureRateSpinBox->setDecimals(2);
        adFailureRateSpinBox->setMaximum(1);
        adFailureRateSpinBox->setSingleStep(0.1);

        horizontalLayout_8->addWidget(adFailureRateSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        exogenousFailureRateLabel = new QLabel(layoutWidget1);
        exogenousFailureRateLabel->setObjectName(QStringLiteral("exogenousFailureRateLabel"));

        horizontalLayout_9->addWidget(exogenousFailureRateLabel);

        exogenousFailureRateSpinBox = new QDoubleSpinBox(layoutWidget1);
        exogenousFailureRateSpinBox->setObjectName(QStringLiteral("exogenousFailureRateSpinBox"));
        exogenousFailureRateSpinBox->setDecimals(2);
        exogenousFailureRateSpinBox->setMaximum(1);
        exogenousFailureRateSpinBox->setSingleStep(0.1);

        horizontalLayout_9->addWidget(exogenousFailureRateSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_9);

        verticalSpacer = new QSpacerItem(18, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        praBox = new QCheckBox(layoutWidget1);
        praBox->setObjectName(QStringLiteral("praBox"));

        verticalLayout_2->addWidget(praBox);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        praCutoffSpinBox = new QSpinBox(layoutWidget1);
        praCutoffSpinBox->setObjectName(QStringLiteral("praCutoffSpinBox"));
        praCutoffSpinBox->setEnabled(false);
        praCutoffSpinBox->setMaximum(100);
        praCutoffSpinBox->setSingleStep(10);

        horizontalLayout_10->addWidget(praCutoffSpinBox);

        praCutoffLabel = new QLabel(layoutWidget1);
        praCutoffLabel->setObjectName(QStringLiteral("praCutoffLabel"));

        horizontalLayout_10->addWidget(praCutoffLabel);

        praAdvantageSpinBox = new QDoubleSpinBox(layoutWidget1);
        praAdvantageSpinBox->setObjectName(QStringLiteral("praAdvantageSpinBox"));
        praAdvantageSpinBox->setEnabled(false);
        praAdvantageSpinBox->setMaximum(10);

        horizontalLayout_10->addWidget(praAdvantageSpinBox);

        praAdvantageLabel = new QLabel(layoutWidget1);
        praAdvantageLabel->setObjectName(QStringLiteral("praAdvantageLabel"));

        horizontalLayout_10->addWidget(praAdvantageLabel);


        verticalLayout_2->addLayout(horizontalLayout_10);

        verticalSpacer_2 = new QSpacerItem(18, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        solutionsSpinBox = new QSpinBox(layoutWidget1);
        solutionsSpinBox->setObjectName(QStringLiteral("solutionsSpinBox"));
        solutionsSpinBox->setMinimum(1);
        solutionsSpinBox->setMaximum(25);
        solutionsSpinBox->setValue(1);

        horizontalLayout_5->addWidget(solutionsSpinBox);

        solutionsLabel = new QLabel(layoutWidget1);
        solutionsLabel->setObjectName(QStringLiteral("solutionsLabel"));

        horizontalLayout_5->addWidget(solutionsLabel);

        solutionsSlider = new QSlider(layoutWidget1);
        solutionsSlider->setObjectName(QStringLiteral("solutionsSlider"));
        solutionsSlider->setMinimum(1);
        solutionsSlider->setMaximum(25);
        solutionsSlider->setPageStep(2);
        solutionsSlider->setValue(1);
        solutionsSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(solutionsSlider);


        verticalLayout_2->addLayout(horizontalLayout_5);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        layoutWidget2 = new QWidget(tab_2);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 11, 219, 139));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_11->addWidget(label_3);

        chainStorageComboBox = new QComboBox(layoutWidget2);
        chainStorageComboBox->setObjectName(QStringLiteral("chainStorageComboBox"));

        horizontalLayout_11->addWidget(chainStorageComboBox);


        verticalLayout->addLayout(horizontalLayout_11);

        reserveOtoOBox = new QCheckBox(layoutWidget2);
        reserveOtoOBox->setObjectName(QStringLiteral("reserveOtoOBox"));

        verticalLayout->addWidget(reserveOtoOBox);

        checkDPBox = new QCheckBox(layoutWidget2);
        checkDPBox->setObjectName(QStringLiteral("checkDPBox"));

        verticalLayout->addWidget(checkDPBox);

        compatibleBox = new QCheckBox(layoutWidget2);
        compatibleBox->setObjectName(QStringLiteral("compatibleBox"));

        verticalLayout->addWidget(compatibleBox);

        excludeABDonorsBox = new QCheckBox(layoutWidget2);
        excludeABDonorsBox->setObjectName(QStringLiteral("excludeABDonorsBox"));

        verticalLayout->addWidget(excludeABDonorsBox);

        allowABBridgeBox = new QCheckBox(layoutWidget2);
        allowABBridgeBox->setObjectName(QStringLiteral("allowABBridgeBox"));

        verticalLayout->addWidget(allowABBridgeBox);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_3->addWidget(tabWidget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_4->addWidget(buttonBox);


        verticalLayout_3->addLayout(horizontalLayout_4);

#ifndef QT_NO_SHORTCUT
        optLabel->setBuddy(optComboBox);
        utilLabel->setBuddy(utilComboBox);
        chainLengthLabel->setBuddy(chainLengthSpinBox);
        pairFailureRateLabel->setBuddy(chainLengthSpinBox);
        adFailureRateLabel->setBuddy(chainLengthSpinBox);
        exogenousFailureRateLabel->setBuddy(chainLengthSpinBox);
        solutionsLabel->setBuddy(solutionsSpinBox);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(chainLengthSpinBox, chainLengthSlider);
        QWidget::setTabOrder(chainLengthSlider, utilComboBox);
        QWidget::setTabOrder(utilComboBox, optComboBox);
        QWidget::setTabOrder(optComboBox, praBox);
        QWidget::setTabOrder(praBox, reserveOtoOBox);
        QWidget::setTabOrder(reserveOtoOBox, checkDPBox);
        QWidget::setTabOrder(checkDPBox, compatibleBox);
        QWidget::setTabOrder(compatibleBox, allowABBridgeBox);

        retranslateUi(SimParamDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SimParamDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SimParamDialog, SLOT(reject()));
        QObject::connect(chainLengthSpinBox, SIGNAL(valueChanged(int)), chainLengthSlider, SLOT(setValue(int)));
        QObject::connect(chainLengthSlider, SIGNAL(sliderMoved(int)), chainLengthSpinBox, SLOT(setValue(int)));
        QObject::connect(solutionsSpinBox, SIGNAL(valueChanged(int)), solutionsSlider, SLOT(setValue(int)));
        QObject::connect(solutionsSlider, SIGNAL(sliderMoved(int)), solutionsSpinBox, SLOT(setValue(int)));
        QObject::connect(excludeABDonorsBox, SIGNAL(toggled(bool)), SimParamDialog, SLOT(enableBridgeDonorOptions(bool)));
        QObject::connect(praBox, SIGNAL(toggled(bool)), SimParamDialog, SLOT(enablePRAOptions(bool)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SimParamDialog);
    } // setupUi

    void retranslateUi(QDialog *SimParamDialog)
    {
        SimParamDialog->setWindowTitle(QApplication::translate("SimParamDialog", "Set Parameters", 0));
        optLabel->setText(QApplication::translate("SimParamDialog", "Optimization Scheme", 0));
        optComboBox->clear();
        optComboBox->insertItems(0, QStringList()
         << QApplication::translate("SimParamDialog", "Utility", 0)
         << QApplication::translate("SimParamDialog", "Expected Utility", 0)
         << QApplication::translate("SimParamDialog", "Fallbacks", 0)
         << QApplication::translate("SimParamDialog", "Extended Fallbacks", 0)
        );
        utilLabel->setText(QApplication::translate("SimParamDialog", "Utility Scheme", 0));
        utilComboBox->clear();
        utilComboBox->insertItems(0, QStringList()
         << QApplication::translate("SimParamDialog", "Transplants", 0)
         << QApplication::translate("SimParamDialog", "5 Year Survival", 0)
         << QApplication::translate("SimParamDialog", "10 Year Survival", 0)
         << QApplication::translate("SimParamDialog", "Score", 0)
        );
        chainLengthLabel->setText(QApplication::translate("SimParamDialog", "Maximum Chain Length", 0));
        pairFailureRateLabel->setText(QApplication::translate("SimParamDialog", "Pair Failure Rate", 0));
        adFailureRateLabel->setText(QApplication::translate("SimParamDialog", "AD Failure Rate", 0));
        exogenousFailureRateLabel->setText(QApplication::translate("SimParamDialog", "Exogenous Match Failure Rate", 0));
        praBox->setText(QApplication::translate("SimParamDialog", "Add Advantage to High PRA Recipients", 0));
        praCutoffLabel->setText(QApplication::translate("SimParamDialog", "Cutoff", 0));
        praAdvantageLabel->setText(QApplication::translate("SimParamDialog", "Value", 0));
        solutionsLabel->setText(QApplication::translate("SimParamDialog", "Number of Solutions", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SimParamDialog", "Numerical Parameters", 0));
        label_3->setText(QApplication::translate("SimParamDialog", "Chains Are Stored:", 0));
        chainStorageComboBox->clear();
        chainStorageComboBox->insertItems(0, QStringList()
         << QApplication::translate("SimParamDialog", "As They Are Found", 0)
         << QApplication::translate("SimParamDialog", "First", 0)
         << QApplication::translate("SimParamDialog", "Last", 0)
        );
        reserveOtoOBox->setText(QApplication::translate("SimParamDialog", "Reserve O Donors for O Recipients", 0));
        checkDPBox->setText(QApplication::translate("SimParamDialog", "Check Additional HLA Information", 0));
        compatibleBox->setText(QApplication::translate("SimParamDialog", "Include Compatible Pairs in Match Run", 0));
        excludeABDonorsBox->setText(QApplication::translate("SimParamDialog", "Exclude AB Donors from Simulation", 0));
        allowABBridgeBox->setText(QApplication::translate("SimParamDialog", "Allow AB Bridge Donors", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SimParamDialog", "Additional Options", 0));
    } // retranslateUi

};

namespace Ui {
    class SimParamDialog: public Ui_SimParamDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPARAMDIALOG_H
