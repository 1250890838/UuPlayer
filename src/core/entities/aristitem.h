#pragma once

#include <QString>

namespace entities {

class AristItem {
  Q_GADGET
  Q_PROPERTY(qulonglong id READ id)
  Q_PROPERTY(QString name READ name)

 public:
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }

  bool operator==(const AristItem&) const = default;

 private:
  qulonglong m_id = 0;
  QString m_name;
};

}  // namespace entities