#include "playlist_item_model.h"
#include <qabstractitemmodel.h>
#include <qglobal.h>
#include <qvariant.h>

namespace model {

PlaylistItemModel::PlaylistItemModel(QObject* parent)
    : QAbstractListModel(parent) {}

int PlaylistItemModel::rowCount(const QModelIndex& parent) const {
  return m_items.count();
}

QVariant PlaylistItemModel::data(const QModelIndex& index, int role) const {
  PlaylistRoles prole = static_cast<PlaylistRoles>(role);
  switch (prole) {
    case IdRole:
      return QVariant::fromValue(m_items[index.row()]->id());
    case NameRole:
      return m_items[index.row()]->name();
    case UserId:
      return m_items[index.row()]->userId();
    case CreateTimeRole:
      return m_items[index.row()]->createTime();
    case UpdateTimeRole:
      return m_items[index.row()]->updateTime();
    case CoverUrlRole:
      return m_items[index.row()]->coverUrl();
    case DescriptionRole:
      return m_items[index.row()]->desc();
    case TagsRole:
      return QVariant::fromValue(m_items[index.row()]->tags());
    case PlayCountRole:
      return m_items[index.row()]->playCount();
    case CreatorRole:
      return QVariant::fromValue(m_items[index.row()]->creator());
    case SubscribersRole: {
      QVariantList result;
      auto users = m_items[index.row()]->subscribers();
      for (const auto& user : users) {
        result << QVariant::fromValue(user);
      }
      return result;
    }
    case SubscribedRole:
      return m_items[index.row()]->subscribed();
    default:
      break;
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
          {SubscribedRole, "subscribed"}};
}

void PlaylistItemModel::appendItem(const PlaylistItem& item) {
  beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
  m_items.emplace_back(std::make_shared<PlaylistItem>(item));
  endInsertRows();
}

void PlaylistItemModel::appendItems(const QVector<PlaylistItem>& items) {
  beginInsertRows(QModelIndex(), m_items.size(),
                  m_items.size() + items.size() - 1);
  for (auto& item : items) {
    m_items.append(std::make_shared<PlaylistItem>(item));
  }
  endInsertRows();
}

void PlaylistItemModel::clear() {
  beginResetModel();
  m_items.clear();
  endResetModel();
}

PlaylistItem* PlaylistItemModel::last() {
  return m_items.last().get();
}

PlaylistItem PlaylistItemModel::itemAt(quint32 index) {
  return *(m_items[index]);
}

}  // namespace model
