#ifndef GPI_ABOUT_GLOBAL_H
#define GPI_ABOUT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GPI_ABOUT_LIBRARY)
#  define GPI_ABOUT_EXPORT Q_DECL_EXPORT
#else
#  define GPI_ABOUT_EXPORT Q_DECL_IMPORT
#endif

#endif // GPI_ABOUT_GLOBAL_H
