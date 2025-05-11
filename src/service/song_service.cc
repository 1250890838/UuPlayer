#include "song_service.h"

#include "model/media_item_model.h"
#include "playlist_service.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

service::SongService::SongService(QObject* parent) {
  connect(&m_network, &network::SongNetwork::getSongUrlFinished, this,
          &SongService::onGetSongUrlFinished);
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

void service::SongService::getSongUrl(qulonglong id) {
  auto mediaItem = g_idToMediaMap[id];
  if(!mediaItem->url.isEmpty()){
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
