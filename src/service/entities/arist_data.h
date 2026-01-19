#ifndef ARIST_DATA_H
#define ARIST_DATA_H
#include <QObject>
#include <QQmlEngine>
#include <QString>

namespace entities {

class AristData {
  Q_GADGET
  QML_VALUE_TYPE(aristData)
  Q_PROPERTY(qulonglong id READ id)
  Q_PROPERTY(QString name READ name)
 public:
  AristData() = default;
  ~AristData() = default;
  AristData& operator=(const AristData& other) = default;
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }

 private:
  qulonglong m_id;
  QString m_name;
};
}
Q_DECLARE_METATYPE(entities::AristData);
#endif  // ARIST_DATA_H
