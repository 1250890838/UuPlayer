#include "local_song_network.h"

#include <QDir>
namespace network{

LocalSongNetwork::LocalSongNetwork():m_settings("uu", "mediaplayer", this)
{

}

QFileInfoList LocalSongNetwork::mediasInSearchDirs()
{
  m_settings.beginGroup("MediasSearchDirs");
  QStringList keys = m_settings.childKeys();
  QStringList dirs;
  for(const QString& key:keys){
    if(m_settings.value(key).toBool())
      dirs.append(key);
  }
  m_settings.endGroup();
  QFileInfoList result;
  for(const QString& str:dirs){
    QDir dir(str);
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setNameFilters({"*.mp3","*.wav","*.flac","*.ogg"});
    QFileInfoList fileInfoList = dir.entryInfoList();
    result.append(fileInfoList);
  }
  return result;
}
}

