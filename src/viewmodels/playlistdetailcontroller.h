#pragma once

#include <QList>
#include <QObject>

#include "entities/commentitem.h"
#include "entities/playlistitem.h"
#include "entities/types.h"
#include "models/mediaitemmodel.h"

class QQmlEngine;
class QJSEngine;

namespace core {
class CommentRepository;
class PlaylistRepository;
}

namespace viewmodel {
class PlayController;
}

namespace viewmodel {

class PlaylistDetailController : public QObject {
  Q_OBJECT
  Q_PROPERTY(entities::PlaylistItem detail READ detail NOTIFY detailChanged)
  Q_PROPERTY(QList<entities::CommentItem> comments READ comments NOTIFY
                 commentsChanged)
  Q_PROPERTY(MediaItemModel* medias READ medias CONSTANT)

 public:
  PlaylistDetailController(core::PlaylistRepository* playlists,
                           core::CommentRepository* comments,
                           PlayController* player, QObject* parent = nullptr);

  entities::PlaylistItem detail() const { return m_detail; }
  QList<entities::CommentItem> comments() const { return m_comments; }
  MediaItemModel* medias() { return &m_medias; }

  Q_INVOKABLE void fetchDetail(qulonglong id);
  Q_INVOKABLE void fetchComments(qulonglong id, int offset, int limit);
  Q_INVOKABLE void playTrack(int index);
  Q_INVOKABLE void playAll();

 signals:
  void detailChanged();
  void commentsChanged();
  void loadFailed(error_code::ErrorCode code);

 private:
  core::PlaylistRepository* m_playlists = nullptr;
  core::CommentRepository* m_commentsRepository = nullptr;
  PlayController* m_player = nullptr;

  entities::PlaylistItem m_detail;
  QList<entities::CommentItem> m_comments;
  MediaItemModel m_medias;
};

}
