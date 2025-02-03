#ifndef PLAYLISTDETAIL_H
#define PLAYLISTDETAIL_H

#include <QObject>

namespace model{
class PlaylistDetail : public QObject {
  Q_OBJECT
 public:
  explicit PlaylistDetail(QObject* parent = nullptr);

 signals:
};
}
#endif  // PLAYLISTDETAIL_H
