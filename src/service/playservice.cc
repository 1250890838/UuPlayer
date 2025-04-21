#include "play_service.h"

#include <QObject>

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
  for (auto& media : m_medias) {
    if (media.id == id) {
      m_player.play(media.url);
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
    auto& media = m_medias[m_currentIndex];
    this->play(media.id);
  }
}

void PlayService::appendMediaItem(const model::MediaItem& mediaItem) {
  // 先检查歌曲是否已在列表
  for (auto& media : m_medias) {
    if (media.id == mediaItem.id) {
      return;
    }
  }

  m_medias.emplaceBack(mediaItem);
}

void PlayService::insertNext(const model::MediaItem& mediaItem) {
  for (int i = 0; i < m_medias.size(); i++) {
    if (m_medias[i].id == mediaItem.id) {
      m_medias.removeAt(i);
      break;
    }
  }
  m_medias.insert(m_currentIndex + 1, mediaItem);
  m_currentIndex++;
}

void PlayService::onPlaybackStateChanged(QMediaPlayer::PlaybackState state) {
  if (state == QMediaPlayer::PlayingState) {
  } else if (state == QMediaPlayer::PausedState) {
  } else if (state == QMediaPlayer::StoppedState) {
    next();
  }
}
