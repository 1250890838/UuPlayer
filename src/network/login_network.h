#ifndef LOGIN_NETWORK_H
#define LOGIN_NETWORK_H
#include <QtMultimedia/qaudio.h>
#include <qnetworkaccessmanager.h>
#include <qstringview.h>
#include <qtmetamacros.h>
#include <qurl.h>
#include "basic_network.h"
#include "network_global.h"

namespace network {
class NETWORK_DLL_EXPORT LoginNetwork : public BasicNetwork {
  Q_OBJECT
 public:
  LoginNetwork() = default;
  void getQRCodeKey();
  void createQRCode(const QString& key);
 signals:
  void getQRCodeKeyFinished(error_code::ErrorCode code,const QByteArray&);
};
}  // namespace network
#endif
