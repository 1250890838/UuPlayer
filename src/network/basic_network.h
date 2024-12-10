#include <QtQml/qqmlengine.h>
#include <qobject.h>
#include <qtmetamacros.h>
#include "network_global.h"

#include <QNetworkAccessManager>
namespace network{
class BasicNetwork : QObject{
    Q_OBJECT
public:
    BasicNetwork() = default;
protected:
    void sendRequest();
private:
    QNetworkAccessManager m_netAccessManager;
} 


}