#ifndef COMMENT_ITEM_MODEL_H
#define COMMENT_ITEM_MODEL_H

#include <QAbstractListModel>

#include "comment_item.h"

namespace model {

using namespace entities;
class CommentItemModel : public QAbstractListModel {
  Q_OBJECT
  enum CommentRole {
    IdRole = Qt::UserRole + 1,
    UserRole,
    PendantRole,
    TimeRole,
    ContentRole,
    LikeedCountRole
  };
 public:
  explicit CommentItemModel(QObject* parent = nullptr);

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  // Basic functionality:
  int rowCount(const QModelIndex& parent = QModelIndex()) const override;

  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;
  void appendItem(const CommentItem& data);
 private:
  QList<CommentItem> m_data;
};
}  // namespace model
#endif  // COMMENT_ITEM_MODEL_H
