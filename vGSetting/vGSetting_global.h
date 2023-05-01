#ifndef VGSETTING_GLOBAL_H
#define VGSETTING_GLOBAL_H

#include <QtCore/qglobal.h>
#include "vghead.hpp"
#include "FrPlugin.hpp"

#define EXTERN_C  extern "C"
#if defined(VGSETTING_LIBRARY)
#  define VGSETTING_EXPORT Q_DECL_EXPORT
#else
#  define VGSETTING_EXPORT Q_DECL_IMPORT
#endif
extern "C" {
	VGSETTING_EXPORT vGAppWidBase* get_object(vGMenuBase* _parent, vGPlugin*);
	VGSETTING_EXPORT void destory_object(vGAppWidBase* _app);
	VGSETTING_EXPORT void get_info(vGPluginInfo* _info);

	VGSETTING_EXPORT bool GetProperty(FrPluginProperty* _property);
	VGSETTING_EXPORT FrPlugin* GetInstance();

}

#endif // VGSETTING_GLOBAL_H
