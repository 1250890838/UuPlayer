
#include "audio_player.h"

// write a function that multiple two and three

namespace engine{
MediaPlayer::MediaPlayer(QObject *parent) : QMediaPlayer(parent) {
}


void MediaPlayer::play(const QUrl& path) {
  this->stop();
  this->setSource(path);
  QMediaPlayer::play();
}

QObject *MediaPlayer::getInstance(QQmlEngine * eng, QJSEngine *scriptEngine) {
  Q_UNUSED(eng);
  Q_UNUSED(scriptEngine);
  return new MediaPlayer();
}
}
// namespace player_engine

