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

// 获取歌曲相关信息服务
class SERVICE_DLL_EXPORT SongService : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
  QML_NAMED_ELEMENT(SongService)
 public:
  Q_INVOKABLE void getSongUrl(qulonglong id);
  Q_INVOKABLE void checkSongEnable(qulonglong id);
  Q_INVOKABLE void getSongComments(qulonglong id);
  Q_INVOKABLE void getSongLyric(qulonglong id);
  Q_INVOKABLE void getSongNewLyric(qulonglong id);

  static QMap<qulonglong, model::MediaItem*> s_idItemMap;

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
