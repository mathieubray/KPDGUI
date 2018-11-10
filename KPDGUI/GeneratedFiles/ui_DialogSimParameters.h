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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogSimParameters
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *saveSolutionCheckBox;
    QLabel *label;
    QLineEdit *folderLineEdit;
    QToolButton *browseButton;
    QHBoxLayout *horizontalLayout;
    QCheckBox *collectArrangementsCheckBox;
    QSpacerItem *horizontalSpacer;
    QLabel *collectArrangementsLabel;
    QSpinBox *collectArrangementsSpinBox;
    QTabWidget *additionalParametersTabWidget;
    QWidget *tab;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *optLabel;
    QComboBox *optComboBox;
    QLabel *utilLabel;
    QComboBox *utilComboBox;
    QLabel *cycleSizeLabel;
    QHBoxLayout *cycleSizeLayout;
    QSpinBox *cycleSizeSpinBox;
    QSlider *cycleSizeSlider;
    QLabel *chainLengthLabel;
    QHBoxLayout *chainLengthLayout;
    QSpinBox *chainLengthSpinBox;
    QSlider *chainLengthSlider;
    QLabel *componentSizeLabel;
    QHBoxLayout *lrsSizeLayout;
    QSpinBox *lrsSizeSpinBox;
    QSlider *lrsSizeSlider;
    QLabel *solutionsLabel;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *solutionsSpinBox;
    QSlider *solutionsSlider;
    QWidget *additionalOptionsTab;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QCheckBox *praCheckBox;
    QGridLayout *gridLayout_3;
    QSpinBox *praCutoffSpinBox;
    QLabel *praCutoffLabel;
    QDoubleSpinBox *praAdvantageSpinBox;
    QLabel *praAdvantageLabel;
    QCheckBox *estimateEUCheckBox;
    QHBoxLayout *horizontalLayout_4;
    QSpinBox *numberOfEUSimSpinBox;
    QLabel *numberOfEUSimLabel;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *additionalOptionsLayout;
    QCheckBox *reserveOtoOBox;
    QCheckBox *checkAdditionalHLABox;
    QCheckBox *compatibleBox;
    QCheckBox *excludeABDonorsBox;
    QCheckBox *allowABBridgeBox;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *highlightTopSolutionCheckBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogSimParameters)
    {
        if (DialogSimParameters->objectName().isEmpty())
            DialogSimParameters->setObjectName(QStringLiteral("DialogSimParameters"));
        DialogSimParameters->resize(561, 366);
        DialogSimParameters->setMinimumSize(QSize(561, 366));
        DialogSimParameters->setMaximumSize(QSize(561, 366));
        gridLayout_2 = new QGridLayout(DialogSimParameters);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        saveSolutionCheckBox = new QCheckBox(DialogSimParameters);
        saveSolutionCheckBox->setObjectName(QStringLiteral("saveSolutionCheckBox"));
        saveSolutionCheckBox->setLayoutDirection(Qt::LeftToRight);
        saveSolutionCheckBox->setChecked(true);

        horizontalLayout_3->addWidget(saveSolutionCheckBox);

        label = new QLabel(DialogSimParameters);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        folderLineEdit = new QLineEdit(DialogSimParameters);
        folderLineEdit->setObjectName(QStringLiteral("folderLineEdit"));

        horizontalLayout_3->addWidget(folderLineEdit);

        browseButton = new QToolButton(DialogSimParameters);
        browseButton->setObjectName(QStringLiteral("browseButton"));

        horizontalLayout_3->addWidget(browseButton);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        collectArrangementsCheckBox = new QCheckBox(DialogSimParameters);
        collectArrangementsCheckBox->setObjectName(QStringLiteral("collectArrangementsCheckBox"));
        collectArrangementsCheckBox->setChecked(true);

        horizontalLayout->addWidget(collectArrangementsCheckBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        collectArrangementsLabel = new QLabel(DialogSimParameters);
        collectArrangementsLabel->setObjectName(QStringLiteral("collectArrangementsLabel"));
        collectArrangementsLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(collectArrangementsLabel);

        collectArrangementsSpinBox = new QSpinBox(DialogSimParameters);
        collectArrangementsSpinBox->setObjectName(QStringLiteral("collectArrangementsSpinBox"));
        collectArrangementsSpinBox->setMinimum(1);
        collectArrangementsSpinBox->setMaximum(1000);
        collectArrangementsSpinBox->setSingleStep(25);
        collectArrangementsSpinBox->setValue(200);

        horizontalLayout->addWidget(collectArrangementsSpinBox);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        additionalParametersTabWidget = new QTabWidget(DialogSimParameters);
        additionalParametersTabWidget->setObjectName(QStringLiteral("additionalParametersTabWidget"));
        additionalParametersTabWidget->setMinimumSize(QSize(371, 221));
        additionalParametersTabWidget->setMaximumSize(QSize(16777215, 16777215));
        additionalParametersTabWidget->setUsesScrollButtons(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 511, 197));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        optLabel = new QLabel(layoutWidget);
        optLabel->setObjectName(QStringLiteral("optLabel"));

        gridLayout->addWidget(optLabel, 0, 0, 1, 1);

        optComboBox = new QComboBox(layoutWidget);
        optComboBox->setObjectName(QStringLiteral("optComboBox"));

        gridLayout->addWidget(optComboBox, 0, 1, 1, 1);

        utilLabel = new QLabel(layoutWidget);
        utilLabel->setObjectName(QStringLiteral("utilLabel"));

        gridLayout->addWidget(utilLabel, 1, 0, 1, 1);

        utilComboBox = new QComboBox(layoutWidget);
        utilComboBox->setObjectName(QStringLiteral("utilComboBox"));

        gridLayout->addWidget(utilComboBox, 1, 1, 1, 1);

        cycleSizeLabel = new QLabel(layoutWidget);
        cycleSizeLabel->setObjectName(QStringLiteral("cycleSizeLabel"));

        gridLayout->addWidget(cycleSizeLabel, 2, 0, 1, 1);

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


        gridLayout->addLayout(cycleSizeLayout, 2, 1, 1, 1);

        chainLengthLabel = new QLabel(layoutWidget);
        chainLengthLabel->setObjectName(QStringLiteral("chainLengthLabel"));

        gridLayout->addWidget(chainLengthLabel, 3, 0, 1, 1);

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


        gridLayout->addLayout(chainLengthLayout, 3, 1, 1, 1);

        componentSizeLabel = new QLabel(layoutWidget);
        componentSizeLabel->setObjectName(QStringLiteral("componentSizeLabel"));

        gridLayout->addWidget(componentSizeLabel, 4, 0, 1, 1);

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


        gridLayout->addLayout(lrsSizeLayout, 4, 1, 1, 1);

        solutionsLabel = new QLabel(layoutWidget);
        solutionsLabel->setObjectName(QStringLiteral("solutionsLabel"));

        gridLayout->addWidget(solutionsLabel, 5, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        solutionsSpinBox = new QSpinBox(layoutWidget);
        solutionsSpinBox->setObjectName(QStringLiteral("solutionsSpinBox"));
        solutionsSpinBox->setMaximumSize(QSize(33, 16777215));
        solutionsSpinBox->setMinimum(1);
        solutionsSpinBox->setMaximum(25);
        solutionsSpinBox->setValue(1);

        horizontalLayout_2->addWidget(solutionsSpinBox);

        solutionsSlider = new QSlider(layoutWidget);
        solutionsSlider->setObjectName(QStringLiteral("solutionsSlider"));
        solutionsSlider->setMinimum(1);
        solutionsSlider->setMaximum(25);
        solutionsSlider->setPageStep(2);
        solutionsSlider->setValue(1);
        solutionsSlider->setOrientation(Qt::Horizontal);
        solutionsSlider->setTickPosition(QSlider::TicksBelow);

        horizontalLayout_2->addWidget(solutionsSlider);


        gridLayout->addLayout(horizontalLayout_2, 5, 1, 1, 1);

        additionalParametersTabWidget->addTab(tab, QString());
        additionalOptionsTab = new QWidget();
        additionalOptionsTab->setObjectName(QStringLiteral("additionalOptionsTab"));
        layoutWidget1 = new QWidget(additionalOptionsTab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 510, 191));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        praCheckBox = new QCheckBox(layoutWidget1);
        praCheckBox->setObjectName(QStringLiteral("praCheckBox"));

        verticalLayout->addWidget(praCheckBox);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        praCutoffSpinBox = new QSpinBox(layoutWidget1);
        praCutoffSpinBox->setObjectName(QStringLiteral("praCutoffSpinBox"));
        praCutoffSpinBox->setEnabled(false);
        praCutoffSpinBox->setMaximum(100);
        praCutoffSpinBox->setSingleStep(10);

        gridLayout_3->addWidget(praCutoffSpinBox, 0, 0, 1, 1);

        praCutoffLabel = new QLabel(layoutWidget1);
        praCutoffLabel->setObjectName(QStringLiteral("praCutoffLabel"));

        gridLayout_3->addWidget(praCutoffLabel, 0, 1, 1, 1);

        praAdvantageSpinBox = new QDoubleSpinBox(layoutWidget1);
        praAdvantageSpinBox->setObjectName(QStringLiteral("praAdvantageSpinBox"));
        praAdvantageSpinBox->setEnabled(false);
        praAdvantageSpinBox->setMaximum(10);

        gridLayout_3->addWidget(praAdvantageSpinBox, 1, 0, 1, 1);

        praAdvantageLabel = new QLabel(layoutWidget1);
        praAdvantageLabel->setObjectName(QStringLiteral("praAdvantageLabel"));

        gridLayout_3->addWidget(praAdvantageLabel, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        estimateEUCheckBox = new QCheckBox(layoutWidget1);
        estimateEUCheckBox->setObjectName(QStringLiteral("estimateEUCheckBox"));
        estimateEUCheckBox->setEnabled(false);

        verticalLayout->addWidget(estimateEUCheckBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        numberOfEUSimSpinBox = new QSpinBox(layoutWidget1);
        numberOfEUSimSpinBox->setObjectName(QStringLiteral("numberOfEUSimSpinBox"));
        numberOfEUSimSpinBox->setEnabled(false);
        numberOfEUSimSpinBox->setMinimum(100);
        numberOfEUSimSpinBox->setMaximum(100000);

        horizontalLayout_4->addWidget(numberOfEUSimSpinBox);

        numberOfEUSimLabel = new QLabel(layoutWidget1);
        numberOfEUSimLabel->setObjectName(QStringLiteral("numberOfEUSimLabel"));

        horizontalLayout_4->addWidget(numberOfEUSimLabel);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_5->addLayout(verticalLayout);

        additionalOptionsLayout = new QVBoxLayout();
        additionalOptionsLayout->setObjectName(QStringLiteral("additionalOptionsLayout"));
        reserveOtoOBox = new QCheckBox(layoutWidget1);
        reserveOtoOBox->setObjectName(QStringLiteral("reserveOtoOBox"));

        additionalOptionsLayout->addWidget(reserveOtoOBox);

        checkAdditionalHLABox = new QCheckBox(layoutWidget1);
        checkAdditionalHLABox->setObjectName(QStringLiteral("checkAdditionalHLABox"));

        additionalOptionsLayout->addWidget(checkAdditionalHLABox);

        compatibleBox = new QCheckBox(layoutWidget1);
        compatibleBox->setObjectName(QStringLiteral("compatibleBox"));

        additionalOptionsLayout->addWidget(compatibleBox);

        excludeABDonorsBox = new QCheckBox(layoutWidget1);
        excludeABDonorsBox->setObjectName(QStringLiteral("excludeABDonorsBox"));

        additionalOptionsLayout->addWidget(excludeABDonorsBox);

        allowABBridgeBox = new QCheckBox(layoutWidget1);
        allowABBridgeBox->setObjectName(QStringLiteral("allowABBridgeBox"));

        additionalOptionsLayout->addWidget(allowABBridgeBox);


        horizontalLayout_5->addLayout(additionalOptionsLayout);

        additionalParametersTabWidget->addTab(additionalOptionsTab, QString());

        gridLayout_2->addWidget(additionalParametersTabWidget, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        highlightTopSolutionCheckBox = new QCheckBox(DialogSimParameters);
        highlightTopSolutionCheckBox->setObjectName(QStringLiteral("highlightTopSolutionCheckBox"));
        highlightTopSolutionCheckBox->setChecked(true);

        horizontalLayout_6->addWidget(highlightTopSolutionCheckBox);

        buttonBox = new QDialogButtonBox(DialogSimParameters);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_6->addWidget(buttonBox);


        gridLayout_2->addLayout(horizontalLayout_6, 3, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        optLabel->setBuddy(optComboBox);
        utilLabel->setBuddy(utilComboBox);
        cycleSizeLabel->setBuddy(cycleSizeSpinBox);
        chainLengthLabel->setBuddy(cycleSizeSpinBox);
        componentSizeLabel->setBuddy(cycleSizeSpinBox);
        solutionsLabel->setBuddy(solutionsSpinBox);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(cycleSizeSpinBox, cycleSizeSlider);
        QWidget::setTabOrder(cycleSizeSlider, utilComboBox);
        QWidget::setTabOrder(utilComboBox, optComboBox);
        QWidget::setTabOrder(optComboBox, reserveOtoOBox);
        QWidget::setTabOrder(reserveOtoOBox, checkAdditionalHLABox);
        QWidget::setTabOrder(checkAdditionalHLABox, compatibleBox);
        QWidget::setTabOrder(compatibleBox, allowABBridgeBox);

        retranslateUi(DialogSimParameters);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSimParameters, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSimParameters, SLOT(reject()));
        QObject::connect(collectArrangementsCheckBox, SIGNAL(toggled(bool)), collectArrangementsSpinBox, SLOT(setEnabled(bool)));
        QObject::connect(cycleSizeSpinBox, SIGNAL(valueChanged(int)), cycleSizeSlider, SLOT(setValue(int)));
        QObject::connect(solutionsSpinBox, SIGNAL(valueChanged(int)), solutionsSlider, SLOT(setValue(int)));
        QObject::connect(solutionsSlider, SIGNAL(sliderMoved(int)), solutionsSpinBox, SLOT(setValue(int)));
        QObject::connect(excludeABDonorsBox, SIGNAL(toggled(bool)), DialogSimParameters, SLOT(enableBridgeDonorOptions(bool)));
        QObject::connect(chainLengthSpinBox, SIGNAL(valueChanged(int)), chainLengthSlider, SLOT(setValue(int)));
        QObject::connect(chainLengthSlider, SIGNAL(sliderMoved(int)), chainLengthSpinBox, SLOT(setValue(int)));
        QObject::connect(lrsSizeSpinBox, SIGNAL(valueChanged(int)), lrsSizeSlider, SLOT(setValue(int)));
        QObject::connect(cycleSizeSlider, SIGNAL(sliderMoved(int)), cycleSizeSpinBox, SLOT(setValue(int)));
        QObject::connect(lrsSizeSlider, SIGNAL(valueChanged(int)), lrsSizeSpinBox, SLOT(setValue(int)));
        QObject::connect(optComboBox, SIGNAL(currentIndexChanged(int)), DialogSimParameters, SLOT(enableOptimizationOptions(int)));
        QObject::connect(saveSolutionCheckBox, SIGNAL(toggled(bool)), folderLineEdit, SLOT(setEnabled(bool)));
        QObject::connect(saveSolutionCheckBox, SIGNAL(toggled(bool)), browseButton, SLOT(setEnabled(bool)));
        QObject::connect(browseButton, SIGNAL(clicked()), DialogSimParameters, SLOT(browse()));

        additionalParametersTabWidget->setCurrentIndex(0);
        optComboBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(DialogSimParameters);
    } // setupUi

    void retranslateUi(QDialog *DialogSimParameters)
    {
        DialogSimParameters->setWindowTitle(QApplication::translate("DialogSimParameters", "Set Parameters", 0));
        saveSolutionCheckBox->setText(QApplication::translate("DialogSimParameters", "Save Solution", 0));
        label->setText(QApplication::translate("DialogSimParameters", "Folder", 0));
        browseButton->setText(QApplication::translate("DialogSimParameters", "Browse...", 0));
        collectArrangementsCheckBox->setText(QApplication::translate("DialogSimParameters", "Collect All Exchanges", 0));
        collectArrangementsLabel->setText(QApplication::translate("DialogSimParameters", "Maximum Number of Exchanges to Collect", 0));
        optLabel->setText(QApplication::translate("DialogSimParameters", "Optimization Scheme", 0));
        optComboBox->clear();
        optComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSimParameters", "Cycles and Chains", 0)
         << QApplication::translate("DialogSimParameters", "Cycles and Chains With Fallbacks", 0)
         << QApplication::translate("DialogSimParameters", "Locally Relevant Subgraphs", 0)
        );
        utilLabel->setText(QApplication::translate("DialogSimParameters", "Utility Scheme", 0));
        utilComboBox->clear();
        utilComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSimParameters", "Transplants", 0)
         << QApplication::translate("DialogSimParameters", "5 Year Survival", 0)
         << QApplication::translate("DialogSimParameters", "10 Year Survival", 0)
         << QApplication::translate("DialogSimParameters", "Difficult-to-Transplant", 0)
         << QApplication::translate("DialogSimParameters", "Assigned Score", 0)
        );
        cycleSizeLabel->setText(QApplication::translate("DialogSimParameters", "Maximum Cycle Size", 0));
        chainLengthLabel->setText(QApplication::translate("DialogSimParameters", "Maximum Chain Length", 0));
        componentSizeLabel->setText(QApplication::translate("DialogSimParameters", "Maximum Subgraph Size", 0));
        solutionsLabel->setText(QApplication::translate("DialogSimParameters", "Number of Solutions", 0));
        additionalParametersTabWidget->setTabText(additionalParametersTabWidget->indexOf(tab), QApplication::translate("DialogSimParameters", "Simulation Parameters", 0));
        praCheckBox->setText(QApplication::translate("DialogSimParameters", "Add Advantage to High PRA Candidates", 0));
        praCutoffLabel->setText(QApplication::translate("DialogSimParameters", "PRA Cutoff", 0));
        praAdvantageLabel->setText(QApplication::translate("DialogSimParameters", "Advantage", 0));
        estimateEUCheckBox->setText(QApplication::translate("DialogSimParameters", "Estimate Expected Utility", 0));
        numberOfEUSimLabel->setText(QApplication::translate("DialogSimParameters", "Estimation Iterations", 0));
        reserveOtoOBox->setText(QApplication::translate("DialogSimParameters", "Reserve O Donors for O Recipients", 0));
        checkAdditionalHLABox->setText(QApplication::translate("DialogSimParameters", "Check Additional HLA Information", 0));
        compatibleBox->setText(QApplication::translate("DialogSimParameters", "Include Compatible Pairs in Match Run", 0));
        excludeABDonorsBox->setText(QApplication::translate("DialogSimParameters", "Exclude AB Donors from Simulation", 0));
        allowABBridgeBox->setText(QApplication::translate("DialogSimParameters", "Allow AB Bridge Donors", 0));
        additionalParametersTabWidget->setTabText(additionalParametersTabWidget->indexOf(additionalOptionsTab), QApplication::translate("DialogSimParameters", "Additional Options", 0));
        highlightTopSolutionCheckBox->setText(QApplication::translate("DialogSimParameters", "Cluster and Isolate Top Solution", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogSimParameters: public Ui_DialogSimParameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSIMPARAMETERS_H
