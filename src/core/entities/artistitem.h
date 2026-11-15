#pragma once

#include <QString>
#include <QtQml/qqmlregistration.h>

namespace entities {

class ArtistItem {
  Q_GADGET
  QML_VALUE_TYPE(artistItem)
  Q_PROPERTY(qulonglong id READ id WRITE setId)
  Q_PROPERTY(QString name READ name WRITE setName)

 public:
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }

  bool operator==(const ArtistItem&) const = default;

 private:
  qulonglong m_id = 0;
  QString m_name;
};

}
