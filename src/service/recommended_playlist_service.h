#ifndef RECOMMENDED_PLAYLIST_SERVICE_H
#define RECOMMENDED_PLAYLIST_SERVICE_H

#include "model/playlist_item_model.h"
#include "playlist_network.h"
#include "service_global.h"

#include "entities/playlist_item.h"

#include <qglobal.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qtmetamacros.h>
#include <qtypes.h>
#include <qvariant.h>
#include <QObject>

using namespace entities;
namespace service {

using PlaylistItemList = QList<PlaylistItem>;
using PlaylistItemListPtr = QSharedPointer<QList<PlaylistItem>>;

// 获取推荐歌单，获取歌单标签列表
class SERVICE_DLL_EXPORT RecommendedPlaylistService : public QObject {
  Q_OBJECT
 public:
  void getHighquality(const QString& tag, qint32 offset, qint32 limit);
  void getTop(const QString& tag, qint32 offset, qint32 limit);
  void getCategories();
 signals:
  void getHighqualityFinished(error_code::ErrorCode code,
                              PlaylistItemListPtr data);
  void getTopFinsihed(error_code::ErrorCode code, PlaylistItemListPtr data);
  void getCategoriesFinished(error_code::ErrorCode code,
                             QMap<QString, QStringList> categoriesMap);

 public slots:
  void onGetHighqualityFinished(error_code::ErrorCode, const QByteArray& data);
  void onGetTopFinished(error_code::ErrorCode, const QByteArray& data);
  void onGetCatlistFinished(error_code::ErrorCode, const QByteArray& data);

 public:
  RecommendedPlaylistService(QObject* parent = nullptr);

 private:
  QStringList formatTags(const QJsonArray& array);
  UserItem formatCreator(const QJsonObject& object);
  QVector<UserItem> formatSubscribers(const QJsonArray& array);
  UserItem formatUserdDataInComment(const QJsonObject& object);
 private:
  network::PlaylistNetwork m_network;
};
}  // namespace service
#endif
