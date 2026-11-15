#pragma once

#include <QObject>
#include <QObjectBindableProperty>
#include <QProperty>
#include <QQmlEngine>
#include <QVariantList>

namespace core {
class HomepageRepository;
}

namespace viewmodel {

class HomepageController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(QVariantList banners READ banners BINDABLE bindableBanners FINAL)
  Q_PROPERTY(QVariantList recommendedPlaylists READ recommendedPlaylists BINDABLE
                 bindableRecommendedPlaylists FINAL)
  Q_PROPERTY(QVariantList recommendedStyleSongs READ recommendedStyleSongs
                 BINDABLE bindableRecommendedStyleSongs FINAL)

 public:
  explicit HomepageController(QObject* parent = nullptr);

  Q_INVOKABLE void fetch(bool refresh = false);

  QVariantList banners() { return m_banners.value(); }
  QVariantList recommendedPlaylists() {
    return m_recommendedPlaylists.value();
  }
  QVariantList recommendedStyleSongs() {
    return m_recommendedStyleSongs.value();
  }

  QBindable<QVariantList> bindableBanners() { return &m_banners; }
  QBindable<QVariantList> bindableRecommendedPlaylists() {
    return &m_recommendedPlaylists;
  }
  QBindable<QVariantList> bindableRecommendedStyleSongs() {
    return &m_recommendedStyleSongs;
  }

 private:
  core::HomepageRepository* m_homepage = nullptr;

  QProperty<QVariantList> m_banners;
  QProperty<QVariantList> m_recommendedPlaylists;
  QProperty<QVariantList> m_recommendedStyleSongs;
};

}  // namespace viewmodel