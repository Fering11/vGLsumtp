#include "vgmainwindow.h"
#include "ui_mainwindow.h"
#include "vgmainmenu.h"
vGMainWindow::vGMainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setFocusPolicy(Qt::NoFocus);

	//严格来说，只能有一个widget
	ui->background->addWidget(new vGMainMenu(ui->background, this));
	this->setObjectName(tr("vGMainWidget")); 
	UpdateSkin();
}

vGMainWindow::~vGMainWindow()
{
	delete ui;
}

void vGMainWindow::UpdateSkin()
{
	//对于google眼镜，越黑透明度越高
	this->setStyleSheet(QU8("QWidget#vGMainWidget{background-color:%1;}").
		arg(vGp->Skin().theme.name()));
	//this->setStyleSheet(QU8("QWidget#vGMainWidget{background-image: url(:/MainWindow/Resource/background.jpg);}"));
}

