#include <QWKQuick/qwkquickglobal.h>

#include <qqml.h>
#include <qthread.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtGlobal>
#include <QtQml/QQmlExtensionPlugin>

#include "engine/audio_player.h"
#include "network/basic_network.h"
#include "service/login_service.h"
#include "service/song_service.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

Q_IMPORT_QML_PLUGIN(guiPlugin)

int main(int argc, char* argv[]) {

#ifdef Q_OS_WIN
  HMODULE hLib = LoadLibrary(TEXT("service.dll"));
#endif

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  QWK::registerTypes(&engine);
  engine.addImportPath(u"qrc:/gui/qml"_qs);  // register custom components

  qmlRegisterUncreatableMetaObject(network::error_code::staticMetaObject,
                                   "network.errorcode", 1, 0, "ErrorCode",
                                   "Error: only enums");
  /*
  qmlRegisterUncreatableMetaObject(service::PlayService::staticMetaObject,  // 元对象
                                   "service.api", 1, 0, "PlayService",
                                   "Cannot create PlayServiceEnums");
  */

  qmlRegisterSingletonType(QUrl(u"qrc:/gui/qml/assets/Icons.qml"_qs), "assets",
                           1, 0, "Icons");
  qmlRegisterSingletonType(QUrl(u"qrc:/gui/qml/assets/Skins.qml"_qs), "skins",
                           1, 0, "Skins");
  /*
  qRegisterMetaType<model::MediaItem*>("MediaItem*");
  qmlRegisterSingletonInstance<service::LoginService>("service", 1, 0, "LoginService",new service::LoginService());
  qmlRegisterSingletonInstance<service::PlaylistService>("service", 1, 0, "PlaylistsService", new service::PlaylistService());
  qmlRegisterSingletonInstance<service::SongService>(
    "service", 1, 0, "SongService", new service::SongService());
  */

  const QUrl url(u"qrc:/gui/qml/Main.qml"_qs);
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
