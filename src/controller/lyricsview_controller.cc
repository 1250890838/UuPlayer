#include "lyricsview_controller.h"

#include <QtGlobal>
#include <QtMath>

#include "service_manager.h"

namespace controller {
static inline qreal clamp01(qreal v) {
  if (v < 0.0)
    return 0.0;
  if (v > 1.0)
    return 1.0;
  return v;
}

// line.startMs <= pos < line.endMs
static int findLineIndexByPos(const QList<LyricLine>& lines, quint64 posMs) {
  if (lines.isEmpty())
    return -1;

  int lo = 0;
  int hi = lines.size() - 1;
  while (lo <= hi) {
    const int mid = (lo + hi) / 2;
    const auto& line = lines[mid];

    if (posMs < line.startMs) {
      hi = mid - 1;
    } else if (posMs >= line.endMs) {
      lo = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}

// token.startMs <= pos < token.endMs
static int findTokenIndexByPos(const QVector<LyricToken>& tokens,
                               quint64 posMs) {
  if (tokens.isEmpty())
    return -1;

  int lo = 0;
  int hi = tokens.size() - 1;
  while (lo <= hi) {
    const int mid = (lo + hi) / 2;
    const auto& t = tokens[mid];

    if (posMs < t.startMs) {
      hi = mid - 1;
    } else if (posMs >= t.endMs) {
      lo = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}

LyricsViewController::LyricsViewController(QObject* parent) : QObject{parent} {
  m_songLyricService =
      ServiceManager::instance().getInstance<SongLyricService>();
  if (m_songLyricService) {
    connect(m_songLyricService, &SongLyricService::standardReady, this,
            &LyricsViewController::onLyricsReady);
  }
  m_playService = ServiceManager::instance().getInstance<PlayService>();
  if (m_playService) {
    connect(m_playService, &PlayService::positionChanged, this,
            &LyricsViewController::onPositionChanged);
  }
  m_lyricsText.setValue({});
  m_currentTokens.setValue({});
  m_currentTokenIndex.setValue(-1);
  m_currentTokenProgress.setValue(0.0);
  m_currentLineIndex.setValue(-1);
}

void LyricsViewController::onLyricsReady(error_code::ErrorCode code,
                                         qulonglong id,
                                         QList<LyricLine> lyricsLines) {
  if (m_playService->currentPlayItem().id != id ||
      code != error_code::NoError) {
    m_lyricLines.clear();
    m_lyricsText.setValue({});
    m_currentTokens.setValue({});
    m_currentTokenIndex.setValue(-1);
    m_currentTokenProgress.setValue(0.0);
    m_currentLineIndex.setValue(-1);
    return;
  }
  m_lyricLines = std::move(lyricsLines);
  for (int i = 0; i < m_lyricLines.size(); ++i) {
    auto& line = m_lyricLines[i];
    if (line.endMs <= line.startMs) {
      if (i + 1 < m_lyricLines.size()) {
        line.endMs = m_lyricLines[i + 1].startMs;
      } else {
        line.endMs = line.startMs + 5000;
      }
    }

    if (!line.tokens.isEmpty()) {
      for (int j = 0; j < line.tokens.size(); ++j) {
        auto& t = line.tokens[j];
        if (t.endMs <= t.startMs) {
          if (j + 1 < line.tokens.size()) {
            t.endMs = line.tokens[j + 1].startMs;
          } else {
            t.endMs = line.endMs;
          }
          if (t.endMs <= t.startMs) {
            t.endMs = t.startMs + 1;
          }
        }
      }
    }
  }

  QStringList lyricsText;
  lyricsText.reserve(m_lyricLines.size());
  for (const auto& line : m_lyricLines) {
    lyricsText.append(line.plainText);
  }
  m_lyricsText.setValue(lyricsText);
  m_currentTokens.setValue({});
  m_currentTokenIndex.setValue(-1);
  m_currentTokenProgress.setValue(0.0);
  m_currentLineIndex.setValue(-1);
}

void LyricsViewController::onPositionChanged(qint64 pos) {
  if (m_lyricLines.isEmpty())
    return;
  if (pos < 0)
    return;
  const quint64 posMs = static_cast<quint64>(pos);
  const int newLineIndex = findLineIndexByPos(m_lyricLines, posMs);
  if (newLineIndex < 0 || newLineIndex >= m_lyricLines.size()) {
    return;
  }

  if (newLineIndex != m_currentLineIndex.value()) {
    m_currentLineIndex.setValue(newLineIndex);
    const auto& line = m_lyricLines[newLineIndex];
    QStringList tokensText;
    tokensText.reserve(line.tokens.size());
    for (const auto& t : line.tokens) {
      tokensText.append(t.text);
    }
    m_currentTokens.setValue(tokensText);

    m_currentTokenIndex.setValue(-1);
    m_currentTokenProgress.setValue(0.0);
  }

  const auto& line = m_lyricLines[m_currentLineIndex.value()];

  if (line.tokens.isEmpty()) {
    if (m_currentTokenIndex.value() != -1)
      m_currentTokenIndex.setValue(-1);
    if (!qFuzzyIsNull(m_currentTokenProgress.value()))
      m_currentTokenProgress.setValue(0.0);
    return;
  }

  const int newTokenIndex = findTokenIndexByPos(line.tokens, posMs);
  if (newTokenIndex < 0 || newTokenIndex >= line.tokens.size()) {
    return;
  }

  if (newTokenIndex != m_currentTokenIndex.value()) {
    m_currentTokenIndex.setValue(newTokenIndex);
  }

  const auto& tok = line.tokens[newTokenIndex];
  const quint64 span =
      (tok.endMs > tok.startMs) ? (tok.endMs - tok.startMs) : 0;

  qreal prog = 0.0;
  if (span > 0) {
    prog = clamp01(qreal(posMs - tok.startMs) / qreal(span));
  }

  if (qAbs(prog - m_currentTokenProgress.value()) > 0.001) {
    m_currentTokenProgress.setValue(prog);
  }
}

}  // namespace controller