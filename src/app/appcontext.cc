#include "appcontext.h"

namespace app {

AppContext::AppContext(QObject* parent)
    : QObject(parent),
      m_playlists(&m_api),
      m_comments(&m_api),
      m_songs(&m_api),
      m_auth(&m_api),
      m_play(&m_songs),
      m_login(&m_auth),
      m_hub(&m_playlists),
      m_detail(&m_playlists, &m_comments, &m_play) {}

}
