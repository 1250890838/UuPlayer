#include "lyricsviewcontroller.h"

#include <QtGlobal>
#include <QtMath>

#include "playcontroller.h"
#include "repositories/songrepository.h"

namespace viewmodel {
namespace {

qreal clamp01(qreal value) {
  if (value < 0.0) {
    return 0.0;
  }
  if (value > 1.0) {
    return 1.0;
  }
  return value;
}

int findLineIndexByPos(const QList<entities::LyricLine>& lines,
                       quint64 posMs) {
  if (lines.isEmpty()) {
    return -1;
  }
  int lo = 0;
  int hi = lines.size() - 1;
  while (lo <= hi) {
    const int mid = (lo + hi) / 2;
    const entities::LyricLine& line = lines.at(mid);
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

int findTokenIndexByPos(const QVector<entities::LyricToken>& tokens,
                        quint64 posMs) {
  if (tokens.isEmpty()) {
    return -1;
  }
  int lo = 0;
  int hi = tokens.size() - 1;
  while (lo <= hi) {
    const int mid = (lo + hi) / 2;
    const entities::LyricToken& token = tokens.at(mid);
    if (posMs < token.startMs) {
      hi = mid - 1;
    } else if (posMs >= token.endMs) {
      lo = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}

}  // namespace

LyricsViewController::LyricsViewController(core::SongRepository* songs,
                                           PlayController* play,
                                           QObject* parent)
    : QObject(parent), m_songs(songs), m_play(play) {
  reset();
  connect(m_songs, &core::SongRepository::lyricReady, this,
          &LyricsViewController::onLyricsReady);
  connect(m_play, &PlayController::positionChanged, this,
          &LyricsViewController::onPositionChanged);
}

void LyricsViewController::reset() {
  m_lyricLines.clear();
  m_lyricsText.setValue({});
  m_currentTokens.setValue({});
  m_currentTokenIndex.setValue(-1);
  m_currentTokenProgress.setValue(0.0);
  m_currentLineIndex.setValue(-1);
}

void LyricsViewController::onLyricsReady(
    error_code::ErrorCode code, qulonglong id,
    const QList<entities::LyricLine>& lines) {
  const qulonglong currentId = m_play->currMediaItem().id;
  if ((currentId != 0 && currentId != id) || code != error_code::NoError) {
    reset();
    return;
  }

  m_lyricLines = lines;
  for (int i = 0; i < m_lyricLines.size(); ++i) {
    entities::LyricLine& line = m_lyricLines[i];
    if (line.endMs <= line.startMs) {
      line.endMs = (i + 1 < m_lyricLines.size())
                       ? m_lyricLines.at(i + 1).startMs
                       : line.startMs + 5000;
    }
    for (int j = 0; j < line.tokens.size(); ++j) {
      entities::LyricToken& token = line.tokens[j];
      if (token.endMs > token.startMs) {
        continue;
      }
      token.endMs = (j + 1 < line.tokens.size())
                        ? line.tokens.at(j + 1).startMs
                        : line.endMs;
      if (token.endMs <= token.startMs) {
        token.endMs = token.startMs + 1;
      }
    }
  }

  QVariantList lyricsText;
  lyricsText.reserve(m_lyricLines.size());
  for (const entities::LyricLine& line : m_lyricLines) {
    QVariantMap map;
    map.insert(QStringLiteral("start"), line.startMs);
    map.insert(QStringLiteral("text"), line.plainText);
    lyricsText.append(map);
  }
  m_lyricsText.setValue(lyricsText);
  m_currentTokens.setValue({});
  m_currentTokenIndex.setValue(-1);
  m_currentTokenProgress.setValue(0.0);
  m_currentLineIndex.setValue(-1);
}

void LyricsViewController::onPositionChanged(qint64 position) {
  if (m_lyricLines.isEmpty() || position < 0) {
    return;
  }
  const quint64 posMs = quint64(position);
  const int lineIndex = findLineIndexByPos(m_lyricLines, posMs);
  if (lineIndex < 0 || lineIndex >= m_lyricLines.size()) {
    return;
  }

  if (lineIndex != m_currentLineIndex.value()) {
    m_currentLineIndex.setValue(lineIndex);
    const entities::LyricLine& line = m_lyricLines.at(lineIndex);

    QStringList tokensText;
    tokensText.reserve(line.tokens.size());
    for (const entities::LyricToken& token : line.tokens) {
      tokensText.append(token.text);
    }
    if (tokensText.isEmpty()) {
      for (const QChar& c : line.plainText) {
        tokensText.append(QString(c));
      }
    }
    m_currentTokens.setValue(tokensText);
    m_currentTokenIndex.setValue(-1);
    m_currentTokenProgress.setValue(0.0);
    return;
  }

  const entities::LyricLine& line =
      m_lyricLines.at(int(m_currentLineIndex.value()));
  if (line.tokens.isEmpty()) {
    m_currentTokenIndex.setValue(int(line.plainText.size()));
    if (!qFuzzyIsNull(m_currentTokenProgress.value())) {
      m_currentTokenProgress.setValue(0.0);
    }
    return;
  }

  const int tokenIndex = findTokenIndexByPos(line.tokens, posMs);
  if (tokenIndex < 0 || tokenIndex >= line.tokens.size()) {
    return;
  }
  m_currentTokenIndex.setValue(tokenIndex);

  const entities::LyricToken& token = line.tokens.at(tokenIndex);
  const quint64 span =
      token.endMs > token.startMs ? token.endMs - token.startMs : 0;
  qreal progress = 0.0;
  if (span > 0) {
    progress = clamp01(qreal(posMs - token.startMs) / qreal(span));
  }
  if (qAbs(progress - m_currentTokenProgress.value()) > 0.001) {
    m_currentTokenProgress.setValue(progress);
  }
}

}  // namespace viewmodel