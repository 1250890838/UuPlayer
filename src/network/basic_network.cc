#include "basic_network.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QtNetwork/QNetworkAccessManager>

namespace network {

QNetworkAccessManager BasicNetwork::m_netAccessManager;
QNetworkReply* BasicNetwork::get(const QNetworkRequest& request) {
  return m_netAccessManager.get(request);
}

QNetworkReply* BasicNetwork::post(const QNetworkRequest& request,
                                  const QByteArray& data) {
  return m_netAccessManager.post(request, data);
}

error_code::ErrorCode BasicNetwork::handleReplyErrorCode(QNetworkReply* reply) {
  auto e = reply->error();
  error_code::ErrorCode code;
  switch (e) {
    case QNetworkReply::NoError:
      code = error_code::NoError;
      break;
    case QNetworkReply::ConnectionRefusedError:
      code = error_code::ConnectionRefusedError;
      break;
    case QNetworkReply::TimeoutError:
      code = error_code::TimeoutError;
      break;
    default:
      code = error_code::OtherError;
      break;
  }
  return code;
}
}  // namespace network
