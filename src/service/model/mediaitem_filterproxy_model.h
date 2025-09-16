#ifndef MEDIAITEMFILTERPROXYMODEL_H
#define MEDIAITEMFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class MediaItemFilterProxyModel : public QSortFilterProxyModel
{
  Q_OBJECT
 public:
  Q_INVOKABLE void sortByArtistName(Qt::SortOrder);
  Q_INVOKABLE void sortByTitle(Qt::SortOrder);
  Q_INVOKABLE void sortByDuration(Qt::SortOrder);
  Q_INVOKABLE void sortByFileSize(Qt::SortOrder);
  Q_INVOKABLE void sortByAlbumName(Qt::SortOrder);
 public:
  MediaItemFilterProxyModel();
};

#endif // MEDIAITEMFILTERPROXYMODEL_H
