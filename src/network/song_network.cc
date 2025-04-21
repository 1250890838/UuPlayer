#include "song_network.h"
#include <qnetworkreply.h>
#include "api_network.h"

namespace network {

void SongNetwork::getSongUrl(qulonglong id, void* item) {
  QNetworkRequest request;
  QUrl url = network_api::getSongUrl + "?" + "id=" + QString::number(id) + "&" +
             "level=standard";
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply, item, this]() {
    auto e = reply->error();
    if (e == QNetworkReply::NoError) {
      QByteArray data = reply->readAll();
      emit getSongUrlFinished(error_code::NoError, data, item);
    } else {
      emit getSongUrlFinished(error_code::OtherError, QByteArray(), item);
    }
  });
}

void SongNetwork::checkSongEnable(qulonglong id) {}

void SongNetwork::getSongComments(qulonglong id) {}

void SongNetwork::getSongLyric(qulonglong id) {}

void SongNetwork::getSongNewLyric(qulonglong id) {}

}  // namespace network
