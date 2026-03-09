#include "song_lyric_service.h"

#include "recommended_playlist_service.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QRegularExpression>

namespace service {
SongLyricService::SongLyricService(QObject* parent) {
  using namespace network;
  connect(&m_network, &SongLyricNetwork::verbatimReady, this,
          &SongLyricService::onVerbatimReady);
}

void SongLyricService::onLyricReady(error_code::ErrorCode code,
                                    const QByteArray& data) {
  // QVariantList result;
  // if (code == error_code::NoError) {
  //   QJsonDocument doc = QJsonDocument::fromJson(data);
  //   auto obj = doc.object();
  //   if (doc.isNull() || doc.isEmpty() || obj.isEmpty())
  //     code = error_code::JsonContentError;
  //   else {
  //     auto lyricStr = obj["lrc"].toObject()["lyric"].toString();
  //     result = parseLyricStr(lyricStr);
  //   }
  // }
  // emit standardReady(code, result);
}

void SongLyricService::onVerbatimReady(error_code::ErrorCode code,
                                       const QByteArray&) {
  Q_ASSERT_X(false, "onVerbatimReady", "not implemented");
  //emit verbatimReady(code,result);
}

QVariantList SongLyricService::parseLyricStr(const QString& lyric) {
  QRegularExpression regex(R"(\[(\d{2}):(\d{2})\.(\d{2,3})\]\s*(.*))");
  QStringList lines = lyric.split("\n");
  QVariantList result;
  for (const auto& line : lines) {
    QRegularExpressionMatch match = regex.match(line);
    if (match.hasMatch()) {
      int minutes = match.captured(1).toInt();
      int seconds = match.captured(2).toInt();
      int milliseconds = match.captured(3).toInt();
      int totalMs = minutes * 60000 + seconds * 1000 + milliseconds;
      QString text = match.captured(4).trimmed();
      QVariantMap map;
      map["lyric"] = text;
      map["end"] = totalMs;
      result.append(map);
    }
  }
  return result;
}

QList<LyricLine> SongLyricService::parseYrcLyric(const QString& yrc) {
  QList<LyricLine> lines;
  const auto rawLines = yrc.split('\n', Qt::SkipEmptyParts);
  // line start：[start,duration]
  QRegularExpression reLine(R"(^\[(\d+),(\d+)\])");
  // token：(start,duration,xxx)TEXT
  QRegularExpression reTok(R"(\((\d+),(\d+),(-?\d+)\)([^(\r\n]+))");
  for (const auto& raw : rawLines) {
    QString s = raw.trimmed();
    if (s.isEmpty())
      continue;
    auto mLine = reLine.match(s);
    if (!mLine.hasMatch()) {
      continue;
    }
    LyricLine line;
    line.startMs = mLine.captured(1).toLongLong();
    const quint64 durMs = mLine.captured(2).toLongLong();
    line.endMs = line.startMs + durMs;
    const int headerLen = mLine.capturedLength(0);
    const QString rest = s.mid(headerLen);
    auto it = reTok.globalMatch(rest);
    while (it.hasNext()) {
      auto mt = it.next();
      const quint64 tokStart = mt.captured(1).toULongLong();
      const quint64 tokDur = mt.captured(2).toULongLong();
      const QString tokText = mt.captured(4);
      LyricToken t;
      t.startMs = tokStart;
      t.endMs = tokStart + tokDur;
      t.text = tokText;
      line.tokens.push_back(t);
      line.plainText += tokText;
    }
    if (line.tokens.isEmpty() && line.plainText.isEmpty()) {
      line.plainText = rest;
    }
    lines.push_back(std::move(line));
  }
  return lines;
}

void SongLyricService::fetchStandard(qulonglong id) {
  m_network.fetchStandard(id);
  connect(
      &m_network, &network::SongLyricNetwork::lyricReady, this,
      [this, id](error_code::ErrorCode code, const QByteArray& data) {
        QList<LyricLine> result;
        if (code == error_code::NoError) {
          QJsonDocument doc = QJsonDocument::fromJson(data);
          auto obj = doc.object();
          if (doc.isNull() || doc.isEmpty() || obj.isEmpty())
            code = error_code::JsonContentError;
          else {
            auto lyricStr = obj["yrc"].toObject()["lyric"].toString();
            result = parseYrcLyric(lyricStr);
          }
        }
        emit standardReady(code, id, result);
      },
      Qt::SingleShotConnection);
}

void SongLyricService::fetchVerbatim(qulonglong id) {
  Q_UNUSED(id);
  // m_network.fetchVerbatim(id);
  // connect(
  //     &m_network, &network::SongLyricNetwork::lyricReady, this,
  //     [this, id](error_code::ErrorCode code, const QByteArray& data) {
  //       QVariantList result;
  //       if (code == error_code::NoError) {
  //         QJsonDocument doc = QJsonDocument::fromJson(data);
  //         auto obj = doc.object();
  //         if (doc.isNull() || doc.isEmpty() || obj.isEmpty())
  //           code = error_code::JsonContentError;
  //         else {
  //           auto lyricStr = obj["lrc"].toObject()["lyric"].toString();
  //           result = parseLyricStr(lyricStr);
  //         }
  //       }
  //       emit standardReady(code, id, result);
  //     },
  //     Qt::SingleShotConnection);
}
}  // namespace service
