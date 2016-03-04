/********************************************************************************
** Form generated from reading UI file 'DialogSimParameters.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSIMPARAMETERS_H
#define UI_DIALOGSIMPARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
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

class Ui_DialogSimParameters
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *simParametersLayout;
    QGridLayout *parametersGridLayout;
    QLabel *optLabel;
    QComboBox *optComboBox;
    QLabel *utilLabel;
    QComboBox *utilComboBox;
    QLabel *sizeLabel;
    QSpinBox *sizeSpinBox;
    QSlider *sizeSlider;
    QTabWidget *additionalParametersTabWidget;
    QWidget *numericalParametersTab;
    QWidget *layoutWidget1;
    QGridLayout *numericalParametersLayout;
    QHBoxLayout *pairFailureLayout;
    QLabel *pairFailureRateLabel;
    QDoubleSpinBox *pairFailureRateSpinBox;
    QHBoxLayout *adFailureLayout;
    QLabel *adFailureRateLabel;
    QDoubleSpinBox *adFailureRateSpinBox;
    QHBoxLayout *exogenousFailureLayout;
    QLabel *exogenousFailureRateLabel;
    QDoubleSpinBox *exogenousFailureRateSpinBox;
    QSpacerItem *verticalSpacer1;
    QCheckBox *praBox;
    QHBoxLayout *praLayout;
    QSpinBox *praCutoffSpinBox;
    QLabel *praCutoffLabel;
    QDoubleSpinBox *praAdvantageSpinBox;
    QLabel *praAdvantageLabel;
    QSpacerItem *verticalSpacer2;
    QHBoxLayout *solutionsLayout;
    QSpinBox *solutionsSpinBox;
    QLabel *solutionsLabel;
    QSlider *solutionsSlider;
    QHBoxLayout *euSimLayout;
    QSpinBox *euSimSpinBox;
    QLabel *euSimLabel;
    QWidget *additionalOptionsTab;
    QWidget *layoutWidget2;
    QVBoxLayout *additionalOptionsLayout;
    QHBoxLayout *chainStorageLayout;
    QLabel *chainStorageLabel;
    QComboBox *chainStorageComboBox;
    QCheckBox *reserveOtoOBox;
    QCheckBox *checkAdditionalHLABox;
    QCheckBox *compatibleBox;
    QCheckBox *excludeABDonorsBox;
    QCheckBox *allowABBridgeBox;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonHorizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogSimParameters)
    {
        if (DialogSimParameters->objectName().isEmpty())
            DialogSimParameters->setObjectName(QStringLiteral("DialogSimParameters"));
        DialogSimParameters->resize(299, 455);
        DialogSimParameters->setMinimumSize(QSize(0, 0));
        DialogSimParameters->setMaximumSize(QSize(10000000, 10000000));
        layoutWidget = new QWidget(DialogSimParameters);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 281, 431));
        simParametersLayout = new QVBoxLayout(layoutWidget);
        simParametersLayout->setObjectName(QStringLiteral("simParametersLayout"));
        simParametersLayout->setContentsMargins(0, 0, 0, 0);
        parametersGridLayout = new QGridLayout();
        parametersGridLayout->setObjectName(QStringLiteral("parametersGridLayout"));
        optLabel = new QLabel(layoutWidget);
        optLabel->setObjectName(QStringLiteral("optLabel"));

        parametersGridLayout->addWidget(optLabel, 0, 0, 1, 2);

        optComboBox = new QComboBox(layoutWidget);
        optComboBox->setObjectName(QStringLiteral("optComboBox"));

        parametersGridLayout->addWidget(optComboBox, 0, 2, 1, 3);

        utilLabel = new QLabel(layoutWidget);
        utilLabel->setObjectName(QStringLiteral("utilLabel"));

        parametersGridLayout->addWidget(utilLabel, 1, 0, 1, 1);

        utilComboBox = new QComboBox(layoutWidget);
        utilComboBox->setObjectName(QStringLiteral("utilComboBox"));

        parametersGridLayout->addWidget(utilComboBox, 1, 1, 1, 4);

        sizeLabel = new QLabel(layoutWidget);
        sizeLabel->setObjectName(QStringLiteral("sizeLabel"));

        parametersGridLayout->addWidget(sizeLabel, 2, 0, 1, 3);

        sizeSpinBox = new QSpinBox(layoutWidget);
        sizeSpinBox->setObjectName(QStringLiteral("sizeSpinBox"));
        sizeSpinBox->setMinimum(2);
        sizeSpinBox->setMaximum(6);

        parametersGridLayout->addWidget(sizeSpinBox, 2, 3, 1, 1);

        sizeSlider = new QSlider(layoutWidget);
        sizeSlider->setObjectName(QStringLiteral("sizeSlider"));
        sizeSlider->setMinimum(2);
        sizeSlider->setMaximum(6);
        sizeSlider->setPageStep(2);
        sizeSlider->setOrientation(Qt::Horizontal);
        sizeSlider->setTickPosition(QSlider::TicksBelow);
        sizeSlider->setTickInterval(1);

        parametersGridLayout->addWidget(sizeSlider, 2, 4, 1, 1);


        simParametersLayout->addLayout(parametersGridLayout);

        additionalParametersTabWidget = new QTabWidget(layoutWidget);
        additionalParametersTabWidget->setObjectName(QStringLiteral("additionalParametersTabWidget"));
        numericalParametersTab = new QWidget();
        numericalParametersTab->setObjectName(QStringLiteral("numericalParametersTab"));
        layoutWidget1 = new QWidget(numericalParametersTab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 11, 261, 235));
        numericalParametersLayout = new QGridLayout(layoutWidget1);
        numericalParametersLayout->setObjectName(QStringLiteral("numericalParametersLayout"));
        numericalParametersLayout->setContentsMargins(0, 0, 0, 0);
        pairFailureLayout = new QHBoxLayout();
        pairFailureLayout->setObjectName(QStringLiteral("pairFailureLayout"));
        pairFailureRateLabel = new QLabel(layoutWidget1);
        pairFailureRateLabel->setObjectName(QStringLiteral("pairFailureRateLabel"));

        pairFailureLayout->addWidget(pairFailureRateLabel);

        pairFailureRateSpinBox = new QDoubleSpinBox(layoutWidget1);
        pairFailureRateSpinBox->setObjectName(QStringLiteral("pairFailureRateSpinBox"));
        pairFailureRateSpinBox->setDecimals(2);
        pairFailureRateSpinBox->setMaximum(1);
        pairFailureRateSpinBox->setSingleStep(0.1);

        pairFailureLayout->addWidget(pairFailureRateSpinBox);


        numericalParametersLayout->addLayout(pairFailureLayout, 0, 0, 1, 1);

        adFailureLayout = new QHBoxLayout();
        adFailureLayout->setObjectName(QStringLiteral("adFailureLayout"));
        adFailureRateLabel = new QLabel(layoutWidget1);
        adFailureRateLabel->setObjectName(QStringLiteral("adFailureRateLabel"));

        adFailureLayout->addWidget(adFailureRateLabel);

        adFailureRateSpinBox = new QDoubleSpinBox(layoutWidget1);
        adFailureRateSpinBox->setObjectName(QStringLiteral("adFailureRateSpinBox"));
        adFailureRateSpinBox->setDecimals(2);
        adFailureRateSpinBox->setMaximum(1);
        adFailureRateSpinBox->setSingleStep(0.1);

        adFailureLayout->addWidget(adFailureRateSpinBox);


        numericalParametersLayout->addLayout(adFailureLayout, 1, 0, 1, 1);

        exogenousFailureLayout = new QHBoxLayout();
        exogenousFailureLayout->setObjectName(QStringLiteral("exogenousFailureLayout"));
        exogenousFailureRateLabel = new QLabel(layoutWidget1);
        exogenousFailureRateLabel->setObjectName(QStringLiteral("exogenousFailureRateLabel"));

        exogenousFailureLayout->addWidget(exogenousFailureRateLabel);

        exogenousFailureRateSpinBox = new QDoubleSpinBox(layoutWidget1);
        exogenousFailureRateSpinBox->setObjectName(QStringLiteral("exogenousFailureRateSpinBox"));
        exogenousFailureRateSpinBox->setDecimals(2);
        exogenousFailureRateSpinBox->setMaximum(1);
        exogenousFailureRateSpinBox->setSingleStep(0.1);

        exogenousFailureLayout->addWidget(exogenousFailureRateSpinBox);


        numericalParametersLayout->addLayout(exogenousFailureLayout, 2, 0, 1, 1);

        verticalSpacer1 = new QSpacerItem(18, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        numericalParametersLayout->addItem(verticalSpacer1, 3, 0, 1, 1);

        praBox = new QCheckBox(layoutWidget1);
        praBox->setObjectName(QStringLiteral("praBox"));

        numericalParametersLayout->addWidget(praBox, 4, 0, 1, 1);

        praLayout = new QHBoxLayout();
        praLayout->setObjectName(QStringLiteral("praLayout"));
        praCutoffSpinBox = new QSpinBox(layoutWidget1);
        praCutoffSpinBox->setObjectName(QStringLiteral("praCutoffSpinBox"));
        praCutoffSpinBox->setEnabled(false);
        praCutoffSpinBox->setMaximum(100);
        praCutoffSpinBox->setSingleStep(10);

        praLayout->addWidget(praCutoffSpinBox);

        praCutoffLabel = new QLabel(layoutWidget1);
        praCutoffLabel->setObjectName(QStringLiteral("praCutoffLabel"));

        praLayout->addWidget(praCutoffLabel);

        praAdvantageSpinBox = new QDoubleSpinBox(layoutWidget1);
        praAdvantageSpinBox->setObjectName(QStringLiteral("praAdvantageSpinBox"));
        praAdvantageSpinBox->setEnabled(false);
        praAdvantageSpinBox->setMaximum(10);

        praLayout->addWidget(praAdvantageSpinBox);

        praAdvantageLabel = new QLabel(layoutWidget1);
        praAdvantageLabel->setObjectName(QStringLiteral("praAdvantageLabel"));

        praLayout->addWidget(praAdvantageLabel);


        numericalParametersLayout->addLayout(praLayout, 5, 0, 1, 1);

        verticalSpacer2 = new QSpacerItem(18, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        numericalParametersLayout->addItem(verticalSpacer2, 6, 0, 1, 1);

        solutionsLayout = new QHBoxLayout();
        solutionsLayout->setObjectName(QStringLiteral("solutionsLayout"));
        solutionsSpinBox = new QSpinBox(layoutWidget1);
        solutionsSpinBox->setObjectName(QStringLiteral("solutionsSpinBox"));
        solutionsSpinBox->setMinimum(1);
        solutionsSpinBox->setMaximum(25);
        solutionsSpinBox->setValue(1);

        solutionsLayout->addWidget(solutionsSpinBox);

        solutionsLabel = new QLabel(layoutWidget1);
        solutionsLabel->setObjectName(QStringLiteral("solutionsLabel"));

        solutionsLayout->addWidget(solutionsLabel);

        solutionsSlider = new QSlider(layoutWidget1);
        solutionsSlider->setObjectName(QStringLiteral("solutionsSlider"));
        solutionsSlider->setMinimum(1);
        solutionsSlider->setMaximum(25);
        solutionsSlider->setPageStep(2);
        solutionsSlider->setValue(1);
        solutionsSlider->setOrientation(Qt::Horizontal);

        solutionsLayout->addWidget(solutionsSlider);


        numericalParametersLayout->addLayout(solutionsLayout, 7, 0, 1, 1);

        euSimLayout = new QHBoxLayout();
        euSimLayout->setObjectName(QStringLiteral("euSimLayout"));
        euSimSpinBox = new QSpinBox(layoutWidget1);
        euSimSpinBox->setObjectName(QStringLiteral("euSimSpinBox"));
        euSimSpinBox->setEnabled(false);
        euSimSpinBox->setMinimum(100);
        euSimSpinBox->setMaximum(100000);

        euSimLayout->addWidget(euSimSpinBox);

        euSimLabel = new QLabel(layoutWidget1);
        euSimLabel->setObjectName(QStringLiteral("euSimLabel"));

        euSimLayout->addWidget(euSimLabel);


        numericalParametersLayout->addLayout(euSimLayout, 8, 0, 1, 1);

        additionalParametersTabWidget->addTab(numericalParametersTab, QString());
        additionalOptionsTab = new QWidget();
        additionalOptionsTab->setObjectName(QStringLiteral("additionalOptionsTab"));
        layoutWidget2 = new QWidget(additionalOptionsTab);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 11, 219, 139));
        additionalOptionsLayout = new QVBoxLayout(layoutWidget2);
        additionalOptionsLayout->setObjectName(QStringLiteral("additionalOptionsLayout"));
        additionalOptionsLayout->setContentsMargins(0, 0, 0, 0);
        chainStorageLayout = new QHBoxLayout();
        chainStorageLayout->setObjectName(QStringLiteral("chainStorageLayout"));
        chainStorageLabel = new QLabel(layoutWidget2);
        chainStorageLabel->setObjectName(QStringLiteral("chainStorageLabel"));

        chainStorageLayout->addWidget(chainStorageLabel);

        chainStorageComboBox = new QComboBox(layoutWidget2);
        chainStorageComboBox->setObjectName(QStringLiteral("chainStorageComboBox"));

        chainStorageLayout->addWidget(chainStorageComboBox);


        additionalOptionsLayout->addLayout(chainStorageLayout);

        reserveOtoOBox = new QCheckBox(layoutWidget2);
        reserveOtoOBox->setObjectName(QStringLiteral("reserveOtoOBox"));

        additionalOptionsLayout->addWidget(reserveOtoOBox);

        checkAdditionalHLABox = new QCheckBox(layoutWidget2);
        checkAdditionalHLABox->setObjectName(QStringLiteral("checkAdditionalHLABox"));

        additionalOptionsLayout->addWidget(checkAdditionalHLABox);

        compatibleBox = new QCheckBox(layoutWidget2);
        compatibleBox->setObjectName(QStringLiteral("compatibleBox"));

        additionalOptionsLayout->addWidget(compatibleBox);

        excludeABDonorsBox = new QCheckBox(layoutWidget2);
        excludeABDonorsBox->setObjectName(QStringLiteral("excludeABDonorsBox"));

        additionalOptionsLayout->addWidget(excludeABDonorsBox);

        allowABBridgeBox = new QCheckBox(layoutWidget2);
        allowABBridgeBox->setObjectName(QStringLiteral("allowABBridgeBox"));

        additionalOptionsLayout->addWidget(allowABBridgeBox);

        additionalParametersTabWidget->addTab(additionalOptionsTab, QString());

        simParametersLayout->addWidget(additionalParametersTabWidget);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
        buttonHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonHorizontalSpacer);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        buttonLayout->addWidget(buttonBox);


        simParametersLayout->addLayout(buttonLayout);

#ifndef QT_NO_SHORTCUT
        optLabel->setBuddy(optComboBox);
        utilLabel->setBuddy(utilComboBox);
        sizeLabel->setBuddy(sizeSpinBox);
        pairFailureRateLabel->setBuddy(sizeSpinBox);
        adFailureRateLabel->setBuddy(sizeSpinBox);
        exogenousFailureRateLabel->setBuddy(sizeSpinBox);
        solutionsLabel->setBuddy(solutionsSpinBox);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(sizeSpinBox, sizeSlider);
        QWidget::setTabOrder(sizeSlider, utilComboBox);
        QWidget::setTabOrder(utilComboBox, optComboBox);
        QWidget::setTabOrder(optComboBox, praBox);
        QWidget::setTabOrder(praBox, reserveOtoOBox);
        QWidget::setTabOrder(reserveOtoOBox, checkAdditionalHLABox);
        QWidget::setTabOrder(checkAdditionalHLABox, compatibleBox);
        QWidget::setTabOrder(compatibleBox, allowABBridgeBox);

        retranslateUi(DialogSimParameters);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSimParameters, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSimParameters, SLOT(reject()));
        QObject::connect(sizeSpinBox, SIGNAL(valueChanged(int)), sizeSlider, SLOT(setValue(int)));
        QObject::connect(sizeSlider, SIGNAL(sliderMoved(int)), sizeSpinBox, SLOT(setValue(int)));
        QObject::connect(solutionsSpinBox, SIGNAL(valueChanged(int)), solutionsSlider, SLOT(setValue(int)));
        QObject::connect(solutionsSlider, SIGNAL(sliderMoved(int)), solutionsSpinBox, SLOT(setValue(int)));
        QObject::connect(excludeABDonorsBox, SIGNAL(toggled(bool)), DialogSimParameters, SLOT(enableBridgeDonorOptions(bool)));
        QObject::connect(praBox, SIGNAL(toggled(bool)), DialogSimParameters, SLOT(enablePRAOptions(bool)));
        QObject::connect(optComboBox, SIGNAL(currentIndexChanged(int)), DialogSimParameters, SLOT(changeLabel(int)));

        additionalParametersTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogSimParameters);
    } // setupUi

    void retranslateUi(QDialog *DialogSimParameters)
    {
        DialogSimParameters->setWindowTitle(QApplication::translate("DialogSimParameters", "Set Parameters", 0));
        optLabel->setText(QApplication::translate("DialogSimParameters", "Optimization Scheme", 0));
        optComboBox->clear();
        optComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSimParameters", "Utility", 0)
         << QApplication::translate("DialogSimParameters", "Expected Utility", 0)
         << QApplication::translate("DialogSimParameters", "Fallbacks", 0)
         << QApplication::translate("DialogSimParameters", "Extended Fallbacks", 0)
        );
        utilLabel->setText(QApplication::translate("DialogSimParameters", "Utility Scheme", 0));
        utilComboBox->clear();
        utilComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSimParameters", "Transplants", 0)
         << QApplication::translate("DialogSimParameters", "5 Year Survival", 0)
         << QApplication::translate("DialogSimParameters", "10 Year Survival", 0)
         << QApplication::translate("DialogSimParameters", "Score", 0)
        );
        sizeLabel->setText(QApplication::translate("DialogSimParameters", "Maximum Chain Length", 0));
        pairFailureRateLabel->setText(QApplication::translate("DialogSimParameters", "Pair Failure Rate", 0));
        adFailureRateLabel->setText(QApplication::translate("DialogSimParameters", "AD Failure Rate", 0));
        exogenousFailureRateLabel->setText(QApplication::translate("DialogSimParameters", "Exogenous Match Failure Rate", 0));
        praBox->setText(QApplication::translate("DialogSimParameters", "Add Advantage to High PRA Recipients", 0));
        praCutoffLabel->setText(QApplication::translate("DialogSimParameters", "Cutoff", 0));
        praAdvantageLabel->setText(QApplication::translate("DialogSimParameters", "Value", 0));
        solutionsLabel->setText(QApplication::translate("DialogSimParameters", "Number of Solutions", 0));
        euSimLabel->setText(QApplication::translate("DialogSimParameters", "Number of Expected Utility Simulations", 0));
        additionalParametersTabWidget->setTabText(additionalParametersTabWidget->indexOf(numericalParametersTab), QApplication::translate("DialogSimParameters", "Numerical Parameters", 0));
        chainStorageLabel->setText(QApplication::translate("DialogSimParameters", "Chains Are Stored:", 0));
        chainStorageComboBox->clear();
        chainStorageComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSimParameters", "As They Are Found", 0)
         << QApplication::translate("DialogSimParameters", "First", 0)
         << QApplication::translate("DialogSimParameters", "Last", 0)
        );
        reserveOtoOBox->setText(QApplication::translate("DialogSimParameters", "Reserve O Donors for O Recipients", 0));
        checkAdditionalHLABox->setText(QApplication::translate("DialogSimParameters", "Check Additional HLA Information", 0));
        compatibleBox->setText(QApplication::translate("DialogSimParameters", "Include Compatible Pairs in Match Run", 0));
        excludeABDonorsBox->setText(QApplication::translate("DialogSimParameters", "Exclude AB Donors from Simulation", 0));
        allowABBridgeBox->setText(QApplication::translate("DialogSimParameters", "Allow AB Bridge Donors", 0));
        additionalParametersTabWidget->setTabText(additionalParametersTabWidget->indexOf(additionalOptionsTab), QApplication::translate("DialogSimParameters", "Additional Options", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogSimParameters: public Ui_DialogSimParameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSIMPARAMETERS_H
