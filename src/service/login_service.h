#include <QObject>
#include "service_global.h"

#include "login_network.h"

namespace service {
class SERVICE_DLL_EXPORT LoginService : public QObject {
  Q_OBJECT
 public:
  Q_INVOKABLE void getQRCodeImage();
 signals:
  void qrCodeImageStatus();
  void qrCodeImageData(const QByteArray& image);
 public slots:
  void onGetQRCodeKeyFinished(network::error_code::ErrorCode,const QByteArray& data);

 public:
  LoginService(QObject* parent = nullptr);

 private:
  network::LoginNetwork m_network;
};
}  // namespace service