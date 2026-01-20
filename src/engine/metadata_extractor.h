#ifndef METADATAEXTRACTOR_H
#define METADATAEXTRACTOR_H

#include <QMediaMetaData>
#include <QMediaPlayer>
#include <QObject>
#include <QStringList>

#include "local_media_item.h"

namespace engine {

class MetaDataExtractor : public QObject {
  Q_OBJECT
 public:
  explicit MetaDataExtractor(QObject* parent = nullptr);
  ~MetaDataExtractor();

  void processFiles(const QStringList& filePaths);
  QList<entities::LocalMediaItem> processResults();

 signals:
  void finished();

 private slots:
  void onMetaDataChanged();

 private:
  void processNextFile();
  QMediaPlayer* m_player;
  QStringList m_fileQueue;
  int m_currentIndex;
  QList<entities::LocalMediaItem> m_metaDatas;
};
}  // namespace engine
#endif  // METADATAEXTRACTOR_H
