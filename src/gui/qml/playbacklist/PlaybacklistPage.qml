import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Effects
import QtQuick.Layouts

import components 1.0
import service.api 1.0

Popup {
    id: popup
    modal: true
    focus: true
    padding: 0
    dim: false
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    background: Rectangle {
        color: "transparent"
    }

    MultiEffect {
        id: effect
        source: container
        anchors.fill: container
        shadowBlur: 0.2
        shadowColor: "gray"
        shadowEnabled: true
        shadowVerticalOffset: 0
        shadowHorizontalOffset: 0
        shadowOpacity: 1
        shadowScale: 1.0
    }

    UScrollBar {
        id: scrollbar
    }

    Rectangle {
        id: container
        anchors.fill: parent
        radius: 8
        color: "#fafafa"

        Column {
            id: containerColumn
            anchors.fill: parent
            anchors.margins: 20
            spacing: 20
            Row {
                id: headerRow
                width: parent.width
                Label {
                    id: playlistLabel
                    text: qsTr("播放列表")
                    font.bold: true
                    font.pointSize: 12
                }
                Label {
                    id: playlistSizeLabel
                    text: repeater.count
                    font.pointSize: 5
                    anchors.top: playlistLabel.top
                }
            }

            Flickable {
                id: flickable
                contentWidth: width
                contentHeight: contentColumn.height // 使用实际内容高度
                width: container.width
                height: parent.height - headerRow.height - containerColumn.spacing // 动态计算高度
                clip: true

                Column {
                    id: contentColumn
                    Repeater {
                        id: repeater
                        model: PlayService.playbacklist
                        PlaybacklistItem {
                            id: playbacklistItem
                            width: parent.width
                            implicitHeight: 70
                        }
                    }
                }
            }
        }
    }
}
