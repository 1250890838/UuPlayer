#ifndef PLAYLIST_NETWORK_H
#define PLAYLIST_NETWORK_H
#include "basic_network.h"
#include "network_global.h"

#include <qnetworkaccessmanager.h>
#include <qstringview.h>
#include <qtmetamacros.h>
#include <qurl.h>

using namespace entities;
namespace network {
class NETWORK_DLL_EXPORT PlaylistNetwork : public BasicNetwork {
  Q_OBJECT
 public:
  PlaylistNetwork() = default;
  void getHighqualityPlaylists(const QString& tag, qint32 offset, qint32 limit);
  void getTopPlaylists(const QString& tag, qint32 offset, qint32 limit);
  void getPlaylistsCatlist();
  //  void getPlaylistDetail(qulonglong id);
  //  void getPlaylistTracks(qulonglong id, void* item);
  //  void getPlaylistComments(qulonglong id);
 signals:
  void getHighqualityPlaylistsFinished(error_code::ErrorCode code,
                                       const QByteArray&);
  void getTopPlaylistsFinished(error_code::ErrorCode code, const QByteArray&);
  void getPlaylistsCatlistFinished(error_code::ErrorCode code,
                                   const QByteArray&);
  void getPlaylistDetailFinished(error_code::ErrorCode code, const QByteArray&,
                                 qulonglong id);
  void getPlaylistTracksFinished(error_code::ErrorCode code, const QByteArray&,
                                 void* item);
  void getPlaylistCommentsFinished(error_code::ErrorCode code,
                                   const QByteArray&, qulonglong id);
};
}  // namespace network
#endif
