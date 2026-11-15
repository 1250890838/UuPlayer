#include "playlistrepository.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QUrlQuery>

#include "apiclient.h"
#include "apiendpoints.h"
#include "mappers.h"

namespace core {

PlaylistRepository::PlaylistRepository(ApiClient* api, QObject* parent)
    : QObject(parent), m_api(api) {}

void PlaylistRepository::fetchTop(const QString& category, int offset,
                                  int limit) {
  QUrlQuery query;
  query.addQueryItem(QStringLiteral("cat"), category);
  query.addQueryItem(QStringLiteral("offset"), QString::number(offset));
  query.addQueryItem(QStringLiteral("limit"), QString::number(limit));

  m_api->get(endpoints::topPlaylists(), query, this,
             [this](error_code::ErrorCode code, const QByteArray& body) {
               const auto object = mappers::apiObject(body);
               if (code != error_code::NoError || !object) {
                 emit topReady(code == error_code::NoError
                                   ? error_code::JsonContentError
                                   : code,
                               {});
                 return;
               }
               emit topReady(
                   error_code::NoError,
                   mappers::playlists(
                       object->value(QStringLiteral("playlists")).toArray()));
             });
}

void PlaylistRepository::fetchCategories() {
  m_api->get(endpoints::playlistCategories(), this,
             [this](error_code::ErrorCode code, const QByteArray& body) {
               const auto object = mappers::apiObject(body);
               if (code != error_code::NoError || !object) {
                 emit categoriesReady(code == error_code::NoError
                                          ? error_code::JsonContentError
                                          : code,
                                      {});
                 return;
               }

               const QJsonArray subs = object->value(QStringLiteral("sub")).toArray();
               const QJsonObject groups =
                   object->value(QStringLiteral("categories")).toObject();

               QMap<QString, QStringList> categories;
               for (auto it = groups.constBegin(); it != groups.constEnd();
                    ++it) {
                 const int groupId = it.key().toInt();
                 QStringList names;
                 for (const auto& sub : subs) {
                   const QJsonObject entry = sub.toObject();
                   if (entry.value(QStringLiteral("category")).toInt() ==
                       groupId) {
                     names.append(entry.value(QStringLiteral("name")).toString());
                   }
                 }
                 categories.insert(it.value().toString(), names);
               }
               emit categoriesReady(error_code::NoError, categories);
             });
}

void PlaylistRepository::fetchDetail(qulonglong id) {
  QUrlQuery query;
  query.addQueryItem(QStringLiteral("id"), QString::number(id));

  m_api->get(endpoints::playlistDetail(), query, this,
             [this](error_code::ErrorCode code, const QByteArray& body) {
               const auto object = mappers::apiObject(body);
               if (code != error_code::NoError || !object) {
                 emit detailReady(code == error_code::NoError
                                      ? error_code::JsonContentError
                                      : code,
                                  {});
                 return;
               }
               emit detailReady(
                   error_code::NoError,
                   mappers::playlistItem(
                       object->value(QStringLiteral("playlist")).toObject()));
             });
}

}
