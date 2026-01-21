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
  void getHighqualityData(const QString& tag, qint32 offset, qint32 limit);
  void getTopData(const QString& tag, qint32 offset, qint32 limit);
  void getCategoriesData();

 private:
  void getPlaylistData(const QString& apiUrl, const QString& tag, qint32 offset,
                       qint32 limit,
                       void (RecommendedPlaylistNetwork::*finishedSignal)(
                           error_code::ErrorCode, const QByteArray&));
  void handleNetworkReply(QNetworkReply* reply,
                          void (RecommendedPlaylistNetwork::*finishedSignal)(
                              error_code::ErrorCode, const QByteArray&));
  //  void getPlaylistDetail(qulonglong id);
  //  void getPlaylistTracks(qulonglong id, void* item);
  //  void getPlaylistComments(qulonglong id);

 signals:
  void getHighqualityDataFinished(error_code::ErrorCode code,
                                  const QByteArray&);
  void getTopDataFinished(error_code::ErrorCode code, const QByteArray&);
  void getPlaylistsCatlistFinished(error_code::ErrorCode code,
                                   const QByteArray&);
  //  void getPlaylistDetailFinished(error_code::ErrorCode code, const QByteArray&,
  //                                 qulonglong id);
  //  void getPlaylistTracksFinished(error_code::ErrorCode code, const QByteArray&,
  //                                 void* item);
  //  void getPlaylistCommentsFinished(error_code::ErrorCode code,
  //                                   const QByteArray&, qulonglong id);
};
}  // namespace network
#endif
