#pragma once

#include <QColor>
#include <QList>
#include <QString>
#include <QStringList>
#include <QUrl>

namespace entities {

struct Banner {
  QColor titleColor;
  QString title;
  QUrl picUrl;
};

struct RcmdPlaylistInfo {
  qulonglong targetId = 0;
  QString mainTitle;
  QString subTitle;
  QUrl picUrl;
  QStringList labels;
  qulonglong playCount = 0;
};

struct RcmdSongInfo {
  qulonglong targetId = 0;
  QString mainTitle;
  QString subTitle;
  QUrl picUrl;
  QStringList artistNames;
  QList<qulonglong> artistIds;
};

struct HomePageInfo {
  QList<Banner> banners;
  QList<RcmdPlaylistInfo> rcmdPlaylists;
  QList<RcmdSongInfo> rcmdSongs;
};

}  // namespace entities