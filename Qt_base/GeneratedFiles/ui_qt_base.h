/********************************************************************************
** Form generated from reading UI file 'qt_base.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_BASE_H
#define UI_QT_BASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include "openglwidget_.h"

QT_BEGIN_NAMESPACE

class Ui_Qt_baseClass
{
public:
    OpenglWidgetClass *centralWidget;

    void setupUi(QMainWindow *Qt_baseClass)
    {
        if (Qt_baseClass->objectName().isEmpty())
            Qt_baseClass->setObjectName(QStringLiteral("Qt_baseClass"));
        Qt_baseClass->resize(727, 678);
        centralWidget = new OpenglWidgetClass(Qt_baseClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Qt_baseClass->setCentralWidget(centralWidget);

        retranslateUi(Qt_baseClass);

        QMetaObject::connectSlotsByName(Qt_baseClass);
    } // setupUi

    void retranslateUi(QMainWindow *Qt_baseClass)
    {
        Qt_baseClass->setWindowTitle(QApplication::translate("Qt_baseClass", "Qt_base", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Qt_baseClass: public Ui_Qt_baseClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_BASE_H
