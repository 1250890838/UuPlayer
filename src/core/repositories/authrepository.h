#pragma once

#include <QObject>
#include <QString>

#include "entities/types.h"

namespace core {

class ApiClient;

class AuthRepository : public QObject {
  Q_OBJECT
 public:
  explicit AuthRepository(ApiClient* api, QObject* parent = nullptr);

  void requestQrKey();
  void requestQrImage(const QString& key);
  void checkScan(const QString& key);

 signals:
  void qrKeyReady(error_code::ErrorCode code, const QString& key);
  void qrImageReady(error_code::ErrorCode code, const QString& base64Image);
  void scanChecked(error_code::ErrorCode code, int apiCode,
                   const QString& cookie);

 private:
  ApiClient* m_api = nullptr;
};

}
