#pragma once

#include <QString>
#include <QUrl>
#include <QtQml/qqmlregistration.h>

namespace entities {

class AlbumItem {
  Q_GADGET
  QML_VALUE_TYPE(albumItem)
  Q_PROPERTY(qulonglong id READ id WRITE setId)
  Q_PROPERTY(QString name READ name WRITE setName)
  Q_PROPERTY(QUrl picUrl READ picUrl WRITE setPicUrl)

 public:
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }
  QUrl picUrl() const { return m_picUrl; }
  void setPicUrl(const QUrl& url) { m_picUrl = url; }

  bool operator==(const AlbumItem&) const = default;

 private:
  qulonglong m_id = 0;
  QString m_name;
  QUrl m_picUrl;
};

}
