#include "login_service.h"
#include <qthread.h>
#include <qtimer.h>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QThread>
#include <QTimer>

namespace service {
LoginService::LoginService(QObject* parent) : QObject(parent) {
  connect(&m_network, &network::LoginNetwork::getQRCodeKeyFinished, this,
          &LoginService::onGetQRCodeKeyFinished);
  connect(&m_network, &network::LoginNetwork::createQRCodeFinished, this,
          &LoginService::onCreateQRCodeImageFinished);
  connect(&m_network, &network::LoginNetwork::checkQRCodeScanFinished, this,
          &LoginService::onCheckQRCodeScanStatusFinished);
}

void LoginService::getQRCodeImage() {
  m_network.getQRCodeKey();
}

void LoginService::createQRCodeImage() {
  m_network.createQRCode(m_key);
}

void LoginService::checkQRCodeScanStatus() {
  m_network.checkQRCodeScan(m_key);
}

void LoginService::onGetQRCodeKeyFinished(network::error_code::ErrorCode code,
                                          const QByteArray& data) {
  if (code != network::error_code::ErrorCode::NoError) {
    emit qrCodeImageStatus(code);
    return;
  }
  QJsonDocument doc = QJsonDocument::fromJson(data);
  if (doc.isNull()) {
    emit qrCodeImageStatus(network::error_code::ErrorCode::JsonContentError);
    return;
  }

  QJsonObject obj = doc.object();
  auto jsonCode = obj["code"].toInt(0);
  if (jsonCode != 200) {
    emit qrCodeImageStatus(network::error_code::ErrorCode::JsonContentError);
    return;
  }

  auto unikey = obj["data"].toObject()["unikey"].toString();
  m_key = unikey;
  createQRCodeImage();
}

void LoginService::onCreateQRCodeImageFinished(
    network::error_code::ErrorCode code, const QByteArray& data) {
  if (code != network::error_code::ErrorCode::NoError) {
    emit qrCodeImageStatus(code);
    return;
  }
  QJsonDocument doc = QJsonDocument::fromJson(data);
  if (doc.isNull()) {
    emit qrCodeImageStatus(network::error_code::ErrorCode::JsonContentError);
    return;
  }
  QJsonObject obj = doc.object();
  auto jsonCode = obj["code"].toInt(0);
  if (jsonCode != 200) {
    emit qrCodeImageStatus(network::error_code::ErrorCode::JsonContentError);
    return;
  }

  auto img = obj["data"].toObject()["qrimg"].toString();
  emit qrCodeImageStatus(network::error_code::ErrorCode::NoError);
  emit qrCodeImageData(img);
  checkQRCodeScanStatus();
}

void LoginService::onCheckQRCodeScanStatusFinished(
    network::error_code::ErrorCode code, const QByteArray& data) {
  if (code != network::error_code::ErrorCode::NoError) {
    return;
  }
  QJsonDocument doc = QJsonDocument::fromJson(data);
  if (doc.isNull()) {
    return;
  }

  QJsonObject obj = doc.object();
  auto jsonCode = obj["code"].toInt(0);
  if (jsonCode == 803) {
    auto cookie = obj["cookie"].toString();
    m_cookie = cookie;
    emit loginSuccess();
  } else {
    QTimer::singleShot(3000, [this]() { checkQRCodeScanStatus(); });
  }
}

}  // namespace service
