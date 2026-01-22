#ifndef PLAYLISTTRACKSSERVICE_H
#define PLAYLISTTRACKSSERVICE_H

#include <QObject>

#include "media_item.h"
#include "playlist_tracks_network.h"
#include "service_global.h"

using MediaItemList = QList<MediaItem>;
using MediaItemListPtr = QSharedPointer<MediaItemList>;

class SERVICE_DLL_EXPORT PlaylistTracksService : public QObject {
  Q_OBJECT
 public:
  explicit PlaylistTracksService(QObject* parent = nullptr);
  /**
    * @brief Get tracks from playlist by ID
    * @param limit Max tracks to return (-1 means get ALL tracks)
    */
  void getTracks(qulonglong id, quint32 offset = 0, quint32 limit = -1);
 private slots:
  void onGetTracksFinished(error_code::ErrorCode code, const QByteArray& data);

 private:
  MediaItemListPtr parseTracksData(error_code::ErrorCode code,
                                   const QByteArray& data);
  AristItem parseArtistObject(const QJsonObject& artistObj);
  QList<AristItem> parseArtistsArray(const QJsonArray& artistsArray);
  entities::AlbumData parseAlbumData(const QJsonObject& albumObj);
  MediaItem parseTrackObject(const QJsonObject& trackObj);
  MediaItemListPtr parseTracksArray(const QJsonArray& tracksArray);
 signals:
  void getTracksFinished(error_code::ErrorCode code, MediaItemListPtr data);

 private:
  network::PlaylistTracksNetwork m_network;
};

#endif  // PLAYLISTTRACKSSERVICE_H
