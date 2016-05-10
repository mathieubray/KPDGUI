/********************************************************************************
** Form generated from reading UI file 'ReadFileDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READFILEDIALOG_H
#define UI_READFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ReadFileDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *pairFileLabel;
    QLineEdit *pairFileLineEdit;
    QToolButton *toolButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ReadFileDialog)
    {
        if (ReadFileDialog->objectName().isEmpty())
            ReadFileDialog->setObjectName(QStringLiteral("ReadFileDialog"));
        ReadFileDialog->resize(417, 100);
        ReadFileDialog->setMinimumSize(QSize(417, 100));
        ReadFileDialog->setMaximumSize(QSize(417, 100));
        verticalLayout = new QVBoxLayout(ReadFileDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pairFileLabel = new QLabel(ReadFileDialog);
        pairFileLabel->setObjectName(QStringLiteral("pairFileLabel"));

        horizontalLayout->addWidget(pairFileLabel);

        pairFileLineEdit = new QLineEdit(ReadFileDialog);
        pairFileLineEdit->setObjectName(QStringLiteral("pairFileLineEdit"));

        horizontalLayout->addWidget(pairFileLineEdit);

        toolButton = new QToolButton(ReadFileDialog);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        horizontalLayout->addWidget(toolButton);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(ReadFileDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setEnabled(true);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ReadFileDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ReadFileDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ReadFileDialog, SLOT(reject()));
        QObject::connect(toolButton, SIGNAL(clicked()), ReadFileDialog, SLOT(browse()));
        QObject::connect(pairFileLineEdit, SIGNAL(textChanged(QString)), ReadFileDialog, SLOT(checkValidFile(QString)));

        QMetaObject::connectSlotsByName(ReadFileDialog);
    } // setupUi

    void retranslateUi(QDialog *ReadFileDialog)
    {
        ReadFileDialog->setWindowTitle(QApplication::translate("ReadFileDialog", "Load Pairs From File", 0));
        pairFileLabel->setText(QApplication::translate("ReadFileDialog", "Pair File", 0));
        toolButton->setText(QApplication::translate("ReadFileDialog", "Browse...", 0));
    } // retranslateUi

};

namespace Ui {
    class ReadFileDialog: public Ui_ReadFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READFILEDIALOG_H
