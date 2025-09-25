#ifndef LOCALSONGSERVICE_H
#define LOCALSONGSERVICE_H

#include <QObject>
#include <QQmlEngine>
#include <QSettings>
#include <QVariantMap>

#include "local_song_network.h"
#include "metadata_extractor.h"

class LocalSongService : public QObject
{
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
  Q_INVOKABLE QVariantMap seachSongsInSetPaths();
  Q_INVOKABLE void setSeachSongsPaths(const QVariantMap& map);
 public:
  explicit LocalSongService(QObject *parent = nullptr);
 private:
  QSettings m_settings;
  network::LocalSongNetwork m_network;
 signals:
  engine::MetaDataExtractor m_mediaMetadataExtractor;
};

#endif // LOCALSONGSERVICE_H
