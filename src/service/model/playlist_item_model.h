#ifndef _MODEL_PLAYLIST_ITEM_MODEL_H
#define _MODEL_PLAYLIST_ITEM_MODEL_H

#include "entities/playlist_item.h"

#include <qglobal.h>
#include <qtmetamacros.h>
#include <QAbstractListModel>
#include <QColor>
#include <QObject>
#include <QUrl>

using namespace entities;
namespace model{
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

  Q_INVOKABLE PlaylistItem itemAt(quint32 index);
  Q_INVOKABLE PlaylistItem* last();

  PlaylistItemModel(QObject* parent = nullptr);
  int rowCount(const QModelIndex& parent) const;
  QVariant data(const QModelIndex& index, int role) const;
  QHash<int, QByteArray> roleNames() const;
  void appendItem(PlaylistItem* item);
  void appendItems(const QVector<PlaylistItem>& items);
  void clear();

 private:
  QList<PlaylistItem*> m_items;
};
}  // namespace model

#endif
