#ifndef PLAYLISTALBUM_DETAIL_SERVICE_H
#define PLAYLISTALBUM_DETAIL_SERVICE_H

#include <QObject>

#include "playlist_item.h"
#include "playlistalbum_detail_network.h"

namespace service {
using namespace entities;
using PlaylistItemPtr = QSharedPointer<PlaylistItem>;

class PlaylistAlbumDetailService : public QObject {
  Q_OBJECT
 public:
  explicit PlaylistAlbumDetailService(QObject* parent = nullptr);
 private slots:
  void onPlaylistReady(error_code::ErrorCode code, const QByteArray& data);

 private:
  QStringList formatTags(const QJsonArray& array);
  UserItem formatCreator(const QJsonObject& object);
  QList<UserItem> formatSubscribers(const QJsonArray& array);
 signals:
  void playlistReady(error_code::ErrorCode code, PlaylistItemPtr ptr);
};
}  // namespace service
#endif // PLAYLISTALBUM_DETAIL_SERVICE_H
