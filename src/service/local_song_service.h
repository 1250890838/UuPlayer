#ifndef LOCALSONGSERVICE_H
#define LOCALSONGSERVICE_H

#include <QObject>
#include <QQmlEngine>
#include <QSettings>
#include <QVariantMap>

#include "local_song_network.h"
#include "metadata_extractor.h"
#include "model/mediaitem_filterproxy_model.h"

namespace service {
class LocalSongService : public QObject {
  Q_OBJECT
 public:
  QVariantMap songsSearchDirs();
  void setSearchSongsPaths(const QVariantMap& map);

 public:
  explicit LocalSongService(QObject* parent = nullptr);
  model::MediaItemFilterProxyModel* mediaItemModel();
  void clearSearchDirs();

 private:
  QMap<QString, bool> variantMapToBoolMap(const QVariantMap& map);
  QVariantMap boolMapToVariantMap(const QMap<QString, bool>& map);

 private:
  QSettings m_settings;
  network::LocalSongNetwork m_network;
  engine::MetaDataExtractor m_mediaMetadataExtractor;
 signals:
};
}  // namespace service
#endif  // LOCALSONGSERVICE_H
