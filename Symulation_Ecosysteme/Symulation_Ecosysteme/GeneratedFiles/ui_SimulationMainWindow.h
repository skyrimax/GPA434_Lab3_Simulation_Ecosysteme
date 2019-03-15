/********************************************************************************
** Form generated from reading UI file 'SimulationMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONMAINWINDOW_H
#define UI_SIMULATIONMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationMainWindowClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimulationMainWindowClass)
    {
        if (SimulationMainWindowClass->objectName().isEmpty())
            SimulationMainWindowClass->setObjectName(QString::fromUtf8("SimulationMainWindowClass"));
        SimulationMainWindowClass->resize(600, 400);
        menuBar = new QMenuBar(SimulationMainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SimulationMainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimulationMainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SimulationMainWindowClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SimulationMainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SimulationMainWindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SimulationMainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SimulationMainWindowClass->setStatusBar(statusBar);

        retranslateUi(SimulationMainWindowClass);

        QMetaObject::connectSlotsByName(SimulationMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimulationMainWindowClass)
    {
        SimulationMainWindowClass->setWindowTitle(QApplication::translate("SimulationMainWindowClass", "SimulationMainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimulationMainWindowClass: public Ui_SimulationMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONMAINWINDOW_H
