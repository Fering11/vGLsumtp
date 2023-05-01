#include "FrPlugin.hpp"
#include "vghead.hpp"


/////////////////////// FrPluginManager ######################################
///////////// 

FrPluginManager::FrPluginManager(){
}
//对每一个插件进行销毁
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
void FrPluginManager::load(QDir _dir){
	_dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
	_dir.setSorting(QDir::Type);
	auto dir_list = _dir.entryInfoList();
	this->data_.reserve(dir_list.size());
	for (auto& file : dir_list) {
		try{
			loadPlugin(file.filePath());
		}catch (...){
			//异常视为文件错误，不处理
		}
	}
}
//防止外部直接操作data_
//FrPluginData线程操作线程安全
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
		//插件还存在，不删除
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
		//上锁
		QWriteLocker lock(&this->lock_);
		FrPluginData data(_file);
		data_.push_back(std::move(data));
		return true;
	}
	catch (const FrError&) {
		//失败一般是文件错误导致的失败,FrError错误异常不处理
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
	//感觉没必要加锁,判断两个同为真的汇编代码也不多
	//QReadLocker lock(&this->lock_);
	return _is_invalid();
}
void FrPluginData::updateProperty(){
	QWriteLocker lock(&this->lock_); 
	f_get_property(&this->property_);
}
//只有文件是可以加载的并且包含所需函数则不会抛异常
void FrPluginData::_load(QDir _path){
	QLibrary lib(_path.absolutePath());
	lib.load();
	if (lib.isLoaded()) {
		//上锁
		QWriteLocker lock(&this->lock_);
		f_get_instance = reinterpret_cast<fget_instance_type>(lib.resolve("GetInstance"));
		f_get_property = reinterpret_cast<fget_property_type>(lib.resolve("GetProperty"));
		if (!this->_is_invalid()) {
			//加载信息，但不加载对象
			f_get_property(&this->property_);
			return;
			//updateProperty(); 死锁现象
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
		//插件对象错误，无法正常返回插件地址
		vGlog->error("QPointer<FrPlugin> FrPluginData::plugin():can't get the plugin's instance");
		return nullptr;
	}
	plugin_thread_ = new QThread();
	object_->moveToThread(plugin_thread_);
	//保证FrPlugin正确析构
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
	//返回结构体的同时又更新了信息，比较少见，不考虑
	//考虑速度，故返回引用
	return property_;
}
QThread* FrPluginData::thread()const{
	plugin_thread_->start();
	return plugin_thread_;
}
void FrPluginData::start(QThread::Priority _py){
	QReadLocker lock(&this->lock_);
	if (!plugin_thread_) {
		//如果线程对象不存在就创建
		lock.unlock();
		plugin();
		lock.relock();
	}
	object_->initialize();
	plugin_thread_->start(_py);
}
//TODO 测试函数
bool FrPluginData::isService() const{
	//不存在大量拷贝，且property不经常更新，不使用互斥锁
	QByteArray package = property_.package;
	int pos = package.lastIndexOf('.');
	return package.right(package.size() - pos - 1).compare("app");
}
bool FrPluginData::_is_invalid()const{
	return f_get_property == 0 && f_get_instance == 0;
}
//该函数会被重复调用(plugin_thread_已经deleteLater的情况下)
bool FrPluginData::release(const int _overtime, bool _force) {
	//无论如何，一定要获取到锁之后才操作(_force仅仅对于thread)
	//plugin_thread_为空则说明已经释放或者没有初始化plugin
	if (plugin_thread_&&lock_.tryLockForWrite(_overtime)) {
		plugin_thread_->exit();
		if (!plugin_thread_->wait(_overtime < 1 ?
			QDeadlineTimer(QDeadlineTimer::Forever) : QDeadlineTimer(_overtime))) {
			//如果超时了，那么直接强制删除
			//TODO在线程进行测试(QEvent)
			vGlog->info("thread {} can't be released", size_t(QThread::currentThreadId()));
			if (_force)	plugin_thread_->terminate();
			lock_.unlock();
			return _force;//默认强制释放是成功的
		}
		//现在线程已经停止下来，FrPlugin也已经被析构
		//删除plugin_thread
		plugin_thread_->deleteLater();
		lock_.unlock();
		return true;
	}
	//release上就是删除plugin_thread_
	//会到这里就说明没有拿到锁或者plugin_thread_是空
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
	this->setVisible(false);//一开始初始化设置为不可见
}

QPointer<FrPlugin> FrPluginWidget::plugin() const
{
	return plugin_;
}
