#ifndef PLAYLISTALBUM_DETAIL_SERVICE_H
#define PLAYLISTALBUM_DETAIL_SERVICE_H

#include <QObject>

#include "playlist_item.h"
#include "playlistalbum_detail_network.h"
#include "service_global.h"

namespace service {
using namespace entities;
using PlaylistItemPtr = QSharedPointer<PlaylistItem>;
using UserItemsPtr = QSharedPointer<QList<UserItem>>;

class SERVICE_DLL_EXPORT PlaylistAlbumDetailService : public QObject {
  Q_OBJECT
 public:
  explicit PlaylistAlbumDetailService(QObject* parent = nullptr);
  void fetchPlaylist(qulonglong id);
  void fetchPlaylistSubscribers(qulonglong id,quint32 offset,quint32 limit);
 private slots:
  void onPlaylistReady(error_code::ErrorCode code, const QByteArray& data);
  void onPlaylistSubscribers(error_code::ErrorCode, const QByteArray& data);

 private:
  QStringList formatTags(const QJsonArray& array);
  UserItem formatCreator(const QJsonObject& object);
  auto formatSubscribers(const QJsonArray& array);
  auto formatTracks(const QJsonArray& array);

  network::PlaylistAlbumDetailNetwork m_network;
 signals:
  void playlistReady(error_code::ErrorCode code, PlaylistItemPtr ptr);
  void playlistSubscribersReady(error_code::ErrorCode code, UserItemsPtr ptr);
};
}  // namespace service
#endif // PLAYLISTALBUM_DETAIL_SERVICE_H
