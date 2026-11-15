#pragma once

#include <QByteArray>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QStringList>
#include <QUrl>
#include <optional>

#include "entities/commentitem.h"
#include "entities/mediaitem.h"
#include "entities/playlistitem.h"
#include "entities/useritem.h"

namespace core {

namespace mappers {

std::optional<QJsonObject> apiObject(const QByteArray& body);

QUrl networkImage(const QString& rawUrl);

QStringList tags(const QJsonArray& array);

entities::UserItem user(const QJsonObject& object);
QList<entities::UserItem> users(const QJsonArray& array);

entities::AlbumItem album(const QJsonObject& object);
entities::ArtistItem artist(const QJsonObject& object);
QList<entities::ArtistItem> artists(const QJsonArray& array);

entities::MediaItem mediaItem(const QJsonObject& object);
QList<entities::MediaItem> mediaItems(const QJsonArray& array);

entities::PlaylistItem playlistItem(const QJsonObject& object);
QList<entities::PlaylistItem> playlists(const QJsonArray& array);
entities::CommentItem comment(const QJsonObject& object);
QList<entities::CommentItem> comments(const QJsonArray& array);

QVariantList lyrics(const QString& lrc);

}
}
