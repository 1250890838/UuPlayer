#ifndef SONG_NETWORK_H
#define SONG_NETWORK_H

#include "basic_network.h"
#include "network_global.h"

#include <qnetworkaccessmanager.h>
#include <qstringview.h>
#include <qtmetamacros.h>
#include <qurl.h>

namespace network {
class NETWORK_DLL_EXPORT SongNetwork : public BasicNetwork {
  Q_OBJECT
 public:
  SongNetwork()=default;
  void getSongUrl(qulonglong id);
  void checkSongEnable(qulonglong id);
  void getSongComments(qulonglong id);
  void getSongLyric(qulonglong id);
  void getSongNewLyric(qulonglong id);

 signals:
};
}  // namespace network
#endif  // SONG_NETWORK_H
