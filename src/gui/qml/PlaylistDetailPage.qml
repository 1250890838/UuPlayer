import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import service 1.0
import components 1.0

Flickable {
    id: root
    required property var detail
    contentHeight: columnLayout.implicitHeight
    contentWidth: this.width
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
                    color: "#54534d"
                    wrapMode: Text.WordWrap
                }
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
                Row {
                    spacing: 10
                    Text {
                        id: avatarName
                        text: detail.creator.name
                    }
                    Text {
                        id: createdTime
                        color: "gray"
                        font.pointSize: 7
                        text: Utils.convertMillisecondsToDate(detail.createTime)
                    }
                }
            }
        }
    }
}
