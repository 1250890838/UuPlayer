#include "mediaitemmodel.h"

namespace viewmodel {

MediaItemModel::MediaItemModel(QObject* parent) : QAbstractListModel(parent) {}

int MediaItemModel::rowCount(const QModelIndex& parent) const {
  return parent.isValid() ? 0 : m_items.size();
}

QVariant MediaItemModel::data(const QModelIndex& index, int role) const {
  if (index.row() < 0 || index.row() >= m_items.size()) {
    return {};
  }
  const entities::MediaItem& item = m_items.at(index.row());
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
    case UrlRole:
      return item.url;
    default:
      return {};
  }
}

QHash<int, QByteArray> MediaItemModel::roleNames() const {
  return {{IdRole, "id"},         {NameRole, "name"},
          {DurationRole, "duration"}, {AlbumRole, "album"},
          {ArtistRole, "artists"}, {UrlRole, "url"}};
}

entities::MediaItem MediaItemModel::itemAt(int row) const {
  return item(row);
}

entities::MediaItem MediaItemModel::item(int row) const {
  if (row < 0 || row >= m_items.size()) {
    return {};
  }
  return m_items.at(row);
}

void MediaItemModel::append(const entities::MediaItem& item) {
  append(QList<entities::MediaItem>{item});
}

void MediaItemModel::append(const QList<entities::MediaItem>& items) {
  if (items.isEmpty()) {
    return;
  }
  beginInsertRows(QModelIndex(), m_items.size(),
                  m_items.size() + items.size() - 1);
  m_items.append(items);
  endInsertRows();
  emit countChanged();
}

void MediaItemModel::clear() {
  if (m_items.isEmpty()) {
    return;
  }
  beginResetModel();
  m_items.clear();
  endResetModel();
  emit countChanged();
}

bool MediaItemModel::containsId(qulonglong id) const {
  return indexOfId(id) >= 0;
}

int MediaItemModel::indexOfId(qulonglong id) const {
  for (int row = 0; row < m_items.size(); ++row) {
    if (m_items.at(row).id == id) {
      return row;
    }
  }
  return -1;
}

void MediaItemModel::setUrl(qulonglong id, const QUrl& url) {
  const int row = indexOfId(id);
  if (row < 0) {
    return;
  }
  m_items[row].url = url;
  const QModelIndex changed = index(row);
  emit dataChanged(changed, changed, {UrlRole});
}

}
