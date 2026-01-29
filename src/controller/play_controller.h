#ifndef PLAYCONTROLLER_H
#define PLAYCONTROLLER_H

#include <QObject>
#include <QObjectBindableProperty>
#include <QQmlEngine>

#include "model/media_item_model.h"
#include "play_service.h"
namespace controller {
using namespace service;
using namespace entities;
using namespace model;

class PlayController : QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
  Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged)
  Q_PROPERTY(qin64 duration READ duration NOTIFY durationChanged)
  Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
  Q_PROPERTY(play_mode::PlayMode playmode READ playmode NOTIFY playmodeChanged)
  Q_PROPERTY(float volumn READ volumn NOTIFY volumnChanged)

  bool isPlaying() { return m_service->isPlaying(); }
  qint64 duration() { return m_service->duration(); }
  qint64 position() { return m_service->position(); }
  PlayMode playbackMode() { return m_service->playbackMode(); }
  float volumn() { return m_service->volumn(); }

 public:
  PlayController(PlayService* service);
  static PlayController* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
 signals:
  void isPlayingChanged();
  void durationChanged();
  void positionChnaged();
  void playmodeChanged();
  void volumnChanged();

 private:
  MediaItemModel m_mediasModel;
  QPointer<PlayService> m_service;
};
}  // namespace controller

#endif // PLAYCONTROLLER_H
