/*
* vGLsumtp head file
* 管理全局配置
*/

#ifndef VGHEAD_DEF
#define VGHEAD_DEF
#include "vGConfig.h"

class VGCORE_EXPORT vGAppWidBase;
class VGCORE_EXPORT vGPlugin;
class VGCORE_EXPORT vGImageLabel;
class VGCORE_EXPORT vGApp;
class VGCORE_EXPORT vGMenuBase;
class VGCORE_EXPORT vGMessageBox;
class VGCORE_EXPORT FrMenuBase;
class VGCORE_EXPORT FrPluginPr;
class VGCORE_EXPORT FrPluginWidgetPr;

class FrPlugin;	//插件实例对象
class FrPluginData;	//插件管理元素
class FrPluginManager; //插件管理
class FrPluginWidget; //插件窗口

//主要是为了刷新时避免突然变化
class vGImageLabel :public QLabel {

	Q_OBJECT
public:
	vGImageLabel(QWidget* _parent = nullptr);
	//设置下一张位图
	void setNextPixmap(const QPixmap& _pix) { pix_.reset(new QPixmap(_pix)); }
	//获取下一张位图	
	QPixmap* nextPixmap()const { return pix_.get(); }

private:
	std::shared_ptr<QPixmap> pix_;
};


//主控制的基类
//已经包含了UI，动画
//该实例窗口不会被隐藏，所有窗口都基于这个类
//窗口的切换也只是之类窗口的隐藏和显示
class vGMenuBase :public QWidget {
	Q_OBJECT
	Q_PROPERTY(qreal allOpacity READ allOpacity WRITE setAllOpacity)
	Q_PROPERTY(qreal ebOpacity READ ebOpacity WRITE setEbOpacity)

public:
	constexpr static int center_side = 10;
	enum Action {
		Resize,//重新调整大小
		Left, //方向，向左流
		Right, //向右流
		Enter, //进入app
		Escape //退出app
	};
	vGMenuBase(QWidget* _parent, QLayout* _back);
	~vGMenuBase();
	//获取前台app(无则空)
	QPointer<vGAppWidBase> GetFrontApp()const;
	//强制杀死该对象
	void kill();
	//相对于界面左、中、右的Label(setPos会更新)
	vGImageLabel* left();
	vGImageLabel* center();
	vGImageLabel* right();
	vGImageLabel* buff() { return buff_; }
	QLabel* description() { return description_; }
	vGImageLabel* left() const;
	vGImageLabel* center() const;
	vGImageLabel* right() const;
	vGImageLabel* buff()const { return buff_; }
	QLabel* description() const { return description_; }

	//设置都是操作队列，对显示内容不会更换
	//setPos是在原来的基础上进行增减
	void setPos(int _size);
	void add();
	void sub();
	//加上3的倍数一样
	unsigned int getPos() const;
	//获取动画持续时间
	quint16 duration()const;
	//获取过度样式
	QEasingCurve::Type easingCurve()const;
	//设置全部的透明度，用来隐藏或显示
	void setAllOpacity(qreal _num);
	//没啥用的函数
	qreal allOpacity() { return center_oe_->opacity(); }

	//设置除了buff之外的label透明度
	void setEbOpacity(qreal _num);
	qreal ebOpacity() { return buff_oe_->opacity(); }
public slots:
	//app页面退出时调用
	virtual void ReleaseWindow(vGAppWidBase* _object) = 0;
	//app进入主界面时调用
	virtual void LaunchWidget(vGAppWidBase* _object) = 0;
	//更新皮肤样式
	virtual void UpdateSkin();
	//更新主界面
	virtual void UpdateLayout(Action _action, QSize _new_size = {});
	void setDuration(quint16 _ms);
	void setEasingCurve(QEasingCurve::Type _type);
signals:
	//更新皮肤的信号(stylesheet),主菜单每一次刷新都会调用
	//TODO 带动全部插件的update_skin
	//TODO 当有大量app时，生成会非常缓慢，用线程池解决
	void update_skin();
protected:
	//接受键盘左右键和ad enter键
	virtual void keyPressEvent(QKeyEvent* _event);
	//通知更新布局和动画
	virtual void resizeEvent(QResizeEvent* event);
	bool event(QEvent* _event);
	
	//设置动画组
	void setParallel(QAbstractAnimation* _p);
	QPointer<vGAppWidBase> front_;//前台窗口
	//DEL_ME
	QPointer<QLayout> background_;//后面背景
	//活动的插件
	//TODO 删除
	std::set<vGPlugin*> ui_ac_;
	std::shared_mutex mt_uia;

	void __initialize_ui();
	//之类要重新实现就直接覆盖override
	virtual QAbstractAnimation* __ac_left(QSize _size = {});
	virtual QAbstractAnimation* __ac_right(QSize _size = {});
	virtual QAbstractAnimation* __ac_resize(QSize _size = {});
	virtual QAbstractAnimation* __ac_enter(QSize _size = {});
	virtual QAbstractAnimation* __ac_escape(QSize _size = {});
	void __get_layout(QSize _size,QRect _re[4]);
	//left center right description
private:

	QLabel* description_;
	vGImageLabel* buff_;
	QGraphicsOpacityEffect* left_oe_;
	QGraphicsOpacityEffect* center_oe_;
	QGraphicsOpacityEffect* right_oe_;
	QGraphicsOpacityEffect* buff_oe_;
	QGraphicsOpacityEffect* desc_oe_;
	std::deque<vGImageLabel*> labs_;

	quint16 duration_time_; //动画时间 
	quint8 easing_curve_; //动画样式

	quint8 now_pos_; //现在label位置
	QPointer<QAbstractAnimation> para_ag;//动画队列
};
//基础信息在vGPlugin获得
struct vGPluginInfo{
	QByteArray package;//包名，格式 app.***.com
	QString version;
	QString app_name;
	QString description;
	QPixmap logo;
	//xQPixmap* logo = nullptr;//为了避免频繁画图造成的卡顿(树莓派性能担忧)
};

//x所有App的基类,注意，当调用close的时候，会自动回收内存，不是hide
//!后面删除
//所有插件基类，
class vGAppWidBase :public QWidget {
	Q_OBJECT
public:
	//初始化后窗口是隐藏的，必须显式调用show
	vGAppWidBase(vGMenuBase* _parent,vGPlugin* _plugin);
	~vGAppWidBase();
    /*//获取svg xml代码
	//子类重载可以自定义图标
	//获取图标后不再更改颜色
	virtual QByteArray GetSvg();*/

	//获取菜单界面指针
	vGMenuBase* menu();
	//获取信息
	const vGPluginInfo* info()const;
	vGPlugin* plugin()const;
signals:
	//关闭程序时
	void CloseApp(vGAppWidBase* _app);
	//更新皮肤样式(包括logo)的信号
	void update_skin();
public slots:
	virtual void UpdateSkin();
protected:
	vGPluginInfo* _info();
	void closeEvent(QCloseEvent* event);
	void keyPressEvent(QKeyEvent* _event);
	//App的基础信息
	vGPlugin* plugin_;
	friend class vGPlugin;
};
//TODO 删除这个
//本程序用异常驱动，不适合用错误代码
enum vGAppAttribute
{
	//xIntoApp = 0x1, //进入app(反例:发生致命错误)
	Restart = 0x2,  //重启的，一般是因为异常错误而重启，会计数
	Critical = 0x4, //严重错误，程序需要退出
	Initialized =0x8 //已经初始化的
};
//主框架信息
struct vGAppInfomation{
	QString version_; //版本
	QString app_name;//app名称
	QString log_file; //日志文件位置(可以不计日志)
	//这个成员用处较多
	//1.在命令解析中充当信息缓存的作用
	//2.在重启中充当储存错误信息的作用
	QStringList msg_buf;
	quint32 attribute_; //标志
	quint32 log_file_size; //日志文件大小(kb);
	quint16 log_file_count; //日志文件数量(单次启动)(0无限制)
	quint8 restart_count_; //重启次数
	quint8 log_level;//日志等级
	int lastest_exit_code;//上一次退出的代码
};

//插件管理,依赖于vGApp
class vGPlugin {
public:
	using get_object_t = vGAppWidBase * (*)(vGMenuBase*, vGPlugin*);
	using destory_object_t = void (*)(vGAppWidBase*);
	using get_info_t = void (*)(vGPluginInfo*);

	vGPlugin();
	vGPlugin(const vGPlugin&) = delete;
	vGPlugin& operator=(const vGPlugin&) = delete;
	vGPlugin(vGPlugin&&)noexcept;
	vGPlugin(const QString& _path);
	~vGPlugin();
	//加载动态库,跟QLibrary一样
	bool load();
	//卸载库
	bool unload();
	//获取构造对象函数的地址
	get_object_t create_ptr()const;
	//获取销毁对象函数的地址,建议使用destory()
	destory_object_t destory_ptr()const;
	//构造对象,在此之前,object_是空的
	//注意，该函数会操作vGApp
	bool create(vGMenuBase* _parent );
	//销毁对象 deleteLater
	//注意，该函数会操作vGApp
	void destory();
	//获取(或更新)信息
	void get_info();
	//获取库
	QLibrary* library()const;
	//x获取位图,假使插件中位图为空
	//x则使用自定义图标
	//xQPixmap getPixmap(QSize _size)const;
	//返回对象
	vGAppWidBase* app()const;
	const vGPluginInfo& info()const;
	friend bool operator==(const vGPlugin& _Left, const vGPlugin& _Right);
private:

	QLibrary* lib_;
	vGPluginInfo info_;
	QPointer<vGAppWidBase> object_;
	friend class vGAppWidBase;
};
//主程序基类
class vGApp :public QApplication {
	Q_OBJECT
	using value_type = std::vector<vGPlugin*>;
public:
	vGApp(int argc, char* argv[], std::shared_ptr<vGAppInfomation> _argu);
	~vGApp();
	bool notify(QObject* _receiver, QEvent* _event);
	//获取版本
	QString GetVersion()const; 
	//获取属性标志
	quint32 GetAttribute() const;
	//不在构造函数初始化，这个函数进行初始化
	void initialize();
	//设置标志位,永远成功
	bool setvGAtt(vGAppAttribute _att);
	//删除标志位，当标志位不存在时，返回false
	bool removevGAtt(vGAppAttribute _att);
	//配置文件(read only)
	const vGConfig& Config()const;
	//获取插件
	const value_type& Plugins()const;
	value_type& Plugins();//注意加锁

	std::vector<std::shared_ptr<FrPluginPr>>& fPlugins();
	//获取活动插件
	const std::set<vGPlugin*>& activities()const;
	std::set<vGPlugin*>& activities();
	//获取皮肤样式
	const vGC_Skin& Skin()const;
	//返回全部皮肤路径
	QFileInfoList GetSkins()const;
	std::shared_ptr<vGAppInfomation> _getInfo();
	std::shared_ptr<vGAppInfomation> _getRestartInfo();
	std::shared_ptr<spdlog::logger> _getLogger();
	//用于修改的互斥锁
	//影响成员有 fplugins_
	std::shared_mutex mt_plugin; //plugins_  activities_
	//只有初始化菜单之后才设置
	QPointer<vGMenuBase> menu() const{ return menu_; }
	//修改主菜单地址,提供接口给vGMainMenu自己设置
	//不要输入空地址
	void setMenu(QPointer<vGMenuBase> _point);

	FrPluginManager& pluginManager();
protected:
	//打开日志文件，自定义文件无法开打则使用默认文件
	//默认文件都打不开则重启
	//当info_中某些参数异常时，会自动修复该错误
	void setLogger();
	//读取默认的日志文件，并返回该日志文件的json
	//读取失败抛异常
	//! 该函数没有进行测试
	vGConfig readDefaultConfig();
	//加载插件
	void LoadPlugins();
	//加载皮肤
	void LoadSkin();
private:
	vGC_Skin skin_;
	//old
	value_type plugins_; //插件
	std::set<vGPlugin*> activities_;//活动的插件（创建了对象,来源于plugins_）
	//!fplugins的内存实在插件全局区上，不是堆分配内存
	std::vector<std::shared_ptr<FrPluginPr>> fplugins_;

	//插件管理器
	std::unique_ptr<FrPluginManager> manager_;
	//指向主菜单
	QPointer<vGMenuBase> menu_;
	std::shared_ptr<vGConfig> config_;
	std::shared_ptr<vGAppInfomation> info_;
	std::shared_ptr<spdlog::logger> log_;
};

//每个插件都有这个基础对象
//!这个的生命周期长于vGApp
class FrPluginPr {
public:
	FrPluginPr();
	FrPluginPr(const FrPluginPr&) = delete;
	FrPluginPr(FrPluginPr&& _l);
	~FrPluginPr();
	//初始化插件
	virtual void initialize();
	//释放插件资源
	//!整个插件废弃，和析构一样
	//!要准备被重复调用至少2次
	virtual void release();
	//销毁窗口
	virtual void destory();
	QByteArray package()const { return package_; }
	QByteArray version() const { return version_; }
	QString path()const { return path_; }
	QString name()const { return name_; }
	QString description() const { return description_; }
	QPixmap logo()const { return logo_; }
	//是否注册为服务
	//服务插件即是无互动窗口，不会在主界面显示插件名称
	virtual bool service(); 
	//创建对象，失败抛异常
	//子类创建FrPluginWidget需要FrPlugin和vGMenuBase对象，
	//!确保显示主菜单之后再来调用create函数，否则menu()为空
	virtual void create();
	QPointer<FrPluginWidgetPr> widget()const;
protected:
	QByteArray package_;//包名，格式 app.***.com
	QByteArray version_;//版本，e.g. 1.0.1
	//应用路径,为了以后方便扩展
	//e.g. .\plugins\date\Core.dll 
	QString path_;
	//应用名称,不同于包名，应用名称可以重复
	QString name_;
	//应用简短描述
	QString description_;
	//插件自动处理图像与主题适应
	//注意logo可以是无效值
	//!主程序只需要获得图像句柄即可
	QPixmap logo_;
	//app对象，在调用create函数时会被创建   ==> 窗口后台
	//destory会销毁该对象,释放相对应资源 ==> 应用后台
	//服务可以不需要这个成员，也可以存在，作为后台设置
	QPointer<FrPluginWidgetPr> widget_;
	friend class FrPluginWidgetPr;
	friend class vGApp; //主要是提供接口修改路径
};
//窗口基础类，这里主要隐藏信号槽连接
// 1. 被通知隐藏窗口时，即失去对焦
// 2. 更新皮肤样式时
class FrPluginWidgetPr:public QWidget {
	Q_OBJECT;
public:
	FrPluginWidgetPr(vGMenuBase* _menubase, FrPluginPr* _pluginctr);
	~FrPluginWidgetPr();
	//获取该App的插件类
	FrPluginPr& plugin()const;
public slots:
	//更新皮肤
	virtual void UpdateSkins();
	//当隐藏时
	virtual void WhenHide();
signals:
	//窗口显示信号
	void widget_show();
	//窗口隐藏信号
	void widget_hide();
	//关闭信号有析构函数，就不添加
protected:
	//获取菜单父类
	QPointer<vGMenuBase> menu()const;

	//触发信号消息
	virtual void hideEvent(QHideEvent* _event);
	virtual void showEvent(QShowEvent* _event);
	//给更新皮肤提供接口
	QPixmap& logo() { return plugin().logo_; }
private:
	//不给weak_ptr 一是因为难处理，FrPlugin里面要create不好弄
	//二是能确保FrPlugin生命周期  > FrPluginWidgetPr 的生命周期
	FrPluginPr* plugin_;
};

//输入svg图片，转换颜色为默认颜色(path,fill属性)
VGCORE_EXPORT void SetAllTag(QDomElement& elem, QString strtagname, QString strattr, QString strattrval);
//Svg格式图片转换为QPixmap
VGCORE_EXPORT QPixmap Svg2Pixmap(QByteArray _xml, QSize _pix_size);

#if _HAS_NODISCARD
#ifndef _NODISCARD 
#define _NODISCARD [[nodiscard]]
#endif
#else
#define _NODISCARD  
#endif
//输入支持双向迭代器的容器，提供双向循环迭代器
//size at成员必须存在 value_type reference pointer difference_type类型必须存在
template<class _Collect >
class vIterator {
public:
	using _MyVector = _Collect;
	using value_type = typename _MyVector::value_type;
	using reference = typename _MyVector::reference;
	using pointer = typename _MyVector:: pointer;
	using difference_type = typename _MyVector::difference_type;
	vIterator(_MyVector* _object, int _cur = 0) :object_(_object), current_(_cur) { 
		__set_correct_pos();
	}
	_NODISCARD value_type& operator*() const {
		_Chceck_Pointer();
		return object_->at(current_);
	}
	_NODISCARD pointer operator->()const {
		return &(this->operator*());
	}
	vIterator& operator++() {
		_Chceck_Pointer();
		++current_;
		__set_correct_pos();
		return *this;
	}
	vIterator operator++(int) {
		vIterator Tmp = *this;
		++* this;
		return Tmp;
	}
	vIterator& operator--() {
		_Chceck_Pointer();
		--current_;
		__set_correct_pos();
		return *this;
	}
	vIterator operator--(int) {
		vIterator Tmp = *this;
		--* this;
		return Tmp;
	}
	void __set_correct_pos() {
        if(object_->size()==0){
            current_=0;
        }else if (current_ < 0) {
			auto t1 = (-current_) % object_->size();
			if (t1 != 0) {
				current_ = object_->size() - t1;
			} else current_ = 0;
		} else {
			current_ = current_ % object_->size();
		}
	}
	vIterator& operator+=(difference_type _count) {
		current_ += _count;
		__set_correct_pos();
		return *this;
	}
	_NODISCARD vIterator operator+(difference_type _count)const {
		vIterator Tmp = *this;
		Tmp += _count;
		return Tmp;
	}
	_NODISCARD friend vIterator operator+(difference_type _count, vIterator _object) {
		_object += _count;
		return _object;
	}
	vIterator& operator-=(difference_type _count) {
		(*this) += -_count;
		return *this;
	}
	_NODISCARD vIterator operator-(difference_type _count)const {
		vIterator Tmp = *this;
		Tmp -= _count;
		return Tmp;
	}
	void _Compat(const vIterator& _right) const noexcept {
#if _ITERATOR_DEBUG_LEVEL != 0
		_STL_VERIFY(this->object_ == _right.object_, "vector iterators incompatible");
#endif
	}
	_NODISCARD difference_type operator-(const vIterator& _right) {
		_Compat(_right);
		return current_ - _right.current_;
	}
	_NODISCARD reference operator[](const difference_type _Off) const noexcept {
		return *(*this + _Off);
	}

	_NODISCARD bool operator==(const vIterator& _Right) const noexcept {
		_Compat(_Right);
		return current_ == _Right.current_;
	}
	_NODISCARD difference_type pos()const {
		return current_;
	}
	_NODISCARD bool vaild()const {
		return object_ != nullptr;
	}
protected:
	void _Chceck_Pointer() const {
#if _ITERATOR_DEBUG_LEVEL != 0
		_STL_VERIFY(object_, "The vector pointer is null!");
#endif
	}
	
private:
	_MyVector* object_;
	difference_type current_;
};

//主界面菜单
class FrMenuBase :public QWidget {
	Q_OBJECT
public:
	FrMenuBase(QLayout* _layout,QWidget* _parent=nullptr);
	//加载指定插件
	virtual void launchPlugin(FrPluginData* _target) = 0;
	virtual void releasePlugin(FrPluginData* _target) = 0;
	virtual void switchPlugin(FrPluginData* _starter, FrPluginData* _destination) = 0;
	virtual void killPlugin(FrPluginData* _target) = 0;
protected:
	QLayout& background();
	//因为layout在初始化时已经确定了的
	//activity在开始时为null，故返回指针
	FrPluginData* activity();

	FrPluginData* activity_; //前台插件
	QLayout* background_ ;
};


//消息框
enum vGMsgType {
	Error, Info, Warning, Success
};
//正常情况下，该对话框不会自动更改大小(show的时候已经计算好了位置)
//维护了一个全局变量，确保消息框不会重复,该变量线程安全
//依赖于Config
class vGMessageBox : public QWidget
{
	Q_OBJECT
public:
	//效果:会驻留在窗口的右下角
	//延迟时间过后自动删除
	vGMessageBox(QWidget* menu, vGMsgType _type);
	~vGMessageBox();
	static void warning(QWidget* menu, QString _text, quint16 _time = 10000);
	static void error(QWidget* menu, QString _text, quint16 _time = 10000);
	static void info(QWidget* menu, QString _text, quint16 _time = 10000);
	static void success(QWidget* menu, QString _text, quint16 _time = 10000);
	static void box(QWidget* menu, QString _text, vGMsgType _type, quint16 _time = 10000);

public slots:
	void resize(QSize _new);
	//尽量短小
	//建议直接添加<font size=?></font>设置字体大小
	void setText(const QString& _text);
	void setFont(const QFont& _font);
	//显示时间包括动画时间
	void setTime(const quint16 _time);
	void show();
	void close();

signals:
	//关闭动画开始播放
	void close_ac_start();
protected:
	QPropertyAnimation* an_group();
private:
	void show_pr();
	static quint16 _get_duration();
	static QEasingCurve _get_easing_curve();

	quint16 delay_time_;//延迟时间
	QLabel* background_;
	QLabel* title_;

	static std::deque<vGMessageBox*> __mb_msg_box_deque; //信息框队列
	static std::shared_mutex __mb_mt_msg;
	static constexpr int dialog_width = 315;
	static constexpr int dialog_height = dialog_width / 2.232;
	static constexpr int dialog_bottom_side = 70;//距离下边框	
	static constexpr int dialog_right_side = 18; //距离右边框
	static constexpr int dialog_end_right_offset = 100; //结束时往x的偏移量(处理结束时出现对话框)
};

#define vGp              (static_cast<vGApp*>(QCoreApplication::instance()))
#define vGlog            (vGp->_getLogger())
#define vgDebug          (vGlog->debug)
//info才能输出信息
#define vgTrace			 (vGlog->info)

#define DebugBox(title,msg)   (QMessageBox::information(nullptr,title,msg))
//配置文件默认位置  
//TODO:之后更换为二进制.dat
#define _APP_CONFIG_PATH  ("./config.json")

//关于资源文件的
#define _ARES_CORE_CONFIG (R"(:/core/default_config)")        //默认配置文件
#define _ARES_CORE_LOGO   (R"(:/core/unknow_icon)")           //未知应用
#define _ARES_CORE_SKIN   (R"(:/core/dark)")                  //默认皮肤
#define _AP_MSG_BE_FILE   (R"(:/core/bk_error)")               //消息框(Error)
#define _AP_MSG_BW_FILE   (R"(:/core/bk_warning)")             //消息框(warning)
#define _AP_MSG_BI_FILE   (R"(:/core/bk_info)")                //消息框(info)
#define _AP_MSG_BS_FILE   (R"(:/core/bk_success)")             //消息框(success)

#endif
