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
  void getMusic(qulonglong id, quint32 offset, quint32 limit);
  void getAlbum(qulonglong id, quint32 offset, quint32 limit);
  void getPlaylist(qulonglong id, quint32 offset, quint32 limit);
  void getMv(qulonglong id, quint32 offset, quint32 limit);
 public slots:
  void onGetMusicFinished(error_code::ErrorCode code, const QByteArray& data);
  void onGetAlbumFinished(error_code::ErrorCode code, const QByteArray& data);
  void onGetPlaylistFinished(error_code::ErrorCode code,
                             const QByteArray& data);
  void onGetMvFinished(error_code::ErrorCode code, const QByteArray& data);
 signals:
  void getMusicFinished(error_code::ErrorCode code, CommentItemListPtr data);
  void getAlbumFinished(error_code::ErrorCode code, CommentItemListPtr data);
  void getPlaylistFinished(error_code::ErrorCode code, CommentItemListPtr data);
  void getMvFinished(error_code::ErrorCode code, CommentItemListPtr data);

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
