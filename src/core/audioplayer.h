#pragma once

#include <QAudioOutput>
#include <QMediaPlayer>
#include <QObject>
#include <QUrl>

namespace core {

class AudioPlayer : public QMediaPlayer {
  Q_OBJECT
 public:
  explicit AudioPlayer(QObject* parent = nullptr);

  void playUrl(const QUrl& url);

  float volume() const;
  void setVolume(float volume);

 private:
  QAudioOutput* m_output = nullptr;
};

}
