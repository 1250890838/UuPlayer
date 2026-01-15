#include "image_provider.h"

#include <QNetworkReply>
#include <QtConcurrent/QtConcurrent>

namespace gui {

NetworkImageResponse::NetworkImageResponse(const QString& id,
                                           network::BasicNetwork* network)
    : m_network(network) {
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
    m_image.loadFromData(data);
    QtConcurrent::run([this, data]() {
      QImage tempImage;
      tempImage.loadFromData(data);
      m_image = tempImage;
      emit finished();
    });
  } else {
    qDebug() << "Network Error:" << m_reply->errorString();
  }
  m_reply->deleteLater();
  m_reply = nullptr;
  emit finished();
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
  Q_UNUSED(requestedSize);
  return new NetworkImageResponse(id, m_network);
}
}  // namespace gui
