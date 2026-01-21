#include "recommended_playlist_service.h"
#include <qglobal.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <qobject.h>

#include <QJsonArray>
#include <QJsonDocument>
#include "recommended_playlist_network.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QThread>
#include <QTimer>
#include <QtConcurrent>

namespace service {

RecommendedPlaylistService::RecommendedPlaylistService(QObject* parent)
    : QObject(parent) {
  QThread* netThread = new QThread;
  m_network.moveToThread(netThread);
  using namespace network;
  connect(&m_network, &RecommendedPlaylistNetwork::getHighqualityDataFinished,
          this, &RecommendedPlaylistService::onGetHighqualityFinished,
          Qt::QueuedConnection);
  connect(&m_network, &RecommendedPlaylistNetwork::getTopDataFinished, this,
          &RecommendedPlaylistService::onGetTopFinished, Qt::QueuedConnection);
  connect(&m_network, &RecommendedPlaylistNetwork::getPlaylistsCatlistFinished,
          this, &RecommendedPlaylistService::onGetCategoriesFinished,
          Qt::QueuedConnection);
  netThread->start();
}

void RecommendedPlaylistService::getHighquality(const QString& tag,
                                                qint32 offset, qint32 limit) {
  m_network.getHighqualityData(tag, offset, limit);
}

void RecommendedPlaylistService::getTop(const QString& tag, qint32 offset,
                                        qint32 limit) {
  m_network.getTopData(tag, offset, limit);
}

void RecommendedPlaylistService::getCategories() {
  m_network.getCategoriesData();
}

// 公共的 JSON 解析方法
PlaylistItemListPtr RecommendedPlaylistService::parsePlaylistData(
    error_code::ErrorCode code, const QByteArray& data) {

  PlaylistItemListPtr ptr(nullptr);

  if (code != error_code::NoError) {
    return ptr;
  }

  QJsonDocument doc = QJsonDocument::fromJson(data);
  if (doc.isNull() || doc.isEmpty()) {
    return ptr;
  }

  auto obj = doc.object();
  if (obj["code"].toInt() != 200) {
    return ptr;
  }

  ptr = PlaylistItemListPtr::create();
  QJsonArray playlists = obj["playlists"].toArray();

  for (const QJsonValue& playlist : playlists) {
    ptr->append(parsePlaylistItem(playlist.toObject()));
  }

  return ptr;
}

PlaylistItem RecommendedPlaylistService::parsePlaylistItem(
    const QJsonObject& o) {
  PlaylistItem item;
  item.setId(o["id"].toVariant().toLongLong());
  item.setName(o["name"].toString());
  item.setUserId(o["userId"].toVariant().toLongLong());
  item.setCreateTime(o["createTime"].toVariant().toLongLong());
  item.setUpdateTime(o["updateTime"].toVariant().toLongLong());
  item.setCoverUrl(QUrl(o["coverImgUrl"].toString()));
  item.setDesc(o["description"].toString());
  item.setTags(formatTags(o["tags"].toArray()));
  item.setPlayCount(o["playCount"].toVariant().toLongLong());
  item.setCreator(formatCreator(o["creator"].toObject()));
  item.setSubscribed(o["subscribed"].toBool());
  return item;
}

error_code::ErrorCode RecommendedPlaylistService::getActualErrorCode(
    error_code::ErrorCode networkCode, const PlaylistItemListPtr& ptr) {

  if (networkCode == error_code::NoError && (!ptr || ptr->isEmpty())) {
    return error_code::JsonContentError;
  }

  return networkCode;
}

void RecommendedPlaylistService::onGetHighqualityFinished(
    error_code::ErrorCode code, const QByteArray& data) {
  PlaylistItemListPtr ptr = parsePlaylistData(code, data);
  emit getHighqualityFinished(getActualErrorCode(code, ptr), ptr);
}

void RecommendedPlaylistService::onGetTopFinished(error_code::ErrorCode code,
                                                  const QByteArray& data) {
  PlaylistItemListPtr ptr = parsePlaylistData(code, data);
  emit getTopFinished(getActualErrorCode(code, ptr), ptr);  // 修正拼写
}

QStringList RecommendedPlaylistService::formatTags(const QJsonArray& array) {
  QStringList tags;
  for (const QJsonValue& value : array) {
    tags.append(value.toString());
  }
  return tags;
}

UserItem RecommendedPlaylistService::formatCreator(const QJsonObject& object) {
  UserItem user;
  user.setId(object["userId"].toVariant().toLongLong());
  user.setName(object["nickname"].toString());
  user.setAvatarUrl(object["avatarUrl"].toString());
  user.setBackgroundUrl(object["backgroundUrl"].toString());
  user.setExpertTags(formatTags(object["expertTags"].toArray()));
  user.setBirthday(object["birthday"].toVariant().toLongLong());
  user.setFollowed(object["followed"].toBool());
  return user;
}

QVector<UserItem> RecommendedPlaylistService::formatSubscribers(
    const QJsonArray& array) {
  QVector<UserItem> result;
  for (const auto& v : array) {
    result.append(formatCreator(v.toObject()));
  }
  return result;
}

UserItem RecommendedPlaylistService::formatUserDataInComment(
    const QJsonObject& object) {
  UserItem data;
  data.setId(object["userId"].toVariant().toULongLong());
  data.setAvatarUrl(object["avatarUrl"].toString());
  data.setName(object["nickname"].toString());
  return data;
}

void RecommendedPlaylistService::onGetCategoriesFinished(
    error_code::ErrorCode code, const QByteArray& data) {
  QMap<QString, QStringList> result;
  if (code == error_code::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    auto obj = doc.object();
    auto subs = obj["sub"].toArray();                // 标签
    auto categories = obj["categories"].toObject();  // 分类
    for (int i = 0; i < categories.size(); i++) {
      QStringList list;
      auto category = categories[QString::number(i)].toString();
      for (const auto& sub : subs) {
        auto o = sub.toObject();
        if (o["category"].toInt() == i) {
          list.append(o["name"].toString());
        }
      }
      result.insert(category, list);
    }
  }
  emit getCategoriesFinished(code, result);
}

//void PlaylistService::onGetPlaylistDetail(network::error_code::ErrorCode code,
//                                          const QByteArray& data,
//                                          qulonglong id) {
//  QtConcurrent::run([code, data, id, this] {
//    if (code == network::error_code::NoError) {
//      QJsonDocument doc = QJsonDocument::fromJson(data);
//      auto obj = doc.object();
//      auto playlist = obj["playlist"].toObject();
//      auto tracks = playlist["tracks"].toArray();
//      auto fitem = g_idToPlaylistMap[id];
//      auto model = fitem->mediaItemModel();
//      QVector<entities::MediaItem*> mediaItems;
//      for (const QJsonValue& track : tracks) {
//        entities::MediaItem* item =
//            g_idToMediaMap[track["id"].toVariant().toLongLong()];
//        if (item == nullptr) {
//          item = new entities::MediaItem();
//          g_idToMediaMap[track["id"].toVariant().toLongLong()] = item;
//        }
//        item->id = track["id"].toVariant().toLongLong();
//        item->name = track["name"].toString();
//        entities::AlbumData albumData;
//        auto albumObj = track["al"].toObject();
//        albumData.setId(albumObj["id"].toVariant().toLongLong());
//        albumData.setName(albumObj["name"].toString());
//        albumData.setPicUrl("image://net/" + albumObj["picUrl"].toString());
//        item->albumdata = albumData;
//        auto artistsArr = track["ar"].toArray();
//        entities::AristData aristData;
//        item->artists.clear();
//        for (const auto& artistValue : artistsArr) {
//          auto artistObj = artistValue.toObject();
//          aristData.setId(artistObj["id"].toVariant().toLongLong());
//          aristData.setName(artistObj["name"].toString());
//          item->artists.append(aristData);
//        }
//        item->duration = track["dt"].toVariant().toLongLong();
//        mediaItems.append(item);
//      }
//      QMetaObject::invokeMethod(model, [model, mediaItems]() mutable {
//        model->appendItems(
//            mediaItems);  // Move GUI-related operations to the GUI thread.
//      });
//      auto subscribers = playlist["subscribers"].toArray();
//      QVariantList list;

//      int limit = 30;
//      for (const QJsonValue& subscriber : subscribers) {
//        QJsonObject subscriberObj = subscriber.toObject();
//        UserItem userData;
//        userData.setId(subscriberObj["userId"].toVariant().toLongLong());
//        userData.setAvatarUrl(subscriberObj["avatarUrl"].toString());
//        userData.setName(subscriberObj["nickname"].toString());
//        userData.setBackgroundUrl(subscriberObj["backgroundUrl"].toString());
//        userData.setGender(subscriberObj["gender"].toInt());
//        userData.setDesc(subscriberObj["description"].toString());
//        list.append(QVariant::fromValue(userData));
//        if (limit-- <= 0)
//          break;
//      }
//      fitem->setSubscribers(list);
//      emit playlistSubscribersStatus(network::error_code::NoError);
//    }
//  });
//}

//void PlaylistService::onGetPlaylistTracks(network::error_code::ErrorCode code,
//                                          const QByteArray& data, void* item) {
//  if (code == network::error_code::NoError) {
//    QJsonDocument doc = QJsonDocument::fromJson(data);
//    if (doc.isNull() || doc.isEmpty()) {
//    } else {
//      auto obj = doc.object();
//      QJsonArray tracks = obj["songs"].toArray();
//      auto fitem = static_cast<PlaylistItem*>(item);
//      auto model = fitem->mediaItemModel();
//      for (const QJsonValue& track : tracks) {
//        entities::MediaItem* mediaItem =
//            g_idToMediaMap[track["id"].toVariant().toLongLong()];
//        if (mediaItem == nullptr) {
//          mediaItem = new entities::MediaItem();
//          g_idToMediaMap[track["id"].toVariant().toLongLong()] = mediaItem;
//        }
//        mediaItem->id = track["id"].toVariant().toLongLong();
//        mediaItem->name = track["name"].toString();
//        entities::AlbumData albumData;
//        auto albumObj = track["al"].toObject();
//        albumData.setId(albumObj["id"].toVariant().toLongLong());
//        albumData.setName(albumObj["name"].toString());
//        albumData.setPicUrl("image://net/" + albumObj["picUrl"].toString());
//        mediaItem->albumdata = albumData;
//        auto artistsArr = track["ar"].toArray();
//        entities::AristData aristData;
//        for (const auto& artistValue : artistsArr) {
//          auto artistObj = artistValue.toObject();
//          aristData.setId(artistObj["id"].toVariant().toLongLong());
//          aristData.setName(artistObj["name"].toString());
//          mediaItem->artists.append(aristData);
//        }
//        mediaItem->duration = track["dt"].toVariant().toLongLong();
//        model->appendItem(mediaItem);
//      }
//    }
//  }
//}

//void PlaylistService::onGetPlaylistComments(network::error_code::ErrorCode code,
//                                            const QByteArray& data,
//                                            qulonglong id) {
//  if (code == network::error_code::NoError) {
//    QJsonDocument doc = QJsonDocument::fromJson(data);
//    if (doc.isNull() || doc.isEmpty()) {
//    } else {
//      auto obj = doc.object();
//      QJsonArray commentsArr = obj["comments"].toArray();
//      auto fitem = g_idToPlaylistMap[id];
//      QVariantList commentDatas;
//      for (const auto& commentValue : commentsArr) {
//        CommentItem tempData;
//        auto commentObj = commentValue.toObject();
//        tempData.setId(commentObj["commentId"].toVariant().toULongLong());
//        tempData.setContent(commentObj["content"].toString());
//        tempData.setLikedCount(
//            commentObj["likedCount"].toVariant().toULongLong());
//        tempData.setTime(commentObj["time"].toVariant().toULongLong());
//        tempData.setUserData(
//            formatUserdDataInComment(commentObj["user"].toObject()));
//        commentDatas.append(QVariant::fromValue(tempData));
//      }
//      fitem->setCommentItems(commentDatas);
//      emit playlistCommentsStatus(network::error_code::NoError);
//    }
//  }
//}

}  // namespace service
