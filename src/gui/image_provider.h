#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H
#endif

#include <QNetworkReply>
#include <QQuickAsyncImageProvider>

#include "basic_network.h"

namespace gui {

class NetworkImageResponse : public QQuickImageResponse {
  Q_OBJECT
 public:
  NetworkImageResponse(const QString& id, network::BasicNetwork* network);
  QQuickTextureFactory* textureFactory() const override;

 public slots:
  void handleNetFinished();

 private:
  network::BasicNetwork* m_network = nullptr;
  QImage m_image;
  QNetworkReply* m_reply;
};

class ImageProvider : public QQuickAsyncImageProvider {
 public:
  ImageProvider();
  ~ImageProvider();
  QQuickImageResponse* requestImageResponse(
      const QString& id, const QSize& requestedSize) override;

 private:
  network::BasicNetwork* m_network = nullptr;
};
}  // namespace gui
