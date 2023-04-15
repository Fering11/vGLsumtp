#ifndef VGSETTING_GLOBAL_H
#define VGSETTING_GLOBAL_H

#include <QtCore/qglobal.h>
#include "vghead.hpp"

#define EXTERN_C  extern "C"
#if defined(VGSETTING_LIBRARY)
#  define VGSETTING_EXPORT Q_DECL_EXPORT
#else
#  define VGSETTING_EXPORT Q_DECL_IMPORT
#endif

EXTERN_C VGSETTING_EXPORT vGAppWidBase* get_object(vGMenuBase* _parent,vGPlugin*);
EXTERN_C VGSETTING_EXPORT void destory_object(vGAppWidBase* _app);
EXTERN_C VGSETTING_EXPORT void get_info(vGPluginInfo* _info);

#endif // VGSETTING_GLOBAL_H
