#ifndef PLAYLIST_NETWORK_H
#define PLAYLIST_NETWORK_H
#include <qnetworkaccessmanager.h>
#include <qstringview.h>
#include <qtmetamacros.h>
#include <qurl.h>
#include "basic_network.h"
#include "network_global.h"

namespace network {
class NETWORK_DLL_EXPORT PlaylistNetwork : public BasicNetwork {
  Q_OBJECT
 public:
  PlaylistNetwork() = default;
  void getHighqualityPlaylists(qint32 limit,qint32 tag);
  void getSelectivePlaylists(qint32 limit,qint32 tag);
  void getPlaylistsCatlist();
 signals:
  void getHighqualityPlaylistsFinished(error_code::ErrorCode code , const QByteArray&);
  void getSelectivePlaylistsFinished(error_code::ErrorCode code , const QByteArray&);
  void getPlaylistsCatlistFinished(error_code::ErrorCode code , const QByteArray&);
};
}  // namespace network
#endif
