/*
*	vGLsumtp head file
*	���������湦��
*/

#ifndef FP_PLUGIN_HEAD
#define FP_PLUGIN_HEAD
#include "vGConfig.h"
#include <QReadWriteLock>

class VGCORE_EXPORT FrPlugin;	//���ʵ������
class VGCORE_EXPORT FrPluginData;	//�������Ԫ��
class VGCORE_EXPORT FrPluginManager; //�������
class VGCORE_EXPORT FrPluginApp; //�������

//�����Ϣ
struct FrPluginProperty {
	QByteArray version;
	QByteArray package;
	QString description;
	QString name;
	QPixmap logo;
};
//�����߳�
class FrPluginManager {
public:
	FrPluginManager();

private:
	QReadWriteLock lock_;
	std::vector<FrPluginData> data_;
};
//�����̣߳�����һ�������̬�����
class FrPluginData {
public:
	using fget_property_type = void(*)(FrPluginProperty*);
	using fget_instance_type = FrPlugin(*)();

	FrPluginData(FrPluginData&& _object)noexcept;
	//����path���ز��
	//�������쳣
	FrPluginData(QDir _path);
private:
	void _load(QDir _path);

	fget_property_type f_get_property;
	fget_instance_type f_get_instance;
	FrPlugin* object_;
	FrPluginProperty property_;
};

//����һ���߳���
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