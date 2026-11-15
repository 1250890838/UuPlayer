#include "homepagecontroller.h"

#include "app/appcontext.h"
#include "repositories/homepagerepository.h"

namespace viewmodel {

HomepageController::HomepageController(QObject* parent) : QObject(parent) {
  m_homepage = app::AppContext::instance()->homepage();

  connect(m_homepage, &core::HomepageRepository::ready, this,
          [this](error_code::ErrorCode code,
                 const entities::HomePageInfo& info) {
            if (code != error_code::NoError) {
              return;
            }

            QVariantList banners;
            for (const auto& banner : info.banners) {
              QVariantMap map;
              map.insert(QStringLiteral("picUrl"), banner.picUrl);
              map.insert(QStringLiteral("title"), banner.title);
              map.insert(QStringLiteral("titleColor"), banner.titleColor);
              banners.append(map);
            }
            m_banners.setValue(banners);

            QVariantList playlists;
            for (const auto& playlist : info.rcmdPlaylists) {
              QVariantMap map;
              map.insert(QStringLiteral("targetId"), playlist.targetId);
              map.insert(QStringLiteral("labels"), playlist.labels);
              map.insert(QStringLiteral("name"), playlist.mainTitle);
              map.insert(QStringLiteral("subName"), playlist.subTitle);
              map.insert(QStringLiteral("coverUrl"), playlist.picUrl);
              map.insert(QStringLiteral("playCount"), playlist.playCount);
              playlists.append(map);
            }
            m_recommendedPlaylists.setValue(playlists);

            QVariantList songs;
            for (const auto& song : info.rcmdSongs) {
              QVariantMap map;
              map.insert(QStringLiteral("targetId"), song.targetId);
              map.insert(QStringLiteral("mainTitle"), song.mainTitle);
              map.insert(QStringLiteral("subTitle"), song.subTitle);
              map.insert(QStringLiteral("picUrl"), song.picUrl);
              map.insert(QStringLiteral("artistNames"), song.artistNames);
              songs.append(map);
            }
            m_recommendedStyleSongs.setValue(songs);
          });
}

void HomepageController::fetch(bool refresh) {
  m_homepage->fetch(refresh);
}

}  // namespace viewmodel