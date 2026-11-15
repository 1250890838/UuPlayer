#pragma once

#include <QObject>

#include "apiclient.h"
#include "repositories/authrepository.h"
#include "repositories/commentrepository.h"
#include "repositories/homepagerepository.h"
#include "repositories/playlistrepository.h"
#include "repositories/songrepository.h"
#include "viewmodels/logincontroller.h"
#include "viewmodels/lyricsviewcontroller.h"
#include "viewmodels/playcontroller.h"

namespace app {

class AppContext : public QObject {
  Q_OBJECT
 public:
  static AppContext* instance();

  explicit AppContext(QObject* parent = nullptr);

  core::ApiClient* api() { return &m_api; }
  core::PlaylistRepository* playlists() { return &m_playlists; }
  core::CommentRepository* comments() { return &m_comments; }
  core::SongRepository* songs() { return &m_songs; }
  core::AuthRepository* auth() { return &m_auth; }
  core::HomepageRepository* homepage() { return &m_homepage; }
  viewmodel::PlayController* play() { return &m_play; }
  viewmodel::LyricsViewController* lyrics() { return &m_lyrics; }
  viewmodel::LoginController* login() { return &m_login; }

 private:
  core::ApiClient m_api;
  core::PlaylistRepository m_playlists;
  core::CommentRepository m_comments;
  core::SongRepository m_songs;
  core::AuthRepository m_auth;
  core::HomepageRepository m_homepage;
  viewmodel::PlayController m_play;
  viewmodel::LyricsViewController m_lyrics;
  viewmodel::LoginController m_login;
};

}  // namespace app