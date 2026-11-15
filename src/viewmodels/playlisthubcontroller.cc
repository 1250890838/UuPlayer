#include "playlisthubcontroller.h"

#include "repositories/playlistrepository.h"

namespace viewmodel {

PlaylistHubController::PlaylistHubController(
    core::PlaylistRepository* repository, QObject* parent)
    : QObject(parent), m_repository(repository) {
  connect(m_repository, &core::PlaylistRepository::topReady, this,
          [this](error_code::ErrorCode code,
                 const QList<entities::PlaylistItem>& playlists) {
            m_loading = false;
            emit loadingChanged();
            if (code != error_code::NoError) {
              emit loadFailed(code);
              return;
            }
            m_items.append(playlists);
            m_offset += playlists.size();
            m_hasMore = playlists.size() >= m_limit;
          });

  connect(m_repository, &core::PlaylistRepository::categoriesReady, this,
          [this](error_code::ErrorCode code,
                 const QMap<QString, QStringList>& categories) {
            if (code != error_code::NoError) {
              emit loadFailed(code);
              return;
            }
            QVariantMap map;
            for (auto it = categories.constBegin(); it != categories.constEnd();
                 ++it) {
              map.insert(it.key(), it.value());
            }
            m_categories = map;
            emit categoriesChanged();

            if (m_category.isEmpty() && !map.isEmpty()) {
              const QStringList tags =
                  map.constBegin().value().value<QStringList>();
              if (!tags.isEmpty()) {
                selectCategory(tags.first());
              }
            }
          });
}

void PlaylistHubController::fetchCategories() {
  if (!m_categories.isEmpty()) {
    return;
  }
  m_repository->fetchCategories();
}

void PlaylistHubController::selectCategory(const QString& category) {
  if (category.isEmpty() || category == m_category) {
    return;
  }
  m_category = category;
  m_offset = 0;
  m_hasMore = true;
  m_items.clear();
  requestPage();
}

void PlaylistHubController::fetchNextPage() {
  if (m_category.isEmpty() || m_loading || !m_hasMore) {
    return;
  }
  requestPage();
}

void PlaylistHubController::requestPage() {
  m_loading = true;
  emit loadingChanged();
  m_repository->fetchTop(m_category, m_offset, m_limit);
}

}
