#ifndef SONGURLNETWORK_H
#define SONGURLNETWORK_H

#include "basic_network.h"
#include "network_global.h"

namespace network {
class NETWORK_DLL_EXPORT SongUrlNetwork : public BasicNetwork {
  Q_OBJECT
 public:
  SongUrlNetwork();
  void fetch(qulonglong id, sound_level::SoundQualityLevel level);
  void checkEnable(qulonglong id);
 signals:
  void ready(error_code::ErrorCode code, const QByteArray& data);
  void enabledReady(error_code::ErrorCode code, const QByteArray& data);
};
}  // namespace network
#endif  // SONGURLNETWORK_H
