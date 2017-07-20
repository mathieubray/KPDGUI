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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogMessage
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *messageBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogMessage)
    {
        if (DialogMessage->objectName().isEmpty())
            DialogMessage->setObjectName(QStringLiteral("DialogMessage"));
        DialogMessage->resize(400, 514);
        DialogMessage->setMinimumSize(QSize(400, 514));
        DialogMessage->setMaximumSize(QSize(400, 514));
        layoutWidget = new QWidget(DialogMessage);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 381, 501));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        messageBox = new QTextEdit(layoutWidget);
        messageBox->setObjectName(QStringLiteral("messageBox"));

        verticalLayout->addWidget(messageBox);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


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
