#include <qtmetamacros.h>
#include <qtypes.h>
#include <QObject>

#include "model/media_item_model.h"

#include "service_global.h"
#include "playlist_network.h"

namespace service {
class SERVICE_DLL_EXPORT PlaylistService : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
 public:
  Q_INVOKABLE void getHighqualityPlaylists(qint32 limit,qint32 tag);
  Q_INVOKABLE void getSelectivePlaylists(qint32 limit,qint32 tag);
 signals:
 public slots:
  void onGetHighqualityPlaylists(network::error_code::ErrorCode,
                              const QByteArray& data);
  void onGetSelectivePlaylists(network::error_code::ErrorCode,
                                   const QByteArray& data);


 public:
  PlaylistService(QObject* parent = nullptr);

 private:
  network::PlaylistNetwork m_network;
};
}  // namespace service