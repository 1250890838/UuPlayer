#ifndef NETWORK_API_H
#define NETWORK_API_H

#include <qstringliteral.h>
#include <QStringLiteral>
#include <QString>

namespace network_api {
    const QString host=QStringLiteral("http://localhost:3000");

    const QString apiGetQRCode=host + QStringLiteral("/login/qr/key");
    const QString apiCreateQRCode=host + QStringLiteral("/login/qr/create");
    const QString apiCheckQRCode=host + QStringLiteral("/login/qr/check");
    const QString apiGetHighqualityPlaylists=host+QStringLiteral("/top/playlist/highquality");
    const QString apiGetSelectivePlaylists=host+QStringLiteral("/top/playlist");
    const QString apiCatlist=host+QStringLiteral("/playlist/catlist");
    const QString apiPlaylistDetail=host+QStringLiteral("/playlist/detail");
    const QString apiPlaylistTracks=host+QStringLiteral("/playlist/track/all");
}

#endif
