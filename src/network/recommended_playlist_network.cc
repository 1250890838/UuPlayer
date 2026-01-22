#include "recommended_playlist_network.h"
#include <QNetworkReply>
#include "api_network.h"
#include "basic_network.h"

namespace network {
void RecommendedPlaylistNetwork::getHighqualityData(const QString& tag,
                                                    qint32 offset,
                                                    qint32 limit) {
  getPlaylistData(network_api::apiGetHighqualityPlaylists, tag, offset, limit,
                  &RecommendedPlaylistNetwork::getHighqualityDataFinished);
}

void RecommendedPlaylistNetwork::getTopData(const QString& tag, qint32 offset,
                                            qint32 limit) {
  getPlaylistData(network_api::apiGetTopPlaylists, tag, offset, limit,
                  &RecommendedPlaylistNetwork::getTopDataFinished);
}

void RecommendedPlaylistNetwork::getPlaylistData(
    const QString& apiUrl, const QString& tag, qint32 offset, qint32 limit,
    void (RecommendedPlaylistNetwork::*finishedSignal)(error_code::ErrorCode,
                                                       const QByteArray&)) {
  QNetworkRequest request;
  QUrl url = apiUrl + "?" + "limit=" + QString::number(limit) + "&" +
             "cat=" + tag + "&" + "offset=" + QString::number(offset);
  request.setUrl(url);

  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this,
          [reply, this, finishedSignal]() {
            handleNetworkReply(reply, finishedSignal);
          });
}

void RecommendedPlaylistNetwork::handleNetworkReply(
    QNetworkReply* reply,
    void (RecommendedPlaylistNetwork::*finishedSignal)(error_code::ErrorCode,
                                                       const QByteArray&)) {

  error_code::ErrorCode code = BasicNetwork::handleReplyErrorCode(reply);
  QByteArray data = reply->readAll();
  emit(this->*finishedSignal)(error_code::NoError, data);
  reply->deleteLater();
}

void RecommendedPlaylistNetwork::getCategoriesData() {
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
      emit getPlaylistsCatlistFinished(error_code::OtherError, QByteArray());
    }
    reply->deleteLater();
  });
}

//void PlaylistNetwork::getPlaylistDetail(qulonglong id) {
//  QNetworkRequest request;
//  QUrl url = network_api::apiPlaylistDetail + "?" + "id=" + QString::number(id);
//  request.setUrl(url);
//  auto reply = this->get(request);
//  connect(reply, &QNetworkReply::finished, this, [reply, id, this]() {
//    auto e = reply->error();
//    if (e == QNetworkReply::NoError) {
//      QByteArray data = reply->readAll();
//      emit getPlaylistDetailFinished(error_code::NoError, data, id);
//    } else {
//      emit getPlaylistDetailFinished(error_code::OtherError, QByteArray(), id);
//    }
//    reply->deleteLater();
//  });
//}

}  // namespace network
