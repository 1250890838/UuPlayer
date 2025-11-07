#ifndef LOCAL_MEDIA_ITEM_H
#define LOCAL_MEDIA_ITEM_H
#include <QString>
#include <QStringList>

namespace entities {

struct LocalMediaItem {
  qlonglong id;
  QString name;
  qulonglong duration;
  QString albumName;
  QStringList artists;
  QString dirPath;
  qulonglong fileSize;
};
}
#endif // LOCAL_MEDIA_ITEM_H
