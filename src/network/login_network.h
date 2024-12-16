#include <QtMultimedia/qaudio.h>
#include <qnetworkaccessmanager.h>
#include <qstringview.h>
#include <qurl.h>
#include "basic_network.h"
#include "network_global.h"

namespace network {
class NETWORK_DLL_EXPORT LoginNetwork : public BasicNetwork {
 public:
  LoginNetwork() = default;
  void getQRCodeKey();
 signals:
  void getQRCodeKeyFinished(error_code::ErrorCode code,const QByteArray&);
};
}  // namespace network
