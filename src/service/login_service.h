#include <QObject>
#include "service_global.h"

#include "login_network.h"

namespace service {
class SERVICE_DLL_EXPORT LoginService : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
 public:
  Q_INVOKABLE void getQRCodeImage();
 signals:
  void qrCodeImageStatus(network::error_code::ErrorCode);
  void qrCodeImageData(const QString& base64);
 public slots:
  void onGetQRCodeKeyFinished(network::error_code::ErrorCode,
                              const QByteArray& data);
  void onCreateQRCodeImageFinished(network::error_code::ErrorCode,
                                   const QByteArray& data);

 public:
  LoginService(QObject* parent = nullptr);

 private:
  void createQRCodeImage();

 private:
  network::LoginNetwork m_network;
  QString m_key;
};
}  // namespace service