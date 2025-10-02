#ifndef METADATAEXTRACTOR_H
#define METADATAEXTRACTOR_H

#include <QObject>
#include <QStringList>
#include <QMediaPlayer>
#include <QMediaMetaData>

#include "service/entities/local_media_item.h"

namespace engine{

class MetaDataExtractor : public QObject
{
  Q_OBJECT
 public:
  explicit MetaDataExtractor(QObject *parent = nullptr);
  ~MetaDataExtractor();

  void processFiles(const QStringList &filePaths);
  QList<entities::MediaItem> processResults();

 signals:
  void finished();

 private slots:
  void onMetaDataChanged();

 private:
  void processNextFile();
  QMediaPlayer* m_player;
  QStringList m_fileQueue;
  int m_currentIndex;
  QList<entities::MediaItem> m_metaDatas;
};
}
#endif // METADATAEXTRACTOR_H
