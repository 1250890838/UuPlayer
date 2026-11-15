#include "audioplayer.h"

namespace core {

AudioPlayer::AudioPlayer(QObject* parent)
    : QMediaPlayer(parent), m_output(new QAudioOutput(this)) {
  setAudioOutput(m_output);
}

void AudioPlayer::playUrl(const QUrl& url) {
  if (url == source()) {
    play();
    return;
  }
  setSource(url);
  play();
}

float AudioPlayer::volume() const {
  return m_output->volume();
}

void AudioPlayer::setVolume(float volume) {
  m_output->setVolume(volume);
}

}  // namespace core