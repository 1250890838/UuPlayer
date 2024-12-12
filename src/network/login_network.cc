#include "login_network.h"

#include "api_network.h"

#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <qnetworkreply.h>
#include <qtypes.h>

namespace network {
QNetworkReply* LoginNetwork::getQRCodeKey() {
    QString timeStamp = QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch(),10);
    QUrl url=QUrl(network_api::apiGetQRCode + "?" +"timestamp=" + timeStamp);
    QNetworkRequest request;
    auto reply=this->get(request);
    //connect(reply, &QNetworkReply::readyRead, this, &LoginNetwork::onReadyRead);
    connect(reply, &QNetworkReply::errorOccurred,
         this, [](QNetworkReply::NetworkError error){
            switch (error) {
                
            }
         });
    connect(reply, &QNetworkReply::sslErrors,
         this, &LoginNetwork::slotSslErrors);
}
}  // namespace network