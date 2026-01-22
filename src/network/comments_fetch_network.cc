#include "comments_fetch_network.h"

#include <QNetworkReply>

#include "api_network.h"

namespace network {
CommentsFetchNetwork::CommentsFetchNetwork() {}

void CommentsFetchNetwork::getMusic(qulonglong id, quint32 offset,
                                    quint32 limit) {
  getComments(network_api::apiMusicComment, id, offset, limit,
              &CommentsFetchNetwork::getMusicFinished);
}

void CommentsFetchNetwork::getAlbum(qulonglong id, quint32 offset,
                                    quint32 limit) {
  getComments(network_api::apiAlbumComment, id, offset, limit,
              &CommentsFetchNetwork::getAlbumFinished);
}

void CommentsFetchNetwork::getPlaylist(qulonglong id, quint32 offset,
                                       quint32 limit) {
  getComments(network_api::apiPlaylistComment, id, offset, limit,
              &CommentsFetchNetwork::getPlaylistFinished);
}

void CommentsFetchNetwork::getMv(qulonglong id, quint32 offset, quint32 limit) {
  getComments(network_api::apiMvComment, id, offset, limit,
              &CommentsFetchNetwork::getMvFinished);
}

void CommentsFetchNetwork::getComments(
    const QString& apiUrl, qulonglong id, quint32 offset, quint32 limit,
    void (CommentsFetchNetwork::*finishedSignal)(error_code::ErrorCode,
                                                 const QByteArray&)) {
  QNetworkRequest request;
  QUrl url = apiUrl + "?" + "id=" + QString::number(id) + "&" +
             "limit=" + QString::number(limit) + "&" +
             "offset=" + QString::number(offset);
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this,
          [reply, this, finishedSignal]() {
            handleNetworkReply(reply, finishedSignal);
          });
}

void CommentsFetchNetwork::handleNetworkReply(
    QNetworkReply* reply,
    void (CommentsFetchNetwork::*finishedSignal)(error_code::ErrorCode,
                                                 const QByteArray&)) {
  auto code = BasicNetwork::handleReplyErrorCode(reply);
  auto data = reply->readAll();
  emit(this->*finishedSignal)(code, data);
  reply->deleteLater();
}
}  // namespace network
