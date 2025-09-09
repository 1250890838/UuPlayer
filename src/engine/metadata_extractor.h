#ifndef METADATAEXTRACTOR_H
#define METADATAEXTRACTOR_H

#include <QObject>
#include <QStringList>
#include <QMediaPlayer>
#include <QMediaMetaData>
namespace engine{

struct MetaData{
  QString title;
  QString author;
  QString albumTitle;
  qint64 duration;
  qint64 date;
};

class MetaDataExtractor : public QObject
{
  Q_OBJECT
 public:
  explicit MetaDataExtractor(QObject *parent = nullptr);
  ~MetaDataExtractor();

  void processFiles(const QStringList &filePaths);

 signals:
  void finished();

 private slots:
  void onMetaDataChanged();

 private:
  void processNextFile();
  QMediaPlayer* m_player;
  QStringList m_fileQueue;
  int m_currentIndex;
  QList<MetaData> m_metaDatas
};
}
#endif // METADATAEXTRACTOR_H
