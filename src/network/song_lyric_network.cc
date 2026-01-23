#include "song_lyric_network.h"
#include <qnetworkreply.h>
#include "api_network.h"

namespace network {

void SongLyricNetwork::fetchStandard(qulonglong id) {
  fetchHelper(network_api::apiSongNewLyric, id, &SongLyricNetwork::lyricReady);
}

void SongLyricNetwork::fetchVerbatim(qulonglong id) {
  fetchHelper(network_api::apiSongNewLyric, id,
              &SongLyricNetwork::verbatimReady);
}

void SongLyricNetwork::fetchHelper(
    const QString& apiUrl, qulonglong id,
    NetworkReadySignal<SongLyricNetwork> signal) {
  QNetworkRequest request;
  QUrl url = apiUrl + "?" + "id=" + QString::number(id);
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this,
          [reply, this, signal] { handleNetworkReply(reply, signal); });
}

void SongLyricNetwork::handleNetworkReply(
    QNetworkReply* reply, NetworkReadySignal<SongLyricNetwork> signal) {
  auto code = BasicNetwork::handleReplyErrorCode(reply);
  auto data = reply->readAll();
  emit(this->*signal)(code, data);
  reply->deleteLater();
}

}  // namespace network
