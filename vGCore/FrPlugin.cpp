#include "FrPlugin.hpp"
#include "vghead.hpp"


/////////////////////// FrPluginManager ######################################
///////////// 

FrPluginManager::FrPluginManager(){
}

void FrPluginManager::load(QDir _dir){
	_dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	_dir.setSorting(QDir::Type);
	auto dir_list = _dir.entryInfoList();
	this->data_.reserve(dir_list.size());
	for (auto& file : dir_list) {
		loadPlugin(file.filePath());
	}
}
//��ֹ�ⲿֱ�Ӳ���data_
//FrPluginData�̲߳����̰߳�ȫ
std::vector<FrPluginData*> FrPluginManager::plugins(){
	QReadLocker lock(&this->lock_);
	std::vector<FrPluginData*> result;
	result.reserve(data_.size());
	for (auto& i : data_) {
		result.push_back(std::addressof(i));
	}
	return result;
}

bool FrPluginManager::__remove(std::vector<FrPluginData>::iterator _it){
	auto& fp = *_it;
	if (fp.thread()) {
		//��������ڣ���ɾ��
		return false;
	}
	data_.erase(_it);
}

bool FrPluginManager::remove(size_t _pos) {
	QWriteLocker lock(&this->lock_);
	return __remove(data_.begin() + _pos);
}

FrPluginData& FrPluginManager::at(size_t _pos){
	QReadLocker lock(&this->lock_);
	return data_.at(_pos);
}

bool FrPluginManager::loadPlugin(QString _file) {
	try {
		//����
		QWriteLocker lock(&this->lock_);
		FrPluginData data(_file);
		data_.push_back(std::move(data));
		return true;
	}
	catch (const FrError&) {
		//ʧ��һ�����ļ������µ�ʧ��,FrError�����쳣������
		//if (_error.code() != FrErrorStatue::InvalidFile) {}
	}
	catch (...) {
		vGlog->error("Loading the library '{}', an unusual exception occurred.", QSTD(_file));
	}
	return false;
}


/////////////////////// FrPluginData ######################################
///////////// 

FrPluginData::FrPluginData(FrPluginData&& _obj)noexcept{
	object_ = std::exchange(_obj.object_, nullptr);
	f_get_instance = std::exchange(_obj.f_get_instance, nullptr);
	f_get_property = std::exchange(_obj.f_get_property, nullptr);
	property_ = std::exchange(_obj.property_, FrPluginProperty{});
	plugin_thread_ = std::exchange(_obj.plugin_thread_, {});
}

FrPluginData::FrPluginData(QDir _path):
	f_get_property(nullptr), f_get_instance(nullptr),
	object_(nullptr), property_({}), plugin_thread_(nullptr){
	this->_load(_path);
}
FrPluginData::~FrPluginData(){
	release();
	plugin_thread_->deleteLater();
}
bool FrPluginData::isInvalid()const{
	//�о�û��Ҫ����,�ж�����ͬΪ��Ļ�����Ҳ����
	//QReadLocker lock(&this->lock_);
	return _is_invalid();
}
void FrPluginData::updateProperty(){
	QWriteLocker lock(&this->lock_); 
	f_get_property(&this->property_);
}
//ֻ���ļ��ǿ��Լ��صĲ��Ұ������躯���򲻻����쳣
void FrPluginData::_load(QDir _path){
	QLibrary lib(_path.absolutePath());
	lib.load();
	if (lib.isLoaded()) {
		//����
		QWriteLocker lock(&this->lock_);
		f_get_instance = reinterpret_cast<fget_instance_type>(lib.resolve("GetInstance"));
		f_get_property = reinterpret_cast<fget_property_type>(lib.resolve("GetProperty"));
		if (!this->_is_invalid()) {
			//������Ϣ���������ض���
			f_get_property(&this->property_);
			//updateProperty(); ��������
		}
		FrThrowError(FrErrorStatue::InvalidFile, "The Plugin haven't standard function");
	}
	FrThrowError(FrErrorStatue::InvalidFile, "The File is not a loadable");
}
QPointer<FrPlugin> FrPluginData::plugin() {
	if (!object_.isNull())return object_;
	QWriteLocker lock(&this->lock_);
	object_ = f_get_instance();
	if (object_.isNull()) {
		//�����������޷��������ز����ַ
		vGlog->error("QPointer<FrPlugin> FrPluginData::plugin():can't get the plugin's instance");
		return nullptr;
	}
	plugin_thread_ = new QThread();
	object_->moveToThread(plugin_thread_);
	//��֤FrPlugin��ȷ����
	QObject::connect(plugin_thread_, &QThread::finished, object_, &FrPlugin::deleteLater);
	return object_;
}
	
QPointer<FrPlugin> FrPluginData::plugin()const{
	return object_;
}
FrPluginProperty FrPluginData::property() const{
	//���ؽṹ���ͬʱ�ָ�������Ϣ���Ƚ��ټ���������
	return property_;
}
QThread* FrPluginData::thread(){
	return plugin_thread_;
}
bool FrPluginData::_is_invalid()const{
	return f_get_property && f_get_instance;
}
bool FrPluginData::release(const int _overtime, bool _force) {
	//������Σ�һ��Ҫ��ȡ����֮��Ų���(_force��������thread)
	if (lock_.tryLockForWrite(_overtime)) {
		plugin_thread_->exit();
		if (!plugin_thread_->wait(_overtime < 1 ?
			QDeadlineTimer(QDeadlineTimer::Forever) : QDeadlineTimer(_overtime))) {
			//�����ʱ�ˣ���ôֱ��ǿ��ɾ��
			vGlog->info("thread {} can't be released", size_t(QThread::currentThreadId()));
			if (_force)	plugin_thread_->terminate();
		}
		//�����߳��Ѿ�ֹͣ������FrPluginҲ�Ѿ�������
		//ɾ��plugin_thread
		plugin_thread_->deleteLater();
	}
	return false;
}

/////////////////////// FrPlugin ######################################
///////////// 


FrPlugin::FrPlugin():widget_(nullptr){
}

FrPlugin::~FrPlugin(){
	vGlog->info("Th:{} FrPlugin destructed", size_t(QThread::currentThreadId()));
}

bool FrPlugin::initialize()
{
	return false;
}


/////////////////////// FrPluginApp ######################################
///////////// 

FrPluginApp::FrPluginApp(vGMenuBase* _parent, FrPlugin* _plugin)
	:QWidget(_parent), plugin_(_plugin) {
	this->setVisible(false);//һ��ʼ��ʼ������Ϊ���ɼ�
}
