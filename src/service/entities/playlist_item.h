#ifndef PLAYLIST_ITEM_H
#define PLAYLIST_ITEM_H
#include <QObject>
#include "model/media_item_model.h"
#include "user_item.h"

using namespace model;

namespace entities {

class PlaylistItem {
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
  Q_PROPERTY(UserData creator READ creator)
  Q_PROPERTY(qulonglong subscribedCount READ subscribedCount)
  Q_PROPERTY(QVector<UserData> subscribers READ subscribers)
  Q_PROPERTY(bool subscribed READ subscribed)
  Q_PROPERTY(MediaItemModel* mediaItemModel READ mediaItemModel)

 public:
  PlaylistItem()
      : m_id(0),
        m_userId(0),
        m_createTime(0),
        m_updateTime(0),
        m_subscribed(false),
        m_mediaItemModel(new MediaItemModel()) {}
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
  UserData creator() const { return m_creator; }
  qulonglong playCount() const { return m_playCount; }
  QVector<UserData> subscribers() const { return m_subscribers; }
  bool subscribed() const { return m_subscribed; }
  MediaItemModel* mediaItemModel() { return m_mediaItemModel; }
  qulonglong subscribedCount() const { return m_subscribedCount; }

  void setId(qulonglong id) { m_id = id; }
  void setName(const QString& name) { m_name = name; }
  void setUserId(qulonglong userId) { m_userId = userId; }
  void setCreateTime(qulonglong createTime) { m_createTime = createTime; }
  void setUpdateTime(qulonglong updateTime) { m_updateTime = updateTime; }
  void setCoverUrl(const QUrl& coverUrl) { m_coverUrl = coverUrl; }
  void setPlayCount(qulonglong count) { m_playCount = count; }
  void setDesc(const QString& desc) { m_description = desc; }
  void setTags(const QStringList& tags) { m_tags = tags; }
  void setCreator(const UserData& creator) { m_creator = creator; }
  void setSubscribed(bool b) { m_subscribed = b; }
  void setSubscribers(const QVector<UserData>& subscribers) {
    m_subscribers = subscribers;
  }
  void setSubscribedCount(qulonglong count) { m_subscribedCount = count; }

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
  UserData m_creator;
  QVector<UserData> m_subscribers;
  bool m_subscribed;
  qulonglong m_subscribedCount;
  MediaItemModel* m_mediaItemModel;
};
}
#endif  // PLAYLIST_ITEM_H
