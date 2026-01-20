#ifndef LOCAL_MEDIA_ITEM_MODEL_H
#define LOCAL_MEDIA_ITEM_MODEL_H

#include <QAbstractListModel>
#include "local_media_item.h"

namespace  model {
class LocalMediaItemModel : public QAbstractListModel {
  Q_OBJECT
 public:
  enum MediaRoles {
    IdRole = Qt::UserRole + 1,
    NameRole,
    DurationRole,
    AlbumRole,
    ArtistRole,
    PathRole,
    FileSizeRole
  };
  explicit LocalMediaItemModel(QObject* parent = nullptr);

  // Basic functionality:
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;

  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  void appendItem(const entities::LocalMediaItem& item);
  void clear();
  // Add data:
  bool insertRows(int row, int count,
                  const QModelIndex& parent = QModelIndex()) override;
  // Remove data:
  bool removeRows(int row, int count,
                  const QModelIndex& parent = QModelIndex()) override;

 public:
  QHash<int, QByteArray> roleNames() const override;
 private:
  QList<entities::LocalMediaItem> m_items;
};
}
#endif  // LOCAL_MEDIA_ITEM_MODEL_H
