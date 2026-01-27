#include "song_url_service.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

SongUrlService::SongUrlService(QObject *parent)
    : QObject{parent}
{
  using namespace network;
  connect(&m_network, &SongUrlNetwork::ready, this, &SongUrlService::onReady);
}

void SongUrlService::fetch(qulonglong id,
                           sound_level::SoundQualityLevel level) {
  m_network.fetch(id, level);
}

void SongUrlService::onReady(error_code::ErrorCode code,
                             const QByteArray& data) {
  QUrl resultUrl;
  qulonglong id = 0;
  if (code == error_code::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    auto obj = doc.object();
    if (doc.isNull() || doc.isEmpty() || obj.isEmpty())
      code = error_code::JsonContentError;
    else {
      auto dataArr = obj["data"].toArray();
      if (dataArr.empty())
        return;
      auto dataObj = dataArr[0].toObject();
      id = dataObj["id"].toVariant().toULongLong();
      auto songUrl = dataObj["url"].toString();
      resultUrl = songUrl;
    }
  }
  emit ready(code, resultUrl, id);
}
