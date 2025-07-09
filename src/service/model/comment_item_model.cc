#include "comment_item_model.h"

namespace model {

CommentItemModel::CommentItemModel(QObject* parent)
    : QAbstractListModel(parent) {}

QVariant CommentItemModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const {
  // FIXME: Implement me!
  return QVariant();
}

QHash<int, QByteArray> CommentItemModel::roleNames() const {
  return {{IdRole, "id"},           {UserRole, "user"},
          {PendantRole, "pendant"}, {TimeRole, "time"},
          {ContentRole, "content"}, {LikeedCountRole, "likedCount"}};
}

int CommentItemModel::rowCount(const QModelIndex& parent) const {
  // For list models only the root node (an invalid parent) should return the list's size. For all
  // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
  if (parent.isValid())
    return 0;
  return m_data.count();
}

QVariant CommentItemModel::data(const QModelIndex& index, int role) const {
  if (!index.isValid())
    return QVariant();
  if (index.row() < 0 || index.row() >= m_data.size()) {
    return QVariant();
  }
  CommentRole frole = static_cast<CommentRole>(role);
  const CommentData& comment = m_data.at(index.row());
  switch (frole) {
    case IdRole:
      // For IdRole, you can return the index or an actual unique ID if you have one
      return QVariant(
          index
              .row());  // Placeholder for ID (replace with actual ID if available)

    case UserRole:
      return QVariant::fromValue(
          comment.userData());  // Assuming `userData` is a complex object

    case PendantRole:
      return QVariant::fromValue(
          comment.pendant());  // Assuming `pendant` is a complex object

    case TimeRole:
      return QVariant::fromValue(comment.time());  // Time as qulonglong

    case ContentRole:
      return comment.content();  // The actual content of the comment

    case LikeedCountRole:
      return QVariant(comment.likedCount());  // Number of likes

    default:
      return QVariant();  // Return invalid QVariant for unknown roles
  }
}
}  // namespace model
