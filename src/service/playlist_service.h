#include <qglobal.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qtmetamacros.h>
#include <qtypes.h>
#include <qvariant.h>
#include <QObject>

#include "model/playlist_item_model.h"
#include "service_global.h"
#include "playlist_network.h"

namespace service {
class SERVICE_DLL_EXPORT PlaylistService : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
  Q_PROPERTY(model::PlaylistItemModel* highqualityPlaylists READ highqualityPlaylists CONSTANT)
  Q_PROPERTY(model::PlaylistItemModel* selectivePlaylists READ selectivePlaylists CONSTANT)

 public:
  Q_INVOKABLE void getHighqualityPlaylists(qint32 limit=5,qint32 tag=-1);
  Q_INVOKABLE void getSelectivePlaylists(qint32 limit=5,qint32 tag=-1);
  Q_INVOKABLE void getPlaylistsCatlist();
 signals:
  void highqualityPlaylistsStatus(network::error_code::ErrorCode code);
  void selectivePlaylistsStatus(network::error_code::ErrorCode code);
  void playlistsCatlistStatus(QVariantMap catlist);

 public slots:
  void onGetHighqualityPlaylists(network::error_code::ErrorCode,
                              const QByteArray& data);
  void onGetSelectivePlaylists(network::error_code::ErrorCode,
                                   const QByteArray& data);
  void onGetPlaylistsCatlist(network::error_code::ErrorCode,const QByteArray& data);


 public:
  PlaylistService(QObject* parent = nullptr);
  model::PlaylistItemModel* highqualityPlaylists() { return &m_highqualityPlaylists; }
  model::PlaylistItemModel* selectivePlaylists() { return &m_selectivePlaylists; }
private:
  QStringList formatTags(const QJsonArray& array);
  model::UserData formatCreator(const QJsonObject& object);
  QVector<model::UserData> formatSubscribers(const QJsonArray& array);
 private:
  network::PlaylistNetwork m_network;
  model::PlaylistItemModel m_highqualityPlaylists;
  model::PlaylistItemModel m_selectivePlaylists;
};
}  // namespace service