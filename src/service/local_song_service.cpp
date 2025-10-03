#include "local_song_service.h"

#include <QVariantMap>
#include <QFileInfo>

LocalSongService::LocalSongService(QObject* parent)
    : QObject{parent} {
  setSeachSongsPaths(QVariantMap()); // init
}

model::MediaItemFilterProxyModel *LocalSongService::mediaItemModel()
{
  return &m_mediaItemsFilterProxyModel;
}

QMap<QString, bool> LocalSongService::variantMapToBoolMap(const QVariantMap &map)
{
  QMap<QString,bool> result;
  for (auto it = map.constKeyValueBegin(); it != map.constKeyValueEnd(); ++it) {
    const auto& [key, value] = *it;
    result[key] = value.toBool();
  }
  return result;
}

QVariantMap LocalSongService::boolMapToVariantMap(const QMap<QString, bool> &map)
{
  QMap<QString,QVariant> result;
  for (auto it = map.constKeyValueBegin(); it != map.constKeyValueEnd(); ++it) {
    const auto& [key, value] = *it;
    result[key] = QVariant::fromValue(value);
  }
  return result;
}
QVariantMap LocalSongService::songsSearchDirs() {
  auto map = m_network.mediasSearchDirs();
  return boolMapToVariantMap(map);
}

void LocalSongService::setSeachSongsPaths(const QVariantMap& map) {
  if(!map.empty())
    m_network.setMediasSearchDirs(variantMapToBoolMap(map));
  QFileInfoList infos = m_network.mediasInSearchDirs();
  QStringList paths;
  for(const QFileInfo& info : infos){
  paths.append(info.path());
  }
  m_mediaMetadataExtractor.processFiles(paths);
  QList<entities::MediaItem> items = m_mediaMetadataExtractor.processResults();

  for(const entities::MediaItem& item : items)
  {
    m_mediaItemsModel.appendItem(item);
  }
}
