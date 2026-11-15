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
  const QJsonValue code = object.value(QStringLiteral("code"));
  if (code.isDouble() && code.toInt() != 200) {
    return std::nullopt;
  }
  return object;
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
  result.setId(
      object.value(QStringLiteral("userId")).toVariant().toULongLong());
  result.setName(object.value(QStringLiteral("nickname")).toString());
  result.setAvatarUrl(
      object.value(QStringLiteral("avatarUrl")).toString());
  result.setBackgroundUrl(
      object.value(QStringLiteral("backgroundUrl")).toString());
  result.setExpertTags(
      tags(object.value(QStringLiteral("expertTags")).toArray()));
  result.setBirthday(
      object.value(QStringLiteral("birthday")).toVariant().toULongLong());
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

entities::AlbumData album(const QJsonObject& object) {
  entities::AlbumData result;
  result.setId(object.value(QStringLiteral("id")).toVariant().toULongLong());
  result.setName(object.value(QStringLiteral("name")).toString());
  const QString pic = object.value(QStringLiteral("picUrl")).toString();
  result.setPicUrl(pic.isEmpty() ? QUrl()
                                 : QUrl(QStringLiteral("image://net/") + pic));
  return result;
}

entities::AristItem artist(const QJsonObject& object) {
  entities::AristItem result;
  result.setId(object.value(QStringLiteral("id")).toVariant().toULongLong());
  result.setName(object.value(QStringLiteral("name")).toString());
  return result;
}

QList<entities::AristItem> artists(const QJsonArray& array) {
  QList<entities::AristItem> result;
  for (const QJsonValue& value : array) {
    result.append(artist(value.toObject()));
  }
  return result;
}

entities::MediaItem mediaItem(const QJsonObject& object) {
  entities::MediaItem result;
  result.id = object.value(QStringLiteral("id")).toVariant().toULongLong();
  result.name = object.value(QStringLiteral("name")).toString();
  result.duration =
      object.value(QStringLiteral("dt")).toVariant().toULongLong();
  result.albumdata = album(object.value(QStringLiteral("al")).toObject());
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
  result.setUpdateTime(
      object.value(QStringLiteral("updateTime")).toVariant().toULongLong());
  result.setCoverUrl(
      object.value(QStringLiteral("coverImgUrl")).toString());
  result.setDesc(object.value(QStringLiteral("description")).toString());
  result.setPlayCount(
      object.value(QStringLiteral("playCount")).toVariant().toULongLong());
  result.setSubscribedCount(object.value(QStringLiteral("subscribedCount"))
                                .toVariant()
                                .toULongLong());
  result.setTags(tags(object.value(QStringLiteral("tags")).toArray()));
  result.setCreator(user(object.value(QStringLiteral("creator")).toObject()));
  result.setSubscribers(
      users(object.value(QStringLiteral("subscribers")).toArray()));
  result.setSubscribed(object.value(QStringLiteral("subscribed")).toBool());
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
  result.setTime(
      object.value(QStringLiteral("time")).toVariant().toULongLong());
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

namespace {

QList<entities::LyricLine> parseLrc(const QString& lrc) {
  static const QRegularExpression kLine(
      QStringLiteral(R"(\[(\d{2}):(\d{2})\.(\d{2,3})\]\s*(.*))"));
  QList<entities::LyricLine> result;
  for (const QString& raw : lrc.split(QLatin1Char('\n'))) {
    const QRegularExpressionMatch match = kLine.match(raw);
    if (!match.hasMatch()) {
      continue;
    }
    const int minutes = match.captured(1).toInt();
    const int seconds = match.captured(2).toInt();
    const int milliseconds = match.captured(3).toInt();
    const quint64 startMs =
        static_cast<quint64>(minutes * 60000 + seconds * 1000 + milliseconds);
    if (!result.isEmpty()) {
      result.last().endMs = startMs;
    }
    entities::LyricLine line;
    line.plainText = match.captured(4).trimmed();
    line.startMs = startMs;
    result.append(line);
  }
  if (!result.isEmpty()) {
    result.last().endMs = result.last().startMs + 500;
  }
  return result;
}

QList<entities::LyricLine> parseYrc(const QString& yrc) {
  static const QRegularExpression kLine(QStringLiteral(R"(^\[(\d+),(\d+)\])"));
  static const QRegularExpression kToken(
      QStringLiteral(R"(\((\d+),(\d+),(-?\d+)\)([^(\r\n]+))"));

  QList<entities::LyricLine> result;
  for (const QString& raw : yrc.split(QLatin1Char('\n'),
                                      Qt::SkipEmptyParts)) {
    const QString text = raw.trimmed();
    const QRegularExpressionMatch header = kLine.match(text);
    if (!header.hasMatch()) {
      continue;
    }
    entities::LyricLine line;
    line.startMs = header.captured(1).toULongLong();
    line.endMs = line.startMs + header.captured(2).toULongLong();

    const QString rest = text.mid(header.capturedLength(0));
    auto it = kToken.globalMatch(rest);
    while (it.hasNext()) {
      const QRegularExpressionMatch token = it.next();
      entities::LyricToken t;
      t.startMs = token.captured(1).toULongLong();
      t.endMs = t.startMs + token.captured(2).toULongLong();
      t.text = token.captured(4);
      line.tokens.push_back(t);
      line.plainText += t.text;
    }
    if (line.tokens.isEmpty()) {
      line.plainText = rest;
    }
    result.append(line);
  }
  return result;
}

}  // namespace

QList<entities::LyricLine> lyricLines(const QJsonObject& body) {
  const QJsonObject yrcObject = body.value(QStringLiteral("yrc")).toObject();
  const QString yrc = yrcObject.value(QStringLiteral("lyric")).toString();
  if (!yrc.isEmpty()) {
    return parseYrc(yrc);
  }
  return parseLrc(body.value(QStringLiteral("lrc"))
                      .toObject()
                      .value(QStringLiteral("lyric"))
                      .toString());
}

entities::HomePageInfo homepageInfo(const QJsonObject& body) {
  entities::HomePageInfo result;
  const QJsonObject data = body.value(QStringLiteral("data")).toObject();
  const QJsonArray blocks = data.value(QStringLiteral("blocks")).toArray();

  for (const QJsonValue& blockValue : blocks) {
    const QJsonObject block = blockValue.toObject();
    const QString code = block.value(QStringLiteral("blockCode")).toString();

    if (code == QStringLiteral("HOMEPAGE_BANNER")) {
      const QJsonArray banners = block.value(QStringLiteral("extInfo"))
                                     .toObject()
                                     .value(QStringLiteral("banners"))
                                     .toArray();
      for (const QJsonValue& value : banners) {
        const QJsonObject object = value.toObject();
        entities::Banner banner;
        banner.picUrl = object.value(QStringLiteral("pic")).toString();
        banner.title = object.value(QStringLiteral("typeTitle")).toString();
        banner.titleColor =
            QColor::fromString(object.value(QStringLiteral("titleColor")).toString());
        result.banners.append(banner);
      }
    }

    if (code == QStringLiteral("HOMEPAGE_BLOCK_PLAYLIST_RCMD")) {
      const QJsonArray creatives =
          block.value(QStringLiteral("creatives")).toArray();
      for (const QJsonValue& creativeValue : creatives) {
        const QJsonArray resources = creativeValue.toObject()
                                         .value(QStringLiteral("resources"))
                                         .toArray();
        for (const QJsonValue& resourceValue : resources) {
          const QJsonObject resource = resourceValue.toObject();
          const QJsonObject element =
              resource.value(QStringLiteral("uiElement")).toObject();
          entities::RcmdPlaylistInfo info;
          info.mainTitle = element.value(QStringLiteral("mainTitle"))
                               .toObject()
                               .value(QStringLiteral("title"))
                               .toString();
          info.subTitle = element.value(QStringLiteral("subTitle"))
                              .toObject()
                              .value(QStringLiteral("title"))
                              .toString();
          info.picUrl = element.value(QStringLiteral("image"))
                            .toObject()
                            .value(QStringLiteral("imageUrl"))
                            .toString();
          for (const QJsonValue& label :
               element.value(QStringLiteral("labelTexts")).toArray()) {
            info.labels.append(label.toString());
          }
          info.targetId = resource.value(QStringLiteral("resourceId"))
                              .toVariant()
                              .toULongLong();
          info.playCount = resource.value(QStringLiteral("resourceExtInfo"))
                               .toObject()
                               .value(QStringLiteral("playCount"))
                               .toVariant()
                               .toULongLong();
          result.rcmdPlaylists.append(info);
        }
      }
    }

    if (code == QStringLiteral("HOMEPAGE_BLOCK_STYLE_RCMD")) {
      const QJsonArray creatives =
          block.value(QStringLiteral("creatives")).toArray();
      for (const QJsonValue& creativeValue : creatives) {
        const QJsonArray resources = creativeValue.toObject()
                                         .value(QStringLiteral("resources"))
                                         .toArray();
        for (const QJsonValue& resourceValue : resources) {
          const QJsonObject resource = resourceValue.toObject();
          const QJsonObject element =
              resource.value(QStringLiteral("uiElement")).toObject();
          entities::RcmdSongInfo info;
          info.mainTitle = element.value(QStringLiteral("mainTitle"))
                               .toObject()
                               .value(QStringLiteral("title"))
                               .toString();
          info.subTitle = element.value(QStringLiteral("subTitle"))
                              .toObject()
                              .value(QStringLiteral("title"))
                              .toString();
          info.picUrl = element.value(QStringLiteral("image"))
                            .toObject()
                            .value(QStringLiteral("imageUrl"))
                            .toString();
          info.targetId = resource.value(QStringLiteral("resourceId"))
                              .toVariant()
                              .toULongLong();
          const QJsonArray artistArray =
              resource.value(QStringLiteral("resourceExtInfo"))
                  .toObject()
                  .value(QStringLiteral("artists"))
                  .toArray();
          for (const QJsonValue& artistValue : artistArray) {
            const QJsonObject artistObject = artistValue.toObject();
            info.artistNames.append(
                artistObject.value(QStringLiteral("name")).toString());
            info.artistIds.append(artistObject.value(QStringLiteral("id"))
                                      .toVariant()
                                      .toULongLong());
          }
          result.rcmdSongs.append(info);
        }
      }
    }
  }
  return result;
}

}  // namespace core::mappers