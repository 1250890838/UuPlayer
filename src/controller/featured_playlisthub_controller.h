#ifndef PLAYLISTHUB_H
#define PLAYLISTHUB_H

#include <QObject>
#include <QObjectBindableProperty>
#include <QQmlEngine>

#include "model/playlist_item_model.h"

#include "controller_global.h"
#include "recommended_playlist_service.h"

namespace controller {

using namespace model;
using namespace service;
class CONTROLLER_DLL_EXPORT FeaturedPlaylistHubController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
  Q_PROPERTY(PlaylistItemModel* currPlaylistItems READ currPlaylistItems)
  Q_PROPERTY(QVariantMap categories READ categories NOTIFY categoriesChanged
                 BINDABLE bindableCategories)
 public:
  static FeaturedPlaylistHubController* create(QQmlEngine* qmlEngine,
                                               QJSEngine* jsEngine);

  Q_INVOKABLE void fetchPlaylistItems(const QString& tag, quint32 offset,
                                      quint32 limit);
  Q_INVOKABLE void fetchCategories();

 public:
  FeaturedPlaylistHubController(RecommendedPlaylistService*);
  PlaylistItemModel* currPlaylistItems();
  QVariantMap categories() { return m_categories.value(); }
  QBindable<QVariantMap> bindableCategories() { return &m_categories; }

 signals:
  void categoriesChanged();
 private slots:
  void onTopReady(error_code::ErrorCode code, PlaylistItemListPtr data);
  void onCategoriesReady(error_code::ErrorCode code,
                         QMap<QString, QStringList> categoriesMap);

 private:
  Q_OBJECT_BINDABLE_PROPERTY(FeaturedPlaylistHubController, QVariantMap,
                             m_categories,
                             &FeaturedPlaylistHubController::categoriesChanged);

  RecommendedPlaylistService* m_recommendedPlaylistService;

  PlaylistItemModel m_playlistItemModel;
};
}  // namespace controller
#endif  // PLAYLISTHUB_H
