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
using namespace play_mode;

class PlayController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
  Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged FINAL)
  Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged FINAL)
  Q_PROPERTY(qint64 position READ position NOTIFY positionChanged FINAL)
  // Q_PROPERTY(PlayMode playmode READ playmode NOTIFY playmodeChanged)
  Q_PROPERTY(float volumn READ volumn NOTIFY volumnChanged)
  Q_PROPERTY(MediaItem currMediaItem READ currMediaItem NOTIFY
                 currMediaItemChanged FINAL)

 public:
  Q_INVOKABLE void play(qulonglong id);
  Q_INVOKABLE void pause();
  Q_INVOKABLE void next();
  Q_INVOKABLE void previous();

  bool isPlaying() { return m_service->isPlaying(); }
  qint64 duration() { return m_service->duration(); }
  qint64 position() { return m_service->position(); }
  // PlayMode playmode() { return m_service->playbackMode(); }
  float volumn() { return m_service->volumn(); }
  MediaItem currMediaItem() { return m_service->currentPlayItem(); }

  PlayController(PlayService* service);
  static PlayController* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);
 signals:
  void isPlayingChanged();
  void durationChanged();
  void positionChanged();
  void playmodeChanged();
  void volumnChanged();
  void currMediaItemChanged();

 private:
  MediaItemModel m_mediasModel;
  QPointer<PlayService> m_service;
};
}  // namespace controller

#endif  // PLAYCONTROLLER_H
