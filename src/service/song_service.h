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
 void getSongUrl()
 signals:

 public slots:


 public:
  SongService(QObject* parent = nullptr){}

 private:


};
}  // namespace service
