#ifndef PLAY_SERVICE_H
#define PLAY_SERVICE_H

#include "audio_player.h"
#include "model/media_item_model.h"
#include "service_global.h"
#include "types.h"

#include <QList>
#include <QObject>

using namespace entities;
// 播放服务、存储播放列表

namespace service {

using namespace play_mode;
class SERVICE_DLL_EXPORT PlayService : public QObject {
  Q_OBJECT

 public:
 public:
  PlayService();
  bool isPlaying();
  qint64 duration();
  qint64 position();
  void setPosition(quint64 position);
  qint64 num();
  PlayMode playbackMode();
  void setPlaybackMode(PlayMode mode);
  float volumn();
  void setVolumn(float volumn);
  // interface public:
  void play(qulonglong id);
  void pause();
  void next();
  void previous();
  void play();
  void appendMediaId(qulonglong id);
  void insertNext(qulonglong id);
  entities::MediaItem currentPlayItem();
 private slots:
  void onPlaybackStateChanged(QMediaPlayer::PlaybackState state);
  void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
 private:
  void operateForPlaybackMode();
 private:
  engine::MediaPlayer m_player;
  QList<MediaItem> m_medias;
  PlayMode m_playbackMode;
  quint32 m_currentIndex;
 signals:
  void playingChanged(bool b);
  void durationChanged(qint64 duration);
  void positionChanged(qint64 position);
  void currentPlayItemChanged();
  void numChanged();
  void playbackModeChanged();
  void volumnChanged(float);
};
}  // namespace service
#endif  // PLAY_SERVICE_H
