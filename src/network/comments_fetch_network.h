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
  void getMusic(qulonglong id, quint32 offset, quint32 limit);
  void getAlbum(qulonglong id, quint32 offset, quint32 limit);
  void getPlaylist(qulonglong id, quint32 offset, quint32 limit);
  void getMv(qulonglong id, quint32 offset, quint32 limit);

 private:
  void getComments(const QString& apiUrl, qulonglong id, quint32 offset,
                   quint32 limit,
                   void (CommentsFetchNetwork::*finishedSignal)(
                       error_code::ErrorCode, const QByteArray&));
  void handleNetworkReply(QNetworkReply* reply,
                          void (CommentsFetchNetwork::*finishedSignal)(
                              error_code::ErrorCode, const QByteArray&));
 signals:
  void getMusicFinished(error_code::ErrorCode code, const QByteArray& data);
  void getAlbumFinished(error_code::ErrorCode code, const QByteArray& data);
  void getPlaylistFinished(error_code::ErrorCode code, const QByteArray& data);
  void getMvFinished(error_code::ErrorCode code, const QByteArray& data);
};
}  // namespace network
#endif // COMMENTSFETCHNETWORK_H
