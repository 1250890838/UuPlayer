#ifndef PLAYLISTDETAILS_H
#define PLAYLISTDETAILS_H

#include <QObject>
#include <QObjectBindableProperty>
#include <QQmlEngine>
#include <QSortFilterProxyModel>

#include "comments_fetch_service.h"
#include "model/mediaitem_filterproxy_model.h"
#include "play_service.h"
#include "playlistalbum_detail_service.h"
#include "song_lyric_service.h"
#include "song_url_service.h"
#include "user_item.h"

#include "model/media_item_model.h"

namespace controller {

using namespace model;
using namespace entities;
using namespace service;
class PlaylistDetailsController : public QObject {

  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(
      PlaylistItem playlist READ playlist BINDABLE bindablePlaylistItem FINAL)
  Q_PROPERTY(
      MediaItemFilterProxyModel* medias READ medias NOTIFY mediasChanged FINAL)
  Q_PROPERTY(
      QList<CommentItem> comments READ comments BINDABLE bindableComments FINAL)
  Q_PROPERTY(QList<UserItem> subscribers READ subscribers BINDABLE
                 bindableSubscribers FINAL)
  Q_PROPERTY(QString name READ name BINDABLE bindableName FINAL)
  Q_PROPERTY(QString desc READ desc BINDABLE bindableDesc FINAL)
  Q_PROPERTY(QUrl coverUrl READ coverUrl BINDABLE bindableCoverUrl FINAL)
  Q_PROPERTY(
      QString creatorName READ creatorName BINDABLE bindableCreatorName FINAL)
  Q_PROPERTY(QUrl creatorCoverUrl READ creatorCoverUrl BINDABLE
                 bindableCreatorCoverUrl FINAL)
  Q_PROPERTY(qulonglong subscribedCount READ subscribedCount BINDABLE
                 bindableSubscribedCount FINAL)
  Q_PROPERTY(
      qulonglong createTime READ createTime BINDABLE bindableCreateTime FINAL)

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
  MediaItemFilterProxyModel* medias() { return &m_mediasProxyModel; }
  QString name() { return m_name.value(); }
  QString desc() { return m_desc.value(); }
  QUrl coverUrl() { return m_coverUrl.value(); }
  QString creatorName() { return m_creatorName.value(); }
  QUrl creatorCoverUrl() { return m_creatorCoverUrl.value(); }
  qulonglong subscribedCount() { return m_subscribedCount.value(); }
  qulonglong createTime() { return m_createTime.value(); }
  QList<UserItem> subscribers() { return m_subscribers.value(); }

  QBindable<PlaylistItem> bindablePlaylistItem() {
    return QBindable<PlaylistItem>(&m_playlist);
  }
  QBindable<QList<CommentItem>> bindableComments() { return &m_comments; }
  QBindable<QList<UserItem>> bindableSubscribers() { return &m_subscribers; }
  QBindable<QString> bindableName() { return &m_name; }
  QBindable<QString> bindableDesc() { return &m_desc; }
  QBindable<QUrl> bindableCoverUrl() { return &m_coverUrl; }
  QBindable<QString> bindableCreatorName() { return &m_creatorName; }
  QBindable<QUrl> bindableCreatorCoverUrl() { return &m_creatorCoverUrl; }
  QBindable<qulonglong> bindableSubscribedCount() { return &m_subscribedCount; }
  QBindable<qulonglong> bindableCreateTime() { return &m_createTime; }

 private slots:
  void onDetailReady(error_code::ErrorCode code, PlaylistItemPtr data);
  void onCommentsReady(error_code::ErrorCode code, CommentItemListPtr data);
  void onMediaUrlReady(error_code::ErrorCode code, const QUrl& url,
                       qulonglong id);
  void onLyricReady(error_code::ErrorCode code, qulonglong id,
                    const QVariantList& data);
  void onSubsribersReady(error_code::ErrorCode code, UserItemsPtr data);
 signals:
  void mediasChanged();
  void mediaUrlReady(error_code::ErrorCode code, qulonglong id);

 private:
  QProperty<PlaylistItem> m_playlist;
  QProperty<QList<CommentItem>> m_comments;
  QProperty<QList<UserItem>> m_subscribers;
  QProperty<QUrl> m_coverUrl;
  QProperty<QString> m_name;
  QProperty<QString> m_desc;
  QProperty<QUrl> m_creatorCoverUrl;
  QProperty<QString> m_creatorName;
  QProperty<qulonglong> m_subscribedCount;
  QProperty<qulonglong> m_createTime;

  QPointer<PlaylistAlbumDetailService> m_detailService;
  QPointer<CommentsFetchService> m_commentsService;
  QPointer<SongUrlService> m_songUrlService;
  QPointer<PlayService> m_playService;
  QPointer<SongLyricService> m_songLyricService;

  MediaItemFilterProxyModel m_mediasProxyModel;
  MediaItemModel m_mediasModel;
  quint8 m_stateCounter = 0;
};
}  // namespace controller
#endif  // PLAYLISTDETAILS_H
