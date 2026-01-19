#include "playlist_service.h"
#include <qglobal.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <qobject.h>

#include <QJsonArray>
#include <QJsonDocument>
#include "basic_network.h"
#include "model/playlist_item_model.h"
#include "playlist_network.h"
#include "song_service.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QThread>
#include <QTimer>
#include <QtConcurrent>

namespace service {

QMap<qulonglong, MediaItem*> g_idToMediaMap;
QMap<qulonglong, PlaylistItem*> g_idToPlaylistMap;

PlaylistService::PlaylistService(QObject* parent)
    : QObject(parent), m_currLimit(4), m_currOffset(0) {
  QThread* netThread = new QThread;
  m_network.moveToThread(netThread);
  using namespace network;
  connect(&m_network, &PlaylistNetwork::getHighqualityPlaylistsFinished, this,
          &PlaylistService::onGetHighqualityPlaylists, Qt::QueuedConnection);
  connect(&m_network, &PlaylistNetwork::getSelectivePlaylistsFinished, this,
          &PlaylistService::onGetSelectivePlaylists, Qt::QueuedConnection);
  connect(&m_network, &PlaylistNetwork::getPlaylistsCatlistFinished, this,
          &PlaylistService::onGetPlaylistsCatlist, Qt::QueuedConnection);
  connect(&m_network, &PlaylistNetwork::getPlaylistDetailFinished, this,
          &PlaylistService::onGetPlaylistDetail, Qt::QueuedConnection);
  connect(&m_network, &PlaylistNetwork::getPlaylistTracksFinished, this,
          &PlaylistService::onGetPlaylistTracks, Qt::QueuedConnection);
  connect(&m_network, &PlaylistNetwork::getPlaylistCommentsFinished, this,
          &PlaylistService::onGetPlaylistComments, Qt::QueuedConnection);
  netThread->start();
}

void PlaylistService::getHighqualityPlaylists(qint32 limit, qint32 tag) {
  m_network.getHighqualityPlaylists(limit, tag);
}

void PlaylistService::getSelectivePlaylists() {
  if (m_currOffset == 0)
    m_currPlaylists.clear();
  m_network.getSelectivePlaylists(m_currLimit, m_currCat, m_currOffset);
  m_currOffset += m_currLimit;
}

void PlaylistService::getPlaylistsCatlist() {
  m_network.getPlaylistsCatlist();
}

void PlaylistService::getPlaylistDetail(qulonglong id) {
  m_network.getPlaylistDetail(id);
}

void PlaylistService::getPlaylistTracks(qulonglong id, PlaylistItem* item) {
  m_network.getPlaylistTracks(id, item);
}

void PlaylistService::getPlaylistComments(qulonglong id) {
  m_network.getPlaylistComments(id);
}

void PlaylistService::onGetHighqualityPlaylists(
    network::error_code::ErrorCode code, const QByteArray& data) {
  if (code == network::error_code::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() && doc.isEmpty()) {
      emit highqualityPlaylistsStatus(network::error_code::JsonContentError);
      m_currPlaylists.clear();

    } else {
      auto obj = doc.object();
      if (obj["code"].toInt() != 200) {
        emit highqualityPlaylistsStatus(network::error_code::JsonContentError);
        m_currPlaylists.clear();
      } else {
        QJsonArray playlists = obj["playlists"].toArray();
        for (const QJsonValue& playlist : playlists) {
          auto o = playlist.toObject();
          PlaylistItem* item = g_idToPlaylistMap.value(
              o["id"].toVariant().toLongLong(), nullptr);
          if (item == nullptr) {
            item = new PlaylistItem();
            g_idToPlaylistMap[o["id"].toVariant().toLongLong()] = item;
          }
          item->setId(o["id"].toVariant().toLongLong());
          item->setName(o["name"].toString());
          item->setUserId(o["userId"].toVariant().toLongLong());
          item->setCreateTime(o["createTime"].toVariant().toLongLong());
          item->setUpdateTime(o["updateTime"].toVariant().toLongLong());
          item->setCoverUrl(QUrl(o["coverImgUrl"].toString()));
          item->setDesc(o["description"].toString());
          item->setTags(formatTags(o["tags"].toArray()));
          item->setPlayCount(o["playCount"].toVariant().toLongLong());
          item->setCreator(formatCreator(o["creator"].toObject()));
          item->setSubscribed(o["subscribed"].toBool());
          m_currPlaylists.appendItem(item);
        }
      }
    }
  } else {
    emit highqualityPlaylistsStatus(code);
    m_currPlaylists.clear();
  }
}
void PlaylistService::onGetSelectivePlaylists(
    network::error_code::ErrorCode code, const QByteArray& data) {

  if (m_currOffset == 0) {
    m_currPlaylists.clear();
  }
  if (code == network::error_code::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || doc.isEmpty()) {
      emit selectivePlaylistsStatus(network::error_code::JsonContentError);
      m_currPlaylists.clear();

    } else {
      auto obj = doc.object();
      if (obj["code"].toInt() != 200) {
        emit selectivePlaylistsStatus(network::error_code::JsonContentError);
        m_currPlaylists.clear();
      } else {
        QJsonArray playlists = obj["playlists"].toArray();
        for (const QJsonValue& playlist : playlists) {
          auto o = playlist.toObject();
          PlaylistItem* item = g_idToPlaylistMap.value(
              o["id"].toVariant().toLongLong(), nullptr);
          if (item == nullptr) {
            item = new PlaylistItem();
            g_idToPlaylistMap[o["id"].toVariant().toLongLong()] = item;
          }
          item->setId(o["id"].toVariant().toLongLong());
          item->setName(o["name"].toString());
          item->setUserId(o["userId"].toVariant().toLongLong());
          item->setCreateTime(o["createTime"].toVariant().toLongLong());
          item->setUpdateTime(o["updateTime"].toVariant().toLongLong());
          item->setCoverUrl(QUrl(o["coverImgUrl"].toString()));
          item->setDesc(o["description"].toString());
          item->setTags(formatTags(o["tags"].toArray()));
          item->setPlayCount(o["playCount"].toVariant().toLongLong());
          item->setCreator(formatCreator(o["creator"].toObject()));
          item->setSubscribed(o["subscribed"].toBool());
          item->setSubscribedCount(
              o["subscribedCount"].toVariant().toULongLong());
          m_currPlaylists.appendItem(item);
          item->mediaItemModel()->clear();
          // this->getPlaylistTracks(item->id(), item);
        }
      }
    }
  } else {
    emit selectivePlaylistsStatus(code);
    m_currPlaylists.clear();
  }
}

QStringList PlaylistService::formatTags(const QJsonArray& array) {
  QStringList tags;
  for (const QJsonValue& value : array) {
    tags.append(value.toString());
  }
  return tags;
}

UserData PlaylistService::formatCreator(const QJsonObject& object) {
  UserData user;
  user.setId(object["userId"].toVariant().toLongLong());
  user.setName(object["nickname"].toString());
  user.setAvatarUrl(object["avatarUrl"].toString());
  user.setBackgroundUrl(object["backgroundUrl"].toString());
  user.setExpertTags(formatTags(object["expertTags"].toArray()));
  user.setBirthday(object["birthday"].toVariant().toLongLong());
  user.setFollowed(object["followed"].toBool());
  return user;
}

QVector<UserData> PlaylistService::formatSubscribers(const QJsonArray& array) {
  QVector<UserData> result;
  for (const auto& v : array) {
    result.append(formatCreator(v.toObject()));
  }
  return result;
}

UserData PlaylistService::formatUserdDataInComment(const QJsonObject& object) {
  UserData data;
  data.setId(object["userId"].toVariant().toULongLong());
  data.setAvatarUrl(object["avatarUrl"].toString());
  data.setName(object["nickname"].toString());
  return data;
}

void PlaylistService::onGetPlaylistsCatlist(network::error_code::ErrorCode code,
                                            const QByteArray& data) {
  if (!m_catlist.empty()) {
    emit playlistsCatlist(m_catlist);
    return;
  }
  if (code == network::error_code::NoError) {
    QVariantMap result;
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
    emit playlistsCatlist(result);
  }
}

void PlaylistService::onGetPlaylistDetail(network::error_code::ErrorCode code,
                                          const QByteArray& data,
                                          qulonglong id) {
  QtConcurrent::run([code, data, id, this] {
    if (code == network::error_code::NoError) {
      QJsonDocument doc = QJsonDocument::fromJson(data);
      auto obj = doc.object();
      auto playlist = obj["playlist"].toObject();
      auto tracks = playlist["tracks"].toArray();
      auto fitem = g_idToPlaylistMap[id];
      auto model = fitem->mediaItemModel();
      QVector<entities::MediaItem*> mediaItems;
      for (const QJsonValue& track : tracks) {
        entities::MediaItem* item =
            g_idToMediaMap[track["id"].toVariant().toLongLong()];
        if (item == nullptr) {
          item = new entities::MediaItem();
          g_idToMediaMap[track["id"].toVariant().toLongLong()] = item;
        }
        item->id = track["id"].toVariant().toLongLong();
        item->name = track["name"].toString();
        entities::AlbumData albumData;
        auto albumObj = track["al"].toObject();
        albumData.setId(albumObj["id"].toVariant().toLongLong());
        albumData.setName(albumObj["name"].toString());
        albumData.setPicUrl("image://net/" + albumObj["picUrl"].toString());
        item->albumdata = albumData;
        auto artistsArr = track["ar"].toArray();
        entities::AristData aristData;
        item->artists.clear();
        for (const auto& artistValue : artistsArr) {
          auto artistObj = artistValue.toObject();
          aristData.setId(artistObj["id"].toVariant().toLongLong());
          aristData.setName(artistObj["name"].toString());
          item->artists.append(aristData);
        }
        item->duration = track["dt"].toVariant().toLongLong();
        mediaItems.append(item);
      }
      QMetaObject::invokeMethod(model, [model, mediaItems]() mutable {
        model->appendItems(
            mediaItems);  // Move GUI-related operations to the GUI thread.
      });
      auto subscribers = playlist["subscribers"].toArray();
      QVariantList list;

      int limit = 30;
      for (const QJsonValue& subscriber : subscribers) {
        QJsonObject subscriberObj = subscriber.toObject();
        UserData userData;
        userData.setId(subscriberObj["userId"].toVariant().toLongLong());
        userData.setAvatarUrl(subscriberObj["avatarUrl"].toString());
        userData.setName(subscriberObj["nickname"].toString());
        userData.setBackgroundUrl(subscriberObj["backgroundUrl"].toString());
        userData.setGender(subscriberObj["gender"].toInt());
        userData.setDesc(subscriberObj["description"].toString());
        list.append(QVariant::fromValue(userData));
        if (limit-- <= 0)
          break;
      }
      fitem->setSubscribers(list);
      emit playlistSubscribersStatus(network::error_code::NoError);
    }
  });
}

void PlaylistService::onGetPlaylistTracks(network::error_code::ErrorCode code,
                                          const QByteArray& data, void* item) {
  if (code == network::error_code::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || doc.isEmpty()) {
    } else {
      auto obj = doc.object();
      QJsonArray tracks = obj["songs"].toArray();
      auto fitem = static_cast<PlaylistItem*>(item);
      auto model = fitem->mediaItemModel();
      for (const QJsonValue& track : tracks) {
        entities::MediaItem* mediaItem =
            g_idToMediaMap[track["id"].toVariant().toLongLong()];
        if (mediaItem == nullptr) {
          mediaItem = new entities::MediaItem();
          g_idToMediaMap[track["id"].toVariant().toLongLong()] = mediaItem;
        }
        mediaItem->id = track["id"].toVariant().toLongLong();
        mediaItem->name = track["name"].toString();
        entities::AlbumData albumData;
        auto albumObj = track["al"].toObject();
        albumData.setId(albumObj["id"].toVariant().toLongLong());
        albumData.setName(albumObj["name"].toString());
        albumData.setPicUrl("image://net/" + albumObj["picUrl"].toString());
        mediaItem->albumdata = albumData;
        auto artistsArr = track["ar"].toArray();
        entities::AristData aristData;
        for (const auto& artistValue : artistsArr) {
          auto artistObj = artistValue.toObject();
          aristData.setId(artistObj["id"].toVariant().toLongLong());
          aristData.setName(artistObj["name"].toString());
          mediaItem->artists.append(aristData);
        }
        mediaItem->duration = track["dt"].toVariant().toLongLong();
        model->appendItem(mediaItem);
      }
    }
  }
}

void PlaylistService::onGetPlaylistComments(network::error_code::ErrorCode code,
                                            const QByteArray& data,
                                            qulonglong id) {
  if (code == network::error_code::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || doc.isEmpty()) {
    } else {
      auto obj = doc.object();
      QJsonArray commentsArr = obj["comments"].toArray();
      auto fitem = g_idToPlaylistMap[id];
      QVariantList commentDatas;
      for (const auto& commentValue : commentsArr) {
        CommentData tempData;
        auto commentObj = commentValue.toObject();
        tempData.setId(commentObj["commentId"].toVariant().toULongLong());
        tempData.setContent(commentObj["content"].toString());
        tempData.setLikedCount(
            commentObj["likedCount"].toVariant().toULongLong());
        tempData.setTime(commentObj["time"].toVariant().toULongLong());
        tempData.setUserData(
            formatUserdDataInComment(commentObj["user"].toObject()));
        commentDatas.append(QVariant::fromValue(tempData));
      }
      fitem->setCommentData(commentDatas);
      emit playlistCommentsStatus(network::error_code::NoError);
    }
  }
}

}  // namespace service
