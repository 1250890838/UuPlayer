#include "playlistitemmodel.h"

namespace viewmodel {

PlaylistItemModel::PlaylistItemModel(QObject* parent)
    : QAbstractListModel(parent) {}

int PlaylistItemModel::rowCount(const QModelIndex& parent) const {
  return parent.isValid() ? 0 : int(m_items.size());
}

QVariant PlaylistItemModel::data(const QModelIndex& index, int role) const {
  if (index.row() < 0 || index.row() >= m_items.size()) {
    return {};
  }
  const entities::PlaylistItem& item = m_items.at(index.row());
  switch (role) {
    case IdRole:
      return QVariant::fromValue(item.id());
    case NameRole:
      return item.name();
    case UserId:
      return item.userId();
    case CreateTimeRole:
      return item.createTime();
    case UpdateTimeRole:
      return item.updateTime();
    case CoverUrlRole:
      return item.coverUrl();
    case DescriptionRole:
      return item.desc();
    case TagsRole:
      return QVariant::fromValue(item.tags());
    case PlayCountRole:
      return item.playCount();
    case CreatorRole:
      return QVariant::fromValue(item.creator());
    case SubscribersRole: {
      QVariantList result;
      const auto users = item.subscribers();
      for (const auto& user : users) {
        result << QVariant::fromValue(user);
      }
      return result;
    }
    case SubscribedRole:
      return item.subscribed();
    case TracksRole:
      return QVariant::fromValue(item.mediaItems());
    default:
      return {};
  }
}

QHash<int, QByteArray> PlaylistItemModel::roleNames() const {
  return {{IdRole, "id"},
          {NameRole, "name"},
          {UserId, "userId"},
          {CreateTimeRole, "createTime"},
          {UpdateTimeRole, "updateTime"},
          {CoverUrlRole, "coverUrl"},
          {DescriptionRole, "description"},
          {TagsRole, "tags"},
          {PlayCountRole, "playCount"},
          {CreatorRole, "creator"},
          {SubscribersRole, "subscribers"},
          {SubscribedRole, "subscribed"},
          {TracksRole, "tracks"}};
}

entities::PlaylistItem PlaylistItemModel::itemAt(quint32 index) const {
  if (index >= quint32(m_items.size())) {
    return {};
  }
  return m_items.at(int(index));
}

entities::PlaylistItem PlaylistItemModel::last() const {
  return m_items.isEmpty() ? entities::PlaylistItem() : m_items.last();
}

void PlaylistItemModel::appendItem(const entities::PlaylistItem& item) {
  appendItems({item});
}

void PlaylistItemModel::appendItems(
    const QList<entities::PlaylistItem>& items) {
  if (items.isEmpty()) {
    return;
  }
  beginInsertRows(QModelIndex(), int(m_items.size()),
                  int(m_items.size() + items.size() - 1));
  m_items.append(items);
  endInsertRows();
}

void PlaylistItemModel::clear() {
  if (m_items.isEmpty()) {
    return;
  }
  beginResetModel();
  m_items.clear();
  endResetModel();
}

}  // namespace viewmodel