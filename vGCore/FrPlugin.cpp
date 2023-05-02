#include "FrPlugin.hpp"
#include "vghead.hpp"


/////////////////////// FrPluginManager ######################################
///////////// 

FrPluginManager::FrPluginManager(){
}
//��ÿһ�������������
FrPluginManager::~FrPluginManager(){
	release();
}
void FrPluginManager::release() {
	QWriteLocker lock(&this->lock_);
	for (auto& plugin : data_) {
		plugin.release();
	}
	data_.clear();
}
FrPluginManager::SeReType FrPluginManager::search(const QString& _name){
	QReadLocker lock(&this->lock_);
	return __search([_name](const FrPluginProperty& _property) {
		return !_property.name.compare(_name);
		});
}
FrPluginManager::SeReType FrPluginManager::searchPackage(const QByteArray& _package){
	QReadLocker lock(&this->lock_);
	return __search([_package](const FrPluginProperty& _property) {
		return !_property.package.compare(_package);
		});
}
bool FrPluginManager::isExist(const QByteArray& _package)const{
	for (auto i = data_.begin(); i != data_.end(); ++i) {
		if (!i->property().package.compare(_package)) {
			return true;
		}
	}
	return false;
}
void FrPluginManager::load(QDir _dir){
	_dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	_dir.setSorting(QDir::Type);
	auto dir_list = _dir.entryInfoList();
	this->data_.reserve(dir_list.size());
	for (auto& file : dir_list) {
		try{
			loadPlugin(file.filePath());
		}catch (...){
			//�쳣��Ϊ�ļ����󣬲�����
		}
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

bool FrPluginManager::__remove(std::vector<FrPluginData>::const_iterator _it){
	auto& fp = *_it;
	if (fp.thread()) {
		//��������ڣ���ɾ��
		return false;
	}
	data_.erase(_it);
	return true;
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
		if (!isExist(data.property().package)) {
			data_.push_back(std::move(data));
			return true;
		}
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
	*this = std::move(_obj);
}

FrPluginData& FrPluginData::operator=(FrPluginData&& _obj){
	object_ = std::exchange(_obj.object_, nullptr);
	f_get_instance = std::exchange(_obj.f_get_instance, nullptr);
	f_get_property = std::exchange(_obj.f_get_property, nullptr);
	property_ = std::exchange(_obj.property_, FrPluginProperty{});
	plugin_thread_ = std::exchange(_obj.plugin_thread_, {});
	return *this;
}

FrPluginData::FrPluginData(QDir _path):
	f_get_property(nullptr), f_get_instance(nullptr),
	object_(nullptr), property_({}), plugin_thread_(nullptr){
	this->_load(_path);
}
FrPluginData::~FrPluginData(){
	release();
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
			return;
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
	//QObject::connect(plugin_thread_, &QThread::finished, object_, &FrPlugin::deleteLater);
	QObject::connect(plugin_thread_, &QThread::finished, object_, [this]() {
		vGlog->info("FrPluginData Thread finished,Now is preparing to delete the object");
		object_->deleteLater();
		});
	return object_;
}
	
QPointer<FrPlugin> FrPluginData::plugin()const{
	return object_;
}
const FrPluginProperty& FrPluginData::property() const{
	//���ؽṹ���ͬʱ�ָ�������Ϣ���Ƚ��ټ���������
	//�����ٶȣ��ʷ�������
	return property_;
}
QThread* FrPluginData::thread()const{
	plugin_thread_->start();
	return plugin_thread_;
}
void FrPluginData::start(QThread::Priority _py) {
	if (!isRunning()) {
		QReadLocker lock(&this->lock_);
		if (!plugin_thread_) {
			//����̶߳��󲻴��ھʹ���
			lock.unlock();
			plugin();
			lock.relock();
		}
		object_->initialize();
		plugin_thread_->start(_py);
	}
}
//TODO ���Ժ���
bool FrPluginData::isService() const{
	//�����ڴ�����������property���������£���ʹ�û�����
	QByteArray package = property_.package;
	int pos = package.lastIndexOf('.');
	return package.right(package.size() - pos - 1).compare("app");
}
bool FrPluginData::isRunning() const{
	return plugin_thread_ && plugin_thread_->isRunning();
}
bool FrPluginData::_is_invalid()const{
	return f_get_property == 0 && f_get_instance == 0;
}
//�ú����ᱻ�ظ�����(plugin_thread_�Ѿ�deleteLater�������)
bool FrPluginData::release(const int _overtime, bool _force) {
	//������Σ�һ��Ҫ��ȡ����֮��Ų���(_force��������thread)
	//plugin_thread_Ϊ����˵���Ѿ��ͷŻ���û�г�ʼ��plugin
	if (plugin_thread_&&lock_.tryLockForWrite(_overtime)) {
		plugin_thread_->exit();
		if (!plugin_thread_->wait(_overtime < 1 ?
			QDeadlineTimer(QDeadlineTimer::Forever) : QDeadlineTimer(_overtime))) {
			//�����ʱ�ˣ���ôֱ��ǿ��ɾ��
			//TODO���߳̽��в���(QEvent)
			vGlog->info("thread {} can't be released", size_t(QThread::currentThreadId()));
			if (_force)	plugin_thread_->terminate();
			lock_.unlock();
			return _force;//Ĭ��ǿ���ͷ��ǳɹ���
		}
		//�����߳��Ѿ�ֹͣ������FrPluginҲ�Ѿ�������
		//ɾ��plugin_thread
		plugin_thread_->deleteLater();
		lock_.unlock();
		return true;
	}
	//release�Ͼ���ɾ��plugin_thread_
	//�ᵽ�����˵��û���õ�������plugin_thread_�ǿ�
	return plugin_thread_ == nullptr;
}

/////////////////////// FrPlugin ######################################
///////////// 


FrPlugin::FrPlugin():
	QObject(nullptr), widget_(nullptr) {
}

FrPlugin::~FrPlugin(){
	vGlog->info("Th:{} FrPlugin destructed", size_t(QThread::currentThreadId()));
}

bool FrPlugin::initialize(){
	return false;
}

QPointer<FrPluginWidget> FrPlugin::widget()const{
	return widget_;
}


/////////////////////// FrPluginWidget ######################################
///////////// 

FrPluginWidget::FrPluginWidget(vGMenuBase* _parent, FrPlugin* _plugin)
	:QWidget(_parent), plugin_(_plugin) {
	this->setVisible(false);//һ��ʼ��ʼ������Ϊ���ɼ�
}

QPointer<FrPlugin> FrPluginWidget::plugin() const
{
	return plugin_;
}
