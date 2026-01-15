#include "image_provider.h"
#include <QCoreApplication>  // 用于获取主线程上下文（如果需要），这里直接用 network 对象即可
#include <QNetworkReply>
#include <QtConcurrent>

namespace gui {

NetworkImageResponse::NetworkImageResponse(const QString& id,
                                           network::BasicNetwork* network,
                                           QSize requestedSize)
    : m_requestedSize(requestedSize) {
  QUrl url(id);
  QNetworkRequest req(url);
  QMetaObject::invokeMethod(
      network,
      [this, req, network]() {
        QNetworkReply* reply = network->get(req);
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
          if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QtConcurrent::run([this, data]() {
              QImage tempImage;
              tempImage.loadFromData(data);
              if (m_requestedSize.isValid() && !tempImage.isNull()) {
                tempImage =
                    tempImage.scaled(m_requestedSize, Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);
              }
              m_image = tempImage;
              emit finished();
            });
          } else {
            qDebug() << "Network Error:" << reply->errorString();
            emit finished();
          }
          reply->deleteLater();
        });
      },
      Qt::QueuedConnection);
}

void NetworkImageResponse::handleNetFinished() {}

QQuickTextureFactory* NetworkImageResponse::textureFactory() const {
  return QQuickTextureFactory::textureFactoryForImage(m_image);
}

ImageProvider::ImageProvider() : m_network(new network::BasicNetwork()) {}

ImageProvider::~ImageProvider() {
  delete m_network;
}

QQuickImageResponse* ImageProvider::requestImageResponse(
    const QString& id, const QSize& requestedSize) {
  return new NetworkImageResponse(id, m_network, requestedSize);
}

}  // namespace gui
