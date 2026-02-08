#ifndef PLAYLISTALBUMDETAILNETWORK_H
#define PLAYLISTALBUMDETAILNETWORK_H

#include "basic_network.h"
#include "network_global.h"

// 获取专辑/歌单详情
namespace network {
class NETWORK_DLL_EXPORT PlaylistAlbumDetailNetwork : public BasicNetwork {
  Q_OBJECT
 public:
  PlaylistAlbumDetailNetwork();
  void fetchPlaylist(qulonglong id);
  QT_DEPRECATED_X("not used")
  void fetchPlaylistTracks(qulonglong id);
  void fetchAlbum(qulonglong id);
  void fetchPlaylistSubscribers(qulonglong id, quint32 offset, quint32 limit);

 private:
  void fetchHelper(const QString& apiUrl, qulonglong id,
                   NetworkReadySignal<PlaylistAlbumDetailNetwork> signal);
 signals:
  void playlistReady(error_code::ErrorCode code, const QByteArray& data);
  void albumReady(error_code::ErrorCode code, const QByteArray& data);
  void playlistSubscribersReady(error_code::ErrorCode code,
                                const QByteArray& data);
};
}  // namespace network
#endif // PLAYLISTALBUMDETAILNETWORK_H
