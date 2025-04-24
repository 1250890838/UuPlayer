#include "audio_player.h"

#include <QAudioOutput>

namespace engine{
MediaPlayer::MediaPlayer(QObject *parent) : QMediaPlayer(parent) {
  m_audioOutput = new QAudioOutput(this);
  this->setAudioOutput(m_audioOutput);
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

