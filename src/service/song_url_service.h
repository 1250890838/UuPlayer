#ifndef SONGURLSERVICE_H
#define SONGURLSERVICE_H

#include <QObject>

#include "song_url_network.h"

class SongUrlService : public QObject
{
  Q_OBJECT
 public:
  explicit SongUrlService(QObject* parent = nullptr);

 private:
  network::SongUrlNetwork m_network;
};

#endif // SONGURLSERVICE_H
