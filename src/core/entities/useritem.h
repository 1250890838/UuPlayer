#pragma once

#include <QString>
#include <QStringList>
#include <QUrl>
#include <QtQml/qqmlregistration.h>

namespace entities {

class UserItem {
  Q_GADGET
  QML_VALUE_TYPE(userItem)
  Q_PROPERTY(qulonglong id READ id WRITE setId)
  Q_PROPERTY(QString name READ name WRITE setName)
  Q_PROPERTY(QUrl avatarUrl READ avatarUrl WRITE setAvatarUrl)
  Q_PROPERTY(QUrl backgroundUrl READ backgroundUrl WRITE setBackgroundUrl)
  Q_PROPERTY(QStringList expertTags READ expertTags WRITE setExpertTags)
  Q_PROPERTY(qulonglong birthday READ birthday WRITE setBirthday)
  Q_PROPERTY(bool followed READ followed WRITE setFollowed)
  Q_PROPERTY(qint8 gender READ gender WRITE setGender)
  Q_PROPERTY(QString desc READ desc WRITE setDesc)

 public:
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  QString name() const { return m_name; }
  void setName(const QString& name) { m_name = name; }
  QUrl avatarUrl() const { return m_avatarUrl; }
  void setAvatarUrl(const QUrl& url) { m_avatarUrl = url; }
  QUrl backgroundUrl() const { return m_backgroundUrl; }
  void setBackgroundUrl(const QUrl& url) { m_backgroundUrl = url; }
  QStringList expertTags() const { return m_expertTags; }
  void setExpertTags(const QStringList& tags) { m_expertTags = tags; }
  qulonglong birthday() const { return m_birthday; }
  void setBirthday(qulonglong birthday) { m_birthday = birthday; }
  bool followed() const { return m_followed; }
  void setFollowed(bool followed) { m_followed = followed; }
  qint8 gender() const { return m_gender; }
  void setGender(qint8 gender) { m_gender = gender; }
  QString desc() const { return m_desc; }
  void setDesc(const QString& desc) { m_desc = desc; }

  bool operator==(const UserItem&) const = default;

 private:
  qulonglong m_id = 0;
  QString m_name;
  QUrl m_avatarUrl;
  QUrl m_backgroundUrl;
  QStringList m_expertTags;
  qulonglong m_birthday = 0;
  bool m_followed = false;
  qint8 m_gender = 0;
  QString m_desc;
};

}
