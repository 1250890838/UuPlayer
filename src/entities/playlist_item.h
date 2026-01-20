#ifndef PLAYLIST_ITEM_H
#define PLAYLIST_ITEM_H
#include <QObject>
#include "comment_item.h"
#include "entities_global.h"
#include "media_item.h"
#include "user_item.h"

namespace entities {

class ENTITIES_EXPORT PlaylistItem {
  Q_GADGET
  Q_PROPERTY(qulonglong id READ id)
  Q_PROPERTY(QString name READ name)
  Q_PROPERTY(qulonglong userId READ userId)
  Q_PROPERTY(qulonglong createTime READ createTime)
  Q_PROPERTY(qulonglong updateTime READ updateTime)
  Q_PROPERTY(QUrl coverUrl READ coverUrl)
  Q_PROPERTY(QString desc READ desc)
  Q_PROPERTY(qulonglong playCount READ playCount)
  Q_PROPERTY(QStringList tags READ tags)
  Q_PROPERTY(UserItem creator READ creator)
  Q_PROPERTY(qulonglong subscribedCount READ subscribedCount)
  Q_PROPERTY(QList<UserItem> subscribers READ subscribers)
  Q_PROPERTY(bool subscribed READ subscribed)
  Q_PROPERTY(QList<CommentItem> commentItems READ commentItems)

 public:
  PlaylistItem()
      : m_id(0),
        m_userId(0),
        m_createTime(0),
        m_updateTime(0),
        m_subscribed(false),
        m_mediaItems({}) {}
  ~PlaylistItem() = default;

 public:
  qulonglong id() const { return m_id; }
  QString name() const { return m_name; }
  qulonglong userId() const { return m_userId; }
  qulonglong createTime() const { return m_createTime; }
  qulonglong updateTime() const { return m_updateTime; }
  QUrl coverUrl() const { return m_coverUrl; }
  QString desc() const { return m_description; }
  QStringList tags() const { return m_tags; }
  UserItem creator() const { return m_creator; }
  qulonglong playCount() const { return m_playCount; }
  QList<UserItem> subscribers() const { return m_subscribers; }
  bool subscribed() const { return m_subscribed; }
  qulonglong subscribedCount() const { return m_subscribedCount; }
  QList<CommentItem> commentItems() const { return m_commentItems; }

  void setId(qulonglong id) { m_id = id; }
  void setName(const QString& name) { m_name = name; }
  void setUserId(qulonglong userId) { m_userId = userId; }
  void setCreateTime(qulonglong createTime) { m_createTime = createTime; }
  void setUpdateTime(qulonglong updateTime) { m_updateTime = updateTime; }
  void setCoverUrl(const QUrl& coverUrl) { m_coverUrl = coverUrl; }
  void setPlayCount(qulonglong count) { m_playCount = count; }
  void setDesc(const QString& desc) { m_description = desc; }
  void setTags(const QStringList& tags) { m_tags = tags; }
  void setCreator(const UserItem& creator) { m_creator = creator; }
  void setSubscribed(bool b) { m_subscribed = b; }
  void setSubscribers(const QList<UserItem>& subscribers) {
    m_subscribers = subscribers;
  }
  void setSubscribedCount(qulonglong count) { m_subscribedCount = count; }
  void setCommentItems(const QList<CommentItem>& data) {
    m_commentItems = data;
  }

 private:
  qulonglong m_id;
  QString m_name;
  qulonglong m_userId;
  qulonglong m_createTime;
  qulonglong m_updateTime;
  QUrl m_coverUrl;
  QString m_description;
  QStringList m_tags;
  qulonglong m_playCount;
  UserItem m_creator;
  QList<UserItem> m_subscribers;
  bool m_subscribed;
  qulonglong m_subscribedCount;
  QVector<MediaItem> m_mediaItems;
  QList<CommentItem> m_commentItems;
};
}  // namespace entities
#endif  // PLAYLIST_ITEM_H
