/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QCustomPlot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPortName;
    QComboBox *cboPortName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelBaudRate;
    QComboBox *cboBaudrate;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelDataBit;
    QComboBox *cboDataBit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelParity;
    QComboBox *cboParity;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelStopBit;
    QComboBox *cboStopBit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelFlowControl;
    QComboBox *cboFlowContral;
    QVBoxLayout *verticalLayout_2;
    QPlainTextEdit *RecveeiveplainTextEdit;
    QPlainTextEdit *SendplainTextEdit;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *timePlot;
    QPushButton *btnOpenPort;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *checkBox;
    QLineEdit *lineEdit;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSend;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(878, 476);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelPortName = new QLabel(groupBox);
        labelPortName->setObjectName(QString::fromUtf8("labelPortName"));

        horizontalLayout->addWidget(labelPortName);

        cboPortName = new QComboBox(groupBox);
        cboPortName->setObjectName(QString::fromUtf8("cboPortName"));
        cboPortName->setMinimumSize(QSize(70, 0));
        cboPortName->setMaximumSize(QSize(70, 16777215));

        horizontalLayout->addWidget(cboPortName);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelBaudRate = new QLabel(groupBox);
        labelBaudRate->setObjectName(QString::fromUtf8("labelBaudRate"));

        horizontalLayout_2->addWidget(labelBaudRate);

        cboBaudrate = new QComboBox(groupBox);
        cboBaudrate->setObjectName(QString::fromUtf8("cboBaudrate"));
        cboBaudrate->setMinimumSize(QSize(70, 0));
        cboBaudrate->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_2->addWidget(cboBaudrate);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        labelDataBit = new QLabel(groupBox);
        labelDataBit->setObjectName(QString::fromUtf8("labelDataBit"));

        horizontalLayout_3->addWidget(labelDataBit);

        cboDataBit = new QComboBox(groupBox);
        cboDataBit->setObjectName(QString::fromUtf8("cboDataBit"));
        cboDataBit->setMinimumSize(QSize(70, 0));
        cboDataBit->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(cboDataBit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        labelParity = new QLabel(groupBox);
        labelParity->setObjectName(QString::fromUtf8("labelParity"));

        horizontalLayout_4->addWidget(labelParity);

        cboParity = new QComboBox(groupBox);
        cboParity->setObjectName(QString::fromUtf8("cboParity"));
        cboParity->setMinimumSize(QSize(70, 0));
        cboParity->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_4->addWidget(cboParity);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        labelStopBit = new QLabel(groupBox);
        labelStopBit->setObjectName(QString::fromUtf8("labelStopBit"));

        horizontalLayout_5->addWidget(labelStopBit);

        cboStopBit = new QComboBox(groupBox);
        cboStopBit->setObjectName(QString::fromUtf8("cboStopBit"));
        cboStopBit->setMinimumSize(QSize(70, 0));
        cboStopBit->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_5->addWidget(cboStopBit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        labelFlowControl = new QLabel(groupBox);
        labelFlowControl->setObjectName(QString::fromUtf8("labelFlowControl"));

        horizontalLayout_6->addWidget(labelFlowControl);

        cboFlowContral = new QComboBox(groupBox);
        cboFlowContral->setObjectName(QString::fromUtf8("cboFlowContral"));
        cboFlowContral->setMinimumSize(QSize(70, 0));
        cboFlowContral->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_6->addWidget(cboFlowContral);


        verticalLayout->addLayout(horizontalLayout_6);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        RecveeiveplainTextEdit = new QPlainTextEdit(centralwidget);
        RecveeiveplainTextEdit->setObjectName(QString::fromUtf8("RecveeiveplainTextEdit"));

        verticalLayout_2->addWidget(RecveeiveplainTextEdit);

        SendplainTextEdit = new QPlainTextEdit(centralwidget);
        SendplainTextEdit->setObjectName(QString::fromUtf8("SendplainTextEdit"));
        SendplainTextEdit->setMinimumSize(QSize(0, 80));
        SendplainTextEdit->setMaximumSize(QSize(16777215, 80));

        verticalLayout_2->addWidget(SendplainTextEdit);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        timePlot = new QCustomPlot(centralwidget);
        timePlot->setObjectName(QString::fromUtf8("timePlot"));
        timePlot->setMinimumSize(QSize(500, 192));

        verticalLayout_3->addWidget(timePlot);


        gridLayout->addLayout(verticalLayout_3, 0, 2, 1, 1);

        btnOpenPort = new QPushButton(centralwidget);
        btnOpenPort->setObjectName(QString::fromUtf8("btnOpenPort"));

        gridLayout->addWidget(btnOpenPort, 1, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_7->addWidget(checkBox);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(60, 0));
        lineEdit->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_7->addWidget(lineEdit);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_7->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        btnSend = new QPushButton(centralwidget);
        btnSend->setObjectName(QString::fromUtf8("btnSend"));

        horizontalLayout_7->addWidget(btnSend);


        gridLayout->addLayout(horizontalLayout_7, 1, 1, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 878, 23));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "SerialToolPlus", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        labelPortName->setText(QCoreApplication::translate("MainWindow", "\347\253\257\345\217\243\345\220\215\347\247\260", nullptr));
        labelBaudRate->setText(QCoreApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        labelDataBit->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        labelParity->setText(QCoreApplication::translate("MainWindow", "\345\245\207\345\201\266", nullptr));
        labelStopBit->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        labelFlowControl->setText(QCoreApplication::translate("MainWindow", "\346\265\201\346\216\247\345\210\266", nullptr));
        btnOpenPort->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "CheckBox", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "ms/\346\254\241", nullptr));
        btnSend->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
