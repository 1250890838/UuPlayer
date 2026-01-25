#ifndef SONGURLSERVICE_H
#define SONGURLSERVICE_H

#include <QObject>

#include "service_global.h"
#include "song_url_network.h"

class SERVICE_DLL_EXPORT SongUrlService : public QObject {
  Q_OBJECT
 public:
  explicit SongUrlService(QObject* parent = nullptr);
 private slots:
  void onReady(error_code::ErrorCode code, const QByteArray& data);
 signals:
  void ready(error_code::ErrorCode code, const QUrl& url);

 private:
  network::SongUrlNetwork m_network;
};

#endif // SONGURLSERVICE_H
