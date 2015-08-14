/********************************************************************************
** Form generated from reading UI file 'AltruisticDonorDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALTRUISTICDONORDIALOG_H
#define UI_ALTRUISTICDONORDIALOG_H

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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AltruisticDonorDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *donorGroupBox;
    QWidget *layoutWidget;
    QGridLayout *donorGridLayout;
    QLabel *donorNameLabel;
    QLineEdit *donorNameLineEdit;
    QLabel *donorAgeLabel;
    QLabel *donorBTLabel;
    QSpinBox *donorAgeSpinBox;
    QSpacerItem *donorAgeSpacer;
    QSpacerItem *donorBTSpacer;
    QComboBox *donorBTComboBox;
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
    QWidget *hlaInfoTab;
    QWidget *layoutWidget_7;
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
    QWidget *layoutWidget_9;
    QHBoxLayout *horizontalLayout;
    QLabel *donorHLAAdditionalLabel;
    QLineEdit *donorHLALineEdit;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
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
    QWidget *commentTab;
    QTextEdit *commentTextEdit;

    void setupUi(QDialog *AltruisticDonorDialog)
    {
        if (AltruisticDonorDialog->objectName().isEmpty())
            AltruisticDonorDialog->setObjectName(QStringLiteral("AltruisticDonorDialog"));
        AltruisticDonorDialog->resize(346, 436);
        AltruisticDonorDialog->setMinimumSize(QSize(346, 436));
        AltruisticDonorDialog->setMaximumSize(QSize(346, 436));
        buttonBox = new QDialogButtonBox(AltruisticDonorDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(220, 20, 81, 101));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        donorGroupBox = new QGroupBox(AltruisticDonorDialog);
        donorGroupBox->setObjectName(QStringLiteral("donorGroupBox"));
        donorGroupBox->setGeometry(QRect(10, 10, 192, 139));
        layoutWidget = new QWidget(donorGroupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 161, 74));
        donorGridLayout = new QGridLayout(layoutWidget);
        donorGridLayout->setObjectName(QStringLiteral("donorGridLayout"));
        donorGridLayout->setContentsMargins(0, 0, 0, 0);
        donorNameLabel = new QLabel(layoutWidget);
        donorNameLabel->setObjectName(QStringLiteral("donorNameLabel"));

        donorGridLayout->addWidget(donorNameLabel, 0, 0, 1, 1);

        donorNameLineEdit = new QLineEdit(layoutWidget);
        donorNameLineEdit->setObjectName(QStringLiteral("donorNameLineEdit"));

        donorGridLayout->addWidget(donorNameLineEdit, 0, 1, 1, 2);

        donorAgeLabel = new QLabel(layoutWidget);
        donorAgeLabel->setObjectName(QStringLiteral("donorAgeLabel"));

        donorGridLayout->addWidget(donorAgeLabel, 1, 0, 1, 1);

        donorBTLabel = new QLabel(layoutWidget);
        donorBTLabel->setObjectName(QStringLiteral("donorBTLabel"));

        donorGridLayout->addWidget(donorBTLabel, 2, 0, 1, 1);

        donorAgeSpinBox = new QSpinBox(layoutWidget);
        donorAgeSpinBox->setObjectName(QStringLiteral("donorAgeSpinBox"));
        donorAgeSpinBox->setMaximum(130);
        donorAgeSpinBox->setValue(40);

        donorGridLayout->addWidget(donorAgeSpinBox, 1, 1, 1, 1);

        donorAgeSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        donorGridLayout->addItem(donorAgeSpacer, 1, 2, 1, 1);

        donorBTSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        donorGridLayout->addItem(donorBTSpacer, 2, 2, 1, 1);

        donorBTComboBox = new QComboBox(layoutWidget);
        donorBTComboBox->setObjectName(QStringLiteral("donorBTComboBox"));

        donorGridLayout->addWidget(donorBTComboBox, 2, 1, 1, 1);

        morePairInfo = new QTabWidget(AltruisticDonorDialog);
        morePairInfo->setObjectName(QStringLiteral("morePairInfo"));
        morePairInfo->setEnabled(true);
        morePairInfo->setGeometry(QRect(10, 160, 321, 261));
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
        donorWeightSpinBox->setValue(100);

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
        hlaInfoTab = new QWidget();
        hlaInfoTab->setObjectName(QStringLiteral("hlaInfoTab"));
        layoutWidget_7 = new QWidget(hlaInfoTab);
        layoutWidget_7->setObjectName(QStringLiteral("layoutWidget_7"));
        layoutWidget_7->setGeometry(QRect(10, 10, 191, 152));
        donorHLAGridLayout = new QGridLayout(layoutWidget_7);
        donorHLAGridLayout->setObjectName(QStringLiteral("donorHLAGridLayout"));
        donorHLAGridLayout->setContentsMargins(0, 0, 0, 0);
        donorALabel = new QLabel(layoutWidget_7);
        donorALabel->setObjectName(QStringLiteral("donorALabel"));

        donorHLAGridLayout->addWidget(donorALabel, 0, 0, 1, 1);

        donorA1LineEdit = new QLineEdit(layoutWidget_7);
        donorA1LineEdit->setObjectName(QStringLiteral("donorA1LineEdit"));

        donorHLAGridLayout->addWidget(donorA1LineEdit, 0, 1, 1, 1);

        donorA2LineEdit = new QLineEdit(layoutWidget_7);
        donorA2LineEdit->setObjectName(QStringLiteral("donorA2LineEdit"));

        donorHLAGridLayout->addWidget(donorA2LineEdit, 0, 2, 1, 1);

        donorBLineEdit = new QLabel(layoutWidget_7);
        donorBLineEdit->setObjectName(QStringLiteral("donorBLineEdit"));

        donorHLAGridLayout->addWidget(donorBLineEdit, 1, 0, 1, 1);

        donorB1lineEdit = new QLineEdit(layoutWidget_7);
        donorB1lineEdit->setObjectName(QStringLiteral("donorB1lineEdit"));

        donorHLAGridLayout->addWidget(donorB1lineEdit, 1, 1, 1, 1);

        donorB2LineEdit = new QLineEdit(layoutWidget_7);
        donorB2LineEdit->setObjectName(QStringLiteral("donorB2LineEdit"));

        donorHLAGridLayout->addWidget(donorB2LineEdit, 1, 2, 1, 1);

        donorCWLineEdit = new QLabel(layoutWidget_7);
        donorCWLineEdit->setObjectName(QStringLiteral("donorCWLineEdit"));

        donorHLAGridLayout->addWidget(donorCWLineEdit, 2, 0, 1, 1);

        donorCW1LineEdit = new QLineEdit(layoutWidget_7);
        donorCW1LineEdit->setObjectName(QStringLiteral("donorCW1LineEdit"));

        donorHLAGridLayout->addWidget(donorCW1LineEdit, 2, 1, 1, 1);

        donorCW2LineEdit = new QLineEdit(layoutWidget_7);
        donorCW2LineEdit->setObjectName(QStringLiteral("donorCW2LineEdit"));

        donorHLAGridLayout->addWidget(donorCW2LineEdit, 2, 2, 1, 1);

        donorDPLabel = new QLabel(layoutWidget_7);
        donorDPLabel->setObjectName(QStringLiteral("donorDPLabel"));

        donorHLAGridLayout->addWidget(donorDPLabel, 3, 0, 1, 1);

        donorDP1LineEdit = new QLineEdit(layoutWidget_7);
        donorDP1LineEdit->setObjectName(QStringLiteral("donorDP1LineEdit"));

        donorHLAGridLayout->addWidget(donorDP1LineEdit, 3, 1, 1, 1);

        donorDP2LineEdit = new QLineEdit(layoutWidget_7);
        donorDP2LineEdit->setObjectName(QStringLiteral("donorDP2LineEdit"));

        donorHLAGridLayout->addWidget(donorDP2LineEdit, 3, 2, 1, 1);

        donorDQLabel = new QLabel(layoutWidget_7);
        donorDQLabel->setObjectName(QStringLiteral("donorDQLabel"));

        donorHLAGridLayout->addWidget(donorDQLabel, 4, 0, 1, 1);

        donorDQ1LineEdit = new QLineEdit(layoutWidget_7);
        donorDQ1LineEdit->setObjectName(QStringLiteral("donorDQ1LineEdit"));

        donorHLAGridLayout->addWidget(donorDQ1LineEdit, 4, 1, 1, 1);

        donorDQ2LineEdit = new QLineEdit(layoutWidget_7);
        donorDQ2LineEdit->setObjectName(QStringLiteral("donorDQ2LineEdit"));

        donorHLAGridLayout->addWidget(donorDQ2LineEdit, 4, 2, 1, 1);

        donorDRLabel = new QLabel(layoutWidget_7);
        donorDRLabel->setObjectName(QStringLiteral("donorDRLabel"));

        donorHLAGridLayout->addWidget(donorDRLabel, 5, 0, 1, 1);

        donorDR1LineEdit = new QLineEdit(layoutWidget_7);
        donorDR1LineEdit->setObjectName(QStringLiteral("donorDR1LineEdit"));

        donorHLAGridLayout->addWidget(donorDR1LineEdit, 5, 1, 1, 1);

        donorDR2LineEdit = new QLineEdit(layoutWidget_7);
        donorDR2LineEdit->setObjectName(QStringLiteral("donorDR2LineEdit"));

        donorHLAGridLayout->addWidget(donorDR2LineEdit, 5, 2, 1, 1);

        layoutWidget_9 = new QWidget(hlaInfoTab);
        layoutWidget_9->setObjectName(QStringLiteral("layoutWidget_9"));
        layoutWidget_9->setGeometry(QRect(10, 200, 277, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget_9);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        donorHLAAdditionalLabel = new QLabel(layoutWidget_9);
        donorHLAAdditionalLabel->setObjectName(QStringLiteral("donorHLAAdditionalLabel"));

        horizontalLayout->addWidget(donorHLAAdditionalLabel);

        donorHLALineEdit = new QLineEdit(layoutWidget_9);
        donorHLALineEdit->setObjectName(QStringLiteral("donorHLALineEdit"));

        horizontalLayout->addWidget(donorHLALineEdit);

        layoutWidget1 = new QWidget(hlaInfoTab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(210, 10, 91, 181));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        donorHLADRLayout = new QGroupBox(layoutWidget1);
        donorHLADRLayout->setObjectName(QStringLiteral("donorHLADRLayout"));
        layoutWidget_5 = new QWidget(donorHLADRLayout);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(20, 20, 51, 65));
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


        verticalLayout->addWidget(donorHLADRLayout);

        donorHLABWLayout = new QGroupBox(layoutWidget1);
        donorHLABWLayout->setObjectName(QStringLiteral("donorHLABWLayout"));
        layoutWidget_6 = new QWidget(donorHLABWLayout);
        layoutWidget_6->setObjectName(QStringLiteral("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(20, 20, 47, 42));
        donorHLABWVerticalLayout = new QVBoxLayout(layoutWidget_6);
        donorHLABWVerticalLayout->setObjectName(QStringLiteral("donorHLABWVerticalLayout"));
        donorHLABWVerticalLayout->setContentsMargins(0, 0, 0, 0);
        donorBW4CheckBox = new QCheckBox(layoutWidget_6);
        donorBW4CheckBox->setObjectName(QStringLiteral("donorBW4CheckBox"));

        donorHLABWVerticalLayout->addWidget(donorBW4CheckBox);

        donorBW6CheckBox = new QCheckBox(layoutWidget_6);
        donorBW6CheckBox->setObjectName(QStringLiteral("donorBW6CheckBox"));

        donorHLABWVerticalLayout->addWidget(donorBW6CheckBox);


        verticalLayout->addWidget(donorHLABWLayout);

        morePairInfo->addTab(hlaInfoTab, QString());
        layoutWidget->raise();
        layoutWidget_7->raise();
        layoutWidget_9->raise();
        commentTab = new QWidget();
        commentTab->setObjectName(QStringLiteral("commentTab"));
        commentTextEdit = new QTextEdit(commentTab);
        commentTextEdit->setObjectName(QStringLiteral("commentTextEdit"));
        commentTextEdit->setGeometry(QRect(13, 10, 291, 211));
        morePairInfo->addTab(commentTab, QString());

        retranslateUi(AltruisticDonorDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AltruisticDonorDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AltruisticDonorDialog, SLOT(reject()));

        morePairInfo->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AltruisticDonorDialog);
    } // setupUi

    void retranslateUi(QDialog *AltruisticDonorDialog)
    {
        AltruisticDonorDialog->setWindowTitle(QApplication::translate("AltruisticDonorDialog", "Add New AD", 0));
        donorGroupBox->setTitle(QApplication::translate("AltruisticDonorDialog", "Donor Information", 0));
        donorNameLabel->setText(QApplication::translate("AltruisticDonorDialog", "Name", 0));
        donorAgeLabel->setText(QApplication::translate("AltruisticDonorDialog", "Age", 0));
        donorBTLabel->setText(QApplication::translate("AltruisticDonorDialog", "Blood Type", 0));
        donorBTComboBox->clear();
        donorBTComboBox->insertItems(0, QStringList()
         << QApplication::translate("AltruisticDonorDialog", "O", 0)
         << QApplication::translate("AltruisticDonorDialog", "A", 0)
         << QApplication::translate("AltruisticDonorDialog", "B", 0)
         << QApplication::translate("AltruisticDonorDialog", "AB", 0)
        );
        donorGenderComboBox->clear();
        donorGenderComboBox->insertItems(0, QStringList()
         << QApplication::translate("AltruisticDonorDialog", "Male", 0)
         << QApplication::translate("AltruisticDonorDialog", "Female", 0)
        );
        donorHeightLabel->setText(QApplication::translate("AltruisticDonorDialog", "Height (m)", 0));
        donorWeightLabel->setText(QApplication::translate("AltruisticDonorDialog", "Weight (kg)", 0));
        donorGenderLabel->setText(QApplication::translate("AltruisticDonorDialog", "Gender", 0));
        morePairInfo->setTabText(morePairInfo->indexOf(donorCharacteristicsTab), QApplication::translate("AltruisticDonorDialog", "Donor Characteristics", 0));
        donorALabel->setText(QApplication::translate("AltruisticDonorDialog", "Donor HLA A", 0));
        donorBLineEdit->setText(QApplication::translate("AltruisticDonorDialog", "Donor HLA B", 0));
        donorCWLineEdit->setText(QApplication::translate("AltruisticDonorDialog", "Donor HLA CW", 0));
        donorDPLabel->setText(QApplication::translate("AltruisticDonorDialog", "Donor HLA DP", 0));
        donorDQLabel->setText(QApplication::translate("AltruisticDonorDialog", "Donor HLA DQ", 0));
        donorDRLabel->setText(QApplication::translate("AltruisticDonorDialog", "Donor HLA DR", 0));
        donorHLAAdditionalLabel->setText(QApplication::translate("AltruisticDonorDialog", "Additional Donor Antigens", 0));
        donorHLADRLayout->setTitle(QApplication::translate("AltruisticDonorDialog", "Donor HLA DR", 0));
        donorDR51CheckBox->setText(QApplication::translate("AltruisticDonorDialog", "DR51", 0));
        donorDR52CheckBox->setText(QApplication::translate("AltruisticDonorDialog", "DR52", 0));
        donorDR53CheckBox->setText(QApplication::translate("AltruisticDonorDialog", "DR53", 0));
        donorHLABWLayout->setTitle(QApplication::translate("AltruisticDonorDialog", "Donor HLA BW", 0));
        donorBW4CheckBox->setText(QApplication::translate("AltruisticDonorDialog", "BW4", 0));
        donorBW6CheckBox->setText(QApplication::translate("AltruisticDonorDialog", "BW6", 0));
        morePairInfo->setTabText(morePairInfo->indexOf(hlaInfoTab), QApplication::translate("AltruisticDonorDialog", "HLA Information", 0));
        morePairInfo->setTabText(morePairInfo->indexOf(commentTab), QApplication::translate("AltruisticDonorDialog", "Comments", 0));
    } // retranslateUi

};

namespace Ui {
    class AltruisticDonorDialog: public Ui_AltruisticDonorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALTRUISTICDONORDIALOG_H
