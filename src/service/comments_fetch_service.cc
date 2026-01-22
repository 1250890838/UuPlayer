#include "comments_fetch_service.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

CommentsFetchService::CommentsFetchService(QObject* parent) : QObject{parent} {
  using namespace network;
  connect(&m_network, &CommentsFetchNetwork::getAlbumFinished, this,
          &CommentsFetchService::onGetAlbumFinished);
  connect(&m_network, &CommentsFetchNetwork::getPlaylistFinished, this,
          &CommentsFetchService::onGetPlaylistFinished);
  connect(&m_network, &CommentsFetchNetwork::getMusicFinished, this,
          &CommentsFetchService::onGetMusicFinished);
  connect(&m_network, &CommentsFetchNetwork::getMvFinished, this,
          &CommentsFetchService::onGetMvFinished);
}

void CommentsFetchService::getMusic(qulonglong id, quint32 offset,
                                    quint32 limit) {
  m_network.getMusic(id, offset, limit);
}

void CommentsFetchService::getAlbum(qulonglong id, quint32 offset,
                                    quint32 limit) {
  m_network.getAlbum(id, offset, limit);
}

void CommentsFetchService::getPlaylist(qulonglong id, quint32 offset,
                                       quint32 limit) {
  m_network.getPlaylist(id, offset, limit);
}

void CommentsFetchService::getMv(qulonglong id, quint32 offset, quint32 limit) {
  m_network.getMv(id, offset, limit);
}

void CommentsFetchService::onGetMusicFinished(error_code::ErrorCode code,
                                              const QByteArray& data) {
  auto ptr = parseCommentsData(code, data);
  emit getMusicFinished(getActualErrorCode(code, ptr), ptr);
}

void CommentsFetchService::onGetAlbumFinished(error_code::ErrorCode code,
                                              const QByteArray& data) {
  auto ptr = parseCommentsData(code, data);
  emit getAlbumFinished(getActualErrorCode(code, ptr), ptr);
}

UserItem CommentsFetchService::formatUserdDataInComment(
    const QJsonObject& object) {
  UserItem item;
  item.setId(object["userId"].toVariant().toULongLong());
  item.setAvatarUrl(object["avatarUrl"].toString());
  item.setName(object["nickname"].toString());
  return item;
}

void CommentsFetchService::onGetPlaylistFinished(error_code::ErrorCode code,
                                                 const QByteArray& data) {
  auto ptr = parseCommentsData(code, data);
  emit getPlaylistFinished(getActualErrorCode(code, ptr), ptr);
}

void CommentsFetchService::onGetMvFinished(error_code::ErrorCode code,
                                           const QByteArray& data) {
  auto ptr = parseCommentsData(code, data);
  emit getMvFinished(getActualErrorCode(code, ptr), ptr);
}

error_code::ErrorCode CommentsFetchService::getActualErrorCode(
    error_code::ErrorCode networkCode, const CommentItemListPtr& ptr) {

  if (networkCode == error_code::NoError && (!ptr || ptr->isEmpty())) {
    return error_code::JsonContentError;
  }
  return networkCode;
}

CommentItemListPtr CommentsFetchService::parseCommentsData(
    error_code::ErrorCode code, const QByteArray& data) {
  CommentItemListPtr ptr(nullptr);
  if (code != error_code::NoError)
    return ptr;
  QJsonDocument doc = QJsonDocument::fromJson(data);
  if (doc.isNull() || doc.isEmpty())
    return ptr;
  auto obj = doc.object();
  QJsonArray commentsArr = obj["comments"].toArray();
  ptr = CommentItemListPtr::create();
  for (const auto& commentValue : commentsArr) {
    CommentItem tempData;
    auto commentObj = commentValue.toObject();
    tempData.setId(commentObj["commentId"].toVariant().toULongLong());
    tempData.setContent(commentObj["content"].toString());
    tempData.setLikedCount(commentObj["likedCount"].toVariant().toULongLong());
    tempData.setTime(commentObj["time"].toVariant().toULongLong());
    tempData.setUserData(
        formatUserdDataInComment(commentObj["user"].toObject()));
    ptr->append(tempData);
  }
  return ptr;
}
