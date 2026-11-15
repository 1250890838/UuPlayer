#include "featuredplaylisthubcontroller.h"

#include "app/appcontext.h"
#include "repositories/playlistrepository.h"

namespace viewmodel {

FeaturedPlaylistHubController::FeaturedPlaylistHubController() {
  m_playlists = app::AppContext::instance()->playlists();

  connect(m_playlists, &core::PlaylistRepository::topReady, this,
          [this](error_code::ErrorCode code,
                 const QList<entities::PlaylistItem>& playlists) {
            if (code != error_code::NoError) {
              return;
            }
            m_playlistItemModel.appendItems(playlists);
          });

  connect(m_playlists, &core::PlaylistRepository::categoriesReady, this,
          [this](error_code::ErrorCode code,
                 const QMap<QString, QStringList>& categories) {
            if (code != error_code::NoError) {
              return;
            }
            QVariantMap result;
            for (auto it = categories.constBegin(); it != categories.constEnd();
                 ++it) {
              result.insert(it.key(), it.value());
            }
            m_categories.setValue(result);
          });
}

void FeaturedPlaylistHubController::fetchPlaylistItems(const QString& tag,
                                                       quint32 offset,
                                                       quint32 limit) {
  m_playlists->fetchTop(tag, int(offset), int(limit));
}

void FeaturedPlaylistHubController::clearPlaylistItems() {
  m_playlistItemModel.clear();
}

void FeaturedPlaylistHubController::fetchCategories() {
  m_playlists->fetchCategories();
}

}  // namespace viewmodel