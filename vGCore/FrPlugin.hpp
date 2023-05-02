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
class VGCORE_EXPORT FrPluginWidget; //�������
#define TH_SAFETY //�̰߳�ȫָʾ��
//�����Ϣ
struct FrPluginProperty {
	QByteArray version;
	QByteArray package; //www.time.app
	QString description;
	QString name;
	QPixmap logo;
	//���ظ�ʽ{ǰ׺��, Ӧ����, ����}
	static QByteArrayList SplitPackage(const QByteArray& _pk) {
		QByteArrayList result;
		int left = _pk.indexOf('.');
		int right = _pk.indexOf('.', left + 1);
		return { _pk.left(left),_pk.mid(left + 1,right - left - 1),_pk.mid(right + 1) };
	}
};
//�����߳�
class FrPluginManager {
public:
	using SeReType = std::vector<FrPluginData*>;
	FrPluginManager();
	~FrPluginManager();
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
	//�ͷ����в��
	void release()TH_SAFETY;
	//����,���ض�Ӧ�����ָ��
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
//�����̣߳�����һ�������̬�����
class FrPluginData {
public:
	using fget_property_type = bool(*)(FrPluginProperty*);
	using fget_instance_type = FrPlugin*(*)();

	FrPluginData(FrPluginData&& _object)noexcept;
	FrPluginData(const FrPluginData&) = delete;
	FrPluginData& operator=(const FrPluginData&) = delete;
	FrPluginData& operator=(FrPluginData&&);
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
	const FrPluginProperty& property()const;
	//�ͷŸò��������ֹAPP����
	// overtime ��ʱʱ�䣬force�Ƿ�ǿ��(�����Ȼ�ȡ��)
	//������������У����QThread::exit�˳�
	//!����overtime����forceΪ�棬������thread��terminial
	bool release(const int overtime = -1,bool force = false)TH_SAFETY;
	//���ص�ǰ���̶߳������Ϊ����˵���߳�û�п�ʼ����
	QThread* thread()const;
	//�����߳�,�������Ѿ������У���ô��ʲôҲ����
	void start(QThread::Priority = QThread::InheritPriority);
	//�Ƿ��Ƿ���
	bool isService()const;
	//����Ƿ�������
	bool isRunning()const;
private:
	void _load(QDir _path)TH_SAFETY;
	bool _is_invalid()const;

	QReadWriteLock lock_;
	fget_property_type f_get_property;
	fget_instance_type f_get_instance;
	//������ڵ��߳�
	//��������ֻ��object_��һ��(����鿴release)
	QThread* plugin_thread_;
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
	//��ʼ�������������ʱ��ʼ�����ڶ���
	//����������ڲ��������ʱ�����
	virtual bool initialize();
	//��ȡ���ڶ���
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