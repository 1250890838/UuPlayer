#pragma once

#include <QList>
#include <QObject>
#include <QUrl>

#include "entities/lyrictypes.h"
#include "entities/types.h"

namespace core {

class ApiClient;

class SongRepository : public QObject {
  Q_OBJECT
 public:
  explicit SongRepository(ApiClient* api, QObject* parent = nullptr);

  void fetchUrl(qulonglong id,
                sound_level::SoundQualityLevel level =
                    sound_level::SoundQualityLevel::Exhigh);
  void fetchLyric(qulonglong id);

 signals:
  void urlReady(error_code::ErrorCode code, qulonglong id, const QUrl& url);
  void lyricReady(error_code::ErrorCode code, qulonglong id,
                  const QList<entities::LyricLine>& lines);

 private:
  static QString levelName(sound_level::SoundQualityLevel level);

  ApiClient* m_api = nullptr;
};

}  // namespace core