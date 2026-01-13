#ifndef BASIC_NETWORK_H
#define BASIC_NETWORK_H
#include <QtQml/qqmlengine.h>
#include <qobject.h>
#include <qtmetamacros.h>
#include "network_global.h"

#include <QNetworkAccessManager>

namespace network {
namespace error_code {
NETWORK_DLL_EXPORT Q_NAMESPACE enum ErrorCode {
  NoError = 0,
  ConnectionRefusedError,
  TimeoutError,
  JsonContentError,
  OtherError
};
Q_ENUM_NS(ErrorCode)
}  // namespace error_code

class NETWORK_DLL_EXPORT BasicNetwork : public QObject {
  Q_OBJECT
 public:
  BasicNetwork() = default;
  // QNetworkAccessManager* networkAccessManager() { return m_netAccessManager;}
 protected:
  QNetworkReply* get(const QNetworkRequest&);
  QNetworkReply* post(const QNetworkRequest&, const QByteArray&);

 private:
  static QNetworkAccessManager m_netAccessManager;
};

}  // namespace network
#endif
