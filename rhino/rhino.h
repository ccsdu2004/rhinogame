#ifndef RHINO_H
#define RHINO_H
#include <qglobal.h>
#include <QString>

#  if defined(RHINO_BUILD_LIB)
#    define RHINO_EXPORT Q_DECL_EXPORT
#  else
#    define RHINO_EXPORT Q_DECL_IMPORT
#  endif

QString RHINO_EXPORT rhinoVersion();

class QWidget;

#endif