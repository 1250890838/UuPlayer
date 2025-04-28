#ifndef ENGINE_MEDIAPLAYER_H
#define ENGINE_MEDIAPLAYER_H
#include "engine_global.h"

#include <QJSEngine>
#include <QObject>
#include <QQmlEngine>
#include <QAudioOutput>

#include <QList>
#include <QMediaPlayer>

namespace engine {
class ENGINE_DLL_EXPORT MediaPlayer : public QMediaPlayer {
  Q_OBJECT
  Q_DISABLE_COPY(MediaPlayer)
 public:
  using QMediaPlayer::play;
  static QObject* getInstance(QQmlEngine* eng, QJSEngine* scriptEngine);

  MediaPlayer(QObject* parent = nullptr);

 public slots:
  void play(const QUrl& url);

 private:
  QAudioOutput* m_audioOutput;
};
}  // namespace engine
#endif
