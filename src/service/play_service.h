#ifndef PLAY_SERVICE_H
#define PLAY_SERVICE_H

#include "audio_player.h"
#include "model/media_item_model.h"

#include <QList>
#include <QObject>

// 播放服务、存储播放列表

namespace service {
class PlayService : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
  QML_NAMED_ELEMENT(PlayService)

  Q_PROPERTY(bool playing READ isPlaying NOTIFY playingChanged)
  Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
  Q_PROPERTY(
      qint64 position READ position WRITE setPosition NOTIFY positionChanged)
  Q_PROPERTY(model::MediaItem currentPlayItem  READ currentPlayItem NOTIFY currentPlayItemChanged)
  Q_PROPERTY(qint64 num READ num NOTIFY numChanged)
  Q_PROPERTY(PlaybackMode playbackMode READ playbackMode WRITE setPlaybackMode NOTIFY playbackModeChanged)
  Q_PROPERTY(model::MediaItemModel* playbacklist READ playbacklist CONSTANT)
 public:
  enum class PlaybackMode {
    Sequentially,
    ListLoop,
    SingleLoop,
    Shuffle
  };
  Q_ENUM(PlaybackMode) // 注册枚举到元对象系统
 public:
  PlayService();
  bool isPlaying();
  qint64 duration();
  qint64 position();
  void setPosition(quint64 position);
  qint64 num();
  PlaybackMode playbackMode();
  model::MediaItemModel* playbacklist();
  void setPlaybackMode(PlaybackMode mode);
  // interface
 public:
  Q_INVOKABLE void play(qulonglong id);
  Q_INVOKABLE void pause();
  Q_INVOKABLE void next();
  Q_INVOKABLE void previous();
  Q_INVOKABLE void play();
  Q_INVOKABLE void appendMediaId(qulonglong id);
  Q_INVOKABLE void insertNext(qulonglong id);
  Q_INVOKABLE model::MediaItem currentPlayItem();
 private slots:
  void onPlaybackStateChanged(QMediaPlayer::PlaybackState state);
  void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
 private:
  void operateForPlaybackMode();
 private:
  model::MediaItemModel m_playbacklistModel;
  engine::MediaPlayer m_player;
 // QList<model::MediaItem*> m_medias;
  PlaybackMode m_playbackMode;
  quint32 m_currentIndex;
 signals:
  void playingChanged(bool b);
  void durationChanged(qint64 duration);
  void positionChanged(qint64 position);
  void currentPlayItemChanged();
  void numChanged();
  void playbackModeChanged();
};
}  // namespace service
#endif  // PLAY_SERVICE_H
