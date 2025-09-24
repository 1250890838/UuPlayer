#include "local_song_service.h"

#include <QVariantMap>


LocalSongService::LocalSongService(QObject* parent)
    : QObject{parent} {}
QVariantMap LocalSongService::seachSongsInSetPaths() {
  QVariantMap varMap;

}

void LocalSongService::setSeachSongsPaths(const QVariantMap& map) {

}
