#include <qglobal.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qtmetamacros.h>
#include <qtypes.h>
#include <qvariant.h>
#include <QObject>

#include "model/playlist_item_model.h"
#include "playlist_network.h"
#include "service_global.h"

namespace service {
class SERVICE_DLL_EXPORT PlaylistService : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
  QML_NAMED_ELEMENT(PlaylistsService)
  Q_PROPERTY(model::PlaylistItemModel* highqualityPlaylists READ
                 highqualityPlaylists CONSTANT)
  Q_PROPERTY(model::PlaylistItemModel* selectivePlaylists READ
                 selectivePlaylists CONSTANT)

 public:
  Q_INVOKABLE void getHighqualityPlaylists(qint32 limit = 5, qint32 tag = -1);
  Q_INVOKABLE void getSelectivePlaylists();
  Q_INVOKABLE void getPlaylistsCatlist();
  Q_INVOKABLE void getPlaylistDetail(qulonglong id, model::PlaylistItem* item);
  Q_INVOKABLE void getPlaylistTracks(qulonglong id, model::PlaylistItem* item);
  Q_INVOKABLE void getPlaylistComments(qulonglong id,
                                       model::PlaylistItem* item);

  Q_INVOKABLE void setCurrLimit(qint32 limit) { m_currLimit = limit; }
  Q_INVOKABLE void setCurrCat(const QString& cat) { m_currCat = cat; }
  Q_INVOKABLE void setCurrOffset(qint32 offset) { m_currOffset = offset; }
 signals:
  void highqualityPlaylistsStatus(network::error_code::ErrorCode code);
  void selectivePlaylistsStatus(network::error_code::ErrorCode code);
  void playlistsCatlist(QVariantMap catlist);

 public slots:
  void onGetHighqualityPlaylists(network::error_code::ErrorCode,
                                 const QByteArray& data);
  void onGetSelectivePlaylists(network::error_code::ErrorCode,
                               const QByteArray& data);
  void onGetPlaylistsCatlist(network::error_code::ErrorCode,
                             const QByteArray& data);
  void onGetPlaylistDetail(network::error_code::ErrorCode,
                           const QByteArray& data, void* item);
  void onGetPlaylistTracks(network::error_code::ErrorCode,
                           const QByteArray& data, void* item);

 public:
  PlaylistService(QObject* parent = nullptr);
  model::PlaylistItemModel* highqualityPlaylists() {
    return &m_highqualityPlaylists;
  }
  model::PlaylistItemModel* selectivePlaylists() {
    return &m_selectivePlaylists;
  }

 private:
  QStringList formatTags(const QJsonArray& array);
  model::UserData formatCreator(const QJsonObject& object);
  QVector<model::UserData> formatSubscribers(const QJsonArray& array);

 private:
  network::PlaylistNetwork m_network;
  model::PlaylistItemModel m_highqualityPlaylists;
  model::PlaylistItemModel m_selectivePlaylists;
  QVariantMap m_catlist;

  qint32 m_currLimit;
  qint32 m_currOffset;
  QString m_currCat;
};
}  // namespace service
