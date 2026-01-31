#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <QHash>
#include <QMetaType>
#include <QObject>
#include <QScopedPointer>
#include <QSharedPointer>
#include <typeindex>

#include "service_global.h"

namespace service {
class SERVICE_DLL_EXPORT ServiceManager : QObject {
  Q_OBJECT

 public:
  static ServiceManager& instance();

  template <typename T, typename... Args>
  T* getInstance(Args&&... args) {
    const auto type = std::type_index(typeid(T));

    if (m_instances.contains(type)) {
      return static_cast<T*>(m_instances[type]);
    }

    QScopedPointer<T> newInstance(new T(std::forward<Args>(args)...));
    T* rawInstance = newInstance.data();
    m_instances[type] = newInstance.take();
    return rawInstance;
  }

  template <typename T>
  bool hasInstance() const {
    const auto type = std::type_index(typeid(T));
    return m_instances.contains(type);
  }

  template <typename T>
  void destroyInstance() {
    const auto type = std::type_index(typeid(T));
    if (m_instances.contains(type)) {
      m_instances.remove(type);
    }
  }

  void clear();

 private:
  explicit ServiceManager(QObject* parent = nullptr);
  ~ServiceManager() override;

  ServiceManager(const ServiceManager&) = delete;
  ServiceManager& operator=(const ServiceManager&) = delete;

  QHash<std::type_index, QObject*> m_instances;
};
}  // namespace service
#endif // SERVICEMANAGER_H
