#include "image_store.h"

#include <QDebug>
#include <QtConcurrent>

namespace gui {

using namespace network;
ImageStore::ImageStore(network::BasicNetwork* net, QObject* parent)
    : QObject(parent), m_net(net) {}

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
  if (!m_net) {
    emit imageFailed(key.url, key.size, QStringLiteral("Network is null"));
    return;
  }
  QUrl qurl(key.url);
  QNetworkRequest req(qurl);
  QMetaObject::invokeMethod(
      m_net,
      [this, req, key]() {
        QNetworkReply* reply = m_net->get(req);
        QObject::connect(
            reply, &QNetworkReply::finished, this, [this, reply, key]() {
              const auto doneCleanup = [this, key]() {
                QMutexLocker locker(&m_mutex);
                m_inFlight.remove(key);
              };

              if (reply->error() != QNetworkReply::NoError) {
                const QString reason = reply->errorString();
                qDebug() << "ImageStore network error:" << reason
                         << "url=" << key.url;
                doneCleanup();
                emit imageFailed(key.url, key.size, reason);
                reply->deleteLater();
                return;
              }
              const QByteArray data = reply->readAll();
              reply->deleteLater();
              auto future = QtConcurrent::task([data, key]() -> QImage {
                              QImage img;
                              img.loadFromData(data);
                              if (key.size.isValid() && !img.isNull()) {
                                img = img.scaled(key.size, Qt::KeepAspectRatio,
                                                 Qt::SmoothTransformation);
                              }
                              return img;
                            })
                                .withPriority(QThread::HighPriority)
                                .spawn();
              future.then(this, [this, key, doneCleanup](const QImage& img) {
                doneCleanup();
                if (img.isNull()) {
                  emit imageFailed(key.url, key.size,
                                   QStringLiteral("Decoded image is null"));
                  return;
                }
                {
                  QMutexLocker locker(&m_mutex);
                  m_cache.insert(key, img);
                }
                emit imageReady(key.url, key.size);
              });
            });
      },
      Qt::QueuedConnection);
}

}  // namespace gui
