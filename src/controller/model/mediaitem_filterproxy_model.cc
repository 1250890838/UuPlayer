#include "mediaitem_filterproxy_model.h"

#include "media_item_model.h"
namespace model{

MediaItemFilterProxyModel::MediaItemFilterProxyModel() {}
// QTC_TEMP
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

}
