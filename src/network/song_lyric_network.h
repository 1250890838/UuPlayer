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
  void fetchStandard(qulonglong id);
  void fetchVerbatim(qulonglong id);  // 获取逐字歌词
 signals:
  void lyricReady(error_code::ErrorCode code, const QByteArray&);
  void verbatimReady(error_code::ErrorCode code, const QByteArray&);

 private:
  void fetchHelper(const QString& apiUrl, qulonglong id,
                   NetworkReadySignal<SongLyricNetwork> signal);
  void handleNetworkReply(QNetworkReply* reply,
                          NetworkReadySignal<SongLyricNetwork> signal);
};
}  // namespace network
#endif  // SONG_LYRIC_NETWORK_H
