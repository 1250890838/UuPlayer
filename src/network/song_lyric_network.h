#ifndef SONG_LYRIC_NETWORK_H
#define SONG_LYRIC_NETWORK_H

#include "basic_network.h"
#include "network_global.h"

#include <qnetworkaccessmanager.h>
#include <qstringview.h>
#include <qtmetamacros.h>
#include <qurl.h>

namespace network {
class NETWORK_DLL_EXPORT SongLyricNetwork : public BasicNetwork {
  Q_OBJECT
 public:
  SongLyricNetwork() = default;
  //void getSongUrl(qulonglong id, void* item);
  //void checkSongEnable(qulonglong id);
  //void getSongComments(qulonglong id);
  void getSongLyric(qulonglong id);
  void getSongVerbatimLyric(qulonglong id);  // 获取逐字歌词

 signals:
  //  void getSongUrlFinished(error_code::ErrorCode code, const QByteArray&,
  //                          void* item);
  void getSongLyricFinished(error_code::ErrorCode code, const QByteArray&);
  void getSongVerbatimLyricFinished(error_code::ErrorCode code,
                                    const QByteArray&);

 private:
  void getLyricHelper(const QString& apiUrl, qulonglong id,
                      void (SongLyricNetwork::*finishedSignal)(
                          error_code::ErrorCode, const QByteArray&));
  void handleNetworkReply(QNetworkReply* reply,
                          void (SongLyricNetwork::*finishedSignal)(
                              error_code::ErrorCode, const QByteArray&));
};
}  // namespace network
#endif  // SONG_LYRIC_NETWORK_H
