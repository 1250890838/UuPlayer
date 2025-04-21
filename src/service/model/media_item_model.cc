#include "media_item_model.h"
#include <qobject.h>
#include <qvariant.h>
namespace model {

MediaItemModel::MediaItemModel(QObject* parent) {}

int MediaItemModel::rowCount(const QModelIndex& parent) const {
  return m_items.size();
}

QVariant MediaItemModel::data(const QModelIndex& index, int role) const {
  if (index.row() < 0 || index.row() >= m_items.size()) {
    return QVariant();
  }
  MediaItem item = m_items[index.row()];
  switch (role) {
    case IdRole:
      return item.id;
    case NameRole:
      return item.name;
    case DurationRole:
      return item.duration;
    case AlbumRole:
      return QVariant::fromValue(item.album);
    case ArtistRole:
      return QVariant::fromValue(item.artists);
    case ReasonRole:
      return item.reason;
    default:
      return QVariant();
  }
}

QHash<int, QByteArray> MediaItemModel::roleNames() const {
  return {
      {IdRole, "id"},       {NameRole, "name"},      {DurationRole, "duration"},
      {AlbumRole, "album"}, {ArtistRole, "artists"}, {ReasonRole, "reason"}};
}

void MediaItemModel::appendItem(const MediaItem& item) {
  beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
  m_items.append(item);
  endInsertRows();
}

void MediaItemModel::appendItems(const QVector<MediaItem>& items) {
  beginInsertRows(QModelIndex(), m_items.size(),
                  m_items.size() + items.size() - 1);
  m_items.append(items);
  endInsertRows();
}

void MediaItemModel::clear() {
  beginResetModel();
  m_items.clear();
  endResetModel();
}

}  // namespace model
