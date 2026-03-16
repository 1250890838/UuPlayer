import QtQuick.Controls
import QtQuick
import QtQuick.Layouts
import QtQuick.Effects

Item {
    id: root
    signal clicked
    property var itemModel: model
    function formatCount(count) {
        if (count >= 1000 && count <= 9999) {
            return (count / 1000).toFixed(1) + "千";
        } else if (count >= 10000) {
            return (count / 10000).toFixed(1) + "万";
        } else {
            return count;
        }
    }
    Item {
        id: container
        anchors.fill: parent
        RoundedImage {
            id: image
            radius: 10
            isTopLeftRounded: true
            isTopRightRounded: true
            imageUrl: itemModel.coverUrl
            width: parent.width
            height: parent.height - 55
            Text {
                id: imageText
                color: "white"
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: 10
                anchors.topMargin: 10
                text: root.formatCount(itemModel.playCount)
                font.bold: true
                font.pointSize: 10
            }
        }

        RoundedRectangle {
            id: descRect
            width: parent.width
            height: 55
            radius: 10
            color: "#FFB6C1"
            x: 0
            y: image.height
            isBottomLeftRounded: true
            isBottomRightRounded: true

            NumberAnimation on height {
                id: heightAnimation1
                running: false
                from: 55
                to: container.height * 0.35 + 55
            }

            NumberAnimation on y {
                id: yAnimation1
                running: false
                from: image.height
                to: image.height - container.height * 0.35
            }

            NumberAnimation on height {
                id: heightAnimation2
                running: false
                from: container.height * 0.35 + 55
                to: 55
            }

            NumberAnimation on y {
                id: yAnimation2
                running: false
                from: image.height - container.height * 0.35
                to: image.height
            }

            Label {
                id: desc
                color: "white"
                font.pointSize: 10.5
                height: 55
                width: parent.width
                padding: 7
                text: itemModel.name
                wrapMode: Text.WordWrap
                elide: Qt.ElideRight
                maximumLineCount: 2
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: root.clicked()
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true
        onHoveredChanged: {
            yAnimation1.running = mouseArea.containsMouse;
            heightAnimation1.running = mouseArea.containsMouse;
            yAnimation2.running = !mouseArea.containsMouse;
            heightAnimation2.running = !mouseArea.containsMouse;
        }
    }
}
