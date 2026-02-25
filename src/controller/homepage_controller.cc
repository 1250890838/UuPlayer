#include "homepage_controller.h"

#include "service_manager.h"

namespace controller {
HomepageController::HomepageController(QObject* parent) : QObject{parent} {
  m_homepageService = ServiceManager::instance().getInstance<HomepageService>();
  if (m_homepageService) {
    connect(m_homepageService, &HomepageService::ready, this,
            &HomepageController::onReady);
  }
}

void HomepageController::fetch(bool refresh) {
  m_homepageService->fetch(refresh);
}

QVariantList HomepageController::recommendedPlaylists() {
  return m_recommendedPlaylists.value();
}

QVariantList HomepageController::recommendedStyleSongs() {
  return m_recommendedStyleSongs.value();
}

QVariantList HomepageController::banners() {
  return m_banners.value();
}

void HomepageController::onReady(error_code::ErrorCode code,
                                 HomePageInfoPtr ptr) {
  if (code == error_code::NoError && !ptr.isNull()) {
    // process banners
    QVariantList temp;
    for (const auto& banner : ptr->banners) {
      QVariantMap map;
      map["picUrl"] = banner.picUrl;
      map["title"] = banner.title;
      map["titleColor"] = banner.titleColor;
      temp.append(map);
    }
    m_banners = temp;
    temp.clear();
    // process playlists
    for (const auto& playlistInfo : ptr->rcmdPlaylists) {
      QVariantMap map;
      map["targetId"] = playlistInfo.targetId;
      map["labels"] = playlistInfo.labels;
      map["name"] = playlistInfo.mainTitle;
      map["subName"] = playlistInfo.subTitle;
      map["coverUrl"] = playlistInfo.picUrl;
      map["playCount"] = playlistInfo.playCount;
      temp.append(map);
    }
    m_recommendedPlaylists = temp;
    temp.clear();
    // process songs
    for (const auto& songInfo : ptr->rcmdSongs) {
      QVariantMap map;
      map["targetId"] = songInfo.targetId;
      map["mainTitle"] = songInfo.mainTitle;
      map["subTitle"] = songInfo.subTitle;
      map["picUrl"] = songInfo.picUrl;
      temp.append(map);
    }
    m_recommendedStyleSongs = temp;
  }
}
}
