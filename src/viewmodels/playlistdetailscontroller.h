#pragma once

#include <QObject>
#include <QObjectBindableProperty>
#include <QProperty>
#include <QQmlEngine>
#include <QSortFilterProxyModel>
#include <QUrl>

#include "entities/commentitem.h"
#include "entities/playlistitem.h"
#include "entities/types.h"
#include "entities/useritem.h"
#include "models/mediaitemfilterproxymodel.h"
#include "models/mediaitemmodel.h"

namespace viewmodel {
class PlayController;
}

namespace core {
class CommentRepository;
class PlaylistRepository;
class SongRepository;
}

namespace viewmodel {

class PlaylistDetailsController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(entities::PlaylistItem playlist READ playlist BINDABLE
                 bindablePlaylistItem FINAL)
  Q_PROPERTY(MediaItemFilterProxyModel* medias READ medias NOTIFY mediasChanged
                 FINAL)
  Q_PROPERTY(QList<entities::CommentItem> comments READ comments BINDABLE
                 bindableComments FINAL)
  Q_PROPERTY(QList<entities::UserItem> subscribers READ subscribers BINDABLE
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
  PlaylistDetailsController();
  ~PlaylistDetailsController() override = default;

  Q_INVOKABLE void fetchDetail(qulonglong id);
  Q_INVOKABLE void fetchLyric(qulonglong id);
  Q_INVOKABLE void fetchComments(qulonglong id, quint32 offset, quint32 limit);
  Q_INVOKABLE void fetchMediaUrl(qulonglong id,
                                 sound_level::SoundQualityLevel level);
  Q_INVOKABLE void fetchSubscribers(qulonglong id, quint32 offset = 0,
                                    quint32 limit = 30);
  Q_INVOKABLE void playAll();

  entities::PlaylistItem playlist() { return m_playlist.value(); }
  QList<entities::CommentItem> comments() { return m_comments.value(); }
  QList<entities::UserItem> subscribers() { return m_subscribers.value(); }
  MediaItemFilterProxyModel* medias() { return &m_mediasProxyModel; }
  QString name() { return m_name.value(); }
  QString desc() { return m_desc.value(); }
  QUrl coverUrl() { return m_coverUrl.value(); }
  QString creatorName() { return m_creatorName.value(); }
  QUrl creatorCoverUrl() { return m_creatorCoverUrl.value(); }
  qulonglong subscribedCount() { return m_subscribedCount.value(); }
  qulonglong createTime() { return m_createTime.value(); }

  QBindable<entities::PlaylistItem> bindablePlaylistItem() {
    return QBindable<entities::PlaylistItem>(&m_playlist);
  }
  QBindable<QList<entities::CommentItem>> bindableComments() {
    return &m_comments;
  }
  QBindable<QList<entities::UserItem>> bindableSubscribers() {
    return &m_subscribers;
  }
  QBindable<QString> bindableName() { return &m_name; }
  QBindable<QString> bindableDesc() { return &m_desc; }
  QBindable<QUrl> bindableCoverUrl() { return &m_coverUrl; }
  QBindable<QString> bindableCreatorName() { return &m_creatorName; }
  QBindable<QUrl> bindableCreatorCoverUrl() { return &m_creatorCoverUrl; }
  QBindable<qulonglong> bindableSubscribedCount() {
    return &m_subscribedCount;
  }
  QBindable<qulonglong> bindableCreateTime() { return &m_createTime; }

 signals:
  void mediasChanged();
  void mediaUrlReady(error_code::ErrorCode code, qulonglong id);

 private:
  core::PlaylistRepository* m_playlists = nullptr;
  core::CommentRepository* m_commentsRepository = nullptr;
  core::SongRepository* m_songs = nullptr;
  PlayController* m_player = nullptr;

  QProperty<entities::PlaylistItem> m_playlist;
  QProperty<QList<entities::CommentItem>> m_comments;
  QProperty<QList<entities::UserItem>> m_subscribers;
  QProperty<QUrl> m_coverUrl;
  QProperty<QString> m_name;
  QProperty<QString> m_desc;
  QProperty<QUrl> m_creatorCoverUrl;
  QProperty<QString> m_creatorName;
  QProperty<qulonglong> m_subscribedCount;
  QProperty<qulonglong> m_createTime;

  MediaItemFilterProxyModel m_mediasProxyModel;
  MediaItemModel m_mediasModel;
};

}  // namespace viewmodel