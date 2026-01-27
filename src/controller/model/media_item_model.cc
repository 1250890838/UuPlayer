#include "media_item_model.h"
#include <qobject.h>
#include <qvariant.h>
#include <algorithm>

namespace model {

MediaItem MediaItemModel::itemAt(qint32 index) {
  return m_items[index];
}

quint32 MediaItemModel::count() {
  return m_items.size();
}

MediaItemModel::MediaItemModel(QObject* parent) {}

int MediaItemModel::rowCount(const QModelIndex& parent) const {
  return m_items.size();
}

QVariant MediaItemModel::data(const QModelIndex& index, int role) const {
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
      return QVariant::fromValue(item.albumdata);
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

void MediaItemModel::appendItem(MediaItem item) {
  beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
  m_items.append(item);
  endInsertRows();
  emit countChanged();
}

void MediaItemModel::insertItem(MediaItem item, quint32 pos) {
  beginInsertRows(QModelIndex(), pos, pos);
  m_items.insert(pos, item);
  endInsertRows();
}

void MediaItemModel::appendItems(QVector<MediaItem>& items) {
  beginInsertRows(QModelIndex(), m_items.size(),
                  m_items.size() + items.size() - 1);
  for (const auto& item : items) {
    m_items.append(item);
  }
  endInsertRows();
}

void MediaItemModel::removeItem(qint32 pos) {
  beginRemoveRows(QModelIndex(), pos, pos);
  m_items.remove(pos);
  endRemoveRows();
}

MediaItem MediaItemModel::last() {
  if (m_items.size() != 0) {
    return m_items[m_items.size() - 1];
  }
  return {};
}

void MediaItemModel::clear() {
  beginResetModel();
  m_items.clear();
  endResetModel();
}

QList<MediaItem>& MediaItemModel::rawData() {
  return m_items;
}

}  // namespace model

bool model::MediaItemModel::setData(const QModelIndex& index,
                                    const QVariant& value, int role) {
  if (!index.isValid())
    return false;
  auto i = index.row();
  if (m_items.size() <= i)
    return false;
  MediaRoles r = static_cast<MediaRoles>(role);
  if (r > UrlRole || r < NameRole)
    return false;
  auto typeId = value.typeId();
  switch (r) {
    case NameRole:
      if (typeId == QMetaType::QString)
        m_items[i].name = value.toString();
      else
        return false;
      break;
    case DurationRole:
      if (typeId == QMetaType::ULongLong)
        m_items[i].duration = value.toULongLong();
      else
        return false;
      break;
    case AlbumRole:
      if (typeId == qMetaTypeId<AlbumData>())
        m_items[i].albumdata = value.value<AlbumData>();
      else
        return false;
      break;
    case ArtistRole:
      if (typeId == qMetaTypeId<QList<AristItem>>())
        m_items[i].artists = value.value<QList<AristItem>>();
      else
        return false;
      break;
    case ReasonRole:
      if (typeId == QMetaType::QString)
        m_items[i].reason = value.toString();
      else
        return false;
      break;
    case UrlRole:
      if (typeId == QMetaType::QUrl)
        m_items[i].url = value.toUrl();
      else
        return false;
      break;
    default:
      return false;
  }
  emit dataChanged(index, index, {role});
  return true;
}

bool model::MediaItemModel::setDataForId(qulonglong id, const QVariant& value,
                                         int role) {

  auto item =
      std::find_if(m_items.begin(), m_items.end(),
                   [id](const MediaItem& item) { return item.id == id; });

  if (item == m_items.end())
    return false;
  MediaRoles r = static_cast<MediaRoles>(role);
  if (r > UrlRole || r < NameRole)
    return false;
  auto typeId = value.typeId();
  switch (r) {
    case NameRole:
      if (typeId == QMetaType::QString)
        item->name = value.toString();
      else
        return false;
      break;
    case DurationRole:
      if (typeId == QMetaType::ULongLong)
        item->duration = value.toULongLong();
      else
        return false;
      break;
    case AlbumRole:
      if (typeId == qMetaTypeId<AlbumData>())
        item->albumdata = value.value<AlbumData>();
      else
        return false;
      break;
    case ArtistRole:
      if (typeId == qMetaTypeId<QList<AristItem>>())
        item->artists = value.value<QList<AristItem>>();
      else
        return false;
      break;
    case ReasonRole:
      if (typeId == QMetaType::QString)
        item->reason = value.toString();
      else
        return false;
      break;
    case UrlRole:
      if (typeId == QMetaType::QUrl)
        item->url = value.toUrl();
      else
        return false;
      break;
    default:
      return false;
  }
  return true;
}
