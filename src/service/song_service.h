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
  Q_INVOKABLE void getSongUrl(qulonglong id){}
  Q_INVOKABLE void checkSongEnable(qulonglong id){}
  Q_INVOKABLE void getSongComments(qulonglong id){}
  Q_INVOKABLE void getSongLyric(qulonglong id){}
  Q_INVOKABLE void getSongNewLyric(qulonglong id){}

 signals:

 public slots:

 public:
  SongService(QObject* parent = nullptr) {}

 private:
};
}  // namespace service
