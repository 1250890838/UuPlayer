#ifndef PLAYLISTHUB_H
#define PLAYLISTHUB_H

#include <QObject>
#include <QQmlEngine>
namespace controller {

class FeaturedPlaylistHubController : public QObject {
  Q_OBJECT
  QML_ELEMENT
  QML_SINGLETON
 public:
  FeaturedPlaylistHubController();
};
}  // namespace controller
#endif // PLAYLISTHUB_H
