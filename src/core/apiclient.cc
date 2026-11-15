#include "apiclient.h"

#include <QNetworkReply>
#include <QNetworkRequest>

namespace core {

ApiClient::ApiClient(QObject* parent) : QObject(parent) {}

void ApiClient::get(const QString& endpoint, const QUrlQuery& query,
                    QObject* context, Callback callback) {
  QUrl url(endpoint);
  url.setQuery(query);

  QNetworkRequest request(url);
  if (!m_sessionCookie.isEmpty()) {
    request.setRawHeader("Cookie", m_sessionCookie.toUtf8());
  }

  QNetworkReply* reply = m_manager.get(request);
  QObject::connect(reply, &QNetworkReply::finished, context,
                   [reply, callback = std::move(callback)]() {
                     error_code::ErrorCode code = error_code::NoError;
                     switch (reply->error()) {
                       case QNetworkReply::NoError:
                         break;
                       case QNetworkReply::ConnectionRefusedError:
                         code = error_code::ConnectionRefusedError;
                         break;
                       case QNetworkReply::TimeoutError:
                         code = error_code::TimeoutError;
                         break;
                       default:
                         code = error_code::OtherError;
                         break;
                     }
                     const QByteArray body = reply->readAll();
                     reply->deleteLater();
                     callback(code, body);
                   });
}

void ApiClient::get(const QString& endpoint, QObject* context,
                    Callback callback) {
  get(endpoint, QUrlQuery(), context, std::move(callback));
}

void ApiClient::setSessionCookie(const QString& cookie) {
  m_sessionCookie = cookie;
}

}
