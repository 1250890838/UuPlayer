#include "authrepository.h"

#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>

#include "apiclient.h"
#include "apiendpoints.h"

namespace core {
namespace {

QString timestamp() {
  return QString::number(QDateTime::currentMSecsSinceEpoch());
}

}

AuthRepository::AuthRepository(ApiClient* api, QObject* parent)
    : QObject(parent), m_api(api) {}

void AuthRepository::requestQrKey() {
  QUrlQuery query;
  query.addQueryItem(QStringLiteral("timestamp"), timestamp());

  m_api->get(endpoints::qrKey(), query, this,
             [this](error_code::ErrorCode code, const QByteArray& body) {
               if (code != error_code::NoError) {
                 emit qrKeyReady(code, {});
                 return;
               }
               const QJsonObject object = QJsonDocument::fromJson(body).object();
               const QString key =
                   object.value(QStringLiteral("data"))
                       .toObject()
                       .value(QStringLiteral("unikey"))
                       .toString();
               if (object.value(QStringLiteral("code")).toInt() != 200 ||
                   key.isEmpty()) {
                 emit qrKeyReady(error_code::JsonContentError, {});
                 return;
               }
               emit qrKeyReady(error_code::NoError, key);
             });
}

void AuthRepository::requestQrImage(const QString& key) {
  QUrlQuery query;
  query.addQueryItem(QStringLiteral("key"), key);
  query.addQueryItem(QStringLiteral("qrimg"), QStringLiteral("true"));
  query.addQueryItem(QStringLiteral("timestamp"), timestamp());

  m_api->get(endpoints::qrCreate(), query, this,
             [this](error_code::ErrorCode code, const QByteArray& body) {
               if (code != error_code::NoError) {
                 emit qrImageReady(code, {});
                 return;
               }
               const QJsonObject object = QJsonDocument::fromJson(body).object();
               const QString image =
                   object.value(QStringLiteral("data"))
                       .toObject()
                       .value(QStringLiteral("qrimg"))
                       .toString();
               if (object.value(QStringLiteral("code")).toInt() != 200 ||
                   image.isEmpty()) {
                 emit qrImageReady(error_code::JsonContentError, {});
                 return;
               }
               emit qrImageReady(error_code::NoError, image);
             });
}

void AuthRepository::checkScan(const QString& key) {
  QUrlQuery query;
  query.addQueryItem(QStringLiteral("key"), key);
  query.addQueryItem(QStringLiteral("timestamp"), timestamp());

  m_api->get(endpoints::qrCheck(), query, this,
             [this](error_code::ErrorCode code, const QByteArray& body) {
               if (code != error_code::NoError) {
                 emit scanChecked(code, 0, {});
                 return;
               }
               const QJsonObject object = QJsonDocument::fromJson(body).object();
               const int apiCode =
                   object.value(QStringLiteral("code")).toInt();
               const QString cookie =
                   object.value(QStringLiteral("cookie")).toString();
               if (apiCode == 803 && !cookie.isEmpty()) {
                 m_api->setSessionCookie(cookie);
               }
               emit scanChecked(error_code::NoError, apiCode, cookie);
             });
}

}
