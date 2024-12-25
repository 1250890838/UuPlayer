#include "playlist_item_model.h"

namespace model {

PlaylistItemModel::PlaylistItemModel(QObject* parent): QAbstractListModel(parent) {

}

int rowCount(const QModelIndex& parent) const;
QVariant data(const QModelIndex& index, int role) const;
QHash<int, QByteArray> roleNames() const;
}  // namespace model