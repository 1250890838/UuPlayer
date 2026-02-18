#include "homepage_network.h"

#include <QNetworkReply>
#include <QNetworkRequest>

#include "api_network.h"

namespace network {
HomepageNetwork::HomepageNetwork() {}

void HomepageNetwork::fetch(bool refresh) {
  QNetworkRequest request;
  QUrl url = network_api::apiHomepage + "?" +
             "refresh=" + (refresh ? "true" : "false");
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply, this] {
    auto code = handleReplyErrorCode(reply);
    auto data = reply->readAll();
    emit (code, data);
    reply->deleteLater();
  });
}
}