#pragma once

#include <QImage>
#include <QQuickAsyncImageProvider>
#include <QSize>
#include <QString>

#include "imagestore.h"

namespace ui {

class NetworkImageResponse : public QQuickImageResponse {
  Q_OBJECT
 public:
  NetworkImageResponse(const QString& id, ImageStore* store,
                       const QSize& requestedSize);

  QQuickTextureFactory* textureFactory() const override;

 private slots:
  void onReady(const QString& url, const QSize& size);
  void onFailed(const QString& url, const QSize& size,
                const QString& reason);

 private:
  QString m_url;
  QSize m_requestedSize;
  ImageStore* m_store = nullptr;
  QImage m_image;
};

class ImageProvider : public QQuickAsyncImageProvider {
 public:
  explicit ImageProvider(ImageStore* store);

  QQuickImageResponse* requestImageResponse(
      const QString& id, const QSize& requestedSize) override;

 private:
  ImageStore* m_store = nullptr;
};

}  // namespace ui