#include "song_service.h"

#include "model/media_item_model.h"
#include "playlist_service.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QRegularExpression>

service::SongService::SongService(QObject* parent) {
  connect(&m_network, &network::SongNetwork::getSongUrlFinished, this,
          &SongService::onGetSongUrlFinished);
  connect(&m_network, &network::SongNetwork::getSongLyricFinished, this,
          &SongService::onGetSongLyricFinished);
}

void service::SongService::onGetSongUrlFinished(
    network::error_code::ErrorCode code, const QByteArray& data, void* item) {
  if (code == network::error_code::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    auto obj = doc.object();
    auto dataArr = obj["data"].toArray();
    if (dataArr.empty())
      return;

    auto dataObj = dataArr[0].toObject();
    auto songUrl = dataObj["url"].toString();
    auto media_item = static_cast<model::MediaItem*>(item);
    media_item->url = songUrl;
    emit songUrlStatus(network::error_code::NoError);
  }
}

void service::SongService::onGetSongLyricFinished(
    network::error_code::ErrorCode code, const QByteArray& data,
    qulonglong id) {
  if (code == network::error_code::NoError) {
    auto mediaItem = g_idToMediaMap[id];
    if (mediaItem != nullptr) {
      QJsonDocument doc = QJsonDocument::fromJson(data);
      auto obj = doc.object();
      auto lyricStr = obj["lrc"].toObject()["lyric"].toString();
      mediaItem->lyrics = parseLyricStr(lyricStr);
    }
  }
  emit songLyricStatus(code);
}

QVariantList service::SongService::parseLyricStr(const QString& lyric) {
  QRegularExpression regex(R"($$(\d{2}):(\d{2})\.(\d{3})$$\s*(.*))");
  QStringList lines = lyric.split(",");
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
      map["text"] = text;
      map["end"] = totalMs;
      result.append(map);
    }
  }
  return result;
}

void service::SongService::getSongUrl(qulonglong id) {
  auto mediaItem = g_idToMediaMap[id];
  if (!mediaItem->url.isEmpty()) {
    return;
  }
  if (mediaItem != nullptr) {
    m_network.getSongUrl(id, mediaItem);
  }
}

void service::SongService::checkSongEnable(qulonglong id) {}

void service::SongService::getSongComments(qulonglong id) {}

void service::SongService::getSongLyric(qulonglong id) {}

void service::SongService::getSongNewLyric(qulonglong id) {}
