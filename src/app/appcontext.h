#pragma once

#include <QObject>

#include "apiclient.h"
#include "repositories/authrepository.h"
#include "repositories/commentrepository.h"
#include "repositories/playlistrepository.h"
#include "repositories/songrepository.h"
#include "viewmodels/logincontroller.h"
#include "viewmodels/playcontroller.h"
#include "viewmodels/playlistdetailcontroller.h"
#include "viewmodels/playlisthubcontroller.h"

namespace app {

class AppContext : public QObject {
  Q_OBJECT
 public:
  explicit AppContext(QObject* parent = nullptr);

  core::PlaylistRepository* playlists() { return &m_playlists; }
  core::CommentRepository* comments() { return &m_comments; }
  core::SongRepository* songs() { return &m_songs; }
  core::AuthRepository* auth() { return &m_auth; }
  viewmodel::PlayController* play() { return &m_play; }
  viewmodel::LoginController* login() { return &m_login; }
  viewmodel::PlaylistHubController* hub() { return &m_hub; }
  viewmodel::PlaylistDetailController* detail() { return &m_detail; }

 private:
  core::ApiClient m_api;
  core::PlaylistRepository m_playlists;
  core::CommentRepository m_comments;
  core::SongRepository m_songs;
  core::AuthRepository m_auth;
  viewmodel::PlayController m_play;
  viewmodel::LoginController m_login;
  viewmodel::PlaylistHubController m_hub;
  viewmodel::PlaylistDetailController m_detail;
};

}
