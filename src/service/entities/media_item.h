#ifndef MEDIA_ITEM_H
#define MEDIA_ITEM_H
#include <QObject>
#include <QVariantList>
#include "album_data.h"

namespace entities {

struct MediaItem {
  Q_GADGET
  Q_PROPERTY(qulonglong id MEMBER id)
  Q_PROPERTY(QString name MEMBER name)
  Q_PROPERTY(qulonglong duration MEMBER duration)
  Q_PROPERTY(AlbumData album READ album WRITE setAlbum)
  Q_PROPERTY(QVariantList artists MEMBER artists)
  Q_PROPERTY(QString reason MEMBER reason)
  Q_PROPERTY(QUrl url MEMBER url)
  Q_PROPERTY(QVariantList lyrics MEMBER lyrics)
 public:
  AlbumData album() { return albumdata; }
  void setAlbum(const AlbumData& data) { albumdata = data; }
  MediaItem();
  MediaItem(const MediaItem& item) = default;
  MediaItem& operator=(const MediaItem& other);

 public:
  qulonglong id;
  QString name;
  qulonglong duration;
  AlbumData albumdata;
  QVariantList artists;  // QList<AristData> artists
  QString reason;
  QUrl url;
  QVariantList lyrics;
};
}  // namespace entities
#endif  // MEDIA_ITEM_H
