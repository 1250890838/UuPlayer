#include "imageprovider.h"

namespace ui {

NetworkImageResponse::NetworkImageResponse(const QString& id,
                                           ImageStore* store,
                                           const QSize& requestedSize)
    : m_url(id), m_requestedSize(requestedSize), m_store(store) {
  if (m_store->has(m_url, m_requestedSize)) {
    m_image = m_store->get(m_url, m_requestedSize);
    emit finished();
    return;
  }
  connect(m_store, &ImageStore::imageReady, this,
          &NetworkImageResponse::onReady);
  connect(m_store, &ImageStore::imageFailed, this,
          &NetworkImageResponse::onFailed);
  m_store->request(m_url, m_requestedSize);
}

void NetworkImageResponse::onReady(const QString& url, const QSize& size) {
  if (url != m_url || size != m_requestedSize) {
    return;
  }
  m_image = m_store->get(url, size);
  emit finished();
}

void NetworkImageResponse::onFailed(const QString& url, const QSize& size,
                                    const QString&) {
  if (url != m_url || size != m_requestedSize) {
    return;
  }
  emit finished();
}

QQuickTextureFactory* NetworkImageResponse::textureFactory() const {
  return QQuickTextureFactory::textureFactoryForImage(m_image);
}

ImageProvider::ImageProvider(ImageStore* store) : m_store(store) {}

QQuickImageResponse* ImageProvider::requestImageResponse(
    const QString& id, const QSize& requestedSize) {
  return new NetworkImageResponse(id, m_store, requestedSize);
}

}  // namespace ui