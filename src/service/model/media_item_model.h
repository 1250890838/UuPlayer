#ifndef _MODEL_MEDIA_ITEM_MODEL_H
#define _MODEL_MEDIA_ITEM_MODEL_H
#include <qobject.h>
#include <QAbstractItemModel>
#include <QObject>
#include <QString>
#include <QUrl>

#include "entities/arist_data.h"
#include "entities/album_data.h"
#include "entities/media_item.h"
using namespace entities;

namespace model {

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
#endif
