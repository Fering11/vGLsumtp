/*
*	vGLsumtp head file
*	���������湦��
*/

#ifndef FP_PLUGIN_HEAD
#define FP_PLUGIN_HEAD
#include "vGConfig.h"

class VGCORE_EXPORT FrPlugin;	//���ʵ������
class VGCORE_EXPORT FrPluginData;	//�������Ԫ��
class VGCORE_EXPORT FrPluginManager; //�������
class VGCORE_EXPORT FrPluginApp; //�������
#define TH_SAFETY //�̰߳�ȫָʾ��
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
	//!����Ŀ¼����Ĳ��
	void load(QDir _directory);
	//!����ָ���Ĳ��
	//�������ʧ�ܷ���false
	bool loadPlugin(QString _directory)TH_SAFETY;
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
	FrPluginData(QDir _path)TH_SAFETY; 
	//������������Ч���򷵻�true
	//���������Ч������object�������
	bool isInvalid()const;
	//���»�ȡ�������
	void updateProperty()TH_SAFETY;
	//��ȡ���
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

//����һ���߳���
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