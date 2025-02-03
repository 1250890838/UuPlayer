#include "playlist_service.h"
#include <qglobal.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <qobject.h>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QThread>
#include <QTimer>
#include "basic_network.h"
#include "model/playlist_item_model.h"
#include "playlist_network.h"

namespace service {

PlaylistService::PlaylistService(QObject* parent) :
      QObject(parent),
      m_currLimit(4),
      m_currOffset(0)
{
  using namespace network;
  connect(&m_network, &PlaylistNetwork::getHighqualityPlaylistsFinished, this,
          &PlaylistService::onGetHighqualityPlaylists);
  connect(&m_network, &PlaylistNetwork::getSelectivePlaylistsFinished, this,
          &PlaylistService::onGetSelectivePlaylists);
  connect(&m_network, &PlaylistNetwork::getPlaylistsCatlistFinished, this,
          &PlaylistService::onGetPlaylistsCatlist);
}

void PlaylistService::getHighqualityPlaylists(qint32 limit, qint32 tag) {
  m_network.getHighqualityPlaylists(limit, tag);
}

void PlaylistService::getSelectivePlaylists() {
  if(m_currOffset==0) m_selectivePlaylists.clear();
  m_network.getSelectivePlaylists(m_currLimit, m_currCat,m_currOffset);
  m_currOffset+=m_currLimit;
}

void PlaylistService::getPlaylistsCatlist() {
  m_network.getPlaylistsCatlist();
}

void PlaylistService::getPlaylistDetail(qulonglong id,model::PlaylistItem* item){
  //m_network.getPlaylistDetail(id,item);
}

void PlaylistService::onGetHighqualityPlaylists(
    network::error_code::ErrorCode code, const QByteArray& data) {
  if (code == network::error_code::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() && doc.isEmpty()) {
      emit highqualityPlaylistsStatus(network::error_code::JsonContentError);
      m_highqualityPlaylists.clear();

    } else {
      auto obj = doc.object();
      if (obj["code"].toInt() != 200) {
        emit highqualityPlaylistsStatus(network::error_code::JsonContentError);
        m_highqualityPlaylists.clear();
      } else {
        QJsonArray playlists = obj["playlists"].toArray();
        for (const QJsonValue& playlist : playlists) {
          auto o = playlist.toObject();
          model::PlaylistItem item;
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
          item.setSubscribers(formatSubscribers(o["subscribers"].toArray()));
          item.setSubscribed(o["subscribed"].toBool());
          m_highqualityPlaylists.appendItem(item);
        }
      }
    }
  } else {
    emit highqualityPlaylistsStatus(code);
    m_highqualityPlaylists.clear();
  }
}
void PlaylistService::onGetSelectivePlaylists(
    network::error_code::ErrorCode code, const QByteArray& data) {

  if (code == network::error_code::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || doc.isEmpty()) {
      emit selectivePlaylistsStatus(network::error_code::JsonContentError);
      m_selectivePlaylists.clear();

    } else {
      auto obj = doc.object();
      if (obj["code"].toInt() != 200) {
        emit selectivePlaylistsStatus(network::error_code::JsonContentError);
        m_selectivePlaylists.clear();
      } else {
        QJsonArray playlists = obj["playlists"].toArray();
        for (const QJsonValue& playlist : playlists) {
          auto o = playlist.toObject();
          model::PlaylistItem item;
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
          item.setSubscribers(formatSubscribers(o["subscribers"].toArray()));
          item.setSubscribed(o["subscribed"].toBool());
          m_selectivePlaylists.appendItem(item);
        }
      }
    }
  } else {
    emit selectivePlaylistsStatus(code);
    m_selectivePlaylists.clear();
  }
}

QStringList PlaylistService::formatTags(const QJsonArray& array) {
  QStringList tags;
  for (const QJsonValue& value : array) {
    tags.append(value.toString());
  }
  return tags;
}

model::UserData PlaylistService::formatCreator(const QJsonObject& object) {
  model::UserData user;
  user.setId(object["userId"].toVariant().toLongLong());
  user.setName(object["nickname"].toString());
  user.setAvatarUrl(object["avatarUrl"].toString());
  user.setBackgroundUrl(object["backgroundUrl"].toString());
  user.setExpertTags(formatTags(object["expertTags"].toArray()));
  user.setBirthday(object["birthday"].toVariant().toLongLong());
  user.setFollowed(object["followed"].toBool());
  return user;
}

QVector<model::UserData> PlaylistService::formatSubscribers(
    const QJsonArray& array) {
  QVector<model::UserData> result;
  for (const auto& v : array) {
    result.append(formatCreator(v.toObject()));
  }
  return result;
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
    auto subs = obj["sub"].toArray(); // 标签
    auto categories = obj["categories"].toObject(); // 分类
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

void PlaylistService::onGetPlaylistDetail(network::error_code::ErrorCode code,const QByteArray& data,model::PlaylistItem* item){
  if(code == network::error_code::NoError){
    QJsonDocument doc = QJsonDocument::fromJson(data);
    auto obj = doc.object();
    auto playlist = obj["playlist"].toObject();
    auto tracks=obj["tracks"].toArray();
    auto model=item->mediaItemModel();
    for(const QJsonValue& track:tracks){
      model::MediaItem item;
      item.id=track["id"].toVariant().toLongLong();
      item.name=track["name"].toString();
      model::AlbumData albumData;
      auto albumObj=track["al"].toObject();
      albumData.setId(albumObj["id"].toVariant().toLongLong());
      albumData.setName(albumObj["name"].toString());
      albumData.setPicUrl(albumObj["picUrl"].toString());
      item.album=albumData;
      auto artistObj=track["ar"].toObject();
      model::AristData aristData;
      aristData.setId(artistObj["id"].toVariant().toLongLong());
      aristData.setName(artistObj["name"].toString());
      item.artist=aristData;
      item.duration=track["dt"].toVariant().toLongLong();
    }
  }
}

}// namespace service
