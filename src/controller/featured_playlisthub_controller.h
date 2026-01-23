#ifndef PLAYLISTHUB_H
#define PLAYLISTHUB_H

#include <QObject>
#include <QQmlEngine>

#include "model/playlist_item_model.h"

#include "recommended_playlist_service.h"

namespace controller {

using namespace model;
using namespace service;
class FeaturedPlaylistHubController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
  Q_PROPERTY(PlaylistItemModel* currPlaylistItems READ currPlaylistItems)
  Q_PROPERTY(QVariantMap categories READ categories NOTIFY categoriesChanged)
 public:
  Q_INVOKABLE void fetchPlaylistItems(const QString& tag);
  Q_INVOKABLE void fetchCategories();

 public:
  FeaturedPlaylistHubController();
  PlaylistItemModel* currPlaylistItems();
  QVariantMap categories();

 signals:
  void categoriesChanged();

 private:
  RecommendedPlaylistService m_recommendedPlaylistService;

  PlaylistItemModel m_playlistItemModel;
};
}  // namespace controller
#endif // PLAYLISTHUB_H
