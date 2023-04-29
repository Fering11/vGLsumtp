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

bool FrPluginManager::loadPlugin(QString _file) {
	try {
		//����
		QWriteLocker lock(&this->lock_);
		FrPluginData data(_file);
		data_.push_back(std::move(data));
		return true;
	}
	catch (const FrError& _error) {
		//ʧ��һ�����ļ������µ�ʧ��,FrError�����쳣������
		//if (_error.code() != FrErrorStatue::InvalidFile) {}
	}
	catch (...) {
		vGlog->error("Loading the library '{}', an unusual exception occurred.", _file);
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
}

FrPluginData::FrPluginData(QDir _path):
	f_get_property(nullptr), f_get_instance(nullptr),
	object_(nullptr), property_({}) {
	this->_load(_path);
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
QPointer<FrPlugin> FrPluginData::plugin()const{
	return object_;
}
FrPluginProperty FrPluginData::property() const{
	//���ؽṹ���ͬʱ�ָ�������Ϣ���Ƚ��ټ���������
	return property_;
}
bool FrPluginData::_is_invalid()const{
	return f_get_property && f_get_instance;
}

/////////////////////// FrPlugin ######################################
///////////// 



/////////////////////// FrPluginApp ######################################
///////////// 

