#include "login_network.h"

#include "api_network.h"

#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qtenvironmentvariables.h>
#include <qtypes.h>

namespace network {
void LoginNetwork::getQRCodeKey() {
  QString timeStamp =
      QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch(), 10);
  QUrl url = QUrl(network_api::apiGetQRCode + "?" + "timestamp=" + timeStamp);
  QNetworkRequest request;
  auto reply = this->get(request);

  connect(reply, &QNetworkReply::finished, this, [reply, this]() {
    if (reply->error() != QNetworkReply::NoError) {
      if(reply->error()==QNetworkReply::NetworkError::ConnectionRefusedError){
        emit getQRCodeKeyFinished(error_code::ConnectionRefusedError, QByteArray());
      }else{
        emit getQRCodeKeyFinished(error_code::TimeoutError, QByteArray());
      }
      qDebug() << "LoginNetWork::getQRCodeKey get error code : "
               << reply->error() << " " << reply->errorString();
    } else {
      qDebug() << "LoginNetWork::getQRCodeKey get success";
      QByteArray data = reply->readAll();
      emit getQRCodeKeyFinished(error_code::NoError, data);
      QString str(data);
      qDebug() << "LoginNetWork::getQRCodeKey get response : " << str;
    }
  });
}
}  // namespace network