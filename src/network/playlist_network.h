#ifndef PLAYLIST_NETWORK_H
#define PLAYLIST_NETWORK_H
#include "basic_network.h"
#include "network_global.h"

#include <qnetworkaccessmanager.h>
#include <qstringview.h>
#include <qtmetamacros.h>
#include <qurl.h>

namespace network {
class NETWORK_DLL_EXPORT PlaylistNetwork : public BasicNetwork {
  Q_OBJECT
 public:
  PlaylistNetwork() = default;
  void getHighqualityPlaylists(qint32 limit, qint32 tag);
  void getSelectivePlaylists(qint32 limit, const QString& tag, qint32 offest);
  void getPlaylistsCatlist();
  void getPlaylistDetail(qulonglong id, void* item);
  void getPlaylistTracks(qulonglong id, void* item);
  void getPlaylistComments(qulonglong id);
 signals:
  void getHighqualityPlaylistsFinished(error_code::ErrorCode code,
                                       const QByteArray&);
  void getSelectivePlaylistsFinished(error_code::ErrorCode code,
                                     const QByteArray&);
  void getPlaylistsCatlistFinished(error_code::ErrorCode code,
                                   const QByteArray&);
  void getPlaylistDetailFinished(error_code::ErrorCode code, const QByteArray&,
                                 void* item);
  void getPlaylistTracksFinished(error_code::ErrorCode code, const QByteArray&,
                                 void* item);
  void getPlaylistCommentsFinished(error_code::ErrorCode code,
                                   const QByteArray&,qulonglong id);
};
}  // namespace network
#endif
