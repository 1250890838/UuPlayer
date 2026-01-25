#include "playlistdetails_controller.h"

#include "service_manager.h"
namespace controller {

PlaylistDetailsController::PlaylistDetailsController(
    PlaylistAlbumDetailService* detailService,
    CommentsFetchService* commentsService)
    : m_detailService(detailService), m_commentsService(commentsService) {
  connect(m_detailService, &PlaylistAlbumDetailService::playlistReady, this,
          &PlaylistDetailsController::onDetailReady);
  connect(m_commentsService, &CommentsFetchService::playlistReady, this,
          &PlaylistDetailsController::onCommentsReady);
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

void PlaylistDetailsController::fetchDetail(qulonglong id) {
  m_detailService->fetchPlaylist(id);
}

void PlaylistDetailsController::fetchComments(qulonglong id, quint32 offset,
                                              quint32 limit) {
  m_commentsService->fetchPlaylist(id, offset, limit);
}

PlaylistDetailsController* PlaylistDetailsController::create(
    QQmlEngine* qmlEngine, QJSEngine* jsEngine) {
  return new PlaylistDetailsController(
      ServiceManager::instance().getInstance<PlaylistAlbumDetailService>(),
      ServiceManager::instance().getInstance<CommentsFetchService>());
}

}  // namespace controller
