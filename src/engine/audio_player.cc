
#include "audio_player.h"

namespace engine{
MediaPlayer::MediaPlayer(QObject *parent) : QMediaPlayer(parent) {
}

void MediaPlayer::play(const QString &path) {
  
}

QObject *MediaPlayer::getInstance(QQmlEngine * eng, QJSEngine *scriptEngine) {
  Q_UNUSED(eng);
  Q_UNUSED(scriptEngine);
  return new MediaPlayer();
}
}
// namespace player_engine

