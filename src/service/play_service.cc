#include "play_service.h"
#include "recommended_playlist_service.h"

#include <QModelIndex>
#include <QObject>
#include <QRandomGenerator>

namespace service {
PlayService::PlayService():m_playbackMode(play_mode::ListLoop) {
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
    playByIndex(std::distance(m_medias.begin(), it));
  }
}

void PlayService::playByIndex(quint32 index) {
  if (index >= m_medias.size())
    return;
  const auto& media = m_medias[index];
  m_player.play(media.url);
  m_currentIndex = index;
  emit currentPlayItemChanged();
}

void PlayService::pause() {
  m_player.pause();
}

void PlayService::next() {
  operateForPlaybackMode(true);
}

void PlayService::previous() {
  operateForPlaybackMode(false);
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

void PlayService::insertNextToPlayingItem(const MediaItem& item) {
  quint32 index = 0;
  if (m_currentIndex && *m_currentIndex < m_medias.size())
    index = *m_currentIndex + 1;
  emit beginInsertItems(QModelIndex(), index, index);
  m_medias.insert(index, item);
  emit endInsertItems();
}

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
    operateForPlaybackMode(true);
  }
}

void PlayService::operateForPlaybackMode(bool next) {
  if (m_medias.empty()) {
    m_currentIndex = std::nullopt;
    return;
  }
  const qsizetype size = static_cast<qsizetype>(m_medias.size());
  qsizetype idx = m_currentIndex ? static_cast<qsizetype>(*m_currentIndex) : -1;
  switch (m_playbackMode) {
    case play_mode::Sequentially:
      if (!m_currentIndex) {
        idx = next ? 0 : size - 1;
      } else {
        idx += next ? 1 : -1;
        if (idx < 0 || idx >= size) {
          m_currentIndex.reset();
          return;
        }
      }
      break;

    case play_mode::ListLoop:
      if (!m_currentIndex) {
        idx = next ? 0 : size - 1;
      } else {
        idx = (idx + (next ? 1 : -1) + size) % size;
      }
      break;

    case play_mode::SingleLoop:
      if (!m_currentIndex)
        idx = 0;
      break;

    case play_mode::Shuffle:
      idx = QRandomGenerator::global()->bounded(size);
      break;

    default:
      return;
  }

  playByIndex(idx);
}
}  // namespace service
