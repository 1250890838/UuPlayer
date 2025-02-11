#ifndef COMMENT_DATA_H
#define COMMENT_DATA_H

#include <QObject>
#include <QUrl>
#include "playlist_item_model.h"

namespace model {

struct PendantData {
  qulonglong id;
  QUrl imageUrl;
};

class CommentData {
  Q_GADGET
  Q_PROPERTY(qulonglong id READ id)
  Q_PROPERTY(UserData userData READ userData)
  Q_PROPERTY(PendantData pendant READ pendant)
  Q_PROPERTY(qulonglong time READ time)
  Q_PROPERTY(QString content READ content)
  Q_PROPERTY(qulonglong likedCount READ likedCount)

 public:
  CommentData() = default;

  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }

  UserData userData() const { return m_user; }
  void setUserData(UserData data) { m_user = data; }

  PendantData pendant() const { return m_pendant; }
  void setPendant(PendantData data) { m_pendant = data; }

  qulonglong time() const { return m_time; }
  void setTime(qulonglong time) { m_time = time; }

  QString content() const { return m_content; }
  void setContent(const QString& content) { m_content = content; }

  qulonglong likedCount() const { return m_likedCount; }
  void setLikedCount(qulonglong count) { m_likedCount = count; }

 private:
  qulonglong m_id;
  UserData m_user;
  PendantData m_pendant;    //头像挂饰
  qulonglong m_time;        //评论时间
  QString m_content;        //评论内容
  qulonglong m_likedCount;  //点赞数
};
}  // namespace model
#endif  // COMMENT_DATA_H
