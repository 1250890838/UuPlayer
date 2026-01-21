#include <QObject>
#include "service_global.h"

#include "login_network.h"

namespace service {

// 获取登录相关服务
class SERVICE_DLL_EXPORT LoginService : public QObject {
  Q_OBJECT
 public:
  void getQRCodeImage();
 signals:
  void qrCodeImageStatus(network::error_code::ErrorCode);
  void qrCodeImageData(const QString& base64);
  void loginSuccess();
 public slots:
  void onGetQRCodeKeyFinished(network::error_code::ErrorCode,
                              const QByteArray& data);
  void onCreateQRCodeImageFinished(network::error_code::ErrorCode,
                                   const QByteArray& data);
  void onCheckQRCodeScanStatusFinished(network::error_code::ErrorCode,
                                       const QByteArray& data);

 public:
  LoginService(QObject* parent = nullptr);

 private:
  void createQRCodeImage();
  void checkQRCodeScanStatus();

 private:
  network::LoginNetwork m_network;
  QString m_key;
  QString m_cookie;
};
}  // namespace service
