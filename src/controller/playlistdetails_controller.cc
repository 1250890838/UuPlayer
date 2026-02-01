#include "playlistdetails_controller.h"

#include "service_manager.h"
namespace controller {

PlaylistDetailsController::PlaylistDetailsController() {
  m_detailService =
      ServiceManager::instance().getInstance<PlaylistAlbumDetailService>();
  m_commentsService =
      ServiceManager::instance().getInstance<CommentsFetchService>();
  m_songUrlService = ServiceManager::instance().getInstance<SongUrlService>();
  m_playService = ServiceManager::instance().getInstance<PlayService>();
  m_songLyricService =
      ServiceManager::instance().getInstance<SongLyricService>();

  if(m_detailService)
    connect(m_detailService, &PlaylistAlbumDetailService::playlistReady, this,
          &PlaylistDetailsController::onDetailReady);
  if(m_commentsService)
    connect(m_commentsService, &CommentsFetchService::playlistReady, this,
          &PlaylistDetailsController::onCommentsReady);
  if(m_songUrlService)
  connect(m_songUrlService, &SongUrlService::ready, this,
          &PlaylistDetailsController::onMediaUrlReady);
  connect(m_songLyricService, &SongLyricService::standardReady, this,
          &PlaylistDetailsController::onLyricReady);
}

void PlaylistDetailsController::onDetailReady(error_code::ErrorCode code,
                                              PlaylistItemPtr data) {
  m_playlist.setValue(*data.get());
  m_name.setValue(data->name());
  m_desc.setValue(data->desc());
  m_creatorName.setValue(data->creator().name());
  m_coverUrl.setValue(data->coverUrl());
  m_creatorCoverUrl.setValue(data->creator().avatarUrl());
  m_subscribedCount.setValue(data->subscribedCount());
  m_createTime.setValue(data->createTime());
  for (const auto& item : data->mediaItems()) {
    m_mediasModel.appendItem(item);
  }
}

void PlaylistDetailsController::onCommentsReady(error_code::ErrorCode code,
                                                CommentItemListPtr data) {
  auto temp = m_comments.value().toList();
  temp.append(*data);
  m_comments.setValue(temp);
}

void PlaylistDetailsController::onMediaUrlReady(error_code::ErrorCode code,
                                                const QUrl& url,
                                                qulonglong id) {
  m_mediasModel.setDataForId(id, url, MediaItemModel::UrlRole);
  m_playService->appendMediaItem(m_mediasModel.getItemForId(id));
  m_playService->play(id);
  emit mediaUrlReady(code, id);
}

void PlaylistDetailsController::onLyricReady(error_code::ErrorCode code,
                                             qulonglong id,
                                             const QVariantList& data) {
  m_playService->setLyric(data);
  emit m_playService->currentLyricChanged();
}

void PlaylistDetailsController::fetchDetail(qulonglong id) {
  if (m_detailService)
    m_detailService->fetchPlaylist(id);
}

void PlaylistDetailsController::fetchLyric(qulonglong id) {
  if(m_songLyricService)
    m_songLyricService->fetchStandard(id);
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

}  // namespace controller
