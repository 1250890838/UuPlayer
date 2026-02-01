#include "song_url_network.h"

#include <QNetworkReply>

namespace network {
SongUrlNetwork::SongUrlNetwork() {}

void SongUrlNetwork::fetch(qulonglong id,
                           sound_level::SoundQualityLevel level) {
  using namespace sound_level;
  QNetworkRequest request;
  QUrl url = network_api::apiSongUrl + "?" + "id=" + QString::number(id);
  QString levelStr = [level] {
    switch (level) {
      case Standard:
        return "standard";
      case Higher:
        return "higher";
      case Exhigh:
        return "exhigh";
      case Lossless:
        return "lossless";
      case Hires:
        return "hires";
      case Jyeffect:
        return "jyeffect";
      case Sky:
        return "Sky";
      case Jymaster:
        return "jymaster";
      default:
        return "standard";
    }
  }();
  url = url.toString() + "&" + "level=" + levelStr;
  request.setUrl(url);
  auto reply = this->get(request);
  connect(reply, &QNetworkReply::finished, this, [reply, this]() {
    auto code = handleReplyErrorCode(reply);
    auto data = reply->readAll();
    emit ready(code, data);
    reply->deleteLater();
  });
}
}  // namespace network
