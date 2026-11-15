#pragma once

#include <QObject>
#include <QString>
#include <QTimer>

#include "entities/types.h"

namespace core {
class AuthRepository;
}

namespace viewmodel {

class LoginController : public QObject {
  Q_OBJECT
  Q_PROPERTY(bool loggedIn READ isLoggedIn NOTIFY loggedInChanged)

 public:
  LoginController(core::AuthRepository* auth, QObject* parent = nullptr);

  bool isLoggedIn() const { return m_loggedIn; }

  Q_INVOKABLE void startLogin();

 signals:
  void qrCodeImageStatus(error_code::ErrorCode status);
  void qrCodeImageData(const QString& base64Image);
  void loginSuccess();
  void loggedInChanged();

 private slots:
  void onQrKeyReady(error_code::ErrorCode code, const QString& key);
  void onQrImageReady(error_code::ErrorCode code, const QString& base64Image);
  void onScanChecked(error_code::ErrorCode code, int apiCode,
                     const QString& cookie);

 private:
  core::AuthRepository* m_auth = nullptr;
  QTimer m_pollTimer;
  QString m_key;
  bool m_loggedIn = false;
};

}  // namespace viewmodel