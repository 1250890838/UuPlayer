#include "playlist_network.h"
#include <qnetworkreply.h>
#include "api_network.h"
#include "basic_network.h"

namespace network {
void PlaylistNetwork::getHighqualityPlaylists(qint32 limit, qint32 tag) {
  QNetworkRequest request;
  QUrl url;
  if (tag != -1) {
    url = QUrl(QString("%1?limit=%2&tag=%3")
                   .arg(network_api::apiGetHighqualityPlaylists)
                   .arg(limit)
                   .arg(tag));
  } else {
    url = QUrl(QString("%1?limit=%2")
                   .arg(network_api::apiGetHighqualityPlaylists)
                   .arg(limit));
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
  QUrl url = QString("%1?limit=%2&cat=%3&offset=%4")
                 .arg(network_api::apiGetSelectivePlaylists)
                 .arg(limit)
                 .arg(tag)
                 .arg(offset);
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

void PlaylistNetwork::getPlaylistDetail(qulonglong id){
  QNetworkRequest request;
  QUrl url = QString("%1?id=%2")
                 .arg(network_api::apiPlaylistDetail)
                 .arg(id);
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply,id,this]() {
    auto e = reply->error();
    if (e == QNetworkReply::NoError) {
      QByteArray data = reply->readAll();
      emit getPlaylistDetailFinished(error_code::NoError, data,id);
    } else {
      emit getPlaylistDetailFinished(error_code::OtherError,
                                       QByteArray(),id);
    }
    reply->deleteLater();
  });
}

void PlaylistNetwork::getPlaylistTracks(qulonglong id,void* item){
  QNetworkRequest request;
  QUrl url = QString("%1?id=%2")
                 .arg(network_api::apiPlaylistTracks)
                 .arg(id);
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

void PlaylistNetwork::getPlaylistComments(qulonglong id) {
  QNetworkRequest request;
  QUrl url = QString("%1?id=%2")
                 .arg(network_api::apiPlaylistComments)
                 .arg(id);
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply,id,this]() {
    auto e = reply->error();
    if (e == QNetworkReply::NoError) {
      QByteArray data = reply->readAll();
      emit getPlaylistCommentsFinished(error_code::NoError, data,id);
    } else {
      emit getPlaylistCommentsFinished(error_code::OtherError,
                                     QByteArray(),id);
    }
    reply->deleteLater();
  });
}

}  // namespace network
