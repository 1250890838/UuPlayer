#pragma once

#include <QList>
#include <QString>
#include <QStringList>
#include <QUrl>
#include <QtQml/qqmlregistration.h>

#include "mediaitem.h"
#include "useritem.h"

namespace entities {

class PlaylistItem {
  Q_GADGET
  QML_VALUE_TYPE(playlistItem)
  Q_PROPERTY(qulonglong id READ id)
  Q_PROPERTY(QString name READ name)
  Q_PROPERTY(qulonglong userId READ userId)
  Q_PROPERTY(qulonglong createTime READ createTime)
  Q_PROPERTY(QString desc READ desc)
  Q_PROPERTY(QUrl coverUrl READ coverUrl)
  Q_PROPERTY(qulonglong playCount READ playCount)
  Q_PROPERTY(qulonglong subscribedCount READ subscribedCount)
  Q_PROPERTY(QStringList tags READ tags)
  Q_PROPERTY(UserItem creator READ creator)
  Q_PROPERTY(QList<UserItem> subscribers READ subscribers)
  Q_PROPERTY(bool subscribed READ subscribed)
  Q_PROPERTY(QList<MediaItem> mediaItems READ mediaItems)

 public:
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }
  qulonglong userId() const { return m_userId; }
  void setUserId(qulonglong userId) { m_userId = userId; }
  qulonglong createTime() const { return m_createTime; }
  void setCreateTime(qulonglong createTime) { m_createTime = createTime; }
  QString desc() const { return m_desc; }
  void setDesc(const QString& desc) { m_desc = desc; }
  QUrl coverUrl() const { return m_coverUrl; }
  void setCoverUrl(const QUrl& url) { m_coverUrl = url; }
  qulonglong playCount() const { return m_playCount; }
  void setPlayCount(qulonglong count) { m_playCount = count; }
  qulonglong subscribedCount() const { return m_subscribedCount; }
  void setSubscribedCount(qulonglong count) { m_subscribedCount = count; }
  QStringList tags() const { return m_tags; }
  void setTags(const QStringList& tags) { m_tags = tags; }
  UserItem creator() const { return m_creator; }
  void setCreator(const UserItem& creator) { m_creator = creator; }
  QList<UserItem> subscribers() const { return m_subscribers; }
  void setSubscribers(const QList<UserItem>& subscribers) {
    m_subscribers = subscribers;
  }
  bool subscribed() const { return m_subscribed; }
  void setSubscribed(bool subscribed) { m_subscribed = subscribed; }
  QList<MediaItem> mediaItems() const { return m_mediaItems; }
  void setMediaItems(const QList<MediaItem>& items) { m_mediaItems = items; }

  bool operator==(const PlaylistItem& other) const { return id() == other.id(); }

 private:
  qulonglong m_id = 0;
  QString m_name;
  qulonglong m_userId = 0;
  qulonglong m_createTime = 0;
  QString m_desc;
  QUrl m_coverUrl;
  qulonglong m_playCount = 0;
  qulonglong m_subscribedCount = 0;
  QStringList m_tags;
  UserItem m_creator;
  QList<UserItem> m_subscribers;
  bool m_subscribed = false;
  QList<MediaItem> m_mediaItems;
};

}
