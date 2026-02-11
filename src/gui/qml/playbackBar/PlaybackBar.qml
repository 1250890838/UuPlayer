import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import ui_base 1.0
import controller
import App.Enums
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
            spacing: 20
            anchors.leftMargin: 30
            anchors.rightMargin: 30
            AlbumDisplay {
                id: albumDisplay
                implicitHeight: 60
                implicitWidth: 60
                imageUrl: mediaData.album.picUrl
                running: PlayController.isPlaying
                MouseArea {
                    id: albumDisplayMouseArea
                    anchors.fill: parent
                    onClicked: function () {
                        if (lyricsViewPage.state === "opened") {
                            lyricsViewPage.state = "closed"
                        } else {
                            lyricsViewPage.state = "opened"
                        }
                    }
                }
            }

            Column {
                id: nameColumn
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
                Layout.fillWidth: true // 占据剩余空间
                Layout.alignment: Qt.AlignHCenter // 水平居中
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
                        onClicked: PlayController.previous()
                    }
                    IconButton {
                        id: playbackButton
                        icon: PlayController.isPlaying ? Icons.playbackBarPauseIcon : Icons.playbackBarPlayIcon
                        hoveredIcon: this.icon
                        width: 41
                        height: 41
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: {
                            if (PlayController.isPlaying)
                                PlayController.pause()
                            else
                                PlayController.play()
                        }
                    }
                    IconButton {
                        icon: Icons.playbackBarNextIcon
                        hoveredIcon: Icons.playbackBarNextIcon
                        width: 21
                        height: 21
                        anchors.verticalCenter: parent.verticalCenter
                        onClicked: PlayController.next()
                    }
                    IconButton {
                        property var currentMode: playbackModes[0]
                        property var playbackModes: [PlayMode.Sequentially, PlayMode.ListLoop, PlayMode.SingleLoop, PlayMode.Shuffle]
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
                            PlayService.playbackMode = currentMode
                        }
                    }
                }
                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 2
                    Label {
                        id: currentTime
                        anchors.verticalCenter: parent.verticalCenter
                        text: Utils.formatTime(playbackSlider.value)
                        font.pixelSize: 9
                        color: "gray"
                    }
                    UuSlider {
                        id: playbackSlider
                        anchors.verticalCenter: parent.verticalCenter
                        width: 310
                        height: 15
                        from: 0
                        to: PlayController.duration
                        value: PlayController.position
                        onMoved: PlayController.position = this.value
                        HoverHandler {
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                    Label {
                        id: totalTime
                        anchors.verticalCenter: parent.verticalCenter
                        text: Utils.formatTime(playbackSlider.to)
                        font.pixelSize: 9
                        color: "gray"
                    }
                }
            }

            IconButton {
                id: playbacklistButton
                implicitWidth: 21
                implicitHeight: 21
                icon: Icons.playbackBarPlaylistIcon
                hoveredIcon: Icons.playbackBarPlaylistIcon
                Layout.alignment: Qt.AlignCenter
                onClicked: {
                    playbacklistPage.open()
                }
            }

            VolumeControlButton {
                implicitWidth: 20
                implicitHeight: 20
            }
        }
    }
}
