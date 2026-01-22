#include "song_lyric_network.h"
#include <qnetworkreply.h>
#include "api_network.h"

namespace network {

//void SongLyricNetwork::getSongUrl(qulonglong id, void* item) {
//  QNetworkRequest request;
//  QUrl url = network_api::getSongUrl + "?" + "id=" + QString::number(id) + "&" +
//             "level=standard";
//  request.setUrl(url);
//  auto reply = this->get(request);
//  connect(reply, &QNetworkReply::finished, this, [reply, item, this]() {
//    auto e = reply->error();
//    if (e == QNetworkReply::NoError) {
//      QByteArray data = reply->readAll();
//      emit getSongUrlFinished(error_code::NoError, data, item);
//    } else {
//      emit getSongUrlFinished(error_code::OtherError, QByteArray(), item);
//    }
//    reply->deleteLater();
//  });
//}

//void SongLyricNetwork::checkSongEnable(qulonglong id) {}

//void SongLyricNetwork::getSongComments(qulonglong id) {}

void SongLyricNetwork::getSongLyric(qulonglong id) {
  getLyricHelper(network_api::apiSongNewLyric, id,
                 &SongLyricNetwork::getSongLyricFinished);
}

void SongLyricNetwork::getSongVerbatimLyric(qulonglong id) {
  getLyricHelper(network_api::apiSongNewLyric, id,
                 &SongLyricNetwork::getSongVerbatimLyricFinished);
}

void SongLyricNetwork::getLyricHelper(
    const QString& apiUrl, qulonglong id,
    void (SongLyricNetwork::*finishedSignal)(error_code::ErrorCode,
                                             const QByteArray&)) {
  QNetworkRequest request;
  QUrl url = apiUrl + "?" + "id=" + QString::number(id);
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply, this, finishedSignal] {
    handleNetworkReply(reply, finishedSignal);
  });
}

void SongLyricNetwork::handleNetworkReply(
    QNetworkReply* reply,
    void (SongLyricNetwork::*finishedSignal)(error_code::ErrorCode,
                                             const QByteArray&)) {
  auto code = BasicNetwork::handleReplyErrorCode(reply);
  auto data = reply->readAll();
  emit(this->*finishedSignal)(code, data);
  reply->deleteLater();
}

}  // namespace network
