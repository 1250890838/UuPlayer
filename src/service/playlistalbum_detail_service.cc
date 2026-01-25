#include "playlistalbum_detail_service.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

namespace service {
PlaylistAlbumDetailService::PlaylistAlbumDetailService(QObject* parent)
    : QObject{parent} {}

void PlaylistAlbumDetailService::onPlaylistReady(error_code::ErrorCode code,
                                                 const QByteArray& data) {

  PlaylistItemPtr ptr(nullptr);
  if (code == error_code::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    auto obj = doc.object();
    if (doc.isEmpty() || obj.isEmpty() || obj["code"].toInt() != 200) {
      code = error_code::JsonContentError;
    } else {
      ptr = PlaylistItemPtr::create();
      auto playlist = obj["playlist"].toObject();
      ptr->setId(playlist["id"].toVariant().toULongLong());
      ptr->setName(playlist["name"].toString());
      ptr->setUserId(playlist["userId"].toVariant().toULongLong());
      ptr->setCreateTime(playlist["createTime"].toVariant().toULongLong());
      ptr->setUpdateTime(playlist["updateTime"].toVariant().toULongLong());
      ptr->setCoverUrl(QUrl(playlist["coverImgUrl"].toString()));
      ptr->setPlayCount(playlist["playCount"].toVariant().toULongLong());
      ptr->setDesc(playlist["description"].toString());
      ptr->setTags(formatTags(playlist["tags"].toArray()));
      ptr->setCreator(formatCreator(playlist["creator"].toObject()));
      ptr->setSubscribers(formatSubscribers(playlist["subscribers"].toArray()));
      ptr->setSubscribedCount(
          playlist["subscribedCount"].toVariant().toULongLong());
      ptr->

          auto tracks = playlist["tracks"].toArray();
      QVector<MediaItem> mediaItems;
      for (const QJsonValue& track : tracks) {
        MediaItem item;
        item.id = track["id"].toVariant().toLongLong();
        item.name = track["name"].toString();
        AlbumData albumData;
        auto albumObj = track["al"].toObject();
        albumData.setId(albumObj["id"].toVariant().toLongLong());
        albumData.setName(albumObj["name"].toString());
        albumData.setPicUrl("image://net/" + albumObj["picUrl"].toString());
        item.albumdata = albumData;
        auto artistsArr = track["ar"].toArray();
        AristItem aristData;
        item.artists.clear();
        for (const auto& artistValue : artistsArr) {
          auto artistObj = artistValue.toObject();
          aristData.setId(artistObj["id"].toVariant().toLongLong());
          aristData.setName(artistObj["name"].toString());
          item.artists.append(aristData);
        }
        item.duration = track["dt"].toVariant().toLongLong();
        mediaItems.append(item);
      }
      ptr->setMediaItems(mediaItems);
      auto subscribers = playlist["subscribers"].toArray();
      QList<UserItem> list;
      for (const QJsonValue& subscriber : subscribers) {
        QJsonObject subscriberObj = subscriber.toObject();
        UserItem userData;
        userData.setId(subscriberObj["userId"].toVariant().toLongLong());
        userData.setAvatarUrl(subscriberObj["avatarUrl"].toString());
        userData.setName(subscriberObj["nickname"].toString());
        userData.setBackgroundUrl(subscriberObj["backgroundUrl"].toString());
        userData.setGender(subscriberObj["gender"].toInt());
        userData.setDesc(subscriberObj["description"].toString());
        list.append(userData);
      }
      ptr->setSubscribers(list);
    }
  }
  emit playlistReady(code, ptr);
}
}  // namespace service
