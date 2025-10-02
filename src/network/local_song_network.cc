#include "local_song_network.h"

#include <QDir>
#include <QStandardPaths>

namespace network {

LocalSongNetwork::LocalSongNetwork() : m_settings("uu", "mediaplayer", this) {
  // init setting
  if (!m_settings.beginReadArray("MediaSearchDirs")) {
    m_settings.endArray();
    m_settings.beginWriteArray("MediaSearchDirs");
    QString musicPath =
        QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    QString downloadPath =
        QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    m_settings.setArrayIndex(0);
    m_settings.setValue("searchDir", musicPath);
    m_settings.setValue("isSearched", true);
    m_settings.setArrayIndex(1);
    m_settings.setValue("searchDir", downloadPath);
    m_settings.setValue("isSearched", true);
  }
}

QFileInfoList LocalSongNetwork::mediasInSearchDirs() {
  int size = m_settings.beginReadArray("MediaSearchDirs");
  QStringList dirs;
  for (int i = 0; i < size; i++) {
    m_settings.setArrayIndex(i);
    bool isSearched = m_settings.value("isSearched").toBool();
    if (isSearched) {
      QString dir = m_settings.value("searchDir").toString();
      dirs.append(dir);
    }
  }
  m_settings.endArray();
  QFileInfoList result;
  for (const QString& str : dirs) {
    QDir dir(str);
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    dir.setNameFilters({"*.mp3", "*.wav", "*.flac", "*.ogg"});
    QFileInfoList fileInfoList = dir.entryInfoList();
    result.append(fileInfoList);
  }
  return result;
}

void LocalSongNetwork::setMediasSearchDirs(const QMap<QString, bool> &map)
{
  m_settings.beginWriteArray("MediaSearchDirs");
  QMap<QString, bool>::const_iterator v;
  int i = 0;
  for (v = map.constBegin(); v != map.constEnd(); ++v) {
    m_settings.setArrayIndex(i++);
    m_settings.setValue("isSearched",v.value());
    m_settings.setValue("searchDir",v.key());
  }
  m_settings.endArray();
}

QMap<QString, bool> LocalSongNetwork::mediasSearchDirs()
{
  int size = m_settings.beginReadArray("MediaSearchDirs");
  QMap<QString,bool> result;
  for (int i = 0; i < size; i++) {
    m_settings.setArrayIndex(i);
    bool isSearched = m_settings.value("isSearched").toBool();
    QString dir = m_settings.value("searchDir").toString();
    result[dir] = isSearched;
  }
  m_settings.endArray();
  return result;
}
}  // namespace network
