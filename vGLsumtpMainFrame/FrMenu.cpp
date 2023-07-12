#include "FrMenu.hpp"

// ///////////////////////////  FrMenu ////////////////////////////
////
////

FrMenu::FrMenu(QLayout* _lay, QWidget* _parent):
	FrMenuBase(_lay,_parent)
{
	this->setObjectName("FrMenu");
	setFocusPolicy(Qt::StrongFocus);

	wid_switch = new FrMenuSwitch(this);
	wid_back = new QWidget;

	//应用开启时，先显示主菜单
	wid_switch->show();
	//
	connect(wid_switch, &FrMenuSwitch::activatePlugin, this, &FrMenu::launchPlugin);

	setLayout(new QVBoxLayout);
	layout()->addWidget(wid_switch);
	launchPlugin(FrMenuPlugin);

	//this->setStyleSheet(QU8("QWidget#FrMenu{border-color:rgb(255,0,0);border-style:solid;border-width:5px;}"));
}

void FrMenu::launchPlugin(FrPluginData* _target) {
	//是主窗口一直处于焦点状态，通过焦点代理转移
	this->setFocus();
	if (_target == FrMenuPlugin) {
		background().addWidget(this);
		activity_ = FrMenuPlugin;
		this->show();
		//TODO 处理后台显示界面的焦点代理
		this->setFocusProxy(wid_switch);
	} else if (_target != nullptr) {
		//正常情况，服务插件不会出现在菜单界面上
		if (activity_ == FrMenuPlugin) {
			background().removeWidget(this);
			this->hide();
		}
		if (_target->plugin() != nullptr) {
			if (_target->plugin()->initialize()) {
				//获取QWidget，设置显示
				auto widget = _target->plugin()->widget();
				activity_ = _target;
				widget->show();
				background().addWidget(widget);
				this->setFocusProxy(widget);
				return;
			} else { //插件初始化失败，表明插件异常
				//销毁插件
				_target->release(2000);
			}
		}
		//插件启动失败
		//TODO 完善Dialog提示
		vGMessageBox::error(this, tr("启动插件%1失败!").
			arg(_target->property().name),4000);
		//恢复菜单
		launchPlugin(FrMenuPlugin);
	} else {//错误的参数
		vGlog->error("FrMenu::launchPlugin.An illegal parameter was passed.");
	}
}

void FrMenu::releasePlugin(FrPluginData* _target){

}

void FrMenu::switchPlugin(FrPluginData* _starter, FrPluginData* _destination){

}

void FrMenu::killPlugin(FrPluginData* _target){

}
// ///////////////////////////  FrMenuSwitch ////////////////////////////
////
////

FrMenuSwitch::FrMenuSwitch(FrMenu* _menu):
	QWidget(_menu), frplugin_(),iter_(&frplugin_,0)
{
	updatePlugin();
	this->setObjectName("FrMenuSwitch");
	setFocusPolicy(Qt::StrongFocus);//确保窗体能获得焦点
	
	left_ = new QLabel(this);
	left_->setObjectName("FrMenuSwitchLeft");
	center_ = new QLabel(this);
	center_->setObjectName("FrMenuSwitchCenter");
	right_ = new QLabel(this);
	right_->setObjectName("FrMenuSwitchRight");
	description_ = new QLabel(this);
	description_->setObjectName("FrMenuSwitchDescription");
	//防止自动更改大小
	QSizePolicy size_policy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	size_policy.setHorizontalStretch(0);
	size_policy.setVerticalStretch(0);
	size_policy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
	left_->setSizePolicy(size_policy);
	right_->setSizePolicy(size_policy);
	center_->setSizePolicy(size_policy);
	description_->setSizePolicy(size_policy);
	//使内容居中显示
	left_->setAlignment(Qt::AlignCenter);
	right_->setAlignment(Qt::AlignCenter);
	center_->setAlignment(Qt::AlignCenter);
	description_->setAlignment(Qt::AlignCenter);
	//不获取焦点
	left_->setFocusPolicy(Qt::NoFocus);
	right_->setFocusPolicy(Qt::NoFocus);
	center_->setFocusPolicy(Qt::NoFocus);
	description_->setFocusPolicy(Qt::NoFocus);
	//图片填充
	left_->setScaledContents(true);
	right_->setScaledContents(true);
	center_->setScaledContents(true);

	{
		//TODO 添加设置：显示控件边界
		this->setStyleSheet(QU8("QWidget#FrMenu{border-color:rgb(125,230,20);border-style:solid;border-width:1px;}"));
		left_->setStyleSheet(QU8("QWidget#FrMenuSwitchLeft{border-color:rgb(255,0,0);border-style:solid;border-width:2px;}"));
		center_->setStyleSheet(QU8("QWidget#FrMenuSwitchCenter{border-color:rgb(0,255,0);border-style:solid;border-width:2px;}"));
		right_->setStyleSheet(QU8("QWidget#FrMenuSwitchRight{border-color:rgb(0,0,255);border-style:solid;border-width:2px;}"));
		description_->setStyleSheet(QU8("QWidget#FrMenuSwitchDescription{border-color:rgb(150,100,55);border-style:solid;border-width:2px;}"));
	}

	connect(this, &FrMenuSwitch::updateSize, this, [this](QSize _size) {
		QRect rect[4] = {};
		calculateSize(_size, rect);
		left_->setGeometry(rect[0]);
		center_->setGeometry(rect[1]);
		right_->setGeometry(rect[2]);
		description_->setGeometry(rect[3]);
		});

	updateImage();
}

void FrMenuSwitch::calculateSize(QSize _size, QRect _target[4]){
	const auto window_size = _size.isValid() ? _size : this->rect().size();
	const auto ms_mark = window_size.width() / 10;
	const auto wheight = window_size.height();
	const auto wwidth = window_size.width();
	//Center与其他框有空格
	const auto cen_wid = wwidth - (ms_mark + center_side) * 2;
	//const auto cen_wid = wwidth - ms_mark * 2 - cen_side * 2;
	const auto cen_hei = static_cast<int>(wheight * 0.9) - center_side * 2;
	//左侧
	if (wheight >= ms_mark) {
		_target[0] = { 0,(wheight / 2 - ms_mark / 2),ms_mark ,ms_mark };
		_target[2] = { wwidth - ms_mark,(wheight / 2 - ms_mark / 2) ,ms_mark,ms_mark };
	}
	else {
		_target[0] = { (ms_mark / 2 - wheight / 2),0,wheight,wheight };
		_target[2] = { (wwidth - ms_mark / 2 - wheight / 2),0,wheight,wheight };
	}
	if (cen_wid > cen_hei) {
		_target[1] = { (cen_wid / 2 + 10 + ms_mark) - cen_hei / 2 ,center_side,cen_hei,cen_hei };
	}
	else {
		//这个是没有计算的结果，会导致无法维持正方形状态
		//TODO 计算精准的数值
		_target[1] = { ms_mark, 0, wwidth - ms_mark * 2, static_cast<int>(wheight * 0.9) };
	}
	_target[3] = { ms_mark, static_cast<int>(wheight * 0.9), wwidth - ms_mark * 2, wheight / 10 };

	
}

bool FrMenuSwitch::advance(){
	if (!iter_.vaild()) {
		//未经初始化而操作，忽略
		vGlog->warn("FrMenuSwitch::advance.The object was not initialized and performed an unexpected operation");
		return false;
	}
	++iter_;
	return true;
}

bool FrMenuSwitch::retreat(){
	if (!iter_.vaild()) {
		//未经初始化而操作，忽略
		vGlog->warn("FrMenuSwitch::advance.The object was not initialized and performed an unexpected operation");
		return false;
	}
	--iter_;
	return true;
}

void FrMenuSwitch::updatePlugin(){
	frplugin_ = vGp->pluginManager().plugins();
	iter_ = vIterator(&frplugin_, 0);
}

void FrMenuSwitch::updateImage() {
	this->setUpdatesEnabled(false);
	left_->setPixmap((*iter_)->property().logo);
	center_->setPixmap((*(iter_ + 1))->property().logo);
	right_->setPixmap((*(iter_ + 2))->property().logo);
	description_->setText(QU8("<font size=10>%1</font>").arg((iter_+1)->data()->property().description));
	this->setUpdatesEnabled(true);
}

void FrMenuSwitch::keyPressEvent(QKeyEvent* _event)
{
	switch (_event->key()) {
	case Qt::Key_Left:
	case Qt::Key_A: {
		retreat();
		break;
	}
	case Qt::Key_Right:
	case Qt::Key_D: {
		advance();
		break;
	}
	case Qt::Key_Return:
	case Qt::Key_Enter: {
		//启动插件，通知FrMenu处理
		emit activatePlugin((iter_ + 1)->data());
		break;
	}
	default:
		QWidget::keyPressEvent(_event);
		return; //其他事件不做UI更新
	}
	updateImage();
}

void FrMenuSwitch::resizeEvent(QResizeEvent* _event){
	emit updateSize(_event->size());
	vGlog->info("FrMenuSwitch::resizeEvent");
	QWidget::resizeEvent(_event);
}
