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
  Q_GADGET
  Q_PROPERTY(qulonglong id MEMBER id)
  Q_PROPERTY(QString name MEMBER name)
  Q_PROPERTY(qulonglong duration MEMBER duration)
  Q_PROPERTY(AlbumData album READ album WRITE setAlbum)
  Q_PROPERTY(QVariantList artists MEMBER artists)
  Q_PROPERTY(QString reason MEMBER reason)
  Q_PROPERTY(QUrl url MEMBER url)
 public:
  AlbumData album() { return albumdata; }
  void setAlbum(const AlbumData& data) { albumdata = data; }
 public:
  qulonglong id;
  QString name;
  qulonglong duration;
  AlbumData albumdata;
  QVariantList artists; // QList<AristData> artists
  QString reason;
  QUrl url;
};

class MediaItemModel : public QAbstractListModel {
  Q_OBJECT  
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
  Q_PROPERTY(quint32 count READ count NOTIFY countChanged)

  Q_INVOKABLE MediaItem itemAt(qint32 index);
  Q_INVOKABLE quint32 count();

  MediaItemModel(QObject* parent = nullptr);
  int rowCount(const QModelIndex& parent) const;
  QVariant data(const QModelIndex& index, int role) const;
  QHash<int, QByteArray> roleNames() const;
  void insertItem(MediaItem* item,quint32 pos);
  void appendItem(MediaItem* item);
  void appendItems(QVector<MediaItem*>& items);
  void removeItem(qint32 pos);
  MediaItem* last();
  void clear();
  QList<MediaItem*>& rawData();
 signals:
  void countChanged();
 private:
  QList<MediaItem*> m_items;
};
}  // namespace model

Q_DECLARE_METATYPE(model::MediaItemModel);
Q_DECLARE_METATYPE(model::MediaItemModel*);
Q_DECLARE_METATYPE(model::AlbumData);
#endif
