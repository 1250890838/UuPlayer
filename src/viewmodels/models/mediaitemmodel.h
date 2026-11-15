#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QUrl>

#include "entities/mediaitem.h"

namespace viewmodel {

class MediaItemModel : public QAbstractListModel {
  Q_OBJECT
  Q_PROPERTY(quint32 count READ count NOTIFY countChanged)
  Q_PROPERTY(int rows READ rows NOTIFY countChanged)

 public:
  enum MediaRoles {
    IdRole = Qt::UserRole + 1,
    NameRole,
    DurationRole,
    AlbumRole,
    ArtistRole,
    ReasonRole,
    UrlRole
  };

  explicit MediaItemModel(QObject* parent = nullptr);

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;
  bool setData(const QModelIndex& index, const QVariant& value,
               int role) override;

  Q_INVOKABLE entities::MediaItem itemAt(int index) const;
  Q_INVOKABLE entities::MediaItem last() const;
  Q_INVOKABLE int rows() const { return int(m_items.size()); }
  quint32 count() const { return quint32(m_items.size()); }

  void insertItem(const entities::MediaItem& item, int pos);
  void appendItem(const entities::MediaItem& item);
  void appendItems(const QList<entities::MediaItem>& items);
  void removeItem(int pos);
  void clear();

  bool setDataForId(qulonglong id, const QVariant& value, int role);
  entities::MediaItem getItemForId(qulonglong id) const;
  QList<entities::MediaItem> items() const { return m_items; }

  void setUrl(qulonglong id, const QUrl& url);

 signals:
  void countChanged();
  void itemsChanged();

 private:
  QList<entities::MediaItem> m_items;
};

}  // namespace viewmodel