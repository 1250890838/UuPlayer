import QtQuick
import QtQuick.Layouts
import QtQuick.Effects

import controller
import components 1.0
import assets 1.0
import App.Enums 1.0

Item {
    id: root
    readonly property bool isPlaying: PlayService.playing
                                      && PlayService.currentPlayItem.id === model.id
    readonly property bool isActive: mouseArea.containsMouse
                                     || PlayService.currentPlayItem.id === model.id
    MultiEffect {
        id: effect
        visible: root.isActive
        source: container
        anchors.fill: container
        shadowBlur: 0.01
        shadowColor: "gray"
        shadowEnabled: true
        shadowVerticalOffset: 0
        shadowHorizontalOffset: 0
        shadowOpacity: 0.3
        shadowScale: 1.0
    }

    Rectangle {
        id: container
        anchors.fill: parent
        radius: 8
        color: root.isActive ? "#ffffff" : "transparent"
    }

    RowLayout {
        id: rowLayout
        anchors.fill: parent
        anchors.leftMargin: 25
        anchors.rightMargin: 25
        spacing: 10
        Text {
            id: index
            visible: !playButton.visible
            text: model.index.toString().padStart(2, '0') // 转换为两位数格式
            Layout.preferredWidth: headerDummyItem.width
        }

        Component {
            id: connectFactory
            Connections {
                id: playSongConnection
                target: NetworkSongService
                property int count: 2
                function onSongUrlStatus(code) {
                    if (code === ErrorCode.NoError) {
                        PlayService.appendMediaId(model.id)
                        PlayService.play(model.id)
                    }
                    count--
                    if (count === 0)
                        playSongConnection.destroy()
                }
                function onSongLyricStatus(code) {
                    if (code === ErrorCode.NoError) {
                        PlayService.currentPlayItemChanged()
                    }
                    count--
                    if (count === 0)
                        playSongConnection.destroy()
                }
            }
        }

        IconButton {
            id: playButton
            visible: root.isActive
            icon: root.isPlaying ? Icons.pauseGrayIcon : Icons.playGrayIcon
            hoveredIcon: Icons.playGrayIcon
            Layout.preferredHeight: index.implicitHeight
            Layout.preferredWidth: headerDummyItem.width
            onClicked: {
                if (PlayService.playing
                        && PlayService.currentPlayItem.id === model.id) {
                    PlayService.pause()
                } else {
                    NetworkSongService.getSongUrl(model.id)
                    NetworkSongService.getSongLyric(model.id)
                    connectFactory.createObject(this)
                }
            }
        }
        Row {
            Layout.preferredWidth: headerTitleItem.width
            spacing: 10
            RoundedImage {
                id: image
                sourceSize: Qt.size(36, 36)
                width: 36
                height: 36
                radius: 5
                imageUrl: model.album.picUrl
                isTopLeftRounded: true
                isTopRightRounded: true
                isBottomLeftRounded: true
                isBottomRightRounded: true
            }
            Column {
                spacing: 5
                width: 2 * (parent.width - image.width) / 3
                Text {
                    id: name
                    width: parent.width
                    elide: Text.ElideRight
                    text: model.name
                    font {
                        pointSize: 8
                    }
                }
                Text {
                    id: artists
                    width: parent.width
                    font {
                        pointSize: 7.5
                    }
                    color: "gray"
                    elide: Text.ElideRight
                    text: model.artists.map(a => a.name).join(' / ')
                }
            }
        }
        Text {
            id: albumName
            Layout.preferredWidth: headerAlbumItem.width
            text: model.album.name
            font {
                pointSize: 8
            }
        }
        Text {
            id: duration
            text: Utils.millisecondsToTime(model.duration)
            Layout.preferredWidth: headerDurationItem.width
        }
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        propagateComposedEvents: true
        hoverEnabled: true
    }
}
