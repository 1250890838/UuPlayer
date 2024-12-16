#include "login_service.h"

namespace service {
LoginService::LoginService(QObject* parent) : QObject(parent) {
  using namespace network;
  connect(m_network, &LoginNetwork::getQRCodeKeyFinished, this,
          &LoginService::onGetQRCodeKeyFinished);
}

void LoginService::getQRCodeImage() {
  m_network.getQRCodeKey();
}

void LoginService::onGetQRCodeKeyFinished(network::error_code::ErrorCode code,const QByteArray& data) {
}
}  // namespace service