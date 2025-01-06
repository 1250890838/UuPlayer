import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import components 1.0
import service 1.0

Item {
    id: root

    Connections {
        target: PlaylistsService
        onPlaylistsCatlistChanged: {
            console.log("PlaylistsService.onPlaylistsCatlistChanged");
            console.log(PlaylistsService.playlistsCatlist);
        }
    }

    Pane {
        anchors.fill: parent
        background: Rectangle {
            color: "transparent"
        }
        Text {
            id: title
            anchors.centerIn: parent
            text: "歌单广场"
            font.pixelSize: 40
            font.bold: true
            color: "black"
        }
    }
    Component.onCompleted: {
        PlaylistsService.getPlaylistsCatlist();
    }
}
