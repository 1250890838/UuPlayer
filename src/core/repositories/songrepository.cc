#include "songrepository.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QUrlQuery>

#include "apiclient.h"
#include "apiendpoints.h"
#include "mappers.h"

namespace core {

SongRepository::SongRepository(ApiClient* api, QObject* parent)
    : QObject(parent), m_api(api) {}

QString SongRepository::levelName(sound_level::SoundQualityLevel level) {
  using sound_level::SoundQualityLevel;
  switch (level) {
    case SoundQualityLevel::Standard:
      return QStringLiteral("standard");
    case SoundQualityLevel::Higher:
      return QStringLiteral("higher");
    case SoundQualityLevel::Exhigh:
      return QStringLiteral("exhigh");
    case SoundQualityLevel::Lossless:
      return QStringLiteral("lossless");
    case SoundQualityLevel::Hires:
      return QStringLiteral("hires");
    case SoundQualityLevel::Jyeffect:
      return QStringLiteral("jyeffect");
    case SoundQualityLevel::Sky:
      return QStringLiteral("sky");
    case SoundQualityLevel::Jymaster:
      return QStringLiteral("jymaster");
  }
  return QStringLiteral("standard");
}

void SongRepository::fetchUrl(qulonglong id,
                              sound_level::SoundQualityLevel level) {
  QUrlQuery query;
  query.addQueryItem(QStringLiteral("id"), QString::number(id));
  query.addQueryItem(QStringLiteral("level"), levelName(level));

  m_api->get(endpoints::songUrl(), query, this,
             [this, id](error_code::ErrorCode code, const QByteArray& body) {
               const auto object = mappers::apiObject(body);
               if (code != error_code::NoError || !object) {
                 emit urlReady(code == error_code::NoError
                                   ? error_code::JsonContentError
                                   : code,
                               id, {});
                 return;
               }
               const QJsonArray data =
                   object->value(QStringLiteral("data")).toArray();
               if (data.isEmpty()) {
                 emit urlReady(error_code::JsonContentError, id, {});
                 return;
               }
               emit urlReady(
                   error_code::NoError, id,
                   QUrl(data.first()
                            .toObject()
                            .value(QStringLiteral("url"))
                            .toString()));
             });
}

void SongRepository::fetchLyric(qulonglong id) {
  QUrlQuery query;
  query.addQueryItem(QStringLiteral("id"), QString::number(id));

  m_api->get(endpoints::songLyric(), query, this,
             [this, id](error_code::ErrorCode code, const QByteArray& body) {
               const auto object = mappers::apiObject(body);
               if (code != error_code::NoError || !object) {
                 emit lyricReady(code == error_code::NoError
                                     ? error_code::JsonContentError
                                     : code,
                                 id, {});
                 return;
               }
               emit lyricReady(
                   error_code::NoError, id,
                   mappers::lyrics(
                       object->value(QStringLiteral("lrc"))
                           .toObject()
                           .value(QStringLiteral("lyric"))
                           .toString()));
             });
}

}
