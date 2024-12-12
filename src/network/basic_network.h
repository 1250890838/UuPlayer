#include <QtQml/qqmlengine.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <qobject.h>
#include <qtmetamacros.h>
#include "network_global.h"

#include <QNetworkAccessManager>
namespace network {
class NETWORK_DLL_EXPORT BasicNetwork : public QObject {
  Q_OBJECT
 public:
  BasicNetwork() = default;
 // QNetworkAccessManager* networkAccessManager() { return m_netAccessManager;}
 protected:
  QNetworkReply* get(const QNetworkRequest&);
  QNetworkReply* post(const QNetworkRequest&, const QByteArray&);
 private:
  QNetworkAccessManager m_netAccessManager;
};

}  // namespace network