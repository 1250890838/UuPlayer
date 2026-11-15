#include "commentrepository.h"

#include <QUrlQuery>

#include "apiclient.h"
#include "apiendpoints.h"
#include "mappers.h"

namespace core {

CommentRepository::CommentRepository(ApiClient* api, QObject* parent)
    : QObject(parent), m_api(api) {}

void CommentRepository::fetchPlaylistComments(qulonglong playlistId,
                                              int offset, int limit) {
  QUrlQuery query;
  query.addQueryItem(QStringLiteral("id"), QString::number(playlistId));
  query.addQueryItem(QStringLiteral("offset"), QString::number(offset));
  query.addQueryItem(QStringLiteral("limit"), QString::number(limit));

  m_api->get(endpoints::playlistComments(), query, this,
             [this](error_code::ErrorCode code, const QByteArray& body) {
               const auto object = mappers::apiObject(body);
               if (code != error_code::NoError || !object) {
                 emit playlistCommentsReady(
                     code == error_code::NoError ? error_code::JsonContentError
                                                 : code,
                     {});
                 return;
               }
               emit playlistCommentsReady(
                   error_code::NoError,
                   mappers::comments(
                       object->value(QStringLiteral("comments")).toArray()));
             });
}

}  // namespace core