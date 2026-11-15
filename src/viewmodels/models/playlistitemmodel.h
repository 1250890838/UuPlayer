#pragma once

#include <QAbstractListModel>
#include <QColor>
#include <QList>
#include <QUrl>

#include "entities/playlistitem.h"

namespace viewmodel {

class PlaylistItemModel : public QAbstractListModel {
  Q_OBJECT
 public:
  enum PlaylistRoles {
    IdRole = Qt::UserRole + 1,
    NameRole,
    UserId,
    CreateTimeRole,
    UpdateTimeRole,
    CoverUrlRole,
    DescriptionRole,
    TagsRole,
    PlayCountRole,
    CreatorRole,
    SubscribersRole,
    SubscribedRole,
    TracksRole
  };

  explicit PlaylistItemModel(QObject* parent = nullptr);

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE entities::PlaylistItem itemAt(quint32 index) const;
  Q_INVOKABLE entities::PlaylistItem last() const;

  void appendItem(const entities::PlaylistItem& item);
  void appendItems(const QList<entities::PlaylistItem>& items);
  void clear();

 private:
  QList<entities::PlaylistItem> m_items;
};

}  // namespace viewmodel