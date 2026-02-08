#include "playlistalbum_detail_network.h"

#include <QNetworkReply>

namespace network {

PlaylistAlbumDetailNetwork::PlaylistAlbumDetailNetwork() {}

void PlaylistAlbumDetailNetwork::fetchPlaylist(qulonglong id) {
  fetchHelper(network_api::apiPlaylistDetail, id,
              &PlaylistAlbumDetailNetwork::playlistReady);
}

void PlaylistAlbumDetailNetwork::fetchPlaylistTracks(qulonglong id) {}

void PlaylistAlbumDetailNetwork::fetchAlbum(qulonglong id) {
  fetchHelper(network_api::apiAlbumDetail, id,
              &PlaylistAlbumDetailNetwork::albumReady);
}

void PlaylistAlbumDetailNetwork::fetchPlaylistSubscribers(qulonglong id,
                                                          quint32 offset,
                                                          quint32 limit) {
  QNetworkRequest request;
  QUrl url = network_api::apiPlaylistSubscribers + "?" +
             "id=" + QString::number(id) + "&" +
             "offset=" + QString::number(offset) + "&" +
             "limit=" + QString::number(limit);
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply, this] {
    auto code = handleReplyErrorCode(reply);
    auto data = reply->readAll();
    emit playlistSubscribersReady(code, data);
    reply->deleteLater();
  });
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
