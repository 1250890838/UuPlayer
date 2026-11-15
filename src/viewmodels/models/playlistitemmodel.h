#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QtQml/qqmlregistration.h>

#include "entities/playlistitem.h"

namespace viewmodel {

class PlaylistItemModel : public QAbstractListModel {
  Q_OBJECT
  QML_ANONYMOUS
  Q_PROPERTY(int count READ count NOTIFY countChanged)

 public:
  enum Role {
    IdRole = Qt::UserRole + 1,
    NameRole,
    CoverUrlRole,
    PlayCountRole,
    DescriptionRole,
    CreatorRole,
    SubscribedCountRole
  };

  explicit PlaylistItemModel(QObject* parent = nullptr);

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

  int count() const { return m_items.size(); }

  void append(const QList<entities::PlaylistItem>& items);
  void clear();

 signals:
  void countChanged();

 private:
  QList<entities::PlaylistItem> m_items;
};

}
