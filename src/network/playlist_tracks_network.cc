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
    auto code = handleReplyErrorCode(reply);
    QByteArray data = reply->readAll();
    emit getPlaylistTracksFinished(code, data);
    reply->deleteLater();
  });
}
}  // namespace network
