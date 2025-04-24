#include "play_service.h"

#include <QObject>

namespace service {
PlayService::PlayService() {
  connect(&m_player, &engine::MediaPlayer::playingChanged, this,
          &PlayService::playingChanged);
  connect(&m_player, &engine::MediaPlayer::durationChanged, this,
          &PlayService::durationChanged);
  connect(&m_player, &engine::MediaPlayer::positionChanged, this,
          &PlayService::positionChanged);
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

void PlayService::setPosition(quint64 position) {
  m_player.setPosition(position);
}

void PlayService::play(qulonglong id) {
  for (auto media : m_medias) {
    if (media->id == id) {
      m_player.play(media->url);
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
    auto media = m_medias[m_currentIndex];
    this->play(media->id);
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
    this->play(media->id);
  }
}

void PlayService::appendMediaId(qulonglong id) {
  // 先检查歌曲是否已在列表
  for (auto& media : m_medias) {
    if (media->id == id) {
      return;
    }
  }

  if (g_idToMediaMap[id] == Q_NULLPTR) {
    return;
  }

  model::MediaItem* item = g_idToMediaMap[id];

  m_medias.emplaceBack(item);
}

void PlayService::insertNext(qulonglong id) {
  for (int i = 0; i < m_medias.size(); i++) {
    if (m_medias[i]->id == id) {
      m_medias.removeAt(i);
      break;
    }
  }

  if (g_idToMediaMap[id] != Q_NULLPTR) {
    return;
  }

  m_medias.insert(m_currentIndex + 1, g_idToMediaMap[id]);
  m_currentIndex++;
}

void PlayService::onPlaybackStateChanged(QMediaPlayer::PlaybackState state) {
  if (state == QMediaPlayer::PlayingState) {
  } else if (state == QMediaPlayer::PausedState) {
  } else if (state == QMediaPlayer::StoppedState) {
    next();
  }
}
}  // namespace service
