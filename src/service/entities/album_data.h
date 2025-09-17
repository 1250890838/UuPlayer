#ifndef ALBUM_DATA_H
#define ALBUM_DATA_H
#include <QObject>
#include <QUrl>
namespace entities {

class AlbumData {
  Q_GADGET
  Q_PROPERTY(qulonglong id READ id WRITE setId)
  Q_PROPERTY(QString name READ name WRITE setName)
  Q_PROPERTY(QUrl picUrl READ picUrl WRITE setPicUrl)
 public:
  AlbumData() = default;
  AlbumData(qulonglong id, const QString& name, const QUrl& picUrl);
  ~AlbumData() = default;
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }
  QUrl picUrl() const { return m_picUrl; }
  void setPicUrl(const QUrl& picUrl) { m_picUrl = picUrl; }

 private:
  qulonglong m_id;
  QString m_name;
  QUrl m_picUrl;
};
}
Q_DECLARE_METATYPE(entities::AlbumData);
#endif // ALBUM_DATA_H
