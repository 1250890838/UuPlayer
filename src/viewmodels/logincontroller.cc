#include "logincontroller.h"

#include "repositories/authrepository.h"

namespace viewmodel {

LoginController::LoginController(core::AuthRepository* auth, QObject* parent)
    : QObject(parent), m_auth(auth) {
  m_pollTimer.setInterval(2000);
  connect(&m_pollTimer, &QTimer::timeout, this,
          [this]() { m_auth->checkScan(m_key); });
  connect(m_auth, &core::AuthRepository::qrKeyReady, this,
          &LoginController::onQrKeyReady);
  connect(m_auth, &core::AuthRepository::qrImageReady, this,
          &LoginController::onQrImageReady);
  connect(m_auth, &core::AuthRepository::scanChecked, this,
          &LoginController::onScanChecked);
}

void LoginController::startLogin() {
  m_pollTimer.stop();
  m_key.clear();
  m_auth->requestQrKey();
}

void LoginController::onQrKeyReady(error_code::ErrorCode code,
                                   const QString& key) {
  if (code != error_code::NoError) {
    emit qrCodeImageStatus(code);
    return;
  }
  m_key = key;
  m_auth->requestQrImage(key);
}

void LoginController::onQrImageReady(error_code::ErrorCode code,
                                     const QString& base64Image) {
  if (code != error_code::NoError) {
    emit qrCodeImageStatus(code);
    return;
  }
  emit qrCodeImageStatus(error_code::NoError);
  emit qrCodeImageData(base64Image);
  m_pollTimer.start();
}

void LoginController::onScanChecked(error_code::ErrorCode code, int apiCode,
                                    const QString&) {
  if (code != error_code::NoError) {
    return;
  }
  if (apiCode == 803) {
    m_pollTimer.stop();
    m_loggedIn = true;
    emit loggedInChanged();
    emit loginSuccess();
  } else if (apiCode == 800) {
    m_pollTimer.stop();
    emit qrCodeImageStatus(error_code::OtherError);
  }
}

}  // namespace viewmodel