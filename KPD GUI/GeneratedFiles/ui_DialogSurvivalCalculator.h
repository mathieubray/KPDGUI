/********************************************************************************
** Form generated from reading UI file 'DialogSurvivalCalculator.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSURVIVALCALCULATOR_H
#define UI_DIALOGSURVIVALCALCULATOR_H

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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogSurvivalCalculator
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *donorGroupBox;
    QWidget *layoutWidget;
    QHBoxLayout *donorHLAAdditionalHorizontalLayout;
    QLabel *donorHLAAdditionalLabel;
    QLineEdit *donorHLALineEdit;
    QWidget *layoutWidget1;
    QGridLayout *donorHLAGridLayout;
    QLabel *donorCWLabel;
    QLabel *donorALabel;
    QLabel *donorBLabel;
    QLabel *donorDRLabel;
    QLabel *donorDQLabel;
    QComboBox *donorHLAA1ComboBox;
    QComboBox *donorHLAA2ComboBox;
    QComboBox *donorHLACW2ComboBox;
    QComboBox *donorHLAB1ComboBox;
    QComboBox *donorHLACW1ComboBox;
    QComboBox *donorHLAB2ComboBox;
    QComboBox *donorHLADQ1ComboBox;
    QComboBox *donorHLADR1ComboBox;
    QComboBox *donorHLADQ2ComboBox;
    QComboBox *donorHLADR2ComboBox;
    QWidget *layoutWidget2;
    QGridLayout *donorGridLayout;
    QLabel *donorAgeLabel;
    QSpinBox *donorAgeSpinBox;
    QSpacerItem *horizontalSpacer;
    QLabel *donorGenderLabel;
    QComboBox *donorGenderComboBox;
    QLabel *donorBTLabel;
    QComboBox *donorBTComboBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *donorWeightLabel;
    QDoubleSpinBox *donorWeightSpinBox;
    QLabel *donorRaceLabel;
    QComboBox *donorRaceComboBox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *donorHeightLabel;
    QDoubleSpinBox *donorHeightSpinBox;
    QCheckBox *donorCigaretteCheckBox;
    QGroupBox *donorHLABWLayout;
    QWidget *layoutWidget_6;
    QVBoxLayout *donorHLABWVerticalLayout;
    QCheckBox *donorBW4CheckBox;
    QCheckBox *donorBW6CheckBox;
    QGroupBox *donorHLADRLayout;
    QWidget *layoutWidget_5;
    QVBoxLayout *donorHLADRVerticalLayout;
    QCheckBox *donorDR51CheckBox;
    QCheckBox *donorDR52CheckBox;
    QCheckBox *donorDR53CheckBox;
    QGroupBox *candidateGroupBox;
    QWidget *layoutWidget_2;
    QGridLayout *candidateGridLayout;
    QSpinBox *candidatePRASpinBox;
    QLabel *candidateAdditionalLabel;
    QSpacerItem *candidateAgeSpacer;
    QLabel *candidateBTLabel;
    QComboBox *candidateBTComboBox;
    QSlider *praSlider;
    QLabel *candidateInsuranceLabel;
    QLabel *candidateAgeLabel;
    QSpacerItem *candidateBTSpacer;
    QSpinBox *candidateAgeSpinBox;
    QLabel *candidatePRALabel;
    QLineEdit *candidateHLALineEdit;
    QComboBox *candidateInsuranceComboBox;
    QWidget *layoutWidget3;
    QGridLayout *candidateCharacteristicsGridLayout;
    QSpacerItem *candidateGenderSpacer;
    QComboBox *candidateGenderComboBox;
    QSpacerItem *candidateWeightSpacer;
    QLabel *candidateHeightLabel;
    QLabel *candidateWeightLabel;
    QSpacerItem *candidateHeightSpacer;
    QLabel *candidateRaceLabel;
    QDoubleSpinBox *candidateTODSpinBox;
    QComboBox *candidateRaceComboBox;
    QSpacerItem *candidateRaceSpacer;
    QLabel *candidateGenderLabel;
    QLabel *candidateTODLabel;
    QDoubleSpinBox *candidateHeightSpinBox;
    QDoubleSpinBox *candidateWeightSpinBox;
    QWidget *layoutWidget4;
    QVBoxLayout *candidateVerticalLayout;
    QCheckBox *candidateHepCCheckBox;
    QCheckBox *candidateDiabetesCheckBox;
    QCheckBox *candidatePrevTransCheckBox;
    QTextEdit *crossmatchTextEdit;
    QLabel *crossmatchResultLabel;
    QLabel *fiveYearLabel;
    QTextEdit *fiveYearTextEdit;
    QListWidget *donorList;
    QLabel *copyDonorLabel;
    QLabel *copyCandidateLabel;
    QListWidget *candidateList;
    QLabel *tenYearLabel;
    QTextEdit *tenYearTextEdit;
    QTextEdit *survivalArrowTextEdit;

    void setupUi(QDialog *DialogSurvivalCalculator)
    {
        if (DialogSurvivalCalculator->objectName().isEmpty())
            DialogSurvivalCalculator->setObjectName(QStringLiteral("DialogSurvivalCalculator"));
        DialogSurvivalCalculator->resize(827, 684);
        DialogSurvivalCalculator->setMinimumSize(QSize(827, 684));
        DialogSurvivalCalculator->setMaximumSize(QSize(827, 684));
        buttonBox = new QDialogButtonBox(DialogSurvivalCalculator);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(470, 640, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        donorGroupBox = new QGroupBox(DialogSurvivalCalculator);
        donorGroupBox->setObjectName(QStringLiteral("donorGroupBox"));
        donorGroupBox->setGeometry(QRect(10, 10, 391, 371));
        layoutWidget = new QWidget(donorGroupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 300, 251, 59));
        donorHLAAdditionalHorizontalLayout = new QHBoxLayout(layoutWidget);
        donorHLAAdditionalHorizontalLayout->setObjectName(QStringLiteral("donorHLAAdditionalHorizontalLayout"));
        donorHLAAdditionalHorizontalLayout->setContentsMargins(0, 0, 0, 0);
        donorHLAAdditionalLabel = new QLabel(layoutWidget);
        donorHLAAdditionalLabel->setObjectName(QStringLiteral("donorHLAAdditionalLabel"));

        donorHLAAdditionalHorizontalLayout->addWidget(donorHLAAdditionalLabel);

        donorHLALineEdit = new QLineEdit(layoutWidget);
        donorHLALineEdit->setObjectName(QStringLiteral("donorHLALineEdit"));

        donorHLAAdditionalHorizontalLayout->addWidget(donorHLALineEdit);

        layoutWidget1 = new QWidget(donorGroupBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 150, 246, 140));
        donorHLAGridLayout = new QGridLayout(layoutWidget1);
        donorHLAGridLayout->setObjectName(QStringLiteral("donorHLAGridLayout"));
        donorHLAGridLayout->setContentsMargins(0, 0, 0, 0);
        donorCWLabel = new QLabel(layoutWidget1);
        donorCWLabel->setObjectName(QStringLiteral("donorCWLabel"));

        donorHLAGridLayout->addWidget(donorCWLabel, 2, 0, 1, 1);

        donorALabel = new QLabel(layoutWidget1);
        donorALabel->setObjectName(QStringLiteral("donorALabel"));

        donorHLAGridLayout->addWidget(donorALabel, 0, 0, 1, 1);

        donorBLabel = new QLabel(layoutWidget1);
        donorBLabel->setObjectName(QStringLiteral("donorBLabel"));

        donorHLAGridLayout->addWidget(donorBLabel, 1, 0, 1, 1);

        donorDRLabel = new QLabel(layoutWidget1);
        donorDRLabel->setObjectName(QStringLiteral("donorDRLabel"));

        donorHLAGridLayout->addWidget(donorDRLabel, 4, 0, 1, 1);

        donorDQLabel = new QLabel(layoutWidget1);
        donorDQLabel->setObjectName(QStringLiteral("donorDQLabel"));

        donorHLAGridLayout->addWidget(donorDQLabel, 3, 0, 1, 1);

        donorHLAA1ComboBox = new QComboBox(layoutWidget1);
        donorHLAA1ComboBox->setObjectName(QStringLiteral("donorHLAA1ComboBox"));

        donorHLAGridLayout->addWidget(donorHLAA1ComboBox, 0, 1, 1, 1);

        donorHLAA2ComboBox = new QComboBox(layoutWidget1);
        donorHLAA2ComboBox->setObjectName(QStringLiteral("donorHLAA2ComboBox"));

        donorHLAGridLayout->addWidget(donorHLAA2ComboBox, 0, 2, 1, 1);

        donorHLACW2ComboBox = new QComboBox(layoutWidget1);
        donorHLACW2ComboBox->setObjectName(QStringLiteral("donorHLACW2ComboBox"));

        donorHLAGridLayout->addWidget(donorHLACW2ComboBox, 2, 2, 1, 1);

        donorHLAB1ComboBox = new QComboBox(layoutWidget1);
        donorHLAB1ComboBox->setObjectName(QStringLiteral("donorHLAB1ComboBox"));

        donorHLAGridLayout->addWidget(donorHLAB1ComboBox, 1, 1, 1, 1);

        donorHLACW1ComboBox = new QComboBox(layoutWidget1);
        donorHLACW1ComboBox->setObjectName(QStringLiteral("donorHLACW1ComboBox"));

        donorHLAGridLayout->addWidget(donorHLACW1ComboBox, 2, 1, 1, 1);

        donorHLAB2ComboBox = new QComboBox(layoutWidget1);
        donorHLAB2ComboBox->setObjectName(QStringLiteral("donorHLAB2ComboBox"));

        donorHLAGridLayout->addWidget(donorHLAB2ComboBox, 1, 2, 1, 1);

        donorHLADQ1ComboBox = new QComboBox(layoutWidget1);
        donorHLADQ1ComboBox->setObjectName(QStringLiteral("donorHLADQ1ComboBox"));

        donorHLAGridLayout->addWidget(donorHLADQ1ComboBox, 3, 1, 1, 1);

        donorHLADR1ComboBox = new QComboBox(layoutWidget1);
        donorHLADR1ComboBox->setObjectName(QStringLiteral("donorHLADR1ComboBox"));

        donorHLAGridLayout->addWidget(donorHLADR1ComboBox, 4, 1, 1, 1);

        donorHLADQ2ComboBox = new QComboBox(layoutWidget1);
        donorHLADQ2ComboBox->setObjectName(QStringLiteral("donorHLADQ2ComboBox"));

        donorHLAGridLayout->addWidget(donorHLADQ2ComboBox, 3, 2, 1, 1);

        donorHLADR2ComboBox = new QComboBox(layoutWidget1);
        donorHLADR2ComboBox->setObjectName(QStringLiteral("donorHLADR2ComboBox"));

        donorHLAGridLayout->addWidget(donorHLADR2ComboBox, 4, 2, 1, 1);

        layoutWidget2 = new QWidget(donorGroupBox);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(11, 28, 363, 109));
        donorGridLayout = new QGridLayout(layoutWidget2);
        donorGridLayout->setObjectName(QStringLiteral("donorGridLayout"));
        donorGridLayout->setContentsMargins(0, 0, 0, 0);
        donorAgeLabel = new QLabel(layoutWidget2);
        donorAgeLabel->setObjectName(QStringLiteral("donorAgeLabel"));

        donorGridLayout->addWidget(donorAgeLabel, 0, 0, 1, 1);

        donorAgeSpinBox = new QSpinBox(layoutWidget2);
        donorAgeSpinBox->setObjectName(QStringLiteral("donorAgeSpinBox"));
        donorAgeSpinBox->setMaximum(130);
        donorAgeSpinBox->setValue(40);

        donorGridLayout->addWidget(donorAgeSpinBox, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        donorGridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        donorGenderLabel = new QLabel(layoutWidget2);
        donorGenderLabel->setObjectName(QStringLiteral("donorGenderLabel"));

        donorGridLayout->addWidget(donorGenderLabel, 0, 3, 1, 1);

        donorGenderComboBox = new QComboBox(layoutWidget2);
        donorGenderComboBox->setObjectName(QStringLiteral("donorGenderComboBox"));

        donorGridLayout->addWidget(donorGenderComboBox, 0, 4, 1, 1);

        donorBTLabel = new QLabel(layoutWidget2);
        donorBTLabel->setObjectName(QStringLiteral("donorBTLabel"));

        donorGridLayout->addWidget(donorBTLabel, 1, 0, 1, 1);

        donorBTComboBox = new QComboBox(layoutWidget2);
        donorBTComboBox->setObjectName(QStringLiteral("donorBTComboBox"));

        donorGridLayout->addWidget(donorBTComboBox, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        donorGridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        donorWeightLabel = new QLabel(layoutWidget2);
        donorWeightLabel->setObjectName(QStringLiteral("donorWeightLabel"));

        donorGridLayout->addWidget(donorWeightLabel, 1, 3, 1, 1);

        donorWeightSpinBox = new QDoubleSpinBox(layoutWidget2);
        donorWeightSpinBox->setObjectName(QStringLiteral("donorWeightSpinBox"));
        donorWeightSpinBox->setMaximum(400);
        donorWeightSpinBox->setValue(60);

        donorGridLayout->addWidget(donorWeightSpinBox, 1, 4, 1, 1);

        donorRaceLabel = new QLabel(layoutWidget2);
        donorRaceLabel->setObjectName(QStringLiteral("donorRaceLabel"));

        donorGridLayout->addWidget(donorRaceLabel, 2, 0, 1, 1);

        donorRaceComboBox = new QComboBox(layoutWidget2);
        donorRaceComboBox->setObjectName(QStringLiteral("donorRaceComboBox"));

        donorGridLayout->addWidget(donorRaceComboBox, 2, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        donorGridLayout->addItem(horizontalSpacer_3, 2, 2, 1, 1);

        donorHeightLabel = new QLabel(layoutWidget2);
        donorHeightLabel->setObjectName(QStringLiteral("donorHeightLabel"));

        donorGridLayout->addWidget(donorHeightLabel, 2, 3, 1, 1);

        donorHeightSpinBox = new QDoubleSpinBox(layoutWidget2);
        donorHeightSpinBox->setObjectName(QStringLiteral("donorHeightSpinBox"));
        donorHeightSpinBox->setMaximum(3);
        donorHeightSpinBox->setValue(1.5);

        donorGridLayout->addWidget(donorHeightSpinBox, 2, 4, 1, 1);

        donorCigaretteCheckBox = new QCheckBox(layoutWidget2);
        donorCigaretteCheckBox->setObjectName(QStringLiteral("donorCigaretteCheckBox"));
        donorCigaretteCheckBox->setLayoutDirection(Qt::RightToLeft);

        donorGridLayout->addWidget(donorCigaretteCheckBox, 3, 4, 1, 1);

        donorHLABWLayout = new QGroupBox(donorGroupBox);
        donorHLABWLayout->setObjectName(QStringLiteral("donorHLABWLayout"));
        donorHLABWLayout->setGeometry(QRect(271, 264, 103, 81));
        layoutWidget_6 = new QWidget(donorHLABWLayout);
        layoutWidget_6->setObjectName(QStringLiteral("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(20, 20, 55, 49));
        donorHLABWVerticalLayout = new QVBoxLayout(layoutWidget_6);
        donorHLABWVerticalLayout->setObjectName(QStringLiteral("donorHLABWVerticalLayout"));
        donorHLABWVerticalLayout->setContentsMargins(0, 0, 0, 0);
        donorBW4CheckBox = new QCheckBox(layoutWidget_6);
        donorBW4CheckBox->setObjectName(QStringLiteral("donorBW4CheckBox"));

        donorHLABWVerticalLayout->addWidget(donorBW4CheckBox);

        donorBW6CheckBox = new QCheckBox(layoutWidget_6);
        donorBW6CheckBox->setObjectName(QStringLiteral("donorBW6CheckBox"));

        donorHLABWVerticalLayout->addWidget(donorBW6CheckBox);

        donorHLADRLayout = new QGroupBox(donorGroupBox);
        donorHLADRLayout->setObjectName(QStringLiteral("donorHLADRLayout"));
        donorHLADRLayout->setGeometry(QRect(270, 150, 103, 106));
        layoutWidget_5 = new QWidget(donorHLADRLayout);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(20, 20, 59, 76));
        donorHLADRVerticalLayout = new QVBoxLayout(layoutWidget_5);
        donorHLADRVerticalLayout->setObjectName(QStringLiteral("donorHLADRVerticalLayout"));
        donorHLADRVerticalLayout->setContentsMargins(0, 0, 0, 0);
        donorDR51CheckBox = new QCheckBox(layoutWidget_5);
        donorDR51CheckBox->setObjectName(QStringLiteral("donorDR51CheckBox"));

        donorHLADRVerticalLayout->addWidget(donorDR51CheckBox);

        donorDR52CheckBox = new QCheckBox(layoutWidget_5);
        donorDR52CheckBox->setObjectName(QStringLiteral("donorDR52CheckBox"));

        donorHLADRVerticalLayout->addWidget(donorDR52CheckBox);

        donorDR53CheckBox = new QCheckBox(layoutWidget_5);
        donorDR53CheckBox->setObjectName(QStringLiteral("donorDR53CheckBox"));

        donorHLADRVerticalLayout->addWidget(donorDR53CheckBox);

        candidateGroupBox = new QGroupBox(DialogSurvivalCalculator);
        candidateGroupBox->setObjectName(QStringLiteral("candidateGroupBox"));
        candidateGroupBox->setGeometry(QRect(420, 10, 391, 371));
        layoutWidget_2 = new QWidget(candidateGroupBox);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 30, 361, 140));
        candidateGridLayout = new QGridLayout(layoutWidget_2);
        candidateGridLayout->setObjectName(QStringLiteral("candidateGridLayout"));
        candidateGridLayout->setContentsMargins(0, 0, 0, 0);
        candidatePRASpinBox = new QSpinBox(layoutWidget_2);
        candidatePRASpinBox->setObjectName(QStringLiteral("candidatePRASpinBox"));
        candidatePRASpinBox->setMaximum(100);

        candidateGridLayout->addWidget(candidatePRASpinBox, 2, 2, 1, 2);

        candidateAdditionalLabel = new QLabel(layoutWidget_2);
        candidateAdditionalLabel->setObjectName(QStringLiteral("candidateAdditionalLabel"));

        candidateGridLayout->addWidget(candidateAdditionalLabel, 3, 0, 1, 2);

        candidateAgeSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateGridLayout->addItem(candidateAgeSpacer, 0, 4, 1, 1);

        candidateBTLabel = new QLabel(layoutWidget_2);
        candidateBTLabel->setObjectName(QStringLiteral("candidateBTLabel"));

        candidateGridLayout->addWidget(candidateBTLabel, 1, 0, 1, 1);

        candidateBTComboBox = new QComboBox(layoutWidget_2);
        candidateBTComboBox->setObjectName(QStringLiteral("candidateBTComboBox"));

        candidateGridLayout->addWidget(candidateBTComboBox, 1, 2, 1, 2);

        praSlider = new QSlider(layoutWidget_2);
        praSlider->setObjectName(QStringLiteral("praSlider"));
        praSlider->setMaximum(100);
        praSlider->setOrientation(Qt::Horizontal);

        candidateGridLayout->addWidget(praSlider, 2, 4, 1, 1);

        candidateInsuranceLabel = new QLabel(layoutWidget_2);
        candidateInsuranceLabel->setObjectName(QStringLiteral("candidateInsuranceLabel"));

        candidateGridLayout->addWidget(candidateInsuranceLabel, 4, 0, 1, 1);

        candidateAgeLabel = new QLabel(layoutWidget_2);
        candidateAgeLabel->setObjectName(QStringLiteral("candidateAgeLabel"));

        candidateGridLayout->addWidget(candidateAgeLabel, 0, 0, 1, 1);

        candidateBTSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateGridLayout->addItem(candidateBTSpacer, 1, 4, 1, 1);

        candidateAgeSpinBox = new QSpinBox(layoutWidget_2);
        candidateAgeSpinBox->setObjectName(QStringLiteral("candidateAgeSpinBox"));
        candidateAgeSpinBox->setMaximum(130);
        candidateAgeSpinBox->setValue(40);

        candidateGridLayout->addWidget(candidateAgeSpinBox, 0, 2, 1, 2);

        candidatePRALabel = new QLabel(layoutWidget_2);
        candidatePRALabel->setObjectName(QStringLiteral("candidatePRALabel"));

        candidateGridLayout->addWidget(candidatePRALabel, 2, 0, 1, 1);

        candidateHLALineEdit = new QLineEdit(layoutWidget_2);
        candidateHLALineEdit->setObjectName(QStringLiteral("candidateHLALineEdit"));

        candidateGridLayout->addWidget(candidateHLALineEdit, 3, 2, 1, 3);

        candidateInsuranceComboBox = new QComboBox(layoutWidget_2);
        candidateInsuranceComboBox->setObjectName(QStringLiteral("candidateInsuranceComboBox"));

        candidateGridLayout->addWidget(candidateInsuranceComboBox, 4, 2, 1, 3);

        layoutWidget3 = new QWidget(candidateGroupBox);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 170, 201, 151));
        candidateCharacteristicsGridLayout = new QGridLayout(layoutWidget3);
        candidateCharacteristicsGridLayout->setObjectName(QStringLiteral("candidateCharacteristicsGridLayout"));
        candidateCharacteristicsGridLayout->setContentsMargins(0, 0, 0, 0);
        candidateGenderSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateCharacteristicsGridLayout->addItem(candidateGenderSpacer, 0, 1, 1, 1);

        candidateGenderComboBox = new QComboBox(layoutWidget3);
        candidateGenderComboBox->setObjectName(QStringLiteral("candidateGenderComboBox"));

        candidateCharacteristicsGridLayout->addWidget(candidateGenderComboBox, 0, 2, 1, 1);

        candidateWeightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateCharacteristicsGridLayout->addItem(candidateWeightSpacer, 3, 1, 1, 1);

        candidateHeightLabel = new QLabel(layoutWidget3);
        candidateHeightLabel->setObjectName(QStringLiteral("candidateHeightLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateHeightLabel, 4, 0, 1, 1);

        candidateWeightLabel = new QLabel(layoutWidget3);
        candidateWeightLabel->setObjectName(QStringLiteral("candidateWeightLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateWeightLabel, 3, 0, 1, 1);

        candidateHeightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateCharacteristicsGridLayout->addItem(candidateHeightSpacer, 4, 1, 1, 1);

        candidateRaceLabel = new QLabel(layoutWidget3);
        candidateRaceLabel->setObjectName(QStringLiteral("candidateRaceLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateRaceLabel, 1, 0, 1, 1);

        candidateTODSpinBox = new QDoubleSpinBox(layoutWidget3);
        candidateTODSpinBox->setObjectName(QStringLiteral("candidateTODSpinBox"));
        candidateTODSpinBox->setMaximum(200);

        candidateCharacteristicsGridLayout->addWidget(candidateTODSpinBox, 2, 2, 1, 1);

        candidateRaceComboBox = new QComboBox(layoutWidget3);
        candidateRaceComboBox->setObjectName(QStringLiteral("candidateRaceComboBox"));

        candidateCharacteristicsGridLayout->addWidget(candidateRaceComboBox, 1, 2, 1, 1);

        candidateRaceSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateCharacteristicsGridLayout->addItem(candidateRaceSpacer, 1, 1, 1, 1);

        candidateGenderLabel = new QLabel(layoutWidget3);
        candidateGenderLabel->setObjectName(QStringLiteral("candidateGenderLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateGenderLabel, 0, 0, 1, 1);

        candidateTODLabel = new QLabel(layoutWidget3);
        candidateTODLabel->setObjectName(QStringLiteral("candidateTODLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateTODLabel, 2, 0, 1, 2);

        candidateHeightSpinBox = new QDoubleSpinBox(layoutWidget3);
        candidateHeightSpinBox->setObjectName(QStringLiteral("candidateHeightSpinBox"));
        candidateHeightSpinBox->setMaximum(3);
        candidateHeightSpinBox->setValue(1.5);

        candidateCharacteristicsGridLayout->addWidget(candidateHeightSpinBox, 4, 2, 1, 1);

        candidateWeightSpinBox = new QDoubleSpinBox(layoutWidget3);
        candidateWeightSpinBox->setObjectName(QStringLiteral("candidateWeightSpinBox"));
        candidateWeightSpinBox->setMaximum(400);
        candidateWeightSpinBox->setValue(60);

        candidateCharacteristicsGridLayout->addWidget(candidateWeightSpinBox, 3, 2, 1, 1);

        layoutWidget4 = new QWidget(candidateGroupBox);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(220, 170, 151, 76));
        candidateVerticalLayout = new QVBoxLayout(layoutWidget4);
        candidateVerticalLayout->setObjectName(QStringLiteral("candidateVerticalLayout"));
        candidateVerticalLayout->setContentsMargins(0, 0, 0, 0);
        candidateHepCCheckBox = new QCheckBox(layoutWidget4);
        candidateHepCCheckBox->setObjectName(QStringLiteral("candidateHepCCheckBox"));
        candidateHepCCheckBox->setLayoutDirection(Qt::LeftToRight);

        candidateVerticalLayout->addWidget(candidateHepCCheckBox);

        candidateDiabetesCheckBox = new QCheckBox(layoutWidget4);
        candidateDiabetesCheckBox->setObjectName(QStringLiteral("candidateDiabetesCheckBox"));
        candidateDiabetesCheckBox->setLayoutDirection(Qt::LeftToRight);

        candidateVerticalLayout->addWidget(candidateDiabetesCheckBox);

        candidatePrevTransCheckBox = new QCheckBox(layoutWidget4);
        candidatePrevTransCheckBox->setObjectName(QStringLiteral("candidatePrevTransCheckBox"));
        candidatePrevTransCheckBox->setLayoutDirection(Qt::LeftToRight);

        candidateVerticalLayout->addWidget(candidatePrevTransCheckBox);

        crossmatchTextEdit = new QTextEdit(DialogSurvivalCalculator);
        crossmatchTextEdit->setObjectName(QStringLiteral("crossmatchTextEdit"));
        crossmatchTextEdit->setGeometry(QRect(200, 580, 611, 31));
        crossmatchTextEdit->setReadOnly(true);
        crossmatchResultLabel = new QLabel(DialogSurvivalCalculator);
        crossmatchResultLabel->setObjectName(QStringLiteral("crossmatchResultLabel"));
        crossmatchResultLabel->setGeometry(QRect(20, 590, 151, 16));
        fiveYearLabel = new QLabel(DialogSurvivalCalculator);
        fiveYearLabel->setObjectName(QStringLiteral("fiveYearLabel"));
        fiveYearLabel->setGeometry(QRect(20, 620, 161, 16));
        fiveYearTextEdit = new QTextEdit(DialogSurvivalCalculator);
        fiveYearTextEdit->setObjectName(QStringLiteral("fiveYearTextEdit"));
        fiveYearTextEdit->setGeometry(QRect(200, 610, 161, 31));
        fiveYearTextEdit->setReadOnly(true);
        donorList = new QListWidget(DialogSurvivalCalculator);
        donorList->setObjectName(QStringLiteral("donorList"));
        donorList->setGeometry(QRect(10, 420, 391, 151));
        copyDonorLabel = new QLabel(DialogSurvivalCalculator);
        copyDonorLabel->setObjectName(QStringLiteral("copyDonorLabel"));
        copyDonorLabel->setGeometry(QRect(10, 390, 141, 16));
        copyCandidateLabel = new QLabel(DialogSurvivalCalculator);
        copyCandidateLabel->setObjectName(QStringLiteral("copyCandidateLabel"));
        copyCandidateLabel->setGeometry(QRect(420, 390, 171, 16));
        candidateList = new QListWidget(DialogSurvivalCalculator);
        candidateList->setObjectName(QStringLiteral("candidateList"));
        candidateList->setGeometry(QRect(420, 420, 391, 151));
        tenYearLabel = new QLabel(DialogSurvivalCalculator);
        tenYearLabel->setObjectName(QStringLiteral("tenYearLabel"));
        tenYearLabel->setGeometry(QRect(20, 650, 161, 16));
        tenYearTextEdit = new QTextEdit(DialogSurvivalCalculator);
        tenYearTextEdit->setObjectName(QStringLiteral("tenYearTextEdit"));
        tenYearTextEdit->setGeometry(QRect(200, 640, 161, 31));
        tenYearTextEdit->setReadOnly(true);
        survivalArrowTextEdit = new QTextEdit(DialogSurvivalCalculator);
        survivalArrowTextEdit->setObjectName(QStringLiteral("survivalArrowTextEdit"));
        survivalArrowTextEdit->setGeometry(QRect(360, 610, 41, 61));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        font.setStyleStrategy(QFont::PreferDefault);
        survivalArrowTextEdit->setFont(font);
        survivalArrowTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        survivalArrowTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        survivalArrowTextEdit->setReadOnly(true);

        retranslateUi(DialogSurvivalCalculator);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogSurvivalCalculator, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogSurvivalCalculator, SLOT(reject()));
        QObject::connect(donorAgeSpinBox, SIGNAL(valueChanged(int)), DialogSurvivalCalculator, SLOT(updateDonorAge(int)));
        QObject::connect(donorCigaretteCheckBox, SIGNAL(toggled(bool)), DialogSurvivalCalculator, SLOT(updateDonorCigaretteUse(bool)));
        QObject::connect(donorBTComboBox, SIGNAL(currentIndexChanged(int)), DialogSurvivalCalculator, SLOT(updateDonorBT(int)));
        QObject::connect(candidateBTComboBox, SIGNAL(currentIndexChanged(int)), DialogSurvivalCalculator, SLOT(updateCandidateBT(int)));
        QObject::connect(donorRaceComboBox, SIGNAL(currentIndexChanged(int)), DialogSurvivalCalculator, SLOT(updateDonorRace(int)));
        QObject::connect(donorGenderComboBox, SIGNAL(currentIndexChanged(int)), DialogSurvivalCalculator, SLOT(updateDonorGender(int)));
        QObject::connect(donorWeightSpinBox, SIGNAL(valueChanged(double)), DialogSurvivalCalculator, SLOT(updateDonorWeight(double)));
        QObject::connect(donorHeightSpinBox, SIGNAL(valueChanged(double)), DialogSurvivalCalculator, SLOT(updateDonorHeight(double)));
        QObject::connect(candidateAgeSpinBox, SIGNAL(valueChanged(int)), DialogSurvivalCalculator, SLOT(updateCandidateAge(int)));
        QObject::connect(candidatePRASpinBox, SIGNAL(valueChanged(int)), praSlider, SLOT(setValue(int)));
        QObject::connect(praSlider, SIGNAL(valueChanged(int)), candidatePRASpinBox, SLOT(setValue(int)));
        QObject::connect(candidatePRASpinBox, SIGNAL(valueChanged(int)), DialogSurvivalCalculator, SLOT(updateCandidatePRA(int)));
        QObject::connect(candidateHLALineEdit, SIGNAL(textChanged(QString)), DialogSurvivalCalculator, SLOT(updateCandidateHLA(QString)));
        QObject::connect(candidateInsuranceComboBox, SIGNAL(currentIndexChanged(int)), DialogSurvivalCalculator, SLOT(updateCandidateInsurance(int)));
        QObject::connect(candidateGenderComboBox, SIGNAL(currentIndexChanged(int)), DialogSurvivalCalculator, SLOT(updateCandidateGender(int)));
        QObject::connect(candidateRaceComboBox, SIGNAL(currentIndexChanged(int)), DialogSurvivalCalculator, SLOT(updateCandidateRace(int)));
        QObject::connect(candidateTODSpinBox, SIGNAL(valueChanged(double)), DialogSurvivalCalculator, SLOT(updateCandidateTOD(double)));
        QObject::connect(candidateWeightSpinBox, SIGNAL(valueChanged(double)), DialogSurvivalCalculator, SLOT(updateCandidateWeight(double)));
        QObject::connect(candidateHeightSpinBox, SIGNAL(valueChanged(double)), DialogSurvivalCalculator, SLOT(updateDonorHeight(double)));
        QObject::connect(candidateHepCCheckBox, SIGNAL(toggled(bool)), DialogSurvivalCalculator, SLOT(updateCandidateHepC(bool)));
        QObject::connect(candidateDiabetesCheckBox, SIGNAL(toggled(bool)), DialogSurvivalCalculator, SLOT(updateCandidateDiabetes(bool)));
        QObject::connect(candidatePrevTransCheckBox, SIGNAL(toggled(bool)), DialogSurvivalCalculator, SLOT(updateCandidatePrevTrans(bool)));
        QObject::connect(donorHLALineEdit, SIGNAL(textChanged(QString)), DialogSurvivalCalculator, SLOT(updateAdditionalDonorHLA(QString)));
        QObject::connect(donorDR51CheckBox, SIGNAL(toggled(bool)), DialogSurvivalCalculator, SLOT(updateDonorDR51(bool)));
        QObject::connect(donorDR52CheckBox, SIGNAL(toggled(bool)), DialogSurvivalCalculator, SLOT(updateDonorDR52(bool)));
        QObject::connect(donorDR53CheckBox, SIGNAL(toggled(bool)), DialogSurvivalCalculator, SLOT(updateDonorDR53(bool)));
        QObject::connect(donorBW4CheckBox, SIGNAL(toggled(bool)), DialogSurvivalCalculator, SLOT(updateDonorBW4(bool)));
        QObject::connect(donorBW6CheckBox, SIGNAL(toggled(bool)), DialogSurvivalCalculator, SLOT(updateDonorBW6(bool)));
        QObject::connect(donorHLAB1ComboBox, SIGNAL(currentIndexChanged(QString)), DialogSurvivalCalculator, SLOT(updateDonorB()));
        QObject::connect(donorHLACW1ComboBox, SIGNAL(currentIndexChanged(QString)), DialogSurvivalCalculator, SLOT(updateDonorCW()));
        QObject::connect(donorHLADQ1ComboBox, SIGNAL(currentIndexChanged(QString)), DialogSurvivalCalculator, SLOT(updateDonorDQ()));
        QObject::connect(donorHLADR1ComboBox, SIGNAL(currentIndexChanged(QString)), DialogSurvivalCalculator, SLOT(updateDonorDR()));
        QObject::connect(donorHLAA2ComboBox, SIGNAL(currentIndexChanged(QString)), DialogSurvivalCalculator, SLOT(updateDonorA()));
        QObject::connect(donorHLAB2ComboBox, SIGNAL(currentIndexChanged(QString)), DialogSurvivalCalculator, SLOT(updateDonorB()));
        QObject::connect(donorHLACW2ComboBox, SIGNAL(currentIndexChanged(QString)), DialogSurvivalCalculator, SLOT(updateDonorCW()));
        QObject::connect(donorHLADQ2ComboBox, SIGNAL(currentIndexChanged(QString)), DialogSurvivalCalculator, SLOT(updateDonorDQ()));
        QObject::connect(donorHLADR2ComboBox, SIGNAL(currentIndexChanged(QString)), DialogSurvivalCalculator, SLOT(updateDonorDR()));
        QObject::connect(donorHLAA1ComboBox, SIGNAL(currentIndexChanged(QString)), DialogSurvivalCalculator, SLOT(updateDonorA()));
        QObject::connect(donorList, SIGNAL(itemPressed(QListWidgetItem*)), DialogSurvivalCalculator, SLOT(selectDonor(QListWidgetItem*)));
        QObject::connect(candidateList, SIGNAL(itemPressed(QListWidgetItem*)), DialogSurvivalCalculator, SLOT(selectCandidate(QListWidgetItem*)));

        donorGenderComboBox->setCurrentIndex(1);
        candidateGenderComboBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(DialogSurvivalCalculator);
    } // setupUi

    void retranslateUi(QDialog *DialogSurvivalCalculator)
    {
        DialogSurvivalCalculator->setWindowTitle(QApplication::translate("DialogSurvivalCalculator", "Survival Calculator", 0));
        donorGroupBox->setTitle(QApplication::translate("DialogSurvivalCalculator", "Donor Information", 0));
        donorHLAAdditionalLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Additional Donor Antigens", 0));
        donorCWLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Donor HLA CW", 0));
        donorALabel->setText(QApplication::translate("DialogSurvivalCalculator", "Donor HLA A", 0));
        donorBLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Donor HLA B", 0));
        donorDRLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Donor HLA DR", 0));
        donorDQLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Donor HLA DQ", 0));
        donorAgeLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Age", 0));
        donorGenderLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Gender", 0));
        donorGenderComboBox->clear();
        donorGenderComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSurvivalCalculator", "Male", 0)
         << QApplication::translate("DialogSurvivalCalculator", "Female", 0)
        );
        donorBTLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Blood Type", 0));
        donorBTComboBox->clear();
        donorBTComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSurvivalCalculator", "O", 0)
         << QApplication::translate("DialogSurvivalCalculator", "A", 0)
         << QApplication::translate("DialogSurvivalCalculator", "B", 0)
         << QApplication::translate("DialogSurvivalCalculator", "AB", 0)
        );
        donorWeightLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Weight (kg)", 0));
        donorRaceLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Race", 0));
        donorRaceComboBox->clear();
        donorRaceComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSurvivalCalculator", "White", 0)
         << QApplication::translate("DialogSurvivalCalculator", "Black", 0)
         << QApplication::translate("DialogSurvivalCalculator", "Hispanic", 0)
         << QApplication::translate("DialogSurvivalCalculator", "Other", 0)
        );
        donorHeightLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Height (m)", 0));
        donorCigaretteCheckBox->setText(QApplication::translate("DialogSurvivalCalculator", "Cigarette User", 0));
        donorHLABWLayout->setTitle(QApplication::translate("DialogSurvivalCalculator", "Donor HLA BW", 0));
        donorBW4CheckBox->setText(QApplication::translate("DialogSurvivalCalculator", "BW4", 0));
        donorBW6CheckBox->setText(QApplication::translate("DialogSurvivalCalculator", "BW6", 0));
        donorHLADRLayout->setTitle(QApplication::translate("DialogSurvivalCalculator", "Donor HLA DR", 0));
        donorDR51CheckBox->setText(QApplication::translate("DialogSurvivalCalculator", "DR51", 0));
        donorDR52CheckBox->setText(QApplication::translate("DialogSurvivalCalculator", "DR52", 0));
        donorDR53CheckBox->setText(QApplication::translate("DialogSurvivalCalculator", "DR53", 0));
        candidateGroupBox->setTitle(QApplication::translate("DialogSurvivalCalculator", "Candidate Information", 0));
        candidateAdditionalLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Candidate Antibodies", 0));
        candidateBTLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Blood Type", 0));
        candidateBTComboBox->clear();
        candidateBTComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSurvivalCalculator", "O", 0)
         << QApplication::translate("DialogSurvivalCalculator", "A", 0)
         << QApplication::translate("DialogSurvivalCalculator", "B", 0)
         << QApplication::translate("DialogSurvivalCalculator", "AB", 0)
        );
        candidateInsuranceLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Insurance", 0));
        candidateAgeLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Age", 0));
        candidatePRALabel->setText(QApplication::translate("DialogSurvivalCalculator", "PRA", 0));
        candidateInsuranceComboBox->clear();
        candidateInsuranceComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSurvivalCalculator", "Public Primary Payer", 0)
         << QApplication::translate("DialogSurvivalCalculator", "Private Primary Payer", 0)
         << QApplication::translate("DialogSurvivalCalculator", "Other", 0)
        );
        candidateGenderComboBox->clear();
        candidateGenderComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSurvivalCalculator", "Male", 0)
         << QApplication::translate("DialogSurvivalCalculator", "Female", 0)
        );
        candidateHeightLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Height (m)", 0));
        candidateWeightLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Weight (kg)", 0));
        candidateRaceLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Race", 0));
        candidateRaceComboBox->clear();
        candidateRaceComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogSurvivalCalculator", "White", 0)
         << QApplication::translate("DialogSurvivalCalculator", "Black", 0)
         << QApplication::translate("DialogSurvivalCalculator", "Hispanic", 0)
         << QApplication::translate("DialogSurvivalCalculator", "Other", 0)
        );
        candidateGenderLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Gender", 0));
        candidateTODLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Months On Dialysis", 0));
        candidateHepCCheckBox->setText(QApplication::translate("DialogSurvivalCalculator", "Hepatitis C", 0));
        candidateDiabetesCheckBox->setText(QApplication::translate("DialogSurvivalCalculator", "Diabetes", 0));
        candidatePrevTransCheckBox->setText(QApplication::translate("DialogSurvivalCalculator", "Previous Transplant ", 0));
        crossmatchResultLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Crossmatch Result", 0));
        fiveYearLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Estimated 5 Year Survival", 0));
        copyDonorLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Copy Donor Information", 0));
        copyCandidateLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Copy Candidate Information", 0));
        tenYearLabel->setText(QApplication::translate("DialogSurvivalCalculator", "Estimated 10 Year Survival", 0));
        survivalArrowTextEdit->setHtml(QApplication::translate("DialogSurvivalCalculator", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:18pt; font-weight:600; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:14pt;\"><br /></p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogSurvivalCalculator: public Ui_DialogSurvivalCalculator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSURVIVALCALCULATOR_H
