#include "playcontroller.h"

#include <QRandomGenerator>

#include "app/appcontext.h"
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
  connect(m_songs, &core::SongRepository::urlReady, this,
          &PlayController::onUrlReady);
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

play_mode::PlayMode PlayController::playmode() const {
  return m_playbackMode;
}

void PlayController::setPlaymode(play_mode::PlayMode mode) {
  if (m_playbackMode == mode) {
    return;
  }
  m_playbackMode = mode;
  emit playmodeChanged();
}

float PlayController::volumn() const {
  return m_player.volume();
}

void PlayController::setVolumn(float volumn) {
  m_player.setVolume(volumn);
  emit volumnChanged();
}

void PlayController::play(qulonglong id) {
  play(id, sound_level::SoundQualityLevel::Exhigh);
}

void PlayController::play(qulonglong id,
                          sound_level::SoundQualityLevel level) {
  const QList<entities::MediaItem> items = m_medias.items();
  for (int i = 0; i < items.size(); ++i) {
    if (items.at(i).id != id) {
      continue;
    }
    if (!items.at(i).url.isEmpty()) {
      playByIndex(i);
      return;
    }
    m_pendingUrlId = id;
    m_songs->fetchUrl(id, level);
    return;
  }
}

void PlayController::play() {
  m_player.play();
}

void PlayController::pause() {
  m_player.pause();
}

void PlayController::next() {
  operateForPlaybackMode(true);
}

void PlayController::previous() {
  operateForPlaybackMode(false);
}

void PlayController::appendMediaItem(const entities::MediaItem& item) {
  for (const entities::MediaItem& media : m_medias.items()) {
    if (media.id == item.id) {
      return;
    }
  }
  const int first = m_medias.rows();
  m_medias.appendItem(item);
  emit mediasChanged();
  Q_UNUSED(first);
}

void PlayController::insertNextToPlayingItem(const entities::MediaItem& item) {
  for (const entities::MediaItem& media : m_medias.items()) {
    if (media.id == item.id) {
      return;
    }
  }
  int index = 0;
  if (m_currentIndex.has_value()) {
    index = *m_currentIndex + 1;
  }
  m_medias.insertItem(item, index);
  emit mediasChanged();
}

bool PlayController::hasUrl(qulonglong id) const {
  const QList<entities::MediaItem> items = m_medias.items();
  for (const entities::MediaItem& media : items) {
    if (media.id == id) {
      return !media.url.isEmpty();
    }
  }
  return false;
}

void PlayController::playByIndex(int index) {
  if (index < 0 || index >= m_medias.rows()) {
    return;
  }
  m_currentIndex = index;
  setCurrentItem(index);
  m_player.playUrl(m_medias.itemAt(index).url);
}

void PlayController::setCurrentItem(int index) {
  m_currentItem = m_medias.itemAt(index);
  emit currMediaItemChanged();
}

void PlayController::operateForPlaybackMode(bool forward) {
  const int size = m_medias.rows();
  if (size == 0) {
    m_currentIndex.reset();
    return;
  }

  int index = m_currentIndex.value_or(-1);
  switch (m_playbackMode) {
    case play_mode::Sequentially:
      if (!m_currentIndex.has_value()) {
        index = forward ? 0 : size - 1;
      } else {
        index += forward ? 1 : -1;
        if (index < 0 || index >= size) {
          m_currentIndex.reset();
          return;
        }
      }
      break;

    case play_mode::ListLoop:
      if (!m_currentIndex.has_value()) {
        index = forward ? 0 : size - 1;
      } else {
        index = (index + (forward ? 1 : -1) + size) % size;
      }
      break;

    case play_mode::SingleLoop:
      if (!m_currentIndex.has_value()) {
        index = 0;
      }
      break;

    case play_mode::Shuffle:
      index = QRandomGenerator::global()->bounded(size);
      break;

    default:
      return;
  }

  playByIndex(index);
}

void PlayController::onUrlReady(error_code::ErrorCode code, qulonglong id,
                                const QUrl& url) {
  if (code != error_code::NoError || url.isEmpty()) {
    return;
  }
  m_medias.setUrl(id, url);

  if (id != m_pendingUrlId) {
    return;
  }
  m_pendingUrlId = 0;

  const QList<entities::MediaItem> items = m_medias.items();
  for (int i = 0; i < items.size(); ++i) {
    if (items.at(i).id == id) {
      playByIndex(i);
      return;
    }
  }
}

void PlayController::onPlaybackStateChanged(QMediaPlayer::PlaybackState) {
  emit isPlayingChanged();
}

void PlayController::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
  if (status == QMediaPlayer::EndOfMedia) {
    operateForPlaybackMode(true);
  }
}

}  // namespace viewmodel