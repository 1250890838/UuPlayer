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
  using namespace network;
  connect(&m_network, &RecommendedPlaylistNetwork::highqualityReady, this,
          &RecommendedPlaylistService::onHighqualityReady);
  connect(&m_network, &RecommendedPlaylistNetwork::topReady, this,
          &RecommendedPlaylistService::onTopReady);
  connect(&m_network, &RecommendedPlaylistNetwork::CategoriesReady, this,
          &RecommendedPlaylistService::onCategoriesReady);
}

void RecommendedPlaylistService::fetchHighquality(const QString& tag,
                                                  qint32 offset, qint32 limit) {
  m_network.fetchHighquality(tag, offset, limit);
}

void RecommendedPlaylistService::fetchTop(const QString& tag, qint32 offset,
                                          qint32 limit) {
  m_network.fetchTop(tag, offset, limit);
}

void RecommendedPlaylistService::fetchCategories() {
  m_network.fetchCategories();
}

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

void RecommendedPlaylistService::onHighqualityReady(error_code::ErrorCode code,
                                                    const QByteArray& data) {
  PlaylistItemListPtr ptr = parsePlaylistData(code, data);
  emit highqualityReady(getActualErrorCode(code, ptr), ptr);
}

void RecommendedPlaylistService::onTopReady(error_code::ErrorCode code,
                                            const QByteArray& data) {
  PlaylistItemListPtr ptr = parsePlaylistData(code, data);
  emit topReady(getActualErrorCode(code, ptr), ptr);  // 修正拼写
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

void RecommendedPlaylistService::onCategoriesReady(error_code::ErrorCode code,
                                                   const QByteArray& data) {
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
  emit categoriesReady(code, result);
}
}  // namespace service
