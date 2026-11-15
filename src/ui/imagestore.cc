#include "imagestore.h"

#include <QtConcurrent>

#include "apiclient.h"

namespace ui {

ImageStore::ImageStore(core::ApiClient* api, QObject* parent)
    : QObject(parent), m_api(api) {}

bool ImageStore::has(const QString& url, const QSize& requestedSize) const {
  QMutexLocker locker(&m_mutex);
  return m_cache.contains(ImageKey{url, requestedSize});
}

QImage ImageStore::get(const QString& url, const QSize& requestedSize) const {
  QMutexLocker locker(&m_mutex);
  return m_cache.value(ImageKey{url, requestedSize});
}

void ImageStore::request(const QString& url, const QSize& requestedSize) {
  const ImageKey key{url, requestedSize};
  {
    QMutexLocker locker(&m_mutex);
    if (m_cache.contains(key)) {
      QMetaObject::invokeMethod(
          this,
          [this, url, requestedSize]() { emit imageReady(url, requestedSize); },
          Qt::QueuedConnection);
      return;
    }
    if (m_inFlight.value(key, false)) {
      return;
    }
    m_inFlight.insert(key, true);
  }
  startNetworkRequest(key);
}

void ImageStore::startNetworkRequest(const ImageKey& key) {
  if (!m_api) {
    emit imageFailed(key.url, key.size, QStringLiteral("ApiClient is null"));
    return;
  }

  QNetworkReply* reply = m_api->getRaw(QUrl(key.url));
  connect(reply, &QNetworkReply::finished, this, [this, reply, key]() {
    const auto doneCleanup = [this, key]() {
      QMutexLocker locker(&m_mutex);
      m_inFlight.remove(key);
    };

    if (reply->error() != QNetworkReply::NoError) {
      const QString reason = reply->errorString();
      doneCleanup();
      emit imageFailed(key.url, key.size, reason);
      reply->deleteLater();
      return;
    }

    const QByteArray data = reply->readAll();
    reply->deleteLater();

    auto future = QtConcurrent::task([data, key]() -> QImage {
                    QImage image;
                    image.loadFromData(data);
                    if (key.size.isValid() && !image.isNull()) {
                      image = image.scaled(key.size, Qt::KeepAspectRatio,
                                           Qt::SmoothTransformation);
                    }
                    return image;
                  })
                      .withPriority(QThread::HighPriority)
                      .spawn();

    future.then(this, [this, key, doneCleanup](const QImage& image) {
      doneCleanup();
      if (image.isNull()) {
        emit imageFailed(key.url, key.size,
                         QStringLiteral("Decoded image is null"));
        return;
      }
      {
        QMutexLocker locker(&m_mutex);
        m_cache.insert(key, image);
      }
      emit imageReady(key.url, key.size);
    });
  });
}

}  // namespace ui