/********************************************************************************
** Form generated from reading UI file 'DialogMatch.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMATCH_H
#define UI_DIALOGMATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogMatch
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *matchLayout;
    QGridLayout *textLayout;
    QLabel *crossmatchLabel;
    QLineEdit *crossmatchLineEdit;
    QCheckBox *includeCheckBox;
    QLineEdit *donorLineEdit;
    QLineEdit *candidateLineEdit;
    QLabel *donorLabel;
    QLabel *candidateLabel;
    QCheckBox *difficultToMatchBox;
    QGridLayout *estimatesLayout;
    QLineEdit *tenYearSurvivalLineEdit;
    QLabel *probabilityLabel;
    QDoubleSpinBox *scoreSpinBox;
    QLabel *scoreLabel;
    QLabel *tenYearSurvivalLabel;
    QLineEdit *fiveYearSurvivalLineEdit;
    QDoubleSpinBox *probabilitySpinBox;
    QLabel *fiveYearSurvivalLabel;
    QHBoxLayout *buttonBoxLayout;
    QPushButton *additionalInformationButton;
    QSpacerItem *buttonBoxSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogMatch)
    {
        if (DialogMatch->objectName().isEmpty())
            DialogMatch->setObjectName(QStringLiteral("DialogMatch"));
        DialogMatch->resize(501, 201);
        DialogMatch->setMinimumSize(QSize(501, 201));
        DialogMatch->setMaximumSize(QSize(501, 201));
        layoutWidget = new QWidget(DialogMatch);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 481, 181));
        matchLayout = new QVBoxLayout(layoutWidget);
        matchLayout->setObjectName(QStringLiteral("matchLayout"));
        matchLayout->setContentsMargins(0, 0, 0, 0);
        textLayout = new QGridLayout();
        textLayout->setObjectName(QStringLiteral("textLayout"));
        crossmatchLabel = new QLabel(layoutWidget);
        crossmatchLabel->setObjectName(QStringLiteral("crossmatchLabel"));

        textLayout->addWidget(crossmatchLabel, 3, 0, 1, 2);

        crossmatchLineEdit = new QLineEdit(layoutWidget);
        crossmatchLineEdit->setObjectName(QStringLiteral("crossmatchLineEdit"));
        crossmatchLineEdit->setReadOnly(true);

        textLayout->addWidget(crossmatchLineEdit, 3, 2, 1, 2);

        includeCheckBox = new QCheckBox(layoutWidget);
        includeCheckBox->setObjectName(QStringLiteral("includeCheckBox"));
        includeCheckBox->setLayoutDirection(Qt::RightToLeft);
        includeCheckBox->setChecked(true);

        textLayout->addWidget(includeCheckBox, 1, 3, 1, 1);

        donorLineEdit = new QLineEdit(layoutWidget);
        donorLineEdit->setObjectName(QStringLiteral("donorLineEdit"));
        donorLineEdit->setReadOnly(true);

        textLayout->addWidget(donorLineEdit, 1, 2, 1, 1);

        candidateLineEdit = new QLineEdit(layoutWidget);
        candidateLineEdit->setObjectName(QStringLiteral("candidateLineEdit"));
        candidateLineEdit->setReadOnly(true);

        textLayout->addWidget(candidateLineEdit, 2, 2, 1, 1);

        donorLabel = new QLabel(layoutWidget);
        donorLabel->setObjectName(QStringLiteral("donorLabel"));

        textLayout->addWidget(donorLabel, 1, 0, 1, 2);

        candidateLabel = new QLabel(layoutWidget);
        candidateLabel->setObjectName(QStringLiteral("candidateLabel"));

        textLayout->addWidget(candidateLabel, 2, 0, 1, 2);

        difficultToMatchBox = new QCheckBox(layoutWidget);
        difficultToMatchBox->setObjectName(QStringLiteral("difficultToMatchBox"));
        difficultToMatchBox->setEnabled(false);
        difficultToMatchBox->setLayoutDirection(Qt::RightToLeft);
        difficultToMatchBox->setCheckable(true);

        textLayout->addWidget(difficultToMatchBox, 2, 3, 1, 1);


        matchLayout->addLayout(textLayout);

        estimatesLayout = new QGridLayout();
        estimatesLayout->setObjectName(QStringLiteral("estimatesLayout"));
        tenYearSurvivalLineEdit = new QLineEdit(layoutWidget);
        tenYearSurvivalLineEdit->setObjectName(QStringLiteral("tenYearSurvivalLineEdit"));
        tenYearSurvivalLineEdit->setReadOnly(true);

        estimatesLayout->addWidget(tenYearSurvivalLineEdit, 0, 3, 1, 1);

        probabilityLabel = new QLabel(layoutWidget);
        probabilityLabel->setObjectName(QStringLiteral("probabilityLabel"));

        estimatesLayout->addWidget(probabilityLabel, 1, 0, 1, 1);

        scoreSpinBox = new QDoubleSpinBox(layoutWidget);
        scoreSpinBox->setObjectName(QStringLiteral("scoreSpinBox"));
        scoreSpinBox->setMaximum(1000);
        scoreSpinBox->setValue(1);

        estimatesLayout->addWidget(scoreSpinBox, 1, 3, 1, 1);

        scoreLabel = new QLabel(layoutWidget);
        scoreLabel->setObjectName(QStringLiteral("scoreLabel"));

        estimatesLayout->addWidget(scoreLabel, 1, 2, 1, 1);

        tenYearSurvivalLabel = new QLabel(layoutWidget);
        tenYearSurvivalLabel->setObjectName(QStringLiteral("tenYearSurvivalLabel"));

        estimatesLayout->addWidget(tenYearSurvivalLabel, 0, 2, 1, 1);

        fiveYearSurvivalLineEdit = new QLineEdit(layoutWidget);
        fiveYearSurvivalLineEdit->setObjectName(QStringLiteral("fiveYearSurvivalLineEdit"));
        fiveYearSurvivalLineEdit->setReadOnly(true);

        estimatesLayout->addWidget(fiveYearSurvivalLineEdit, 0, 1, 1, 1);

        probabilitySpinBox = new QDoubleSpinBox(layoutWidget);
        probabilitySpinBox->setObjectName(QStringLiteral("probabilitySpinBox"));
        probabilitySpinBox->setMaximum(1);
        probabilitySpinBox->setSingleStep(0.1);
        probabilitySpinBox->setValue(0.1);

        estimatesLayout->addWidget(probabilitySpinBox, 1, 1, 1, 1);

        fiveYearSurvivalLabel = new QLabel(layoutWidget);
        fiveYearSurvivalLabel->setObjectName(QStringLiteral("fiveYearSurvivalLabel"));

        estimatesLayout->addWidget(fiveYearSurvivalLabel, 0, 0, 1, 1);


        matchLayout->addLayout(estimatesLayout);

        buttonBoxLayout = new QHBoxLayout();
        buttonBoxLayout->setObjectName(QStringLiteral("buttonBoxLayout"));
        additionalInformationButton = new QPushButton(layoutWidget);
        additionalInformationButton->setObjectName(QStringLiteral("additionalInformationButton"));

        buttonBoxLayout->addWidget(additionalInformationButton);

        buttonBoxSpacer = new QSpacerItem(258, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonBoxLayout->addItem(buttonBoxSpacer);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        buttonBoxLayout->addWidget(buttonBox);


        matchLayout->addLayout(buttonBoxLayout);


        retranslateUi(DialogMatch);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogMatch, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogMatch, SLOT(reject()));
        QObject::connect(additionalInformationButton, SIGNAL(clicked()), DialogMatch, SLOT(accept()));
        QObject::connect(additionalInformationButton, SIGNAL(clicked()), DialogMatch, SLOT(setAdditionalInformation()));

        QMetaObject::connectSlotsByName(DialogMatch);
    } // setupUi

    void retranslateUi(QDialog *DialogMatch)
    {
        DialogMatch->setWindowTitle(QApplication::translate("DialogMatch", "Match Information", 0));
        crossmatchLabel->setText(QApplication::translate("DialogMatch", "Crossmatch Result", 0));
        includeCheckBox->setText(QApplication::translate("DialogMatch", "Include in Match Run", 0));
        donorLabel->setText(QApplication::translate("DialogMatch", "Donor", 0));
        candidateLabel->setText(QApplication::translate("DialogMatch", "Candidate", 0));
        difficultToMatchBox->setText(QApplication::translate("DialogMatch", "Difficult Match", 0));
        probabilityLabel->setText(QApplication::translate("DialogMatch", "Failure Probability", 0));
        scoreLabel->setText(QApplication::translate("DialogMatch", "User-Assigned Score", 0));
        tenYearSurvivalLabel->setText(QApplication::translate("DialogMatch", "Ten Year Survival Estimate", 0));
        fiveYearSurvivalLabel->setText(QApplication::translate("DialogMatch", "Five Year Survival Estimate", 0));
        additionalInformationButton->setText(QApplication::translate("DialogMatch", "View Additional Information", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogMatch: public Ui_DialogMatch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMATCH_H
