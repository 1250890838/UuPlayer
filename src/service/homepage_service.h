#ifndef HOMEPAGE_SERVICE_H
#define HOMEPAGE_SERVICE_H

#include <QObject>
#include <QColor>
#include <QString>
#include <QUrl>
#include <QList>

#include "homepage_network.h"
#include "service_global.h"

namespace service {

struct Banner {
  QColor titleColor;
  QString title;
  QUrl picUrl;
};
struct RcmdPlaylistInfo {  // Rcmd => Recommend
  qulonglong targetId;
  QString mainTitle;
  QString subTitle;
  QUrl picUrl;
  QList<QString> labels;
  qulonglong playCount;
};

struct RcmdSongInfo {
  qulonglong targetId;
  QString mainTitle;
  QString subTitle;
  QUrl picUrl;
};

struct HomePageInfo {
  QList<Banner> banners;
  QList<RcmdPlaylistInfo> rcmdPlaylists;
  QList<RcmdSongInfo> rcmdSongs;
};


using namespace network;
using HomePageInfoPtr = QSharedPointer<HomePageInfo>;

class SERVICE_DLL_EXPORT HomepageService : public QObject {
  Q_OBJECT
 public:
  explicit HomepageService(QObject* parent = nullptr);
  void fetch(bool refresh);
 signals:
  void ready(error_code::ErrorCode code, HomePageInfoPtr ptr);
 private slots:
  void onReady(error_code::ErrorCode code, const QByteArray& data);
 private:
  void parseBanners(HomePageInfoPtr ptr, QJsonValue value);
  void parseRcmdPlaylists(HomePageInfoPtr ptr, QJsonValue value);
  void parseRcmdSongs(HomePageInfoPtr ptr, QJsonValue value);
 private:
  HomepageNetwork m_network;
};
}  // namespace service
#endif  // HOMEPAGE_SERVICE_H
