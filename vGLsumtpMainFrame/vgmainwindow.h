#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FrMenu.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class vGMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	vGMainWindow(QWidget *parent = nullptr);
	~vGMainWindow();
public slots:
	//设置皮肤样式 (这个不是虚函数)
	void UpdateSkin();
private:
	Ui::MainWindow *ui;
	FrMenu* menu;
};
#endif // MAINWINDOW_H
