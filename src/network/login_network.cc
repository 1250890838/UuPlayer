#include "login_network.h"

#include "api_network.h"

#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qtypes.h>

namespace network {
QNetworkReply* LoginNetwork::getQRCodeKey() {
  QString timeStamp =
      QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch(), 10);
  QUrl url = QUrl(network_api::apiGetQRCode + "?" + "timestamp=" + timeStamp);
  QNetworkRequest request;
  auto reply = this->get(request);

  connect(reply, &QNetworkReply::finished, this, [reply]() {
    if (reply->error() != QNetworkReply::NoError) {
      qDebug() << "LoginNetWork::getQRCodeKey get error code : "
               << reply->error() << " " << reply->errorString();
    }
    else{
      qDebug() << "LoginNetWork::getQRCodeKey get success";
      QByteArray data = reply->readAll();
      QString str(data);
      qDebug() << "LoginNetWork::getQRCodeKey get response : " << str;
    }
  }
    );
}
}  // namespace network