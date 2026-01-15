#include "play_service.h"
#include "playlist_service.h"

#include <QObject>

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
  return m_playbacklistModel.rowCount(QModelIndex());
}

void PlayService::setPlaybackMode(PlaybackMode mode) {
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

PlayService::PlaybackMode PlayService::playbackMode() {
  return m_playbackMode;
}

model::MediaItemModel* PlayService::playbacklist() {
  return &m_playbacklistModel;
}

void PlayService::setPosition(quint64 position) {
  m_player.setPosition(position);
}

void PlayService::play(qulonglong id) {
  auto items = m_playbacklistModel.rawData();

  for (int i = 0; i < items.size(); i++) {
    if (items[i]->id == id) {
      m_player.play(items[i]->url);
      m_currentIndex = i;
      qDebug() << "play media id=" << id << " " << items[i]->url;
      emit currentPlayItemChanged();
      break;
    }
  }
}

void PlayService::pause() {
  m_player.pause();
}

void PlayService::next() {
  auto items = m_playbacklistModel.rawData();
  m_currentIndex++;
  if (m_currentIndex >= items.size()) {
    m_currentIndex = 0;
  }

  if (m_currentIndex >= items.size()) {
    m_currentIndex = -1;
  }

  if (m_currentIndex != -1) {
    auto& media = items[m_currentIndex];
    this->play(media->id);
  }
}

void PlayService::previous() {
  auto items = m_playbacklistModel.rawData();
  m_currentIndex--;
  if (m_currentIndex < 0) {
    m_currentIndex = 0;
  }

  if (m_currentIndex >= items.size()) {
    m_currentIndex = -1;
  }

  if (m_currentIndex != -1) {
    auto media = items[m_currentIndex];
    this->play(media->id);
  }
}

void PlayService::play() {
  m_player.play();
}

void PlayService::appendMediaId(qulonglong id) {
  // 先检查歌曲是否已在列表
  auto items = m_playbacklistModel.rawData();
  for (auto& media : items) {
    if (media->id == id) {
      return;
    }
  }

  if (g_idToMediaMap[id] == Q_NULLPTR) {
    return;
  }

  entities::MediaItem* item = g_idToMediaMap[id];
  m_playbacklistModel.appendItem(item);
  emit numChanged();
}

void PlayService::insertNext(qulonglong id) {
  auto items = m_playbacklistModel.rawData();
  for (int i = 0; i < items.size(); i++) {
    if (items[i]->id == id) {
      m_playbacklistModel.removeItem(i);
      break;
    }
  }

  if (g_idToMediaMap[id] != Q_NULLPTR) {
    return;
  }

  m_playbacklistModel.insertItem(g_idToMediaMap[id], m_currentIndex + 1);
  m_currentIndex++;
  emit numChanged();
}

entities::MediaItem PlayService::currentPlayItem() {
  auto items = m_playbacklistModel.rawData();
  if (m_currentIndex >= 0 && m_currentIndex < items.size()) {
    return *items[m_currentIndex];
  }
  //return model::MediaItem();
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
    ;
  }
}

void PlayService::operateForPlaybackMode() {
  auto items = m_playbacklistModel.rawData();
  switch (m_playbackMode) {
    case PlaybackMode::Sequentially:
      m_currentIndex++;
      if (m_currentIndex < items.size()) {
        play(items[m_currentIndex]->id);
      }
      break;
    case PlaybackMode::ListLoop:
      m_currentIndex++;
      if (m_currentIndex >= items.size()) {
        m_currentIndex = 0;
      }
      play(items[m_currentIndex]->id);
      break;
    case PlaybackMode::SingleLoop:
      play(items[m_currentIndex]->id);
      break;
    case PlaybackMode::Shuffle:
      break;
    default:
      break;
  }
}
}  // namespace service
