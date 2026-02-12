#include "play_service.h"
#include "recommended_playlist_service.h"

#include <QModelIndex>
#include <QObject>

namespace service {
PlayService::PlayService() {
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

PlayMode PlayService::playbackMode() {
  return m_playbackMode;
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
  auto it = std::ranges::find_if(
      m_medias, [&](const auto& media) { return media.id == id; });
  if (it != m_medias.end() && !it->url.isEmpty()) {
    m_player.play(it->url);
    m_currentIndex = std::distance(m_medias.begin(), it);
    emit currentPlayItemChanged();
  }
}

void PlayService::pause() {
  m_player.pause();
}

void PlayService::next() {
  if (m_medias.empty()) {
    m_currentIndex = std::nullopt;
    return;
  }
  m_currentIndex = m_currentIndex ? (*m_currentIndex + 1) % m_medias.size() : 0;
  play(m_medias[*m_currentIndex].id);
}

void PlayService::previous() {
  if (m_medias.empty()) {
    m_currentIndex.reset();
    return;
  }

  if (!m_currentIndex.has_value()) {
    m_currentIndex = m_medias.size() - 1;
  } else {
    m_currentIndex =
        (*m_currentIndex == 0) ? m_medias.size() - 1 : *m_currentIndex - 1;
  }

  play(m_medias[*m_currentIndex].id);
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

void PlayService::insertNextToPlayingItem(const MediaItem& item) {}

entities::MediaItem PlayService::currentPlayItem() {
  if (m_currentIndex.has_value()) {
    return m_medias[m_currentIndex.value()];
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
  // switch (m_playbackMode) {
  //   case play_mode::Sequentially:
  //     m_currentIndex++;
  //     if (m_currentIndex < m_medias.size()) {
  //       play(m_medias[m_currentIndex].id);
  //     }
  //     break;
  //   case play_mode::ListLoop:
  //     m_currentIndex++;
  //     if (m_currentIndex >= m_medias.size()) {
  //       m_currentIndex = 0;
  //     }
  //     play(m_medias[m_currentIndex].id);
  //     break;
  //   case play_mode::SingleLoop:
  //     play(m_medias[m_currentIndex].id);
  //     break;
  //   case play_mode::Shuffle:
  //     break;
  //   default:
  //     break;
  // }
}
}  // namespace service
