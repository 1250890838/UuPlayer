#include "homepage_service.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

namespace service {
HomepageService::HomepageService(QObject* parent) : QObject{parent} {
  connect(&m_network, &HomepageNetwork::ready, this, &HomepageService::onReady);
}

void HomepageService::fetch(bool refresh) {
  m_network.fetch(refresh);
}

void HomepageService::onReady(error_code::ErrorCode code,
                              const QByteArray& data) {
  HomePageInfoPtr result = nullptr;
  if (code == error_code::NoError) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    if (!doc.isEmpty() && !obj.empty()) {
      auto jsonCode = obj["code"].toInt();
      if (jsonCode == 200) {
        result = HomePageInfoPtr::create();
        auto dataObj = obj["data"].toObject();
        auto blocksArr = dataObj["blocks"].toArray();

        std::for_each(blocksArr.begin(), blocksArr.end(),
                      [this, result](const QJsonValue& value) {
                        parseBanners(result, value);
                        parseRcmdPlaylists(result, value);
                        parseRcmdSongs(result, value);
                      });
      }
    } else {
      code = error_code::JsonContentError;
    }
  }
  emit ready(code, result);
}

void HomepageService::parseBanners(HomePageInfoPtr ptr, QJsonValue value) {
  QJsonObject obj = value.toObject();
  if (obj["blockCode"].toString() != "HOMEPAGE_BANNER")
    return;
  QJsonArray arr = obj["extInfo"].toObject()["banners"].toArray();
  for (const auto& bannerValue : arr) {
    auto bannerObj = bannerValue.toObject();
    Banner banner;
    banner.picUrl = bannerObj["pic"].toString();
    banner.title = bannerObj["typeTitle"].toString();
    banner.titleColor = QColor::fromString(bannerObj["titleColor"].toString());
    ptr->banners.append(banner);
  }
}

void HomepageService::parseRcmdPlaylists(HomePageInfoPtr ptr,
                                         QJsonValue value) {
  QJsonObject obj = value.toObject();
  if (obj["blockCode"].toString() != "HOMEPAGE_BLOCK_PLAYLIST_RCMD")
    return;
  QJsonArray arr = obj["creatives"].toArray();
  for (const auto& creativeValue : arr) {
    auto creativeObj = creativeValue.toObject();
    auto resourceArr = creativeObj["resources"].toArray();
    for (const auto& resourceValue : resourceArr) {
      auto resourceObj = resourceValue.toObject();
      auto uiElemntObj = resourceObj["uiElement"].toObject();
      RcmdPlaylistInfo playlistInfo;
      playlistInfo.mainTitle =
          uiElemntObj["mainTitle"].toObject()["title"].toString();
      playlistInfo.subTitle =
          uiElemntObj["subTitle"].toObject()["title"].toString();
      playlistInfo.picUrl =
          uiElemntObj["image"].toObject()["imageUrl"].toString();
      for (const auto& labelValue : uiElemntObj["labelTexts"].toArray()) {
        playlistInfo.labels.append(labelValue.toString());
      }
      playlistInfo.targetId =
          resourceObj["resourceId"].toVariant().toULongLong();
      playlistInfo.playCount = resourceObj["resourceExtInfo"]
                                   .toObject()["playCount"]
                                   .toVariant()
                                   .toULongLong();
      ptr->rcmdPlaylists.append(playlistInfo);
    }
  }
}

void HomepageService::parseRcmdSongs(HomePageInfoPtr ptr, QJsonValue value) {
  QJsonObject obj = value.toObject();
  if (obj["blockCode"].toString() != "HOMEPAGE_BLOCK_STYLE_RCMD")
    return;
  QJsonArray arr = obj["creatives"].toArray();
  for (const auto& creativeValue : arr) {
    auto creativeObj = creativeValue.toObject();
    auto resourceArr = creativeObj["resources"].toArray();
    for (const auto& resourceValue : resourceArr) {
      RcmdSongInfo info;
      auto resourceObj = resourceValue.toObject();
      info.mainTitle = resourceObj["uiElement"]
                           .toObject()["mainTtile"]
                           .toObject()["title"]
                           .toString();
      info.subTitle = resourceObj["uiElement"]
                          .toObject()["subTitle"]
                          .toObject()["title"]
                          .toString();
      info.picUrl = resourceObj["image"].toObject()["imageUrl"].toString();
      info.targetId = resourceObj["resourceId"].toVariant().toULongLong();
      auto [ids, names] = parseRcmdSongArtistValueArray(
          resourceObj["resourceExtInfo"].toObject()["artists"].toArray());
      info.artistIds = ids;
      info.artistNames = names;
      ptr->rcmdSongs.append(info);
    }
  }
}
// {
//   "name": "连麻Swimming",
//   "id": 12064019,
//   "picId": 0,
//   "img1v1Id": 0,
//   "briefDesc": "",
//   "picUrl": "",
//   "img1v1Url": "http://p1.music.126.net/6y-UleORITEDbvrOLV0Q8A==/5639395138885805.jpg",
//   "albumSize": 0,
//   "alias": [],
//   "trans": "",
//   "musicSize": 0,
//   "topicPerson": 0
// },

QPair<QList<qulonglong>, QList<QString>>
HomepageService::parseRcmdSongArtistValueArray(QJsonArray data) {
  QList<qulonglong> ids;
  QList<QString> names;
  for (const auto& value : data) {
    auto obj = value.toObject();
    names.append(obj["name"].toString());
    ids.append(obj["id"].toVariant().toULongLong());
  }
  return {ids, names};
}

}  // namespace service
