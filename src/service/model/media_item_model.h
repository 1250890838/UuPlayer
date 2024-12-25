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
  qulonglong id;
  QString name;
  QString duration;
  AlbumData album;
  AristData artist;
  QString reason;
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
    ReasonRole
  };
  MediaItemModel(QObject* parent = nullptr);
  int rowCount(const QModelIndex& parent) const;
  QVariant data(const QModelIndex& index, int role) const;
  QHash<int, QByteArray> roleNames() const;

 private:
  QVector<MediaItem> m_items;
};
}  // namespace model
#endif