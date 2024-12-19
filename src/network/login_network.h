#ifndef LOGIN_NETWORK_H
#define LOGIN_NETWORK_H
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
  void checkQRCodeScan(const QString& key);
 signals:
  void getQRCodeKeyFinished(error_code::ErrorCode code, const QByteArray&);
  void createQRCodeFinished(error_code::ErrorCode code, const QByteArray&);
  void checkQRCodeScanFinished(error_code::ErrorCode code, const QByteArray&);
};
}  // namespace network
#endif
