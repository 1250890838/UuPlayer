#include "login_service.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

namespace service {
LoginService::LoginService(QObject* parent) : QObject(parent) {
  connect(&m_network, &network::LoginNetwork::getQRCodeKeyFinished, this,
          &LoginService::onGetQRCodeKeyFinished);
}

void LoginService::getQRCodeImage() {
  m_network.getQRCodeKey();
}

void LoginService::onGetQRCodeKeyFinished(network::error_code::ErrorCode code,
                                          const QByteArray& data) {
  if (code != network::error_code::ErrorCode::NoError) {
    emit qrCodeImageStatus(code);
    return;
  }
  QJsonDocument doc = QJsonDocument::fromJson(data);
  if (!doc.isNull()) {
    emit qrCodeImageStatus(network::error_code::ErrorCode::JsonContentError);
    return;
  }

  QJsonObject obj = doc.object();
  auto jsonCode = obj["code"].toInt(0);
  if (jsonCode != 200) {
    emit qrCodeImageStatus(network::error_code::ErrorCode::JsonContentError);
    return;
  } 

  auto unikey=obj["data"].toObject()["unikey"].toString();
}

}  // namespace service
