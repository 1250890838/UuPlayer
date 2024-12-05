#ifndef UUENGINE_GLOBAL_H
#define UUENGINE_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(ENGINE_EXPORT_SYMBOLS)
#define ENGINE_DLL_EXPORT Q_DECL_EXPORT
#else
#define ENGINE_DLL_EXPORT Q_DECL_IMPORT
#endif
#endif