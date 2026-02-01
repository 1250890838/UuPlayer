#include "play_service.h"
#include "recommended_playlist_service.h"

#include <QObject>
#include <QModelIndex>

namespace service {
PlayService::PlayService() : m_currentIndex(-1) {
  // connect(&m_player, &engine::MediaPlayer::playingChanged, this,
  //        &PlayService::playingChanged);
  connect(&m_player, &engine::MediaPlayer::durationChanged, this,
          &PlayService::durationChanged);
  connect(&m_player, &engine::MediaPlayer::positionChanged, this,
          &PlayService::positionChanged);
  connect(&m_player, &engine::MediaPlayer::playbackStateChanged, this,
          &PlayService::onPlaybackStateChanged);
  connect(&m_player, &engine::MediaPlayer::mediaStatusChanged, this,
          &PlayService::onMediaStatusChanged);
}

bool PlayService::isPlaying() {
  return m_player.isPlaying();
}

qint64 PlayService::duration() {
  return m_player.duration();
}

qint64 PlayService::position() {
  return m_player.position();
}

qint64 PlayService::num() {
  return m_medias.count();
}

void PlayService::setPlaybackMode(PlayMode mode) {
  m_playbackMode = mode;
  emit playbackModeChanged();
}

float PlayService::volumn() {
  auto audioOutput = m_player.audioOutput();
  if (audioOutput != nullptr) {
    return audioOutput->volume();
  }
  return 0.0f;
}

void PlayService::setVolumn(float volumn) {
  auto audioOutput = m_player.audioOutput();
  if (audioOutput != nullptr) {
    audioOutput->setVolume(volumn);
    emit volumnChanged(volumn);
  }
}

void PlayService::setPosition(quint64 position) {
  m_player.setPosition(position);
}

void PlayService::play(qulonglong id) {
  for (int i = 0; i < m_medias.size(); i++) {
    if (m_medias[i].id == id) {
      m_player.play(m_medias[i].url);
      m_currentIndex = i;
      emit currentPlayItemChanged();
      break;
    }
  }
}

void PlayService::pause() {
  m_player.pause();
}

void PlayService::next() {
  m_currentIndex++;
  if (m_currentIndex >= m_medias.size()) {
    m_currentIndex = 0;
  }

  if (m_currentIndex >= m_medias.size()) {
    m_currentIndex = -1;
  }

  if (m_currentIndex != -1) {
    auto& media = m_medias[m_currentIndex];
    this->play(media.id);
  }
}

void PlayService::previous() {
  m_currentIndex--;
  if (m_currentIndex < 0) {
    m_currentIndex = 0;
  }

  if (m_currentIndex >= m_medias.size()) {
    m_currentIndex = -1;
  }

  if (m_currentIndex != -1) {
    auto media = m_medias[m_currentIndex];
    this->play(media.id);
  }
}

void PlayService::play() {
  m_player.play();
}

void PlayService::appendMediaItem(const MediaItem& item) {
  for (const auto& media : m_medias) {
    if (media.id == item.id)  // 如果已有，直接返回即可
      return;
  }
  emit beginInsertItems(QModelIndex(), m_medias.size(), m_medias.size());
  m_medias.append(item);
  emit endInsertItems();
}

void PlayService::insertNext(qulonglong id) {
  //  auto items = m_playbacklistModel.rawData();
  //  for (int i = 0; i < items.size(); i++) {
  //    if (items[i]->id == id) {
  //      m_playbacklistModel.removeItem(i);
  //      break;
  //    }
  //  }

  //  if (g_idToMediaMap[id] != Q_NULLPTR) {
  //    return;
  //  }

  //  m_playbacklistModel.insertItem(g_idToMediaMap[id], m_currentIndex + 1);
  //  m_currentIndex++;
  //  emit numChanged();
}

entities::MediaItem PlayService::currentPlayItem() {
  if (m_currentIndex >= 0 && m_currentIndex < m_medias.size()) {
    return m_medias[m_currentIndex];
  }
  return {};
}

void PlayService::onPlaybackStateChanged(QMediaPlayer::PlaybackState state) {
  if (state == QMediaPlayer::PlayingState) {
    emit playingChanged(true);
  } else if (state == QMediaPlayer::PausedState) {
    emit playingChanged(false);
  } else if (state == QMediaPlayer::StoppedState) {
    emit playingChanged(false);
  }
}

void PlayService::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
  if (status == QMediaPlayer::EndOfMedia) {
    operateForPlaybackMode();
  }
}

void PlayService::operateForPlaybackMode() {
  switch (m_playbackMode) {
    case play_mode::Sequentially:
      m_currentIndex++;
      if (m_currentIndex < m_medias.size()) {
        play(m_medias[m_currentIndex].id);
      }
      break;
    case play_mode::ListLoop:
      m_currentIndex++;
      if (m_currentIndex >= m_medias.size()) {
        m_currentIndex = 0;
      }
      play(m_medias[m_currentIndex].id);
      break;
    case play_mode::SingleLoop:
      play(m_medias[m_currentIndex].id);
      break;
    case play_mode::Shuffle:
      break;
    default:
      break;
  }
}
}  // namespace service
