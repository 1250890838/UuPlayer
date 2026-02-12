#include "mediaitem_filterproxy_model.h"

#include "media_item_model.h"
namespace model {

void MediaItemFilterProxyModel::setFilterString(const QString& str) {
  m_filterStr = str;
  invalidateFilter();
}

MediaItemFilterProxyModel::MediaItemFilterProxyModel() {}

bool MediaItemFilterProxyModel::lessThan(
    const QModelIndex& source_left, const QModelIndex& source_right) const {
  int role = sortRole();
  if (role == MediaItemModel::AlbumRole) {
    QVariant leftData = sourceModel()->data(source_left, role);
    QVariant rightData = sourceModel()->data(source_right, role);
    if (leftData.canConvert<AlbumData>() && rightData.canConvert<AlbumData>()) {
      AlbumData left = leftData.value<AlbumData>();
      AlbumData right = rightData.value<AlbumData>();
      return left.name() < right.name();
    }
  } else if (role == MediaItemModel::ArtistRole) {
    QVariant leftData = sourceModel()->data(source_left, role);
    QVariant rightData = sourceModel()->data(source_right, role);
    if (leftData.canConvert<QList<AristItem>>() &&
        rightData.canConvert<QList<AristItem>>()) {
      QList<AristItem> left = leftData.value<QList<AristItem>>();
      QList<AristItem> right = rightData.value<QList<AristItem>>();
      if (left.empty())
        return true;
      else if (right.empty())
        return false;
      else
        return left[0].name() < right[0].name();
    }
  }
  return QSortFilterProxyModel::lessThan(source_left, source_right);
}

void MediaItemFilterProxyModel::sort(int column, Qt::SortOrder order) {
  return QSortFilterProxyModel::sort(column, order);
}

bool MediaItemFilterProxyModel::filterAcceptsRow(
    int source_row, const QModelIndex& source_parent) const {
  if (m_filterStr.isEmpty())
    return true;
  auto model = sourceModel();
  QModelIndex idx = model->index(source_row, 0, source_parent);
  auto name = model->data(idx, MediaItemModel::NameRole).toString();
  if (name.contains(m_filterStr, Qt::CaseInsensitive))
    return true;
  auto albumVar = model->data(idx, MediaItemModel::AlbumRole);
  if (albumVar.canConvert<AlbumData>()) {
    auto albumData = albumVar.value<AlbumData>();
    if (albumData.name().contains(m_filterStr, Qt::CaseInsensitive))
      return true;
  }
  auto artistsVar = model->data(idx, MediaItemModel::ArtistRole);
  if (artistsVar.canConvert<QList<AristItem>>()) {
    auto artistData = artistsVar.value<QList<AristItem>>();
    for (const auto& artist : artistData) {
      if (artist.name().contains(m_filterStr, Qt::CaseInsensitive))
        return true;
    }
  }
  return false;
}
// void MediaItemFilterProxyModel::sortByArtistName(Qt::SortOrder order)
// {
//   QHash<int,QByteArray> roleNames = sourceModel()->roleNames();
//   int role = roleNames.key("artists");
//   this->setSortRole(role);
//   this->sort(0,order);
// }

// void MediaItemFilterProxyModel::sortByTitle(Qt::SortOrder order)
// {
//   QHash<int,QByteArray> roleNames = sourceModel()->roleNames();
//   int role = roleNames.key("name");
//   this->setSortRole(role);
//   this->sort(0,order);
// }

// void MediaItemFilterProxyModel::sortByDuration(Qt::SortOrder order)
// {
//   QHash<int,QByteArray> roleNames = sourceModel()->roleNames();
//   int role = roleNames.key("duration");
//   this->setSortRole(role);
//   this->sort(0,order);
// }

// void MediaItemFilterProxyModel::sortByFileSize(Qt::SortOrder order)
// {
//   //TODO:
// }

// void MediaItemFilterProxyModel::sortByAlbumName(Qt::SortOrder order)
// {
//   QHash<int,QByteArray> roleNames = sourceModel()->roleNames();
//   int role = roleNames.key("album");
//   this->setSortRole(role);
//   this->sort(0,order);
// }

}  // namespace model
