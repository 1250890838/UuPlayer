#ifndef RECOMMENDED_PLAYLIST_NETWORK_H
#define RECOMMENDED_PLAYLIST_NETWORK_H
#include "basic_network.h"
#include "network_global.h"

#include <qnetworkaccessmanager.h>
#include <qstringview.h>
#include <qtmetamacros.h>
#include <qurl.h>

using namespace entities;
namespace network {
class NETWORK_DLL_EXPORT RecommendedPlaylistNetwork : public BasicNetwork {
  Q_OBJECT
 public:
  RecommendedPlaylistNetwork() = default;
  void fetchHighquality(const QString& tag, qint32 offset, qint32 limit);
  void fetchTop(const QString& tag, qint32 offset, qint32 limit);
  void fetchCategories();

 private:
  void fetchHelper(const QString& apiUrl, const QString& tag, qint32 offset,
                   qint32 limit,
                   void (RecommendedPlaylistNetwork::*finishedSignal)(
                       error_code::ErrorCode, const QByteArray&));
  void handleNetworkReply(QNetworkReply* reply,
                          void (RecommendedPlaylistNetwork::*finishedSignal)(
                              error_code::ErrorCode, const QByteArray&));
  //  void getPlaylistDetail(qulonglong id);

 signals:
  void highqualityReady(error_code::ErrorCode code, const QByteArray&);
  void topReady(error_code::ErrorCode code, const QByteArray&);
  void CategoriesReady(error_code::ErrorCode code, const QByteArray&);
  //  void getPlaylistDetailFinished(error_code::ErrorCode code, const QByteArray&,
  //                                 qulonglong id);
};
}  // namespace network
#endif
