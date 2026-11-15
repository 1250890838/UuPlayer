#pragma once

#include <QString>

namespace core::endpoints {

inline const QString host = QStringLiteral("http://localhost:3000");

inline QString qrKey() {
  return host + QStringLiteral("/login/qr/key");
}
inline QString qrCreate() {
  return host + QStringLiteral("/login/qr/create");
}
inline QString qrCheck() {
  return host + QStringLiteral("/login/qr/check");
}

inline QString topPlaylists() {
  return host + QStringLiteral("/top/playlist");
}
inline QString playlistCategories() {
  return host + QStringLiteral("/playlist/catlist");
}
inline QString playlistDetail() {
  return host + QStringLiteral("/playlist/detail");
}
inline QString playlistComments() {
  return host + QStringLiteral("/comment/playlist");
}

inline QString songUrl() {
  return host + QStringLiteral("/song/url/v1");
}
inline QString songLyric() {
  return host + QStringLiteral("/lyric");
}

}
