#ifndef _MODEL_MEDIA_ITEM_MODEL_H
#define _MODEL_MEDIA_ITEM_MODEL_H
#include <qobject.h>
#include <QAbstractItemModel>
#include <QObject>
#include <QString>
#include <QUrl>

#include "media_item.h"
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
  Q_PROPERTY(quint32 count READ count NOTIFY countChanged FINAL)
  Q_INVOKABLE MediaItem itemAt(qint32 index);
  Q_INVOKABLE quint32 count();

  MediaItemModel(QObject* parent = nullptr);
  void setExternalData(QList<MediaItem>* externalSource);
  bool isExternal() const { return m_externalSource != nullptr; }
  bool setData(const QModelIndex& index, const QVariant& value, int role);
  bool setDataForId(qulonglong id, const QVariant& value, int role);

  int rowCount(const QModelIndex& parent) const;
  QVariant data(const QModelIndex& index, int role) const;
  QHash<int, QByteArray> roleNames() const;
  void insertItem(MediaItem item, quint32 pos);
  void appendItem(MediaItem item);
  void appendItems(QVector<MediaItem>& items);
  void removeItem(qint32 pos);
  MediaItem last();
  void clear();
  QList<MediaItem>* currentData();
  const QList<MediaItem>* currentData() const;
  void itemsBeginArrived(const QModelIndex& parent, int first, int last);
  void itemsEndArrived();
  void itemsBeginRemoved(const QModelIndex& parent, int first, int last);
  void itemsEndRemoved();
  MediaItem getItemForId(qulonglong id);

 signals:
  void countChanged();
  void itemsChanged();

 private:
  QList<MediaItem> m_internalItems;
  QList<MediaItem>* m_externalSource;
  // QAbstractItemModel interface
};
}  // namespace model

Q_DECLARE_METATYPE(model::MediaItemModel);
Q_DECLARE_METATYPE(model::MediaItemModel*);
#endif
