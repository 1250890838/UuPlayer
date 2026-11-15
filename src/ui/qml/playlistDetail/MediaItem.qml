import QtQuick
import QtQuick.Layouts
import QtQuick.Effects

import app
import App.Enums 1.0

Item {
    id: root
    signal playRequested()

    readonly property bool isPlaying: PlayController.playing
                                      && PlayController.currentPlayItem.id === model.id
    readonly property bool isActive: mouseArea.containsMouse
                                     || PlayController.currentPlayItem.id === model.id
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
            id: indexLabel
            visible: !playButton.visible
            text: (index + 1).toString().padStart(2, '0')
            Layout.preferredWidth: 25
        }

        IconButton {
            id: playButton
            visible: root.isActive
            icon: root.isPlaying ? Icons.pauseGrayIcon : Icons.playGrayIcon
            hoveredIcon: Icons.playGrayIcon
            Layout.preferredHeight: indexLabel.implicitHeight
            Layout.preferredWidth: 25
            onClicked: {
                if (PlayController.playing
                        && PlayController.currentPlayItem.id === model.id) {
                    PlayController.pause()
                } else {
                    root.playRequested()
                }
            }
        }
        Row {
            Layout.fillWidth: true
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
            Layout.fillWidth: true
            text: model.album.name
            font {
                pointSize: 8
            }
        }
        Text {
            id: duration
            text: Utils.millisecondsToTime(model.duration)
            Layout.preferredWidth: implicitWidth + 20
        }
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        propagateComposedEvents: true
        hoverEnabled: true
    }
}
