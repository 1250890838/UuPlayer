#pragma once

#include <QSortFilterProxyModel>

namespace sort_option {
Q_NAMESPACE
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

namespace viewmodel {

class MediaItemFilterProxyModel : public QSortFilterProxyModel {
  Q_OBJECT

 public:
  explicit MediaItemFilterProxyModel(QObject* parent = nullptr);

  Q_INVOKABLE void setFilterString(const QString& str);
  Q_INVOKABLE void sort(int column,
                        Qt::SortOrder order = Qt::AscendingOrder) override;

 protected:
  bool lessThan(const QModelIndex& source_left,
                const QModelIndex& source_right) const override;
  bool filterAcceptsRow(int source_row,
                        const QModelIndex& source_parent) const override;

 private:
  QString m_filterStr;
};

}  // namespace viewmodel