#ifndef BASIC_NETWORK_H
#define BASIC_NETWORK_H
#include <QtQml/qqmlengine.h>
#include <qobject.h>
#include <qtmetamacros.h>
#include "network_global.h"
#include "types.h"

#include <QNetworkAccessManager>
using namespace entities;

namespace network {

class NETWORK_DLL_EXPORT BasicNetwork : public QObject {
  Q_OBJECT
 public:
  BasicNetwork() = default;
  QNetworkReply* get(const QNetworkRequest&);
  QNetworkReply* post(const QNetworkRequest&, const QByteArray&);

 private:
  static QNetworkAccessManager m_netAccessManager;
};

}  // namespace network
#endif
