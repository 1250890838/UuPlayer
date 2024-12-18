import QtQuick.Controls
import QtQuick

Item {
    id: root
    implicitWidth: row.width
    implicitHeight: row.height
    required property real iconWidth
    required property real iconHeight
    required property url icon
    required property string text

    property real margins: 0

    signal clicked

    Row {
        id: row
        width: image.width + spacing + text.implicitWidth
        height: Math.max(image.height, text.height)
        spacing: 5
        Image {
            id: image
            source: root.icon
            width: root.iconWidth
            height: root.iconHeight
        }
        Text {
            id: text
            anchors.verticalCenter: parent.verticalCenter
            text: root.text
            color: mouseArea.containsMouse ? "black" : "gray"
        }
    }

    MouseArea {
        id: mouseArea
        width:50
        height:32
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            root.clicked();
        }
    }
}
