#include "song_url_service.h"

SongUrlService::SongUrlService(QObject *parent)
    : QObject{parent}
{

}
//void SongLyricService::onGetSongUrlFinished(network::error_code::ErrorCode code,
//                                            const QByteArray& data,
//                                            void* item) {
//  if (code == network::error_code::NoError) {
//    QJsonDocument doc = QJsonDocument::fromJson(data);
//    auto obj = doc.object();
//    auto dataArr = obj["data"].toArray();
//    if (dataArr.empty())
//      return;

//    auto dataObj = dataArr[0].toObject();
//    auto songUrl = dataObj["url"].toString();
//    auto media_item = static_cast<entities::MediaItem*>(item);
//    media_item->url = songUrl;
//    emit songUrlStatus(network ::error_code::NoError);
//  }
//}
