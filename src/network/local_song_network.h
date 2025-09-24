#ifndef LOCAL_SONG_NETWORK_H
#define LOCAL_SONG_NETWORK_H

#include <QObject>
#include <QStringList>
#include <QFileInfoList>
#include <QSettings>

namespace network{
class LocalSongNetwork : public QObject
{
  Q_OBJECT
 public:
  LocalSongNetwork();
  QFileInfoList mediasInSearchDirs();
  void setSearchDirs(const QMap<QString,bool>& map);
 private:
  QSettings m_settings;
};
}
#endif // LOCAL_SONG_NETWORK_H
