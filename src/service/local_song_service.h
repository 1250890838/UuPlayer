#ifndef LOCALSONGSERVICE_H
#define LOCALSONGSERVICE_H

#include <QObject>
#include <QQmlEngine>
#include <QSettings>
#include <QVariantMap>

#include "local_song_network.h"
#include "metadata_extractor.h"
#include "model/mediaitem_filterproxy_model.h"
#include "model/local_media_item_model.h"

class LocalSongService : public QObject
{
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
  Q_PROPERTY(model::MediaItemFilterProxyModel* mediaItemModel READ mediaItemModel CONSTANT)

  Q_INVOKABLE QVariantMap songsSearchDirs();
  Q_INVOKABLE void setSeachSongsPaths(const QVariantMap& map);
 public:
  explicit LocalSongService(QObject *parent = nullptr);
  model::MediaItemFilterProxyModel* mediaItemModel();
 private:
  QMap<QString,bool> variantMapToBoolMap(const QVariantMap& map);
  QVariantMap boolMapToVariantMap(const QMap<QString,bool>& map);
 private:
  QSettings m_settings;
  network::LocalSongNetwork m_network;
  model::MediaItemFilterProxyModel m_mediaItemsFilterProxyModel;
  model::LocalMediaItemModel m_mediaItemsModel;
  engine::MetaDataExtractor m_mediaMetadataExtractor;
 signals:
};

#endif // LOCALSONGSERVICE_H
