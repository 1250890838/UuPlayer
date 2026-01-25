#include "featured_playlisthub_controller.h"

#include <QMap>
#include <QVariant>

#include "service_manager.h"

namespace controller {

FeaturedPlaylistHubController::FeaturedPlaylistHubController(
    RecommendedPlaylistService* playlistService)
    : m_recommendedPlaylistService(playlistService) {
  connect(m_recommendedPlaylistService, &RecommendedPlaylistService::topReady,
          this, &FeaturedPlaylistHubController::onTopReady);
  connect(m_recommendedPlaylistService,
          &RecommendedPlaylistService::categoriesReady, this,
          &FeaturedPlaylistHubController::onCategoriesReady);
}

FeaturedPlaylistHubController* FeaturedPlaylistHubController::create(
    QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
  auto ctr = new FeaturedPlaylistHubController(
      ServiceManager::instance().getInstance<RecommendedPlaylistService>());
  return ctr;
}

void FeaturedPlaylistHubController::fetchPlaylistItems(const QString& tag,
                                                       quint32 offset,
                                                       quint32 limit) {

  m_recommendedPlaylistService->fetchTop(tag, offset, limit);
}

void FeaturedPlaylistHubController::fetchCategories() {
  m_recommendedPlaylistService->fetchCategories();
}

PlaylistItemModel* FeaturedPlaylistHubController::currPlaylistItems() {
  return &m_playlistItemModel;
}

void FeaturedPlaylistHubController::onTopReady(error_code::ErrorCode code,
                                               PlaylistItemListPtr data) {
  if (code == error_code::NoError && !data.isNull()) {
    for (const auto& item : *data)
      m_playlistItemModel.appendItem(item);
  }
}

void FeaturedPlaylistHubController::onCategoriesReady(
    error_code::ErrorCode code, QMap<QString, QStringList> categoriesMap) {
  if (code == error_code::NoError) {
    QVariantMap result;
    for (const auto& [key, list] : categoriesMap.asKeyValueRange()) {
      result.insert(key, list);
    }
    m_categories.setValue(result);
  }
}
}  // namespace controller
