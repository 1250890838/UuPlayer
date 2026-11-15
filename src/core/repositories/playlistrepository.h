#pragma once

#include <QList>
#include <QMap>
#include <QObject>
#include <QStringList>

#include "entities/playlistitem.h"
#include "entities/types.h"

namespace core {

class ApiClient;

class PlaylistRepository : public QObject {
  Q_OBJECT
 public:
  explicit PlaylistRepository(ApiClient* api, QObject* parent = nullptr);

  void fetchTop(const QString& category, int offset, int limit);
  void fetchCategories();
  void fetchDetail(qulonglong id);

 signals:
  void topReady(error_code::ErrorCode code,
                const QList<entities::PlaylistItem>& playlists);
  void categoriesReady(error_code::ErrorCode code,
                       const QMap<QString, QStringList>& categories);
  void detailReady(error_code::ErrorCode code,
                   const entities::PlaylistItem& playlist);

 private:
  ApiClient* m_api = nullptr;
};

}
