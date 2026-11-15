#include "playcontroller.h"

#include <QRandomGenerator>

#include "repositories/songrepository.h"

namespace viewmodel {

PlayController::PlayController(core::SongRepository* songs, QObject* parent)
    : QObject(parent), m_songs(songs) {
  connect(&m_player, &QMediaPlayer::durationChanged, this,
          &PlayController::durationChanged);
  connect(&m_player, &QMediaPlayer::positionChanged, this,
          &PlayController::positionChanged);
  connect(&m_player, &QMediaPlayer::playbackStateChanged, this,
          &PlayController::onPlaybackStateChanged);
  connect(&m_player, &QMediaPlayer::mediaStatusChanged, this,
          &PlayController::onMediaStatusChanged);
  connect(&m_playlist, &MediaItemModel::countChanged, this,
          &PlayController::countChanged);
  connect(m_songs, &core::SongRepository::urlReady, this,
          &PlayController::onUrlReady);
  connect(m_songs, &core::SongRepository::lyricReady, this,
          &PlayController::onLyricReady);
}

bool PlayController::isPlaying() const {
  return m_player.playbackState() == QMediaPlayer::PlayingState;
}

qint64 PlayController::duration() const {
  return m_player.duration();
}

qint64 PlayController::position() const {
  return m_player.position();
}

void PlayController::setPosition(qint64 position) {
  m_player.setPosition(position);
}

float PlayController::volume() const {
  return m_player.volume();
}

void PlayController::setVolume(float volume) {
  m_player.setVolume(volume);
  emit volumeChanged();
}

PlayController::PlayMode PlayController::playbackMode() const {
  return m_playbackMode;
}

void PlayController::setPlaybackMode(PlayMode mode) {
  if (m_playbackMode == mode) {
    return;
  }
  m_playbackMode = mode;
  emit playbackModeChanged();
}

int PlayController::count() const {
  return m_playlist.count();
}

void PlayController::play() {
  if (m_player.hasAudio() || m_player.position() > 0) {
    m_player.play();
    return;
  }
  if (m_currentIndex >= 0) {
    startIndex(m_currentIndex);
  } else if (m_playlist.count() > 0) {
    startIndex(0);
  }
}

void PlayController::pause() {
  m_player.pause();
}

void PlayController::next() {
  advance(true);
}

void PlayController::previous() {
  advance(false);
}

void PlayController::playItem(const entities::MediaItem& item) {
  if (!m_playlist.containsId(item.id)) {
    m_playlist.append(item);
  }
  startIndex(m_playlist.indexOfId(item.id));
}

void PlayController::playById(qulonglong id) {
  const int index = m_playlist.indexOfId(id);
  if (index >= 0) {
    startIndex(index);
  }
}

void PlayController::enqueue(const entities::MediaItem& item) {
  if (!m_playlist.containsId(item.id)) {
    m_playlist.append(item);
  }
}

void PlayController::playAll(const QList<entities::MediaItem>& items) {
  m_currentIndex = -1;
  m_playlist.clear();
  m_playlist.append(items);
  if (m_playlist.count() > 0) {
    startIndex(0);
  }
}

void PlayController::startIndex(int index) {
  if (index < 0 || index >= m_playlist.count()) {
    return;
  }
  m_currentIndex = index;
  const entities::MediaItem item = m_playlist.item(index);
  if (item.url.isValid() && !item.url.isEmpty()) {
    setCurrent(item);
    m_player.playUrl(item.url);
    m_songs->fetchLyric(item.id);
    return;
  }
  m_pendingUrlId = item.id;
  m_songs->fetchUrl(item.id);
}

void PlayController::advance(bool forward) {
  const int total = m_playlist.count();
  if (total == 0) {
    return;
  }

  int index = m_currentIndex;
  if (m_playbackMode == Shuffle && total > 1) {
    do {
      index = QRandomGenerator::global()->bounded(total);
    } while (index == m_currentIndex);
  } else if (forward) {
    index = m_currentIndex + 1;
    if (index >= total) {
      index = m_playbackMode == Sequentially ? -1 : 0;
    }
  } else {
    index = m_currentIndex - 1;
    if (index < 0) {
      index = m_playbackMode == Sequentially ? -1 : total - 1;
    }
  }

  if (index < 0) {
    m_player.stop();
    return;
  }
  startIndex(index);
}

void PlayController::setCurrent(const entities::MediaItem& item) {
  m_currentItem = item;
  emit currentPlayItemChanged();
}

void PlayController::onUrlReady(error_code::ErrorCode code, qulonglong id,
                                const QUrl& url) {
  if (code != error_code::NoError || url.isEmpty()) {
    return;
  }
  m_playlist.setUrl(id, url);
  if (id != m_pendingUrlId) {
    return;
  }
  m_pendingUrlId = 0;
  const entities::MediaItem item = m_playlist.item(m_playlist.indexOfId(id));
  setCurrent(item);
  m_player.playUrl(url);
  m_songs->fetchLyric(id);
}

void PlayController::onLyricReady(error_code::ErrorCode code, qulonglong id,
                                  const QVariantList& lyrics) {
  if (code != error_code::NoError || id != m_currentItem.id) {
    return;
  }
  m_currentItem.lyrics = lyrics;
  emit currentPlayItemChanged();
}

void PlayController::onPlaybackStateChanged(QMediaPlayer::PlaybackState) {
  emit playingChanged();
}

void PlayController::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
  if (status != QMediaPlayer::EndOfMedia) {
    return;
  }
  if (m_playbackMode == SingleLoop) {
    m_player.playUrl(m_currentItem.url);
    return;
  }
  advance(true);
}

}
