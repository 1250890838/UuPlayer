#pragma once

#include <QObject>
#include <QUrl>
#include <optional>

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
  Q_PROPERTY(bool isPlaying READ isPlaying NOTIFY isPlayingChanged FINAL)
  Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged FINAL)
  Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY
                 positionChanged FINAL)
  Q_PROPERTY(play_mode::PlayMode playmode READ playmode WRITE setPlaymode
                 NOTIFY playmodeChanged)
  Q_PROPERTY(float volumn READ volumn WRITE setVolumn NOTIFY volumnChanged)
  Q_PROPERTY(entities::MediaItem currMediaItem READ currMediaItem NOTIFY
                 currMediaItemChanged FINAL)
  Q_PROPERTY(MediaItemModel* medias READ medias NOTIFY mediasChanged FINAL)

 public:
  explicit PlayController(core::SongRepository* songs,
                          QObject* parent = nullptr);

  Q_INVOKABLE void play(qulonglong id);
  Q_INVOKABLE void play();
  Q_INVOKABLE void pause();
  Q_INVOKABLE void next();
  Q_INVOKABLE void previous();

  bool isPlaying() const;
  qint64 duration() const;
  qint64 position() const;
  void setPosition(qint64 position);
  play_mode::PlayMode playmode() const;
  void setPlaymode(play_mode::PlayMode mode);
  float volumn() const;
  void setVolumn(float volumn);
  entities::MediaItem currMediaItem() const { return m_currentItem; }
  MediaItemModel* medias() { return &m_medias; }

  void appendMediaItem(const entities::MediaItem& item);
  void insertNextToPlayingItem(const entities::MediaItem& item);
  bool hasUrl(qulonglong id) const;

  void play(qulonglong id, sound_level::SoundQualityLevel level);

 signals:
  void isPlayingChanged();
  void durationChanged();
  void positionChanged(qint64 position);
  void playmodeChanged();
  void volumnChanged();
  void currMediaItemChanged();
  void mediasChanged();

 private slots:
  void onUrlReady(error_code::ErrorCode code, qulonglong id, const QUrl& url);
  void onPlaybackStateChanged(QMediaPlayer::PlaybackState state);
  void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

 private:
  void playByIndex(int index);
  void operateForPlaybackMode(bool forward);
  void setCurrentItem(int index);

  core::SongRepository* m_songs = nullptr;
  core::AudioPlayer m_player;
  MediaItemModel m_medias;
  entities::MediaItem m_currentItem;
  play_mode::PlayMode m_playbackMode = play_mode::ListLoop;
  std::optional<int> m_currentIndex;
  qulonglong m_pendingUrlId = 0;
};

}  // namespace viewmodel