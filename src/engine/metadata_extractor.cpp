#include "metadata_extractor.h"
#include <QFileInfo>
#include <QDebug>
namespace engine{
MetaDataExtractor::MetaDataExtractor(QObject *parent)
    : QObject{parent}, m_player(new QMediaPlayer(this)), m_currentIndex(0)
{
  connect(m_player, &QMediaPlayer::metaDataChanged, this, &MetaDataExtractor::onMetaDataChanged);
}

MetaDataExtractor::~MetaDataExtractor()
{
}

void MetaDataExtractor::processFiles(const QStringList &filePaths)
{
  m_fileQueue = filePaths;
  m_currentIndex = 0;
  processNextFile();
}

QList<entities::LocalMediaItem> MetaDataExtractor::processResults()
{
  return m_metaDatas;
}

void MetaDataExtractor::processNextFile()
{
  if (m_currentIndex >= m_fileQueue.size()) {
    emit finished();
    return;
  }

  QString path = m_fileQueue.at(m_currentIndex);
  m_player->setSource(QUrl::fromLocalFile(path));
}

void MetaDataExtractor::onMetaDataChanged()
{
  static qlonglong s_local_media_id = -1;
  // struct MediaItem {
  //   qulonglong id;
  //   QString name;
  //   qulonglong duration;
  //   QString albumName;
  //   QStringList artists;
  //   QString dirPath;
  //   qulonglong fileSize;
  // };

  QMediaMetaData metaData = m_player->metaData();
  QString title = metaData.value(QMediaMetaData::Title).toString();
  // QString artist = metaData.value(QMediaMetaData::Author).toString(); // Or Artist
  QString album = metaData.value(QMediaMetaData::AlbumTitle).toString();
  qint64 duration = metaData.value(QMediaMetaData::Duration).toLongLong();
  qint64 date = metaData.value(QMediaMetaData::Date).toLongLong();
  Q_UNUSED(date);
  auto artists = metaData.value(QMediaMetaData::ContributingArtist).toStringList();
  auto path = metaData.value(QMediaMetaData::Url).toUrl().toString();

  entities::LocalMediaItem item{
      .id = s_local_media_id--,
      .name = title,
      .duration = static_cast<qulonglong>(duration),
      .albumName = album,
      .artists = artists,
      .dirPath = path,
      .fileSize = 0

  };
  m_metaDatas.append(item);
  m_currentIndex++;
  processNextFile();
}
}
