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

PlaylistService::PlaylistService(QObject* parent) : QObject(parent) {
  using namespace network;
  connect(&m_network, &PlaylistNetwork::getHighqualityPlaylistsFinished, this,
          &PlaylistService::onGetHighqualityPlaylists);
  connect(&m_network, &PlaylistNetwork::getSelectivePlaylistsFinished, this,
          &PlaylistService::onGetSelectivePlaylists);
}

void PlaylistService::getHighqualityPlaylists(qint32 limit, qint32 tag) {
  m_network.getHighqualityPlaylists(limit, tag);
}

void PlaylistService::getSelectivePlaylists(qint32 limit, qint32 tag) {
  m_network.getSelectivePlaylists(limit, tag);
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
          item.id = o["id"].toVariant().toLongLong();
          item.name = o["name"].toString();
          item.userId = o["userId"].toVariant().toLongLong();
          item.createTime = o["createTime"].toVariant().toLongLong();
          item.updateTime = o["updateTime"].toVariant().toLongLong();
          item.coverUrl = o["coverImgUrl"].toString();
          item.description = o["description"].toString();
          item.tags = formatTags(o["tags"].toArray());
          item.playCount = o["playCount"].toVariant().toLongLong();
          item.creator = formatCreator(o["creator"].toObject());
          item.subscribers = formatSubscribers(o["subscribers"].toArray());
          item.subscribed = o["subscribed"].toBool();
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
    if (!doc.isNull() && !doc.isEmpty()) {
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
          item.id = o["id"].toVariant().toLongLong();
          item.name = o["name"].toString();
          item.userId = o["userId"].toVariant().toLongLong();
          item.createTime = o["createTime"].toVariant().toLongLong();
          item.updateTime = o["updateTime"].toVariant().toLongLong();
          item.coverUrl = o["coverImgUrl"].toString();
          item.description = o["description"].toString();
          item.tags = formatTags(o["tags"].toArray());
          item.playCount = o["playCount"].toVariant().toLongLong();
          item.creator = formatCreator(o["creator"].toObject());
          item.subscribers = formatSubscribers(o["subscribers"].toArray());
          item.subscribed = o["subscribed"].toBool();
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
}  // namespace service
