import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import components 1.0
import assets 1.0

Item {
    id: root
    property var mediaData
    Rectangle {
        id: container
        anchors.fill: parent
        color: "#fafafa"

        Rectangle {
            width: parent.width
            height: 1
            color: "#e8e6e5"
            anchors.top: parent.top
        }

        RowLayout {
            id: containerRowLayout
            anchors.fill: parent
            anchors.leftMargin: 30
            anchors.rightMargin: 30
            AlbumDisplay {
                id: albumDisplay
                implicitHeight: 60
                implicitWidth: 60
                imageUrl: mediaData.album.picUrl
            }

            Column {
                id: nameColumn
                Layout.alignment: Layout.Left
                width: 150
                Label {
                    id: songName
                    text: mediaData.name
                    elide: Text.ElideRight
                    width: parent.width
                }
                Label {
                    id: spilter
                    text: "-"
                }
                Label {
                    id: artistsName
                    elide: Text.ElideRight
                    width: parent.width
                    text: {
                        var names = mediaData.artists.map(artist => artist.name)
                        return names.join("/ ")
                    }
                }
            }

            Column {
                id: playbackCenterColumn
                Row {
                    id: playbackButtons
                    spacing: 25
                    anchors.horizontalCenter: parent.horizontalCenter
                    IconButton {
                        icon: Icons.playbackBarPreviousIcon
                        hoveredIcon: Icons.playbackBarPreviousIcon
                        width: 21
                        height: 21
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    IconButton {
                        icon: Icons.playbackBarPlayIcon
                        hoveredIcon: Icons.playbackBarPlayIcon
                        width: 41
                        height: 41
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    IconButton {
                        icon: Icons.playbackBarNextIcon
                        hoveredIcon: Icons.playbackBarNextIcon
                        width: 21
                        height: 21
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    IconButton {
                        icon: Icons.playbackModeSequentialIcon
                        hoveredIcon: Icons.playbackModeSequentialIcon
                        width: 23
                        height: 23
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
                Row {
                    Label {
                        id: currentTime
                        text: Utils.formatTime(slider.value)
                        width: 50
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 12
                    }
                    UuSlider {
                        id: playbackSlider
                        width: 310
                        from: 0
                        to: PlayService.duration
                    }
                    Label {
                        id: totalTime
                        text: Utils.formatTime(mediaPlayer.duration)
                        width: 50
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 12
                    }
                }
            }
        }
    }
}
