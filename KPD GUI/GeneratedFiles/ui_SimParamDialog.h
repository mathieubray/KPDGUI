/********************************************************************************
** Form generated from reading UI file 'SimParamDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPARAMDIALOG_H
#define UI_SIMPARAMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SimParamDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *chainLengthLabel;
    QSpinBox *chainLengthSpinBox;
    QSlider *chainLengthSlider;
    QHBoxLayout *horizontalLayout_2;
    QLabel *utilLabel;
    QComboBox *utilComboBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *optLabel;
    QComboBox *optComboBox;
    QVBoxLayout *advVerticalLayout;
    QCheckBox *praBox;
    QCheckBox *reserveOtoOBox;
    QCheckBox *checkDPBox;
    QCheckBox *compatibleBox;
    QCheckBox *allowABBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *tiebreakLabel;
    QSpinBox *tiebreakBox;
    QSlider *tiebreakSlider;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SimParamDialog)
    {
        if (SimParamDialog->objectName().isEmpty())
            SimParamDialog->setObjectName(QStringLiteral("SimParamDialog"));
        SimParamDialog->resize(257, 272);
        SimParamDialog->setMinimumSize(QSize(257, 272));
        SimParamDialog->setMaximumSize(QSize(257, 272));
        verticalLayout = new QVBoxLayout(SimParamDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        chainLengthLabel = new QLabel(SimParamDialog);
        chainLengthLabel->setObjectName(QStringLiteral("chainLengthLabel"));

        horizontalLayout->addWidget(chainLengthLabel);

        chainLengthSpinBox = new QSpinBox(SimParamDialog);
        chainLengthSpinBox->setObjectName(QStringLiteral("chainLengthSpinBox"));
        chainLengthSpinBox->setMinimum(2);
        chainLengthSpinBox->setMaximum(6);

        horizontalLayout->addWidget(chainLengthSpinBox);

        chainLengthSlider = new QSlider(SimParamDialog);
        chainLengthSlider->setObjectName(QStringLiteral("chainLengthSlider"));
        chainLengthSlider->setMinimum(2);
        chainLengthSlider->setMaximum(6);
        chainLengthSlider->setPageStep(2);
        chainLengthSlider->setOrientation(Qt::Horizontal);
        chainLengthSlider->setTickPosition(QSlider::TicksBelow);
        chainLengthSlider->setTickInterval(1);

        horizontalLayout->addWidget(chainLengthSlider);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        utilLabel = new QLabel(SimParamDialog);
        utilLabel->setObjectName(QStringLiteral("utilLabel"));

        horizontalLayout_2->addWidget(utilLabel);

        utilComboBox = new QComboBox(SimParamDialog);
        utilComboBox->setObjectName(QStringLiteral("utilComboBox"));

        horizontalLayout_2->addWidget(utilComboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        optLabel = new QLabel(SimParamDialog);
        optLabel->setObjectName(QStringLiteral("optLabel"));

        horizontalLayout_3->addWidget(optLabel);

        optComboBox = new QComboBox(SimParamDialog);
        optComboBox->setObjectName(QStringLiteral("optComboBox"));

        horizontalLayout_3->addWidget(optComboBox);


        verticalLayout->addLayout(horizontalLayout_3);

        advVerticalLayout = new QVBoxLayout();
        advVerticalLayout->setObjectName(QStringLiteral("advVerticalLayout"));
        praBox = new QCheckBox(SimParamDialog);
        praBox->setObjectName(QStringLiteral("praBox"));

        advVerticalLayout->addWidget(praBox);

        reserveOtoOBox = new QCheckBox(SimParamDialog);
        reserveOtoOBox->setObjectName(QStringLiteral("reserveOtoOBox"));

        advVerticalLayout->addWidget(reserveOtoOBox);

        checkDPBox = new QCheckBox(SimParamDialog);
        checkDPBox->setObjectName(QStringLiteral("checkDPBox"));

        advVerticalLayout->addWidget(checkDPBox);

        compatibleBox = new QCheckBox(SimParamDialog);
        compatibleBox->setObjectName(QStringLiteral("compatibleBox"));

        advVerticalLayout->addWidget(compatibleBox);

        allowABBox = new QCheckBox(SimParamDialog);
        allowABBox->setObjectName(QStringLiteral("allowABBox"));

        advVerticalLayout->addWidget(allowABBox);


        verticalLayout->addLayout(advVerticalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        tiebreakLabel = new QLabel(SimParamDialog);
        tiebreakLabel->setObjectName(QStringLiteral("tiebreakLabel"));

        horizontalLayout_5->addWidget(tiebreakLabel);

        tiebreakBox = new QSpinBox(SimParamDialog);
        tiebreakBox->setObjectName(QStringLiteral("tiebreakBox"));
        tiebreakBox->setMinimum(1);
        tiebreakBox->setMaximum(25);
        tiebreakBox->setValue(1);

        horizontalLayout_5->addWidget(tiebreakBox);

        tiebreakSlider = new QSlider(SimParamDialog);
        tiebreakSlider->setObjectName(QStringLiteral("tiebreakSlider"));
        tiebreakSlider->setMinimum(1);
        tiebreakSlider->setMaximum(25);
        tiebreakSlider->setPageStep(2);
        tiebreakSlider->setValue(1);
        tiebreakSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(tiebreakSlider);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        buttonBox = new QDialogButtonBox(SimParamDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_4->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_4);

#ifndef QT_NO_SHORTCUT
        chainLengthLabel->setBuddy(chainLengthSpinBox);
        utilLabel->setBuddy(utilComboBox);
        optLabel->setBuddy(optComboBox);
        tiebreakLabel->setBuddy(tiebreakBox);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(chainLengthSpinBox, chainLengthSlider);
        QWidget::setTabOrder(chainLengthSlider, utilComboBox);
        QWidget::setTabOrder(utilComboBox, optComboBox);
        QWidget::setTabOrder(optComboBox, praBox);
        QWidget::setTabOrder(praBox, reserveOtoOBox);
        QWidget::setTabOrder(reserveOtoOBox, checkDPBox);
        QWidget::setTabOrder(checkDPBox, compatibleBox);
        QWidget::setTabOrder(compatibleBox, allowABBox);

        retranslateUi(SimParamDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SimParamDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SimParamDialog, SLOT(reject()));
        QObject::connect(chainLengthSpinBox, SIGNAL(valueChanged(int)), chainLengthSlider, SLOT(setValue(int)));
        QObject::connect(chainLengthSlider, SIGNAL(sliderMoved(int)), chainLengthSpinBox, SLOT(setValue(int)));
        QObject::connect(tiebreakBox, SIGNAL(valueChanged(int)), tiebreakSlider, SLOT(setValue(int)));
        QObject::connect(tiebreakSlider, SIGNAL(sliderMoved(int)), tiebreakBox, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(SimParamDialog);
    } // setupUi

    void retranslateUi(QDialog *SimParamDialog)
    {
        SimParamDialog->setWindowTitle(QApplication::translate("SimParamDialog", "Set Parameters", 0));
        chainLengthLabel->setText(QApplication::translate("SimParamDialog", "Maximum Chain Length", 0));
        utilLabel->setText(QApplication::translate("SimParamDialog", "Utility Scheme", 0));
        utilComboBox->clear();
        utilComboBox->insertItems(0, QStringList()
         << QApplication::translate("SimParamDialog", "Transplants", 0)
         << QApplication::translate("SimParamDialog", "5 Year Survival", 0)
         << QApplication::translate("SimParamDialog", "10 Year Survival", 0)
         << QApplication::translate("SimParamDialog", "Score", 0)
        );
        optLabel->setText(QApplication::translate("SimParamDialog", "Optimization Scheme", 0));
        optComboBox->clear();
        optComboBox->insertItems(0, QStringList()
         << QApplication::translate("SimParamDialog", "Utility", 0)
         << QApplication::translate("SimParamDialog", "Expected Utility", 0)
         << QApplication::translate("SimParamDialog", "Fallbacks", 0)
         << QApplication::translate("SimParamDialog", "Extended Fallbacks", 0)
        );
        praBox->setText(QApplication::translate("SimParamDialog", "Add Advantage to High PRA Recipients", 0));
        reserveOtoOBox->setText(QApplication::translate("SimParamDialog", "Reserve O Donors for O Recipients", 0));
        checkDPBox->setText(QApplication::translate("SimParamDialog", "Check Additional HLA Information", 0));
        compatibleBox->setText(QApplication::translate("SimParamDialog", "Include Compatible Pairs in Match Run", 0));
        allowABBox->setText(QApplication::translate("SimParamDialog", "Allow AB Bridge Donors", 0));
        tiebreakLabel->setText(QApplication::translate("SimParamDialog", "Number of Solutions", 0));
    } // retranslateUi

};

namespace Ui {
    class SimParamDialog: public Ui_SimParamDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPARAMDIALOG_H
