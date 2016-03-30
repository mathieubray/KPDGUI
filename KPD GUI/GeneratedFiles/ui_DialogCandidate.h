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
    QGroupBox *recipGroupBox;
    QWidget *layoutWidget_3;
    QGridLayout *recipGridLayout;
    QLabel *recipBTLabel;
    QSpinBox *recipAgeSpinBox;
    QLineEdit *recipNameLineEdit;
    QLabel *recipNameLabel;
    QLabel *recipAgeLabel;
    QSpacerItem *recipAgeSpacer;
    QComboBox *recipBTComboBox;
    QSpacerItem *recipBTSpacer;
    QLabel *recipPRALabel;
    QSpinBox *recipPRASpinBox;
    QSlider *praSlider;
    QHBoxLayout *recipAdditionalHorizontalLayout_3;
    QLabel *recipAdditionalLayout_3;
    QLineEdit *recipHLALineEdit;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QTabWidget *moreRecipInfo;
    QWidget *donorCharacteristicsTab;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_3;
    QLineEdit *excludedDonorLineEdit;
    QWidget *layoutWidget_5;
    QGridLayout *recipCharacteristicsGridLayout_3;
    QSpacerItem *recipGenderSpacer_3;
    QComboBox *recipGenderComboBox;
    QSpacerItem *recipWeightSpacer_3;
    QLabel *recipHeightLabel_3;
    QLabel *recipWeightLabel_3;
    QSpacerItem *recipHeightSpacer_3;
    QLabel *recipRaceLabel_3;
    QDoubleSpinBox *recipTODSpinBox;
    QComboBox *recipRaceComboBox;
    QSpacerItem *recipRaceSpacer_3;
    QLabel *recipGenderLabel_3;
    QLabel *recipTODLabel_3;
    QDoubleSpinBox *recipHeightSpinBox;
    QDoubleSpinBox *recipWeightSpinBox;
    QWidget *layoutWidget_2;
    QVBoxLayout *recipVerticalLayout_3;
    QCheckBox *recipHepCCheckBox;
    QCheckBox *recipDiabetesCheckBox;
    QCheckBox *recipPrevTransCheckBox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *buttonHorizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogCandidate)
    {
        if (DialogCandidate->objectName().isEmpty())
            DialogCandidate->setObjectName(QStringLiteral("DialogCandidate"));
        DialogCandidate->resize(376, 427);
        DialogCandidate->setMinimumSize(QSize(376, 427));
        DialogCandidate->setMaximumSize(QSize(376, 427));
        layoutWidget = new QWidget(DialogCandidate);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 361, 171));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        recipGroupBox = new QGroupBox(layoutWidget);
        recipGroupBox->setObjectName(QStringLiteral("recipGroupBox"));
        layoutWidget_3 = new QWidget(recipGroupBox);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 30, 341, 128));
        recipGridLayout = new QGridLayout(layoutWidget_3);
        recipGridLayout->setObjectName(QStringLiteral("recipGridLayout"));
        recipGridLayout->setContentsMargins(0, 0, 0, 0);
        recipBTLabel = new QLabel(layoutWidget_3);
        recipBTLabel->setObjectName(QStringLiteral("recipBTLabel"));

        recipGridLayout->addWidget(recipBTLabel, 2, 0, 1, 1);

        recipAgeSpinBox = new QSpinBox(layoutWidget_3);
        recipAgeSpinBox->setObjectName(QStringLiteral("recipAgeSpinBox"));
        recipAgeSpinBox->setMaximum(130);
        recipAgeSpinBox->setValue(40);

        recipGridLayout->addWidget(recipAgeSpinBox, 1, 1, 1, 1);

        recipNameLineEdit = new QLineEdit(layoutWidget_3);
        recipNameLineEdit->setObjectName(QStringLiteral("recipNameLineEdit"));

        recipGridLayout->addWidget(recipNameLineEdit, 0, 1, 1, 2);

        recipNameLabel = new QLabel(layoutWidget_3);
        recipNameLabel->setObjectName(QStringLiteral("recipNameLabel"));

        recipGridLayout->addWidget(recipNameLabel, 0, 0, 1, 1);

        recipAgeLabel = new QLabel(layoutWidget_3);
        recipAgeLabel->setObjectName(QStringLiteral("recipAgeLabel"));

        recipGridLayout->addWidget(recipAgeLabel, 1, 0, 1, 1);

        recipAgeSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipGridLayout->addItem(recipAgeSpacer, 1, 2, 1, 1);

        recipBTComboBox = new QComboBox(layoutWidget_3);
        recipBTComboBox->setObjectName(QStringLiteral("recipBTComboBox"));

        recipGridLayout->addWidget(recipBTComboBox, 2, 1, 1, 1);

        recipBTSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipGridLayout->addItem(recipBTSpacer, 2, 2, 1, 1);

        recipPRALabel = new QLabel(layoutWidget_3);
        recipPRALabel->setObjectName(QStringLiteral("recipPRALabel"));

        recipGridLayout->addWidget(recipPRALabel, 3, 0, 1, 1);

        recipPRASpinBox = new QSpinBox(layoutWidget_3);
        recipPRASpinBox->setObjectName(QStringLiteral("recipPRASpinBox"));
        recipPRASpinBox->setMaximum(100);

        recipGridLayout->addWidget(recipPRASpinBox, 3, 1, 1, 1);

        praSlider = new QSlider(layoutWidget_3);
        praSlider->setObjectName(QStringLiteral("praSlider"));
        praSlider->setMaximum(100);
        praSlider->setOrientation(Qt::Horizontal);

        recipGridLayout->addWidget(praSlider, 3, 2, 1, 1);

        recipAdditionalHorizontalLayout_3 = new QHBoxLayout();
        recipAdditionalHorizontalLayout_3->setObjectName(QStringLiteral("recipAdditionalHorizontalLayout_3"));
        recipAdditionalLayout_3 = new QLabel(layoutWidget_3);
        recipAdditionalLayout_3->setObjectName(QStringLiteral("recipAdditionalLayout_3"));

        recipAdditionalHorizontalLayout_3->addWidget(recipAdditionalLayout_3);


        recipGridLayout->addLayout(recipAdditionalHorizontalLayout_3, 4, 0, 1, 1);

        recipHLALineEdit = new QLineEdit(layoutWidget_3);
        recipHLALineEdit->setObjectName(QStringLiteral("recipHLALineEdit"));

        recipGridLayout->addWidget(recipHLALineEdit, 4, 1, 1, 2);


        horizontalLayout->addWidget(recipGroupBox);

        layoutWidget1 = new QWidget(DialogCandidate);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 190, 361, 231));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        moreRecipInfo = new QTabWidget(layoutWidget1);
        moreRecipInfo->setObjectName(QStringLiteral("moreRecipInfo"));
        moreRecipInfo->setEnabled(true);
        donorCharacteristicsTab = new QWidget();
        donorCharacteristicsTab->setObjectName(QStringLiteral("donorCharacteristicsTab"));
        layoutWidget_6 = new QWidget(donorCharacteristicsTab);
        layoutWidget_6->setObjectName(QStringLiteral("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(10, 140, 341, 22));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget_6);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_8->addWidget(label_3);

        excludedDonorLineEdit = new QLineEdit(layoutWidget_6);
        excludedDonorLineEdit->setObjectName(QStringLiteral("excludedDonorLineEdit"));

        horizontalLayout_8->addWidget(excludedDonorLineEdit);

        layoutWidget_5 = new QWidget(donorCharacteristicsTab);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(10, 10, 167, 126));
        recipCharacteristicsGridLayout_3 = new QGridLayout(layoutWidget_5);
        recipCharacteristicsGridLayout_3->setObjectName(QStringLiteral("recipCharacteristicsGridLayout_3"));
        recipCharacteristicsGridLayout_3->setContentsMargins(0, 0, 0, 0);
        recipGenderSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipCharacteristicsGridLayout_3->addItem(recipGenderSpacer_3, 0, 1, 1, 1);

        recipGenderComboBox = new QComboBox(layoutWidget_5);
        recipGenderComboBox->setObjectName(QStringLiteral("recipGenderComboBox"));

        recipCharacteristicsGridLayout_3->addWidget(recipGenderComboBox, 0, 2, 1, 1);

        recipWeightSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipCharacteristicsGridLayout_3->addItem(recipWeightSpacer_3, 3, 1, 1, 1);

        recipHeightLabel_3 = new QLabel(layoutWidget_5);
        recipHeightLabel_3->setObjectName(QStringLiteral("recipHeightLabel_3"));

        recipCharacteristicsGridLayout_3->addWidget(recipHeightLabel_3, 4, 0, 1, 1);

        recipWeightLabel_3 = new QLabel(layoutWidget_5);
        recipWeightLabel_3->setObjectName(QStringLiteral("recipWeightLabel_3"));

        recipCharacteristicsGridLayout_3->addWidget(recipWeightLabel_3, 3, 0, 1, 1);

        recipHeightSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipCharacteristicsGridLayout_3->addItem(recipHeightSpacer_3, 4, 1, 1, 1);

        recipRaceLabel_3 = new QLabel(layoutWidget_5);
        recipRaceLabel_3->setObjectName(QStringLiteral("recipRaceLabel_3"));

        recipCharacteristicsGridLayout_3->addWidget(recipRaceLabel_3, 1, 0, 1, 1);

        recipTODSpinBox = new QDoubleSpinBox(layoutWidget_5);
        recipTODSpinBox->setObjectName(QStringLiteral("recipTODSpinBox"));
        recipTODSpinBox->setMaximum(200);

        recipCharacteristicsGridLayout_3->addWidget(recipTODSpinBox, 2, 2, 1, 1);

        recipRaceComboBox = new QComboBox(layoutWidget_5);
        recipRaceComboBox->setObjectName(QStringLiteral("recipRaceComboBox"));

        recipCharacteristicsGridLayout_3->addWidget(recipRaceComboBox, 1, 2, 1, 1);

        recipRaceSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        recipCharacteristicsGridLayout_3->addItem(recipRaceSpacer_3, 1, 1, 1, 1);

        recipGenderLabel_3 = new QLabel(layoutWidget_5);
        recipGenderLabel_3->setObjectName(QStringLiteral("recipGenderLabel_3"));

        recipCharacteristicsGridLayout_3->addWidget(recipGenderLabel_3, 0, 0, 1, 1);

        recipTODLabel_3 = new QLabel(layoutWidget_5);
        recipTODLabel_3->setObjectName(QStringLiteral("recipTODLabel_3"));

        recipCharacteristicsGridLayout_3->addWidget(recipTODLabel_3, 2, 0, 1, 2);

        recipHeightSpinBox = new QDoubleSpinBox(layoutWidget_5);
        recipHeightSpinBox->setObjectName(QStringLiteral("recipHeightSpinBox"));
        recipHeightSpinBox->setMaximum(3);
        recipHeightSpinBox->setValue(1.5);

        recipCharacteristicsGridLayout_3->addWidget(recipHeightSpinBox, 4, 2, 1, 1);

        recipWeightSpinBox = new QDoubleSpinBox(layoutWidget_5);
        recipWeightSpinBox->setObjectName(QStringLiteral("recipWeightSpinBox"));
        recipWeightSpinBox->setMaximum(400);
        recipWeightSpinBox->setValue(60);

        recipCharacteristicsGridLayout_3->addWidget(recipWeightSpinBox, 3, 2, 1, 1);

        layoutWidget_2 = new QWidget(donorCharacteristicsTab);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(190, 10, 122, 88));
        recipVerticalLayout_3 = new QVBoxLayout(layoutWidget_2);
        recipVerticalLayout_3->setObjectName(QStringLiteral("recipVerticalLayout_3"));
        recipVerticalLayout_3->setContentsMargins(0, 0, 0, 0);
        recipHepCCheckBox = new QCheckBox(layoutWidget_2);
        recipHepCCheckBox->setObjectName(QStringLiteral("recipHepCCheckBox"));
        recipHepCCheckBox->setLayoutDirection(Qt::LeftToRight);

        recipVerticalLayout_3->addWidget(recipHepCCheckBox);

        recipDiabetesCheckBox = new QCheckBox(layoutWidget_2);
        recipDiabetesCheckBox->setObjectName(QStringLiteral("recipDiabetesCheckBox"));
        recipDiabetesCheckBox->setLayoutDirection(Qt::LeftToRight);

        recipVerticalLayout_3->addWidget(recipDiabetesCheckBox);

        recipPrevTransCheckBox = new QCheckBox(layoutWidget_2);
        recipPrevTransCheckBox->setObjectName(QStringLiteral("recipPrevTransCheckBox"));
        recipPrevTransCheckBox->setLayoutDirection(Qt::LeftToRight);

        recipVerticalLayout_3->addWidget(recipPrevTransCheckBox);

        moreRecipInfo->addTab(donorCharacteristicsTab, QString());

        verticalLayout->addWidget(moreRecipInfo);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        buttonHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(buttonHorizontalSpacer);

        buttonBox = new QDialogButtonBox(layoutWidget1);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(DialogCandidate);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogCandidate, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogCandidate, SLOT(reject()));
        QObject::connect(praSlider, SIGNAL(valueChanged(int)), recipPRASpinBox, SLOT(setValue(int)));
        QObject::connect(recipPRASpinBox, SIGNAL(valueChanged(int)), praSlider, SLOT(setValue(int)));

        moreRecipInfo->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogCandidate);
    } // setupUi

    void retranslateUi(QDialog *DialogCandidate)
    {
        DialogCandidate->setWindowTitle(QApplication::translate("DialogCandidate", "Add New Candidate", 0));
        recipGroupBox->setTitle(QApplication::translate("DialogCandidate", "Candidate Information", 0));
        recipBTLabel->setText(QApplication::translate("DialogCandidate", "Blood Type", 0));
        recipNameLineEdit->setText(QApplication::translate("DialogCandidate", "Candidate Name", 0));
        recipNameLineEdit->setPlaceholderText(QString());
        recipNameLabel->setText(QApplication::translate("DialogCandidate", "Name", 0));
        recipAgeLabel->setText(QApplication::translate("DialogCandidate", "Age", 0));
        recipBTComboBox->clear();
        recipBTComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogCandidate", "O", 0)
         << QApplication::translate("DialogCandidate", "A", 0)
         << QApplication::translate("DialogCandidate", "B", 0)
         << QApplication::translate("DialogCandidate", "AB", 0)
        );
        recipPRALabel->setText(QApplication::translate("DialogCandidate", "PRA", 0));
        recipAdditionalLayout_3->setText(QApplication::translate("DialogCandidate", "Candidate Antibodies", 0));
        label_3->setText(QApplication::translate("DialogCandidate", "Excluded Donors", 0));
        recipGenderComboBox->clear();
        recipGenderComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogCandidate", "Male", 0)
         << QApplication::translate("DialogCandidate", "Female", 0)
        );
        recipHeightLabel_3->setText(QApplication::translate("DialogCandidate", "Height (kg)", 0));
        recipWeightLabel_3->setText(QApplication::translate("DialogCandidate", "Weight (kg)", 0));
        recipRaceLabel_3->setText(QApplication::translate("DialogCandidate", "Race", 0));
        recipRaceComboBox->clear();
        recipRaceComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogCandidate", "White", 0)
         << QApplication::translate("DialogCandidate", "Black", 0)
         << QApplication::translate("DialogCandidate", "Hispanic", 0)
         << QApplication::translate("DialogCandidate", "Other", 0)
        );
        recipGenderLabel_3->setText(QApplication::translate("DialogCandidate", "Gender", 0));
        recipTODLabel_3->setText(QApplication::translate("DialogCandidate", "Months On Dialysis", 0));
        recipHepCCheckBox->setText(QApplication::translate("DialogCandidate", "Hepatitis C", 0));
        recipDiabetesCheckBox->setText(QApplication::translate("DialogCandidate", "Diabetes", 0));
        recipPrevTransCheckBox->setText(QApplication::translate("DialogCandidate", "Previous Transplant ", 0));
        moreRecipInfo->setTabText(moreRecipInfo->indexOf(donorCharacteristicsTab), QApplication::translate("DialogCandidate", "Candidate Characteristics", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogCandidate: public Ui_DialogCandidate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCANDIDATE_H
