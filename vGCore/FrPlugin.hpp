/*
*	vGLsumtp head file
*	���������湦��
*/

#ifndef FP_PLUGIN_HEAD
#define FP_PLUGIN_HEAD
#include "vGConfig.h"

class vGMenuBase;

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
	//STL vector::at���غ���
	FrPluginData& at(size_t pos)TH_SAFETY;
	//ɾ�����,_posָ��λ�ã������׳�std�쳣
	//�������û������
	bool remove(size_t _pos)TH_SAFETY;
	//���ز��ָ��
	std::vector<FrPluginData*> plugins()TH_SAFETY;
private:
	bool __remove(std::vector<FrPluginData>::iterator _it);
	QReadWriteLock lock_;
	std::vector<FrPluginData> data_;
};
//�����̣߳�����һ�������̬�����
class FrPluginData {
public:
	using fget_property_type = bool(*)(FrPluginProperty*);
	using fget_instance_type = FrPlugin*(*)();

	FrPluginData(FrPluginData&& _object)noexcept;
	//����path���ز��
	//�������쳣
	FrPluginData(QDir _path)TH_SAFETY;
	~FrPluginData()TH_SAFETY;
	//������������Ч���򷵻�true
	//���������Ч������object�������
	bool isInvalid()const;
	//���»�ȡ�������
	void updateProperty()TH_SAFETY;
	//��ȡ���
	//!���object_����Ϊ�գ���ᴴ������
	//���������ȷ�����޷������ַʱ(ʧ��)����nullptr
	//TODO ����û�п����̣߳�����������Ŀ�޸�
	QPointer<FrPlugin> plugin()TH_SAFETY;
	QPointer<FrPlugin> plugin()const;
	//��ȡ���������
	FrPluginProperty property()const;
	//�ͷŸò��������ֹAPP����
	// overtime ��ʱʱ�䣬force�Ƿ�ǿ��(�����Ȼ�ȡ��)
	//������������У����QThread::exit�˳�
	//!����overtime����forceΪ�棬������thread��terminial
	bool release(const int overtime = -1,bool force = false)TH_SAFETY;
	//���ص�ǰ���̶߳������Ϊ����˵���߳�û�п�ʼ����
	QThread* thread();
private:
	void _load(QDir _path)TH_SAFETY;
	bool _is_invalid()const;

	QReadWriteLock lock_;
	fget_property_type f_get_property;
	fget_instance_type f_get_instance;
	QThread* plugin_thread_; //������ڵ��߳�
	QPointer<FrPlugin> object_;
	FrPluginProperty property_;
};

//����һ���߳���
class FrPlugin :public QObject {
	Q_OBJECT
public:
	//�����ʼ�������������ʼ�����ڶ���
	FrPlugin();
	~FrPlugin();
	//��ʼ���������
	virtual bool initialize();
	//��ȡ���ڶ���
	QPointer<FrPluginApp> widget();
private:
	FrPluginApp* widget_;
};

class FrPluginApp:public QWidget {
public:
	FrPluginApp(vGMenuBase* _menu, FrPlugin* _plugin);
private:

	QPointer<FrPlugin> plugin_;
};



#endif //FP_PLUGIN_HEAD