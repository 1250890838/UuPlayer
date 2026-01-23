#ifndef COMMENTSFETCHSERVICE_H
#define COMMENTSFETCHSERVICE_H

#include <QObject>

#include "comment_item.h"
#include "comments_fetch_network.h"

using CommentItemList = QList<CommentItem>;
using CommentItemListPtr = QSharedPointer<CommentItemList>;

class CommentsFetchService : public QObject {
  Q_OBJECT
 public:
  explicit CommentsFetchService(QObject* parent = nullptr);
  void fetchMusic(qulonglong id, quint32 offset, quint32 limit);
  void fetchAlbum(qulonglong id, quint32 offset, quint32 limit);
  void fetchPlaylist(qulonglong id, quint32 offset, quint32 limit);
  void fetchMv(qulonglong id, quint32 offset, quint32 limit);
 public slots:
  void onMusicReady(error_code::ErrorCode code, const QByteArray& data);
  void onAlbumReady(error_code::ErrorCode code, const QByteArray& data);
  void onPlaylistReady(error_code::ErrorCode code, const QByteArray& data);
  void onMvReady(error_code::ErrorCode code, const QByteArray& data);
 signals:
  void musicReady(error_code::ErrorCode code, CommentItemListPtr data);
  void albumReady(error_code::ErrorCode code, CommentItemListPtr data);
  void playlistReady(error_code::ErrorCode code, CommentItemListPtr data);
  void mvReady(error_code::ErrorCode code, CommentItemListPtr data);

 private:
  CommentItemListPtr parseCommentsData(error_code::ErrorCode code,
                                       const QByteArray& data);
  UserItem formatUserdDataInComment(const QJsonObject& object);
  error_code::ErrorCode getActualErrorCode(error_code::ErrorCode networkCode,
                                           const CommentItemListPtr& ptr);

 private:
  network::CommentsFetchNetwork m_network;
};

#endif  // COMMENTSFETCHSERVICE_H
