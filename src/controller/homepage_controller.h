#ifndef HOMEPAGE_CONTROLLER_H
#define HOMEPAGE_CONTROLLER_H

#include <QObject>
#include <QObjectBindableProperty>
#include <QQmlEngine>
#include <QVariantList>
#include <QProperty>

#include "controller_global.h"

#include "homepage_service.h"

namespace controller {
using namespace service;
class CONTROLLER_DLL_EXPORT HomepageController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(QVariantList banners READ banners BINDABLE bindableBanners FINAL)
  Q_PROPERTY(QVariantList recommendedPlaylists READ recommendedPlaylists BINDABLE bindableRecommendedPlaylists FINAL)
  Q_PROPERTY(QVariantList recommendedStyleSongs READ recommendedStyleSongs
                BINDABLE bindableRecommendedStyleSongs FINAL)
 public:
  Q_INVOKABLE void fetch(bool refresh = false);

  explicit HomepageController(QObject* parent = nullptr);
  QVariantList recommendedPlaylists();
  QBindable<QVariantList> bindableRecommendedPlaylists() {
    return QBindable<QVariantList>(&m_recommendedPlaylists);
  }
  QBindable<QVariantList> bindableRecommendedStyleSongs() {
    return QBindable<QVariantList>(&m_recommendedStyleSongs);
  }
  QBindable<QVariantList> bindableBanners() {
    return QBindable<QVariantList>(&m_banners);
  }
  QVariantList recommendedStyleSongs();
  QVariantList banners();
 private slots:
  void onReady(error_code::ErrorCode code, HomePageInfoPtr ptr);

 private:
  QProperty<QVariantList> m_recommendedPlaylists;
  QProperty<QVariantList> m_recommendedStyleSongs;
  QProperty<QVariantList> m_banners;

  QPointer<HomepageService> m_homepageService;
};
}

#endif  // HOMEPAGE_CONTROLLER_H
