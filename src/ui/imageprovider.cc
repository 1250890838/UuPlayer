#include "imageprovider.h"

#include <QNetworkReply>
#include <QNetworkRequest>

namespace ui {

NetworkImageResponse::NetworkImageResponse(const QString& id,
                                           const QSize& requestedSize,
                                           QNetworkAccessManager* manager)
    : m_requestedSize(requestedSize) {
  QNetworkReply* reply = manager->get(QNetworkRequest(QUrl(id)));
  connect(reply, &QNetworkReply::finished, this, [this, reply]() {
    reply->deleteLater();
    if (reply->error() == QNetworkReply::NoError) {
      QImage image;
      if (image.loadFromData(reply->readAll()) && m_requestedSize.isValid()) {
        image = image.scaled(m_requestedSize, Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
      }
      m_image = image;
    }
    emit finished();
  });
}

QQuickTextureFactory* NetworkImageResponse::textureFactory() const {
  return QQuickTextureFactory::textureFactoryForImage(m_image);
}

ImageProvider::ImageProvider() = default;

QQuickImageResponse* ImageProvider::requestImageResponse(
    const QString& id, const QSize& requestedSize) {
  return new NetworkImageResponse(id, requestedSize, &m_manager);
}

}
