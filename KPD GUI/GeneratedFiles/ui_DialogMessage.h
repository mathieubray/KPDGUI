/********************************************************************************
** Form generated from reading UI file 'DialogMessage.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMESSAGE_H
#define UI_DIALOGMESSAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogMessage
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTextEdit *messageBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogMessage)
    {
        if (DialogMessage->objectName().isEmpty())
            DialogMessage->setObjectName(QStringLiteral("DialogMessage"));
        DialogMessage->resize(500, 514);
        DialogMessage->setMinimumSize(QSize(500, 514));
        DialogMessage->setMaximumSize(QSize(16777215, 514));
        QIcon icon;
        icon.addFile(QStringLiteral("images/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        DialogMessage->setWindowIcon(icon);
        gridLayout = new QGridLayout(DialogMessage);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        messageBox = new QTextEdit(DialogMessage);
        messageBox->setObjectName(QStringLiteral("messageBox"));

        verticalLayout->addWidget(messageBox);

        buttonBox = new QDialogButtonBox(DialogMessage);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(DialogMessage);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogMessage, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogMessage, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogMessage);
    } // setupUi

    void retranslateUi(QDialog *DialogMessage)
    {
        DialogMessage->setWindowTitle(QApplication::translate("DialogMessage", "Solution Information", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogMessage: public Ui_DialogMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMESSAGE_H
