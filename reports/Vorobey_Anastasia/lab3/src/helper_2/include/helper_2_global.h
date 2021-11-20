#ifndef HELPER_2_GLOBAL_H
#define HELPER_2_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HELPER_2_LIBRARY)
#  define HELPER_2_EXPORT Q_DECL_EXPORT
#else
#  define HELPER_2_EXPORT Q_DECL_IMPORT
#endif

#endif // HELPER_2_GLOBAL_H
