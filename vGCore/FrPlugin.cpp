#include "FrPlugin.hpp"
#include "vghead.hpp"

/////////////////////// FrPluginManager ######################################
///////////// 

FrPluginManager::FrPluginManager(){
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
//只有文件是可以加载的并且包含所需函数则不会抛异常
void FrPluginData::_load(QDir _path){
	QLibrary lib(_path.absolutePath());
	lib.load();
	if (lib.isLoaded()) {
		f_get_instance = reinterpret_cast<fget_instance_type>(lib.resolve("GetInstance"));
		f_get_property = reinterpret_cast<fget_property_type>(lib.resolve("GetProperty"));
		if (f_get_instance && f_get_property)return;
		FrThrowError(FrErrorStatue::InvalidFile, "The Plugin haven't standard function");
	}
	FrThrowError(FrErrorStatue::InvalidFile, "The File is not a loadable");
}


/////////////////////// FrPlugin ######################################
///////////// 



/////////////////////// FrPluginApp ######################################
///////////// 

