#ifndef COMMENT_ITEM_H
#define COMMENT_ITEM_H

#include <QObject>
#include <QUrl>
#include "user_item.h"

namespace entities {

struct PendantData {
  qulonglong id;
  QUrl imageUrl;
};

class CommentItem {
  Q_GADGET
  Q_PROPERTY(qulonglong id READ id)
  Q_PROPERTY(UserItem userData READ userData)
  Q_PROPERTY(PendantData pendant READ pendant)
  Q_PROPERTY(qulonglong time READ time)
  Q_PROPERTY(QString content READ content)
  Q_PROPERTY(qulonglong likedCount READ likedCount)

 public:
  CommentItem() = default;

  qulonglong id() const { return m_id; }
  void setId(qulonglong id) { m_id = id; }

  UserItem userData() const { return m_user; }
  void setUserData(UserItem data) { m_user = data; }

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
  UserItem m_user;
  PendantData m_pendant;    //头像挂饰
  qulonglong m_time;        //评论时间
  QString m_content;        //评论内容
  qulonglong m_likedCount;  //点赞数
  // TODO:添加被回复数据
};
}  // namespace model

Q_DECLARE_METATYPE(entities::CommentItem)
#endif  // COMMENT_ITEM_H
