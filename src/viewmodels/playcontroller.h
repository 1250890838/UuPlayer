#pragma once

#include <QObject>
#include <QUrl>
#include <QVariantList>

#include "audioplayer.h"
#include "entities/mediaitem.h"
#include "entities/types.h"
#include "models/mediaitemmodel.h"

namespace core {
class SongRepository;
}

namespace viewmodel {

class PlayController : public QObject {
  Q_OBJECT
  Q_PROPERTY(bool playing READ isPlaying NOTIFY playingChanged)
  Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
  Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY
                 positionChanged)
  Q_PROPERTY(float volume READ volume WRITE setVolume NOTIFY volumeChanged)
  Q_PROPERTY(PlayMode playbackMode READ playbackMode WRITE setPlaybackMode
                 NOTIFY playbackModeChanged)
  Q_PROPERTY(entities::MediaItem currentPlayItem READ currentPlayItem NOTIFY
                 currentPlayItemChanged)
  Q_PROPERTY(int count READ count NOTIFY countChanged)
  Q_PROPERTY(MediaItemModel* playlist READ playlist CONSTANT)

 public:
  enum PlayMode { Sequentially, ListLoop, SingleLoop, Shuffle };
  Q_ENUM(PlayMode)

  explicit PlayController(core::SongRepository* songs,
                          QObject* parent = nullptr);

  bool isPlaying() const;
  qint64 duration() const;
  qint64 position() const;
  void setPosition(qint64 position);
  float volume() const;
  void setVolume(float volume);
  PlayMode playbackMode() const;
  void setPlaybackMode(PlayMode mode);
  entities::MediaItem currentPlayItem() const { return m_currentItem; }
  int count() const;
  MediaItemModel* playlist() { return &m_playlist; }

  Q_INVOKABLE void play();
  Q_INVOKABLE void pause();
  Q_INVOKABLE void next();
  Q_INVOKABLE void previous();
  Q_INVOKABLE void playItem(const entities::MediaItem& item);
  Q_INVOKABLE void playById(qulonglong id);
  Q_INVOKABLE void enqueue(const entities::MediaItem& item);

  void playAll(const QList<entities::MediaItem>& items);

 signals:
  void playingChanged();
  void durationChanged();
  void positionChanged();
  void volumeChanged();
  void playbackModeChanged();
  void currentPlayItemChanged();
  void countChanged();

 private slots:
  void onUrlReady(error_code::ErrorCode code, qulonglong id, const QUrl& url);
  void onLyricReady(error_code::ErrorCode code, qulonglong id,
                    const QVariantList& lyrics);
  void onPlaybackStateChanged(QMediaPlayer::PlaybackState state);
  void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

 private:
  void startIndex(int index);
  void advance(bool forward);
  void setCurrent(const entities::MediaItem& item);

  core::SongRepository* m_songs = nullptr;
  core::AudioPlayer m_player;
  MediaItemModel m_playlist;
  entities::MediaItem m_currentItem;
  PlayMode m_playbackMode = ListLoop;
  int m_currentIndex = -1;
  qulonglong m_pendingUrlId = 0;
};

}
