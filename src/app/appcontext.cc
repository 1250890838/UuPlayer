#include "appcontext.h"

namespace app {
namespace {
AppContext* g_context = nullptr;
}

AppContext::AppContext(QObject* parent)
    : QObject(parent),
      m_playlists(&m_api),
      m_comments(&m_api),
      m_songs(&m_api),
      m_auth(&m_api),
      m_homepage(&m_api),
      m_play(&m_songs),
      m_lyrics(&m_songs, &m_play),
      m_login(&m_auth) {
  g_context = this;
}

AppContext* AppContext::instance() {
  return g_context;
}

}  // namespace app