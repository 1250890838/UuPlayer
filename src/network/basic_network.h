#ifndef BASIC_NETWORK_H
#define BASIC_NETWORK_H
#include <QObject>
#include "api_network.h"
#include "network_global.h"
#include "types.h"

#include <QNetworkAccessManager>

namespace network {
template <typename T>
using NetworkReadySignal = void (T::*)(error_code::ErrorCode,
                                       const QByteArray&);

class NETWORK_DLL_EXPORT BasicNetwork : public QObject {
  Q_OBJECT
 public:
  BasicNetwork() = default;
  QNetworkReply* get(const QNetworkRequest&);
  QNetworkReply* post(const QNetworkRequest&, const QByteArray&);

 protected:
  error_code::ErrorCode handleReplyErrorCode(QNetworkReply* reply);

 private:
  static QNetworkAccessManager m_netAccessManager;
};

}  // namespace network
#endif
