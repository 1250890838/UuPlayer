#include <qnetworkaccessmanager.h>
#include <qstringview.h>
#include <qurl.h>
#include "basic_network.h"

namespace network {
class LoginNetwork : public BasicNetwork {
 public:
  LoginNetwork() = default;
 signals:
   void getQRCodeKeyFinished(const QByteArray&);
 protected:
  QNetworkReply* getQRCodeKey();
};
}  // namespace network
