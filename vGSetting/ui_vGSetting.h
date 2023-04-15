/********************************************************************************
** Form generated from reading UI file 'vGSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VGSETTING_H
#define UI_VGSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vGSetting
{
public:
    QPushButton *btn;

    void setupUi(QWidget *vGSetting)
    {
        if (vGSetting->objectName().isEmpty())
            vGSetting->setObjectName(QString::fromUtf8("vGSetting"));
        vGSetting->resize(400, 300);
        vGSetting->setFocusPolicy(Qt::StrongFocus);
        btn = new QPushButton(vGSetting);
        btn->setObjectName(QString::fromUtf8("btn"));
        btn->setGeometry(QRect(120, 120, 141, 51));
        btn->setFocusPolicy(Qt::StrongFocus);

        retranslateUi(vGSetting);

        QMetaObject::connectSlotsByName(vGSetting);
    } // setupUi

    void retranslateUi(QWidget *vGSetting)
    {
        vGSetting->setWindowTitle(QCoreApplication::translate("vGSetting", "Form", nullptr));
        btn->setText(QCoreApplication::translate("vGSetting", "Come Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vGSetting: public Ui_vGSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VGSETTING_H
