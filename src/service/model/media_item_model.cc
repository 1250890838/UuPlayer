#include "media_item_model.h"
#include <qobject.h>
#include <qvariant.h>
namespace model {

MediaItem MediaItemModel::itemAt(qint32 index) {
  return *m_items[index];
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
      return item->id;
    case NameRole:
      return item->name;
    case DurationRole:
      return item->duration;
    case AlbumRole:
      return QVariant::fromValue(item->albumdata);
    case ArtistRole:
      return QVariant::fromValue(item->artists);
    case ReasonRole:
      return item->reason;
    default:
      return QVariant();
  }
}

QHash<int, QByteArray> MediaItemModel::roleNames() const {
  return {
      {IdRole, "id"},       {NameRole, "name"},      {DurationRole, "duration"},
      {AlbumRole, "album"}, {ArtistRole, "artists"}, {ReasonRole, "reason"}};
}

void MediaItemModel::appendItem(MediaItem* item) {
  beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
  m_items.append(item);
  endInsertRows();
  emit countChanged();
}

void MediaItemModel::insertItem(MediaItem* item, quint32 pos) {
  beginInsertRows(QModelIndex(), pos, pos);
  m_items.insert(pos, item);
  endInsertRows();
}

void MediaItemModel::appendItems(QVector<MediaItem*>& items) {
  beginInsertRows(QModelIndex(), m_items.size(),
                  m_items.size() + items.size() - 1);
  for (auto& item : items) {
    m_items.append(item);
  }
  endInsertRows();
}

void MediaItemModel::removeItem(qint32 pos) {
  beginRemoveRows(QModelIndex(), pos, pos);
  m_items.remove(pos);
  endRemoveRows();
}

MediaItem* MediaItemModel::last() {
  if (m_items.size() != 0) {
    return const_cast<MediaItem*>(m_items[m_items.size() - 1]);
  }
  return nullptr;
}

void MediaItemModel::clear() {
  beginResetModel();
  m_items.clear();
  endResetModel();
}

QList<MediaItem*>& MediaItemModel::rawData() {
  return m_items;
}

MediaItem::MediaItem():id(0),name(),duration(0),albumdata(),artists(),reason(),url(),lyrics()
{

}

MediaItem& MediaItem::operator=(const MediaItem& other) {
  this->id = other.id;
  this->name = other.name;
  this->duration = other.duration;
  this->albumdata = other.albumdata;
  this->artists = other.artists;
  this->reason = other.reason;
  this->url = other.url;
  this->lyrics = other.lyrics;
  return *this;
}

}  // namespace model
