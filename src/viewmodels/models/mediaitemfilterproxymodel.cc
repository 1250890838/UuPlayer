#include "mediaitemfilterproxymodel.h"

#include "mediaitemmodel.h"

namespace viewmodel {

MediaItemFilterProxyModel::MediaItemFilterProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent) {}

void MediaItemFilterProxyModel::setFilterString(const QString& str) {
  m_filterStr = str;
  invalidateFilter();
}

void MediaItemFilterProxyModel::sort(int column, Qt::SortOrder order) {
  QSortFilterProxyModel::sort(column, order);
}

bool MediaItemFilterProxyModel::lessThan(
    const QModelIndex& source_left, const QModelIndex& source_right) const {
  const int role = sortRole();
  if (role == MediaItemModel::AlbumRole) {
    const QVariant leftData = sourceModel()->data(source_left, role);
    const QVariant rightData = sourceModel()->data(source_right, role);
    if (leftData.canConvert<entities::AlbumData>() &&
        rightData.canConvert<entities::AlbumData>()) {
      return leftData.value<entities::AlbumData>().name() <
             rightData.value<entities::AlbumData>().name();
    }
  } else if (role == MediaItemModel::ArtistRole) {
    const QVariant leftData = sourceModel()->data(source_left, role);
    const QVariant rightData = sourceModel()->data(source_right, role);
    if (leftData.canConvert<QList<entities::AristItem>>() &&
        rightData.canConvert<QList<entities::AristItem>>()) {
      const auto left = leftData.value<QList<entities::AristItem>>();
      const auto right = rightData.value<QList<entities::AristItem>>();
      if (left.isEmpty()) {
        return true;
      }
      if (right.isEmpty()) {
        return false;
      }
      return left.first().name() < right.first().name();
    }
  }
  return QSortFilterProxyModel::lessThan(source_left, source_right);
}

bool MediaItemFilterProxyModel::filterAcceptsRow(
    int source_row, const QModelIndex& source_parent) const {
  if (m_filterStr.isEmpty()) {
    return true;
  }
  const QAbstractItemModel* model = sourceModel();
  const QModelIndex idx = model->index(source_row, 0, source_parent);

  const QString name = model->data(idx, MediaItemModel::NameRole).toString();
  if (name.contains(m_filterStr, Qt::CaseInsensitive)) {
    return true;
  }
  const QVariant albumVar = model->data(idx, MediaItemModel::AlbumRole);
  if (albumVar.canConvert<entities::AlbumData>()) {
    if (albumVar.value<entities::AlbumData>().name().contains(
            m_filterStr, Qt::CaseInsensitive)) {
      return true;
    }
  }
  const QVariant artistsVar = model->data(idx, MediaItemModel::ArtistRole);
  if (artistsVar.canConvert<QList<entities::AristItem>>()) {
    for (const auto& artist :
         artistsVar.value<QList<entities::AristItem>>()) {
      if (artist.name().contains(m_filterStr, Qt::CaseInsensitive)) {
        return true;
      }
    }
  }
  return false;
}

}  // namespace viewmodel