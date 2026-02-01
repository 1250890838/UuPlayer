#include "service_manager.h"
namespace service {
ServiceManager::ServiceManager(QObject* parent) {}

ServiceManager& ServiceManager::instance() {
  static ServiceManager manager;
  return manager;
}

void ServiceManager::clear() {
  qDeleteAll(m_instances);
  m_instances.clear();
}

ServiceManager::~ServiceManager() {
  clear();
}

}  // namespace service
