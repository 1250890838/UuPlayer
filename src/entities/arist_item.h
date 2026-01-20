#ifndef ARIST_ITEM_H
#define ARIST_ITEM_H
#include <QObject>
#include <QString>

namespace entities {

class AristItem {
  Q_GADGET
  Q_PROPERTY(qulonglong id READ id)
  Q_PROPERTY(QString name READ name)
 public:
  AristItem() = default;
  ~AristItem() = default;
  AristItem& operator=(const AristItem& other) = default;
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }

 private:
  qulonglong m_id;
  QString m_name;
};
}
Q_DECLARE_METATYPE(entities::AristItem);
#endif  // ARIST_ITEM_H
