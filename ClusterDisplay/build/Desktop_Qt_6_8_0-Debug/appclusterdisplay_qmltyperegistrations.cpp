/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#if __has_include(<BatteryIconObj.hpp>)
#  include <BatteryIconObj.hpp>
#endif
#if __has_include(<SpeedometerObj.hpp>)
#  include <SpeedometerObj.hpp>
#endif


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_ClusterDisplay()
{
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    qmlRegisterTypesAndRevisions<BatteryIconObj>("ClusterDisplay", 1);
    qmlRegisterTypesAndRevisions<SpeedometerObj>("ClusterDisplay", 1);
    QT_WARNING_POP
    qmlRegisterModule("ClusterDisplay", 1, 0);
}

static const QQmlModuleRegistration clusterDisplayRegistration("ClusterDisplay", qml_register_types_ClusterDisplay);