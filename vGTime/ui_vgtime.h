/********************************************************************************
** Form generated from reading UI file 'vgtime.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VGTIME_H
#define UI_VGTIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vGTime
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *lab_time;
    QLabel *lab_date;

    void setupUi(QWidget *vGTime)
    {
        if (vGTime->objectName().isEmpty())
            vGTime->setObjectName(QString::fromUtf8("vGTime"));
        vGTime->resize(500, 333);
        vGTime->setFocusPolicy(Qt::StrongFocus);
        gridLayout = new QGridLayout(vGTime);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lab_time = new QLabel(vGTime);
        lab_time->setObjectName(QString::fromUtf8("lab_time"));
        lab_time->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));
        lab_time->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lab_time);

        lab_date = new QLabel(vGTime);
        lab_date->setObjectName(QString::fromUtf8("lab_date"));
        lab_date->setStyleSheet(QString::fromUtf8("color: rgb(0, 255, 0);"));
        lab_date->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lab_date);

        verticalLayout->setStretch(0, 5);
        verticalLayout->setStretch(1, 1);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(vGTime);

        QMetaObject::connectSlotsByName(vGTime);
    } // setupUi

    void retranslateUi(QWidget *vGTime)
    {
        vGTime->setWindowTitle(QCoreApplication::translate("vGTime", "Form", nullptr));
        lab_time->setText(QCoreApplication::translate("vGTime", "time", nullptr));
        lab_date->setText(QCoreApplication::translate("vGTime", "date", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vGTime: public Ui_vGTime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VGTIME_H
