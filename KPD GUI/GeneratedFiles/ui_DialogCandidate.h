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
    QVBoxLayout *candidateVerticalLayout;
    QTabWidget *moreRecipInfo;
    QWidget *donorCharacteristicsTab;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
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
    QCheckBox *candidateHepCCheckBox;
    QCheckBox *candidateDiabetesCheckBox;
    QCheckBox *candidatePrevTransCheckBox;
    QHBoxLayout *excludedDonorsHorizontalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *buttonBoxHorizontalLayout;
    QSpacerItem *buttonHorizontalSpacer;
    QDialogButtonBox *buttonBox;
    QGroupBox *candidateGroupBox;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QLabel *candidateNameLabel;
    QLineEdit *candidateNameLineEdit;
    QLabel *candidateAgeLabel;
    QSpinBox *candidateAgeSpinBox;
    QSpacerItem *candidateAgeSpacer;
    QLabel *candidateBTLabel;
    QComboBox *candidateBTComboBox;
    QSpacerItem *candidateBTSpacer;
    QLabel *candidatePRALabel;
    QSpinBox *candidatePRASpinBox;
    QSlider *praSlider;
    QLabel *candidateAdditionalLabel;
    QLabel *label;
    QComboBox *candidateInsuranceComboBox;
    QLabel *candidateFailureProbabilityLabel;
    QDoubleSpinBox *candidateFailureProbabilitySpinBox;
    QCheckBox *candidateStatusCheckBox;
    QLineEdit *candidateHLALineEdit;

    void setupUi(QDialog *DialogCandidate)
    {
        if (DialogCandidate->objectName().isEmpty())
            DialogCandidate->setObjectName(QStringLiteral("DialogCandidate"));
        DialogCandidate->resize(387, 588);
        DialogCandidate->setMinimumSize(QSize(387, 588));
        DialogCandidate->setMaximumSize(QSize(387, 588));
        layoutWidget = new QWidget(DialogCandidate);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 310, 371, 261));
        candidateVerticalLayout = new QVBoxLayout(layoutWidget);
        candidateVerticalLayout->setObjectName(QStringLiteral("candidateVerticalLayout"));
        candidateVerticalLayout->setContentsMargins(0, 0, 0, 0);
        moreRecipInfo = new QTabWidget(layoutWidget);
        moreRecipInfo->setObjectName(QStringLiteral("moreRecipInfo"));
        moreRecipInfo->setEnabled(true);
        donorCharacteristicsTab = new QWidget();
        donorCharacteristicsTab->setObjectName(QStringLiteral("donorCharacteristicsTab"));
        layoutWidget1 = new QWidget(donorCharacteristicsTab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(11, 12, 346, 173));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        candidateCharacteristicsGridLayout = new QGridLayout();
        candidateCharacteristicsGridLayout->setObjectName(QStringLiteral("candidateCharacteristicsGridLayout"));
        candidateGenderSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateCharacteristicsGridLayout->addItem(candidateGenderSpacer, 0, 1, 1, 1);

        candidateGenderComboBox = new QComboBox(layoutWidget1);
        candidateGenderComboBox->setObjectName(QStringLiteral("candidateGenderComboBox"));

        candidateCharacteristicsGridLayout->addWidget(candidateGenderComboBox, 0, 2, 1, 1);

        candidateWeightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateCharacteristicsGridLayout->addItem(candidateWeightSpacer, 3, 1, 1, 1);

        candidateHeightLabel = new QLabel(layoutWidget1);
        candidateHeightLabel->setObjectName(QStringLiteral("candidateHeightLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateHeightLabel, 4, 0, 1, 1);

        candidateWeightLabel = new QLabel(layoutWidget1);
        candidateWeightLabel->setObjectName(QStringLiteral("candidateWeightLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateWeightLabel, 3, 0, 1, 1);

        candidateHeightSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateCharacteristicsGridLayout->addItem(candidateHeightSpacer, 4, 1, 1, 1);

        candidateRaceLabel = new QLabel(layoutWidget1);
        candidateRaceLabel->setObjectName(QStringLiteral("candidateRaceLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateRaceLabel, 1, 0, 1, 1);

        candidateTODSpinBox = new QDoubleSpinBox(layoutWidget1);
        candidateTODSpinBox->setObjectName(QStringLiteral("candidateTODSpinBox"));
        candidateTODSpinBox->setMaximum(200);

        candidateCharacteristicsGridLayout->addWidget(candidateTODSpinBox, 2, 2, 1, 1);

        candidateRaceComboBox = new QComboBox(layoutWidget1);
        candidateRaceComboBox->setObjectName(QStringLiteral("candidateRaceComboBox"));

        candidateCharacteristicsGridLayout->addWidget(candidateRaceComboBox, 1, 2, 1, 1);

        candidateRaceSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        candidateCharacteristicsGridLayout->addItem(candidateRaceSpacer, 1, 1, 1, 1);

        candidateGenderLabel = new QLabel(layoutWidget1);
        candidateGenderLabel->setObjectName(QStringLiteral("candidateGenderLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateGenderLabel, 0, 0, 1, 1);

        candidateTODLabel = new QLabel(layoutWidget1);
        candidateTODLabel->setObjectName(QStringLiteral("candidateTODLabel"));

        candidateCharacteristicsGridLayout->addWidget(candidateTODLabel, 2, 0, 1, 2);

        candidateHeightSpinBox = new QDoubleSpinBox(layoutWidget1);
        candidateHeightSpinBox->setObjectName(QStringLiteral("candidateHeightSpinBox"));
        candidateHeightSpinBox->setMaximum(3);
        candidateHeightSpinBox->setValue(1.5);

        candidateCharacteristicsGridLayout->addWidget(candidateHeightSpinBox, 4, 2, 1, 1);

        candidateWeightSpinBox = new QDoubleSpinBox(layoutWidget1);
        candidateWeightSpinBox->setObjectName(QStringLiteral("candidateWeightSpinBox"));
        candidateWeightSpinBox->setMaximum(400);
        candidateWeightSpinBox->setValue(60);

        candidateCharacteristicsGridLayout->addWidget(candidateWeightSpinBox, 3, 2, 1, 1);


        gridLayout_2->addLayout(candidateCharacteristicsGridLayout, 0, 0, 4, 1);

        candidateHepCCheckBox = new QCheckBox(layoutWidget1);
        candidateHepCCheckBox->setObjectName(QStringLiteral("candidateHepCCheckBox"));
        candidateHepCCheckBox->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(candidateHepCCheckBox, 0, 1, 1, 2);

        candidateDiabetesCheckBox = new QCheckBox(layoutWidget1);
        candidateDiabetesCheckBox->setObjectName(QStringLiteral("candidateDiabetesCheckBox"));
        candidateDiabetesCheckBox->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(candidateDiabetesCheckBox, 1, 1, 1, 2);

        candidatePrevTransCheckBox = new QCheckBox(layoutWidget1);
        candidatePrevTransCheckBox->setObjectName(QStringLiteral("candidatePrevTransCheckBox"));
        candidatePrevTransCheckBox->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(candidatePrevTransCheckBox, 2, 1, 1, 2);

        excludedDonorsHorizontalLayout = new QHBoxLayout();
        excludedDonorsHorizontalLayout->setObjectName(QStringLiteral("excludedDonorsHorizontalLayout"));

        gridLayout_2->addLayout(excludedDonorsHorizontalLayout, 4, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 1, 1, 1);

        moreRecipInfo->addTab(donorCharacteristicsTab, QString());

        candidateVerticalLayout->addWidget(moreRecipInfo);

        buttonBoxHorizontalLayout = new QHBoxLayout();
        buttonBoxHorizontalLayout->setObjectName(QStringLiteral("buttonBoxHorizontalLayout"));
        buttonHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonBoxHorizontalLayout->addItem(buttonHorizontalSpacer);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        buttonBoxHorizontalLayout->addWidget(buttonBox);


        candidateVerticalLayout->addLayout(buttonBoxHorizontalLayout);

        candidateGroupBox = new QGroupBox(DialogCandidate);
        candidateGroupBox->setObjectName(QStringLiteral("candidateGroupBox"));
        candidateGroupBox->setGeometry(QRect(10, 10, 371, 291));
        layoutWidget2 = new QWidget(candidateGroupBox);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 22, 351, 263));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        candidateNameLabel = new QLabel(layoutWidget2);
        candidateNameLabel->setObjectName(QStringLiteral("candidateNameLabel"));

        gridLayout->addWidget(candidateNameLabel, 0, 0, 1, 1);

        candidateNameLineEdit = new QLineEdit(layoutWidget2);
        candidateNameLineEdit->setObjectName(QStringLiteral("candidateNameLineEdit"));

        gridLayout->addWidget(candidateNameLineEdit, 0, 2, 1, 3);

        candidateAgeLabel = new QLabel(layoutWidget2);
        candidateAgeLabel->setObjectName(QStringLiteral("candidateAgeLabel"));

        gridLayout->addWidget(candidateAgeLabel, 1, 0, 1, 1);

        candidateAgeSpinBox = new QSpinBox(layoutWidget2);
        candidateAgeSpinBox->setObjectName(QStringLiteral("candidateAgeSpinBox"));
        candidateAgeSpinBox->setMaximum(130);
        candidateAgeSpinBox->setValue(40);

        gridLayout->addWidget(candidateAgeSpinBox, 1, 2, 1, 2);

        candidateAgeSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(candidateAgeSpacer, 1, 4, 1, 1);

        candidateBTLabel = new QLabel(layoutWidget2);
        candidateBTLabel->setObjectName(QStringLiteral("candidateBTLabel"));

        gridLayout->addWidget(candidateBTLabel, 2, 0, 1, 1);

        candidateBTComboBox = new QComboBox(layoutWidget2);
        candidateBTComboBox->setObjectName(QStringLiteral("candidateBTComboBox"));

        gridLayout->addWidget(candidateBTComboBox, 2, 2, 1, 2);

        candidateBTSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(candidateBTSpacer, 2, 4, 1, 1);

        candidatePRALabel = new QLabel(layoutWidget2);
        candidatePRALabel->setObjectName(QStringLiteral("candidatePRALabel"));

        gridLayout->addWidget(candidatePRALabel, 3, 0, 1, 1);

        candidatePRASpinBox = new QSpinBox(layoutWidget2);
        candidatePRASpinBox->setObjectName(QStringLiteral("candidatePRASpinBox"));
        candidatePRASpinBox->setMaximum(100);

        gridLayout->addWidget(candidatePRASpinBox, 3, 2, 1, 2);

        praSlider = new QSlider(layoutWidget2);
        praSlider->setObjectName(QStringLiteral("praSlider"));
        praSlider->setMaximum(100);
        praSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(praSlider, 3, 4, 1, 1);

        candidateAdditionalLabel = new QLabel(layoutWidget2);
        candidateAdditionalLabel->setObjectName(QStringLiteral("candidateAdditionalLabel"));

        gridLayout->addWidget(candidateAdditionalLabel, 4, 0, 1, 2);

        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 5, 0, 1, 1);

        candidateInsuranceComboBox = new QComboBox(layoutWidget2);
        candidateInsuranceComboBox->setObjectName(QStringLiteral("candidateInsuranceComboBox"));

        gridLayout->addWidget(candidateInsuranceComboBox, 5, 2, 1, 3);

        candidateFailureProbabilityLabel = new QLabel(layoutWidget2);
        candidateFailureProbabilityLabel->setObjectName(QStringLiteral("candidateFailureProbabilityLabel"));

        gridLayout->addWidget(candidateFailureProbabilityLabel, 6, 0, 1, 1);

        candidateFailureProbabilitySpinBox = new QDoubleSpinBox(layoutWidget2);
        candidateFailureProbabilitySpinBox->setObjectName(QStringLiteral("candidateFailureProbabilitySpinBox"));
        candidateFailureProbabilitySpinBox->setMaximum(1);
        candidateFailureProbabilitySpinBox->setSingleStep(0.1);
        candidateFailureProbabilitySpinBox->setValue(0.1);

        gridLayout->addWidget(candidateFailureProbabilitySpinBox, 6, 1, 1, 2);

        candidateStatusCheckBox = new QCheckBox(layoutWidget2);
        candidateStatusCheckBox->setObjectName(QStringLiteral("candidateStatusCheckBox"));
        candidateStatusCheckBox->setLayoutDirection(Qt::RightToLeft);
        candidateStatusCheckBox->setChecked(true);

        gridLayout->addWidget(candidateStatusCheckBox, 6, 3, 1, 2);

        candidateHLALineEdit = new QLineEdit(layoutWidget2);
        candidateHLALineEdit->setObjectName(QStringLiteral("candidateHLALineEdit"));

        gridLayout->addWidget(candidateHLALineEdit, 4, 2, 1, 3);


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
        candidateGenderComboBox->clear();
        candidateGenderComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogCandidate", "Male", 0)
         << QApplication::translate("DialogCandidate", "Female", 0)
        );
        candidateHeightLabel->setText(QApplication::translate("DialogCandidate", "Height (m)", 0));
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
        moreRecipInfo->setTabText(moreRecipInfo->indexOf(donorCharacteristicsTab), QApplication::translate("DialogCandidate", "Candidate Characteristics", 0));
        candidateGroupBox->setTitle(QApplication::translate("DialogCandidate", "Candidate Information", 0));
        candidateNameLabel->setText(QApplication::translate("DialogCandidate", "Name", 0));
        candidateNameLineEdit->setText(QApplication::translate("DialogCandidate", "Candidate Name", 0));
        candidateNameLineEdit->setPlaceholderText(QString());
        candidateAgeLabel->setText(QApplication::translate("DialogCandidate", "Age", 0));
        candidateBTLabel->setText(QApplication::translate("DialogCandidate", "Blood Type", 0));
        candidateBTComboBox->clear();
        candidateBTComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogCandidate", "O", 0)
         << QApplication::translate("DialogCandidate", "A", 0)
         << QApplication::translate("DialogCandidate", "B", 0)
         << QApplication::translate("DialogCandidate", "AB", 0)
        );
        candidatePRALabel->setText(QApplication::translate("DialogCandidate", "PRA", 0));
        candidateAdditionalLabel->setText(QApplication::translate("DialogCandidate", "Candidate Antibodies", 0));
        label->setText(QApplication::translate("DialogCandidate", "Insurance", 0));
        candidateInsuranceComboBox->clear();
        candidateInsuranceComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogCandidate", "Public Primary Payer", 0)
         << QApplication::translate("DialogCandidate", "Private Primary Payer", 0)
         << QApplication::translate("DialogCandidate", "Other", 0)
        );
        candidateFailureProbabilityLabel->setText(QApplication::translate("DialogCandidate", "Failure Probability", 0));
        candidateStatusCheckBox->setText(QApplication::translate("DialogCandidate", "Include in Match Runs", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogCandidate: public Ui_DialogCandidate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCANDIDATE_H
