#ifndef VGCORE_GLOBAL_H
#define VGCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(VGCORE_LIBRARY)
#  define VGCORE_EXPORT Q_DECL_EXPORT
#else
#  define VGCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // VGCORE_GLOBAL_H
