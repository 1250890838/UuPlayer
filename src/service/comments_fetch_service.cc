#include "comments_fetch_service.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

CommentsFetchService::CommentsFetchService(QObject* parent) : QObject{parent} {
  using namespace network;
  connect(&m_network, &CommentsFetchNetwork::albumReady, this,
          &CommentsFetchService::onAlbumReady);
  connect(&m_network, &CommentsFetchNetwork::playlistReady, this,
          &CommentsFetchService::onPlaylistReady);
  connect(&m_network, &CommentsFetchNetwork::musicReady, this,
          &CommentsFetchService::onMusicReady);
  connect(&m_network, &CommentsFetchNetwork::mvReady, this,
          &CommentsFetchService::onMvReady);
}

void CommentsFetchService::fetchMusic(qulonglong id, quint32 offset,
                                      quint32 limit) {
  m_network.fetchMusic(id, offset, limit);
}

void CommentsFetchService::fetchAlbum(qulonglong id, quint32 offset,
                                      quint32 limit) {
  m_network.fetchAlbum(id, offset, limit);
}

void CommentsFetchService::fetchPlaylist(qulonglong id, quint32 offset,
                                         quint32 limit) {
  m_network.fetchPlaylist(id, offset, limit);
}

void CommentsFetchService::fetchMv(qulonglong id, quint32 offset,
                                   quint32 limit) {
  m_network.fetchMv(id, offset, limit);
}

void CommentsFetchService::onMusicReady(error_code::ErrorCode code,
                                        const QByteArray& data) {
  auto ptr = parseCommentsData(code, data);
  emit musicReady(getActualErrorCode(code, ptr), ptr);
}

void CommentsFetchService::onAlbumReady(error_code::ErrorCode code,
                                        const QByteArray& data) {
  auto ptr = parseCommentsData(code, data);
  emit albumReady(getActualErrorCode(code, ptr), ptr);
}

UserItem CommentsFetchService::formatUserdDataInComment(
    const QJsonObject& object) {
  UserItem item;
  item.setId(object["userId"].toVariant().toULongLong());
  item.setAvatarUrl(object["avatarUrl"].toString());
  item.setName(object["nickname"].toString());
  return item;
}

void CommentsFetchService::onPlaylistReady(error_code::ErrorCode code,
                                           const QByteArray& data) {
  auto ptr = parseCommentsData(code, data);
  emit playlistReady(getActualErrorCode(code, ptr), ptr);
}

void CommentsFetchService::onMvReady(error_code::ErrorCode code,
                                     const QByteArray& data) {
  auto ptr = parseCommentsData(code, data);
  emit mvReady(getActualErrorCode(code, ptr), ptr);
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
