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

void SongLyricService::fetchStandard(qulonglong id) {
  m_network.fetchStandard(id);
  connect(
      &m_network, &network::SongLyricNetwork::lyricReady, this,
      [this, id](error_code::ErrorCode code, const QByteArray& data) {
        QVariantList result;
        if (code == error_code::NoError) {
          QJsonDocument doc = QJsonDocument::fromJson(data);
          auto obj = doc.object();
          if (doc.isNull() || doc.isEmpty() || obj.isEmpty())
            code = error_code::JsonContentError;
          else {
            auto lyricStr = obj["lrc"].toObject()["lyric"].toString();
            result = parseLyricStr(lyricStr);
          }
        }
        emit standardReady(code, id, result);
      },
      Qt::SingleShotConnection);
}

void SongLyricService::fetchVerbatim(qulonglong id) {
  m_network.fetchVerbatim(id);
}
}  // namespace service
