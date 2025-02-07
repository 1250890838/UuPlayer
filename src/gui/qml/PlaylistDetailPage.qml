import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import service 1.0
import assets 1.0
import components 1.0

Flickable {
    id: root
    required property var detail
    contentHeight: columnLayout.implicitHeight
    contentWidth: this.width
    boundsBehavior: Flickable.StopAtBounds
    boundsMovement: Flickable.StopAtBounds
    clip: true
    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AsNeeded
    }
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        Row {
            spacing: 20
            RoundedImage {
                id: coverImage
                radius: 10
                imageUrl: detail.coverUrl
                width: 170
                height: 170
                isTopLeftRounded: true
                isTopRightRounded: true
                isBottomLeftRounded: true
                isBottomRightRounded: true
            }

            Column {
                spacing: 10
                Text {
                    id: name
                    text: detail.name
                    font {
                        bold: true
                        pointSize: 16
                    }
                }
                Text {
                    id: desc
                    width: 548
                    text: detail.desc
                    font.pointSize: 9
                    height: font.pointSize + 2
                    color: "#54534d"
                    wrapMode: Text.WordWrap
                    elide: Text.ElideRight
                }
                Row {
                    height: avatarImage.height
                    RoundedImage {
                        id: avatarImage
                        radius: 10
                        imageUrl: detail.creator.avatarUrl
                        width: 25
                        height: 25
                        isTopLeftRounded: true
                        isTopRightRounded: true
                        isBottomLeftRounded: true
                        isBottomRightRounded: true
                    }
                    spacing: 10
                    Text {
                        id: avatarName
                        text: detail.creator.name
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Text {
                        id: createdTime
                        color: "gray"
                        font.pointSize: 8.5
                        text: Utils.convertMillisecondsToDate(
                                  detail.createTime) + qsTr("创建")
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }

                Item {
                    width: 1
                    height: 25
                }
                Row {
                    spacing: 10
                    TextIconButton {
                        icon: Icons.playIcon
                        width: 95
                        height: 38
                        iconWidth: 10
                        iconHeight: 10
                        text: "播放全部"
                        textColor: "white"
                        textPointSize: 10
                        textBold: true
                        textWeight: Font.DemiBold
                        radius: 8
                        backgroundColor: "#FC3B5B"
                        hoveredBackgroundColor: "#E33552"
                        pressedAction: true
                    }
                    TextIconButton {
                        icon: Icons.subscribedIcon
                        width: 80
                        height: 38
                        iconWidth: 16
                        iconHeight: 16
                        text: detail.subscribedCount
                        textColor: "black"
                        textPointSize: 8.5
                        textBold: true
                        textWeight: Font.DemiBold
                        radius: 8
                        backgroundColor: "#eae1e7"
                        hoveredBackgroundColor: "#e2d9df"
                        pressedAction: true
                    }
                    TextIconButton {
                        icon: Icons.downloadManagerIcon
                        width: 80
                        height: 38
                        iconWidth: 16
                        iconHeight: 16
                        text: "下载"
                        textColor: "black"
                        textPointSize: 10
                        textBold: true
                        textWeight: Font.DemiBold
                        radius: 8
                        backgroundColor: "#eae1e7"
                        hoveredBackgroundColor: "#e2d9df"
                        pressedAction: true
                    }
                }
            }
        }
        Repeater {
            id: mediaItemsRepeater
            model: detail.mediaItemModel
            MediaItem {
                width: columnLayout.width
            }
        }
    }
}
