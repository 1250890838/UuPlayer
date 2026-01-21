#ifndef PLAYLISTTRACKSSERVICE_H
#define PLAYLISTTRACKSSERVICE_H

#include <QObject>

class PlaylistTracksService : public QObject
{
  Q_OBJECT
 public:
  explicit PlaylistTracksService(QObject *parent = nullptr);

 signals:

};

#endif // PLAYLISTTRACKSSERVICE_H
