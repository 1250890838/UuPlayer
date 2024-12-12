#include <qnetworkaccessmanager.h>
#include <qurl.h>
#include "basic_network.h"

namespace network {
class LoginNetwork : public BasicNetwork {
 public:
  LoginNetwork();
  protected:
   QNetworkReply* getQRCodeKey();
};
}  // namespace network
