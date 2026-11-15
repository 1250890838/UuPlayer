#pragma once

#include <QList>
#include <QString>
#include <QUrl>
#include <QVariantList>

#include "albumitem.h"
#include "aristitem.h"

namespace entities {

struct MediaItem {
  Q_GADGET
  Q_PROPERTY(qulonglong id MEMBER id)
  Q_PROPERTY(QString name MEMBER name)
  Q_PROPERTY(qulonglong duration MEMBER duration)
  Q_PROPERTY(AlbumData album MEMBER albumdata)
  Q_PROPERTY(QList<AristItem> artists MEMBER artists)
  Q_PROPERTY(QString reason MEMBER reason)
  Q_PROPERTY(QUrl url MEMBER url)
  Q_PROPERTY(QVariantList lyrics MEMBER lyrics)

 public:
  qulonglong id = 0;
  QString name;
  qulonglong duration = 0;
  AlbumData albumdata;
  QList<AristItem> artists;
  QString reason;
  QUrl url;
  QVariantList lyrics;

  bool operator==(const MediaItem&) const = default;
};

}  // namespace entities