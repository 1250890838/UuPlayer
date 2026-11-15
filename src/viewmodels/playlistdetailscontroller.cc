#include "playlistdetailscontroller.h"

#include "app/appcontext.h"
#include "playcontroller.h"
#include "repositories/commentrepository.h"
#include "repositories/playlistrepository.h"
#include "repositories/songrepository.h"

namespace viewmodel {

PlaylistDetailsController::PlaylistDetailsController() {
  app::AppContext* context = app::AppContext::instance();
  m_playlists = context->playlists();
  m_commentsRepository = context->comments();
  m_songs = context->songs();
  m_player = context->play();

  m_mediasProxyModel.setSourceModel(&m_mediasModel);
  m_mediasProxyModel.setDynamicSortFilter(true);

  connect(m_playlists, &core::PlaylistRepository::detailReady, this,
          [this](error_code::ErrorCode code,
                 const entities::PlaylistItem& playlist) {
            if (code != error_code::NoError) {
              return;
            }
            m_playlist.setValue(playlist);
            m_name.setValue(playlist.name());
            m_desc.setValue(playlist.desc());
            m_creatorName.setValue(playlist.creator().name());
            m_coverUrl.setValue(playlist.coverUrl());
            m_creatorCoverUrl.setValue(playlist.creator().avatarUrl());
            m_subscribedCount.setValue(playlist.subscribedCount());
            m_createTime.setValue(playlist.createTime());

            m_mediasModel.clear();
            m_mediasModel.appendItems(playlist.mediaItems());
            emit mediasChanged();
          });

  connect(m_playlists, &core::PlaylistRepository::subscribersReady, this,
          [this](error_code::ErrorCode code,
                 const QList<entities::UserItem>& subscribers) {
            if (code != error_code::NoError) {
              return;
            }
            QList<entities::UserItem> all = m_subscribers.value();
            all.append(subscribers);
            m_subscribers.setValue(all);
          });

  connect(m_commentsRepository,
          &core::CommentRepository::playlistCommentsReady, this,
          [this](error_code::ErrorCode code,
                 const QList<entities::CommentItem>& comments) {
            if (code != error_code::NoError) {
              return;
            }
            QList<entities::CommentItem> all = m_comments.value();
            all.append(comments);
            m_comments.setValue(all);
          });

  connect(m_songs, &core::SongRepository::urlReady, this,
          [this](error_code::ErrorCode code, qulonglong id, const QUrl& url) {
            if (code != error_code::NoError) {
              return;
            }
            m_mediasModel.setUrl(id, url);
            const entities::MediaItem item = m_mediasModel.getItemForId(id);
            if (item.id != 0) {
              m_player->appendMediaItem(item);
            }
            emit mediaUrlReady(code, id);
          });
}

void PlaylistDetailsController::fetchDetail(qulonglong id) {
  m_comments.setValue({});
  m_subscribers.setValue({});
  m_playlists->fetchDetail(id);
}

void PlaylistDetailsController::fetchLyric(qulonglong id) {
  m_songs->fetchLyric(id);
}

void PlaylistDetailsController::fetchComments(qulonglong id, quint32 offset,
                                              quint32 limit) {
  m_commentsRepository->fetchPlaylistComments(id, int(offset), int(limit));
}

void PlaylistDetailsController::fetchMediaUrl(
    qulonglong id, sound_level::SoundQualityLevel level) {
  const entities::MediaItem item = m_mediasModel.getItemForId(id);
  if (item.id != 0) {
    m_player->appendMediaItem(item);
  }
  m_player->play(id, level);
}

void PlaylistDetailsController::fetchSubscribers(qulonglong id, quint32 offset,
                                                 quint32 limit) {
  m_playlists->fetchSubscribers(id, int(offset), int(limit));
}

void PlaylistDetailsController::playAll() {
  const QList<entities::MediaItem> items = m_mediasModel.items();
  if (items.isEmpty()) {
    return;
  }
  for (const entities::MediaItem& item : items) {
    m_player->appendMediaItem(item);
  }
  m_player->play(items.first().id);
}

}  // namespace viewmodel