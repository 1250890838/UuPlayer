#ifndef PLAYLISTDETAILS_H
#define PLAYLISTDETAILS_H

#include <QObject>
#include <QObjectBindableProperty>
#include <QQmlEngine>

#include "comments_fetch_service.h"
#include "play_service.h"
#include "playlistalbum_detail_service.h"
#include "song_url_service.h"
#include "song_lyric_service.h"
#include "user_item.h"

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
  Q_PROPERTY(QList<UserItem> subscribers READ subscribers NOTIFY subscribersChanged FINAL)
  Q_PROPERTY(QString name READ name NOTIFY nameChanged FINAL)
  Q_PROPERTY(QString desc READ desc NOTIFY descChanged FINAL)
  Q_PROPERTY(QUrl coverUrl READ coverUrl NOTIFY coverUrlChanged FINAL)
  Q_PROPERTY(
      QString creatorName READ creatorName NOTIFY creatorNameChanged FINAL)
  Q_PROPERTY(QUrl creatorCoverUrl READ creatorCoverUrl NOTIFY
                 creatorCoverUrlChanged FINAL)
  Q_PROPERTY(qulonglong subscribedCount READ subscribedCount NOTIFY
                 subscribedCountChanged FINAL)
  Q_PROPERTY(
      qulonglong createTime READ createTime NOTIFY createTimeChanged FINAL)

 public:
  Q_INVOKABLE void fetchDetail(qulonglong id);
  Q_INVOKABLE void fetchLyric(qulonglong id);
  Q_INVOKABLE void fetchComments(qulonglong id, quint32 offset, quint32 limit);
  Q_INVOKABLE void fetchMediaUrl(qulonglong id,
                                 sound_level::SoundQualityLevel level);
  Q_INVOKABLE void fetchSubscribers(qulonglong id, quint32 offset = 0,
                                    quint32 limit = 30);

  PlaylistDetailsController();
  PlaylistItem playlist() { return m_playlist.value(); }
  QList<CommentItem> comments() { return m_comments.value(); }
  MediaItemModel* medias() { return &m_mediasModel; }
  QString name() { return m_name.value(); }
  QString desc() { return m_desc.value(); }
  QUrl coverUrl() { return m_coverUrl.value(); }
  QString creatorName() { return m_creatorName.value(); }
  QUrl creatorCoverUrl() { return m_creatorCoverUrl.value(); }
  qulonglong subscribedCount() { return m_subscribedCount.value(); }
  qulonglong createTime() { return m_createTime.value(); }
  QList<UserItem> subscribers() { return m_subscribers.value(); }

 private slots:
  void onDetailReady(error_code::ErrorCode code, PlaylistItemPtr data);
  void onCommentsReady(error_code::ErrorCode code, CommentItemListPtr data);
  void onMediaUrlReady(error_code::ErrorCode code, const QUrl& url,
                       qulonglong id);
  void onLyricReady(error_code::ErrorCode code, qulonglong id,const QVariantList& data);
  void onSubsribersReady(error_code::ErrorCode code, UserItemsPtr data);
 signals:
  void playlistChanged();
  void commentsChanged();
  void mediasChanged();
  void mediaUrlReady(error_code::ErrorCode code, qulonglong id);
  void coverUrlChanged();
  void nameChanged();
  void descChanged();
  void creatorNameChanged();
  void creatorCoverUrlChanged();
  void subscribedCountChanged();
  void createTimeChanged();
  void subscribersChanged();

 private:
  Q_OBJECT_BINDABLE_PROPERTY(PlaylistDetailsController, PlaylistItem,
                             m_playlist,
                             &PlaylistDetailsController::playlistChanged);
  Q_OBJECT_BINDABLE_PROPERTY(PlaylistDetailsController, QList<CommentItem>,
                             m_comments,
                             &PlaylistDetailsController::commentsChanged);
  Q_OBJECT_BINDABLE_PROPERTY(PlaylistDetailsController, QList<UserItem>,
                             m_subscribers,
                             &PlaylistDetailsController::subscribersChanged);
  Q_OBJECT_BINDABLE_PROPERTY(PlaylistDetailsController, QUrl, m_coverUrl,
                             &PlaylistDetailsController::coverUrlChanged);
  Q_OBJECT_BINDABLE_PROPERTY(PlaylistDetailsController, QString, m_name,
                             &PlaylistDetailsController::nameChanged);
  Q_OBJECT_BINDABLE_PROPERTY(PlaylistDetailsController, QString, m_desc,
                             &PlaylistDetailsController::descChanged);
  Q_OBJECT_BINDABLE_PROPERTY(
      PlaylistDetailsController, QUrl, m_creatorCoverUrl,
      &PlaylistDetailsController::creatorCoverUrlChanged);
  Q_OBJECT_BINDABLE_PROPERTY(PlaylistDetailsController, QString, m_creatorName,
                             &PlaylistDetailsController::creatorNameChanged);
  Q_OBJECT_BINDABLE_PROPERTY(
      PlaylistDetailsController, qulonglong, m_subscribedCount,
      &PlaylistDetailsController::subscribedCountChanged);
  Q_OBJECT_BINDABLE_PROPERTY(PlaylistDetailsController, qulonglong,
                             m_createTime,
                             &PlaylistDetailsController::createTimeChanged);


  QPointer<PlaylistAlbumDetailService> m_detailService;
  QPointer<CommentsFetchService> m_commentsService;
  QPointer<SongUrlService> m_songUrlService;
  QPointer<PlayService> m_playService;
  QPointer<SongLyricService> m_songLyricService;

  MediaItemModel m_mediasModel;
  quint8 m_stateCounter = 0;
};
}  // namespace controller
#endif  // PLAYLISTDETAILS_H
