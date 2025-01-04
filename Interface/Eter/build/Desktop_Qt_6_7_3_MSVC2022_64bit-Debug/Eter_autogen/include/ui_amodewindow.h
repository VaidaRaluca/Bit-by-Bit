/********************************************************************************
** Form generated from reading UI file 'amodewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AMODEWINDOW_H
#define UI_AMODEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AModeWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AModeWindow)
    {
        if (AModeWindow->objectName().isEmpty())
            AModeWindow->setObjectName("AModeWindow");
        AModeWindow->resize(1315, 708);
        centralwidget = new QWidget(AModeWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(310, 500, 841, 111));
        layoutWidget->setMaximumSize(QSize(16777212, 16777215));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        label->setMaximumSize(QSize(16777212, 16777215));

        horizontalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setMaximumSize(QSize(16777212, 16777215));

        horizontalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        label_3->setMaximumSize(QSize(16777212, 16777215));

        horizontalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");
        label_4->setMaximumSize(QSize(16777212, 16777215));

        horizontalLayout->addWidget(label_4);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");
        label_5->setMaximumSize(QSize(16777212, 16777215));

        horizontalLayout->addWidget(label_5);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");
        label_6->setMaximumSize(QSize(16777212, 16777215));

        horizontalLayout->addWidget(label_6);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName("label_7");

        horizontalLayout->addWidget(label_7);

        AModeWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AModeWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1315, 26));
        AModeWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AModeWindow);
        statusbar->setObjectName("statusbar");
        AModeWindow->setStatusBar(statusbar);

        retranslateUi(AModeWindow);

        QMetaObject::connectSlotsByName(AModeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AModeWindow)
    {
        AModeWindow->setWindowTitle(QCoreApplication::translate("AModeWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("AModeWindow", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("AModeWindow", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("AModeWindow", "TextLabel", nullptr));
        label_4->setText(QCoreApplication::translate("AModeWindow", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("AModeWindow", "TextLabel", nullptr));
        label_6->setText(QCoreApplication::translate("AModeWindow", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("AModeWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AModeWindow: public Ui_AModeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AMODEWINDOW_H
