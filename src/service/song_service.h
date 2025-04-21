#include "song_network.h"
#include "model/media_item_model.h"

#include <qglobal.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include <qtmetamacros.h>
#include <qtypes.h>
#include <qvariant.h>
#include <QObject>

#include "service_global.h"

namespace service {
class SERVICE_DLL_EXPORT SongService : public QObject {
  Q_OBJECT
 public:
  Q_INVOKABLE void getSongUrl(qulonglong id,model::MediaItem* item);
  Q_INVOKABLE void checkSongEnable(qulonglong id);
  Q_INVOKABLE void getSongComments(qulonglong id);
  Q_INVOKABLE void getSongLyric(qulonglong id);
  Q_INVOKABLE void getSongNewLyric(qulonglong id);
 public:
  SongService(QObject* parent = nullptr);
 public slots:
  void onGetSongUrlFinished(network::error_code::ErrorCode code,const QByteArray&,void* item);
 private:
  network::SongNetwork m_network;
 signals:
  void songUrlStatus(network::error_code::ErrorCode code);
};
}  // namespace service
