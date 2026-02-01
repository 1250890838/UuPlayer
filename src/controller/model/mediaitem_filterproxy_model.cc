#include "mediaitem_filterproxy_model.h"

namespace model{

MediaItemFilterProxyModel::MediaItemFilterProxyModel()
{

}
void MediaItemFilterProxyModel::sortByArtistName(Qt::SortOrder order)
{
  QHash<int,QByteArray> roleNames = sourceModel()->roleNames();
  int role = roleNames.key("artists");
  this->setSortRole(role);
  this->sort(0,order);
}

void MediaItemFilterProxyModel::sortByTitle(Qt::SortOrder order)
{
  QHash<int,QByteArray> roleNames = sourceModel()->roleNames();
  int role = roleNames.key("name");
  this->setSortRole(role);
  this->sort(0,order);
}

void MediaItemFilterProxyModel::sortByDuration(Qt::SortOrder order)
{
  QHash<int,QByteArray> roleNames = sourceModel()->roleNames();
  int role = roleNames.key("duration");
  this->setSortRole(role);
  this->sort(0,order);
}

void MediaItemFilterProxyModel::sortByFileSize(Qt::SortOrder order)
{
  //TODO:
}

void MediaItemFilterProxyModel::sortByAlbumName(Qt::SortOrder order)
{
  QHash<int,QByteArray> roleNames = sourceModel()->roleNames();
  int role = roleNames.key("album");
  this->setSortRole(role);
  this->sort(0,order);
}

}
