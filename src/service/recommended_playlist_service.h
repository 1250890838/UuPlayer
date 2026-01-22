#ifndef RECOMMENDED_PLAYLIST_SERVICE_H
#define RECOMMENDED_PLAYLIST_SERVICE_H

#include "playlist_item.h"
#include "recommended_playlist_network.h"
#include "service_global.h"

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
using PlaylistItemListPtr = QSharedPointer<PlaylistItemList>;

// 获取推荐歌单，获取歌单标签列表
class SERVICE_DLL_EXPORT RecommendedPlaylistService : public QObject {
  Q_OBJECT
 public:
  void getHighquality(const QString& tag, qint32 offset, qint32 limit);
  void getTop(const QString& tag, qint32 offset, qint32 limit);
  void getCategories();

 private:
  error_code::ErrorCode getActualErrorCode(error_code::ErrorCode networkCode,
                                           const PlaylistItemListPtr& ptr);
  PlaylistItemListPtr parsePlaylistData(error_code::ErrorCode code,
                                        const QByteArray& data);
  PlaylistItem parsePlaylistItem(const QJsonObject& o);
 signals:
  void getHighqualityFinished(error_code::ErrorCode code,
                              PlaylistItemListPtr data);
  void getTopFinished(error_code::ErrorCode code, PlaylistItemListPtr data);
  void getCategoriesFinished(error_code::ErrorCode code,
                             QMap<QString, QStringList> categoriesMap);

 public slots:
  void onGetHighqualityFinished(error_code::ErrorCode, const QByteArray& data);
  void onGetTopFinished(error_code::ErrorCode, const QByteArray& data);
  void onGetCategoriesFinished(error_code::ErrorCode, const QByteArray& data);

 public:
  RecommendedPlaylistService(QObject* parent = nullptr);

 private:
  QStringList formatTags(const QJsonArray& array);
  UserItem formatCreator(const QJsonObject& object);
  QVector<UserItem> formatSubscribers(const QJsonArray& array);
  UserItem formatUserDataInComment(const QJsonObject& object);

 private:
  network::RecommendedPlaylistNetwork m_network;
};
}  // namespace service
#endif
