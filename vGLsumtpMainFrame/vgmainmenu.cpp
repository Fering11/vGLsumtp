#include "vgmainmenu.h"
#include "vghead.hpp"
vGMainMenu::vGMainMenu(QLayout* _back, QWidget* parent) :
	vGMenuBase(parent, _back), item_pos_(0), private_(new vGMainMenu_Private(this))
{
	setObjectName("vGMainMenu");

	vIterator it(&vGp->fPlugins(), itemPos());
	//vIterator it(&vGp->Plugins(), itemPos());
	left()->setPixmap((*it)->logo());
	center()->setPixmap((*(it + 1))->logo());
	right()->setPixmap((*(it + 2))->logo());
	description()->setText((*(it + 1))->description());
	//读取配置里的
	setDuration(vGp->Config().base().duration_time);
	setEasingCurve(QEasingCurve::Type(vGp->Config().base().easing_curve));


	//信号槽触发顺序按照定义的连接顺序
	emit update_skin();
	//消息框问候语
	setGeometry(parent->rect());
	vGMessageBox::info(this, tr("<font size=10>Welcome to <font color=\"#007d65\">vGLsumtp</font></font>"), 5000);
	vGMessageBox::warning(this, tr("this is warning box"));
	vGMessageBox::error(this, tr("this is error box"));
	vGMessageBox::success(this, tr("this is success box"));
	//vGMessageBox* box = new vGMessageBox(this, Info);
	//box->setText(tr("<font size=12>Welcome to <font color=\"#007d65\">vGLsumtp</font></font>"));
	//box->setTime(5000);
	//box->raise();
	//box->show();
}

vGMainMenu::~vGMainMenu()
{
}
void vGMainMenu::UpdateSkin()
{
	//this->setStyleSheet(QU8("QWidget#vGMainMenu{background-color:%1;}").
	//	arg(vGp->Skin().menu.background.name()));
	
	vGMenuBase::UpdateSkin();
	//this->setStyleSheet(QU8("background-color:%1;").
	//	arg(vGp->Skin().menu.background.name()));
}

void vGMainMenu::UpdateLayout(Action _action, QSize _new_size)
{
	switch (_action)
	{
	case Action::Enter: {
		if (front_.isNull()) {
			//空值为错误
			DebugBox("error", "nullptr in updateLayout");
			return;
		}
		//主窗口全部隐藏
		setFocusPolicy(Qt::NoFocus);
		//隐藏上一个
		//TODO delete me 
		if(last_app_!=this)
			last_app_->hide();
		break;
	}
	case Action::Escape: {
		//可能是因为close或者被替换
		setFocusPolicy(Qt::StrongFocus);
	}
	default:
		break;
	}
	vGMenuBase::UpdateLayout(_action, _new_size);
}
void vGMainMenu::ac_turnLeft()
{
	add();

	//vIterator it(&vGp->Plugins(), itemPos() - 1);
	//item_pos_ = it.pos();
	//left()->setNextPixmap((*it)->info().logo);
	//center()->setNextPixmap((*(it + 1))->info().logo);
	//right()->setNextPixmap((*(it + 2))->info().logo);
	//description()->setText((*(it + 1))->info().description);

	vIterator it(&vGp->fPlugins(), itemPos()-1);
	//vIterator it(&vGp->Plugins(), itemPos());
	left()->setNextPixmap((*it)->logo());
	center()->setNextPixmap((*(it + 1))->logo());
	right()->setNextPixmap((*(it + 2))->logo());
	description()->setText((*(it + 1))->description());

	UpdateLayout(Right);
}
void vGMainMenu::ac_turnRight()
{
	sub();

	//vIterator it(&vGp->Plugins(), itemPos() + 1);
	//item_pos_ = it.pos();
	//left()->setNextPixmap((*it)->info().logo);
	//center()->setNextPixmap((*(it + 1))->info().logo);
	//right()->setNextPixmap((*(it + 2))->info().logo);
	//description()->setText((*(it + 1))->info().description);

	vIterator it(&vGp->fPlugins(), itemPos()+1);
	//vIterator it(&vGp->Plugins(), itemPos());
	left()->setNextPixmap((*it)->logo());
	center()->setNextPixmap((*(it + 1))->logo());
	right()->setNextPixmap((*(it + 2))->logo());
	description()->setText((*(it + 1))->description());

	UpdateLayout(Left);
}
void vGMainMenu::ac_enter()
{
	vGp->mt_plugin.lock();
	vIterator it(&vGp->Plugins(), itemPos() + 1);
	auto plugin = (vGp->Plugins()[it.pos()]);
	//已经创建了就不会重复创建
	plugin->create(this);
	vGp->mt_plugin.unlock();
	if (front_.isNull()) {
	} else {
		//也可以将其关入后台
		DebugBox("enter again","enter");
	}
	LaunchWidget(plugin->app());
}
void vGMainMenu::keyPressEvent(QKeyEvent* _event){
	//有前台窗口时，不接受键盘信息
	if (!front_.isNull())return;
	switch (_event->key())
	{
	case Qt::Key_Right:
	case Qt::Key_D: {
		ac_turnRight();
		break;
	}
	case Qt::Key_Left:
	case Qt::Key_A: {
		ac_turnLeft();
		break;
	}
	case Qt::Key_Return:
	case Qt::Key_Enter: {
		ac_enter();
		break;
	}
	case Qt::Key_Escape: {
		ReleaseWindow(front_);
		break;
	}
	default:
		break;
	}
	vGMenuBase::keyPressEvent(_event); 
}
QAbstractAnimation* vGMainMenu::__ac_enter(QSize _size)
{
	//TODO last_app 与 this 区分
	//效果:主窗口逐渐隐藏，子窗口从上面滑下
	const auto ws = _size.isValid() ? _size : this->rect().size();
	QRect rect(0, -ws.height(), ws.width(), ws.height());
	buff()->setGeometry(QRect(-2, -2, 1, 1));

	QPropertyAnimation* aopa = new QPropertyAnimation(this, "allOpacity");
	aopa->setDuration(duration());
	aopa->setEasingCurve(easingCurve());
	aopa->setStartValue(1);
	aopa->setEndValue(0);

	QPropertyAnimation* fspa = new QPropertyAnimation(private_, "front_show");
	fspa->setDuration(1);//瞬间变化
	fspa->setEasingCurve(easingCurve());
	fspa->setStartValue(0);
	fspa->setEndValue(1);

	QPropertyAnimation* fgpa = new QPropertyAnimation(front_, "geometry");
	fgpa->setDuration(duration());
	fgpa->setEasingCurve(easingCurve());
	fgpa->setStartValue(rect);
	fgpa->setEndValue(QRect(0, 0, ws.width(), ws.height()));
	QParallelAnimationGroup* pa_group = new QParallelAnimationGroup(this);
	pa_group->addAnimation(aopa);
	pa_group->addAnimation(fgpa);
	pa_group->addAnimation(fspa);
	//pa_group->finished
	return pa_group;
}
QAbstractAnimation* vGMainMenu::__ac_escape(QSize _size)
{
	//效果:子窗口从中间滑上，主窗口逐渐显示
	auto* result = new QSequentialAnimationGroup(this);
	auto backward_enter = __ac_enter(_size);
	//backward_enter->setDirection(QParallelAnimationGroup::Backward);
	
	connect(backward_enter, &QParallelAnimationGroup::finished, this, [this]() {
		front_ = nullptr;
		});
	//return backward_enter;
	result->addAnimation(backward_enter);
	result->setDirection(QParallelAnimationGroup::Backward);
	//auto* resize_an = __ac_resize(_size);
	//result->addAnimation(resize_an);
	return result;
}
void vGMainMenu::ReleaseWindow(vGAppWidBase* _object) {
	if (_object && front_ == _object) {
		UpdateLayout(Action::Escape);
		//xfront_ = nullptr;
	}
#if 0
	//背景不为空
	if (!background_.isNull() && _object && front_ == _object) {
		background_->removeWidget(_object);
		_object->setVisible(false);
		_object->setFocusPolicy(Qt::NoFocus); //释放焦点聚焦
		this->setVisible(true);
		this->setFocusPolicy(Qt::StrongFocus);
		//x_object->releaseKeyboard();
		//x_object->releaseMouse();
		front_ = nullptr;
	}
#endif 
}
void vGMainMenu::LaunchWidget(vGAppWidBase* _object) {
	//已经有前台就不干
	//TODO 提取共同部分
	if (front_.isNull()) {
		last_app_ = this;
	} else {
		last_app_ = front_;
	}
	mt_uia.lock();
	ui_ac_.insert(_object->plugin());
	mt_uia.unlock();

	front_ = _object;
	UpdateLayout(Enter);
#if 0
	if (!front_) {
		front_ = _object;
		this->setVisible(false); //隐藏，后添加
		this->setFocusPolicy(Qt::NoFocus); //无焦点状态
		_object->setVisible(true);
		_object->setFocusPolicy(Qt::StrongFocus);
		background_->addWidget(_object);
		//x_object->grabKeyboard(); //聚焦
		//x_object->grabMouse();
	} else {
		//这样做会使焦点聚焦到菜单上
		//TODO 日志记录完善
		//DebugBox("warn", "front window is exist!");
	}
#endif
}


vGMainMenu_Private::vGMainMenu_Private(vGMainMenu* _parent):
	QObject(_parent)
{

}

quint32 vGMainMenu_Private::front_show()
{
	return vp()->front_->isVisible();//true or false
}

void vGMainMenu_Private::set_front_show(qint32 _value)
{
	_value = _value <= 0 ? 0 : 1;
	qDebug() << _value;
	vp()->front_->setVisible(_value);
}

vGMainMenu* vGMainMenu_Private::vp()
{
	return reinterpret_cast<vGMainMenu*>(this->parent());
}
