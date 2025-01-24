#include "playlist_network.h"
#include <qnetworkreply.h>
#include "api_network.h"
#include "basic_network.h"

namespace network {
void PlaylistNetwork::getHighqualityPlaylists(qint32 limit, qint32 tag) {
  QNetworkRequest request;
  QUrl url = QUrl(network_api::apiGetHighqualityPlaylists + "?" +
                  "limit=" + QString::number(limit));
  if (tag != -1) {
    url.setUrl(url.toString(QUrl::None) + "&" + "tag=" + QString::number(tag));
  }
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply, this]() {
    auto e = reply->error();
    if (e == QNetworkReply::NoError) {
      QByteArray data = reply->readAll();
      emit getHighqualityPlaylistsFinished(error_code::NoError, data);
    } else {
       emit this->getHighqualityPlaylistsFinished(error_code::OtherError,
                                                 QByteArray());
    }
  });
}

void PlaylistNetwork::getSelectivePlaylists(qint32 limit, qint32 tag) {
  QNetworkRequest request;
  QUrl url = network_api::host + network_api::apiGetSelectivePlaylists + "?" +
             "limit=" + QString::number(limit) + "&" +
             "tag=" + QString::number(tag);
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply, this]() {
    auto e = reply->error();
    if (e == QNetworkReply::NoError) {
      QByteArray data = reply->readAll();
      emit getSelectivePlaylistsFinished(error_code::NoError, data);
    } else {
        emit getSelectivePlaylistsFinished(error_code::OtherError,
                                           QByteArray());
    }
  });
}
  void PlaylistNetwork::getPlaylistsCatlist() {
    QNetworkRequest request;
    QUrl url = network_api::host + network_api::apiCatlist;
    request.setUrl(url);
    auto reply = this->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this]() {
      auto e = reply->error();
      if (e == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        emit getSelectivePlaylistsFinished(error_code::NoError, data);
      } else {
        emit getSelectivePlaylistsFinished(error_code::OtherError,
                                           QByteArray());
      }
  });
}

}  // namespace network
