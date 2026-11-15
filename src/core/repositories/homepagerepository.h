#pragma once

#include <QObject>

#include "entities/homepageinfo.h"
#include "entities/types.h"

namespace core {

class ApiClient;

class HomepageRepository : public QObject {
  Q_OBJECT
 public:
  explicit HomepageRepository(ApiClient* api, QObject* parent = nullptr);

  void fetch(bool refresh);

 signals:
  void ready(error_code::ErrorCode code, const entities::HomePageInfo& info);

 private:
  ApiClient* m_api = nullptr;
};

}  // namespace core