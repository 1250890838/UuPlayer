#ifndef SONG_SERVICE_H
#define SONG_SERVICE_H

#include <QObject>

class song_service : public QObject {
  Q_OBJECT
 public:
  explicit song_service(QObject* parent = nullptr);

 signals:
};

#endif  // SONG_SERVICE_H
