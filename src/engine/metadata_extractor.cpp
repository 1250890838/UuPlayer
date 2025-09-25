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

QList<MetaData> MetaDataExtractor::processResults()
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
  QMediaMetaData metaData = m_player->metaData();
  QString title = metaData.value(QMediaMetaData::Title).toString();
  QString artist = metaData.value(QMediaMetaData::Author).toString(); // Or Artist
  QString album = metaData.value(QMediaMetaData::AlbumTitle).toString();
  qint64 duration = metaData.value(QMediaMetaData::Duration).toLongLong();
  qint64 date = metaData.value(QMediaMetaData::Date).toLongLong();

  MetaData data{
      .title = title,
      .author = artist,
      .albumTitle = album,
      .duration = duration,
      .date = date
  };
  m_metaDatas.append(data);
  m_currentIndex++;
  processNextFile();
}
}
