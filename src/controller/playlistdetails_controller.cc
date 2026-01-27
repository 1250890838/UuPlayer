#include "playlistdetails_controller.h"

#include "service_manager.h"
namespace controller {

PlaylistDetailsController::PlaylistDetailsController(
    PlaylistAlbumDetailService* detailService,
    CommentsFetchService* commentsService, SongUrlService* songUrlService)
    : m_detailService(detailService),
      m_commentsService(commentsService),
      m_songUrlService(songUrlService) {
  connect(m_detailService, &PlaylistAlbumDetailService::playlistReady, this,
          &PlaylistDetailsController::onDetailReady);
  connect(m_commentsService, &CommentsFetchService::playlistReady, this,
          &PlaylistDetailsController::onCommentsReady);
  connect(m_songUrlService, &SongUrlService::ready, this,
          &PlaylistDetailsController::onMediaUrlReady);
}

void PlaylistDetailsController::onDetailReady(error_code::ErrorCode code,
                                              PlaylistItemPtr data) {
  m_playlist.setValue(*data.get());
  for (const auto& item : data->mediaItems()) {
    m_mediasModel.appendItem(item);
  }
}

void PlaylistDetailsController::onCommentsReady(error_code::ErrorCode code,
                                                CommentItemListPtr data) {
  m_comments.setValue(*data.get());
}

void PlaylistDetailsController::onMediaUrlReady(error_code::ErrorCode code,
                                                const QUrl& url,
                                                qulonglong id) {
  m_mediasModel.setDataForId(id, url, MediaItemModel::UrlRole);
}

void PlaylistDetailsController::fetchDetail(qulonglong id) {
  if (m_detailService)
    m_detailService->fetchPlaylist(id);
}

void PlaylistDetailsController::fetchComments(qulonglong id, quint32 offset,
                                              quint32 limit) {
  if (m_commentsService)
    m_commentsService->fetchPlaylist(id, offset, limit);
}

void PlaylistDetailsController::fetchMediaUrl(
    qulonglong id, sound_level::SoundQualityLevel level) {
  if (m_songUrlService)
    m_songUrlService->fetch(id, level);
}

PlaylistDetailsController* PlaylistDetailsController::create(
    QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
  return new PlaylistDetailsController(
      ServiceManager::instance().getInstance<PlaylistAlbumDetailService>(),
      ServiceManager::instance().getInstance<CommentsFetchService>(),
      ServiceManager::instance().getInstance<SongUrlService>());
}

}  // namespace controller
