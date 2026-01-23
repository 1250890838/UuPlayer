#include "featured_playlisthub_controller.h"
namespace controller {

FeaturedPlaylistHubController::FeaturedPlaylistHubController() {}

PlaylistItemModel* FeaturedPlaylistHubController::currPlaylistItems() {
  return &m_playlistItemModel;
}
}  // namespace controller
