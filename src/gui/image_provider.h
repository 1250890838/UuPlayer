#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickAsyncImageProvider>
#include <QQuickImageResponse>
#include <QQuickTextureFactory>
#include <QObject>
#include <QImage>
#include <QSize>

#include "image_store.h"

namespace gui {

class NetworkImageResponse : public QQuickImageResponse {
  Q_OBJECT
 public:
  NetworkImageResponse(const QString& id, ImageStore* store, QSize requestedSize);
  QQuickTextureFactory* textureFactory() const override;

 private slots:
  void onReady(const QString& url, const QSize& size);
  void onFailed(const QString& url, const QSize& size, const QString& reason);

 private:
  QString m_url;
  QSize m_requestedSize;
  ImageStore* m_store = nullptr; // 不拥有
  QImage m_image;
};

class ImageProvider : public QQuickAsyncImageProvider {
 public:
  explicit ImageProvider(ImageStore* store);
  QQuickImageResponse* requestImageResponse(const QString& id,
                                            const QSize& requestedSize) override;

 private:
  ImageStore* m_store = nullptr; // 不拥有
};

}  // namespace gui

#endif // IMAGEPROVIDER_H
