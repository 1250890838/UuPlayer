#ifndef NETWORK_API_H
#define NETWORK_API_H

#include <qstringliteral.h>
#include <QString>
#include <QStringLiteral>

namespace network_api {
const QString host = QStringLiteral("http://localhost:3000");

const QString apiGetQRCode = host + QStringLiteral("/login/qr/key");
const QString apiCreateQRCode = host + QStringLiteral("/login/qr/create");
const QString apiCheckQRCode = host + QStringLiteral("/login/qr/check");
const QString apiGetHighqualityPlaylists =
    host + QStringLiteral("/top/playlist/highquality");
const QString apiGetTopPlaylists = host + QStringLiteral("/top/playlist");
const QString apiCatlist = host + QStringLiteral("/playlist/catlist");
const QString apiPlaylistDetail = host + QStringLiteral("/playlist/detail");
const QString apiAlbumDetail = host + QStringLiteral("/album/detail");
const QString apiPlaylistTracks = host + QStringLiteral("/playlist/track/all");
const QString apiPlaylistComments = host + QStringLiteral("/comment/playlist");

const QString apiSongUrl = host + QStringLiteral("/song/url/v1");
const QString apiSongLyric = host + QStringLiteral("/lyric");
const QString apiSongNewLyric = host + QStringLiteral("lyric/new");

const QString apiMvComment = host + QStringLiteral("comment/mv");
const QString apiPlaylistComment = host + QStringLiteral("comment/playlist");
const QString apiAlbumComment = host + QStringLiteral("/comment/album");
const QString apiMusicComment = host + QStringLiteral("/comment/music");
}  // namespace network_api

#endif
