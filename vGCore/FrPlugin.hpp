/*
*	vGLsumtp head file
*	管理插件方面功能
*/

#ifndef FP_PLUGIN_HEAD
#define FP_PLUGIN_HEAD
#include "vGConfig.h"

class VGCORE_EXPORT FrPlugin;	//插件实例对象
class VGCORE_EXPORT FrPluginData;	//插件管理元素
class VGCORE_EXPORT FrPluginManager; //插件管理
class VGCORE_EXPORT FrPluginApp; //插件窗口
#define TH_SAFETY //线程安全指示符
//插件信息
struct FrPluginProperty {
	QByteArray version;
	QByteArray package;
	QString description;
	QString name;
	QPixmap logo;
};
//在主线程
class FrPluginManager {
public:
	FrPluginManager();
	//!加载目录里面的插件
	void load(QDir _directory);
	//!加载指定的插件
	//插件加载失败返回false
	bool loadPlugin(QString _directory)TH_SAFETY;
private:
	QReadWriteLock lock_;
	std::vector<FrPluginData> data_;
};
//在主线程，代表一个插件动态库对象
class FrPluginData {
public:
	using fget_property_type = void(*)(FrPluginProperty*);
	using fget_instance_type = FrPlugin(*)();

	FrPluginData(FrPluginData&& _object)noexcept;
	//根据path加载插件
	//错误抛异常
	FrPluginData(QDir _path)TH_SAFETY; 
	//如果插件对象无效，则返回true
	//插件对象有效不代表object对象存在
	bool isInvalid()const;
	//重新获取插件属性
	void updateProperty()TH_SAFETY;
	//获取插件
	QPointer<FrPlugin> plugin()const;
	FrPluginProperty property()const;
private:
	void _load(QDir _path)TH_SAFETY;
	bool _is_invalid()const;

	QReadWriteLock lock_;
	fget_property_type f_get_property;
	fget_instance_type f_get_instance;
	QPointer<FrPlugin> object_;
	FrPluginProperty property_;
};

//在另一个线程中
class FrPlugin :public QObject {
	Q_OBJECT
public:
	FrPlugin();

private:
	QPointer<FrPluginApp> widget_;
};

class FrPluginApp:public QWidget {


};



#endif //FP_PLUGIN_HEAD