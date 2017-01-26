#ifndef QTAWSS3_GLOBAL_H
#define QTAWSS3_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTAWSS3_LIBRARY)
#  define QTAWSS3SHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTAWSS3SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTAWSS3_GLOBAL_H
