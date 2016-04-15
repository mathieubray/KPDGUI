/********************************************************************************
** Form generated from reading UI file 'DialogCandidate.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCANDIDATE_H
#define UI_DIALOGCANDIDATE_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogCandidate
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *candidateGroupBox;
    QWidget *layoutWidget_3;
    QGridLayout *candidateGridLayout;
    QLabel *candidateBTLabel;
    QSpinBox *candidateAgeSpinBox;
    QLineEdit *candidateNameLineEdit;
    QLabel *candidateNameLabel;
    QLabel *candidateAgeLabel;
    QSpacerItem *candidateAgeSpacer;
    QComboBox *candidateBTComboBox;
    QSpacerItem *candidateBTSpacer;
    QLabel *candidatePRALabel;
    QSpinBox *candidatePRASpinBox;
    QSlider *praSlider;
    QHBoxLayout *candidateAdditionalHLAHorizontalLayout;
    QLabel *candidateAdditionalLabel;
    QLineEdit *candidateHLALineEdit;
    QWidget *layoutWidget1;
    QVBoxLayout *candidateVerticalLayout;
    QTabWidget *moreRecipInfo;
    QWidget *donorCharacteristicsTab;
    QWidget *widget;
    QVBoxLayout *donorCharacteristicsVerticalLayout;
    QHBoxLayout *donorMajorInfoHorizontalLayout;
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
    QVBoxLayout *donorMinorInfoVerticalLayout;
    QVBoxLayout *checkBoxesVerticalLayout;
    QCheckBox *candidateHepCCheckBox;
    QCheckBox *candidateDiabetesCheckBox;
    QCheckBox *candidatePrevTransCheckBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *excludedDonorsHorizontalLayout;
    QLabel *exccludedDonorsLabel;
    QLineEdit *excludedDonorLineEdit;
    QHBoxLayout *buttonBoxHorizontalLayout;
    QSpacerItem *buttonHorizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogCandidate)
    {
        if (DialogCandidate->objectName().isEmpty())
            DialogCandidate->setObjectName(QStringLiteral("DialogCandidate"));
        DialogCandidate->resize(392, 467);
        DialogCandidate->setMinimumSize(QSize(392, 467));
        DialogCandidate->setMaximumSize(QSize(392, 467));
        layoutWidget = new QWidget(DialogCandidate);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 361, 171));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        candidateGroupBox = new QGroupBox(layoutWidget);
        candidateGroupBox->setObjectName(QStringLiteral("candidateGroupBox"));
        layoutWidget_3 = new QWidget(candidateGroupBox);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 20, 341, 140));
        candidateGridLayout = new QGridLayout(layoutWidget_3);
        candidateGridLayout->setObjectName(QStringLiteral("candidateGridLayout"));
        candidateGridLayout->setContentsMargins(0, 0, 0, 0);
        candidateBTLabel = new QLabel(layoutWidget_3);
        candidateBTLabel->setObjectName(QStringLiteral("candidateBTLabel"));

        candidateGridLayout->addWidget(candidateBTLabel, 2, 0, 1, 1);

        candidateAgeSpinBox = new QSpinBox(layoutWidget_3);
        candidateAgeSpinBox->setObjectName(QStringLiteral("candidateAgeSpinBox"));
        candidateAgeSpinBox->setMaximum(130);
        candidateAgeSpinBox->setValue(40);

        candidateGridLayout->addWidget(candidateAgeSpinBox, 1, 1, 1, 1);

        candidateNameLineEdit = new QLineEdit(layoutWidget_3);
        candidateNameLineEdit->setObjectName(QStringLiteral("candidateNameLineEdit"));

        candidateGridLayout->addWidget(candidateNameLineEdit, 0, 1, 1, 2);

        candidateNameLabel = new QLabel(layoutWidget_3);
        candidateNameLabel->setObjectName(QStringLiteral("candidateNameLabel"));

        candidateGridLayout->addWidget(candidateNameLabel, 0, 0, 1, 1);

        candidateAgeLabel = new QLabel(layoutWidget_3);
        candidateAgeLabel->setObjectName(QStringLiteral("candidateAgeLabel"));

        candidateGridLayout->addWidget(candidateAgeLabel, 1, 0, 1, 1);

        candidateAgeSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateGridLayout->addItem(candidateAgeSpacer, 1, 2, 1, 1);

        candidateBTComboBox = new QComboBox(layoutWidget_3);
        candidateBTComboBox->setObjectName(QStringLiteral("candidateBTComboBox"));

        candidateGridLayout->addWidget(candidateBTComboBox, 2, 1, 1, 1);

        candidateBTSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateGridLayout->addItem(candidateBTSpacer, 2, 2, 1, 1);

        candidatePRALabel = new QLabel(layoutWidget_3);
        candidatePRALabel->setObjectName(QStringLiteral("candidatePRALabel"));

        candidateGridLayout->addWidget(candidatePRALabel, 3, 0, 1, 1);

        candidatePRASpinBox = new QSpinBox(layoutWidget_3);
        candidatePRASpinBox->setObjectName(QStringLiteral("candidatePRASpinBox"));
        candidatePRASpinBox->setMaximum(100);

        candidateGridLayout->addWidget(candidatePRASpinBox, 3, 1, 1, 1);

        praSlider = new QSlider(layoutWidget_3);
        praSlider->setObjectName(QStringLiteral("praSlider"));
        praSlider->setMaximum(100);
        praSlider->setOrientation(Qt::Horizontal);

        candidateGridLayout->addWidget(praSlider, 3, 2, 1, 1);

        candidateAdditionalHLAHorizontalLayout = new QHBoxLayout();
        candidateAdditionalHLAHorizontalLayout->setObjectName(QStringLiteral("candidateAdditionalHLAHorizontalLayout"));
        candidateAdditionalLabel = new QLabel(layoutWidget_3);
        candidateAdditionalLabel->setObjectName(QStringLiteral("candidateAdditionalLabel"));

        candidateAdditionalHLAHorizontalLayout->addWidget(candidateAdditionalLabel);


        candidateGridLayout->addLayout(candidateAdditionalHLAHorizontalLayout, 4, 0, 1, 1);

        candidateHLALineEdit = new QLineEdit(layoutWidget_3);
        candidateHLALineEdit->setObjectName(QStringLiteral("candidateHLALineEdit"));

        candidateGridLayout->addWidget(candidateHLALineEdit, 4, 1, 1, 2);


        horizontalLayout->addWidget(candidateGroupBox);

        layoutWidget1 = new QWidget(DialogCandidate);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 200, 371, 261));
        candidateVerticalLayout = new QVBoxLayout(layoutWidget1);
        candidateVerticalLayout->setObjectName(QStringLiteral("candidateVerticalLayout"));
        candidateVerticalLayout->setContentsMargins(0, 0, 0, 0);
        moreRecipInfo = new QTabWidget(layoutWidget1);
        moreRecipInfo->setObjectName(QStringLiteral("moreRecipInfo"));
        moreRecipInfo->setEnabled(true);
        donorCharacteristicsTab = new QWidget();
        donorCharacteristicsTab->setObjectName(QStringLiteral("donorCharacteristicsTab"));
        widget = new QWidget(donorCharacteristicsTab);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 351, 175));
        donorCharacteristicsVerticalLayout = new QVBoxLayout(widget);
        donorCharacteristicsVerticalLayout->setObjectName(QStringLiteral("donorCharacteristicsVerticalLayout"));
        donorCharacteristicsVerticalLayout->setContentsMargins(0, 0, 0, 0);
        donorMajorInfoHorizontalLayout = new QHBoxLayout();
        donorMajorInfoHorizontalLayout->setObjectName(QStringLiteral("donorMajorInfoHorizontalLayout"));
        candidateCharacteristicsGridLayout = new QGridLayout();
        candidateCharacteristicsGridLayout->setObjectName(QStringLiteral("candidateCharacteristicsGridLayout"));
        candidateGenderSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateCharacteristicsGridLayout->addItem(candidateGenderSpacer, 0, 1, 1, 1);

        candidateGenderComboBox = new QComboBox(widget);
        candidateGenderComboBox->setObjectName(QStringLiteral("candidateGenderComboBox"));

        candidateCharacteristicsGridLayout->addWidget(candidateGenderComboBox, 0, 2, 1, 1);

        candidateWeightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateCharacteristicsGridLayout->addItem(candidateWeightSpacer, 3, 1, 1, 1);

        candidateHeightLabel = new QLabel(widget);
        candidateHeightLabel->setObjectName(QStringLiteral("candidateHeightLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateHeightLabel, 4, 0, 1, 1);

        candidateWeightLabel = new QLabel(widget);
        candidateWeightLabel->setObjectName(QStringLiteral("candidateWeightLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateWeightLabel, 3, 0, 1, 1);

        candidateHeightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateCharacteristicsGridLayout->addItem(candidateHeightSpacer, 4, 1, 1, 1);

        candidateRaceLabel = new QLabel(widget);
        candidateRaceLabel->setObjectName(QStringLiteral("candidateRaceLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateRaceLabel, 1, 0, 1, 1);

        candidateTODSpinBox = new QDoubleSpinBox(widget);
        candidateTODSpinBox->setObjectName(QStringLiteral("candidateTODSpinBox"));
        candidateTODSpinBox->setMaximum(200);

        candidateCharacteristicsGridLayout->addWidget(candidateTODSpinBox, 2, 2, 1, 1);

        candidateRaceComboBox = new QComboBox(widget);
        candidateRaceComboBox->setObjectName(QStringLiteral("candidateRaceComboBox"));

        candidateCharacteristicsGridLayout->addWidget(candidateRaceComboBox, 1, 2, 1, 1);

        candidateRaceSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateCharacteristicsGridLayout->addItem(candidateRaceSpacer, 1, 1, 1, 1);

        candidateGenderLabel = new QLabel(widget);
        candidateGenderLabel->setObjectName(QStringLiteral("candidateGenderLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateGenderLabel, 0, 0, 1, 1);

        candidateTODLabel = new QLabel(widget);
        candidateTODLabel->setObjectName(QStringLiteral("candidateTODLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateTODLabel, 2, 0, 1, 2);

        candidateHeightSpinBox = new QDoubleSpinBox(widget);
        candidateHeightSpinBox->setObjectName(QStringLiteral("candidateHeightSpinBox"));
        candidateHeightSpinBox->setMaximum(3);
        candidateHeightSpinBox->setValue(1.5);

        candidateCharacteristicsGridLayout->addWidget(candidateHeightSpinBox, 4, 2, 1, 1);

        candidateWeightSpinBox = new QDoubleSpinBox(widget);
        candidateWeightSpinBox->setObjectName(QStringLiteral("candidateWeightSpinBox"));
        candidateWeightSpinBox->setMaximum(400);
        candidateWeightSpinBox->setValue(60);

        candidateCharacteristicsGridLayout->addWidget(candidateWeightSpinBox, 3, 2, 1, 1);


        donorMajorInfoHorizontalLayout->addLayout(candidateCharacteristicsGridLayout);

        donorMinorInfoVerticalLayout = new QVBoxLayout();
        donorMinorInfoVerticalLayout->setObjectName(QStringLiteral("donorMinorInfoVerticalLayout"));
        checkBoxesVerticalLayout = new QVBoxLayout();
        checkBoxesVerticalLayout->setObjectName(QStringLiteral("checkBoxesVerticalLayout"));
        candidateHepCCheckBox = new QCheckBox(widget);
        candidateHepCCheckBox->setObjectName(QStringLiteral("candidateHepCCheckBox"));
        candidateHepCCheckBox->setLayoutDirection(Qt::LeftToRight);

        checkBoxesVerticalLayout->addWidget(candidateHepCCheckBox);

        candidateDiabetesCheckBox = new QCheckBox(widget);
        candidateDiabetesCheckBox->setObjectName(QStringLiteral("candidateDiabetesCheckBox"));
        candidateDiabetesCheckBox->setLayoutDirection(Qt::LeftToRight);

        checkBoxesVerticalLayout->addWidget(candidateDiabetesCheckBox);

        candidatePrevTransCheckBox = new QCheckBox(widget);
        candidatePrevTransCheckBox->setObjectName(QStringLiteral("candidatePrevTransCheckBox"));
        candidatePrevTransCheckBox->setLayoutDirection(Qt::LeftToRight);

        checkBoxesVerticalLayout->addWidget(candidatePrevTransCheckBox);


        donorMinorInfoVerticalLayout->addLayout(checkBoxesVerticalLayout);

        verticalSpacer = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        donorMinorInfoVerticalLayout->addItem(verticalSpacer);


        donorMajorInfoHorizontalLayout->addLayout(donorMinorInfoVerticalLayout);


        donorCharacteristicsVerticalLayout->addLayout(donorMajorInfoHorizontalLayout);

        excludedDonorsHorizontalLayout = new QHBoxLayout();
        excludedDonorsHorizontalLayout->setObjectName(QStringLiteral("excludedDonorsHorizontalLayout"));
        exccludedDonorsLabel = new QLabel(widget);
        exccludedDonorsLabel->setObjectName(QStringLiteral("exccludedDonorsLabel"));

        excludedDonorsHorizontalLayout->addWidget(exccludedDonorsLabel);

        excludedDonorLineEdit = new QLineEdit(widget);
        excludedDonorLineEdit->setObjectName(QStringLiteral("excludedDonorLineEdit"));

        excludedDonorsHorizontalLayout->addWidget(excludedDonorLineEdit);


        donorCharacteristicsVerticalLayout->addLayout(excludedDonorsHorizontalLayout);

        moreRecipInfo->addTab(donorCharacteristicsTab, QString());

        candidateVerticalLayout->addWidget(moreRecipInfo);

        buttonBoxHorizontalLayout = new QHBoxLayout();
        buttonBoxHorizontalLayout->setObjectName(QStringLiteral("buttonBoxHorizontalLayout"));
        buttonHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonBoxHorizontalLayout->addItem(buttonHorizontalSpacer);

        buttonBox = new QDialogButtonBox(layoutWidget1);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        buttonBoxHorizontalLayout->addWidget(buttonBox);


        candidateVerticalLayout->addLayout(buttonBoxHorizontalLayout);


        retranslateUi(DialogCandidate);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogCandidate, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogCandidate, SLOT(reject()));
        QObject::connect(praSlider, SIGNAL(valueChanged(int)), candidatePRASpinBox, SLOT(setValue(int)));
        QObject::connect(candidatePRASpinBox, SIGNAL(valueChanged(int)), praSlider, SLOT(setValue(int)));

        moreRecipInfo->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogCandidate);
    } // setupUi

    void retranslateUi(QDialog *DialogCandidate)
    {
        DialogCandidate->setWindowTitle(QApplication::translate("DialogCandidate", "Add New Candidate", 0));
        candidateGroupBox->setTitle(QApplication::translate("DialogCandidate", "Candidate Information", 0));
        candidateBTLabel->setText(QApplication::translate("DialogCandidate", "Blood Type", 0));
        candidateNameLineEdit->setText(QApplication::translate("DialogCandidate", "Candidate Name", 0));
        candidateNameLineEdit->setPlaceholderText(QString());
        candidateNameLabel->setText(QApplication::translate("DialogCandidate", "Name", 0));
        candidateAgeLabel->setText(QApplication::translate("DialogCandidate", "Age", 0));
        candidateBTComboBox->clear();
        candidateBTComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogCandidate", "O", 0)
         << QApplication::translate("DialogCandidate", "A", 0)
         << QApplication::translate("DialogCandidate", "B", 0)
         << QApplication::translate("DialogCandidate", "AB", 0)
        );
        candidatePRALabel->setText(QApplication::translate("DialogCandidate", "PRA", 0));
        candidateAdditionalLabel->setText(QApplication::translate("DialogCandidate", "Candidate Antibodies", 0));
        candidateGenderComboBox->clear();
        candidateGenderComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogCandidate", "Male", 0)
         << QApplication::translate("DialogCandidate", "Female", 0)
        );
        candidateHeightLabel->setText(QApplication::translate("DialogCandidate", "Height (kg)", 0));
        candidateWeightLabel->setText(QApplication::translate("DialogCandidate", "Weight (kg)", 0));
        candidateRaceLabel->setText(QApplication::translate("DialogCandidate", "Race", 0));
        candidateRaceComboBox->clear();
        candidateRaceComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogCandidate", "White", 0)
         << QApplication::translate("DialogCandidate", "Black", 0)
         << QApplication::translate("DialogCandidate", "Hispanic", 0)
         << QApplication::translate("DialogCandidate", "Other", 0)
        );
        candidateGenderLabel->setText(QApplication::translate("DialogCandidate", "Gender", 0));
        candidateTODLabel->setText(QApplication::translate("DialogCandidate", "Months On Dialysis", 0));
        candidateHepCCheckBox->setText(QApplication::translate("DialogCandidate", "Hepatitis C", 0));
        candidateDiabetesCheckBox->setText(QApplication::translate("DialogCandidate", "Diabetes", 0));
        candidatePrevTransCheckBox->setText(QApplication::translate("DialogCandidate", "Previous Transplant ", 0));
        exccludedDonorsLabel->setText(QApplication::translate("DialogCandidate", "Excluded Donors", 0));
        moreRecipInfo->setTabText(moreRecipInfo->indexOf(donorCharacteristicsTab), QApplication::translate("DialogCandidate", "Candidate Characteristics", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogCandidate: public Ui_DialogCandidate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCANDIDATE_H
