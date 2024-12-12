#ifndef NETWORK_API_H
#define NETWORK_API_H

#include <QStringLiteral>
#include <QString>

namespace network_api {
    const QString host=QStringLiteral("http://localhost:3000");

    const QString apiGetQRCode=host + QStringLiteral("/login/qr/key");
    const QString apiCreateQRCode=host + QStringLiteral("/login/qr/create");
    const QString apiCheckQRCode=host + QStringLiteral("/login/qr/check");
}

#endif