#include "homepage_service.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

namespace service {
HomepageService::HomepageService(QObject* parent) : QObject{parent} {
  connect(m_network, &HomepageNetwork::ready, this, &HomepageService::onReady);
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
        // parseBanners(blocksArr.at(0));
        // parseRcmdPlaylists(blocksArr.at(2));
        // parseRcmdSongs(blocksArr.at(3));
      }
    }
  }
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

}

}  // namespace service
