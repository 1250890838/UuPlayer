#ifndef LYRICSVIEW_CONTROLLER_H
#define LYRICSVIEW_CONTROLLER_H

#include <QObject>
#include <QProperty>
#include <QQmlEngine>

#include "song_lyric_service.h"
#include "play_service.h"

namespace controller {
using namespace service;
using namespace entities;
// currentTokens
//     currentTokenIndex
//         currentTokenProgress（0~1）
class LyricsViewController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
  Q_PROPERTY(
      QStringList lyricsText READ lyricsText BINDABLE bindableLyricsText FINAL)
  Q_PROPERTY(QStringList currentTokens READ currentTokens BINDABLE
                 bindableCurrentTokens FINAL)
  Q_PROPERTY(qreal currentTokenProgress READ currentTokenProgress BINDABLE
                 bindableCurrentTokenProgress FINAL)
  Q_PROPERTY(qint64 currentTokenIndex READ currentTokenIndex BINDABLE
                 bindableCurrentTokenIndex FINAL)
  Q_PROPERTY(qint64 currentLineIndex READ currentLineIndex BINDABLE
                 bindableCurrentLineIndex FINAL)
 public:
  explicit LyricsViewController(QObject* parent = nullptr);
  QStringList lyricsText() { return m_lyricsText.value(); }
  QBindable<QStringList> bindableLyricsText() { return &m_lyricsText; }
  qint64 currentTokenIndex() { return m_currentTokenIndex.value(); }
  QBindable<qint64> bindableCurrentTokenIndex() { return &m_currentTokenIndex; }
  QStringList currentTokens() { return m_currentTokens.value(); }
  QBindable<QStringList> bindableCurrentTokens() { return &m_currentTokens; }
  qreal currentTokenProgress() { return m_currentTokenProgress.value(); }
  QBindable<qreal> bindableCurrentTokenProgress() {
    return &m_currentTokenProgress;
  }
  qint64 currentLineIndex() { return m_currentLineIndex.value(); }
  QBindable<qint64> bindableCurrentLineIndex() { return &m_currentLineIndex; }
 private slots:
  void onLyricsReady(error_code::ErrorCode code, qulonglong id,
                     QList<LyricLine> lyricsLines);
  void onPositionChanged(qint64 pos);
 private:
  QProperty<QStringList> m_lyricsText;
  QProperty<QStringList> m_currentTokens;
  QProperty<qint64> m_currentTokenIndex;
  QProperty<qreal> m_currentTokenProgress;
  QProperty<qint64> m_currentLineIndex;
  QList<LyricLine> m_lyricLines;

  QPointer<SongLyricService> m_songLyricService;
  QPointer<PlayService> m_playService;
 signals:
};
}  // namespace controller
#endif  // LYRICSVIEW_CONTROLLER_H
