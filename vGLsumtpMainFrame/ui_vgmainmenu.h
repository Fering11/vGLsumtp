/********************************************************************************
** Form generated from reading UI file 'vgmainmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VGMAINMENU_H
#define UI_VGMAINMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vGMainMenu
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *lab_center;
    QLabel *lab_description;
    QLabel *lab_left;
    QLabel *lab_right;

    void setupUi(QWidget *vGMainMenu)
    {
        if (vGMainMenu->objectName().isEmpty())
            vGMainMenu->setObjectName(QString::fromUtf8("vGMainMenu"));
        vGMainMenu->resize(544, 332);
        vGMainMenu->setFocusPolicy(Qt::StrongFocus);
        gridLayout_2 = new QGridLayout(vGMainMenu);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lab_center = new QLabel(vGMainMenu);
        lab_center->setObjectName(QString::fromUtf8("lab_center"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lab_center->sizePolicy().hasHeightForWidth());
        lab_center->setSizePolicy(sizePolicy);
        lab_center->setStyleSheet(QString::fromUtf8("gridline-color: rgb(85, 85, 0);"));
        lab_center->setScaledContents(false);
        lab_center->setAlignment(Qt::AlignCenter);
        lab_center->setMargin(-1);

        gridLayout->addWidget(lab_center, 0, 1, 1, 1);

        lab_description = new QLabel(vGMainMenu);
        lab_description->setObjectName(QString::fromUtf8("lab_description"));
        sizePolicy.setHeightForWidth(lab_description->sizePolicy().hasHeightForWidth());
        lab_description->setSizePolicy(sizePolicy);
        lab_description->setScaledContents(true);
        lab_description->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lab_description, 1, 1, 1, 1);

        lab_left = new QLabel(vGMainMenu);
        lab_left->setObjectName(QString::fromUtf8("lab_left"));
        sizePolicy.setHeightForWidth(lab_left->sizePolicy().hasHeightForWidth());
        lab_left->setSizePolicy(sizePolicy);
        lab_left->setScaledContents(false);
        lab_left->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lab_left, 0, 0, 2, 1);

        lab_right = new QLabel(vGMainMenu);
        lab_right->setObjectName(QString::fromUtf8("lab_right"));
        sizePolicy.setHeightForWidth(lab_right->sizePolicy().hasHeightForWidth());
        lab_right->setSizePolicy(sizePolicy);
        lab_right->setScaledContents(false);
        lab_right->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lab_right, 0, 2, 2, 1);

        gridLayout->setRowStretch(0, 10);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 7);
        gridLayout->setColumnStretch(2, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(vGMainMenu);

        QMetaObject::connectSlotsByName(vGMainMenu);
    } // setupUi

    void retranslateUi(QWidget *vGMainMenu)
    {
        vGMainMenu->setWindowTitle(QCoreApplication::translate("vGMainMenu", "Form", nullptr));
        lab_center->setText(QCoreApplication::translate("vGMainMenu", "Center", nullptr));
        lab_description->setText(QCoreApplication::translate("vGMainMenu", "description", nullptr));
        lab_left->setText(QCoreApplication::translate("vGMainMenu", "left", nullptr));
        lab_right->setText(QCoreApplication::translate("vGMainMenu", "Right", nullptr));
    } // retranslateUi

};

namespace Ui {
    class vGMainMenu: public Ui_vGMainMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VGMAINMENU_H
