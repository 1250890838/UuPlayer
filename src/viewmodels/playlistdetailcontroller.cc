#include "playlistdetailcontroller.h"

#include "playcontroller.h"
#include "repositories/commentrepository.h"
#include "repositories/playlistrepository.h"

namespace viewmodel {

PlaylistDetailController::PlaylistDetailController(
    core::PlaylistRepository* playlists, core::CommentRepository* comments,
    PlayController* player, QObject* parent)
    : QObject(parent),
      m_playlists(playlists),
      m_commentsRepository(comments),
      m_player(player) {
  connect(m_playlists, &core::PlaylistRepository::detailReady, this,
          [this](error_code::ErrorCode code,
                 const entities::PlaylistItem& playlist) {
            if (code != error_code::NoError) {
              emit loadFailed(code);
              return;
            }
            m_detail = playlist;
            emit detailChanged();

            m_medias.clear();
            m_medias.append(playlist.mediaItems());
          });

  connect(m_commentsRepository,
          &core::CommentRepository::playlistCommentsReady, this,
          [this](error_code::ErrorCode code,
                 const QList<entities::CommentItem>& comments) {
            if (code != error_code::NoError) {
              emit loadFailed(code);
              return;
            }
            m_comments = comments;
            emit commentsChanged();
          });
}

void PlaylistDetailController::fetchDetail(qulonglong id) {
  m_playlists->fetchDetail(id);
}

void PlaylistDetailController::fetchComments(qulonglong id, int offset,
                                             int limit) {
  m_commentsRepository->fetchPlaylistComments(id, offset, limit);
}

void PlaylistDetailController::playTrack(int index) {
  m_player->playItem(m_medias.item(index));
}

void PlaylistDetailController::playAll() {
  m_player->playAll(m_medias.items());
}

}
