#pragma once

#include <QObject>
#include <QProperty>
#include <QStringList>
#include <QVariantList>

#include "entities/lyrictypes.h"
#include "entities/types.h"

namespace core {
class SongRepository;
}

namespace viewmodel {
class PlayController;
}

namespace viewmodel {

class LyricsViewController : public QObject {
  Q_OBJECT
  Q_PROPERTY(
      QVariantList lyricsText READ lyricsText BINDABLE bindableLyricsText FINAL)
  Q_PROPERTY(QStringList currentTokens READ currentTokens BINDABLE
                 bindableCurrentTokens FINAL)
  Q_PROPERTY(qreal currentTokenProgress READ currentTokenProgress BINDABLE
                 bindableCurrentTokenProgress FINAL)
  Q_PROPERTY(qint64 currentTokenIndex READ currentTokenIndex BINDABLE
                 bindableCurrentTokenIndex FINAL)
  Q_PROPERTY(qint64 currentLineIndex READ currentLineIndex BINDABLE
                 bindableCurrentLineIndex FINAL)

 public:
  LyricsViewController(core::SongRepository* songs, PlayController* play,
                       QObject* parent = nullptr);

  QVariantList lyricsText() { return m_lyricsText.value(); }
  QBindable<QVariantList> bindableLyricsText() { return &m_lyricsText; }
  QStringList currentTokens() { return m_currentTokens.value(); }
  QBindable<QStringList> bindableCurrentTokens() { return &m_currentTokens; }
  qreal currentTokenProgress() { return m_currentTokenProgress.value(); }
  QBindable<qreal> bindableCurrentTokenProgress() {
    return &m_currentTokenProgress;
  }
  qint64 currentTokenIndex() { return m_currentTokenIndex.value(); }
  QBindable<qint64> bindableCurrentTokenIndex() {
    return &m_currentTokenIndex;
  }
  qint64 currentLineIndex() { return m_currentLineIndex.value(); }
  QBindable<qint64> bindableCurrentLineIndex() {
    return &m_currentLineIndex;
  }

 private slots:
  void onLyricsReady(error_code::ErrorCode code, qulonglong id,
                     const QList<entities::LyricLine>& lines);
  void onPositionChanged(qint64 position);

 private:
  void reset();

  core::SongRepository* m_songs = nullptr;
  PlayController* m_play = nullptr;
  QList<entities::LyricLine> m_lyricLines;

  QProperty<QVariantList> m_lyricsText;
  QProperty<QStringList> m_currentTokens;
  QProperty<qint64> m_currentTokenIndex;
  QProperty<qreal> m_currentTokenProgress;
  QProperty<qint64> m_currentLineIndex;
};

}  // namespace viewmodel