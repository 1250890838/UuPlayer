#include "playlist_tracks_service.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "media_item.h"

namespace service {

PlaylistTracksService::PlaylistTracksService(QObject* parent)
    : QObject{parent} {
  using namespace network;
  connect(&m_network, &PlaylistTracksNetwork::ready, this,
          &PlaylistTracksService::onGetTracksFinished);
}

void PlaylistTracksService::fetch(qulonglong id, quint32 offset,
                                  quint32 limit) {
  m_network.fetch(id, offset, limit);
}

void PlaylistTracksService::onGetTracksFinished(error_code::ErrorCode code,
                                                const QByteArray& data) {
  MediaItemListPtr ptr = parseTracksData(code, data);
  emit ready(code, ptr);
}

MediaItemListPtr PlaylistTracksService::parseTracksData(
    error_code::ErrorCode code, const QByteArray& data) {
  if (code != error_code::NoError) {
    return MediaItemListPtr(nullptr);
  }
  QJsonDocument doc = QJsonDocument::fromJson(data);
  if (doc.isNull() || doc.isEmpty()) {
    return MediaItemListPtr(nullptr);
  }
  QJsonObject responseObj = doc.object();
  if (!responseObj.contains("songs")) {
    return MediaItemListPtr(nullptr);
  }
  return parseTracksArray(responseObj["songs"].toArray());
}

MediaItemListPtr PlaylistTracksService::parseTracksArray(
    const QJsonArray& tracksArray) {
  MediaItemListPtr ptr = MediaItemListPtr::create();
  for (const QJsonValue& trackValue : tracksArray) {
    MediaItem mediaItem = parseTrackObject(trackValue.toObject());
    ptr->append(mediaItem);
  }
  return ptr;
}

MediaItem PlaylistTracksService::parseTrackObject(const QJsonObject& trackObj) {
  MediaItem item;
  item.id = trackObj["id"].toVariant().toLongLong();
  item.name = trackObj["name"].toString();
  item.duration = trackObj["dt"].toVariant().toLongLong();
  item.albumdata = parseAlbumData(trackObj["al"].toObject());
  item.artists = parseArtistsArray(trackObj["ar"].toArray());
  return item;
}

entities::AlbumData PlaylistTracksService::parseAlbumData(
    const QJsonObject& albumObj) {
  entities::AlbumData albumData;
  albumData.setId(albumObj["id"].toVariant().toLongLong());
  albumData.setName(albumObj["name"].toString());
  albumData.setPicUrl("image://net/" + albumObj["picUrl"].toString());
  return albumData;
}

QList<AristItem> PlaylistTracksService::parseArtistsArray(
    const QJsonArray& artistsArray) {
  QList<AristItem> artists;
  for (const QJsonValue& artistValue : artistsArray) {
    AristItem artist = parseArtistObject(artistValue.toObject());
    artists.append(artist);
  }
  return artists;
}

AristItem PlaylistTracksService::parseArtistObject(
    const QJsonObject& artistObj) {
  AristItem artist;
  artist.setId(artistObj["id"].toVariant().toLongLong());
  artist.setName(artistObj["name"].toString());
  return artist;
}
}  // namespace service
