#ifndef MEDIAITEMFILTERPROXYMODEL_H
#define MEDIAITEMFILTERPROXYMODEL_H
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
  MediaItemFilterProxyModel();

 protected:
  // QTC_TEMP
  // QSortFilterProxyModel interface
 protected:
  bool lessThan(const QModelIndex& source_left,
                const QModelIndex& source_right) const override;

  // QAbstractItemModel interface
 public:
  void sort(int column, Qt::SortOrder order) override;
};
}
#endif
// MEDIAITEMFILTERPROXYMODEL_H
