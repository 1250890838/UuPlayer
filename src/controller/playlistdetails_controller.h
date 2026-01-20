#ifndef PLAYLISTDETAILS_H
#define PLAYLISTDETAILS_H

#include <QObject>
#include <QQmlEngine>

namespace controller {

class PlaylistDetailsController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
 public:
  explicit PlaylistDetailsController(QObject* parent = nullptr);

 signals:
};
}  // namespace controller
#endif // PLAYLISTDETAILS_H
