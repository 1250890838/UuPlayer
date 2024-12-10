#ifndef UUNETWORK_GLOBAL_H
#define UUNETWORK_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(NETWORK_EXPORT_SYMBOLS)
#define NETWORK_DLL_EXPORT Q_DECL_EXPORT
#else
#define NETWORK_DLL_EXPORT Q_DECL_IMPORT
#endif
#endif