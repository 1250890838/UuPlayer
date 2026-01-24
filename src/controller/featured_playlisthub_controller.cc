#include "featured_playlisthub_controller.h"

#include "service_manager.h"

namespace controller {

FeaturedPlaylistHubController::FeaturedPlaylistHubController(
    RecommendedPlaylistService* playlistService)
    : m_recommendedPlaylistService(playlistService) {}

FeaturedPlaylistHubController* FeaturedPlaylistHubController::create(
    QQmlEngine* qmlEngine, QJSEngine* jsEngine) {

  auto service =
      ServiceManager::instance().getInstance<RecommendedPlaylistService>();
  auto ctr = new FeaturedPlaylistHubController(service);
  return ctr;
}

void FeaturedPlaylistHubController::fetchPlaylistItems(const QString& tag) {}

void FeaturedPlaylistHubController::fetchCategories() {}


PlaylistItemModel* FeaturedPlaylistHubController::currPlaylistItems() {
  return &m_playlistItemModel;
}
}  // namespace controller
