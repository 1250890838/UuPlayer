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
}  // namespace network
