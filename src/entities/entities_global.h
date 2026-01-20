#ifndef ENTITIES_GLOBAL_H
#define ENTITIES_GLOBAL_H
#include <QtCore/qglobal.h>

#if defined(ENTITIES_EXPORT_SYMBOLS)
#define ENTITIES_EXPORT Q_DECL_EXPORT  // 编译库时，它是 dllexport
#else
#define ENTITIES_EXPORT Q_DECL_IMPORT  // 别人用库时，它是 dllimport
#endif
#endif // ENTITIES_GLOBAL_H
