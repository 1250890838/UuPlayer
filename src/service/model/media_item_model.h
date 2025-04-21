#ifndef _MODEL_MEDIA_ITEM_MODEL_H
#define _MODEL_MEDIA_ITEM_MODEL_H
#include <qobject.h>
#include <QAbstractItemModel>
#include <QObject>
#include <QString>
#include <QUrl>

namespace model {
class AlbumData {
  Q_GADGET
  Q_PROPERTY(qulonglong id READ id WRITE setId)
  Q_PROPERTY(QString name READ name WRITE setName)
  Q_PROPERTY(QUrl picUrl READ picUrl WRITE setPicUrl)
 public:
  AlbumData() = default;
  AlbumData(qulonglong id, const QString& name, const QUrl& picUrl);
  ~AlbumData() = default;
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }
  QUrl picUrl() const { return m_picUrl; }
  void setPicUrl(const QUrl& picUrl) { m_picUrl = picUrl; }

 private:
  qulonglong m_id;
  QString m_name;
  QUrl m_picUrl;
};

class AristData {
  Q_GADGET
  Q_PROPERTY(qulonglong id READ id WRITE setId)
  Q_PROPERTY(QString name READ name WRITE setName)
 public:
  AristData() = default;
  ~AristData() = default;
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }

 private:
  qulonglong m_id;
  QString m_name;
};

struct MediaItem {
  /*
  Q_GADGET
  Q_PROPERTY(qulonglong id MEMBER id)
  Q_PROPERTY(QString name MEMBER name)
  Q_PROPERTY(qulonglong duration MEMBER duration)
  Q_PROPERTY(AlbumData album MEMBER album)
  Q_PROPERTY(QVariantList artists MEMBER artists)
  Q_PROPERTY(QString reason MEMBER reason)
  Q_PROPERTY(QUrl url MEMBER url)

 public:
*/
  qulonglong id;
  QString name;
  qulonglong duration;
  AlbumData album;
  QVariantList artists; // QList<AristData> artists
  QString reason;
  QUrl url;
};

class MediaItemModel : public QAbstractListModel {
  Q_OBJECT

 public:
  Q_INVOKABLE MediaItem getMediaItem(qulonglong id);
  Q_INVOKABLE MediaItem* getMediaItemPtr(qulonglong id);

 public:
  enum MediaRoles {
    IdRole = Qt::UserRole + 1,
    NameRole,
    DurationRole,
    AlbumRole,
    ArtistRole,
    ReasonRole,
    UrlRole
  };
  MediaItemModel(QObject* parent = nullptr);
  int rowCount(const QModelIndex& parent) const;
  QVariant data(const QModelIndex& index, int role) const;
  QHash<int, QByteArray> roleNames() const;
  void appendItem(const MediaItem& item);
  void appendItems(const QVector<MediaItem>& items);
  void clear();

 private:
  QVector<MediaItem> m_items;
};
}  // namespace model

Q_DECLARE_METATYPE(model::AlbumData);

#endif
