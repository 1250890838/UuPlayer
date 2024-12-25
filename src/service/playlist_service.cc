#include "playlist_service.h"
#include <qobject.h>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QThread>
#include <QTimer>
#include "playlist_network.h"

namespace service {

    PlaylistService::PlaylistService(QObject* parent):QObject(parent){
        using namespace network;
        connect(&m_network,&PlaylistNetwork::getHighqualityPlaylistsFinished,this,&PlaylistService::onGetHighqualityPlaylists);
        connect(&m_network,&PlaylistNetwork::getSelectivePlaylistsFinished,this,&PlaylistService::onGetSelectivePlaylists);
    }

void PlaylistService::getHighqualityPlaylists(qint32 limit,qint32 tag) {
    m_network.getHighqualityPlaylists(limit,tag);
}

void PlaylistService::getSelectivePlaylists(qint32 limit,qint32 tag) {
    m_network.getSelectivePlaylists(limit, tag);
}

void PlaylistService::onGetHighqualityPlaylists(network::error_code::ErrorCode,
                               const QByteArray& data){
                                
}
void PlaylistService::onGetSelectivePlaylists(network::error_code::ErrorCode,
                             const QByteArray& data){

                             }
}  // namespace service


