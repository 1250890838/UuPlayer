#ifndef ARIST_DATA_H
#define ARIST_DATA_H
#include <QObject>
#include <QString>
namespace entities {

class AristData {
  Q_GADGET
  Q_PROPERTY(qulonglong id READ id WRITE setId)
  Q_PROPERTY(QString name READ name WRITE setName)
 public:
  AristData() = default;
  ~AristData() = default;
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }

 private:
  qulonglong m_id;
  QString m_name;
};
}
#endif // ARIST_DATA_H
