#ifndef PLAYLISTTRACKSNETWORK_H
#define PLAYLISTTRACKSNETWORK_H
#include "basic_network.h"
#include "network_global.h"

namespace network {
class NETWORK_DLL_EXPORT PlaylistTracksNetwork : public BasicNetwork {
  Q_OBJECT
 public:
  PlaylistTracksNetwork();
  void getTracks(qulonglong id, quint32 offset, quint32 limit);
 signals:
  void getPlaylistTracksFinished(error_code::ErrorCode, const QByteArray& data);
};
}  // namespace network
#endif // PLAYLISTTRACKSNETWORK_H
