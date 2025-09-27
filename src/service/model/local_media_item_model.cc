#include "local_media_item_model.h"
namespace model {
LocalMediaItemModel::LocalMediaItemModel(QObject* parent)
    : QAbstractListModel(parent) {}

int LocalMediaItemModel::rowCount(const QModelIndex& parent) const {
  // For list models only the root node (an invalid parent) should return the list's size. For all
  // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
  if (parent.isValid())
    return 0;
  return m_items.size();
  // FIXME: Implement me!
}

QVariant LocalMediaItemModel::data(const QModelIndex& index, int role) const {
  if (index.row() < 0 || index.row() >= m_items.size()) {
    return QVariant();
  }
  auto item = m_items[index.row()];
  switch (role) {
    case IdRole:
      return item.id;
    case NameRole:
      return item.name;
    case DurationRole:
      return item.duration;
    case AlbumRole:
      return item.albumName;
    case ArtistRole:
      return QVariant::fromValue(item.artists);
    case PathRole:
      return item.dirPath;
    case FileSizeRole:
      return item.fileSize;
    default:
      return QVariant();
  }
}

bool LocalMediaItemModel::insertRows(int row, int count,
                                     const QModelIndex& parent) {
  beginInsertRows(parent, row, row + count - 1);

  endInsertRows();
  return true;
}

bool LocalMediaItemModel::removeRows(int row, int count,
                                     const QModelIndex& parent) {
  beginRemoveRows(parent, row, row + count - 1);
  // FIXME: Implement me!
  endRemoveRows();
  return true;
}

QHash<int, QByteArray> LocalMediaItemModel::roleNames() const {
  return {{IdRole, "id"},
          {NameRole, "name"},
          {DurationRole, "duration"},
          {AlbumRole, "album"},
          {ArtistRole, "artists"},
          {PathRole, "path"},
          {FileSizeRole, "fileSize"}

  };
}
}  // namespace model
