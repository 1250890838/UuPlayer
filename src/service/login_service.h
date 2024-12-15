#include <QObject>

class LoginService : public QObject {
    Q_OBJECT
public:
    LoginService(QObject* parent = nullptr);
    Q_INVOKABLE void getQRCodeImage();
    Q_INVOKABLE void checkLoginStatus();
}