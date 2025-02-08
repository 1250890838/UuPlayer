#ifndef _MODEL_PLAYLIST_ITEM_MODEL_H
#define _MODEL_PLAYLIST_ITEM_MODEL_H

#include "media_item_model.h"

#include <qglobal.h>
#include <qtmetamacros.h>
#include <QAbstractListModel>
#include <QObject>
#include <QColor>
#include <QUrl>

#include <memory>

namespace model{
class UserData {
  Q_GADGET
  Q_PROPERTY(qulonglong id READ id WRITE setId)
  Q_PROPERTY(QUrl avatarUrl READ avatarUrl WRITE setAvatarUrl)
  Q_PROPERTY(QUrl backgroundUrl READ backgroundUrl WRITE setBackgroundUrl)
  Q_PROPERTY(QStringList expertTags READ expertTags WRITE setExpertTags)
  Q_PROPERTY(qulonglong birthday READ birthday WRITE setBirthday)
  Q_PROPERTY(bool followed READ followed WRITE setFollowed)
  Q_PROPERTY(QString name READ name WRITE setName)

 public:
  UserData() = default;
  ~UserData() = default;
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }
  QUrl avatarUrl() const { return m_avatarUrl; }
  void setAvatarUrl(const QUrl& url) { m_avatarUrl = url; }
  QUrl backgroundUrl() const { return m_backgroundUrl; }
  void setBackgroundUrl(const QUrl& url) { m_backgroundUrl = url; }
  QStringList expertTags() const { return m_expertTags; }
  void setExpertTags(const QStringList& tags) { m_expertTags = tags; }
  qulonglong birthday() const { return m_birthday; }
  void setBirthday(qulonglong birthday) { m_birthday = birthday; }
  bool followed() const { return m_followed; }
  void setFollowed(bool followed) { m_followed = followed; }

 private:
  qulonglong m_id;
  QString m_name;
  QUrl m_avatarUrl;
  QUrl m_backgroundUrl;
  QStringList m_expertTags;
  qulonglong m_birthday;
  bool m_followed;
};


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
  PlaylistItem() : m_id(0), m_userId(0), m_createTime(0), m_updateTime(0), m_subscribed(false),m_mediaItemModel(new MediaItemModel()) {}
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
  qulonglong playCount() const {return m_playCount;}
  QVector<UserData> subscribers() const { return m_subscribers; }
  bool subscribed() const { return m_subscribed; }
  MediaItemModel* mediaItemModel()  { return m_mediaItemModel; }
  qulonglong subscribedCount() const {return m_subscribedCount;}

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
  void setSubscribers(const QVector<UserData>& subscribers) { m_subscribers = subscribers; }
  void setSubscribedCount(qulonglong count) { m_subscribedCount = count;}

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
    MediaItemModel *m_mediaItemModel;
};

class PlaylistItemModel : public QAbstractListModel {
  Q_OBJECT
 public:
  enum PlaylistRoles {
    IdRole = Qt::UserRole + 1,
    NameRole,
    UserId,
    CreateTimeRole,
    UpdateTimeRole,
    CoverUrlRole,
    DescriptionRole,
    TagsRole,
    PlayCountRole,
    CreatorRole,
    SubscribersRole,
    SubscribedRole
  };

  Q_INVOKABLE PlaylistItem itemAt(quint32 index);
  Q_INVOKABLE PlaylistItem* last();

  PlaylistItemModel(QObject* parent = nullptr);
  int rowCount(const QModelIndex& parent) const;
  QVariant data(const QModelIndex& index, int role) const;
  QHash<int, QByteArray> roleNames() const;
  void appendItem(const PlaylistItem& item);
  void appendItems(const QVector<PlaylistItem>& items);
  void clear();
 private:
  QList<std::shared_ptr<PlaylistItem>> m_items;
};
}

Q_DECLARE_METATYPE(model::UserData);
#endif
