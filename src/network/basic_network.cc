#include "basic_network.h"
#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>

#include <QtNetwork/QNetworkAccessManager>

namespace network {
QNetworkReply* BasicNetwork::get(const QNetworkRequest& request) {
  return m_netAccessManager.get(request);
}

QNetworkReply* BasicNetwork::post(const QNetworkRequest& request,
                                  const QByteArray& data) {
  return m_netAccessManager.post(request, data);
}
}  // namespace network