#include "play_service.h"
#include "playlist_service.h"

#include <QObject>

namespace service {
PlayService::PlayService():m_currentIndex(0) {
 // connect(&m_player, &engine::MediaPlayer::playingChanged, this,
  //        &PlayService::playingChanged);
  connect(&m_player, &engine::MediaPlayer::durationChanged, this,
          &PlayService::durationChanged);
  connect(&m_player, &engine::MediaPlayer::positionChanged, this,
          &PlayService::positionChanged);
  connect(&m_player, &engine::MediaPlayer::playbackStateChanged, this,
          &PlayService::onPlaybackStateChanged);
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
  return m_medias.size();
}

void PlayService::setPlaybackMode(PlaybackMode mode) {
  m_playbackMode = mode;
  emit playbackModeChanged();
}

PlayService::PlaybackMode PlayService::playbackMode() {
  return m_playbackMode;
}

void PlayService::setPosition(quint64 position) {
  m_player.setPosition(position);
}

void PlayService::play(qulonglong id) {
  for (int i = 0; i < m_medias.size(); i++) {
    if (m_medias[i]->id == id) {
      m_player.play(m_medias[i]->url);
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

void PlayService::play()
{
  m_player.play();
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
  emit numChanged();
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
  emit numChanged();
}

model::MediaItem PlayService::currentPlayItem() {
  if (m_currentIndex >= 0 && m_currentIndex < m_medias.size()) {
    return *m_medias[m_currentIndex];
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

void PlayService::operateCurrentIndexForPlaybackMode(bool previous) {
  switch (m_playbackMode) {
    case PlaybackMode::Sequentially:
      if (previous) {
        m_currentIndex--;
      } else {
        m_currentIndex++;
      }
      break;
    case PlaybackMode::ListLoop:
      break;
    case PlaybackMode::SingleLoop:
      break;
    case PlaybackMode::Shuffle:
      break;
    default:
      break;
  }
}
}  // namespace service
