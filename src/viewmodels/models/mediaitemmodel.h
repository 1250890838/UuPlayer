#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QUrl>
#include <QtQml/qqmlregistration.h>

#include "entities/mediaitem.h"

namespace viewmodel {

class MediaItemModel : public QAbstractListModel {
  Q_OBJECT
  QML_ANONYMOUS
  Q_PROPERTY(int count READ count NOTIFY countChanged)

 public:
  enum Role {
    IdRole = Qt::UserRole + 1,
    NameRole,
    DurationRole,
    AlbumRole,
    ArtistRole,
    UrlRole
  };

  explicit MediaItemModel(QObject* parent = nullptr);

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE entities::MediaItem itemAt(int row) const;
  int count() const { return m_items.size(); }

  void append(const entities::MediaItem& item);
  void append(const QList<entities::MediaItem>& items);
  void clear();

  bool containsId(qulonglong id) const;
  int indexOfId(qulonglong id) const;
  entities::MediaItem item(int row) const;
  QList<entities::MediaItem> items() const { return m_items; }

  void setUrl(qulonglong id, const QUrl& url);

 signals:
  void countChanged();

 private:
  QList<entities::MediaItem> m_items;
};

}
