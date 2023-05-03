/*
*  vGHead.cpp 
* 
*/
#include "vghead.hpp"
#include "FrPlugin.hpp"
// ///////////////////全局变量
std::deque<vGMessageBox*> vGMessageBox::__mb_msg_box_deque; //信息框队列
std::shared_mutex vGMessageBox::__mb_mt_msg;
//static std::deque<vGMessageBox*> __mb_msg_box_deque; //信息框队列
//static std::shared_mutex __mb_mt_msg;
// //////////// vGImageLabel ///////////////////////
vGImageLabel::vGImageLabel(QWidget* _parent) :
	QLabel(_parent)
{
	pix_ = nullptr;
}

// //////////// vGMenuBase ///////////////////////////////////////
void __set_opacity(QLabel* _lab, qreal _re) {
	((QGraphicsOpacityEffect*)_lab->graphicsEffect())->setOpacity(_re);
}

vGMenuBase::vGMenuBase(QWidget* _parent, QLayout* _back) :
	QWidget(_parent), front_(nullptr), now_pos_(0), easing_curve_(0),
	duration_time_(0), ui_ac_()
{
	//设置主菜单地址
	vGp->setMenu(this);

	background_ = _back;
	//绑定刷新皮肤信号
	connect(this, &vGMenuBase::update_skin, this, &vGMenuBase::UpdateSkin);
	this->setObjectName("vGMainMenu");
	__initialize_ui(); //界面初始化和动画处理
	setFocusPolicy(Qt::StrongFocus); //仅仅是底层UI界面
}

vGMenuBase::~vGMenuBase(){}
void vGMenuBase::__initialize_ui() {
	now_pos_ = 0;

	vGImageLabel* left_ = nullptr;
	vGImageLabel* center_ = nullptr;
	vGImageLabel* right_ = nullptr;
	left_ = new vGImageLabel(this);
	left_->setObjectName("left");

	center_ = new vGImageLabel(this);
	center_->setObjectName("center");

	right_ = new vGImageLabel(this);
	right_->setObjectName("right");

	description_ = new vGImageLabel(this);
	description_->setObjectName("description");

	buff_ = new vGImageLabel(this);
	buff_->setObjectName("buff");

	labs_.assign({ left_, center_,right_ });

	//不自动变化大小
	QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
	left_->setSizePolicy(sizePolicy);
	center_->setSizePolicy(sizePolicy);
	right_->setSizePolicy(sizePolicy);
	description_->setSizePolicy(sizePolicy);
	buff_->setSizePolicy(sizePolicy);
	//内容居中显示
	left_->setAlignment(Qt::AlignCenter);
	right_->setAlignment(Qt::AlignCenter);
	center_->setAlignment(Qt::AlignCenter);
	description_->setAlignment(Qt::AlignCenter);
	buff_->setAlignment(Qt::AlignCenter);
	//图片填充
	left_->setScaledContents(true);
	right_->setScaledContents(true);
	center_->setScaledContents(true);
	description_->setScaledContents(true);
	buff_->setScaledContents(true);
	//透明度代理
	left_oe_ = new QGraphicsOpacityEffect(left_);
	left_->setGraphicsEffect(left_oe_);

	center_oe_ = new QGraphicsOpacityEffect(center_);
	center_->setGraphicsEffect(center_oe_);

	right_oe_ = new QGraphicsOpacityEffect(right_);
	right_->setGraphicsEffect(right_oe_);

	buff_oe_ = new QGraphicsOpacityEffect(buff_);
	buff_->setGraphicsEffect(buff_oe_);

	desc_oe_ = new QGraphicsOpacityEffect(description_);
	description_->setGraphicsEffect(desc_oe_);

	//easing_curve_ = QEasingCurve::Type::InOutCirc;
	//duration_time_ = 500;
}
void vGMenuBase::setAllOpacity(qreal _num){
	left_oe_->setOpacity(_num);
	center_oe_->setOpacity(_num);
	right_oe_->setOpacity(_num);
	buff_oe_->setOpacity(_num);
	desc_oe_->setOpacity(_num);
}
void vGMenuBase::setEbOpacity(qreal _num) {
	left_oe_->setOpacity(_num);
	center_oe_->setOpacity(_num);
	right_oe_->setOpacity(_num);
	desc_oe_->setOpacity(_num);
}
void vGMenuBase::setParallel(QAbstractAnimation* _p){
	//删除现在正在播放的动画
	if (!para_ag.isNull()) {
		//emit para_ag->finished();
		para_ag->deleteLater();
	}
	para_ag = _p;
}
QAbstractAnimation* vGMenuBase::__ac_left(QSize _size)
{
	//这是UI上控件的位置
	auto la_left = right();
	auto la_center = left();
	auto la_right = center();
	QRect position[4];

	__get_layout(_size, position);
	//TODO 为description添加动画
	description_->setGeometry(position[3]);

	//隐藏la_left,buff_替代
	__set_opacity(buff_, 0);
	buff_->setGeometry(la_left->rect());
	buff_->setPixmap(*la_left->pixmap());
	__set_opacity(buff_, 1);
	__set_opacity(la_left, 0);

	la_left->setPixmap(*la_left->nextPixmap());
	la_center->setPixmap(*la_center->nextPixmap());
	la_right->setPixmap(*la_right->nextPixmap());
	//大小变化
	QPropertyAnimation* cpag = new QPropertyAnimation(la_center, "geometry");
	QPropertyAnimation* rpag = new QPropertyAnimation(la_right, "geometry");
	//left和buff同步变化
	QPropertyAnimation* lpag = new QPropertyAnimation(la_left, "geometry");
	QPropertyAnimation* bpag = new QPropertyAnimation(buff_, "geometry");

	lpag->setDuration(duration_time_);
	bpag->setDuration(duration_time_);
	cpag->setDuration(duration_time_);
	rpag->setDuration(duration_time_);

	lpag->setEasingCurve(easingCurve());
	bpag->setEasingCurve(easingCurve());
	cpag->setEasingCurve(easingCurve());
	rpag->setEasingCurve(easingCurve());

	lpag->setStartValue(position[0]);
	bpag->setStartValue(position[0]);
	cpag->setStartValue(position[1]);
	rpag->setStartValue(position[2]);

	//Left ---> Right
	lpag->setEndValue(position[2]);
	bpag->setEndValue(position[2]);
	//Center ---> Left
	cpag->setEndValue(position[0]);
	//Right ---> Center
	rpag->setEndValue(position[1]);

	//添加 Left ---> Right时的透明度变化
	//隐藏buff_       1->0
	QPropertyAnimation* bpaop0 = new QPropertyAnimation(buff_->graphicsEffect(), "opacity", left());
	bpaop0->setDuration(duration_time_ / 2);
	bpaop0->setStartValue(1);
	bpaop0->setEndValue(0);
	bpaop0->setEasingCurve(easingCurve());
	//显示left_       0->1
	QPropertyAnimation* rpaop1 = new QPropertyAnimation(la_left->graphicsEffect(), "opacity", left());
	rpaop1->setDuration(duration_time_ / 2);
	rpaop1->setStartValue(0);
	rpaop1->setEndValue(1);
	rpaop1->setEasingCurve(easingCurve());
	//队列动画
	QSequentialAnimationGroup* rpaop_seq = new QSequentialAnimationGroup(this);
	rpaop_seq->addAnimation(bpaop0);
	rpaop_seq->addAnimation(rpaop1);

	//总队列
	QParallelAnimationGroup* pa_group = new QParallelAnimationGroup(this);

	pa_group->addAnimation(rpaop_seq);
	pa_group->addAnimation(bpag);
	pa_group->addAnimation(cpag);
	pa_group->addAnimation(rpag);
	pa_group->addAnimation(lpag);
	return pa_group;
}
QAbstractAnimation* vGMenuBase::__ac_right(QSize _size) {
	auto la_left = center();
	auto la_center = right();
	auto la_right = left();
	QRect position[4];

	__get_layout(_size,position);
	//TODO 为description添加动画
	description_->setGeometry(position[3]);
	 //隐藏la_left,buff_替代
	__set_opacity(buff_, 0);
	buff_->setGeometry(la_right->rect());
	buff_->setPixmap(*la_right->pixmap());
	__set_opacity(buff_, 1);
	__set_opacity(la_right, 0);

	la_left->setPixmap(*la_left->nextPixmap());
	la_center->setPixmap(*la_center->nextPixmap());
	la_right->setPixmap(*la_right->nextPixmap());
	//大小变化
	QPropertyAnimation* lpag = new QPropertyAnimation(la_left, "geometry");
	QPropertyAnimation* cpag = new QPropertyAnimation(la_center, "geometry");
	//right与buff_同步变化
	QPropertyAnimation* rpag = new QPropertyAnimation(la_right, "geometry");
	QPropertyAnimation* bpag = new QPropertyAnimation(buff_, "geometry");

	lpag->setDuration(duration_time_);
	cpag->setDuration(duration_time_);
	rpag->setDuration(duration_time_);
	bpag->setDuration(duration_time_);

	lpag->setEasingCurve(easingCurve());
	cpag->setEasingCurve(easingCurve());
	rpag->setEasingCurve(easingCurve());
	bpag->setEasingCurve(easingCurve());

	lpag->setStartValue(position[0]);
	cpag->setStartValue(position[1]);
	rpag->setStartValue(position[2]);
	bpag->setStartValue(position[2]);

	//Left ---> Center
	lpag->setEndValue(position[1]);
	//Center ---> rigth
	cpag->setEndValue(position[2]);
	//Right ---> Left
	rpag->setEndValue(position[0]);
	bpag->setEndValue(position[0]);

	//Buff_逐渐变得透明
	QPropertyAnimation* rpaop0 = new QPropertyAnimation(buff_->graphicsEffect(), "opacity", left());
	rpaop0->setDuration(duration_time_ / 2);
	rpaop0->setStartValue(1);
	rpaop0->setEndValue(0);
	rpaop0->setEasingCurve(easingCurve());
	 //right变得明显
	QPropertyAnimation* rpaop1 = new QPropertyAnimation(la_right->graphicsEffect(), "opacity", left());
	rpaop1->setDuration(duration_time_ / 2);
	rpaop1->setStartValue(0);
	rpaop1->setEndValue(1);
	rpaop1->setEasingCurve(easingCurve());
	//队列动画
	QSequentialAnimationGroup* rpaop_seq = new QSequentialAnimationGroup(this);
	rpaop_seq->addAnimation(rpaop0);
	rpaop_seq->addAnimation(rpaop1);

	//总队列
	QParallelAnimationGroup* pa_group = new QParallelAnimationGroup(this);

	pa_group->addAnimation(rpaop_seq);
	pa_group->addAnimation(cpag);
	pa_group->addAnimation(rpag);
	pa_group->addAnimation(lpag);
	pa_group->addAnimation(bpag);
	return pa_group;
}
QAbstractAnimation* vGMenuBase::__ac_resize(QSize _size) {
	auto la_left = left();
	auto la_center = center();
	auto la_right = right();
	QRect position[4];
	__get_layout(_size, position);

	const QRect& ll = position[0];
	const QRect& lc = position[1];
	const QRect& lr = position[2];
	const QRect& ld = position[3];
	//避免按太快导致透明度没完全恢复
	//TODO 不直接实现
	//left_oe_->setOpacity(1);
	//center_oe_->setOpacity(1);
	//right_oe_->setOpacity(1);
	buff_oe_->setOpacity(0); //确保处于隐藏状态 
	//大小变化
	QPropertyAnimation* tpag = new QPropertyAnimation(this, "ebOpacity");
	QPropertyAnimation* lpag = new QPropertyAnimation(la_left, "geometry");
	QPropertyAnimation* cpag = new QPropertyAnimation(la_center, "geometry");
	QPropertyAnimation* rpag = new QPropertyAnimation(la_right, "geometry");
	QPropertyAnimation* dpag = new QPropertyAnimation(description_, "geometry");

	lpag->setDuration(duration_time_);
	cpag->setDuration(duration_time_);
	rpag->setDuration(duration_time_);
	dpag->setDuration(duration_time_);
	tpag->setDuration(duration_time_);

	lpag->setEasingCurve(easingCurve());
	cpag->setEasingCurve(easingCurve());
	rpag->setEasingCurve(easingCurve());
	dpag->setEasingCurve(easingCurve());
	tpag->setEasingCurve(easingCurve());

	lpag->setEndValue(ll);
	cpag->setEndValue(lc);
	rpag->setEndValue(lr);
	dpag->setEndValue(ld);
	tpag->setEndValue(1);//不管开始值

	QParallelAnimationGroup* pa_group = new QParallelAnimationGroup(this);

	pa_group->addAnimation(cpag);
	pa_group->addAnimation(rpag);
	pa_group->addAnimation(lpag);
	pa_group->addAnimation(dpag);
	pa_group->addAnimation(tpag);
	return pa_group;
}
QAbstractAnimation* vGMenuBase::__ac_enter(QSize _size){
	QParallelAnimationGroup* pa_group = new QParallelAnimationGroup(this);
	return pa_group;
}
QAbstractAnimation* vGMenuBase::__ac_escape(QSize _size){
	QParallelAnimationGroup* pa_group = new QParallelAnimationGroup(this);
	return pa_group;
}
void vGMenuBase::__get_layout(QSize _size, QRect _re[4]) {
	const auto window_size = _size.isValid() ? _size : this->rect().size();
	const auto ms_mark = window_size.width() / 10;
	const auto wheight = window_size.height();
	const auto wwidth = window_size.width();
	//Center与其他框有空格 10
	const auto cen_wid = wwidth - (ms_mark + center_side) * 2;
	//const auto cen_wid = wwidth - ms_mark * 2 - cen_side * 2;
	const auto cen_hei = static_cast<int>(wheight * 0.9) - center_side * 2;
	//左侧
	if (wheight >= ms_mark) {
		_re[0] = {0,(wheight / 2 - ms_mark / 2),ms_mark ,ms_mark};
		_re[2] = {wwidth - ms_mark,(wheight / 2 - ms_mark / 2) ,ms_mark,ms_mark};
	} else {
		_re[0] = {(ms_mark / 2 - wheight / 2),0,wheight,wheight};
		_re[2] = {(wwidth - ms_mark / 2 - wheight / 2),0,wheight,wheight};
	}
	if (cen_wid > cen_hei) {
		_re[1] = {(cen_wid / 2 + 10 + ms_mark) - cen_hei / 2 ,center_side,cen_hei,cen_hei};
	} else {
		//不想算了
		_re[1] = {ms_mark, 0, wwidth - ms_mark * 2, static_cast<int>(wheight * 0.9)};
	}
	_re[3] = { ms_mark, static_cast<int>(wheight * 0.9), wwidth - ms_mark * 2, wheight / 10 };
}
void vGMenuBase::UpdateLayout(vGMenuBase::Action _action, QSize _size) {

	left_oe_->setOpacity(1);
	center_oe_->setOpacity(1);
	right_oe_->setOpacity(1);
	switch (_action)
	{
	case Left: {
		setParallel(__ac_left(_size));//->start(QParallelAnimationGroup::DeleteWhenStopped);
		break;
	}
	case Right: {
		setParallel (__ac_right(_size));// ->start(QParallelAnimationGroup::DeleteWhenStopped);
		break;
	}
	case Resize: {
		setParallel(__ac_resize(_size));// ->start(QParallelAnimationGroup::DeleteWhenStopped);
		break;
	}
	case Enter: {
		setParallel(__ac_enter(_size));
		break;
	}
	case Escape: {
		setParallel(__ac_escape(_size));
		break;
	}
	default:
		//啥也不做
		break;
		
	}
	if(!para_ag.isNull())
		para_ag->start();
	//注:更新布局不需要更新皮肤
	//xemit update_skin();
}
void vGMenuBase::resizeEvent(QResizeEvent* _event)
{
	//如果有前台的话，就只更新前台
	if (!front_.isNull()) {
		front_->resize(_event->size());
	} else {
		UpdateLayout(Resize, _event->size());
	}
}
unsigned int vGMenuBase::getPos() const {
	return now_pos_;
}
quint16 vGMenuBase::duration() const
{
	return duration_time_;
}
QEasingCurve::Type vGMenuBase::easingCurve() const
{
	return QEasingCurve::Type(easing_curve_);
}
void vGMenuBase::setDuration(quint16 _ms)
{
	duration_time_ = _ms;
}
void vGMenuBase::setEasingCurve(QEasingCurve::Type _type)
{
	easing_curve_ = _type;
}
vGImageLabel* vGMenuBase::left() {
	return labs_.front();
}
vGImageLabel* vGMenuBase::center() {
	return labs_.at(1);
}
vGImageLabel* vGMenuBase::right() {
	return labs_.back();
}
vGImageLabel* vGMenuBase::left() const {
	return labs_.front();
}
vGImageLabel* vGMenuBase::center() const {
	return labs_.at(1);
}
vGImageLabel* vGMenuBase::right() const {
	return labs_.back();
}
void vGMenuBase::add() {
	setPos(1);
}
void vGMenuBase::sub() {
	setPos(-1);
}
void vGMenuBase::setPos(int _size) {
	int real_size = _size % 3;//3个lab
	//data_pos_ = real_size;
	if (real_size < 0)
		real_size += 3;
	if (real_size == 1) {
		vGImageLabel* back = labs_.back();
		labs_.pop_back();
		labs_.push_front(back);
	} else if (real_size == 2) {
		vGImageLabel* front = labs_.front();
		labs_.pop_front();
		labs_.push_back(front);
	} else {
		//=0
	}
	now_pos_ = (now_pos_ + real_size) % 3;
}
void vGMenuBase::UpdateSkin() {
	this->setStyleSheet(QU8("vGImageLabel#%2{border-color:%1;border-style:solid;border-width:1px;}").
		arg(vGp->Skin().menu.background.name(), center()->objectName()));
}
void vGMenuBase::keyPressEvent(QKeyEvent* _event)
{
	switch (_event->key())
	{
	case Qt::Key_Escape: {
		//构造函数已经保证每个插件都已经初始化
		//ReleaseWindow(GetFrontApp());
		break;
	}
	case Qt::Key_Return: {
		//vIterator it(&vGp->Plugins(), GetItemPos());
		//LaunchWidget(it->app());

		break;
	}
	default:
		QWidget::keyPressEvent(_event);
		return;
	}
}
QPointer<vGAppWidBase> vGMenuBase::GetFrontApp() const{
	return front_;
}
void vGMenuBase::kill()
{
	delete this;
}
bool vGMenuBase::event(QEvent* _event)
{
	
	return QWidget::event(_event);
}
/////////////////// VGAPPWIDBASE ////////////////////////////////////////
// 
// JUST A CROSS LINE 
//
vGAppWidBase::vGAppWidBase(vGMenuBase* _parent, vGPlugin* _plugin) :
	QWidget(_parent), plugin_(_plugin)
{
	//不给QWidget删除是因为防止vGMenuBase析构时顺带把插件也给析构了，插件的生命周期于vGApp差不多
	setVisible(false);
	setFocusPolicy(Qt::NoFocus);
	//setAttribute(Qt::WA_DeleteOnClose);
	//当窗口关闭时，自动通知主菜单
	connect(this, &vGAppWidBase::CloseApp, _parent, &vGMenuBase::ReleaseWindow);
	connect(this, &vGAppWidBase::update_skin, this, &vGAppWidBase::UpdateSkin);
	//主窗口刷新皮肤时，子控件跟着刷新
	connect(_parent, &vGMenuBase::update_skin, this, &vGAppWidBase::UpdateSkin);
	//确保plugin存在
	if (!plugin_) {
		vGlog->critical("{:d} |vGAppWidBase: Illegal parameter [plugin_ == nullptr]", _AE_FUNC_PARAM);
		throw FrError(FrErrorStatue::InvalidParameter, "vGAppWidBase: Illegal parameter [plugin_ == nullptr]");
	}

}


void vGAppWidBase::keyPressEvent(QKeyEvent* _event){
	switch (_event->key())
	{
	case Qt::Key_Escape: {
		//TODO 可以做窗口关闭处理事件
		//关闭窗口
		menu()->ReleaseWindow(this);
		break;
	}
	default:
		QWidget::keyPressEvent(_event);
		break;
	}
}
const vGPluginInfo* vGAppWidBase::info() const{
	return &plugin_->info();
}

vGAppWidBase::~vGAppWidBase(){
	//App销毁时，从vGapp里删除
	std::lock_guard lck(vGp->mt_plugin);
	auto& pl = vGp->Plugins();
	auto it = std::find_if(vGp->Plugins().begin(), vGp->Plugins().end(), [this](const vGPlugin* _pl) {
		return _pl->app() == this;
		});
	if (it != pl.end()) {
		pl.erase(it);
	}
}

vGMenuBase* vGAppWidBase::menu(){
	return reinterpret_cast<vGMenuBase*>(this->parent());
}
//TODO 再次获取Info会有性能损耗
void vGAppWidBase::UpdateSkin() {
	//不做处理
	vGlog->info("'{}':Update Skin",QSTD(info()->app_name));
}

vGPluginInfo* vGAppWidBase::_info(){
	return &plugin_->info_;
}

void vGAppWidBase::closeEvent(QCloseEvent* event)
{
	//发送关闭消息
	emit CloseApp(this);
	QWidget::closeEvent(event);
}

// //////////// COMMAND_PARSE ////////////////////////////
namespace command_parse {
//默认日志文件相对路径(不判断是否正确)
QString get_log_file() {
	return vGp->Config().base().log_path + QDateTime::currentDateTime().toString("/yyMMddhh(mmsszzz).log");
}
//range [begin,end)
template<qlonglong begin, qlonglong end>
bool range_check(qlonglong _cur) {
	if (begin <= _cur && _cur < end) {
		return true;
	}
	return false;
}
template<class _Ty>
auto copy_integer(_Ty&& _arg) {
	return [&_arg](qlonglong _input)->void {
		if (_input < std::numeric_limits<std::decay_t<_Ty> >::max()) {
			_arg = _input;
		}
	};
}
//命令解析
//返回上次错误信息(可能没有)
std::shared_ptr<nlohmann::json> QCommandParse(vGApp& _object) {
	QCommandLineParser parser;
	QList<QCommandLineOption> lo;
	lo.append({ "restart-count", "The number of restarts", "number", "" });
	lo.append({ "log-file", "The location of the log files and the parent folder are not automatically created", "path","" });
	lo.append({ "log-level", "The number of log'level [0,7]", "number", "" });
	lo.append({ "log-size", "The  maximum size of log file (KB) [1,limit)", "number", "" });
	lo.append({ "log-count", "The maximum number of log file(0 means no limit)", "number", "" });
	lo.append({ "error-json", "", "", R"({"code":0,"msg":"","exit_code":0})" });
	//parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
	parser.addOptions(lo);
	auto& out = _object._getInfo()->msg_buf;
	std::shared_ptr<nlohmann::json> result(new nlohmann::json(nlohmann::json::parse(R"({"code":0,"msg":""})")));
#if 0
	if (!parser.parse({ "--restart-count","3",
		 "--log-file","./log/default.log",
		"--log-level" ,"1",
		"--log-size" ,"200",
		"--log-count" ,"2" })) {
#else
	if (!parser.parse(_object.arguments())) {
#endif
		//TODO:不是控制台项目，输入命令行错误不处理，但是记录。在Release版本中为了速度要去除
		DebugBox("Err", "Input param is wrong!");
		out.push_back(QU8("Command parse faild,error text:%1").arg(parser.errorText()));
	} else {
		auto set_integer = [&](QString _arg_name, auto _Copy, auto _Check) {
			auto presult = parser.value(_arg_name);
			if (!presult.isEmpty()) {
				bool suc = false;
				auto con_result = presult.toLongLong(&suc);
				if (suc && _Check(con_result)) {
					//set value
					_Copy(con_result);
					out.append(QU8("Argument:%1; Value:%2").arg(_arg_name, presult));
					return true;
				} else {
					out.append(QU8("%1,The type is wrong, an integer is required, and %2 is entered").arg(QU8("--restart-count"), presult));
				}
			}
			return false;
		};
		set_integer("restart-count", copy_integer(_object._getInfo()->restart_count_), range_check<0, UINT8_MAX>);
		set_integer("log-level", copy_integer(_object._getInfo()->log_level), range_check<0, 7>);
		set_integer("log-size", copy_integer(_object._getInfo()->log_file_size), range_check<0, UINT32_MAX>);
		set_integer("log-count", copy_integer(_object._getInfo()->log_file_count), range_check<0, UINT16_MAX>);
		_object._getInfo()->log_file = parser.value("log-file");//log file
		QString json_data = parser.value("error-json");//也许有上一次输入的错误信息
		if (!json_data.isEmpty()) {
			try
			{
				*result = nlohmann::json::parse(QSTD(json_data));
			}
			catch (const nlohmann::detail::exception&)
			{
				DebugBox("Option Json Wrong", "Inputing json data is wrong");
			}
		} else {
			//输入为空也许是bug
			DebugBox("Warning", "You set the error option,but no data was put in");
		}
	}
	return result;
	}

}
// //////////// CONFIG READER ////////////////////////////
namespace config_reader {
//读取_json里的信息到info中，返回vGConfig json指针维护
std::shared_ptr<vGConfig> parse_info(const nlohmann::json& _json, vGAppInfomation& _info) {
	std::shared_ptr<vGConfig> result(new vGConfig(_json));
	_info.log_file_count = result->base().log_file_count;
	_info.log_file_size = result->base().log_file_size;
	_info.log_level = result->base().log_level;
	return result;
}
std::shared_ptr<vGConfig> reader(vGAppInfomation& _info) {
	nlohmann::json config;
	std::fstream config_file(_APP_CONFIG_PATH, std::ios::in);
	if (config_file.is_open()) {
		try
		{
#if _AE_JSON_BINARY
			config = nlohmann::json::from_msgpack(config_file);
#else
			config = nlohmann::json::parse(config_file);
#endif
			return parse_info(config, _info);
		}
		//异常不能合并，有点尴尬的写法 (>_<)
		catch (const nlohmann::detail::exception& _ex)
		{
			//json 解析错误，替换配置文件
			_info.msg_buf.append(QU8("%1|Config Exception:%2").
				arg(QN2S(_AE_CONFIG_FILE), QU8(_ex.what())));
		}
		catch (const QString& _what) {
			//json 成员缺失，也是替换
			_info.msg_buf.append(QU8("%1|Config Exception:%2").
				arg(QN2S(_AE_CONFIG_FILE), _what));
		}
	}
	DebugBox("Config Error", "Unable to read");
	config_file.close(); //没打开但是关闭
	//权限不足，文件不存在
	//配置文件错误
	QFile target_file(QU8(_APP_CONFIG_PATH));
	QFileInfo tfinfo(target_file);
	if (tfinfo.exists()) {
		QCURDIR.remove(_APP_CONFIG_PATH);//删除,不判断
	}
	if (QFile::copy(QU8(_ARES_CORE_CONFIG), _APP_CONFIG_PATH)) {
		//设置读写属性
		target_file.setPermissions(QFile::ReadOther | QFile::WriteOther);
	} else {
		//打开文件失败 （罕见的错误重启并通知守护进程）
		//TODO 通知守护进程

		//输入错误信息,提供下次判断
		_info.msg_buf.push_back(QU8("%1|Config Exception:Can't read or copy the config.").arg(_AE_CONFIG_FILE));
	}
	return { nullptr };
}
//保存配置文件
void save_config(std::shared_ptr<vGConfig> _config) {
	QFile target_file(QU8(_APP_CONFIG_PATH));
	QFileInfo tfinfo(target_file);
	if (tfinfo.exists()) {
		QCURDIR.remove(_APP_CONFIG_PATH);//删除,不判断
	}
	std::fstream config_file(_APP_CONFIG_PATH, std::ios::out | std::ios::trunc | std::ios::binary);
	if (config_file.is_open()) {
		nlohmann::json data(*_config);
		//_config->make_json(data);
#if _AE_JSON_BINARAY
		auto binary = data.to_msgpack(data);
		config_file.write(reinterpret_cast<const char*>(binary.data()), binary.size() * sizeof(uint8_t));
#else
		config_file << data.dump(3, ' ',
			false, nlohmann::detail::error_handler_t::replace);
#endif
		config_file.close();
	}
	target_file.setPermissions(QFile::ReadOther | QFile::WriteOther);
	//TODO 未判断是否正确写入
}
}
// /////////////////////////   vGApp   /////////////////
vGApp::vGApp(int argc, char* argv[], std::shared_ptr<vGAppInfomation> _argu) :
	QApplication(argc, argv)
{
	info_ = _argu;
	setApplicationVersion(info_->version_);
	setApplicationName(info_->app_name);
	Q_INIT_RESOURCE(vGCore);
	//载入命令
	auto err = command_parse::QCommandParse(*this);
	if (info_->restart_count_) {
		info_->msg_buf.push_back(QU8("Number of program restarts: %1, last exit code: %2").
			arg(QN2S(info_->restart_count_), QN2S(info_->lastest_exit_code)));
	}
	info_->lastest_exit_code = err->at("exit_code");
	quint32 ecode = err->at("code");
	if (ecode) {//错误代码不为正常
		//TODO 让守护进程检视
		//已经设置至多重启5次
	}
	manager_ = new FrPluginManager();
	//日志文件检查由setLogger执行，错误会抛出异常
}

void vGApp::initialize()
{
	//读取配置
	config_ = config_reader::reader(*info_);
	if (!config_) {
		//配置文件错误，下一次自启动,设置启动信息
		//xthis->exit(_APP_RESTART); //抛出异常后自动设置重启
		info_->msg_buf.push_back(QU8("The config file could not be found, maybe it was fixed"));
		info_->attribute_ |= Restart;
		info_->log_file_size = 20480;
		info_->log_level = spdlog::level::trace; //调低记录等级，方便后续跟踪
		throw FrError(FrErrorStatue::InvalidFile, "Config file has been broken.Prepare for restarting...");
	}
	//设置日志系统,之后才可以使用
	setLogger();
	//将输入命令出现的log输入
	for (auto& in : info_->msg_buf) {
		vGlog->debug(QSTD(in));
	}
	vgTrace("Log system initialized {}", 01);
	//加载皮肤
	LoadSkin();
	//加载插件
	//!现在还没有初始化菜单
	LoadPlugins();
	//插件是必须存在至少一个，否则报错
	if (manager_->empty()) {
		info_->attribute_ |= Critical;
		vGlog->critical("The plug-in is not loaded correctly.");
		throw FrError(FrErrorStatue::Peripheral, "The number of plugins is 0");
	}
	setvGAtt(Initialized);
}


bool vGApp::setvGAtt(vGAppAttribute _att)
{
	info_->attribute_ |= _att;
	return true;
}
bool vGApp::removevGAtt(vGAppAttribute _att)
{
	if (info_->attribute_ & _att) {
		info_->attribute_ ^= _att;
	}
	return false;
}
vGApp::~vGApp()
{
	if (config_) { //如果是错误退出的话,config_为空
		config_reader::save_config(config_);
	}
	if (manager_) {
		delete manager_;
	}
}
bool vGApp::notify(QObject* _receiver, QEvent* _event) {
	return QApplication::notify(_receiver, _event);
}
QString vGApp::GetVersion() const {
	return info_->version_;
}
quint32 vGApp::GetAttribute() const
{
	return info_->attribute_;
}
const vGConfig& vGApp::Config() const
{
	return *config_;
}
const vGApp::value_type& vGApp::Plugins() const
{
	return plugins_;
}
vGApp::value_type& vGApp::Plugins()
{
	return plugins_;
}
std::vector<std::shared_ptr<FrPluginPr>>& vGApp::fPlugins()
{
	return fplugins_;
}
const vGC_Skin& vGApp::Skin() const
{
	return skin_;
}
QFileInfoList vGApp::GetSkins() const
{
	std::vector<QString> skins;
	QDir dir(_AP_SKINS_PATH);
	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	dir.setNameFilters({ "*.json" });
	dir.setSorting(QDir::Name);
	return dir.entryInfoList();
}
//获取信息
std::shared_ptr<vGAppInfomation> vGApp::_getInfo()
{
	return info_;
}
//处理重启信息
std::shared_ptr<vGAppInfomation> vGApp::_getRestartInfo()
{
	return std::shared_ptr<vGAppInfomation>(new vGAppInfomation(*info_));
}
const std::set<vGPlugin*>& vGApp::activities() const
{
	return activities_;
}
std::set<vGPlugin*>& vGApp::activities()
{
	return activities_;
}
//处理获取日志对象
std::shared_ptr<spdlog::logger> vGApp::_getLogger()
{
	return log_;
}

void vGApp::setMenu(QPointer<vGMenuBase> _point){
	if (_point.isNull()) {

	}
	menu_ = _point;
}

FrPluginManager* vGApp::pluginManager(){
	return manager_;
}

void vGApp::setLogger()
{
	QString file_path = info_->log_file;
	bool set_success = false;
	int retry_count = 0;
	for (; retry_count < 5; ++retry_count) {
		QFileInfo file(file_path);
		if (!file.isFile()) {
			try {
				auto de_name = file_path.toStdString();
				//下面这两个是不应该出现的错误,设置为Config默认值
				//但如果就是config值还出错的话，就是配置文件错误
				if (!info_->log_file_size) {
					//TODO 判断config->log_file_size是否为0，增加恢复函数
					info_->log_file_size = config_->base().log_file_size;
				}
#ifdef _DEBUG
#ifdef _WINDOWS
				AllocConsole();
				freopen("CON", "w", stdout);
#endif
				spdlog::init_thread_pool(4092, 2);
				auto file_logger = std::make_shared<spdlog::sinks::rotating_file_sink_mt>
					(de_name, info_->log_file_size * 1024, info_->log_file_count, false, spdlog::file_event_handlers{});
				file_logger->set_level(spdlog::level::level_enum(info_->log_level));

				auto console_logger = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>(spdlog::color_mode::always);
				console_logger->set_level(spdlog::level::trace);
				log_ = std::make_shared<spdlog::async_logger>(
					vGp->applicationName().toStdString(),
					spdlog::sinks_init_list{ console_logger,file_logger }, spdlog::thread_pool());
				//Debug下每2秒刷新一次
				spdlog::flush_every(std::chrono::seconds(2));
#else

				log_ = spdlog::rotating_logger_mt<spdlog::async_factory>
					(vGp->applicationName().toStdString(), de_name,
						info_->log_file_size * 1024, info_->log_file_count);
				log_->set_level(spdlog::level::level_enum(info_->log_level));
#endif
				//[时:分:秒-微秒][记录器名称][线程id][等级] 信息
				log_->set_pattern("[%H:%M:%S-%f][%n][%t][%l] %v ");
				//log_->flush_on(spdlog::level::err);
				vgDebug("The log has set up.");
				set_success = true;
				break;
			}
			catch (spdlog::spdlog_ex& _ex) {
				info_->msg_buf.append(QU8("spdlog exception:%1|target file:%2").arg(_ex.what(), file_path));
				//文件错误，尝试自动更换
			}
		}
		//尝试更换日志文件
		file_path = command_parse::get_log_file();
		info_->msg_buf.append(QU8("Set a new log file,path:%1").arg(file_path));
	}
	if (!set_success) {
		//日志无法打开(不应该出现的情况)
		//进行重启
		DebugBox("Error", QString("Can't open the log file:%1").arg(file_path));
		info_->msg_buf.append(QString("%1|Can't open the log file:%2").
			arg(QN2S(_AE_LOG_FILE), file_path));
		vGp->exit(_APP_RESTART);
		info_->attribute_ |= Restart;
		throw FrError(FrErrorStatue::InvalidFile, "Unable to create log file");
		return;
	}
}
vGConfig vGApp::readDefaultConfig()
{
	nlohmann::json data;
	QTemporaryFile config_temp(QU8(_ARES_CORE_CONFIG));
	config_temp.open();
	auto json_data = config_temp.readAll();
#if !_AE_JSON_BINARY
	data = nlohmann::json::from_msgpack(json_data.begin(), json_data.end());
#else
	data = nlohmann::json::parse(json_data);
#endif
	return data.get<vGConfig>();
}

void vGApp::LoadPlugins()
{
#ifndef _DEBUG
	//QDir dir(config_->base().plugins_path); //一直复制太麻烦了
//#error "you forget set default plugin file!"
#endif 
#if 1
#ifdef _DEBUG
	QDir dir(R"(../plugins/debug)");
#else
    QDir dir(config_->base().plugins_path);
    //QDir dir(R"(../plugins/release)");
#endif
#endif
#if 0
	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	dir.setSorting(QDir::Name);
	auto list = dir.entryInfoList();
	plugins_.reserve(list.size());
	for (auto& file : list) {
		QLibrary lib(file.absoluteFilePath());
		if (lib.load()) { //如果有基本成员
			if (lib.resolve("get_object") && lib.resolve("destory_object")&& lib.resolve("get_info")) {
				plugins_.push_back(new vGPlugin(file.absoluteFilePath()));
				vGlog->info("\"{}\" Plugin has been loaded", file.fileName().toStdString());
			}
		}

		//FrPluginPr:
		using __GetInstance = FrPluginPr*(*)();
		auto c1 = file.absoluteFilePath();
		__GetInstance cGetInstance = (__GetInstance)lib.resolve("GetInstance");
		if(cGetInstance){
			FrPluginPr* pointer = cGetInstance();
			if (pointer) {
				//调用插件的release函数
				auto deleter = [](FrPluginPr* _deleter) {
					_deleter->release();
				};
				fplugins_.push_back(std::shared_ptr<FrPluginPr>(pointer,deleter));
				fplugins_.back()->initialize();//进行初始化
			}
			else
				vgTrace("Loaded Plugin Faild");
		}

		lib.unload();
	}
	plugins_.shrink_to_fit();
#endif 
	//new
	manager_->load(dir.path());
	//TEST
	//auto ve = manager_->search("Setting");
	//ve = manager_->searchPackage("app.setting.app");
}

void vGApp::LoadSkin()
{
	auto skins_list = GetSkins();
	for (auto& skin : skins_list) {
		//寻找指定的皮肤名称
		auto skin_file_name = skin.fileName();
		if (!skin_file_name.left(skin_file_name.length() - 5).compare(Config().base().skin_name)) {
			//加载皮肤,缺省值使用默认值处理(默认值为白色0xffffffff)
			std::fstream file(QSTD(skin.absoluteFilePath()), std::ios::in);
			try {
				if (file.is_open()) {
					vGlog->debug("Trying to load \"{}\" skin...", Config().base().skin_name.toStdString());
					auto skin_config = nlohmann::json::parse(file);
					skin_config.get_to<vGC_Skin>(skin_);
					return;
				} 
				vGlog->error("Can't read user's skin!");
			}
			catch (const nlohmann::detail::exception& _ex) {
				   //皮肤配置文件加载错误，使用默认配置文件
				vGlog->error("User'skin is broken,Program is going to use default skin");
				vGlog->error("Error msg:{}", _ex.what());
			}
			//TODO 测试加载缓存文件
			//无法加载指定的皮肤文件
			QTemporaryFile config_temp(QU8(_ARES_CORE_SKIN));
			if (config_temp.open()) {
				auto by_arr = config_temp.readAll().constData();
				auto skin_config = nlohmann::json::parse(by_arr, nullptr, false, false);
				if (!skin_config.is_discarded()) {
					skin_config.get_to<vGC_Skin>(skin_);
					return;
				}
			}
			//这都出错太奇怪了.皮肤不是核心，不需要重启
			vGlog->error("Faild to read default skin config");
		}
	}
}

// //////////////////// vGPlugin //////////////////////////////////####################
vGPlugin::vGPlugin():
	lib_(nullptr), object_(nullptr) {
}
vGPlugin::vGPlugin(vGPlugin&& _Left)noexcept {
	std::exchange(this->object_, _Left.object_);
	std::exchange(this->lib_, _Left.lib_);
	std::exchange(this->info_, _Left.info_);
}

vGPlugin::vGPlugin(const QString& _path)
{
	lib_ = new QLibrary(_path);
	object_ = nullptr;
	lib_->load();
	//注意，同时会处理位图 
	get_info();
}
//插件指定了菜单窗口后，会自动删除
//否则就会在这里进入destory删除
vGPlugin::~vGPlugin(){
	destory();
}
bool vGPlugin::load()
{
	return lib_->load();
}
vGPlugin* vGAppWidBase::plugin() const
{
	return plugin_;
}
bool vGPlugin::unload()
{
	return lib_->unload();
}
vGPlugin::get_object_t vGPlugin::create_ptr()const
{
	return reinterpret_cast<get_object_t>(lib_->resolve("get_object"));
}

vGPlugin::destory_object_t vGPlugin::destory_ptr()const
{
	return reinterpret_cast<destory_object_t>(lib_->resolve("destory_object"));
}
vGAppWidBase* vGPlugin::app() const
{
	return object_;
}

bool vGPlugin::create(vGMenuBase* _parent){
	if (lib_->isLoaded() && object_.isNull()) {
		object_ = reinterpret_cast<vGAppWidBase*>(create_ptr()(_parent, this));
		//创建对象自动添加到vGApp的activities
		//auto it = std::find_if(vGp->Plugins().begin(), vGp->Plugins().end(), [this](const vGPlugin& _pl) {
		//	return _pl == *this;
		//	});
		auto it = std::find(vGp->Plugins().begin(), vGp->Plugins().end(), this);
		bool is_have = it != vGp->Plugins().end();
		if (is_have) {
			vGp->activities().insert(this);
		}
		return object_;
	}
	return false;
}
//销毁对象
//假使对象没有被销毁且不显示，就会和后台进程一样
void vGPlugin::destory()
{
	if (!object_.isNull()) {
		//查看是否在活动插件中
		vGp->mt_plugin.lock_shared();
		auto it = std::find_if(vGp->activities().begin(), vGp->activities().end(), [this](const vGPlugin* _pl) {
			return *_pl == *this;
			});
		bool is_have = it != vGp->activities().end();
		vGp->mt_plugin.unlock_shared();
		if (is_have) {
			std::lock_guard lock(vGp->mt_plugin);
			vGp->activities().erase(it);
		}
		object_->deleteLater();
	}
}

void vGPlugin::get_info()
{
	auto get_info = reinterpret_cast<get_info_t>(lib_->resolve("get_info"));
	get_info(&info_);
	//处理没有位图的插件
	if (info_.logo.isNull()) {
		QFile logo_svg_file(_ARES_CORE_LOGO);
		if (logo_svg_file.open(QIODevice::ReadOnly)) {
			QDomDocument doc;
			auto text = logo_svg_file.readAll();
			doc.setContent(text);
			auto svg_elem = doc.documentElement();
			//设置颜色与主题颜色一致
			SetAllTag(svg_elem, "path", "fill", vGp->Skin().menu.logo.name());
			if (doc.isNull()) {
				vGlog->error("Faild to load default icon!");
			}
			info_.logo = Svg2Pixmap(doc.toByteArray(),
				QSize(vGp->Config().base().sc_width, vGp->Config().base().sc_height));
		}
		//返回原始数据(empty)
		info_.logo = Svg2Pixmap(logo_svg_file.readAll(),
			QSize(vGp->Config().base().sc_width, vGp->Config().base().sc_height));
	}
	//位图大小警告
	if (info_.logo.height() < 64 || info_.logo.width() < 64) {
		vGlog->warn("The logo of the {} plugin is too small", QSTD(info_.app_name));
	}
}


const vGPluginInfo& vGPlugin::info() const{
	return info_;
}

QLibrary* vGPlugin::library()const{
	return lib_;
}

// ///////////////////// vGMessageBox ///////////////////////////####################
vGMessageBox::vGMessageBox(QWidget* parent, vGMsgType _type)
	: QWidget(parent), delay_time_(0), background_(nullptr), title_(nullptr)
{
	assert(parent != 0);
	setAttribute(Qt::WA_DeleteOnClose);
	//设置位置
	QRect pa(parent->rect());

	QRect re(pa.width() - dialog_width - dialog_right_side, pa.height() - dialog_height - dialog_bottom_side, dialog_width, dialog_height);
	this->setGeometry(re);
	this->setVisible(false);

	background_ = new QLabel(this);
	title_ = new QLabel(this);
	QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);

	sizePolicy.setHeightForWidth(background_->sizePolicy().hasHeightForWidth());
	background_->setSizePolicy(sizePolicy);

	sizePolicy.setHeightForWidth(title_->sizePolicy().hasHeightForWidth());
	title_->setSizePolicy(sizePolicy);

	background_->setScaledContents(true);
	title_->setWordWrap(true);//自动换行
	title_->setStyleSheet("margin:2px");

	switch (_type)
	{
	case Error:
		background_->setPixmap(QPixmap(_AP_MSG_BE_FILE));
		break;
	case Info:
		background_->setPixmap(QPixmap(_AP_MSG_BI_FILE));
		break;
	case Warning:
		background_->setPixmap(QPixmap(_AP_MSG_BW_FILE));
		break;
	case Success:
		background_->setPixmap(QPixmap(_AP_MSG_BS_FILE));
		break;
	default:
		vGlog->warn("vGMsgBox:input illegal parameter:{}", static_cast<int>(_type));
		break;
	}

	resize(this->size());
}

void vGMessageBox::resize(QSize _new) {
	background_->setGeometry(QRect(0, 0, _new.width(), _new.height())); //0.0533
	title_->setGeometry(_new.width() * 0.2061, _new.height() * 0.0533, _new.width() * 0.9318 - _new.width() * 0.2061,
		_new.height() * 0.896 - _new.height() * 0.0533);//0.896
}

void vGMessageBox::setText(const QString& _text) {
	title_->setText(_text);
}

void vGMessageBox::setFont(const QFont& _font) {
	title_->setFont(_font);
}

void vGMessageBox::setTime(const quint16 _time) {
	delay_time_ = _time;

}
void vGMessageBox::show() {
	__mb_mt_msg.lock();
	qDebug() << this << "show lock";
	__mb_msg_box_deque.push_back(this);
	if (__mb_msg_box_deque.begin() + 1 != __mb_msg_box_deque.end()) {
		qDebug() << this << "show add box,size:" << __mb_msg_box_deque.size();
		connect(*(__mb_msg_box_deque.end() - 2), &vGMessageBox::close_ac_start, *(__mb_msg_box_deque.end() - 1), [this]() {
			qDebug() << this;
		this->show_pr();
		//(*(msg_box_deque.end() - 1))->show_pr();
			});
	} else {
		//没有其他对话框的话
		this->show_pr();
	}
	qDebug() << this << "show unlock";
	__mb_mt_msg.unlock();
}

void vGMessageBox::close() {
	//动画缩回
	QSequentialAnimationGroup* group = new QSequentialAnimationGroup(this);
	//对话框上升
	auto up_end = QPoint(this->pos().x(), this->pos().y() - this->height());
	QPropertyAnimation* dialog_up = new QPropertyAnimation(this, "pos", this);
	dialog_up->setDuration(_get_duration() * 0.34);
	dialog_up->setEasingCurve(_get_easing_curve());
	dialog_up->setStartValue(this->pos());
	dialog_up->setEndValue(up_end);
	//缩回
	QPropertyAnimation* ppos = new QPropertyAnimation(this, "pos", this);
	ppos->setDuration(_get_duration() * 0.66);
	ppos->setEasingCurve(_get_easing_curve());
	ppos->setStartValue(up_end);
	up_end.setX(up_end.x() + this->width());
	ppos->setEndValue(up_end);

	group->addAnimation(dialog_up);
	group->addAnimation(ppos);
	group->start(QAbstractAnimation::DeleteWhenStopped);
	__mb_mt_msg.lock();
	qDebug() << this << "close lock";
	__mb_msg_box_deque.pop_front();
	qDebug() << this << "close pop front,size:" << __mb_msg_box_deque.size();
	qDebug() << this << "close unlock";
	__mb_mt_msg.unlock();
	emit close_ac_start();
	//延迟调用
	QTimer::singleShot(std::chrono::milliseconds(_get_duration() + 1000), Qt::VeryCoarseTimer, this, [this]() {
		QWidget::close();
		});
}
QPropertyAnimation* vGMessageBox::an_group() {
	auto pos = this->pos();
	QPropertyAnimation* ppos = new QPropertyAnimation(this, "pos", this);
	ppos->setDuration(_get_duration());
	ppos->setEasingCurve(_get_easing_curve());
	ppos->setStartValue(QPoint(pos.x() + this->rect().width(), pos.y()));
	ppos->setEndValue(QPoint(pos));
	return ppos;
}

void vGMessageBox::show_pr() {
	QTimer::singleShot(std::chrono::milliseconds(delay_time_), Qt::PreciseTimer, this, [this]() {
		this->close();
		});
	QWidget::show();
	an_group()->start(QAbstractAnimation::DeleteWhenStopped);
}

quint16 vGMessageBox::_get_duration(){
	return vGp->Config().base().duration_time;
}

QEasingCurve vGMessageBox::_get_easing_curve(){
	return QEasingCurve::Type(vGp->Config().base().easing_curve);
}

vGMessageBox::~vGMessageBox() {
}

void vGMessageBox::warning(QWidget* _parent, QString _text, quint16 _time) {
	box(_parent, _text, Warning, _time);
}

void vGMessageBox::error(QWidget* _parent, QString _text, quint16 _time) {
	box(_parent, _text, Error, _time);
}

void vGMessageBox::info(QWidget* _parent, QString _text, quint16 _time) {
	box(_parent, _text, Info, _time);
}

void vGMessageBox::success(QWidget* _parent, QString _text, quint16 _time) {
	box(_parent, _text, Success, _time);
}

void vGMessageBox::box(QWidget* _parent, QString _text, vGMsgType _type, quint16 _time)
{
	if (_parent == nullptr) {
		//TODO 错误提示
		vGlog->error("vGMsgBox: parent is nullptr!");
		return;
	}
	vGMessageBox* box = new vGMessageBox(_parent, _type);
	box->setText(_text);
	box->setTime(_time);
	box->show();
}

///////////////////////// FrPluginWidgetPr /////////////////////////////###############
/////////// 插件窗口
//
FrPluginWidgetPr::FrPluginWidgetPr(vGMenuBase* _menubase, FrPluginPr* _pluginctr):
	QWidget(_menubase), plugin_(_pluginctr){
	connect(menu(), &vGMenuBase::update_skin, this, &FrPluginWidgetPr::UpdateSkins);
	vgTrace("FrPluginWidgetPr ('{}') constructed", QSTD(plugin().name()));
}
FrPluginWidgetPr::~FrPluginWidgetPr(){
	vgTrace("FrPluginWidgetPr ('{}') destructed", QSTD(plugin().name()));
}
FrPluginPr& FrPluginWidgetPr::plugin() const{
	if (plugin_) {
		return *plugin_;
	}
	//除非FrPlugin在初始化给了nullptr，否则不会错误
	vGlog->error("The FrPluginPr address is null,is not normally!");
	throw FrError(FrErrorStatue::Nullptr, "The FrPluginPr address is null,is not normally!");
}
void FrPluginWidgetPr::UpdateSkins() {
	vgTrace("FrPluginWidgetPr: {}'s widget 'UpdateSkins' event.", QSTD(plugin().name()));
}
void FrPluginWidgetPr::WhenHide(){
	//打印日志输出
	vgTrace("FrPluginWidgetPr: {}'s widget 'WhenHide' event.", QSTD(plugin().name()));
}

QPointer<vGMenuBase> FrPluginWidgetPr::menu() const
{
	return QPointer<vGMenuBase>(reinterpret_cast<vGMenuBase*>(parent()));
}

void FrPluginWidgetPr::hideEvent(QHideEvent* _event){
	emit widget_hide();
	QWidget::hideEvent(_event);
}
void FrPluginWidgetPr::showEvent(QShowEvent* _event){
	emit widget_show();
	QWidget::showEvent(_event);
}


// ///////////////////////////  FrPluginPr  ///////////////////###########################
//////////////// 插件类
///////////

FrPluginPr::FrPluginPr(){
}
FrPluginPr::FrPluginPr(FrPluginPr&& _f):
	package_(std::move(_f.package_)),
	version_(std::move(_f.version_)),
	path_(std::move(_f.path_)),
	name_(std::move(_f.name_)),
	description_(std::move(_f.description_)),
	logo_(std::move(_f.logo_)),
	widget_(std::move(_f.widget_)){
}

FrPluginPr::~FrPluginPr() {
	release();
}
void FrPluginPr::initialize() {
	package_ = "app.unknow.com";
	version_ = "0.0.1";
}
/*
* 该函数有可能会被重复调用
* 1. 在插件的全局变量中被析构
* 2.在vGApp::~vGApp的shared_ptr中被release
*/
void FrPluginPr::release(){
	destory();
}

bool FrPluginPr::service(){
	return true;
}

QPointer<FrPluginWidgetPr> FrPluginPr::widget()const
{
	return widget_;
}

void FrPluginPr::destory() {
	if (!widget_.isNull()) {
		//删除
		widget_->deleteLater();
	}
}
void FrPluginPr::create() {
	widget_ = new FrPluginWidgetPr(vGp->menu(), this);
}
// //////////////////// Other Function //////////////////////////

QPixmap Svg2Pixmap(QByteArray _xml, QSize _size)
{
	if (_xml.isEmpty()) {
		vGlog->warn("Warning: Svg2Pixmap function get a illegal parameter");
		return {};
	} else {
		QSvgRenderer svg_render(_xml);
		QPixmap pixmap(_size);
		pixmap.fill(Qt::transparent);
		QPainter painter(&pixmap);
		svg_render.render(&painter);
		return pixmap;
	}
}
void SetAllTag(QDomElement& elem, QString strtagname, QString strattr, QString strattrval) {
	if (elem.tagName().compare(strtagname) == 0)
	{
		elem.setAttribute(strattr, strattrval);
	}
	for (int i = 0; i < elem.childNodes().count(); i++)
	{
		if (!elem.childNodes().at(i).isElement())
			continue;
		auto son_elem = elem.childNodes().at(i).toElement();
		SetAllTag(son_elem, strtagname, strattr, strattrval);
	}
}
bool operator==(const vGPlugin& _Left, const vGPlugin& _Right)
{
	return !QFileInfo(_Left.library()->fileName()).fileName().
		compare(QFileInfo(_Right.lib_->fileName()).fileName());
}

