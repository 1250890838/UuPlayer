#include "playlist_tracks_network.h"
#include <QNetworkReply>

#include "api_network.h"

namespace network {
PlaylistTracksNetwork::PlaylistTracksNetwork() {}

void PlaylistTracksNetwork::getTracks(qulonglong id, quint32 offset,
                                      quint32 limit) {
  QNetworkRequest request;
  QUrl url = network_api::apiPlaylistTracks + "?" +
             "id=" + QString::number(id) + "&" +
             "offset=" + QString::number(offset);
  if (limit != -1) {
    url = url.toString() + "&" + "limit=" + QString::number(limit);
  }
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply, this]() {
    auto e = reply->error();
    if (e == QNetworkReply::NoError) {
      QByteArray data = reply->readAll();
      emit getPlaylistTracksFinished(error_code::NoError, data);
    } else {
      emit getPlaylistTracksFinished(error_code::OtherError, QByteArray());
    }
    reply->deleteLater();
  });
}
}  // namespace network
