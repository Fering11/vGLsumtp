#ifndef VGTIME_GLOBAL_H
#define VGTIME_GLOBAL_H

#include <QtCore/qglobal.h>
#include "vghead.hpp"
#if defined(VGTIME_LIBRARY)
#  define VGTIME_EXPORT Q_DECL_EXPORT
#else
#  define VGTIME_EXPORT Q_DECL_IMPORT
#endif
extern "C" {
	VGTIME_EXPORT vGAppWidBase* get_object(vGMenuBase* _parent,vGPlugin*);
	VGTIME_EXPORT void destory_object(vGAppWidBase* _parent);
	VGTIME_EXPORT void get_info(vGPluginInfo* _info);

	//获取全局实例
	VGTIME_EXPORT FrPlugin* GetInstance();
}
#endif // VGTIME_GLOBAL_H
