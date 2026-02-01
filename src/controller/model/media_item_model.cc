#include "media_item_model.h"
#include <qobject.h>
#include <qvariant.h>
#include <algorithm>

namespace model {

MediaItem MediaItemModel::itemAt(qint32 index) {
  auto items = currentData();
  return (*items)[index];
}

quint32 MediaItemModel::count() {
  auto items = currentData();
  return items->size();
}

MediaItemModel::MediaItemModel(QObject* parent) : m_externalSource(nullptr) {}

void MediaItemModel::setExternalData(QList<MediaItem>* externalSource) {
  beginResetModel();
  m_externalSource = externalSource;
  endResetModel();
  emit countChanged();
}

int MediaItemModel::rowCount(const QModelIndex& parent) const {
  auto items = currentData();
  return items->size();
}

QVariant MediaItemModel::data(const QModelIndex& index, int role) const {
  auto items = currentData();
  if (index.row() < 0 || index.row() >= items->size()) {
    return QVariant();
  }
  auto item = (*items)[index.row()];
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
  auto items = currentData();
  beginInsertRows(QModelIndex(), items->size(), items->size());
  items->append(item);
  endInsertRows();
  emit countChanged();
}

void MediaItemModel::insertItem(MediaItem item, quint32 pos) {
  auto items = currentData();
  beginInsertRows(QModelIndex(), pos, pos);
  items->insert(pos, item);
  endInsertRows();
}

void MediaItemModel::appendItems(QVector<MediaItem>& items) {
  auto data = currentData();
  beginInsertRows(QModelIndex(), data->size(), data->size() + items.size() - 1);
  for (const auto& item : items) {
    data->append(item);
  }
  endInsertRows();
}

void MediaItemModel::removeItem(qint32 pos) {
  auto items = currentData();
  beginRemoveRows(QModelIndex(), pos, pos);
  items->remove(pos);
  endRemoveRows();
}

MediaItem MediaItemModel::last() {
  auto items = currentData();
  if (items->size() != 0) {
    return (*items)[items->size() - 1];
  }
  return {};
}

void MediaItemModel::clear() {
  auto items = currentData();
  beginResetModel();
  items->clear();
  endResetModel();
}

void MediaItemModel::itemsBeginArrived(const QModelIndex& parent, int first,
                                       int last) {
  beginInsertRows(parent, first, last);
}

void MediaItemModel::itemsEndArrived() {
  endInsertRows();
}

void MediaItemModel::itemsBeginRemoved(const QModelIndex& parent, int first,
                                       int last) {
  beginRemoveRows(parent, first, last);
}

void MediaItemModel::itemsEndRemoved() {
  endRemoveRows();
}

MediaItem MediaItemModel::getItemForId(qulonglong id) {
  auto items = currentData();
  for (const auto& item : *items) {
    if (item.id == id)
      return item;
  }
  return {};
}

QList<MediaItem>* MediaItemModel::currentData() {
  return m_externalSource ? m_externalSource : &m_internalItems;
}

const QList<MediaItem>* MediaItemModel::currentData() const {
  return m_externalSource ? m_externalSource : &m_internalItems;
}

}  // namespace model

bool model::MediaItemModel::setData(const QModelIndex& index,
                                    const QVariant& value, int role) {
  auto items = currentData();
  if (!index.isValid())
    return false;
  auto i = index.row();
  if (items->size() <= i)
    return false;
  MediaRoles r = static_cast<MediaRoles>(role);
  if (r > UrlRole || r < NameRole)
    return false;
  auto typeId = value.typeId();
  switch (r) {
    case NameRole:
      if (typeId == QMetaType::QString)
        (*items)[i].name = value.toString();
      else
        return false;
      break;
    case DurationRole:
      if (typeId == QMetaType::ULongLong)
        (*items)[i].duration = value.toULongLong();
      else
        return false;
      break;
    case AlbumRole:
      if (typeId == qMetaTypeId<AlbumData>())
        (*items)[i].albumdata = value.value<AlbumData>();
      else
        return false;
      break;
    case ArtistRole:
      if (typeId == qMetaTypeId<QList<AristItem>>())
        (*items)[i].artists = value.value<QList<AristItem>>();
      else
        return false;
      break;
    case ReasonRole:
      if (typeId == QMetaType::QString)
        (*items)[i].reason = value.toString();
      else
        return false;
      break;
    case UrlRole:
      if (typeId == QMetaType::QUrl)
        (*items)[i].url = value.toUrl();
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
  auto items = currentData();
  auto item =
      std::find_if(items->begin(), items->end(),
                   [id](const MediaItem& item) { return item.id == id; });

  if (item == items->end())
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
