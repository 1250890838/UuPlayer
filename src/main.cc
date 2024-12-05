#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlExtensionPlugin>
#include <qqml.h>

#include "engine/audio_player.h"
Q_IMPORT_QML_PLUGIN(guiPlugin)

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterSingletonType(QUrl("qrc:/gui/qml/assets/Icons.qml"), "assets", 1, 0, "Icons");
    qmlRegisterSingletonType<engine::MediaPlayer>("engine", 1, 0, "Player",&engine::MediaPlayer::getInstance);
    const QUrl url(u"qrc:/gui/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);
    
    return app.exec();
}
