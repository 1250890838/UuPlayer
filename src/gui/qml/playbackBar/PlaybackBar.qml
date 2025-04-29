import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import components 1.0
import service.api 1.0
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
                running: PlayService.playing
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
                        width: 28
                        height: 28
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: PlayService.previous()
                    }
                    IconButton {
                        id: playbackButton
                        icon: PlayService.playing ? Icons.playbackBarPauseIcon : Icons.playbackBarPlayIcon
                        hoveredIcon: this.icon
                        width: 41
                        height: 41
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: {
                            if (PlayService.playing)
                                PlayService.pause()
                            else
                                PlayService.play()
                        }
                    }
                    IconButton {
                        icon: Icons.playbackBarNextIcon
                        hoveredIcon: Icons.playbackBarNextIcon
                        width: 21
                        height: 21
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: PlayService.next()
                    }
                    IconButton {
                        property var currentMode: playbackModes[0]
                        property var playbackModes: [PlayService.Sequentially, PlayService.ListLoop, PlayService.SingleLoop, PlayService.Shuffle]
                        property var playbackModeIcons: [Icons.playbackModeSequentialIcon, Icons.playbackModeListLoopIcon, Icons.playbackModeSingleLoopIcon, Icons.playbackModeShuffleIcon]
                        icon: playbackModeIcons[currentMode]
                        hoveredIcon: playbackModeIcons[currentMode]
                        width: 23
                        height: 23
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: {
                            currentMode++
                            if (currentMode > playbackModes.length)
                                currentMode = 0
                            PlayService.setPlaybackMode(currentMode)
                        }
                    }
                }
                Row {
                    Label {
                        id: currentTime
                        text: Utils.formatTime(playbackSlider.value)
                        width: 50
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 12
                    }
                    UuSlider {
                        id: playbackSlider
                        width: 310
                        from: 0
                        to: PlayService.duration
                        value: PlayService.position
                        onMoved: PlayService.position = this.value
                        HoverHandler {
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                    Label {
                        id: totalTime
                        text: Utils.formatTime(playbackSlider.to)
                        width: 50
                        verticalAlignment: Text.AlignVCenter
                        font.pixelSize: 12
                    }
                }
            }
        }
    }
}
