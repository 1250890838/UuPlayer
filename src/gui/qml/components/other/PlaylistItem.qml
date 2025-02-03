import QtQuick.Controls
import QtQuick
import QtQuick.Layouts
import QtQuick.Effects

Item {
    id: root

    // required property var model
    function formatCount(count) {
        if (count >= 1000 && count <= 9999) {
            return (count / 1000).toFixed(1) + "千"
        } else if (count >= 10000) {
            return (count / 10000).toFixed(1) + "万"
        } else {
            return count
        }
    }
    Rectangle {
        id: container
        anchors.fill: parent
        radius: 25
        Column {
            anchors.fill: parent
            spacing: 0
            RoundedImage {
                id: image
                radius: 10
                isTopLeftRounded: true
                isTopRightRounded: true
                imageUrl: model.coverUrl
                width: parent.width
                height: parent.height - 55
                Text {
                    id: imageText
                    color: "white"
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.rightMargin: 10
                    anchors.topMargin: 10
                    text: root.formatCount(model.playCount)
                    font.bold: true
                    font.pointSize: 10
                }
            }

            RoundedRectangle {
                id: descRect
                width: parent.width
                height: 55
                radius: 10
                color: "black"
                isBottomLeftRounded: true
                isBottomRightRounded: true
                Text {
                    color: "white"
                    font.pointSize: 10.5
                    anchors.margins: 7
                    anchors.fill: parent
                    text: model.name
                    wrapMode: Text.WordWrap
                }
            }
        }
    }
}
