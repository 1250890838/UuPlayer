#include "mappers.h"

#include <QJsonDocument>
#include <QJsonValue>
#include <QRegularExpression>

namespace core::mappers {

std::optional<QJsonObject> apiObject(const QByteArray& body) {
  const QJsonDocument doc = QJsonDocument::fromJson(body);
  if (!doc.isObject()) {
    return std::nullopt;
  }
  const QJsonObject object = doc.object();
  const auto code = object.value(QStringLiteral("code"));
  if (code.isDouble() && code.toInt() != 200) {
    return std::nullopt;
  }
  return object;
}

QUrl networkImage(const QString& rawUrl) {
  if (rawUrl.isEmpty()) {
    return {};
  }
  return QUrl(QStringLiteral("image://net/") + rawUrl);
}

QStringList tags(const QJsonArray& array) {
  QStringList result;
  for (const QJsonValue& value : array) {
    result.append(value.toString());
  }
  return result;
}

entities::UserItem user(const QJsonObject& object) {
  entities::UserItem result;
  result.setId(object.value(QStringLiteral("userId"))
                   .toVariant()
                   .toULongLong());
  result.setName(object.value(QStringLiteral("nickname")).toString());
  result.setAvatarUrl(
      networkImage(object.value(QStringLiteral("avatarUrl")).toString()));
  result.setBackgroundUrl(networkImage(
      object.value(QStringLiteral("backgroundUrl")).toString()));
  result.setExpertTags(tags(object.value(QStringLiteral("expertTags")).toArray()));
  result.setBirthday(object.value(QStringLiteral("birthday"))
                         .toVariant()
                         .toULongLong());
  result.setFollowed(object.value(QStringLiteral("followed")).toBool());
  result.setGender(
      static_cast<qint8>(object.value(QStringLiteral("gender")).toInt()));
  result.setDesc(object.value(QStringLiteral("description")).toString());
  return result;
}

QList<entities::UserItem> users(const QJsonArray& array) {
  QList<entities::UserItem> result;
  for (const QJsonValue& value : array) {
    result.append(user(value.toObject()));
  }
  return result;
}

entities::AlbumItem album(const QJsonObject& object) {
  entities::AlbumItem result;
  result.setId(object.value(QStringLiteral("id")).toVariant().toULongLong());
  result.setName(object.value(QStringLiteral("name")).toString());
  result.setPicUrl(
      networkImage(object.value(QStringLiteral("picUrl")).toString()));
  return result;
}

entities::ArtistItem artist(const QJsonObject& object) {
  entities::ArtistItem result;
  result.setId(object.value(QStringLiteral("id")).toVariant().toULongLong());
  result.setName(object.value(QStringLiteral("name")).toString());
  return result;
}

QList<entities::ArtistItem> artists(const QJsonArray& array) {
  QList<entities::ArtistItem> result;
  for (const QJsonValue& value : array) {
    result.append(artist(value.toObject()));
  }
  return result;
}

entities::MediaItem mediaItem(const QJsonObject& object) {
  entities::MediaItem result;
  result.id = object.value(QStringLiteral("id")).toVariant().toULongLong();
  result.name = object.value(QStringLiteral("name")).toString();
  result.duration = object.value(QStringLiteral("dt")).toVariant().toULongLong();
  result.album = album(object.value(QStringLiteral("al")).toObject());
  result.artists = artists(object.value(QStringLiteral("ar")).toArray());
  return result;
}

QList<entities::MediaItem> mediaItems(const QJsonArray& array) {
  QList<entities::MediaItem> result;
  for (const QJsonValue& value : array) {
    result.append(mediaItem(value.toObject()));
  }
  return result;
}

entities::PlaylistItem playlistItem(const QJsonObject& object) {
  entities::PlaylistItem result;
  result.setId(object.value(QStringLiteral("id")).toVariant().toULongLong());
  result.setName(object.value(QStringLiteral("name")).toString());
  result.setUserId(
      object.value(QStringLiteral("userId")).toVariant().toULongLong());
  result.setCreateTime(
      object.value(QStringLiteral("createTime")).toVariant().toULongLong());
  result.setDesc(object.value(QStringLiteral("description")).toString());
  result.setCoverUrl(
      networkImage(object.value(QStringLiteral("coverImgUrl")).toString()));
  result.setPlayCount(
      object.value(QStringLiteral("playCount")).toVariant().toULongLong());
  result.setSubscribedCount(object.value(QStringLiteral("subscribedCount"))
                                .toVariant()
                                .toULongLong());
  result.setTags(tags(object.value(QStringLiteral("tags")).toArray()));
  result.setCreator(user(object.value(QStringLiteral("creator")).toObject()));
  result.setSubscribers(
      users(object.value(QStringLiteral("subscribers")).toArray()));
  result.setSubscribed(
      object.value(QStringLiteral("subscribed")).toBool());
  result.setMediaItems(
      mediaItems(object.value(QStringLiteral("tracks")).toArray()));
  return result;
}

QList<entities::PlaylistItem> playlists(const QJsonArray& array) {
  QList<entities::PlaylistItem> result;
  for (const QJsonValue& value : array) {
    result.append(playlistItem(value.toObject()));
  }
  return result;
}

entities::CommentItem comment(const QJsonObject& object) {
  entities::CommentItem result;
  result.setId(
      object.value(QStringLiteral("commentId")).toVariant().toULongLong());
  result.setContent(object.value(QStringLiteral("content")).toString());
  result.setLikedCount(
      object.value(QStringLiteral("likedCount")).toVariant().toULongLong());
  result.setTime(object.value(QStringLiteral("time")).toVariant().toULongLong());
  result.setUserData(user(object.value(QStringLiteral("user")).toObject()));
  return result;
}

QList<entities::CommentItem> comments(const QJsonArray& array) {
  QList<entities::CommentItem> result;
  for (const QJsonValue& value : array) {
    result.append(comment(value.toObject()));
  }
  return result;
}

QVariantList lyrics(const QString& lrc) {
  static const QRegularExpression kLine(
      QStringLiteral(R"(\[(\d{2}):(\d{2})\.(\d{2,3})\]\s*(.*))"));
  QVariantList result;
  for (const QString& line : lrc.split(QLatin1Char('\n'))) {
    const QRegularExpressionMatch match = kLine.match(line);
    if (!match.hasMatch()) {
      continue;
    }
    const int minutes = match.captured(1).toInt();
    const int seconds = match.captured(2).toInt();
    const int milliseconds = match.captured(3).toInt();
    QVariantMap entry;
    entry.insert(QStringLiteral("lyric"), match.captured(4).trimmed());
    entry.insert(QStringLiteral("end"),
                 minutes * 60000 + seconds * 1000 + milliseconds);
    result.append(entry);
  }
  return result;
}

}
