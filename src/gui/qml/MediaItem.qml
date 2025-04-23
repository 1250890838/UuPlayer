import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Effects

import service.api 1.0
import components 1.0
import assets 1.0
import network.errorcode 1.0

Item {
    MultiEffect {
        id: effect
        source: container
        anchors.fill: container
        shadowBlur: 0.02
        shadowColor: "gray"
        shadowEnabled: true
        shadowVerticalOffset: 0
    }

    Rectangle {
        id: container
        anchors.fill: parent
        radius: 8
        color: mouseArea.containsMouse ? "#ffffff" : "transparent"
    }

    RowLayout {
        id: rowLayout
        anchors.fill: parent
        Text {
            id: index
            visible: !playButton.visible
            text: model.index.toString().padStart(2, '0') // 转换为两位数格式
            Layout.preferredWidth: headerDummyItem.width
        }
        Connections {
            id: playSongConnection
            target: SongService
            function onSongUrlStatus(code) {
                if (code === ErrorCode.NoError) {
                    PlayService.appendMediaId(model.id)
                }
            }
        }

        IconButton {
            id: playButton
            visible: mouseArea.containsMouse
            icon: Icons.playGrayIcon
            hoveredIcon: Icons.playGrayIcon
            Layout.preferredHeight: index.implicitHeight
            Layout.preferredWidth: headerDummyItem.width
            onClicked: {
                SongService.getSongUrl(model.id)
            }
        }
        Item {
            id: spacer
            Layout.preferredWidth: 20
            Layout.fillHeight: true
        }
        Row {
            Layout.preferredWidth: headerTitleItem.width
            spacing: 10
            RoundedImage {
                id: image
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
                    text: {
                        let result = ""
                        let ars = model.artists
                        let test = model.album
                        for (let t of ars) {
                            result += t.name
                            result += ' / '
                        }
                        return result.substring(0, result.length - 3)
                    }
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
