#include <QWKQuick/qwkquickglobal.h>

#include <qqml.h>
#include <qthread.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtGlobal>
#include <QtQml/QQmlExtensionPlugin>

#include "network/basic_network.h"
#include "service/login_service.h"
#include "service/model/mediaitem_filterproxy_model.h"
#include "service/song_service.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

Q_IMPORT_QML_PLUGIN(guiPlugin)

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  QWK::registerTypes(&engine);
  engine.addImportPath(u"qrc:/gui/qml"_qs);  // register custom components
  qmlRegisterUncreatableMetaObject(network::error_code::staticMetaObject,
                                   "network.errorcode", 1, 0, "ErrorCode",
                                   "Error: only error code enums");
  qmlRegisterUncreatableMetaObject(sort_option::staticMetaObject,
                                   "model.sortoption", 1, 0, "SortOption",
                                   "Error: only sort option enums");

  qmlRegisterSingletonType(QUrl(u"qrc:/gui/qml/assets/Icons.qml"_qs), "assets",
                           1, 0, "Icons");
  qmlRegisterSingletonType(QUrl(u"qrc:/gui/qml/assets/Skins.qml"_qs), "skins",
                           1, 0, "Skins");
  const QUrl url(u"qrc:/gui/qml/Main.qml"_qs);
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
