#ifndef COMMENTSFETCHNETWORK_H
#define COMMENTSFETCHNETWORK_H

#include <QObject>
#include "network_global.h"

#include "basic_network.h"
namespace network {
class NETWORK_DLL_EXPORT CommentsFetchNetwork : public BasicNetwork {
  Q_OBJECT
 public:
  CommentsFetchNetwork();
  void fetchMusic(qulonglong id, quint32 offset, quint32 limit);
  void fetchAlbum(qulonglong id, quint32 offset, quint32 limit);
  void fetchPlaylist(qulonglong id, quint32 offset, quint32 limit);
  void fetchMv(qulonglong id, quint32 offset, quint32 limit);

 private:
  void fetchHelper(const QString& apiUrl, qulonglong id, quint32 offset,
                   quint32 limit, NetworkReadySignal<CommentsFetchNetwork>);
  void handleNetworkReply(QNetworkReply* reply,
                          NetworkReadySignal<CommentsFetchNetwork>);
 signals:
  void musicReady(error_code::ErrorCode code, const QByteArray& data);
  void albumReady(error_code::ErrorCode code, const QByteArray& data);
  void playlistReady(error_code::ErrorCode code, const QByteArray& data);
  void mvReady(error_code::ErrorCode code, const QByteArray& data);
};
}  // namespace network
#endif // COMMENTSFETCHNETWORK_H
