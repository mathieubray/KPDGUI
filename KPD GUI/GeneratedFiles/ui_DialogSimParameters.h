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
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *optLabel;
    QLabel *utilLabel;
    QHBoxLayout *chainLengthLayout;
    QSpinBox *chainLengthSpinBox;
    QSlider *chainLengthSlider;
    QHBoxLayout *componentSizeLayout;
    QSpinBox *componentSizeSpinBox;
    QSlider *componentSizeSlider;
    QLabel *componentSizeLabel;
    QComboBox *optComboBox;
    QLabel *chainLengthLabel;
    QComboBox *utilComboBox;
    QLabel *cycleSizeLabel;
    QHBoxLayout *cycleSizeLayout;
    QSpinBox *cycleSizeSpinBox;
    QSlider *cycleSizeSlider;
    QDialogButtonBox *buttonBox;
    QTabWidget *additionalParametersTabWidget;
    QWidget *numericalParametersTab;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QCheckBox *praCheckBox;
    QHBoxLayout *praLayout;
    QSpinBox *praCutoffSpinBox;
    QLabel *praCutoffLabel;
    QDoubleSpinBox *praAdvantageSpinBox;
    QLabel *praAdvantageLabel;
    QSpacerItem *verticalSpacer2;
    QHBoxLayout *solutionsLayout;
    QLabel *solutionsLabel;
    QSpinBox *solutionsSpinBox;
    QSlider *solutionsSlider;
    QSpacerItem *verticalSpacer3;
    QCheckBox *estimateEUCheckBox;
    QHBoxLayout *estimateEULayout;
    QSpinBox *numberOfEUSimSpinBox;
    QLabel *numberOfEUSimLabel;
    QWidget *additionalOptionsTab;
    QWidget *layoutWidget;
    QVBoxLayout *additionalOptionsLayout;
    QHBoxLayout *chainStorageLayout;
    QLabel *chainStorageLabel;
    QComboBox *chainStorageComboBox;
    QCheckBox *reserveOtoOBox;
    QCheckBox *checkAdditionalHLABox;
    QCheckBox *compatibleBox;
    QCheckBox *excludeABDonorsBox;
    QCheckBox *allowABBridgeBox;

    void setupUi(QDialog *DialogSimParameters)
    {
        if (DialogSimParameters->objectName().isEmpty())
            DialogSimParameters->setObjectName(QStringLiteral("DialogSimParameters"));
        DialogSimParameters->resize(318, 468);
        DialogSimParameters->setMinimumSize(QSize(0, 0));
        DialogSimParameters->setMaximumSize(QSize(10000000, 16777215));
        widget = new QWidget(DialogSimParameters);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 299, 161));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        optLabel = new QLabel(widget);
        optLabel->setObjectName(QStringLiteral("optLabel"));

        gridLayout->addWidget(optLabel, 0, 0, 1, 1);

        utilLabel = new QLabel(widget);
        utilLabel->setObjectName(QStringLiteral("utilLabel"));

        gridLayout->addWidget(utilLabel, 1, 0, 1, 1);

        chainLengthLayout = new QHBoxLayout();
        chainLengthLayout->setObjectName(QStringLiteral("chainLengthLayout"));
        chainLengthSpinBox = new QSpinBox(widget);
        chainLengthSpinBox->setObjectName(QStringLiteral("chainLengthSpinBox"));
        chainLengthSpinBox->setMinimum(2);
        chainLengthSpinBox->setMaximum(6);

        chainLengthLayout->addWidget(chainLengthSpinBox);

        chainLengthSlider = new QSlider(widget);
        chainLengthSlider->setObjectName(QStringLiteral("chainLengthSlider"));
        chainLengthSlider->setMinimum(2);
        chainLengthSlider->setMaximum(6);
        chainLengthSlider->setPageStep(2);
        chainLengthSlider->setOrientation(Qt::Horizontal);
        chainLengthSlider->setTickPosition(QSlider::TicksBelow);
        chainLengthSlider->setTickInterval(1);

        chainLengthLayout->addWidget(chainLengthSlider);


        gridLayout->addLayout(chainLengthLayout, 3, 2, 1, 1);

        componentSizeLayout = new QHBoxLayout();
        componentSizeLayout->setObjectName(QStringLiteral("componentSizeLayout"));
        componentSizeSpinBox = new QSpinBox(widget);
        componentSizeSpinBox->setObjectName(QStringLiteral("componentSizeSpinBox"));
        componentSizeSpinBox->setEnabled(false);
        componentSizeSpinBox->setMinimum(2);
        componentSizeSpinBox->setMaximum(6);

        componentSizeLayout->addWidget(componentSizeSpinBox);

        componentSizeSlider = new QSlider(widget);
        componentSizeSlider->setObjectName(QStringLiteral("componentSizeSlider"));
        componentSizeSlider->setEnabled(false);
        componentSizeSlider->setMinimum(2);
        componentSizeSlider->setMaximum(6);
        componentSizeSlider->setPageStep(2);
        componentSizeSlider->setOrientation(Qt::Horizontal);
        componentSizeSlider->setTickPosition(QSlider::TicksBelow);
        componentSizeSlider->setTickInterval(1);

        componentSizeLayout->addWidget(componentSizeSlider);


        gridLayout->addLayout(componentSizeLayout, 4, 2, 1, 1);

        componentSizeLabel = new QLabel(widget);
        componentSizeLabel->setObjectName(QStringLiteral("componentSizeLabel"));

        gridLayout->addWidget(componentSizeLabel, 4, 0, 1, 2);

        optComboBox = new QComboBox(widget);
        optComboBox->setObjectName(QStringLiteral("optComboBox"));

        gridLayout->addWidget(optComboBox, 0, 2, 1, 1);

        chainLengthLabel = new QLabel(widget);
        chainLengthLabel->setObjectName(QStringLiteral("chainLengthLabel"));

        gridLayout->addWidget(chainLengthLabel, 3, 0, 1, 1);

        utilComboBox = new QComboBox(widget);
        utilComboBox->setObjectName(QStringLiteral("utilComboBox"));

        gridLayout->addWidget(utilComboBox, 1, 2, 1, 1);

        cycleSizeLabel = new QLabel(widget);
        cycleSizeLabel->setObjectName(QStringLiteral("cycleSizeLabel"));

        gridLayout->addWidget(cycleSizeLabel, 2, 0, 1, 1);

        cycleSizeLayout = new QHBoxLayout();
        cycleSizeLayout->setObjectName(QStringLiteral("cycleSizeLayout"));
        cycleSizeSpinBox = new QSpinBox(widget);
        cycleSizeSpinBox->setObjectName(QStringLiteral("cycleSizeSpinBox"));
        cycleSizeSpinBox->setMinimum(2);
        cycleSizeSpinBox->setMaximum(6);

        cycleSizeLayout->addWidget(cycleSizeSpinBox);

        cycleSizeSlider = new QSlider(widget);
        cycleSizeSlider->setObjectName(QStringLiteral("cycleSizeSlider"));
        cycleSizeSlider->setMinimum(2);
        cycleSizeSlider->setMaximum(6);
        cycleSizeSlider->setPageStep(2);
        cycleSizeSlider->setOrientation(Qt::Horizontal);
        cycleSizeSlider->setTickPosition(QSlider::TicksBelow);
        cycleSizeSlider->setTickInterval(1);

        cycleSizeLayout->addWidget(cycleSizeSlider);


        gridLayout->addLayout(cycleSizeLayout, 2, 2, 1, 1);

        buttonBox = new QDialogButtonBox(DialogSimParameters);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(110, 430, 193, 28));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        additionalParametersTabWidget = new QTabWidget(DialogSimParameters);
        additionalParametersTabWidget->setObjectName(QStringLiteral("additionalParametersTabWidget"));
        additionalParametersTabWidget->setGeometry(QRect(10, 180, 301, 241));
        additionalParametersTabWidget->setUsesScrollButtons(false);
        numericalParametersTab = new QWidget();
        numericalParametersTab->setObjectName(QStringLiteral("numericalParametersTab"));
        widget1 = new QWidget(numericalParametersTab);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(10, 10, 261, 194));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        praCheckBox = new QCheckBox(widget1);
        praCheckBox->setObjectName(QStringLiteral("praCheckBox"));

        verticalLayout->addWidget(praCheckBox);

        praLayout = new QHBoxLayout();
        praLayout->setObjectName(QStringLiteral("praLayout"));
        praCutoffSpinBox = new QSpinBox(widget1);
        praCutoffSpinBox->setObjectName(QStringLiteral("praCutoffSpinBox"));
        praCutoffSpinBox->setEnabled(false);
        praCutoffSpinBox->setMaximum(100);
        praCutoffSpinBox->setSingleStep(10);

        praLayout->addWidget(praCutoffSpinBox);

        praCutoffLabel = new QLabel(widget1);
        praCutoffLabel->setObjectName(QStringLiteral("praCutoffLabel"));

        praLayout->addWidget(praCutoffLabel);

        praAdvantageSpinBox = new QDoubleSpinBox(widget1);
        praAdvantageSpinBox->setObjectName(QStringLiteral("praAdvantageSpinBox"));
        praAdvantageSpinBox->setEnabled(false);
        praAdvantageSpinBox->setMaximum(10);

        praLayout->addWidget(praAdvantageSpinBox);

        praAdvantageLabel = new QLabel(widget1);
        praAdvantageLabel->setObjectName(QStringLiteral("praAdvantageLabel"));

        praLayout->addWidget(praAdvantageLabel);


        verticalLayout->addLayout(praLayout);

        verticalSpacer2 = new QSpacerItem(18, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer2);

        solutionsLayout = new QHBoxLayout();
        solutionsLayout->setObjectName(QStringLiteral("solutionsLayout"));
        solutionsLabel = new QLabel(widget1);
        solutionsLabel->setObjectName(QStringLiteral("solutionsLabel"));

        solutionsLayout->addWidget(solutionsLabel);

        solutionsSpinBox = new QSpinBox(widget1);
        solutionsSpinBox->setObjectName(QStringLiteral("solutionsSpinBox"));
        solutionsSpinBox->setMinimum(1);
        solutionsSpinBox->setMaximum(25);
        solutionsSpinBox->setValue(1);

        solutionsLayout->addWidget(solutionsSpinBox);

        solutionsSlider = new QSlider(widget1);
        solutionsSlider->setObjectName(QStringLiteral("solutionsSlider"));
        solutionsSlider->setMinimum(1);
        solutionsSlider->setMaximum(25);
        solutionsSlider->setPageStep(2);
        solutionsSlider->setValue(1);
        solutionsSlider->setOrientation(Qt::Horizontal);

        solutionsLayout->addWidget(solutionsSlider);


        verticalLayout->addLayout(solutionsLayout);

        verticalSpacer3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer3);

        estimateEUCheckBox = new QCheckBox(widget1);
        estimateEUCheckBox->setObjectName(QStringLiteral("estimateEUCheckBox"));
        estimateEUCheckBox->setEnabled(false);

        verticalLayout->addWidget(estimateEUCheckBox);

        estimateEULayout = new QHBoxLayout();
        estimateEULayout->setObjectName(QStringLiteral("estimateEULayout"));
        numberOfEUSimSpinBox = new QSpinBox(widget1);
        numberOfEUSimSpinBox->setObjectName(QStringLiteral("numberOfEUSimSpinBox"));
        numberOfEUSimSpinBox->setEnabled(false);
        numberOfEUSimSpinBox->setMinimum(100);
        numberOfEUSimSpinBox->setMaximum(100000);

        estimateEULayout->addWidget(numberOfEUSimSpinBox);

        numberOfEUSimLabel = new QLabel(widget1);
        numberOfEUSimLabel->setObjectName(QStringLiteral("numberOfEUSimLabel"));

        estimateEULayout->addWidget(numberOfEUSimLabel);


        verticalLayout->addLayout(estimateEULayout);

        additionalParametersTabWidget->addTab(numericalParametersTab, QString());
        additionalOptionsTab = new QWidget();
        additionalOptionsTab->setObjectName(QStringLiteral("additionalOptionsTab"));
        layoutWidget = new QWidget(additionalOptionsTab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 259, 161));
        additionalOptionsLayout = new QVBoxLayout(layoutWidget);
        additionalOptionsLayout->setObjectName(QStringLiteral("additionalOptionsLayout"));
        additionalOptionsLayout->setContentsMargins(0, 0, 0, 0);
        chainStorageLayout = new QHBoxLayout();
        chainStorageLayout->setObjectName(QStringLiteral("chainStorageLayout"));
        chainStorageLabel = new QLabel(layoutWidget);
        chainStorageLabel->setObjectName(QStringLiteral("chainStorageLabel"));

        chainStorageLayout->addWidget(chainStorageLabel);

        chainStorageComboBox = new QComboBox(layoutWidget);
        chainStorageComboBox->setObjectName(QStringLiteral("chainStorageComboBox"));

        chainStorageLayout->addWidget(chainStorageComboBox);


        additionalOptionsLayout->addLayout(chainStorageLayout);

        reserveOtoOBox = new QCheckBox(layoutWidget);
        reserveOtoOBox->setObjectName(QStringLiteral("reserveOtoOBox"));

        additionalOptionsLayout->addWidget(reserveOtoOBox);

        checkAdditionalHLABox = new QCheckBox(layoutWidget);
        checkAdditionalHLABox->setObjectName(QStringLiteral("checkAdditionalHLABox"));

        additionalOptionsLayout->addWidget(checkAdditionalHLABox);

        compatibleBox = new QCheckBox(layoutWidget);
        compatibleBox->setObjectName(QStringLiteral("compatibleBox"));

        additionalOptionsLayout->addWidget(compatibleBox);

        excludeABDonorsBox = new QCheckBox(layoutWidget);
        excludeABDonorsBox->setObjectName(QStringLiteral("excludeABDonorsBox"));

        additionalOptionsLayout->addWidget(excludeABDonorsBox);

        allowABBridgeBox = new QCheckBox(layoutWidget);
        allowABBridgeBox->setObjectName(QStringLiteral("allowABBridgeBox"));

        additionalOptionsLayout->addWidget(allowABBridgeBox);

        additionalParametersTabWidget->addTab(additionalOptionsTab, QString());
#ifndef QT_NO_SHORTCUT
        optLabel->setBuddy(optComboBox);
        utilLabel->setBuddy(utilComboBox);
        componentSizeLabel->setBuddy(cycleSizeSpinBox);
        chainLengthLabel->setBuddy(cycleSizeSpinBox);
        cycleSizeLabel->setBuddy(cycleSizeSpinBox);
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
        QObject::connect(componentSizeSpinBox, SIGNAL(valueChanged(int)), componentSizeSlider, SLOT(setValue(int)));
        QObject::connect(componentSizeSlider, SIGNAL(valueChanged(int)), componentSizeSpinBox, SLOT(setValue(int)));
        QObject::connect(optComboBox, SIGNAL(currentIndexChanged(int)), DialogSimParameters, SLOT(enableComponentOptions(int)));

        additionalParametersTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogSimParameters);
    } // setupUi

    void retranslateUi(QDialog *DialogSimParameters)
    {
        DialogSimParameters->setWindowTitle(QApplication::translate("DialogSimParameters", "Set Parameters", 0));
        optLabel->setText(QApplication::translate("DialogSimParameters", "Optimization Scheme", 0));
        utilLabel->setText(QApplication::translate("DialogSimParameters", "Utility Scheme", 0));
        componentSizeLabel->setText(QApplication::translate("DialogSimParameters", "Maximum Component Size", 0));
        optComboBox->clear();
        optComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSimParameters", "Utility", 0)
         << QApplication::translate("DialogSimParameters", "Expected Utility", 0)
         << QApplication::translate("DialogSimParameters", "Fallbacks", 0)
         << QApplication::translate("DialogSimParameters", "Extended Fallbacks", 0)
        );
        chainLengthLabel->setText(QApplication::translate("DialogSimParameters", "Maximum Chain Length", 0));
        utilComboBox->clear();
        utilComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSimParameters", "Transplants", 0)
         << QApplication::translate("DialogSimParameters", "5 Year Survival", 0)
         << QApplication::translate("DialogSimParameters", "10 Year Survival", 0)
         << QApplication::translate("DialogSimParameters", "Score", 0)
        );
        cycleSizeLabel->setText(QApplication::translate("DialogSimParameters", "Maximum Cycle Size", 0));
        praCheckBox->setText(QApplication::translate("DialogSimParameters", "Add Advantage to High PRA Candidates", 0));
        praCutoffLabel->setText(QApplication::translate("DialogSimParameters", "Cutoff", 0));
        praAdvantageLabel->setText(QApplication::translate("DialogSimParameters", "Value", 0));
        solutionsLabel->setText(QApplication::translate("DialogSimParameters", "Number of Solutions", 0));
        estimateEUCheckBox->setText(QApplication::translate("DialogSimParameters", "Estimate Expected Utility", 0));
        numberOfEUSimLabel->setText(QApplication::translate("DialogSimParameters", "Number of Expected Utility Simulations", 0));
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
