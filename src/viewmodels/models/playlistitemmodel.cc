#include "playlistitemmodel.h"

namespace viewmodel {

PlaylistItemModel::PlaylistItemModel(QObject* parent)
    : QAbstractListModel(parent) {}

int PlaylistItemModel::rowCount(const QModelIndex& parent) const {
  return parent.isValid() ? 0 : m_items.size();
}

QVariant PlaylistItemModel::data(const QModelIndex& index, int role) const {
  if (index.row() < 0 || index.row() >= m_items.size()) {
    return {};
  }
  const entities::PlaylistItem& item = m_items.at(index.row());
  switch (role) {
    case IdRole:
      return item.id();
    case NameRole:
      return item.name();
    case CoverUrlRole:
      return item.coverUrl();
    case PlayCountRole:
      return item.playCount();
    case DescriptionRole:
      return item.desc();
    case CreatorRole:
      return QVariant::fromValue(item.creator());
    case SubscribedCountRole:
      return item.subscribedCount();
    default:
      return {};
  }
}

QHash<int, QByteArray> PlaylistItemModel::roleNames() const {
  return {{IdRole, "id"},
          {NameRole, "name"},
          {CoverUrlRole, "coverUrl"},
          {PlayCountRole, "playCount"},
          {DescriptionRole, "description"},
          {CreatorRole, "creator"},
          {SubscribedCountRole, "subscribedCount"}};
}

void PlaylistItemModel::append(const QList<entities::PlaylistItem>& items) {
  if (items.isEmpty()) {
    return;
  }
  beginInsertRows(QModelIndex(), m_items.size(),
                  m_items.size() + items.size() - 1);
  m_items.append(items);
  endInsertRows();
  emit countChanged();
}

void PlaylistItemModel::clear() {
  if (m_items.isEmpty()) {
    return;
  }
  beginResetModel();
  m_items.clear();
  endResetModel();
  emit countChanged();
}

}
