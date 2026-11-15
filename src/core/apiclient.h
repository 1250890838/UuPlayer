#pragma once

#include <QNetworkAccessManager>
#include <QObject>
#include <QUrlQuery>
#include <functional>

#include "entities/types.h"

namespace core {

class ApiClient : public QObject {
  Q_OBJECT
 public:
  using Callback = std::function<void(error_code::ErrorCode, const QByteArray&)>;

  explicit ApiClient(QObject* parent = nullptr);

  void get(const QString& endpoint, const QUrlQuery& query, QObject* context,
           Callback callback);
  void get(const QString& endpoint, QObject* context, Callback callback);

  QNetworkReply* getRaw(const QUrl& url);

  void setSessionCookie(const QString& cookie);

 private:
  QNetworkAccessManager m_manager;
  QString m_sessionCookie;
};

}  // namespace core