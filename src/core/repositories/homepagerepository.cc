#include "homepagerepository.h"

#include <QUrlQuery>

#include "apiclient.h"
#include "apiendpoints.h"
#include "mappers.h"

namespace core {

HomepageRepository::HomepageRepository(ApiClient* api, QObject* parent)
    : QObject(parent), m_api(api) {}

void HomepageRepository::fetch(bool refresh) {
  QUrlQuery query;
  query.addQueryItem(QStringLiteral("refresh"),
                     refresh ? QStringLiteral("true")
                             : QStringLiteral("false"));

  m_api->get(endpoints::homepage(), query, this,
             [this](error_code::ErrorCode code, const QByteArray& body) {
               const auto object = mappers::apiObject(body);
               if (code != error_code::NoError || !object) {
                 emit ready(code == error_code::NoError
                                ? error_code::JsonContentError
                                : code,
                            {});
                 return;
               }
               emit ready(error_code::NoError,
                          mappers::homepageInfo(*object));
             });
}

}  // namespace core