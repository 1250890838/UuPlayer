#pragma once

#include <QList>
#include <QString>
#include <QUrl>
#include <QVariantList>
#include <QtQml/qqmlregistration.h>

#include "albumitem.h"
#include "artistitem.h"

namespace entities {

struct MediaItem {
  Q_GADGET
  QML_VALUE_TYPE(mediaItem)
  Q_PROPERTY(qulonglong id MEMBER id)
  Q_PROPERTY(QString name MEMBER name)
  Q_PROPERTY(qulonglong duration MEMBER duration)
  Q_PROPERTY(AlbumItem album MEMBER album)
  Q_PROPERTY(QList<ArtistItem> artists MEMBER artists)
  Q_PROPERTY(QString reason MEMBER reason)
  Q_PROPERTY(QUrl url MEMBER url)
  Q_PROPERTY(QVariantList lyrics MEMBER lyrics)

 public:
  qulonglong id = 0;
  QString name;
  qulonglong duration = 0;
  AlbumItem album;
  QList<ArtistItem> artists;
  QString reason;
  QUrl url;
  QVariantList lyrics;

  bool operator==(const MediaItem&) const = default;
};

}
