#pragma once
#include "vghead.hpp"
#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <deque>
#include <QEvent>
#include <QKeyEvent>
#include <QResizeEvent> 
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QGraphicsOpacityEffect>
#include <QOpenGLWidget>
#define __FONT 0
class vGLMenu : public QMainWindow
{
    Q_OBJECT
public:
	using App_type = QWidget;
	vGLMenu(QWidget *parent = nullptr);
    ~vGLMenu();

	vGImageLabel* left();
	vGImageLabel* center();
	vGImageLabel* right();
	vGImageLabel* left() const;
	vGImageLabel* center() const;
	vGImageLabel* right() const;
	//设置都是操作队列，对显示内容不会更换
	//setPos是在原来的基础上进行增减
	void setPos(int _size);
	void add();
	void sub();
	//加上3的倍数一样
	unsigned int getPos() const;
	enum Action {
		Resize = 0,//重新调整大小
		Left = 1, //方向，向左流
		Right = 2
	};
	quint16 duration()const;
	QEasingCurve::Type easingCurve()const;
public slots:
	virtual void updateLayout(Action _action);
	void setDuration(quint16 _ms);
	void setEasingCurve(QEasingCurve::Type _type);
protected:
	virtual void resizeEvent(QResizeEvent* event);
private:
	/*
	* WARNING:
	* 不建议直接使用left_ center_ right_对象，他们的位置
	* 是绝对的，建议用取值函数
	*/
	mutable QLabel* description_ = nullptr;
	//mutable vGImageLabel* left_ = nullptr;
	//mutable vGImageLabel* center_ = nullptr;
	//mutable vGImageLabel* right_ = nullptr;
	mutable vGImageLabel* buff_ = nullptr;
	QGraphicsOpacityEffect* left_oe_;
	QGraphicsOpacityEffect* center_oe_;
	QGraphicsOpacityEffect* right_oe_;
	QGraphicsOpacityEffect* buff_oe_;
	std::deque<vGImageLabel*> labs_;
	quint16 duration_time_;
	quint8 easing_curve_;
	quint8 now_pos_;
};

class vGLData :public vGLMenu {

	Q_OBJECT

public:
	using iter = vIterator<std::vector<QPixmap>>;
	vGLData(QWidget* _parent = nullptr) :
		vGLMenu(_parent), pos_(0) {
		for (auto i = 1; i != 8; i++) {
			QPixmap pix(QString::fromUtf8(":/vGLMenu/b%1.png").arg(i));
			pix_.push_back(std::move(pix));
		}
		//确保在调用updateLayout之前label有图片数据
		iter it(&pix_, pos_);
		left()->setPixmap(*it);
		center()->setPixmap(*(it + 1));
		right()->setPixmap(*(it + 2));

		setFocusPolicy(Qt::StrongFocus);
	}
	~vGLData() {

	}
protected:
	virtual void keyPressEvent(QKeyEvent* _event) {
		switch (_event->key())
		{
		case Qt::Key_A: {
			sub();

			++pos_;
			iter it(&pix_, pos_);
			left()->setNextPixmap(*it);
			center()->setNextPixmap(*(it + 1));
			right()->setNextPixmap(*(it + 2));

 			updateLayout(Left); 
			break;
		}
		case Qt::Key_D: {
			add();

			//上面两个必加

			--pos_;
			iter it(&pix_, pos_);
			left()->setNextPixmap(*it);
			center()->setNextPixmap(*(it + 1));
			right()->setNextPixmap(*(it + 2));
			updateLayout(Right);
			break;
		}
		default:
			break;
		}
		vGLMenu::keyPressEvent(_event);
	}
private:
	std::vector<QPixmap> pix_;
	int pos_;
};