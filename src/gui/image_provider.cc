#include "image_provider.h"

#include <QNetworkReply>
#include <QtConcurrent/QtConcurrent>

namespace gui {

NetworkImageResponse::NetworkImageResponse(const QString& id,
                                           network::BasicNetwork* network,
                                           QSize requestedSize)
    : m_network(network), m_requestedSize(requestedSize) {
  QUrl url(id);
  QNetworkRequest req(url);
  m_reply = m_network->get(req);
  m_network->connect(m_reply, &QNetworkReply::finished, this,
                     &NetworkImageResponse::handleNetFinished);
  connect(m_reply, &QNetworkReply::errorOccurred, this,
          [this](QNetworkReply::NetworkError) { emit finished(); });
}

void NetworkImageResponse::handleNetFinished() {
  if (m_reply->error() == QNetworkReply::NoError) {
    QByteArray data = m_reply->readAll();
    QtConcurrent::run([this, data]() {
      QImage tempImage;
      tempImage.loadFromData(data);
      if (m_requestedSize.isValid() && !tempImage.isNull()) {
        tempImage = tempImage.scaled(m_requestedSize, Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);
      }
      m_image = tempImage;
      emit finished();
    });
  } else {
    qDebug() << "Network Error:" << m_reply->errorString();
  }
  m_reply->deleteLater();
  m_reply = nullptr;
}

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
