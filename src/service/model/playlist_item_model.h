#ifndef _MODEL_PLAYLIST_ITEM_MODEL_H
#define _MODEL_PLAYLIST_ITEM_MODEL_H

#include <qglobal.h>
#include <qtmetamacros.h>
#include <QAbstractListModel>
#include <QObject>
#include <QUrl>

namespace model{

class UserData {
  Q_GADGET
  Q_PROPERTY(qulonglong id READ id WRITE setId)
  Q_PROPERTY(QUrl avatarUrl READ avatarUrl WRITE setAvatarUrl)
  Q_PROPERTY(QUrl backgroundUrl READ backgroundUrl WRITE setBackgroundUrl)
  Q_PROPERTY(QStringList expertTags READ expertTags WRITE setExpertTags)
  Q_PROPERTY(qulonglong birthday READ birthday WRITE setBirthday)
  Q_PROPERTY(bool followed READ followed WRITE setFollowed)

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


struct PlaylistItem {
    qulonglong id;
    QString name;
    qulonglong userId;
    qulonglong createTime;
    qulonglong updateTime;
    QUrl coverUrl;
    QString description;
    QStringList tags;
    qulonglong playCount;
    UserData creator;
    QVector<UserData> subscribers;
    bool subscribed;
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
    SubscribedRole,
  };
  PlaylistItemModel(QObject* parent = nullptr);
  int rowCount(const QModelIndex& parent) const;
  QVariant data(const QModelIndex& index, int role) const;
  QHash<int, QByteArray> roleNames() const;
  void appendItem(const PlaylistItem& item);
  void appendItems(const QVector<PlaylistItem>& items);

 private:
  QVector<PlaylistItem> m_items;
};
}

Q_DECLARE_METATYPE(model::UserData);
#endif