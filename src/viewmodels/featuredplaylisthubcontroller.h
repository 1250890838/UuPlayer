#pragma once

#include <QObject>
#include <QObjectBindableProperty>
#include <QQmlEngine>
#include <QVariantMap>
#include <QString>

#include "models/playlistitemmodel.h"

namespace core {
class PlaylistRepository;
}

namespace viewmodel {

class FeaturedPlaylistHubController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  Q_PROPERTY(PlaylistItemModel* currPlaylistItems READ currPlaylistItems NOTIFY
                 currPlaylistItemsChanged FINAL)
  Q_PROPERTY(QVariantMap categories READ categories NOTIFY categoriesChanged
                 BINDABLE bindableCategories FINAL)

 public:
  FeaturedPlaylistHubController();

  Q_INVOKABLE void fetchPlaylistItems(const QString& tag, quint32 offset,
                                      quint32 limit);
  Q_INVOKABLE void clearPlaylistItems();
  Q_INVOKABLE void fetchCategories();

  PlaylistItemModel* currPlaylistItems() { return &m_playlistItemModel; }
  QVariantMap categories() { return m_categories.value(); }
  QBindable<QVariantMap> bindableCategories() {
    return QBindable<QVariantMap>(&m_categories);
  }

 signals:
  void categoriesChanged();
  void currPlaylistItemsChanged();

 private:
  core::PlaylistRepository* m_playlists = nullptr;
  Q_OBJECT_BINDABLE_PROPERTY(FeaturedPlaylistHubController, QVariantMap,
                             m_categories,
                             &FeaturedPlaylistHubController::categoriesChanged);
  PlaylistItemModel m_playlistItemModel;
};

}  // namespace viewmodel