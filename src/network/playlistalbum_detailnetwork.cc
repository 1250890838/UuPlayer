#include "playlistalbum_detailnetwork.h"

#include <QNetworkReply>

namespace network {

PlaylistAlbumDetailNetwork::PlaylistAlbumDetailNetwork()
{
  
}

void PlaylistAlbumDetailNetwork::fetchPlaylist(qulonglong id) {
  fetchHelper(network_api::apiPlaylistDetail, id,
              &PlaylistAlbumDetailNetwork::playlistReady);
}

void PlaylistAlbumDetailNetwork::fetchPlaylistTracks(qulonglong id) {}

void PlaylistAlbumDetailNetwork::fetchAlbum(qulonglong id) {
  fetchHelper(network_api::apiAlbumDetail, id,
              &PlaylistAlbumDetailNetwork::albumReady);
}

void PlaylistAlbumDetailNetwork::fetchHelper(
    const QString& apiUrl, qulonglong id,
    NetworkReadySignal<PlaylistAlbumDetailNetwork> signal) {
  QNetworkRequest request;
  QUrl url = apiUrl + "?" + "id=" + QString::number(id);
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply, signal, this]() {
    auto code = handleReplyErrorCode(reply);
    auto data = reply->readAll();
    emit(this->*signal)(code, data);
    reply->deleteLater();
  });
}
}  // namespace network
