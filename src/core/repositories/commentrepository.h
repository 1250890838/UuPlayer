#pragma once

#include <QList>
#include <QObject>

#include "entities/commentitem.h"
#include "entities/types.h"

namespace core {

class ApiClient;

class CommentRepository : public QObject {
  Q_OBJECT
 public:
  explicit CommentRepository(ApiClient* api, QObject* parent = nullptr);

  void fetchPlaylistComments(qulonglong playlistId, int offset, int limit);

 signals:
  void playlistCommentsReady(error_code::ErrorCode code,
                             const QList<entities::CommentItem>& comments);

 private:
  ApiClient* m_api = nullptr;
};

}  // namespace core