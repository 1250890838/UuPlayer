#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/qqml.h>

#include <QWKQuick/qwkquickglobal.h>

#include "app/appcontext.h"
#include "ui/imageprovider.h"

void qml_register_types_app();

int main(int argc, char* argv[]) {
  QGuiApplication application(argc, argv);

  app::AppContext context;

  qml_register_types_app();

  QQmlApplicationEngine engine;
  QWK::registerTypes(&engine);

  engine.addImageProvider(QStringLiteral("net"), new ui::ImageProvider);

  qmlRegisterUncreatableMetaObject(error_code::staticMetaObject, "App.Enums", 1,
                                   0, "ErrorCode", "ErrorCode 只用于枚举");
  qmlRegisterUncreatableMetaObject(sound_level::staticMetaObject, "App.Enums",
                                   1, 0, "SoundLevel",
                                   "SoundLevel 只用于枚举");

  qmlRegisterSingletonInstance("app", 1, 0, "PlayController", context.play());
  qmlRegisterSingletonInstance("app", 1, 0, "LoginController",
                               context.login());
  qmlRegisterSingletonInstance("app", 1, 0, "PlaylistHubController",
                               context.hub());
  qmlRegisterSingletonInstance("app", 1, 0, "PlaylistDetailController",
                               context.detail());

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &application,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

  engine.loadFromModule("app", "Main");

  return application.exec();
}
