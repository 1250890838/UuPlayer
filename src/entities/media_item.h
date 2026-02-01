#ifndef MEDIA_ITEM_H
#define MEDIA_ITEM_H
#include <QObject>
#include <QVariantList>
#include "album_item.h"
#include "arist_item.h"
#include "entities_global.h"

namespace entities {

struct ENTITIES_EXPORT MediaItem {
  Q_GADGET
  Q_PROPERTY(qulonglong id MEMBER id)
  Q_PROPERTY(QString name MEMBER name)
  Q_PROPERTY(qulonglong duration MEMBER duration)
  Q_PROPERTY(AlbumData album MEMBER albumdata)
  Q_PROPERTY(QList<AristItem> artists MEMBER artists CONSTANT)
  Q_PROPERTY(QString reason MEMBER reason)
  Q_PROPERTY(QUrl url MEMBER url)
  Q_PROPERTY(QVariantList lyrics MEMBER lyrics)
 public:
  MediaItem();
  MediaItem(const MediaItem& item) = default;
  MediaItem& operator=(const MediaItem& other);

 public:
  qulonglong id;
  QString name;
  qulonglong duration;
  AlbumData albumdata;
  QList<AristItem> artists;  // QList<AristData> artists
  QString reason;
  QUrl url;
  QVariantList lyrics;
};
}  // namespace entities

Q_DECLARE_METATYPE(QList<entities::MediaItem>)
#endif  // MEDIA_ITEM_H
