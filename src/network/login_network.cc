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
  QUrl url = QUrl(QString("%1?timestamp=%2")
                      .arg(network_api::apiGetQRCode, timeStamp));
  qDebug() << url;
  QNetworkRequest request;
  request.setUrl(url);
  auto reply = this->get(request);

  connect(reply, &QNetworkReply::finished, this, [reply, this]() {
    auto e = reply->error();
    if (e != QNetworkReply::NoError) {
      if (e == QNetworkReply::NetworkError::ConnectionRefusedError) {
        emit getQRCodeKeyFinished(error_code::ConnectionRefusedError,
                                  QByteArray());
      } else {
        emit this->getQRCodeKeyFinished(error_code::TimeoutError, QByteArray());
      }

    } else {
      QByteArray data = reply->readAll();
      emit this->getQRCodeKeyFinished(error_code::NoError, data);
    }
  });
}

void LoginNetwork::createQRCode(const QString& key) {
  QString timeStamp =
      QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch(), 10);
  QUrl url = QUrl(QString("%1?key=%2&qrimg=true&timestamp=%3")
                      .arg(network_api::apiCreateQRCode, key, timeStamp));
  QNetworkRequest request;
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply, this]() {
    if (reply->error() != QNetworkReply::NoError) {
      if (reply->error() ==
          QNetworkReply::NetworkError::ConnectionRefusedError) {
        emit createQRCodeFinished(error_code::ConnectionRefusedError,
                                  QByteArray());
      } else {
        emit this->createQRCodeFinished(error_code::TimeoutError, QByteArray());
      }
      qDebug() << "LoginNetWork::createQRCode get error code : "
               << reply->error() << " " << reply->errorString();
    } else {
      qDebug() << "LoginNetWork::getQRCodeKey get success";
      QByteArray data = reply->readAll();
      emit this->createQRCodeFinished(error_code::NoError, data);
      QString str(data);
      qDebug() << "LoginNetWork::createQRCodeKey get response : " << str;
    }
  });
}

void LoginNetwork::checkQRCodeScan(const QString& key) {
  QString timeStamp =
      QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch(), 10);
  QUrl url = QUrl(QString("%1?key=%2&timestamp=%3")
                      .arg(network_api::apiCheckQRCode, key, timeStamp));
  QNetworkRequest request;
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply, this]() {
    if (reply->error() != QNetworkReply::NoError) {
      if (reply->error() ==
          QNetworkReply::NetworkError::ConnectionRefusedError) {
        emit checkQRCodeScanFinished(error_code::ConnectionRefusedError,
                                     QByteArray());
      } else {
        emit this->checkQRCodeScanFinished(error_code::TimeoutError,
                                           QByteArray());
      }
      qDebug() << "LoginNetWork::checkQRCode get error code : "
               << reply->error() << " " << reply->errorString();
    } else {
      qDebug() << "LoginNetWork::checkQRCode get success";
      QByteArray data = reply->readAll();
      emit this->checkQRCodeScanFinished(error_code::NoError, data);
      QString str(data);
      qDebug() << "LoginNetWork::checkQRCode get response : " << str;
    }
  });
}
}  // namespace network
