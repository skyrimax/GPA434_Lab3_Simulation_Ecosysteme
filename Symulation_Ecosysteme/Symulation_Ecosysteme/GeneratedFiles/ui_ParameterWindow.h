/********************************************************************************
** Form generated from reading UI file 'ParameterWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERWINDOW_H
#define UI_PARAMETERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ParameterWindow
{
public:
    QFormLayout *formLayout;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_6;
    QSpinBox *qteHardes;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_5;
    QSpinBox *qteChevreuils;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QSpinBox *qteLoups;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *qteLapins;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer_4;
    QSpinBox *qteMeutes;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QCheckBox *seasoncheckBox;
    QCheckBox *viruscheckBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *helpButton;
    QPushButton *pretButton;

    void setupUi(QDialog *ParameterWindow)
    {
        if (ParameterWindow->objectName().isEmpty())
            ParameterWindow->setObjectName(QString::fromUtf8("ParameterWindow"));
        ParameterWindow->setWindowModality(Qt::NonModal);
        ParameterWindow->resize(571, 186);
        formLayout = new QFormLayout(ParameterWindow);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetFixedSize);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(ParameterWindow);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_2->addWidget(label_6);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        qteHardes = new QSpinBox(ParameterWindow);
        qteHardes->setObjectName(QString::fromUtf8("qteHardes"));
        qteHardes->setMaximum(10);

        horizontalLayout_2->addWidget(qteHardes);


        gridLayout->addLayout(horizontalLayout_2, 1, 2, 1, 2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(ParameterWindow);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        qteChevreuils = new QSpinBox(ParameterWindow);
        qteChevreuils->setObjectName(QString::fromUtf8("qteChevreuils"));
        qteChevreuils->setMinimum(1);
        qteChevreuils->setMaximum(100);

        horizontalLayout_5->addWidget(qteChevreuils);


        gridLayout->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(ParameterWindow);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        qteLoups = new QSpinBox(ParameterWindow);
        qteLoups->setObjectName(QString::fromUtf8("qteLoups"));
        qteLoups->setMinimum(1);
        qteLoups->setMaximum(100);

        horizontalLayout_4->addWidget(qteLoups);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_3 = new QLabel(ParameterWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_6->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        qteLapins = new QSpinBox(ParameterWindow);
        qteLapins->setObjectName(QString::fromUtf8("qteLapins"));
        qteLapins->setMinimum(1);
        qteLapins->setMaximum(100);

        horizontalLayout_6->addWidget(qteLapins);


        gridLayout->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(ParameterWindow);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        qteMeutes = new QSpinBox(ParameterWindow);
        qteMeutes->setObjectName(QString::fromUtf8("qteMeutes"));
        qteMeutes->setMaximum(10);

        horizontalLayout_3->addWidget(qteMeutes);


        gridLayout->addLayout(horizontalLayout_3, 2, 2, 1, 2);

        verticalSpacer = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 3, 1, 1);

        line = new QFrame(ParameterWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setLineWidth(3);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 0, 1, 3, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        seasoncheckBox = new QCheckBox(ParameterWindow);
        seasoncheckBox->setObjectName(QString::fromUtf8("seasoncheckBox"));

        verticalLayout->addWidget(seasoncheckBox);

        viruscheckBox = new QCheckBox(ParameterWindow);
        viruscheckBox->setObjectName(QString::fromUtf8("viruscheckBox"));

        verticalLayout->addWidget(viruscheckBox);


        gridLayout_2->addLayout(verticalLayout, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        helpButton = new QPushButton(ParameterWindow);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));

        horizontalLayout->addWidget(helpButton);

        pretButton = new QPushButton(ParameterWindow);
        pretButton->setObjectName(QString::fromUtf8("pretButton"));

        horizontalLayout->addWidget(pretButton);


        gridLayout_2->addLayout(horizontalLayout, 2, 1, 1, 1);


        formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout_2);


        retranslateUi(ParameterWindow);
        QObject::connect(pretButton, SIGNAL(clicked()), ParameterWindow, SLOT(accept()));
        QObject::connect(helpButton, SIGNAL(clicked()), ParameterWindow, SLOT(showAide()));

        QMetaObject::connectSlotsByName(ParameterWindow);
    } // setupUi

    void retranslateUi(QDialog *ParameterWindow)
    {
        ParameterWindow->setWindowTitle(QApplication::translate("ParameterWindow", "Param\303\250tres", nullptr));
        label_6->setText(QApplication::translate("ParameterWindow", "Quantit\303\251 de hardes de chevreuil :", nullptr));
        label_4->setText(QApplication::translate("ParameterWindow", "Quantit\303\251 de chevreuils au d\303\251marrage :", nullptr));
        label_5->setText(QApplication::translate("ParameterWindow", "Quantit\303\251 de loups au d\303\251marrage :", nullptr));
        label_3->setText(QApplication::translate("ParameterWindow", "Quantit\303\251 de lapins au d\303\251marrage :", nullptr));
        label->setText(QApplication::translate("ParameterWindow", "Quantit\303\251 de meutes de loup :", nullptr));
        seasoncheckBox->setText(QApplication::translate("ParameterWindow", "Ajout de saison", nullptr));
        viruscheckBox->setText(QApplication::translate("ParameterWindow", "Ajout de maladies", nullptr));
        helpButton->setText(QApplication::translate("ParameterWindow", "Aide", nullptr));
        pretButton->setText(QApplication::translate("ParameterWindow", "Pr\303\252t", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParameterWindow: public Ui_ParameterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERWINDOW_H
