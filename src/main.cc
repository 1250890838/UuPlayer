#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml/qqml.h>

#include <QWKQuick/qwkquickglobal.h>

#include "app/appcontext.h"
#include "ui/imageprovider.h"
#include "ui/imagestore.h"
#include "ui/thememanager.h"

void qml_register_types_app();

int main(int argc, char* argv[]) {
  QGuiApplication application(argc, argv);

  app::AppContext context;
  qml_register_types_app();

  QQmlApplicationEngine engine;
  QWK::registerTypes(&engine);

  auto* imageStore = new ui::ImageStore(context.api(), &engine);
  auto* themeManager = new ui::ThemeManager(imageStore, &engine);
  engine.rootContext()->setContextProperty(QStringLiteral("ThemeManager"),
                                           themeManager);
  engine.addImageProvider(QStringLiteral("net"),
                          new ui::ImageProvider(imageStore));

  qmlRegisterUncreatableMetaObject(error_code::staticMetaObject, "App.Enums", 1,
                                   0, "ErrorCode", "ErrorCode 只用于枚举");
  qmlRegisterUncreatableMetaObject(sound_level::staticMetaObject, "App.Enums",
                                   1, 0, "SoundLevel",
                                   "SoundLevel 只用于枚举");
  qmlRegisterUncreatableMetaObject(play_mode::staticMetaObject, "App.Enums", 1,
                                   0, "PlayMode", "PlayMode 只用于枚举");

  qmlRegisterSingletonInstance("app", 1, 0, "PlayController", context.play());
  qmlRegisterSingletonInstance("app", 1, 0, "LyricsViewController",
                               context.lyrics());
  qmlRegisterSingletonInstance("app", 1, 0, "LoginController",
                               context.login());

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &application,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

  engine.loadFromModule("app", "Main");

  return application.exec();
}