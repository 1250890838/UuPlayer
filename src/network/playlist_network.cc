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
    reply->deleteLater();
  });
}

void PlaylistNetwork::getSelectivePlaylists(qint32 limit, const QString& tag,qint32 offset) {
  QNetworkRequest request;
  QUrl url = network_api::apiGetSelectivePlaylists + "?" +
             "limit=" + QString::number(limit) + "&" +
             "cat=" + tag + "&" + "offset=" + QString::number(offset);
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
    reply->deleteLater();
  });
}
  void PlaylistNetwork::getPlaylistsCatlist() {
    QNetworkRequest request;
    QUrl url = network_api::apiCatlist;
    request.setUrl(url);
    auto reply = this->get(request);
    connect(reply, &QNetworkReply::finished, this, [reply, this]() {
      auto e = reply->error();
      if (e == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        emit getPlaylistsCatlistFinished(error_code::NoError, data);
      } else {
        emit getPlaylistsCatlistFinished(error_code::OtherError,
                                           QByteArray());
      }
      reply->deleteLater();
  });
}

void PlaylistNetwork::getPlaylistDetail(qulonglong id,void* item){
  QNetworkRequest request;
  QUrl url = network_api::apiPlaylistDetail + "?" + "id=" + QString::number(id);
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply,item,this]() {
    auto e = reply->error();
    if (e == QNetworkReply::NoError) {
      QByteArray data = reply->readAll();
      emit getPlaylistDetailFinished(error_code::NoError, data,item);
    } else {
      emit getPlaylistDetailFinished(error_code::OtherError,
                                       QByteArray(),item);
    }
    reply->deleteLater();
  });
}

void PlaylistNetwork::getPlaylistTracks(qulonglong id,void* item){
  QNetworkRequest request;
  QUrl url = network_api::apiPlaylistTracks + "?" + "id=" + QString::number(id);
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply,item,this]() {
    auto e = reply->error();
    if (e == QNetworkReply::NoError) {
      QByteArray data = reply->readAll();
      emit getPlaylistTracksFinished(error_code::NoError, data,item);
    } else {
      emit getPlaylistTracksFinished(error_code::OtherError,
                                     QByteArray(),item);
    }
    reply->deleteLater();
  });
}

void PlaylistNetwork::getPlaylistComments(qulonglong id, void* item) {
  QNetworkRequest request;
  QUrl url = network_api::apiPlaylistComments + "?" + "id=" + QString::number(id);
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply,item,this]() {
    auto e = reply->error();
    if (e == QNetworkReply::NoError) {
      QByteArray data = reply->readAll();
      emit getPlaylistCommentsFinished(error_code::NoError, data,item);
    } else {
      emit getPlaylistCommentsFinished(error_code::OtherError,
                                     QByteArray(),item);
    }
    reply->deleteLater();
  });
}

}  // namespace network
