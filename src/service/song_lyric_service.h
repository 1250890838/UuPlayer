#ifndef SONG_LYRIC_SERVICE_H
#define SONG_LYRIC_SERVICE_H
#include "song_lyric_network.h"

#include <qglobal.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qtmetamacros.h>
#include <qtypes.h>
#include <qvariant.h>
#include <QObject>

#include "service_global.h"
#include "lyric_types.h"

namespace service {
using namespace entities;
// 获取歌曲相关信息服务
class SERVICE_DLL_EXPORT SongLyricService : public QObject {
  Q_OBJECT
 public:
  void fetchStandard(qulonglong id);
  void fetchVerbatim(qulonglong id);

 public:
  SongLyricService(QObject* parent = nullptr);
 public slots:
  //  void onGetSongUrlFinished(network::error_code::ErrorCode code,const QByteArray&,void* item);
  void onLyricReady(error_code::ErrorCode code, const QByteArray&);
  void onVerbatimReady(error_code::ErrorCode code, const QByteArray&);

 private:
  QList<LyricLine> parseLyricStr(const QString& yrc);
  QList<LyricLine> parseYrcLyric(const QString& yrc);

 private:
  network::SongLyricNetwork m_network;
 signals:
  void standardReady(error_code::ErrorCode code, qulonglong id,QList<LyricLine> lyricsLines);
  void verbatimReady(error_code::ErrorCode code, qulonglong id,QList<LyricLine> lyricsLines);
};
}  // namespace service
#endif
