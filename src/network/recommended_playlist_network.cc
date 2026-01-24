#include "recommended_playlist_network.h"
#include <QNetworkReply>
#include "api_network.h"
#include "basic_network.h"

namespace network {
void RecommendedPlaylistNetwork::fetchHighquality(const QString& tag,
                                                  qint32 offset, qint32 limit) {
  fetchHelper(network_api::apiGetHighqualityPlaylists, tag, offset, limit,
              &RecommendedPlaylistNetwork::highqualityReady);
}

void RecommendedPlaylistNetwork::fetchTop(const QString& tag, qint32 offset,
                                          qint32 limit) {
  fetchHelper(network_api::apiGetTopPlaylists, tag, offset, limit,
              &RecommendedPlaylistNetwork::topReady);
}

void RecommendedPlaylistNetwork::fetchHelper(
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

void RecommendedPlaylistNetwork::fetchCategories() {
  QNetworkRequest request;
  QUrl url = network_api::apiCatlist;
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply, this]() {
    auto e = reply->error();
    if (e == QNetworkReply::NoError) {
      QByteArray data = reply->readAll();
      emit CategoriesReady(error_code::NoError, data);
    } else {
      emit CategoriesReady(error_code::OtherError, QByteArray());
    }
    reply->deleteLater();
  });
}

}  // namespace network
