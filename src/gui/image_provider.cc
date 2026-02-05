#include "image_provider.h"

#include <QMetaObject>
#include <QDebug>

namespace gui {

NetworkImageResponse::NetworkImageResponse(const QString& id, ImageStore* store, QSize requestedSize)
    : m_url(id), m_requestedSize(requestedSize), m_store(store) {
  QObject::connect(m_store, &ImageStore::imageReady, this, &NetworkImageResponse::onReady);
  QObject::connect(m_store, &ImageStore::imageFailed, this, &NetworkImageResponse::onFailed);
  m_store->request(m_url, m_requestedSize);
}

void NetworkImageResponse::onReady(const QString& url, const QSize& size) {
  if (url != m_url || size != m_requestedSize) return;
  m_image = m_store->get(m_url, m_requestedSize);
  QMetaObject::invokeMethod(this, [this]() { emit finished(); }, Qt::QueuedConnection);
}

void NetworkImageResponse::onFailed(const QString& url, const QSize& size, const QString& reason) {
  if (url != m_url || size != m_requestedSize) return;
  qDebug() << "ImageProvider failed:" << reason << "url=" << m_url;
  QMetaObject::invokeMethod(this, [this]() { emit finished(); }, Qt::QueuedConnection);
}

QQuickTextureFactory* NetworkImageResponse::textureFactory() const {
  return QQuickTextureFactory::textureFactoryForImage(m_image);
}

ImageProvider::ImageProvider(ImageStore* store) : m_store(store) {}

QQuickImageResponse* ImageProvider::requestImageResponse(const QString& id,
                                                         const QSize& requestedSize) {
  return new NetworkImageResponse(id, m_store, requestedSize);
}

} // namespace gui
