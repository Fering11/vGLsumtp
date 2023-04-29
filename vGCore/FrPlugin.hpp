/*
*	vGLsumtp head file
*	管理插件方面功能
*/

#ifndef FP_PLUGIN_HEAD
#define FP_PLUGIN_HEAD
#include "vGConfig.h"
#include <QReadWriteLock>

class VGCORE_EXPORT FrPlugin;	//插件实例对象
class VGCORE_EXPORT FrPluginData;	//插件管理元素
class VGCORE_EXPORT FrPluginManager; //插件管理
class VGCORE_EXPORT FrPluginApp; //插件窗口

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
	FrPluginData(QDir _path);
private:
	void _load(QDir _path);

	fget_property_type f_get_property;
	fget_instance_type f_get_instance;
	FrPlugin* object_;
	FrPluginProperty property_;
};

//在另一个线程中
class FrPlugin :public QObject {
	Q_OBJECT
public:
	FrPlugin();

private:
	FrPluginApp* widget_;
};

class FrPluginApp {


};



#endif //FP_PLUGIN_HEAD