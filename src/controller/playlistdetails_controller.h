#ifndef PLAYLISTDETAILS_H
#define PLAYLISTDETAILS_H

#include <QObject>
#include <QObjectBindableProperty>
#include <QQmlEngine>

#include "comments_fetch_service.h"
#include "playlistalbum_detail_service.h"
#include "song_url_service.h"

#include "model/media_item_model.h"

namespace controller {

using namespace model;
using namespace entities;
using namespace service;
class PlaylistDetailsController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(PlaylistItem playlist READ playlist NOTIFY playlistChanged FINAL)
  Q_PROPERTY(MediaItemModel* medias READ medias NOTIFY mediasChanged FINAL)
  Q_PROPERTY(
      QList<CommentItem> comments READ comments NOTIFY commentsChanged FINAL)

 public:
  static PlaylistDetailsController* create(QQmlEngine* qmlEngine,
                                           QJSEngine* jsEngine);

  Q_INVOKABLE void fetchDetail(qulonglong id);
  Q_INVOKABLE void fetchComments(qulonglong id, quint32 offset, quint32 limit);
  Q_INVOKABLE void fetchMediaUrl(qulonglong id,
                                 sound_level::SoundQualityLevel level);

  PlaylistDetailsController(PlaylistAlbumDetailService* detailService,
                            CommentsFetchService* commentsService,
                            SongUrlService* songUrlService);
  PlaylistItem playlist() { return m_playlist.value(); }
  QList<CommentItem> comments() { return m_comments.value(); }
  MediaItemModel* medias() { return &m_mediasModel; }
 private slots:
  void onDetailReady(error_code::ErrorCode code, PlaylistItemPtr data);
  void onCommentsReady(error_code::ErrorCode code, CommentItemListPtr data);
  void onMediaUrlReady(error_code::ErrorCode code, const QUrl& url,
                       qulonglong id);
 signals:
  void playlistChanged();
  void commentsChanged();
  void mediasChanged();

 private:
  Q_OBJECT_BINDABLE_PROPERTY(PlaylistDetailsController, PlaylistItem,
                             m_playlist,
                             &PlaylistDetailsController::playlistChanged);
  Q_OBJECT_BINDABLE_PROPERTY(PlaylistDetailsController, QList<CommentItem>,
                             m_comments,
                             &PlaylistDetailsController::commentsChanged);
  QPointer<PlaylistAlbumDetailService> m_detailService;
  QPointer<CommentsFetchService> m_commentsService;
  QPointer<SongUrlService> m_songUrlService;

  MediaItemModel m_mediasModel;
};
}  // namespace controller
#endif  // PLAYLISTDETAILS_H
