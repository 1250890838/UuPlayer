#include <QWKQuick/qwkquickglobal.h>

#include <qqml.h>
#include <qthread.h>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtGlobal>
#include <QtQml/QQmlExtensionPlugin>

#include "image_provider.h"
#include "network/basic_network.h"
#include "service/login_service.h"
//#include "service/model/mediaitem_filterproxy_model.h"
#include "service/song_lyric_service.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

Q_IMPORT_QML_PLUGIN(guiPlugin)

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;
  QWK::registerTypes(&engine);
  engine.addImportPath(u"qrc:/gui/qml"_qs);  // register custom components
  engine.addImageProvider(QLatin1String("net"), new gui::ImageProvider);
  qmlRegisterUncreatableMetaObject(error_code::staticMetaObject, "App.Enums", 1,
                                   0, "ErrorCode",
                                   "Error: only error code enums");
  // qmlRegisterUncreatableMetaObject(sort_option::staticMetaObject, "App.Enums",
  //                                  1, 0, "SortOption",
  //                                  "Error: only sort option enums");
  qmlRegisterUncreatableMetaObject(sound_level::staticMetaObject, "App.Enums",
                                   1, 0, "SoundLevel",
                                   "Error: only sound level enums");
  qmlRegisterUncreatableMetaObject(play_mode::staticMetaObject, "App.Enums", 1,
                                   0, "PlayMode",
                                   "Error: only play mode enums");

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
