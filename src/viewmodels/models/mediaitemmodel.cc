#include "mediaitemmodel.h"

#include <algorithm>

namespace viewmodel {

MediaItemModel::MediaItemModel(QObject* parent) : QAbstractListModel(parent) {}

int MediaItemModel::rowCount(const QModelIndex& parent) const {
  return parent.isValid() ? 0 : int(m_items.size());
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
      return QVariant::fromValue(item.albumdata);
    case ArtistRole:
      return QVariant::fromValue(item.artists);
    case ReasonRole:
      return item.reason;
    case UrlRole:
      return item.url;
    default:
      return {};
  }
}

QHash<int, QByteArray> MediaItemModel::roleNames() const {
  return {{IdRole, "id"},         {NameRole, "name"},
          {DurationRole, "duration"}, {AlbumRole, "album"},
          {ArtistRole, "artists"}, {ReasonRole, "reason"},
          {UrlRole, "url"}};
}

bool MediaItemModel::setData(const QModelIndex& index, const QVariant& value,
                             int role) {
  if (!index.isValid() || index.row() >= m_items.size()) {
    return false;
  }
  return setDataForId(m_items.at(index.row()).id, value, role);
}

entities::MediaItem MediaItemModel::itemAt(int index) const {
  if (index < 0 || index >= m_items.size()) {
    return {};
  }
  return m_items.at(index);
}

entities::MediaItem MediaItemModel::last() const {
  return m_items.isEmpty() ? entities::MediaItem() : m_items.last();
}

void MediaItemModel::insertItem(const entities::MediaItem& item, int pos) {
  if (pos < 0 || pos > m_items.size()) {
    return;
  }
  beginInsertRows(QModelIndex(), pos, pos);
  m_items.insert(pos, item);
  endInsertRows();
  emit countChanged();
}

void MediaItemModel::appendItem(const entities::MediaItem& item) {
  insertItem(item, int(m_items.size()));
}

void MediaItemModel::appendItems(const QList<entities::MediaItem>& items) {
  if (items.isEmpty()) {
    return;
  }
  beginInsertRows(QModelIndex(), int(m_items.size()),
                  int(m_items.size() + items.size() - 1));
  m_items.append(items);
  endInsertRows();
  emit countChanged();
}

void MediaItemModel::removeItem(int pos) {
  if (pos < 0 || pos >= m_items.size()) {
    return;
  }
  beginRemoveRows(QModelIndex(), pos, pos);
  m_items.removeAt(pos);
  endRemoveRows();
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

bool MediaItemModel::setDataForId(qulonglong id, const QVariant& value,
                                  int role) {
  auto it = std::find_if(m_items.begin(), m_items.end(),
                         [id](const entities::MediaItem& item) {
                           return item.id == id;
                         });
  if (it == m_items.end()) {
    return false;
  }
  switch (role) {
    case NameRole:
      it->name = value.toString();
      break;
    case DurationRole:
      it->duration = value.toULongLong();
      break;
    case AlbumRole:
      it->albumdata = value.value<entities::AlbumData>();
      break;
    case ArtistRole:
      it->artists = value.value<QList<entities::AristItem>>();
      break;
    case ReasonRole:
      it->reason = value.toString();
      break;
    case UrlRole:
      it->url = value.toUrl();
      break;
    default:
      return false;
  }
  const QModelIndex changed = index(int(it - m_items.begin()));
  emit dataChanged(changed, changed, {role});
  return true;
}

entities::MediaItem MediaItemModel::getItemForId(qulonglong id) const {
  for (const entities::MediaItem& item : m_items) {
    if (item.id == id) {
      return item;
    }
  }
  return {};
}

void MediaItemModel::setUrl(qulonglong id, const QUrl& url) {
  for (int row = 0; row < m_items.size(); ++row) {
    if (m_items[row].id == id) {
      m_items[row].url = url;
      const QModelIndex changed = index(row);
      emit dataChanged(changed, changed, {UrlRole});
      return;
    }
  }
}

}  // namespace viewmodel