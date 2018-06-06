/********************************************************************************
** Form generated from reading UI file 'DialogSimParameters.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
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
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QComboBox *optComboBox;
    QLabel *optLabel;
    QLabel *componentSizeLabel;
    QHBoxLayout *cycleSizeLayout;
    QSpinBox *cycleSizeSpinBox;
    QSlider *cycleSizeSlider;
    QHBoxLayout *chainLengthLayout;
    QSpinBox *chainLengthSpinBox;
    QSlider *chainLengthSlider;
    QHBoxLayout *lrsSizeLayout;
    QSpinBox *lrsSizeSpinBox;
    QSlider *lrsSizeSlider;
    QLabel *chainLengthLabel;
    QLabel *cycleSizeLabel;
    QLabel *utilLabel;
    QComboBox *utilComboBox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *collectArrangementsCheckBox;
    QSpacerItem *horizontalSpacer;
    QLabel *collectArrangementsLabel;
    QSpinBox *collectArrangementsSpinBox;
    QTabWidget *additionalParametersTabWidget;
    QWidget *numericalParametersTab;
    QWidget *layoutWidget1;
    QVBoxLayout *numericalParametersLayout;
    QCheckBox *praCheckBox;
    QHBoxLayout *praLayout;
    QSpinBox *praCutoffSpinBox;
    QLabel *praCutoffLabel;
    QDoubleSpinBox *praAdvantageSpinBox;
    QLabel *praAdvantageLabel;
    QSpacerItem *spacer1;
    QHBoxLayout *solutionsLayout;
    QLabel *solutionsLabel;
    QSpinBox *solutionsSpinBox;
    QSlider *solutionsSlider;
    QSpacerItem *spacer2;
    QCheckBox *estimateEUCheckBox;
    QHBoxLayout *estimateEULayout;
    QSpinBox *numberOfEUSimSpinBox;
    QLabel *numberOfEUSimLabel;
    QWidget *additionalOptionsTab;
    QWidget *layoutWidget2;
    QVBoxLayout *additionalOptionsLayout;
    QCheckBox *reserveOtoOBox;
    QCheckBox *checkAdditionalHLABox;
    QCheckBox *compatibleBox;
    QCheckBox *excludeABDonorsBox;
    QCheckBox *allowABBridgeBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogSimParameters)
    {
        if (DialogSimParameters->objectName().isEmpty())
            DialogSimParameters->setObjectName(QStringLiteral("DialogSimParameters"));
        DialogSimParameters->resize(388, 471);
        DialogSimParameters->setMinimumSize(QSize(388, 471));
        DialogSimParameters->setMaximumSize(QSize(388, 471));
        layoutWidget = new QWidget(DialogSimParameters);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 373, 457));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        optComboBox = new QComboBox(layoutWidget);
        optComboBox->setObjectName(QStringLiteral("optComboBox"));

        gridLayout->addWidget(optComboBox, 0, 2, 1, 1);

        optLabel = new QLabel(layoutWidget);
        optLabel->setObjectName(QStringLiteral("optLabel"));

        gridLayout->addWidget(optLabel, 0, 0, 1, 1);

        componentSizeLabel = new QLabel(layoutWidget);
        componentSizeLabel->setObjectName(QStringLiteral("componentSizeLabel"));

        gridLayout->addWidget(componentSizeLabel, 4, 0, 1, 2);

        cycleSizeLayout = new QHBoxLayout();
        cycleSizeLayout->setObjectName(QStringLiteral("cycleSizeLayout"));
        cycleSizeSpinBox = new QSpinBox(layoutWidget);
        cycleSizeSpinBox->setObjectName(QStringLiteral("cycleSizeSpinBox"));
        cycleSizeSpinBox->setMinimum(2);
        cycleSizeSpinBox->setMaximum(6);

        cycleSizeLayout->addWidget(cycleSizeSpinBox);

        cycleSizeSlider = new QSlider(layoutWidget);
        cycleSizeSlider->setObjectName(QStringLiteral("cycleSizeSlider"));
        cycleSizeSlider->setMinimum(2);
        cycleSizeSlider->setMaximum(6);
        cycleSizeSlider->setPageStep(2);
        cycleSizeSlider->setOrientation(Qt::Horizontal);
        cycleSizeSlider->setTickPosition(QSlider::TicksBelow);
        cycleSizeSlider->setTickInterval(1);

        cycleSizeLayout->addWidget(cycleSizeSlider);


        gridLayout->addLayout(cycleSizeLayout, 2, 2, 1, 1);

        chainLengthLayout = new QHBoxLayout();
        chainLengthLayout->setObjectName(QStringLiteral("chainLengthLayout"));
        chainLengthSpinBox = new QSpinBox(layoutWidget);
        chainLengthSpinBox->setObjectName(QStringLiteral("chainLengthSpinBox"));
        chainLengthSpinBox->setMinimum(2);
        chainLengthSpinBox->setMaximum(6);

        chainLengthLayout->addWidget(chainLengthSpinBox);

        chainLengthSlider = new QSlider(layoutWidget);
        chainLengthSlider->setObjectName(QStringLiteral("chainLengthSlider"));
        chainLengthSlider->setMinimum(2);
        chainLengthSlider->setMaximum(6);
        chainLengthSlider->setPageStep(2);
        chainLengthSlider->setOrientation(Qt::Horizontal);
        chainLengthSlider->setTickPosition(QSlider::TicksBelow);
        chainLengthSlider->setTickInterval(1);

        chainLengthLayout->addWidget(chainLengthSlider);


        gridLayout->addLayout(chainLengthLayout, 3, 2, 1, 1);

        lrsSizeLayout = new QHBoxLayout();
        lrsSizeLayout->setObjectName(QStringLiteral("lrsSizeLayout"));
        lrsSizeSpinBox = new QSpinBox(layoutWidget);
        lrsSizeSpinBox->setObjectName(QStringLiteral("lrsSizeSpinBox"));
        lrsSizeSpinBox->setEnabled(false);
        lrsSizeSpinBox->setMinimum(2);
        lrsSizeSpinBox->setMaximum(6);

        lrsSizeLayout->addWidget(lrsSizeSpinBox);

        lrsSizeSlider = new QSlider(layoutWidget);
        lrsSizeSlider->setObjectName(QStringLiteral("lrsSizeSlider"));
        lrsSizeSlider->setEnabled(false);
        lrsSizeSlider->setMinimum(2);
        lrsSizeSlider->setMaximum(6);
        lrsSizeSlider->setPageStep(2);
        lrsSizeSlider->setOrientation(Qt::Horizontal);
        lrsSizeSlider->setTickPosition(QSlider::TicksBelow);
        lrsSizeSlider->setTickInterval(1);

        lrsSizeLayout->addWidget(lrsSizeSlider);


        gridLayout->addLayout(lrsSizeLayout, 4, 2, 1, 1);

        chainLengthLabel = new QLabel(layoutWidget);
        chainLengthLabel->setObjectName(QStringLiteral("chainLengthLabel"));

        gridLayout->addWidget(chainLengthLabel, 3, 0, 1, 1);

        cycleSizeLabel = new QLabel(layoutWidget);
        cycleSizeLabel->setObjectName(QStringLiteral("cycleSizeLabel"));

        gridLayout->addWidget(cycleSizeLabel, 2, 0, 1, 1);

        utilLabel = new QLabel(layoutWidget);
        utilLabel->setObjectName(QStringLiteral("utilLabel"));

        gridLayout->addWidget(utilLabel, 1, 0, 1, 1);

        utilComboBox = new QComboBox(layoutWidget);
        utilComboBox->setObjectName(QStringLiteral("utilComboBox"));

        gridLayout->addWidget(utilComboBox, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        collectArrangementsCheckBox = new QCheckBox(layoutWidget);
        collectArrangementsCheckBox->setObjectName(QStringLiteral("collectArrangementsCheckBox"));
        collectArrangementsCheckBox->setChecked(true);

        horizontalLayout->addWidget(collectArrangementsCheckBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        collectArrangementsLabel = new QLabel(layoutWidget);
        collectArrangementsLabel->setObjectName(QStringLiteral("collectArrangementsLabel"));

        horizontalLayout->addWidget(collectArrangementsLabel);

        collectArrangementsSpinBox = new QSpinBox(layoutWidget);
        collectArrangementsSpinBox->setObjectName(QStringLiteral("collectArrangementsSpinBox"));
        collectArrangementsSpinBox->setMinimum(1);
        collectArrangementsSpinBox->setMaximum(1000);
        collectArrangementsSpinBox->setSingleStep(25);
        collectArrangementsSpinBox->setValue(200);

        horizontalLayout->addWidget(collectArrangementsSpinBox);


        verticalLayout->addLayout(horizontalLayout);

        additionalParametersTabWidget = new QTabWidget(layoutWidget);
        additionalParametersTabWidget->setObjectName(QStringLiteral("additionalParametersTabWidget"));
        additionalParametersTabWidget->setMinimumSize(QSize(371, 221));
        additionalParametersTabWidget->setMaximumSize(QSize(371, 221));
        additionalParametersTabWidget->setUsesScrollButtons(false);
        numericalParametersTab = new QWidget();
        numericalParametersTab->setObjectName(QStringLiteral("numericalParametersTab"));
        layoutWidget1 = new QWidget(numericalParametersTab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 341, 171));
        numericalParametersLayout = new QVBoxLayout(layoutWidget1);
        numericalParametersLayout->setObjectName(QStringLiteral("numericalParametersLayout"));
        numericalParametersLayout->setContentsMargins(0, 0, 0, 0);
        praCheckBox = new QCheckBox(layoutWidget1);
        praCheckBox->setObjectName(QStringLiteral("praCheckBox"));

        numericalParametersLayout->addWidget(praCheckBox);

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


        numericalParametersLayout->addLayout(praLayout);

        spacer1 = new QSpacerItem(18, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        numericalParametersLayout->addItem(spacer1);

        solutionsLayout = new QHBoxLayout();
        solutionsLayout->setObjectName(QStringLiteral("solutionsLayout"));
        solutionsLabel = new QLabel(layoutWidget1);
        solutionsLabel->setObjectName(QStringLiteral("solutionsLabel"));

        solutionsLayout->addWidget(solutionsLabel);

        solutionsSpinBox = new QSpinBox(layoutWidget1);
        solutionsSpinBox->setObjectName(QStringLiteral("solutionsSpinBox"));
        solutionsSpinBox->setMinimum(1);
        solutionsSpinBox->setMaximum(25);
        solutionsSpinBox->setValue(1);

        solutionsLayout->addWidget(solutionsSpinBox);

        solutionsSlider = new QSlider(layoutWidget1);
        solutionsSlider->setObjectName(QStringLiteral("solutionsSlider"));
        solutionsSlider->setMinimum(1);
        solutionsSlider->setMaximum(25);
        solutionsSlider->setPageStep(2);
        solutionsSlider->setValue(1);
        solutionsSlider->setOrientation(Qt::Horizontal);

        solutionsLayout->addWidget(solutionsSlider);


        numericalParametersLayout->addLayout(solutionsLayout);

        spacer2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        numericalParametersLayout->addItem(spacer2);

        estimateEUCheckBox = new QCheckBox(layoutWidget1);
        estimateEUCheckBox->setObjectName(QStringLiteral("estimateEUCheckBox"));
        estimateEUCheckBox->setEnabled(false);

        numericalParametersLayout->addWidget(estimateEUCheckBox);

        estimateEULayout = new QHBoxLayout();
        estimateEULayout->setObjectName(QStringLiteral("estimateEULayout"));
        numberOfEUSimSpinBox = new QSpinBox(layoutWidget1);
        numberOfEUSimSpinBox->setObjectName(QStringLiteral("numberOfEUSimSpinBox"));
        numberOfEUSimSpinBox->setEnabled(false);
        numberOfEUSimSpinBox->setMinimum(100);
        numberOfEUSimSpinBox->setMaximum(100000);

        estimateEULayout->addWidget(numberOfEUSimSpinBox);

        numberOfEUSimLabel = new QLabel(layoutWidget1);
        numberOfEUSimLabel->setObjectName(QStringLiteral("numberOfEUSimLabel"));

        estimateEULayout->addWidget(numberOfEUSimLabel);


        numericalParametersLayout->addLayout(estimateEULayout);

        additionalParametersTabWidget->addTab(numericalParametersTab, QString());
        additionalOptionsTab = new QWidget();
        additionalOptionsTab->setObjectName(QStringLiteral("additionalOptionsTab"));
        layoutWidget2 = new QWidget(additionalOptionsTab);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 10, 311, 130));
        additionalOptionsLayout = new QVBoxLayout(layoutWidget2);
        additionalOptionsLayout->setObjectName(QStringLiteral("additionalOptionsLayout"));
        additionalOptionsLayout->setContentsMargins(0, 0, 0, 0);
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

        verticalLayout->addWidget(additionalParametersTabWidget);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        optLabel->setBuddy(optComboBox);
        componentSizeLabel->setBuddy(cycleSizeSpinBox);
        chainLengthLabel->setBuddy(cycleSizeSpinBox);
        cycleSizeLabel->setBuddy(cycleSizeSpinBox);
        utilLabel->setBuddy(utilComboBox);
        solutionsLabel->setBuddy(solutionsSpinBox);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(cycleSizeSpinBox, cycleSizeSlider);
        QWidget::setTabOrder(cycleSizeSlider, utilComboBox);
        QWidget::setTabOrder(utilComboBox, optComboBox);
        QWidget::setTabOrder(optComboBox, praCheckBox);
        QWidget::setTabOrder(praCheckBox, reserveOtoOBox);
        QWidget::setTabOrder(reserveOtoOBox, checkAdditionalHLABox);
        QWidget::setTabOrder(checkAdditionalHLABox, compatibleBox);
        QWidget::setTabOrder(compatibleBox, allowABBridgeBox);

        retranslateUi(DialogSimParameters);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSimParameters, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSimParameters, SLOT(reject()));
        QObject::connect(cycleSizeSpinBox, SIGNAL(valueChanged(int)), cycleSizeSlider, SLOT(setValue(int)));
        QObject::connect(cycleSizeSlider, SIGNAL(sliderMoved(int)), cycleSizeSpinBox, SLOT(setValue(int)));
        QObject::connect(solutionsSpinBox, SIGNAL(valueChanged(int)), solutionsSlider, SLOT(setValue(int)));
        QObject::connect(solutionsSlider, SIGNAL(sliderMoved(int)), solutionsSpinBox, SLOT(setValue(int)));
        QObject::connect(excludeABDonorsBox, SIGNAL(toggled(bool)), DialogSimParameters, SLOT(enableBridgeDonorOptions(bool)));
        QObject::connect(praCheckBox, SIGNAL(toggled(bool)), DialogSimParameters, SLOT(enablePRAOptions(bool)));
        QObject::connect(chainLengthSpinBox, SIGNAL(valueChanged(int)), chainLengthSlider, SLOT(setValue(int)));
        QObject::connect(chainLengthSlider, SIGNAL(sliderMoved(int)), chainLengthSpinBox, SLOT(setValue(int)));
        QObject::connect(lrsSizeSpinBox, SIGNAL(valueChanged(int)), lrsSizeSlider, SLOT(setValue(int)));
        QObject::connect(lrsSizeSlider, SIGNAL(valueChanged(int)), lrsSizeSpinBox, SLOT(setValue(int)));
        QObject::connect(optComboBox, SIGNAL(currentIndexChanged(int)), DialogSimParameters, SLOT(enableOptimizationOptions(int)));
        QObject::connect(estimateEUCheckBox, SIGNAL(toggled(bool)), DialogSimParameters, SLOT(enableEstimateEUOptions(bool)));
        QObject::connect(collectArrangementsCheckBox, SIGNAL(toggled(bool)), collectArrangementsSpinBox, SLOT(setEnabled(bool)));

        optComboBox->setCurrentIndex(2);
        additionalParametersTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogSimParameters);
    } // setupUi

    void retranslateUi(QDialog *DialogSimParameters)
    {
        DialogSimParameters->setWindowTitle(QApplication::translate("DialogSimParameters", "Set Parameters", 0));
        optComboBox->clear();
        optComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSimParameters", "Cycles and Chains", 0)
         << QApplication::translate("DialogSimParameters", "Cycles and Chains With Fallbacks", 0)
         << QApplication::translate("DialogSimParameters", "Locally Relevant Subgraphs", 0)
        );
        optLabel->setText(QApplication::translate("DialogSimParameters", "Optimization Scheme", 0));
        componentSizeLabel->setText(QApplication::translate("DialogSimParameters", "Maximum Subgraph Size", 0));
        chainLengthLabel->setText(QApplication::translate("DialogSimParameters", "Maximum Chain Length", 0));
        cycleSizeLabel->setText(QApplication::translate("DialogSimParameters", "Maximum Cycle Size", 0));
        utilLabel->setText(QApplication::translate("DialogSimParameters", "Utility Scheme", 0));
        utilComboBox->clear();
        utilComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSimParameters", "Transplants", 0)
         << QApplication::translate("DialogSimParameters", "5 Year Survival", 0)
         << QApplication::translate("DialogSimParameters", "10 Year Survival", 0)
         << QApplication::translate("DialogSimParameters", "Difficult-to-Transplant", 0)
         << QApplication::translate("DialogSimParameters", "Assigned Score", 0)
        );
        collectArrangementsCheckBox->setText(QApplication::translate("DialogSimParameters", "Collect Found Exchanges", 0));
        collectArrangementsLabel->setText(QApplication::translate("DialogSimParameters", "Cutoff", 0));
        praCheckBox->setText(QApplication::translate("DialogSimParameters", "Add Advantage to High PRA Candidates", 0));
        praCutoffLabel->setText(QApplication::translate("DialogSimParameters", "Cutoff", 0));
        praAdvantageLabel->setText(QApplication::translate("DialogSimParameters", "Value", 0));
        solutionsLabel->setText(QApplication::translate("DialogSimParameters", "Number of Solutions", 0));
        estimateEUCheckBox->setText(QApplication::translate("DialogSimParameters", "Estimate Expected Utility", 0));
        numberOfEUSimLabel->setText(QApplication::translate("DialogSimParameters", "Number of Expected Utility Simulations", 0));
        additionalParametersTabWidget->setTabText(additionalParametersTabWidget->indexOf(numericalParametersTab), QApplication::translate("DialogSimParameters", "Numerical Parameters", 0));
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
