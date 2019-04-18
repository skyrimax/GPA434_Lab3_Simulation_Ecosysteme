/********************************************************************************
** Form generated from reading UI file 'SimulationMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATIONMAINWINDOW_H
#define UI_SIMULATIONMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulationMainWindowClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QSpacerItem *horizontalSpacer;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QPushButton *parameterButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *resumeButton;
    QPushButton *stepButton;
    QPushButton *stopButton;
    QSpacerItem *verticalSpacer;
    QPushButton *AProposButton;
    QSpacerItem *verticalSpacer_4;
    QFrame *line_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *SimulationMainWindowClass)
    {
        if (SimulationMainWindowClass->objectName().isEmpty())
            SimulationMainWindowClass->setObjectName(QString::fromUtf8("SimulationMainWindowClass"));
        SimulationMainWindowClass->resize(762, 555);
        centralWidget = new QWidget(SimulationMainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(500, 500));
        graphicsView->setMaximumSize(QSize(600, 600));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout->addWidget(graphicsView);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        parameterButton = new QPushButton(centralWidget);
        parameterButton->setObjectName(QString::fromUtf8("parameterButton"));

        verticalLayout->addWidget(parameterButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        verticalLayout->addWidget(startButton);

        pauseButton = new QPushButton(centralWidget);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));

        verticalLayout->addWidget(pauseButton);

        resumeButton = new QPushButton(centralWidget);
        resumeButton->setObjectName(QString::fromUtf8("resumeButton"));

        verticalLayout->addWidget(resumeButton);

        stepButton = new QPushButton(centralWidget);
        stepButton->setObjectName(QString::fromUtf8("stepButton"));

        verticalLayout->addWidget(stepButton);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        verticalLayout->addWidget(stopButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        AProposButton = new QPushButton(centralWidget);
        AProposButton->setObjectName(QString::fromUtf8("AProposButton"));

        verticalLayout->addWidget(AProposButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        SimulationMainWindowClass->setCentralWidget(centralWidget);

        retranslateUi(SimulationMainWindowClass);
        QObject::connect(AProposButton, SIGNAL(clicked()), SimulationMainWindowClass, SLOT(showAPropos()));

        QMetaObject::connectSlotsByName(SimulationMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimulationMainWindowClass)
    {
        SimulationMainWindowClass->setWindowTitle(QApplication::translate("SimulationMainWindowClass", "SimulationMainWindow", nullptr));
        parameterButton->setText(QApplication::translate("SimulationMainWindowClass", "Param\303\250tres", nullptr));
        startButton->setText(QApplication::translate("SimulationMainWindowClass", "D\303\251marrer", nullptr));
        pauseButton->setText(QApplication::translate("SimulationMainWindowClass", "Pause", nullptr));
        resumeButton->setText(QApplication::translate("SimulationMainWindowClass", "Reprendre", nullptr));
        stepButton->setText(QApplication::translate("SimulationMainWindowClass", "Par \303\251tape", nullptr));
        stopButton->setText(QApplication::translate("SimulationMainWindowClass", "Terminer", nullptr));
        AProposButton->setText(QApplication::translate("SimulationMainWindowClass", "\303\200 propos", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimulationMainWindowClass: public Ui_SimulationMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATIONMAINWINDOW_H
