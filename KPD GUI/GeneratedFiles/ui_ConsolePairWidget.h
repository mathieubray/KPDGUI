/********************************************************************************
** Form generated from reading UI file 'ConsolePairWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSOLEPAIRWIDGET_H
#define UI_CONSOLEPAIRWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KPDGUIConsolePairWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QStackedWidget *stack;

    void setupUi(QWidget *KPDGUIConsolePairWidget)
    {
        if (KPDGUIConsolePairWidget->objectName().isEmpty())
            KPDGUIConsolePairWidget->setObjectName(QStringLiteral("KPDGUIConsolePairWidget"));
        KPDGUIConsolePairWidget->resize(463, 161);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(KPDGUIConsolePairWidget->sizePolicy().hasHeightForWidth());
        KPDGUIConsolePairWidget->setSizePolicy(sizePolicy);
        KPDGUIConsolePairWidget->setAutoFillBackground(false);
        gridLayout = new QGridLayout(KPDGUIConsolePairWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, -1, -1, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(308, 14, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        leftButton = new QPushButton(KPDGUIConsolePairWidget);
        leftButton->setObjectName(QStringLiteral("leftButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(leftButton->sizePolicy().hasHeightForWidth());
        leftButton->setSizePolicy(sizePolicy1);
        leftButton->setMinimumSize(QSize(21, 24));
        leftButton->setMaximumSize(QSize(21, 24));

        horizontalLayout->addWidget(leftButton);

        rightButton = new QPushButton(KPDGUIConsolePairWidget);
        rightButton->setObjectName(QStringLiteral("rightButton"));
        sizePolicy1.setHeightForWidth(rightButton->sizePolicy().hasHeightForWidth());
        rightButton->setSizePolicy(sizePolicy1);
        rightButton->setMinimumSize(QSize(21, 24));
        rightButton->setMaximumSize(QSize(21, 24));

        horizontalLayout->addWidget(rightButton);


        verticalLayout->addLayout(horizontalLayout);

        stack = new QStackedWidget(KPDGUIConsolePairWidget);
        stack->setObjectName(QStringLiteral("stack"));
        sizePolicy.setHeightForWidth(stack->sizePolicy().hasHeightForWidth());
        stack->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(stack);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(KPDGUIConsolePairWidget);

        QMetaObject::connectSlotsByName(KPDGUIConsolePairWidget);
    } // setupUi

    void retranslateUi(QWidget *KPDGUIConsolePairWidget)
    {
        KPDGUIConsolePairWidget->setWindowTitle(QApplication::translate("KPDGUIConsolePairWidget", "Form", 0));
        leftButton->setText(QApplication::translate("KPDGUIConsolePairWidget", "\342\227\204", 0));
        rightButton->setText(QApplication::translate("KPDGUIConsolePairWidget", "\342\226\272", 0));
    } // retranslateUi

};

namespace Ui {
    class KPDGUIConsolePairWidget: public Ui_KPDGUIConsolePairWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLEPAIRWIDGET_H
