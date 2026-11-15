#pragma once

#include <QString>
#include <QUrl>
#include <QtQml/qqmlregistration.h>

#include "useritem.h"

namespace entities {

struct PendantData {
  Q_GADGET
  QML_VALUE_TYPE(pendantData)
  Q_PROPERTY(qulonglong id MEMBER id)
  Q_PROPERTY(QUrl imageUrl MEMBER imageUrl)

 public:
  qulonglong id = 0;
  QUrl imageUrl;
};

class CommentItem {
  Q_GADGET
  QML_VALUE_TYPE(commentItem)
  Q_PROPERTY(qulonglong id READ id)
  Q_PROPERTY(UserItem userData READ userData)
  Q_PROPERTY(PendantData pendant READ pendant)
  Q_PROPERTY(qulonglong time READ time)
  Q_PROPERTY(QString content READ content)
  Q_PROPERTY(qulonglong likedCount READ likedCount)

 public:
  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }
  UserItem userData() const { return m_user; }
  void setUserData(const UserItem& user) { m_user = user; }
  PendantData pendant() const { return m_pendant; }
  void setPendant(const PendantData& pendant) { m_pendant = pendant; }
  qulonglong time() const { return m_time; }
  void setTime(qulonglong time) { m_time = time; }
  QString content() const { return m_content; }
  void setContent(const QString& content) { m_content = content; }
  qulonglong likedCount() const { return m_likedCount; }
  void setLikedCount(qulonglong count) { m_likedCount = count; }

  bool operator==(const CommentItem& other) const { return id() == other.id(); }

 private:
  qulonglong m_id = 0;
  UserItem m_user;
  PendantData m_pendant;
  qulonglong m_time = 0;
  QString m_content;
  qulonglong m_likedCount = 0;
};

}
