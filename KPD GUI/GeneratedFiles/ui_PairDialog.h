/********************************************************************************
** Form generated from reading UI file 'PairDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAIRDIALOG_H
#define UI_PAIRDIALOG_H

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
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PairDialog
{
public:
    QTabWidget *morePairInfo;
    QWidget *donorCharacteristicsTab;
    QWidget *layoutWidget_2;
    QGridLayout *donorCharacteristicsGridLayout;
    QDoubleSpinBox *donorWeightSpinBox;
    QComboBox *donorGenderComboBox;
    QLabel *donorHeightLabel;
    QLabel *donorWeightLabel;
    QLabel *donorGenderLabel;
    QDoubleSpinBox *donorHeightSpinBox;
    QWidget *recipCharacteristicsTab;
    QWidget *layoutWidget;
    QGridLayout *recipCharacteristicsGridLayout;
    QSpacerItem *recipGenderSpacer;
    QComboBox *recipGenderComboBox;
    QSpacerItem *recipWeightSpacer;
    QLabel *recipHeightLabel;
    QLabel *recipWeightLabel;
    QSpacerItem *recipHeightSpacer;
    QLabel *recipRaceLabel;
    QDoubleSpinBox *recipTODSpinBox;
    QComboBox *recipRaceComboBox;
    QSpacerItem *recipRaceSpacer;
    QLabel *recipGenderLabel;
    QLabel *recipTODLabel;
    QDoubleSpinBox *recipHeightSpinBox;
    QDoubleSpinBox *recipWeightSpinBox;
    QWidget *layoutWidget1;
    QVBoxLayout *recipVerticalLayout;
    QCheckBox *recipHepCCheckBox;
    QCheckBox *recipDiabetesCheckBox;
    QCheckBox *recipSensitizedCheckBox;
    QCheckBox *recipPrevTransCheckBox;
    QWidget *hlaInfoTab;
    QGroupBox *donorHLADRLayout;
    QWidget *layoutWidget2;
    QVBoxLayout *donorHLADRVerticalLayout;
    QCheckBox *donorDR51CheckBox;
    QCheckBox *donorDR52CheckBox;
    QCheckBox *donorDR53CheckBox;
    QGroupBox *donorHLABWLayout;
    QWidget *layoutWidget_4;
    QVBoxLayout *donorHLABWVerticalLayout;
    QCheckBox *donorBW4CheckBox;
    QCheckBox *donorBW6CheckBox;
    QWidget *layoutWidget3;
    QGridLayout *donorHLAGridLayout;
    QLabel *donorALabel;
    QLineEdit *donorA1LineEdit;
    QLineEdit *donorA2LineEdit;
    QLabel *donorBLineEdit;
    QLineEdit *donorB1lineEdit;
    QLineEdit *donorB2LineEdit;
    QLabel *donorCWLineEdit;
    QLineEdit *donorCW1LineEdit;
    QLineEdit *donorCW2LineEdit;
    QLabel *donorDPLabel;
    QLineEdit *donorDP1LineEdit;
    QLineEdit *donorDP2LineEdit;
    QLabel *donorDQLabel;
    QLineEdit *donorDQ1LineEdit;
    QLineEdit *donorDQ2LineEdit;
    QLabel *donorDRLabel;
    QLineEdit *donorDR1LineEdit;
    QLineEdit *donorDR2LineEdit;
    QWidget *layoutWidget4;
    QHBoxLayout *recipAdditionalHorizontalLayout;
    QLabel *recipAdditionalLayout;
    QLineEdit *recipHLALineEdit;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout;
    QLabel *donorHLAAdditionalLabel;
    QLineEdit *donorHLALineEdit;
    QWidget *commentTab;
    QTextEdit *commentTextEdit;
    QWidget *layoutWidget6;
    QHBoxLayout *mainHorizontalLayout;
    QGroupBox *donorGroupBox;
    QWidget *layoutWidget7;
    QGridLayout *donorGridLayout;
    QLabel *donorNameLabel;
    QLineEdit *donorNameLineEdit;
    QLabel *donorAgeLabel;
    QLabel *donorBTLabel;
    QSpinBox *donorAgeSpinBox;
    QSpacerItem *donorAgeSpacer;
    QSpacerItem *donorBTSpacer;
    QComboBox *donorBTComboBox;
    QGroupBox *recipGroupBox;
    QWidget *layoutWidget8;
    QGridLayout *recipGridLayout;
    QLabel *recipNameLabel;
    QLineEdit *recipNameLineEdit;
    QLabel *recipAgeLabel;
    QSpinBox *recipAgeSpinBox;
    QSpacerItem *recipAgeSpacer;
    QLabel *recipBTLabel;
    QComboBox *recipBTComboBox;
    QSpacerItem *recipBTSpacer;
    QLabel *recipPRALabel;
    QSpinBox *recipPRASpinBox;
    QSlider *praSlider;
    QWidget *layoutWidget9;
    QVBoxLayout *verticalLayout;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PairDialog)
    {
        if (PairDialog->objectName().isEmpty())
            PairDialog->setObjectName(QStringLiteral("PairDialog"));
        PairDialog->resize(499, 412);
        PairDialog->setMinimumSize(QSize(499, 412));
        PairDialog->setMaximumSize(QSize(499, 412));
        morePairInfo = new QTabWidget(PairDialog);
        morePairInfo->setObjectName(QStringLiteral("morePairInfo"));
        morePairInfo->setEnabled(true);
        morePairInfo->setGeometry(QRect(10, 160, 471, 231));
        donorCharacteristicsTab = new QWidget();
        donorCharacteristicsTab->setObjectName(QStringLiteral("donorCharacteristicsTab"));
        layoutWidget_2 = new QWidget(donorCharacteristicsTab);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 10, 124, 74));
        donorCharacteristicsGridLayout = new QGridLayout(layoutWidget_2);
        donorCharacteristicsGridLayout->setObjectName(QStringLiteral("donorCharacteristicsGridLayout"));
        donorCharacteristicsGridLayout->setContentsMargins(0, 0, 0, 0);
        donorWeightSpinBox = new QDoubleSpinBox(layoutWidget_2);
        donorWeightSpinBox->setObjectName(QStringLiteral("donorWeightSpinBox"));
        donorWeightSpinBox->setMaximum(400);
        donorWeightSpinBox->setValue(60);

        donorCharacteristicsGridLayout->addWidget(donorWeightSpinBox, 1, 1, 1, 1);

        donorGenderComboBox = new QComboBox(layoutWidget_2);
        donorGenderComboBox->setObjectName(QStringLiteral("donorGenderComboBox"));

        donorCharacteristicsGridLayout->addWidget(donorGenderComboBox, 0, 1, 1, 1);

        donorHeightLabel = new QLabel(layoutWidget_2);
        donorHeightLabel->setObjectName(QStringLiteral("donorHeightLabel"));

        donorCharacteristicsGridLayout->addWidget(donorHeightLabel, 2, 0, 1, 1);

        donorWeightLabel = new QLabel(layoutWidget_2);
        donorWeightLabel->setObjectName(QStringLiteral("donorWeightLabel"));

        donorCharacteristicsGridLayout->addWidget(donorWeightLabel, 1, 0, 1, 1);

        donorGenderLabel = new QLabel(layoutWidget_2);
        donorGenderLabel->setObjectName(QStringLiteral("donorGenderLabel"));

        donorCharacteristicsGridLayout->addWidget(donorGenderLabel, 0, 0, 1, 1);

        donorHeightSpinBox = new QDoubleSpinBox(layoutWidget_2);
        donorHeightSpinBox->setObjectName(QStringLiteral("donorHeightSpinBox"));
        donorHeightSpinBox->setMaximum(3);
        donorHeightSpinBox->setValue(1.5);

        donorCharacteristicsGridLayout->addWidget(donorHeightSpinBox, 2, 1, 1, 1);

        morePairInfo->addTab(donorCharacteristicsTab, QString());
        recipCharacteristicsTab = new QWidget();
        recipCharacteristicsTab->setObjectName(QStringLiteral("recipCharacteristicsTab"));
        layoutWidget = new QWidget(recipCharacteristicsTab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 167, 126));
        recipCharacteristicsGridLayout = new QGridLayout(layoutWidget);
        recipCharacteristicsGridLayout->setObjectName(QStringLiteral("recipCharacteristicsGridLayout"));
        recipCharacteristicsGridLayout->setContentsMargins(0, 0, 0, 0);
        recipGenderSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipCharacteristicsGridLayout->addItem(recipGenderSpacer, 0, 1, 1, 1);

        recipGenderComboBox = new QComboBox(layoutWidget);
        recipGenderComboBox->setObjectName(QStringLiteral("recipGenderComboBox"));

        recipCharacteristicsGridLayout->addWidget(recipGenderComboBox, 0, 2, 1, 1);

        recipWeightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipCharacteristicsGridLayout->addItem(recipWeightSpacer, 3, 1, 1, 1);

        recipHeightLabel = new QLabel(layoutWidget);
        recipHeightLabel->setObjectName(QStringLiteral("recipHeightLabel"));

        recipCharacteristicsGridLayout->addWidget(recipHeightLabel, 4, 0, 1, 1);

        recipWeightLabel = new QLabel(layoutWidget);
        recipWeightLabel->setObjectName(QStringLiteral("recipWeightLabel"));

        recipCharacteristicsGridLayout->addWidget(recipWeightLabel, 3, 0, 1, 1);

        recipHeightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipCharacteristicsGridLayout->addItem(recipHeightSpacer, 4, 1, 1, 1);

        recipRaceLabel = new QLabel(layoutWidget);
        recipRaceLabel->setObjectName(QStringLiteral("recipRaceLabel"));

        recipCharacteristicsGridLayout->addWidget(recipRaceLabel, 1, 0, 1, 1);

        recipTODSpinBox = new QDoubleSpinBox(layoutWidget);
        recipTODSpinBox->setObjectName(QStringLiteral("recipTODSpinBox"));
        recipTODSpinBox->setMaximum(200);

        recipCharacteristicsGridLayout->addWidget(recipTODSpinBox, 2, 2, 1, 1);

        recipRaceComboBox = new QComboBox(layoutWidget);
        recipRaceComboBox->setObjectName(QStringLiteral("recipRaceComboBox"));

        recipCharacteristicsGridLayout->addWidget(recipRaceComboBox, 1, 2, 1, 1);

        recipRaceSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipCharacteristicsGridLayout->addItem(recipRaceSpacer, 1, 1, 1, 1);

        recipGenderLabel = new QLabel(layoutWidget);
        recipGenderLabel->setObjectName(QStringLiteral("recipGenderLabel"));

        recipCharacteristicsGridLayout->addWidget(recipGenderLabel, 0, 0, 1, 1);

        recipTODLabel = new QLabel(layoutWidget);
        recipTODLabel->setObjectName(QStringLiteral("recipTODLabel"));

        recipCharacteristicsGridLayout->addWidget(recipTODLabel, 2, 0, 1, 2);

        recipHeightSpinBox = new QDoubleSpinBox(layoutWidget);
        recipHeightSpinBox->setObjectName(QStringLiteral("recipHeightSpinBox"));
        recipHeightSpinBox->setMaximum(3);
        recipHeightSpinBox->setValue(1.5);

        recipCharacteristicsGridLayout->addWidget(recipHeightSpinBox, 4, 2, 1, 1);

        recipWeightSpinBox = new QDoubleSpinBox(layoutWidget);
        recipWeightSpinBox->setObjectName(QStringLiteral("recipWeightSpinBox"));
        recipWeightSpinBox->setMaximum(400);
        recipWeightSpinBox->setValue(60);

        recipCharacteristicsGridLayout->addWidget(recipWeightSpinBox, 3, 2, 1, 1);

        layoutWidget1 = new QWidget(recipCharacteristicsTab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(200, 10, 122, 88));
        recipVerticalLayout = new QVBoxLayout(layoutWidget1);
        recipVerticalLayout->setObjectName(QStringLiteral("recipVerticalLayout"));
        recipVerticalLayout->setContentsMargins(0, 0, 0, 0);
        recipHepCCheckBox = new QCheckBox(layoutWidget1);
        recipHepCCheckBox->setObjectName(QStringLiteral("recipHepCCheckBox"));
        recipHepCCheckBox->setLayoutDirection(Qt::LeftToRight);

        recipVerticalLayout->addWidget(recipHepCCheckBox);

        recipDiabetesCheckBox = new QCheckBox(layoutWidget1);
        recipDiabetesCheckBox->setObjectName(QStringLiteral("recipDiabetesCheckBox"));
        recipDiabetesCheckBox->setLayoutDirection(Qt::LeftToRight);

        recipVerticalLayout->addWidget(recipDiabetesCheckBox);

        recipSensitizedCheckBox = new QCheckBox(layoutWidget1);
        recipSensitizedCheckBox->setObjectName(QStringLiteral("recipSensitizedCheckBox"));
        recipSensitizedCheckBox->setLayoutDirection(Qt::LeftToRight);

        recipVerticalLayout->addWidget(recipSensitizedCheckBox);

        recipPrevTransCheckBox = new QCheckBox(layoutWidget1);
        recipPrevTransCheckBox->setObjectName(QStringLiteral("recipPrevTransCheckBox"));
        recipPrevTransCheckBox->setLayoutDirection(Qt::LeftToRight);

        recipVerticalLayout->addWidget(recipPrevTransCheckBox);

        morePairInfo->addTab(recipCharacteristicsTab, QString());
        hlaInfoTab = new QWidget();
        hlaInfoTab->setObjectName(QStringLiteral("hlaInfoTab"));
        donorHLADRLayout = new QGroupBox(hlaInfoTab);
        donorHLADRLayout->setObjectName(QStringLiteral("donorHLADRLayout"));
        donorHLADRLayout->setGeometry(QRect(210, 40, 91, 91));
        layoutWidget2 = new QWidget(donorHLADRLayout);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 20, 51, 65));
        donorHLADRVerticalLayout = new QVBoxLayout(layoutWidget2);
        donorHLADRVerticalLayout->setObjectName(QStringLiteral("donorHLADRVerticalLayout"));
        donorHLADRVerticalLayout->setContentsMargins(0, 0, 0, 0);
        donorDR51CheckBox = new QCheckBox(layoutWidget2);
        donorDR51CheckBox->setObjectName(QStringLiteral("donorDR51CheckBox"));

        donorHLADRVerticalLayout->addWidget(donorDR51CheckBox);

        donorDR52CheckBox = new QCheckBox(layoutWidget2);
        donorDR52CheckBox->setObjectName(QStringLiteral("donorDR52CheckBox"));

        donorHLADRVerticalLayout->addWidget(donorDR52CheckBox);

        donorDR53CheckBox = new QCheckBox(layoutWidget2);
        donorDR53CheckBox->setObjectName(QStringLiteral("donorDR53CheckBox"));

        donorHLADRVerticalLayout->addWidget(donorDR53CheckBox);

        donorHLABWLayout = new QGroupBox(hlaInfoTab);
        donorHLABWLayout->setObjectName(QStringLiteral("donorHLABWLayout"));
        donorHLABWLayout->setGeometry(QRect(309, 40, 91, 91));
        layoutWidget_4 = new QWidget(donorHLABWLayout);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(20, 20, 47, 42));
        donorHLABWVerticalLayout = new QVBoxLayout(layoutWidget_4);
        donorHLABWVerticalLayout->setObjectName(QStringLiteral("donorHLABWVerticalLayout"));
        donorHLABWVerticalLayout->setContentsMargins(0, 0, 0, 0);
        donorBW4CheckBox = new QCheckBox(layoutWidget_4);
        donorBW4CheckBox->setObjectName(QStringLiteral("donorBW4CheckBox"));

        donorHLABWVerticalLayout->addWidget(donorBW4CheckBox);

        donorBW6CheckBox = new QCheckBox(layoutWidget_4);
        donorBW6CheckBox->setObjectName(QStringLiteral("donorBW6CheckBox"));

        donorHLABWVerticalLayout->addWidget(donorBW6CheckBox);

        layoutWidget3 = new QWidget(hlaInfoTab);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 40, 191, 152));
        donorHLAGridLayout = new QGridLayout(layoutWidget3);
        donorHLAGridLayout->setObjectName(QStringLiteral("donorHLAGridLayout"));
        donorHLAGridLayout->setContentsMargins(0, 0, 0, 0);
        donorALabel = new QLabel(layoutWidget3);
        donorALabel->setObjectName(QStringLiteral("donorALabel"));

        donorHLAGridLayout->addWidget(donorALabel, 0, 0, 1, 1);

        donorA1LineEdit = new QLineEdit(layoutWidget3);
        donorA1LineEdit->setObjectName(QStringLiteral("donorA1LineEdit"));

        donorHLAGridLayout->addWidget(donorA1LineEdit, 0, 1, 1, 1);

        donorA2LineEdit = new QLineEdit(layoutWidget3);
        donorA2LineEdit->setObjectName(QStringLiteral("donorA2LineEdit"));

        donorHLAGridLayout->addWidget(donorA2LineEdit, 0, 2, 1, 1);

        donorBLineEdit = new QLabel(layoutWidget3);
        donorBLineEdit->setObjectName(QStringLiteral("donorBLineEdit"));

        donorHLAGridLayout->addWidget(donorBLineEdit, 1, 0, 1, 1);

        donorB1lineEdit = new QLineEdit(layoutWidget3);
        donorB1lineEdit->setObjectName(QStringLiteral("donorB1lineEdit"));

        donorHLAGridLayout->addWidget(donorB1lineEdit, 1, 1, 1, 1);

        donorB2LineEdit = new QLineEdit(layoutWidget3);
        donorB2LineEdit->setObjectName(QStringLiteral("donorB2LineEdit"));

        donorHLAGridLayout->addWidget(donorB2LineEdit, 1, 2, 1, 1);

        donorCWLineEdit = new QLabel(layoutWidget3);
        donorCWLineEdit->setObjectName(QStringLiteral("donorCWLineEdit"));

        donorHLAGridLayout->addWidget(donorCWLineEdit, 2, 0, 1, 1);

        donorCW1LineEdit = new QLineEdit(layoutWidget3);
        donorCW1LineEdit->setObjectName(QStringLiteral("donorCW1LineEdit"));

        donorHLAGridLayout->addWidget(donorCW1LineEdit, 2, 1, 1, 1);

        donorCW2LineEdit = new QLineEdit(layoutWidget3);
        donorCW2LineEdit->setObjectName(QStringLiteral("donorCW2LineEdit"));

        donorHLAGridLayout->addWidget(donorCW2LineEdit, 2, 2, 1, 1);

        donorDPLabel = new QLabel(layoutWidget3);
        donorDPLabel->setObjectName(QStringLiteral("donorDPLabel"));

        donorHLAGridLayout->addWidget(donorDPLabel, 3, 0, 1, 1);

        donorDP1LineEdit = new QLineEdit(layoutWidget3);
        donorDP1LineEdit->setObjectName(QStringLiteral("donorDP1LineEdit"));

        donorHLAGridLayout->addWidget(donorDP1LineEdit, 3, 1, 1, 1);

        donorDP2LineEdit = new QLineEdit(layoutWidget3);
        donorDP2LineEdit->setObjectName(QStringLiteral("donorDP2LineEdit"));

        donorHLAGridLayout->addWidget(donorDP2LineEdit, 3, 2, 1, 1);

        donorDQLabel = new QLabel(layoutWidget3);
        donorDQLabel->setObjectName(QStringLiteral("donorDQLabel"));

        donorHLAGridLayout->addWidget(donorDQLabel, 4, 0, 1, 1);

        donorDQ1LineEdit = new QLineEdit(layoutWidget3);
        donorDQ1LineEdit->setObjectName(QStringLiteral("donorDQ1LineEdit"));

        donorHLAGridLayout->addWidget(donorDQ1LineEdit, 4, 1, 1, 1);

        donorDQ2LineEdit = new QLineEdit(layoutWidget3);
        donorDQ2LineEdit->setObjectName(QStringLiteral("donorDQ2LineEdit"));

        donorHLAGridLayout->addWidget(donorDQ2LineEdit, 4, 2, 1, 1);

        donorDRLabel = new QLabel(layoutWidget3);
        donorDRLabel->setObjectName(QStringLiteral("donorDRLabel"));

        donorHLAGridLayout->addWidget(donorDRLabel, 5, 0, 1, 1);

        donorDR1LineEdit = new QLineEdit(layoutWidget3);
        donorDR1LineEdit->setObjectName(QStringLiteral("donorDR1LineEdit"));

        donorHLAGridLayout->addWidget(donorDR1LineEdit, 5, 1, 1, 1);

        donorDR2LineEdit = new QLineEdit(layoutWidget3);
        donorDR2LineEdit->setObjectName(QStringLiteral("donorDR2LineEdit"));

        donorHLAGridLayout->addWidget(donorDR2LineEdit, 5, 2, 1, 1);

        layoutWidget4 = new QWidget(hlaInfoTab);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 10, 391, 22));
        recipAdditionalHorizontalLayout = new QHBoxLayout(layoutWidget4);
        recipAdditionalHorizontalLayout->setObjectName(QStringLiteral("recipAdditionalHorizontalLayout"));
        recipAdditionalHorizontalLayout->setContentsMargins(0, 0, 0, 0);
        recipAdditionalLayout = new QLabel(layoutWidget4);
        recipAdditionalLayout->setObjectName(QStringLiteral("recipAdditionalLayout"));

        recipAdditionalHorizontalLayout->addWidget(recipAdditionalLayout);

        recipHLALineEdit = new QLineEdit(layoutWidget4);
        recipHLALineEdit->setObjectName(QStringLiteral("recipHLALineEdit"));

        recipAdditionalHorizontalLayout->addWidget(recipHLALineEdit);

        layoutWidget5 = new QWidget(hlaInfoTab);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(211, 171, 251, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget5);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        donorHLAAdditionalLabel = new QLabel(layoutWidget5);
        donorHLAAdditionalLabel->setObjectName(QStringLiteral("donorHLAAdditionalLabel"));

        horizontalLayout->addWidget(donorHLAAdditionalLabel);

        donorHLALineEdit = new QLineEdit(layoutWidget5);
        donorHLALineEdit->setObjectName(QStringLiteral("donorHLALineEdit"));

        horizontalLayout->addWidget(donorHLALineEdit);

        morePairInfo->addTab(hlaInfoTab, QString());
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        donorHLABWLayout->raise();
        donorHLADRLayout->raise();
        commentTab = new QWidget();
        commentTab->setObjectName(QStringLiteral("commentTab"));
        commentTextEdit = new QTextEdit(commentTab);
        commentTextEdit->setObjectName(QStringLiteral("commentTextEdit"));
        commentTextEdit->setGeometry(QRect(10, 10, 441, 181));
        morePairInfo->addTab(commentTab, QString());
        layoutWidget6 = new QWidget(PairDialog);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(10, 10, 391, 141));
        mainHorizontalLayout = new QHBoxLayout(layoutWidget6);
        mainHorizontalLayout->setObjectName(QStringLiteral("mainHorizontalLayout"));
        mainHorizontalLayout->setContentsMargins(0, 0, 0, 0);
        donorGroupBox = new QGroupBox(layoutWidget6);
        donorGroupBox->setObjectName(QStringLiteral("donorGroupBox"));
        layoutWidget7 = new QWidget(donorGroupBox);
        layoutWidget7->setObjectName(QStringLiteral("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(10, 30, 161, 74));
        donorGridLayout = new QGridLayout(layoutWidget7);
        donorGridLayout->setObjectName(QStringLiteral("donorGridLayout"));
        donorGridLayout->setContentsMargins(0, 0, 0, 0);
        donorNameLabel = new QLabel(layoutWidget7);
        donorNameLabel->setObjectName(QStringLiteral("donorNameLabel"));

        donorGridLayout->addWidget(donorNameLabel, 0, 0, 1, 1);

        donorNameLineEdit = new QLineEdit(layoutWidget7);
        donorNameLineEdit->setObjectName(QStringLiteral("donorNameLineEdit"));

        donorGridLayout->addWidget(donorNameLineEdit, 0, 1, 1, 2);

        donorAgeLabel = new QLabel(layoutWidget7);
        donorAgeLabel->setObjectName(QStringLiteral("donorAgeLabel"));

        donorGridLayout->addWidget(donorAgeLabel, 1, 0, 1, 1);

        donorBTLabel = new QLabel(layoutWidget7);
        donorBTLabel->setObjectName(QStringLiteral("donorBTLabel"));

        donorGridLayout->addWidget(donorBTLabel, 2, 0, 1, 1);

        donorAgeSpinBox = new QSpinBox(layoutWidget7);
        donorAgeSpinBox->setObjectName(QStringLiteral("donorAgeSpinBox"));
        donorAgeSpinBox->setMaximum(130);
        donorAgeSpinBox->setValue(40);

        donorGridLayout->addWidget(donorAgeSpinBox, 1, 1, 1, 1);

        donorAgeSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        donorGridLayout->addItem(donorAgeSpacer, 1, 2, 1, 1);

        donorBTSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        donorGridLayout->addItem(donorBTSpacer, 2, 2, 1, 1);

        donorBTComboBox = new QComboBox(layoutWidget7);
        donorBTComboBox->setObjectName(QStringLiteral("donorBTComboBox"));

        donorGridLayout->addWidget(donorBTComboBox, 2, 1, 1, 1);


        mainHorizontalLayout->addWidget(donorGroupBox);

        recipGroupBox = new QGroupBox(layoutWidget6);
        recipGroupBox->setObjectName(QStringLiteral("recipGroupBox"));
        layoutWidget8 = new QWidget(recipGroupBox);
        layoutWidget8->setObjectName(QStringLiteral("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(10, 30, 161, 100));
        recipGridLayout = new QGridLayout(layoutWidget8);
        recipGridLayout->setObjectName(QStringLiteral("recipGridLayout"));
        recipGridLayout->setContentsMargins(0, 0, 0, 0);
        recipNameLabel = new QLabel(layoutWidget8);
        recipNameLabel->setObjectName(QStringLiteral("recipNameLabel"));

        recipGridLayout->addWidget(recipNameLabel, 0, 0, 1, 1);

        recipNameLineEdit = new QLineEdit(layoutWidget8);
        recipNameLineEdit->setObjectName(QStringLiteral("recipNameLineEdit"));

        recipGridLayout->addWidget(recipNameLineEdit, 0, 1, 1, 2);

        recipAgeLabel = new QLabel(layoutWidget8);
        recipAgeLabel->setObjectName(QStringLiteral("recipAgeLabel"));

        recipGridLayout->addWidget(recipAgeLabel, 1, 0, 1, 1);

        recipAgeSpinBox = new QSpinBox(layoutWidget8);
        recipAgeSpinBox->setObjectName(QStringLiteral("recipAgeSpinBox"));
        recipAgeSpinBox->setMaximum(130);
        recipAgeSpinBox->setValue(40);

        recipGridLayout->addWidget(recipAgeSpinBox, 1, 1, 1, 1);

        recipAgeSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipGridLayout->addItem(recipAgeSpacer, 1, 2, 1, 1);

        recipBTLabel = new QLabel(layoutWidget8);
        recipBTLabel->setObjectName(QStringLiteral("recipBTLabel"));

        recipGridLayout->addWidget(recipBTLabel, 2, 0, 1, 1);

        recipBTComboBox = new QComboBox(layoutWidget8);
        recipBTComboBox->setObjectName(QStringLiteral("recipBTComboBox"));

        recipGridLayout->addWidget(recipBTComboBox, 2, 1, 1, 1);

        recipBTSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipGridLayout->addItem(recipBTSpacer, 2, 2, 1, 1);

        recipPRALabel = new QLabel(layoutWidget8);
        recipPRALabel->setObjectName(QStringLiteral("recipPRALabel"));

        recipGridLayout->addWidget(recipPRALabel, 3, 0, 1, 1);

        recipPRASpinBox = new QSpinBox(layoutWidget8);
        recipPRASpinBox->setObjectName(QStringLiteral("recipPRASpinBox"));
        recipPRASpinBox->setMaximum(100);

        recipGridLayout->addWidget(recipPRASpinBox, 3, 1, 1, 1);

        praSlider = new QSlider(layoutWidget8);
        praSlider->setObjectName(QStringLiteral("praSlider"));
        praSlider->setMaximum(100);
        praSlider->setOrientation(Qt::Horizontal);

        recipGridLayout->addWidget(praSlider, 3, 2, 1, 1);


        mainHorizontalLayout->addWidget(recipGroupBox);

        layoutWidget9 = new QWidget(PairDialog);
        layoutWidget9->setObjectName(QStringLiteral("layoutWidget9"));
        layoutWidget9->setGeometry(QRect(410, 18, 77, 131));
        verticalLayout = new QVBoxLayout(layoutWidget9);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        buttonBox = new QDialogButtonBox(layoutWidget9);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        layoutWidget->raise();
        layoutWidget->raise();
        morePairInfo->raise();
        QWidget::setTabOrder(donorNameLineEdit, donorAgeSpinBox);
        QWidget::setTabOrder(donorAgeSpinBox, donorBTComboBox);
        QWidget::setTabOrder(donorBTComboBox, recipNameLineEdit);
        QWidget::setTabOrder(recipNameLineEdit, recipAgeSpinBox);
        QWidget::setTabOrder(recipAgeSpinBox, recipBTComboBox);
        QWidget::setTabOrder(recipBTComboBox, recipPRASpinBox);
        QWidget::setTabOrder(recipPRASpinBox, praSlider);
        QWidget::setTabOrder(praSlider, morePairInfo);
        QWidget::setTabOrder(morePairInfo, donorGenderComboBox);
        QWidget::setTabOrder(donorGenderComboBox, donorWeightSpinBox);
        QWidget::setTabOrder(donorWeightSpinBox, donorHeightSpinBox);
        QWidget::setTabOrder(donorHeightSpinBox, recipGenderComboBox);
        QWidget::setTabOrder(recipGenderComboBox, recipRaceComboBox);
        QWidget::setTabOrder(recipRaceComboBox, recipTODSpinBox);
        QWidget::setTabOrder(recipTODSpinBox, recipWeightSpinBox);
        QWidget::setTabOrder(recipWeightSpinBox, recipHeightSpinBox);
        QWidget::setTabOrder(recipHeightSpinBox, recipHepCCheckBox);
        QWidget::setTabOrder(recipHepCCheckBox, recipDiabetesCheckBox);
        QWidget::setTabOrder(recipDiabetesCheckBox, recipSensitizedCheckBox);
        QWidget::setTabOrder(recipSensitizedCheckBox, recipPrevTransCheckBox);
        QWidget::setTabOrder(recipPrevTransCheckBox, recipHLALineEdit);
        QWidget::setTabOrder(recipHLALineEdit, donorA1LineEdit);
        QWidget::setTabOrder(donorA1LineEdit, donorA2LineEdit);
        QWidget::setTabOrder(donorA2LineEdit, donorB1lineEdit);
        QWidget::setTabOrder(donorB1lineEdit, donorB2LineEdit);
        QWidget::setTabOrder(donorB2LineEdit, donorCW1LineEdit);
        QWidget::setTabOrder(donorCW1LineEdit, donorCW2LineEdit);
        QWidget::setTabOrder(donorCW2LineEdit, donorDP1LineEdit);
        QWidget::setTabOrder(donorDP1LineEdit, donorDP2LineEdit);
        QWidget::setTabOrder(donorDP2LineEdit, donorDQ1LineEdit);
        QWidget::setTabOrder(donorDQ1LineEdit, donorDQ2LineEdit);
        QWidget::setTabOrder(donorDQ2LineEdit, donorDR1LineEdit);
        QWidget::setTabOrder(donorDR1LineEdit, donorDR2LineEdit);
        QWidget::setTabOrder(donorDR2LineEdit, donorDR51CheckBox);
        QWidget::setTabOrder(donorDR51CheckBox, donorDR52CheckBox);
        QWidget::setTabOrder(donorDR52CheckBox, donorDR53CheckBox);
        QWidget::setTabOrder(donorDR53CheckBox, donorBW4CheckBox);
        QWidget::setTabOrder(donorBW4CheckBox, donorBW6CheckBox);
        QWidget::setTabOrder(donorBW6CheckBox, donorHLALineEdit);

        retranslateUi(PairDialog);
        QObject::connect(recipPRASpinBox, SIGNAL(valueChanged(int)), praSlider, SLOT(setValue(int)));
        QObject::connect(praSlider, SIGNAL(sliderMoved(int)), recipPRASpinBox, SLOT(setValue(int)));
        QObject::connect(buttonBox, SIGNAL(rejected()), PairDialog, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), PairDialog, SLOT(accept()));

        morePairInfo->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PairDialog);
    } // setupUi

    void retranslateUi(QDialog *PairDialog)
    {
        PairDialog->setWindowTitle(QApplication::translate("PairDialog", "Add New Pair", 0));
        donorGenderComboBox->clear();
        donorGenderComboBox->insertItems(0, QStringList()
         << QApplication::translate("PairDialog", "Male", 0)
         << QApplication::translate("PairDialog", "Female", 0)
        );
        donorHeightLabel->setText(QApplication::translate("PairDialog", "Height (m)", 0));
        donorWeightLabel->setText(QApplication::translate("PairDialog", "Weight (kg)", 0));
        donorGenderLabel->setText(QApplication::translate("PairDialog", "Gender", 0));
        morePairInfo->setTabText(morePairInfo->indexOf(donorCharacteristicsTab), QApplication::translate("PairDialog", "Donor Characteristics", 0));
        recipGenderComboBox->clear();
        recipGenderComboBox->insertItems(0, QStringList()
         << QApplication::translate("PairDialog", "Male", 0)
         << QApplication::translate("PairDialog", "Female", 0)
        );
        recipHeightLabel->setText(QApplication::translate("PairDialog", "Height (kg)", 0));
        recipWeightLabel->setText(QApplication::translate("PairDialog", "Weight (kg)", 0));
        recipRaceLabel->setText(QApplication::translate("PairDialog", "Race", 0));
        recipRaceComboBox->clear();
        recipRaceComboBox->insertItems(0, QStringList()
         << QApplication::translate("PairDialog", "White", 0)
         << QApplication::translate("PairDialog", "Black", 0)
         << QApplication::translate("PairDialog", "Hispanic", 0)
         << QApplication::translate("PairDialog", "Other", 0)
        );
        recipGenderLabel->setText(QApplication::translate("PairDialog", "Gender", 0));
        recipTODLabel->setText(QApplication::translate("PairDialog", "Months On Dialysis", 0));
        recipHepCCheckBox->setText(QApplication::translate("PairDialog", "Hepatitis C", 0));
        recipDiabetesCheckBox->setText(QApplication::translate("PairDialog", "Diabetes", 0));
        recipSensitizedCheckBox->setText(QApplication::translate("PairDialog", "Can Be Desensitized", 0));
        recipPrevTransCheckBox->setText(QApplication::translate("PairDialog", "Previous Transplant ", 0));
        morePairInfo->setTabText(morePairInfo->indexOf(recipCharacteristicsTab), QApplication::translate("PairDialog", "Recipient Characteristics", 0));
        donorHLADRLayout->setTitle(QApplication::translate("PairDialog", "Donor HLA DR", 0));
        donorDR51CheckBox->setText(QApplication::translate("PairDialog", "DR51", 0));
        donorDR52CheckBox->setText(QApplication::translate("PairDialog", "DR52", 0));
        donorDR53CheckBox->setText(QApplication::translate("PairDialog", "DR53", 0));
        donorHLABWLayout->setTitle(QApplication::translate("PairDialog", "Donor HLA BW", 0));
        donorBW4CheckBox->setText(QApplication::translate("PairDialog", "BW4", 0));
        donorBW6CheckBox->setText(QApplication::translate("PairDialog", "BW6", 0));
        donorALabel->setText(QApplication::translate("PairDialog", "Donor HLA A", 0));
        donorBLineEdit->setText(QApplication::translate("PairDialog", "Donor HLA B", 0));
        donorCWLineEdit->setText(QApplication::translate("PairDialog", "Donor HLA CW", 0));
        donorDPLabel->setText(QApplication::translate("PairDialog", "Donor HLA DP", 0));
        donorDQLabel->setText(QApplication::translate("PairDialog", "Donor HLA DQ", 0));
        donorDRLabel->setText(QApplication::translate("PairDialog", "Donor HLA DR", 0));
        recipAdditionalLayout->setText(QApplication::translate("PairDialog", "Recipient Antibodies", 0));
        donorHLAAdditionalLabel->setText(QApplication::translate("PairDialog", "Additional Donor Antigens", 0));
        morePairInfo->setTabText(morePairInfo->indexOf(hlaInfoTab), QApplication::translate("PairDialog", "HLA Information", 0));
        morePairInfo->setTabText(morePairInfo->indexOf(commentTab), QApplication::translate("PairDialog", "Comments", 0));
        donorGroupBox->setTitle(QApplication::translate("PairDialog", "Donor Information", 0));
        donorNameLabel->setText(QApplication::translate("PairDialog", "Name", 0));
        donorAgeLabel->setText(QApplication::translate("PairDialog", "Age", 0));
        donorBTLabel->setText(QApplication::translate("PairDialog", "Blood Type", 0));
        donorBTComboBox->clear();
        donorBTComboBox->insertItems(0, QStringList()
         << QApplication::translate("PairDialog", "O", 0)
         << QApplication::translate("PairDialog", "A", 0)
         << QApplication::translate("PairDialog", "B", 0)
         << QApplication::translate("PairDialog", "AB", 0)
        );
        recipGroupBox->setTitle(QApplication::translate("PairDialog", "Recipient Information", 0));
        recipNameLabel->setText(QApplication::translate("PairDialog", "Name", 0));
        recipAgeLabel->setText(QApplication::translate("PairDialog", "Age", 0));
        recipBTLabel->setText(QApplication::translate("PairDialog", "Blood Type", 0));
        recipBTComboBox->clear();
        recipBTComboBox->insertItems(0, QStringList()
         << QApplication::translate("PairDialog", "O", 0)
         << QApplication::translate("PairDialog", "A", 0)
         << QApplication::translate("PairDialog", "B", 0)
         << QApplication::translate("PairDialog", "AB", 0)
        );
        recipPRALabel->setText(QApplication::translate("PairDialog", "PRA", 0));
    } // retranslateUi

};

namespace Ui {
    class PairDialog: public Ui_PairDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAIRDIALOG_H
