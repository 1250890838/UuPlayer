#pragma once

#include <QObject>
#include <QVariantMap>
#include <QString>

#include "entities/types.h"
#include "models/playlistitemmodel.h"

class QQmlEngine;
class QJSEngine;

namespace core {
class PlaylistRepository;
}

namespace viewmodel {

class PlaylistHubController : public QObject {
  Q_OBJECT
  Q_PROPERTY(PlaylistItemModel* items READ items CONSTANT)
  Q_PROPERTY(QVariantMap categories READ categories NOTIFY categoriesChanged)
  Q_PROPERTY(bool loading READ isLoading NOTIFY loadingChanged)

 public:
  explicit PlaylistHubController(core::PlaylistRepository* repository,
                                 QObject* parent = nullptr);

  PlaylistItemModel* items() { return &m_items; }
  QVariantMap categories() const { return m_categories; }
  bool isLoading() const { return m_loading; }

  Q_INVOKABLE void fetchCategories();
  Q_INVOKABLE void selectCategory(const QString& category);
  Q_INVOKABLE void fetchNextPage();

 signals:
  void categoriesChanged();
  void loadingChanged();
  void loadFailed(error_code::ErrorCode code);

 private:
  void requestPage();

  core::PlaylistRepository* m_repository = nullptr;
  PlaylistItemModel m_items;
  QVariantMap m_categories;
  QString m_category;
  int m_offset = 0;
  int m_limit = 8;
  bool m_loading = false;
  bool m_hasMore = true;
};

}
