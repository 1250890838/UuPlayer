#include "comments_fetch_network.h"

#include <QNetworkReply>

#include "api_network.h"

namespace network {
CommentsFetchNetwork::CommentsFetchNetwork() {}

void CommentsFetchNetwork::fetchMusic(qulonglong id, quint32 offset,
                                      quint32 limit) {
  fetchHelper(network_api::apiMusicComment, id, offset, limit,
              &CommentsFetchNetwork::musicReady);
}

void CommentsFetchNetwork::fetchAlbum(qulonglong id, quint32 offset,
                                      quint32 limit) {
  fetchHelper(network_api::apiAlbumComment, id, offset, limit,
              &CommentsFetchNetwork::albumReady);
}

void CommentsFetchNetwork::fetchPlaylist(qulonglong id, quint32 offset,
                                         quint32 limit) {
  fetchHelper(network_api::apiPlaylistComment, id, offset, limit,
              &CommentsFetchNetwork::playlistReady);
}

void CommentsFetchNetwork::fetchMv(qulonglong id, quint32 offset,
                                   quint32 limit) {
  fetchHelper(network_api::apiMvComment, id, offset, limit,
              &CommentsFetchNetwork::mvReady);
}

void CommentsFetchNetwork::fetchHelper(
    const QString& apiUrl, qulonglong id, quint32 offset, quint32 limit,
    NetworkReadySignal<CommentsFetchNetwork> signal) {
  QNetworkRequest request;
  QUrl url = apiUrl + "?" + "id=" + QString::number(id) + "&" +
             "limit=" + QString::number(limit) + "&" +
             "offset=" + QString::number(offset);
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this,
          [reply, this, signal]() { handleNetworkReply(reply, signal); });
}

void CommentsFetchNetwork::handleNetworkReply(
    QNetworkReply* reply, NetworkReadySignal<CommentsFetchNetwork> signal) {
  auto code = BasicNetwork::handleReplyErrorCode(reply);
  auto data = reply->readAll();
  emit(this->*signal)(code, data);
  reply->deleteLater();
}
}  // namespace network
