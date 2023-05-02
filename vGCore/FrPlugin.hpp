/*
*	vGLsumtp head file
*	管理插件方面功能
*/

#ifndef FP_PLUGIN_HEAD
#define FP_PLUGIN_HEAD
#include "vGConfig.h"

class vGMenuBase;

class VGCORE_EXPORT FrPlugin;	//插件实例对象
class VGCORE_EXPORT FrPluginData;	//插件管理元素
class VGCORE_EXPORT FrPluginManager; //插件管理
class VGCORE_EXPORT FrPluginWidget; //插件窗口
#define TH_SAFETY //线程安全指示符
//插件信息
struct FrPluginProperty {
	QByteArray version;
	QByteArray package; //www.time.app
	QString description;
	QString name;
	QPixmap logo;
	//返回格式{前缀域, 应用名, 属性}
	static QByteArrayList SplitPackage(const QByteArray& _pk) {
		QByteArrayList result;
		int left = _pk.indexOf('.');
		int right = _pk.indexOf('.', left + 1);
		return { _pk.left(left),_pk.mid(left + 1,right - left - 1),_pk.mid(right + 1) };
	}
};
//在主线程
class FrPluginManager {
public:
	using SeReType = std::vector<FrPluginData*>;
	FrPluginManager();
	~FrPluginManager();
	//!加载目录里面的插件
	void load(QDir _directory);
	//!加载指定的插件
	//插件加载失败返回false
	bool loadPlugin(QString _directory)TH_SAFETY;
	//STL vector::at返回函数
	FrPluginData& at(size_t pos)TH_SAFETY;
	//删除插件,_pos指定位置，错误抛出std异常
	//插件必须没有运行
	bool remove(size_t _pos)TH_SAFETY;
	//返回插件指针
	std::vector<FrPluginData*> plugins()TH_SAFETY;
	//释放所有插件
	void release()TH_SAFETY;
	//搜索,返回对应插件的指针
	SeReType search(const QString& _name)TH_SAFETY;
	SeReType searchPackage(const QByteArray& _package)TH_SAFETY;
	
	bool isExist(const QByteArray& _package)const;
private:
	bool __remove(std::vector<FrPluginData>::const_iterator _it);
	//void Fn(const FrPluginProperty& _fr)
	template<class _Fx>
	SeReType __search(_Fx _fn) const {
		SeReType result;
		for (auto it = data_.cbegin(); it != data_.cend(); ++it) {
			if (_fn(it->property())) {
				result.push_back((FrPluginData*)&(*it));
			}
		}
		return result;
	}

	QReadWriteLock lock_;
	std::vector<FrPluginData> data_;
};
//在主线程，代表一个插件动态库对象
class FrPluginData {
public:
	using fget_property_type = bool(*)(FrPluginProperty*);
	using fget_instance_type = FrPlugin*(*)();

	FrPluginData(FrPluginData&& _object)noexcept;
	FrPluginData(const FrPluginData&) = delete;
	FrPluginData& operator=(const FrPluginData&) = delete;
	FrPluginData& operator=(FrPluginData&&);
	//根据path加载插件
	//错误抛异常
	FrPluginData(QDir _path)TH_SAFETY;
	~FrPluginData()TH_SAFETY;
	//如果插件对象无效，则返回true
	//插件对象有效不代表object对象存在
	bool isInvalid()const;
	//重新获取插件属性
	void updateProperty()TH_SAFETY;
	//获取插件
	//!如果object_对象为空，则会创建对象
	//插件对象不正确或者无法分配地址时(失败)返回nullptr
	//TODO 这里没有开启线程，后续根据项目修改
	QPointer<FrPlugin> plugin()TH_SAFETY;
	QPointer<FrPlugin> plugin()const;
	//获取插件的属性
	const FrPluginProperty& property()const;
	//释放该插件对象，终止APP运行
	// overtime 超时时间，force是否强制(必须先获取锁)
	//如果程序在运行，则会QThread::exit退出
	//!超过overtime并且force为真，则会调用thread的terminial
	bool release(const int overtime = -1,bool force = false)TH_SAFETY;
	//返回当前的线程对象，如果为空则说明线程没有开始运行
	QThread* thread()const;
	//开启线程,如果插件已经在运行，那么将什么也不做
	void start(QThread::Priority = QThread::InheritPriority);
	//是否是服务
	bool isService()const;
	//插件是否在运行
	bool isRunning()const;
private:
	void _load(QDir _path)TH_SAFETY;
	bool _is_invalid()const;

	QReadWriteLock lock_;
	fget_property_type f_get_property;
	fget_instance_type f_get_instance;
	//插件所在的线程
	//生命周期只比object_长一点(具体查看release)
	QThread* plugin_thread_;
	QPointer<FrPlugin> object_;
	FrPluginProperty property_;
};

//在另一个线程中
class FrPlugin :public QObject {
	Q_OBJECT
public:
	//插件初始化不代表立马初始化窗口对象
	FrPlugin();
	~FrPlugin();
	//初始化插件，请在这时初始化窗口对象
	//这个函数会在插件启动的时候调用
	virtual bool initialize();
	//获取窗口对象
	virtual QPointer<FrPluginWidget> widget()const;
protected:
	FrPluginWidget* widget_;
};

class FrPluginWidget:public QWidget {
	Q_OBJECT
public:
	FrPluginWidget(vGMenuBase* _menu, FrPlugin* _plugin);
	QPointer<FrPlugin> plugin()const;
protected:

	const QPointer<FrPlugin> plugin_;
};



#endif //FP_PLUGIN_HEAD