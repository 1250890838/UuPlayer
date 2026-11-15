#pragma once

#include <QImage>
#include <QNetworkAccessManager>
#include <QQuickAsyncImageProvider>

namespace ui {

class NetworkImageResponse : public QQuickImageResponse {
  Q_OBJECT
 public:
  NetworkImageResponse(const QString& id, const QSize& requestedSize,
                       QNetworkAccessManager* manager);

  QQuickTextureFactory* textureFactory() const override;

 private:
  QImage m_image;
  QSize m_requestedSize;
};

class ImageProvider : public QQuickAsyncImageProvider {
 public:
  ImageProvider();

  QQuickImageResponse* requestImageResponse(
      const QString& id, const QSize& requestedSize) override;

 private:
  QNetworkAccessManager m_manager;
};

}
