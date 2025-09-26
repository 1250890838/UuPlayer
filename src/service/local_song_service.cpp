#include "local_song_service.h"

#include <QVariantMap>
#include <QFileInfo>

LocalSongService::LocalSongService(QObject* parent)
    : QObject{parent} {}
QVariantMap LocalSongService::seachSongsInSetPaths() {
  QVariantMap varMap;
  QFileInfoList infos = m_network.mediasInSearchDirs();
  QStringList paths;
  for(const QFileInfo& info : infos){
    paths.append(info.path());
  }
  m_mediaMetadataExtractor.processFiles(paths);
  QList<engine::MetaData> datas = m_mediaMetadataExtractor.processResults();

}

void LocalSongService::setSeachSongsPaths(const QVariantMap& map) {

}
