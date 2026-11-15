#pragma once

#include <QByteArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QStringList>
#include <QUrl>
#include <optional>

#include "entities/commentitem.h"
#include "entities/homepageinfo.h"
#include "entities/lyrictypes.h"
#include "entities/mediaitem.h"
#include "entities/playlistitem.h"
#include "entities/useritem.h"

namespace core::mappers {

std::optional<QJsonObject> apiObject(const QByteArray& body);

QStringList tags(const QJsonArray& array);

entities::UserItem user(const QJsonObject& object);
QList<entities::UserItem> users(const QJsonArray& array);

entities::AlbumData album(const QJsonObject& object);
entities::AristItem artist(const QJsonObject& object);
QList<entities::AristItem> artists(const QJsonArray& array);

entities::MediaItem mediaItem(const QJsonObject& object);
QList<entities::MediaItem> mediaItems(const QJsonArray& array);

entities::PlaylistItem playlistItem(const QJsonObject& object);
QList<entities::PlaylistItem> playlists(const QJsonArray& array);

entities::CommentItem comment(const QJsonObject& object);
QList<entities::CommentItem> comments(const QJsonArray& array);

QList<entities::LyricLine> lyricLines(const QJsonObject& body);
entities::HomePageInfo homepageInfo(const QJsonObject& body);

}  // namespace core::mappers