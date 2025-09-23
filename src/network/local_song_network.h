#ifndef LOCAL_SONG_NETWORK_H
#define LOCAL_SONG_NETWORK_H

#include <QObject>
#include <QStringList>

class LocalSongNetwork : public QObject
{
  Q_OBJECT
 public:
  LocalSongNetwork();
//  void setSearchPaths(const QStringList& paths);

};

#endif // LOCAL_SONG_NETWORK_H
