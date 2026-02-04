#ifndef GUI_IMAGE_STORE_H
#define GUI_IMAGE_STORE_H

#include <QObject>
#include <QImage>
#include <QPointer>
#include <QHash>
#include <QMutex>
#include <QSize>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

#include "basic_network.h"

namespace gui {

struct ImageKey {
  QString url;
  QSize size;
};

inline bool operator==(const ImageKey &a, const ImageKey &b) {
  return a.url == b.url && a.size == b.size;
}

inline size_t qHash(const ImageKey& k, size_t seed = 0) noexcept {
  seed = qHash(k.url, seed);
  const size_t w = static_cast<size_t>(k.size.width());
  const size_t h = static_cast<size_t>(k.size.height());
  seed ^= w + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
  seed ^= h + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
  return seed;
}

class ImageStore : public QObject {
  Q_OBJECT
 public:
  explicit ImageStore(network::BasicNetwork* net, QObject* parent = nullptr);

  Q_INVOKABLE void request(const QString& url, const QSize& requestedSize = QSize());

  bool has(const QString& url, const QSize& requestedSize = QSize()) const;
  QImage get(const QString& url, const QSize& requestedSize = QSize()) const;

 signals:
  void imageReady(const QString& url, const QSize& requestedSize);
  void imageFailed(const QString& url, const QSize& requestedSize, const QString& reason);

 private:
  void startNetworkRequest(const ImageKey& key);

  network::BasicNetwork* m_net = nullptr;
  mutable QMutex m_mutex;

  QHash<ImageKey, QImage> m_cache;
  QHash<ImageKey, bool> m_inFlight;
};

} // namespace gui

#endif // GUI_IMAGE_STORE_H
