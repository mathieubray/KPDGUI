/********************************************************************************
** Form generated from reading UI file 'DialogDonor.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDONOR_H
#define UI_DIALOGDONOR_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogDonor
{
public:
    QGroupBox *donorGroupBox;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *donorNameLabel;
    QLineEdit *donorNameLineEdit;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *donorStatusCheckBox;
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
    QLabel *label;
    QDoubleSpinBox *donorFailureProbabilitySpinBox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *donorHeightLabel;
    QDoubleSpinBox *donorHeightSpinBox;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QTabWidget *donorInfoTabWidget;
    QWidget *donorHLAInfoTab;
    QWidget *layoutWidget2;
    QVBoxLayout *donorHLAInfoVerticalLayout;
    QHBoxLayout *donorHLAInfoHorizontalLayout;
    QVBoxLayout *donorMajorHLAVerticalLayout;
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
    QSpacerItem *verticalSpacer;
    QVBoxLayout *donorHLAVerticalLayout;
    QGroupBox *donorHLADRLayout;
    QWidget *layoutWidget_5;
    QVBoxLayout *donorHLADRVerticalLayout;
    QCheckBox *donorDR51CheckBox;
    QCheckBox *donorDR52CheckBox;
    QCheckBox *donorDR53CheckBox;
    QGroupBox *donorHLABWLayout;
    QWidget *layoutWidget_6;
    QVBoxLayout *donorHLABWVerticalLayout;
    QCheckBox *donorBW4CheckBox;
    QCheckBox *donorBW6CheckBox;
    QHBoxLayout *donorHLAAdditionalHorizontalLayout;
    QLabel *donorHLAAdditionalLabel;
    QLineEdit *donorHLALineEdit;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogDonor)
    {
        if (DialogDonor->objectName().isEmpty())
            DialogDonor->setObjectName(QStringLiteral("DialogDonor"));
        DialogDonor->resize(411, 500);
        DialogDonor->setMinimumSize(QSize(411, 500));
        DialogDonor->setMaximumSize(QSize(411, 500));
        donorGroupBox = new QGroupBox(DialogDonor);
        donorGroupBox->setObjectName(QStringLiteral("donorGroupBox"));
        donorGroupBox->setGeometry(QRect(10, 10, 391, 141));
        layoutWidget = new QWidget(donorGroupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 371, 111));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        donorNameLabel = new QLabel(layoutWidget);
        donorNameLabel->setObjectName(QStringLiteral("donorNameLabel"));

        gridLayout->addWidget(donorNameLabel, 0, 0, 1, 1);

        donorNameLineEdit = new QLineEdit(layoutWidget);
        donorNameLineEdit->setObjectName(QStringLiteral("donorNameLineEdit"));

        gridLayout->addWidget(donorNameLineEdit, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        donorStatusCheckBox = new QCheckBox(layoutWidget);
        donorStatusCheckBox->setObjectName(QStringLiteral("donorStatusCheckBox"));
        donorStatusCheckBox->setLayoutDirection(Qt::RightToLeft);
        donorStatusCheckBox->setChecked(true);

        gridLayout->addWidget(donorStatusCheckBox, 0, 3, 1, 2);

        donorAgeLabel = new QLabel(layoutWidget);
        donorAgeLabel->setObjectName(QStringLiteral("donorAgeLabel"));

        gridLayout->addWidget(donorAgeLabel, 1, 0, 1, 1);

        donorAgeSpinBox = new QSpinBox(layoutWidget);
        donorAgeSpinBox->setObjectName(QStringLiteral("donorAgeSpinBox"));
        donorAgeSpinBox->setMaximum(130);
        donorAgeSpinBox->setValue(40);

        gridLayout->addWidget(donorAgeSpinBox, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        donorGenderLabel = new QLabel(layoutWidget);
        donorGenderLabel->setObjectName(QStringLiteral("donorGenderLabel"));

        gridLayout->addWidget(donorGenderLabel, 1, 3, 1, 1);

        donorGenderComboBox = new QComboBox(layoutWidget);
        donorGenderComboBox->setObjectName(QStringLiteral("donorGenderComboBox"));

        gridLayout->addWidget(donorGenderComboBox, 1, 4, 1, 1);

        donorBTLabel = new QLabel(layoutWidget);
        donorBTLabel->setObjectName(QStringLiteral("donorBTLabel"));

        gridLayout->addWidget(donorBTLabel, 2, 0, 1, 1);

        donorBTComboBox = new QComboBox(layoutWidget);
        donorBTComboBox->setObjectName(QStringLiteral("donorBTComboBox"));

        gridLayout->addWidget(donorBTComboBox, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        donorWeightLabel = new QLabel(layoutWidget);
        donorWeightLabel->setObjectName(QStringLiteral("donorWeightLabel"));

        gridLayout->addWidget(donorWeightLabel, 2, 3, 1, 1);

        donorWeightSpinBox = new QDoubleSpinBox(layoutWidget);
        donorWeightSpinBox->setObjectName(QStringLiteral("donorWeightSpinBox"));
        donorWeightSpinBox->setMaximum(400);
        donorWeightSpinBox->setValue(60);

        gridLayout->addWidget(donorWeightSpinBox, 2, 4, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        donorFailureProbabilitySpinBox = new QDoubleSpinBox(layoutWidget);
        donorFailureProbabilitySpinBox->setObjectName(QStringLiteral("donorFailureProbabilitySpinBox"));

        gridLayout->addWidget(donorFailureProbabilitySpinBox, 3, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 2, 1, 1);

        donorHeightLabel = new QLabel(layoutWidget);
        donorHeightLabel->setObjectName(QStringLiteral("donorHeightLabel"));

        gridLayout->addWidget(donorHeightLabel, 3, 3, 1, 1);

        donorHeightSpinBox = new QDoubleSpinBox(layoutWidget);
        donorHeightSpinBox->setObjectName(QStringLiteral("donorHeightSpinBox"));
        donorHeightSpinBox->setMaximum(3);
        donorHeightSpinBox->setValue(1.5);

        gridLayout->addWidget(donorHeightSpinBox, 3, 4, 1, 1);

        layoutWidget1 = new QWidget(DialogDonor);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 160, 391, 331));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        donorInfoTabWidget = new QTabWidget(layoutWidget1);
        donorInfoTabWidget->setObjectName(QStringLiteral("donorInfoTabWidget"));
        donorInfoTabWidget->setEnabled(true);
        donorHLAInfoTab = new QWidget();
        donorHLAInfoTab->setObjectName(QStringLiteral("donorHLAInfoTab"));
        layoutWidget2 = new QWidget(donorHLAInfoTab);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 10, 364, 251));
        donorHLAInfoVerticalLayout = new QVBoxLayout(layoutWidget2);
        donorHLAInfoVerticalLayout->setObjectName(QStringLiteral("donorHLAInfoVerticalLayout"));
        donorHLAInfoVerticalLayout->setContentsMargins(0, 0, 0, 0);
        donorHLAInfoHorizontalLayout = new QHBoxLayout();
        donorHLAInfoHorizontalLayout->setObjectName(QStringLiteral("donorHLAInfoHorizontalLayout"));
        donorMajorHLAVerticalLayout = new QVBoxLayout();
        donorMajorHLAVerticalLayout->setObjectName(QStringLiteral("donorMajorHLAVerticalLayout"));
        donorHLAGridLayout = new QGridLayout();
        donorHLAGridLayout->setObjectName(QStringLiteral("donorHLAGridLayout"));
        donorCWLabel = new QLabel(layoutWidget2);
        donorCWLabel->setObjectName(QStringLiteral("donorCWLabel"));

        donorHLAGridLayout->addWidget(donorCWLabel, 2, 0, 1, 1);

        donorALabel = new QLabel(layoutWidget2);
        donorALabel->setObjectName(QStringLiteral("donorALabel"));

        donorHLAGridLayout->addWidget(donorALabel, 0, 0, 1, 1);

        donorBLabel = new QLabel(layoutWidget2);
        donorBLabel->setObjectName(QStringLiteral("donorBLabel"));

        donorHLAGridLayout->addWidget(donorBLabel, 1, 0, 1, 1);

        donorDRLabel = new QLabel(layoutWidget2);
        donorDRLabel->setObjectName(QStringLiteral("donorDRLabel"));

        donorHLAGridLayout->addWidget(donorDRLabel, 4, 0, 1, 1);

        donorDQLabel = new QLabel(layoutWidget2);
        donorDQLabel->setObjectName(QStringLiteral("donorDQLabel"));

        donorHLAGridLayout->addWidget(donorDQLabel, 3, 0, 1, 1);

        donorHLAA1ComboBox = new QComboBox(layoutWidget2);
        donorHLAA1ComboBox->setObjectName(QStringLiteral("donorHLAA1ComboBox"));

        donorHLAGridLayout->addWidget(donorHLAA1ComboBox, 0, 1, 1, 1);

        donorHLAA2ComboBox = new QComboBox(layoutWidget2);
        donorHLAA2ComboBox->setObjectName(QStringLiteral("donorHLAA2ComboBox"));

        donorHLAGridLayout->addWidget(donorHLAA2ComboBox, 0, 2, 1, 1);

        donorHLACW2ComboBox = new QComboBox(layoutWidget2);
        donorHLACW2ComboBox->setObjectName(QStringLiteral("donorHLACW2ComboBox"));

        donorHLAGridLayout->addWidget(donorHLACW2ComboBox, 2, 2, 1, 1);

        donorHLAB1ComboBox = new QComboBox(layoutWidget2);
        donorHLAB1ComboBox->setObjectName(QStringLiteral("donorHLAB1ComboBox"));

        donorHLAGridLayout->addWidget(donorHLAB1ComboBox, 1, 1, 1, 1);

        donorHLACW1ComboBox = new QComboBox(layoutWidget2);
        donorHLACW1ComboBox->setObjectName(QStringLiteral("donorHLACW1ComboBox"));

        donorHLAGridLayout->addWidget(donorHLACW1ComboBox, 2, 1, 1, 1);

        donorHLAB2ComboBox = new QComboBox(layoutWidget2);
        donorHLAB2ComboBox->setObjectName(QStringLiteral("donorHLAB2ComboBox"));

        donorHLAGridLayout->addWidget(donorHLAB2ComboBox, 1, 2, 1, 1);

        donorHLADQ1ComboBox = new QComboBox(layoutWidget2);
        donorHLADQ1ComboBox->setObjectName(QStringLiteral("donorHLADQ1ComboBox"));

        donorHLAGridLayout->addWidget(donorHLADQ1ComboBox, 3, 1, 1, 1);

        donorHLADR1ComboBox = new QComboBox(layoutWidget2);
        donorHLADR1ComboBox->setObjectName(QStringLiteral("donorHLADR1ComboBox"));

        donorHLAGridLayout->addWidget(donorHLADR1ComboBox, 4, 1, 1, 1);

        donorHLADQ2ComboBox = new QComboBox(layoutWidget2);
        donorHLADQ2ComboBox->setObjectName(QStringLiteral("donorHLADQ2ComboBox"));

        donorHLAGridLayout->addWidget(donorHLADQ2ComboBox, 3, 2, 1, 1);

        donorHLADR2ComboBox = new QComboBox(layoutWidget2);
        donorHLADR2ComboBox->setObjectName(QStringLiteral("donorHLADR2ComboBox"));

        donorHLAGridLayout->addWidget(donorHLADR2ComboBox, 4, 2, 1, 1);


        donorMajorHLAVerticalLayout->addLayout(donorHLAGridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        donorMajorHLAVerticalLayout->addItem(verticalSpacer);


        donorHLAInfoHorizontalLayout->addLayout(donorMajorHLAVerticalLayout);

        donorHLAVerticalLayout = new QVBoxLayout();
        donorHLAVerticalLayout->setObjectName(QStringLiteral("donorHLAVerticalLayout"));
        donorHLADRLayout = new QGroupBox(layoutWidget2);
        donorHLADRLayout->setObjectName(QStringLiteral("donorHLADRLayout"));
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


        donorHLAVerticalLayout->addWidget(donorHLADRLayout);

        donorHLABWLayout = new QGroupBox(layoutWidget2);
        donorHLABWLayout->setObjectName(QStringLiteral("donorHLABWLayout"));
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


        donorHLAVerticalLayout->addWidget(donorHLABWLayout);


        donorHLAInfoHorizontalLayout->addLayout(donorHLAVerticalLayout);


        donorHLAInfoVerticalLayout->addLayout(donorHLAInfoHorizontalLayout);

        donorHLAAdditionalHorizontalLayout = new QHBoxLayout();
        donorHLAAdditionalHorizontalLayout->setObjectName(QStringLiteral("donorHLAAdditionalHorizontalLayout"));
        donorHLAAdditionalLabel = new QLabel(layoutWidget2);
        donorHLAAdditionalLabel->setObjectName(QStringLiteral("donorHLAAdditionalLabel"));

        donorHLAAdditionalHorizontalLayout->addWidget(donorHLAAdditionalLabel);

        donorHLALineEdit = new QLineEdit(layoutWidget2);
        donorHLALineEdit->setObjectName(QStringLiteral("donorHLALineEdit"));

        donorHLAAdditionalHorizontalLayout->addWidget(donorHLALineEdit);


        donorHLAInfoVerticalLayout->addLayout(donorHLAAdditionalHorizontalLayout);

        donorInfoTabWidget->addTab(donorHLAInfoTab, QString());

        verticalLayout->addWidget(donorInfoTabWidget);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
        buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonSpacer);

        buttonBox = new QDialogButtonBox(layoutWidget1);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        buttonLayout->addWidget(buttonBox);


        verticalLayout->addLayout(buttonLayout);


        retranslateUi(DialogDonor);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogDonor, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogDonor, SLOT(reject()));

        donorInfoTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogDonor);
    } // setupUi

    void retranslateUi(QDialog *DialogDonor)
    {
        DialogDonor->setWindowTitle(QApplication::translate("DialogDonor", "Add New Altruistic Donor", 0));
        donorGroupBox->setTitle(QApplication::translate("DialogDonor", "Donor Information", 0));
        donorNameLabel->setText(QApplication::translate("DialogDonor", "Name", 0));
        donorNameLineEdit->setText(QApplication::translate("DialogDonor", "Donor Name", 0));
        donorStatusCheckBox->setText(QApplication::translate("DialogDonor", "Include in Match Run", 0));
        donorAgeLabel->setText(QApplication::translate("DialogDonor", "Age", 0));
        donorGenderLabel->setText(QApplication::translate("DialogDonor", "Gender", 0));
        donorGenderComboBox->clear();
        donorGenderComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogDonor", "Male", 0)
         << QApplication::translate("DialogDonor", "Female", 0)
        );
        donorBTLabel->setText(QApplication::translate("DialogDonor", "Blood Type", 0));
        donorBTComboBox->clear();
        donorBTComboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogDonor", "O", 0)
         << QApplication::translate("DialogDonor", "A", 0)
         << QApplication::translate("DialogDonor", "B", 0)
         << QApplication::translate("DialogDonor", "AB", 0)
        );
        donorWeightLabel->setText(QApplication::translate("DialogDonor", "Weight (kg)", 0));
        label->setText(QApplication::translate("DialogDonor", "Failure Probability", 0));
        donorHeightLabel->setText(QApplication::translate("DialogDonor", "Height (m)", 0));
        donorCWLabel->setText(QApplication::translate("DialogDonor", "Donor HLA CW", 0));
        donorALabel->setText(QApplication::translate("DialogDonor", "Donor HLA A", 0));
        donorBLabel->setText(QApplication::translate("DialogDonor", "Donor HLA B", 0));
        donorDRLabel->setText(QApplication::translate("DialogDonor", "Donor HLA DR", 0));
        donorDQLabel->setText(QApplication::translate("DialogDonor", "Donor HLA DQ", 0));
        donorHLADRLayout->setTitle(QApplication::translate("DialogDonor", "Donor HLA DR", 0));
        donorDR51CheckBox->setText(QApplication::translate("DialogDonor", "DR51", 0));
        donorDR52CheckBox->setText(QApplication::translate("DialogDonor", "DR52", 0));
        donorDR53CheckBox->setText(QApplication::translate("DialogDonor", "DR53", 0));
        donorHLABWLayout->setTitle(QApplication::translate("DialogDonor", "Donor HLA BW", 0));
        donorBW4CheckBox->setText(QApplication::translate("DialogDonor", "BW4", 0));
        donorBW6CheckBox->setText(QApplication::translate("DialogDonor", "BW6", 0));
        donorHLAAdditionalLabel->setText(QApplication::translate("DialogDonor", "Additional Donor Antigens", 0));
        donorInfoTabWidget->setTabText(donorInfoTabWidget->indexOf(donorHLAInfoTab), QApplication::translate("DialogDonor", "HLA Information", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogDonor: public Ui_DialogDonor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDONOR_H
