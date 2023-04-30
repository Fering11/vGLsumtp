#ifndef VGTIME_GLOBAL_H
#define VGTIME_GLOBAL_H

#include <QtCore/qglobal.h>
#include "vghead.hpp"
#include "FrPlugin.hpp"
#if defined(VGTIME_LIBRARY)
#  define VGTIME_EXPORT Q_DECL_EXPORT
#else
#  define VGTIME_EXPORT Q_DECL_IMPORT
#endif
extern "C" {
	VGTIME_EXPORT vGAppWidBase* get_object(vGMenuBase* _parent,vGPlugin*);
	VGTIME_EXPORT void destory_object(vGAppWidBase* _parent);
	VGTIME_EXPORT void get_info(vGPluginInfo* _info);

	//获取插件信息
	//确保无异常
	VGTIME_EXPORT bool GetProperty(FrPluginProperty* _property);
	//返回new的对象,销毁通过deleteLater实现
	//确保无异常
	VGTIME_EXPORT FrPlugin* GetInstance();
}
#endif // VGTIME_GLOBAL_H
