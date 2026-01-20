#ifndef MEDIAITEMFILTERPROXYMODEL_H
#define MEDIAITEMFILTERPROXYMODEL_H
#endif
#include <QSortFilterProxyModel>
#if defined(CONTROLLER_EXPORT_SYMBOLS)
#define CONTROLLER_DLL_EXPORT Q_DECL_EXPORT
#else
#define CONTROLLER_DLL_EXPORT Q_DECL_IMPORT
#endif
// UUSERVICE_GLOBAL_H

namespace sort_option {
CONTROLLER_DLL_EXPORT Q_NAMESPACE
enum SortOption {
  TitleAsc,
  TitleDesc,
  AlbumNameAsc,
  AlbumNameDesc,
  DurationAsc,
  DurationDesc,
  FileSizeAsc,
  FileSizeDesc
};
Q_ENUM_NS(SortOption)
}  // namespace sort_option

namespace model{
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
}
// MEDIAITEMFILTERPROXYMODEL_H
